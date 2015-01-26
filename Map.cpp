#include "Map.h"

#include "allegro.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Animation.h"

Map::Map(int width, int height): m_iWidth(width), m_iHeight(height), m_pPlayer(NULL), decoy(NULL), m_dLastSpawn(clock()), bPause(false)
{
	int x1=OFFSET_X;
	int x2=OFFSET_X+m_iWidth;
	int y1=OFFSET_Y;
	int y2=OFFSET_Y+m_iHeight;

	m_boundingRect.x1=x1;
	m_boundingRect.x2=x2;
	m_boundingRect.y1=y1;
	m_boundingRect.y2=y2;

	cd.add(HIT_ENEMY,COOLDOWN_CONTACT_DAMAGE);
	cd.add(HIT_PLAYER,COOLDOWN_CONTACT_DAMAGE);

	background=create_bitmap(SCREEN_W, SCREEN_H);
	clear_bitmap(background);
	rectfill(background,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
	rectfill(background,OFFSET_X-BORDER_WIDTH,OFFSET_Y-BORDER_WIDTH,OFFSET_X+m_iWidth+BORDER_WIDTH,OFFSET_Y+m_iHeight+BORDER_WIDTH, makecol(255,255,255));
	rectfill(background,OFFSET_X,OFFSET_Y,OFFSET_X+m_iWidth,OFFSET_Y+m_iHeight, makecol(0,0,0));

	//createSprite();
	loadSound();

	vSpriteList[PLAYER_SPRITE]=new Sprite("Player.bmp",64,64);
	vSpriteList[XP_SPRITE]=new Sprite("Xp.bmp",12,12);
}

//////////////////////////////////////////////////////////////////////////

Map::~Map(void)
{
	delete m_pPlayer;

	while(vEnemies.size())
	{
		delete vEnemies.back();
		vEnemies.pop_back();
	}

	while(vXp.size())
	{
		delete vXp.back();
		vXp.pop_back();
	}

	//delete vSpriteList[PLAYER_SPRITE];
	//delete vSpriteList[XP_SPRITE];
}

void Map::draw(BITMAP* target) const
{

    blit(background,target,0,0,0,0,SCREEN_W-1,SCREEN_H-1);
	drawPlayerStats(target);
	
	#ifdef DEBUG_BOUNDING_RECT
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	for(unsigned int i=0;i<vXp.size();i++)
		vXp[i]->draw(target);

	m_pPlayer->draw(target);

	if(decoy)
		decoy->draw(target);

	for(unsigned int i=0;i<vEnemies.size();i++)
		vEnemies[i]->draw(target);

	if(bPause)
		textprintf(target,font,0-50+(m_boundingRect.x1+m_boundingRect.x2)/2,(m_boundingRect.y1+m_boundingRect.y2)/2,makecol(255,255,255),"PAUSE");
}

bool Map::collide(Entity* e) const
{
	return !collide(m_boundingRect,e->boundingRect());
}

//////////////////////////////////////////////////////////////////////////

bool Map::collide(Rect r1, Rect r2)
{
	return ((r1.x1<r2.x2)&&(r1.x2>r2.x1)&&(r1.y1<r2.y2)&&(r1.y2>r2.y1)); 
}

//////////////////////////////////////////////////////////////////////////

void Map::update(double dt)
{
	m_pPlayer->update(dt);

	if(decoy)
		decoy->update(dt);

	for(unsigned int i=0;i<vEnemies.size();i++)
		vEnemies[i]->update(dt);

	for(unsigned int i=0;i<vXp.size();i++)
		vXp[i]->update(dt);
}

//////////////////////////////////////////////////////////////////////////

void Map::addPlayer()
{
	m_pPlayer=new Player(new Animation(vSpriteList[PLAYER_SPRITE],0),(OFFSET_X+m_iWidth)/2,(OFFSET_Y+m_iHeight)/2);
	m_pPlayer->pMap=this;
	m_pPlayer->setJoystick(joystick);
}

//////////////////////////////////////////////////////////////////////////

void Map::addEnemies()
{
	if(m_dLastSpawn+DEFAULT_DELAY_SPAWN>clock())
		return;
	m_dLastSpawn=clock();

	int x=rand()%m_iWidth+OFFSET_X;	
	int y=rand()%m_iHeight+OFFSET_Y;
	Enemy *e;
	
	if(rand()%10<6)
		e=new Dreamer(x,y,this);
	else
		e=new Tracker(x,y,this);

	e->setLevel((rand()%(m_pPlayer->level+2))+1);
	vEnemies.push_back(e);
}

//////////////////////////////////////////////////////////////////////////

void Map::hitEnemy(int EnemyIndex, bool fireDamage)
{
	MovingEntity* e=vEnemies[EnemyIndex];

	if(fireDamage)
		{
			int damage=m_pPlayer->fireDamage/e->defense;
			e->health-=damage;
			m_pPlayer->increaseFury(FURY_FIRE_DAMAGE_ENEMY);
			m_pPlayer->steal(damage);
		}
	else
		{
			if(!cd.isAvailable(HIT_ENEMY))
				return; 

			e->health-=m_pPlayer->contactDamage/e->defense;
			m_pPlayer->increaseFury(FURY_CONTACT_DAMAGE_ENEMY);

			cd.launch(HIT_ENEMY);
		}

	play_sample(vSoundList[DAMAGE],40,128,800,FALSE);

	if(e->health<=0)
		destroyEnemy(EnemyIndex);
}

//////////////////////////////////////////////////////////////////////////

void Map::drawPlayerStats(BITMAP* target) const
{
	int x=OFFSET_X+m_iWidth+BORDER_WIDTH*2;
	int y=OFFSET_Y-BORDER_WIDTH;

	textprintf(target, font, x-50+BAR_LENGTH/2, y, makecol(255,255,255),"Level:%d Xp:%d",m_pPlayer->level,m_pPlayer->xp);
	y+=20;
	rectfill(target,x,y,x+BAR_LENGTH,y+BAR_WIDTH, makecol(255,255,255));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)),y+BAR_WIDTH-BAR_BORDER, makecol(0,0,0));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)*m_pPlayer->xp/m_pPlayer->xpNextLevel),y+BAR_WIDTH-BAR_BORDER, makecol(0,0,128));
	y+=40;

	textout(target,font,"HP:",x,y-BAR_BORDER+BAR_WIDTH/2,makecol(255,255,255));
	x+=35;
	rectfill(target,x,y,x+BAR_LENGTH,y+BAR_WIDTH, makecol(255,255,255));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)),y+BAR_WIDTH-BAR_BORDER, makecol(0,0,0));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)*m_pPlayer->health/m_pPlayer->healthMax),y+BAR_WIDTH-BAR_BORDER, makecol(0,128,0));
	textprintf_ex(target, font, x-30+BAR_LENGTH/2, y-BAR_BORDER+BAR_WIDTH/2, makecol(255,255,255),-1,"%d/%d",m_pPlayer->health,m_pPlayer->healthMax);
	x-=35;
	y+=20;

	textout(target,font,"Fury:",x,y-BAR_BORDER+BAR_WIDTH/2,makecol(255,255,255));
	x+=35;
	rectfill(target,x,y,x+BAR_LENGTH,y+BAR_WIDTH, makecol(255,255,255));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)),y+BAR_WIDTH-BAR_BORDER, makecol(0,0,0));
	rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)*m_pPlayer->fury/m_pPlayer->furyMax),y+BAR_WIDTH-BAR_BORDER, makecol(255,0,0));
	textprintf_ex(target, font, x-30+BAR_LENGTH/2, y-BAR_BORDER+BAR_WIDTH/2, makecol(255,255,255),-1,"%d/%d",m_pPlayer->fury,m_pPlayer->furyMax);
	x-=35;
	y+=20+BAR_WIDTH;

	textprintf(target, font, x, y, makecol(255,255,255),"Defense:     %f",m_pPlayer->defense);
	y+=20;
	textprintf(target, font, x, y, makecol(255,255,255),"Fire damage: %f",m_pPlayer->fireDamage);
	y+=20;
	textprintf(target, font, x, y, makecol(255,255,255),"Mele damage: %f",m_pPlayer->contactDamage);
	y+=20;

	textprintf(target, font, x, y, makecol(255,255,255),"Max Speed:   %f",m_pPlayer->maxSpeed);
	y+=20;
}

//////////////////////////////////////////////////////////////////////////

void Map::destroyEnemy(int EnemyIndex)
{
	int nbXp=vEnemies[EnemyIndex]->xp;
	int x=vEnemies[EnemyIndex]->x;
	int y=vEnemies[EnemyIndex]->y;

	while(nbXp > 1000)
	{
		Xp *xp=new Xp(Xp::THOUSAND,x+(rand()%60)-30,y+(rand()%60)-30,this);
		vXp.push_back(xp);
		nbXp-=1000;
	}

	while(nbXp > 100)
	{
		Xp *xp=new Xp(Xp::HUNDRED,x+(rand()%60)-30,y+(rand()%60)-30,this);
		vXp.push_back(xp);
		nbXp-=100;
	}

	while(nbXp > 10)
	{
		Xp *xp=new Xp(Xp::TEN,x+(rand()%60)-30,y+(rand()%60)-30,this);
		vXp.push_back(xp);
		nbXp-=10;
	}

	while(nbXp > 1)
	{
		Xp *xp=new Xp(Xp::ONE,x+(rand()%60)-30,y+(rand()%60)-30,this);
		vXp.push_back(xp);
		nbXp-=1;
	}

	m_pPlayer->increaseFury(FURY_DESTROY_ENEMY);

	delete vEnemies[EnemyIndex];
	vEnemies.erase(vEnemies.begin()+EnemyIndex);
	play_sample(vSoundList[EXPLOSION],60,128,1000,FALSE);
}

//////////////////////////////////////////////////////////////////////////

void Map::hitPlayer(int damage)
{
	if(!cd.isAvailable(HIT_PLAYER))
		return; 

	if(m_pPlayer->sneaky_phantom)
		return;

	m_pPlayer->getDamage(damage);

	if(m_pPlayer->health<=0)
		exit(0);

	play_sample(vSoundList[DAMAGE],40,128,1200,FALSE);
	cd.launch(HIT_PLAYER);
}

//////////////////////////////////////////////////////////////////////////

void Map::getXp(Xp* xp)
{
	for(unsigned int i=0; i<vXp.size();++i)
		if(vXp[i]==xp)
		{
			m_pPlayer->getXp(xp->value);

			delete xp;
			vXp.erase(vXp.begin()+i);

			play_sample(vSoundList[XP],90,128,1000,FALSE);

			break;
		}
}

//////////////////////////////////////////////////////////////////////////

void Map::createSprite()
{
	std::vector<Sprite*> l;

	l.push_back(new Sprite("PlayerNormal.bmp",400,400));

		l.push_back(new Sprite("PlayerAgressiveToNormal4.bmp",400,400));
		l.push_back(new Sprite("PlayerAgressiveToNormal3.bmp",400,400));
		l.push_back(new Sprite("PlayerAgressiveToNormal2.bmp",400,400));
		l.push_back(new Sprite("PlayerAgressiveToNormal1.bmp",400,400));
	l.push_back(new Sprite("PlayerAgressive.bmp",400,400));

		l.push_back(new Sprite("PlayerDefensiveToNormal4.bmp",400,400));
		l.push_back(new Sprite("PlayerDefensiveToNormal3.bmp",400,400));
		l.push_back(new Sprite("PlayerDefensiveToNormal2.bmp",400,400));
		l.push_back(new Sprite("PlayerDefensiveToNormal1.bmp",400,400));
	l.push_back(new Sprite("PlayerDefensive.bmp",400,400));

		l.push_back(new Sprite("PlayerSpeedyToNormal4.bmp",400,400));
		l.push_back(new Sprite("PlayerSpeedyToNormal3.bmp",400,400));
		l.push_back(new Sprite("PlayerSpeedyToNormal2.bmp",400,400));
		l.push_back(new Sprite("PlayerSpeedyToNormal1.bmp",400,400));
	l.push_back(new Sprite("PlayerSpeedy.bmp",400,400));

		l.push_back(new Sprite("PlayerSneakyToNormal4.bmp",400,400));
		l.push_back(new Sprite("PlayerSneakyToNormal3.bmp",400,400));
		l.push_back(new Sprite("PlayerSneakyToNormal2.bmp",400,400));
		l.push_back(new Sprite("PlayerSneakyToNormal1.bmp",400,400));
	l.push_back(new Sprite("PlayerSneaky.bmp",400,400));

	int size=64;

	BITMAP*s=create_bitmap(size*l.size(), size);
	rectfill(s, 0, 0, s->w, s->h, makecol(255,0,255));

	for(unsigned int i=0;i<l.size();i++)
		l[i]->draw(s,0,i*size,0,0.16);

	Sprite* sp=new Sprite(s,size,size);

	BITMAP* sprite=create_bitmap(size*l.size(), SPRITE_NUMBER_OF_DIRECTION*size);
	rectfill(sprite, 0, 0, sprite->w, sprite->h, makecol(255,0,255));
	for(int k=0; k<SPRITE_NUMBER_OF_DIRECTION; k++)
	{
		float angle = k*360/SPRITE_NUMBER_OF_DIRECTION;

		for(unsigned int i=0;i<l.size();i++)
			sp->draw(sprite,i,i*size,k*size,1.0,angle+180);
	}

	save_bitmap("Player.bmp", sprite, NULL);

	while(l.size())
	{
		delete l.back();
		l.pop_back();
	}
	delete sp;
	delete sprite;




	l.push_back(new Sprite("Xp1.bmp",200,200));
	l.push_back(new Sprite("Xp10.bmp",200,200));
	l.push_back(new Sprite("Xp100.bmp",200,200));
	l.push_back(new Sprite("Xp1000.bmp",200,200));

	size=12;
	s=create_bitmap(size*l.size(), size);
	rectfill(s, 0, 0, s->w, s->h, makecol(255,0,255));

	for(unsigned int i=0;i<l.size();i++)
		l[i]->draw(s,0,i*size,0,0.06);

	sp=new Sprite(s,size,size);

	sprite=create_bitmap(size*l.size(), SPRITE_NUMBER_OF_DIRECTION*size);
	rectfill(sprite, 0, 0, sprite->w, sprite->h, makecol(255,0,255));
	for(int k=0; k<SPRITE_NUMBER_OF_DIRECTION; k++)
	{
		float angle = k*360/SPRITE_NUMBER_OF_DIRECTION;

		for(unsigned int i=0;i<l.size();i++)
			sp->draw(sprite,i,i*size,k*size,1.0,angle+180);
	}

	save_bitmap("Xp.bmp", sprite, NULL);

	while(l.size())
	{
		delete l.back();
		l.pop_back();
	}
	delete sp;
	delete sprite;
}

void Map::loadSound()
{
	vSoundList[FIRE]=load_sample("Sound/Fire4.wav");
	vSoundList[EXPLOSION]=load_sample("Sound/Explosion.wav");
	vSoundList[SPEED]=load_sample("Sound/Swoosh.wav");
	vSoundList[XP]=load_sample("Sound/Click.wav");
	vSoundList[DAMAGE]=load_sample("Sound/Hit2.wav");
	vSoundList[FORM_OPEN]=load_sample("Sound/Reload.wav");
	vSoundList[FORM_CLOSE]=load_sample("Sound/Reload2.wav");
}

