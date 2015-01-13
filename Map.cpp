#include "Map.h"

#include "allegro.h"
#include "Player.h"
#include "Enemy.h"


Map::Map(int width, int height): m_iWidth(width), m_iHeight(height), m_pPlayer(NULL), m_dLastSpawn(clock())
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
}

void Map::draw(BITMAP* target) const
{
	rectfill(target,OFFSET_X-BORDER_WIDTH,OFFSET_Y-BORDER_WIDTH,OFFSET_X+m_iWidth+BORDER_WIDTH,OFFSET_Y+m_iHeight+BORDER_WIDTH, makecol(255,255,255));
	rectfill(target,OFFSET_X,OFFSET_Y,OFFSET_X+m_iWidth,OFFSET_Y+m_iHeight, makecol(0,0,0));
	//textprintf(screenBuffer, font, 200, 10, makecol(255,255,255),"FPS: %f - Rest: %d",m_Fps->getFrameRate(),m_Fps->getRestTime());
	
	#ifdef DRAW_BOUNDING_RECT
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	m_pPlayer->draw(target);

	for(unsigned int i=0;i<vEnemies.size();i++)
		vEnemies[i]->draw(target);
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

	vEnemies.push_back(e);
}

//////////////////////////////////////////////////////////////////////////

void Map::hitEnemy(int EnemyIndex)
{
	MovingEntity* e=vEnemies[EnemyIndex];

	e->health-=m_pPlayer->fireDamage/e->defense;

	if(e->health<=0)
	{
		delete vEnemies[EnemyIndex];
		vEnemies.erase(vEnemies.begin()+EnemyIndex);
	}
}

