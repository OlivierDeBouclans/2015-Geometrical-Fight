#include "Map.h"

#include "allegro.h"
#include "Player.h"
#include "Enemy.h"


Map::Map(int width, int height): m_iWidth(width), m_iHeight(height), m_pPlayer(NULL), m_dLastSpawn(clock()), bPause(false)
{
	int x1=OFFSET_X;
	int x2=OFFSET_X+m_iWidth;
	int y1=OFFSET_Y;
	int y2=OFFSET_Y+m_iHeight;

	m_boundingRect.x1=x1;
	m_boundingRect.x2=x2;
	m_boundingRect.y1=y1;
	m_boundingRect.y2=y2;
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
}

void Map::draw(BITMAP* target) const
{
	rectfill(target,OFFSET_X-BORDER_WIDTH,OFFSET_Y-BORDER_WIDTH,OFFSET_X+m_iWidth+BORDER_WIDTH,OFFSET_Y+m_iHeight+BORDER_WIDTH, makecol(255,255,255));
	rectfill(target,OFFSET_X,OFFSET_Y,OFFSET_X+m_iWidth,OFFSET_Y+m_iHeight, makecol(0,0,0));
	//textprintf(target, font, 200, 10, makecol(255,255,255),"d %d",vEnemies.size());
	
	drawPlayerStats(target);
	
	#ifdef DEBUG_BOUNDING_RECT
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	for(unsigned int i=0;i<vXp.size();i++)
		vXp[i]->draw(target);

	m_pPlayer->draw(target);

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

	for(unsigned int i=0;i<vEnemies.size();i++)
		vEnemies[i]->update(dt);

	for(unsigned int i=0;i<vXp.size();i++)
		vXp[i]->update(dt);
}

//////////////////////////////////////////////////////////////////////////

void Map::addPlayer()
{
	m_pPlayer=new Player((OFFSET_X+m_iWidth)/2,(OFFSET_Y+m_iHeight)/2);
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
			e->health-=m_pPlayer->contactDamage/e->defense;
			m_pPlayer->increaseFury(FURY_CONTACT_DAMAGE_ENEMY);
		}

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
	Xp *xp=new Xp(vEnemies[EnemyIndex]->x,vEnemies[EnemyIndex]->y,this);
	vXp.push_back(xp);

	m_pPlayer->increaseFury(FURY_DESTROY_ENEMY);

	delete vEnemies[EnemyIndex];
	vEnemies.erase(vEnemies.begin()+EnemyIndex);
}

//////////////////////////////////////////////////////////////////////////

void Map::hitPlayer(int damage)
{
	m_pPlayer->health-=damage/m_pPlayer->defense;

	if(m_pPlayer->health<=0)
		exit(0);
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

			break;
		}
}

