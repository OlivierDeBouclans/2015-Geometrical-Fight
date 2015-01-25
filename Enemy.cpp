#include "Enemy.h"

#include "Macros.h"
#include "Map.h"
#include "SteeringBehavior.h"
#include "Player.h"
#include "Sprite.h"

#include "allegro.h"

/************************************************************************/
/*ENEMY                                                                 */
/************************************************************************/

Enemy::Enemy(int x, int y, Map* world): MovingEntity(x,y)
{
	pMap=world;

	steeringBehavior.setOwner(this);
	steeringBehavior.setMap(pMap);
	steeringBehavior.OnWallAvoidance();

	xp=3;
}

//////////////////////////////////////////////////////////////////////////

Enemy::~Enemy(void)
{
}

//////////////////////////////////////////////////////////////////////////

Vector2D Enemy::getSteeringForce()
{
	return steeringBehavior.getSteeringForce();
}

//////////////////////////////////////////////////////////////////////////

void Enemy::update(double dt)
{
  if(Map::collide(boundingRect(),pMap->getPlayer()->boundingRect()))
	pMap->hitPlayer(contactDamage);

  MovingEntity::update(dt);
}

//////////////////////////////////////////////////////////////////////////

void Enemy::draw(BITMAP* target) const
{
	Rect r=boundingRect();
	textprintf(target,font,r.x1,r.y1-10,makecol(255,255,255),"%d",level);

	//rectfill(target,r.x1+35,r.y1,r.x2,r.y1, makecol(255,255,255));
	//rectfill(target,x+BAR_BORDER,y+BAR_BORDER,x+BAR_BORDER+((BAR_LENGTH-2*BAR_BORDER)),y+BAR_WIDTH-BAR_BORDER, makecol(0,0,0));
	int x1=r.x1+10;
	int x2=r.x2;
	int l=health/2;
	rectfill(target,x1,r.y1-7,x1+l,r.y1-3, makecol(128,0,0));
	//textprintf_ex(target, font, x-30+BAR_LENGTH/2, y-BAR_BORDER+BAR_WIDTH/2, makecol(255,255,255),-1,"%d/%d",m_pPlayer->health,m_pPlayer->healthMax);

	#ifdef DEBUG_WANDER
		Point2D WanderPoint(Point2D(x,y)+vHead*steeringBehavior.m_WanderDistance+vSide*steeringBehavior.m_WanderRadius*sin(steeringBehavior.WanderAngle)+vHead*steeringBehavior.m_WanderRadius*cos(steeringBehavior.WanderAngle));
		Point2D p=Point2D(x,y)+vHead*steeringBehavior.m_WanderDistance;
		circle(target,p.x,p.y,steeringBehavior.m_WanderRadius,makecol(0,255,0));
		circlefill(target,WanderPoint.x,WanderPoint.y,6,makecol(0,255,0));
	#endif
}

/************************************************************************/
/* TRACKER                                                              */
/************************************************************************/

Tracker::Tracker(int x,int y, Map* world): Enemy(x,y,world)
{
	radius        =TRACKER_RADIUS;
	maxSpeed      =TRACKER_SPEED;
	color         =TRACKER_COL;
	health        =TRACKER_HEALTH;
	healthMax     =TRACKER_HEALTH;
	defense       =TRACKER_DEFENSE;
	fireDamage    =TRACKER_FIRE_DAMAGE;
	contactDamage =TRACKER_CONTACT_DAMAGE;

	steeringBehavior.OnPursue(world->getPlayer());
}

//////////////////////////////////////////////////////////////////////////

Rect Tracker::boundingRect() const
{
	Point2D coor(x,y);
	Point2D p1=coor+vHead*(radius/2)-vSide*(radius/2);
	Point2D p2=coor+vHead*(radius/2)+vSide*(radius/2);
	Point2D p3=coor-vHead*(radius/2)+vSide*(radius/2);

	int x1=min(p1.x,p2.x);
	x1=min(x1,p3.x);

	int x2=max(p1.x,p2.x);
	x2=max(x2,p3.x);

	int y1=min(p1.y,p2.y);
	y1=min(y1,p3.y);

	int y2=max(p1.y,p2.y);
	y2=max(y2,p3.y);

	Rect r;
	r.x1=x1;
	r.x2=x2;
	r.y1=y1;
	r.y2=y2;

	return r;
}

//////////////////////////////////////////////////////////////////////////

void Tracker::draw(BITMAP* target) const
{
    /**----------------------------------------------------------------------
	/*@Function: Draw
	/*@Description: Render the entity on the target
	/*----------------------------------------------------------------------**/
	Point2D coor=Point2D(x,y);
	Point2D p1=coor+vHead*radius;
	Point2D p2=coor-(vSide/3)*radius;
	Point2D p3=coor+(vSide/3)*radius;

	triangle(target, ( (int) p3.x), ( (int) p3.y), ( (int) p1.x ), ( (int) p1.y), ( (int) p2.x ), ( (int) p2.y), color);

	/*textprintf(target, font, 200, 10, makecol(255,255,255),"%d",
		m_pWeapon->m_pBullet.size());*/

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	Enemy::draw(target);
}

/************************************************************************/
/* DREAMER                                                              */
/************************************************************************/

Dreamer::Dreamer(int x,int y, Map* world): Enemy(x,y,world)
{
	radius        =DREAMER_RADIUS;
	maxSpeed      =DREAMER_SPEED;
	color         =DREAMER_COL;
	health        =DREAMER_HEALTH;
	healthMax     =DREAMER_HEALTH;
	defense       =DREAMER_DEFENSE;
	fireDamage    =DREAMER_FIRE_DAMAGE;
	contactDamage =DREAMER_CONTACT_DAMAGE;

	steeringBehavior.OnWander(30+rand()%10,200+rand()%50,3.14/64);
}

//////////////////////////////////////////////////////////////////////////

Rect Dreamer::boundingRect() const
{
	Point2D coor(x,y);
	Point2D p1=coor+vHead*(radius/2)-vSide*(radius/2);
	Point2D p2=coor+vHead*(radius/2)+vSide*(radius/2);
	Point2D p3=coor-vHead*(radius/2)+vSide*(radius/2);
	Point2D p4=coor-vHead*(radius/2)-vSide*(radius/2);

	int x1=min(p1.x,p2.x);
	x1=min(x1,p3.x);
	x1=min(x1,p4.x);

	int x2=max(p1.x,p2.x);
	x2=max(x2,p3.x);
	x2=max(x2,p4.x);

	int y1=min(p1.y,p2.y);
	y1=min(y1,p3.y);
	y1=min(y1,p4.y);

	int y2=max(p1.y,p2.y);
	y2=max(y2,p3.y);
	y2=max(y2,p4.y);

	Rect r;
	r.x1=x1;
	r.x2=x2;
	r.y1=y1;
	r.y2=y2;

	return r;
}

//////////////////////////////////////////////////////////////////////////

void Dreamer::draw(BITMAP* target) const
{
    /**----------------------------------------------------------------------
	/*@Function: Draw
	/*@Description: Render the entity on the target
	/*----------------------------------------------------------------------**/
	Point2D coor=Point2D(x,y);
	Point2D p1=coor+vHead*(radius/2)-vSide*(radius/2);
	Point2D p2=coor+vHead*(radius/2)+vSide*(radius/2);
	Point2D p3=coor-vHead*(radius/2)+vSide*(radius/2);
	Point2D p4=coor-vHead*(radius/2)-vSide*(radius/2);

	int poly[8]={p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y};

	polygon(target,4,poly,color);

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	Enemy::draw(target);
}

/************************************************************************/
/* Xp                                                                   */
/************************************************************************/

Xp::Xp(Value e, int x, int y, Map* world): Enemy(x,y,world)
{
	radius        =XP_RADIUS;
	maxSpeed      =XP_SPEED;
	color         =XP_COL;
	health        =XP_HEALTH;
	healthMax     =XP_HEALTH;
	defense       =XP_DEFENSE;
	fireDamage    =XP_FIRE_DAMAGE;
	contactDamage =XP_CONTACT_DAMAGE;

	eValue=e;

	switch(e)
	{
		case ONE: 
			value=1; 
		break;

		case TEN: 
			value=10; 
		break;

		case HUNDRED: 
			value=100; 
		break;

		case THOUSAND: 
			value=1000; 
		break;
	}

	headRotationAngle=XP_ROTATION_SPEED;

	//steeringBehavior.OnWander(0,5,0);
	//steeringBehavior.WanderAngle=3.14/4;
	steeringBehavior.OnPursue(world->getPlayer(),XP_PURSUE_RADIUS,5);
}

//////////////////////////////////////////////////////////////////////////

Rect Xp::boundingRect() const
{
	Rect r;
	r.x1=x-radius;
	r.x2=x+radius;
	r.y1=y-radius;
	r.y2=y+radius;

	return r;
}

//////////////////////////////////////////////////////////////////////////

void Xp::draw(BITMAP* target) const
{
	//circlefill(target,x,y,radius,color);
	Point2D coor=Point2D(x,y);
	Point2D p1=coor+vFakeHead*radius;
	Point2D p2=coor-(vFakeSide/3)*radius;
	Point2D p3=coor+(vFakeSide/3)*radius;

	Sprite *s=pMap->vSpriteList[Map::XP_SPRITE];
	double a=(Vector2D(0,1)*vFakeHead);
	double b= (Vector2D(1,0)*vFakeHead)>0 ? -1 : 1;
	double angle = 360+b*acos(a)*360/(2*3.14);
	int frame = ((int) angle % 360)*SPRITE_NUMBER_OF_DIRECTION / 360;
	s->draw(target,s->getNumberOfRow()*frame+eValue,x-s->getFrameWidth()/2,y-s->getFrameHeight()/2);


	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	#ifdef DEBUG_WANDER
			Point2D WanderPoint(Point2D(x,y)+vHead*steeringBehavior.m_WanderDistance+vSide*steeringBehavior.m_WanderRadius*sin(steeringBehavior.WanderAngle)+vHead*steeringBehavior.m_WanderRadius*cos(steeringBehavior.WanderAngle));
			Point2D p=Point2D(x,y)+vHead*steeringBehavior.m_WanderDistance;
			circle(target,p.x,p.y,steeringBehavior.m_WanderRadius,makecol(0,255,0));
			circlefill(target,WanderPoint.x,WanderPoint.y,6,makecol(0,255,0));
	#endif
}

//////////////////////////////////////////////////////////////////////////

void Xp::update(double dt)
{
	MovingEntity::update(dt);

	if(Map::collide(boundingRect(),pMap->getPlayer()->boundingRect()))
		pMap->getXp(this);	   
}


/************************************************************************/
/* Decoy                                                                */
/************************************************************************/

Decoy::Decoy(int x, int y, Map* world): Enemy(x,y,world)
{
	radius        =PLAYER_DEFAULT_RADIUS;
	maxSpeed      =PLAYER_SPEED;
	color         =PLAYER_DEFAULT_COL;
	health        =PLAYER_HEALTH;
	healthMax     =PLAYER_HEALTH;
	defense       =PLAYER_DEFENSE;
	fireDamage    =0;
	contactDamage =0;

	steeringBehavior.OnWander(10+rand()%10,50+rand()%50,3.14/64);
}

void Decoy::draw(BITMAP* target) const
{
	Point2D coor=Point2D(x,y);
	Point2D p1=coor+vHead*radius;
	Point2D p2=coor-(vSide/3)*radius;
	Point2D p3=coor+(vSide/3)*radius;

	triangle(target, ( (int) p3.x), ( (int) p3.y), ( (int) p1.x ), ( (int) p1.y), ( (int) p2.x ), ( (int) p2.y), color);

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif
}

Rect Decoy::boundingRect() const
{
	Point2D coor(x,y);
	Point2D p1=coor+vHead*radius;
	Point2D p2=coor-(vSide/2)*radius;
	Point2D p3=coor+(vSide/2)*radius;

	int x1=min(p1.x,p2.x);
	x1=min(x1,p3.x);

	int x2=max(p1.x,p2.x);
	x2=max(x2,p3.x);

	int y1=min(p1.y,p2.y);
	y1=min(y1,p3.y);

	int y2=max(p1.y,p2.y);
	y2=max(y2,p3.y);

	Rect r;
	r.x1=x1;
	r.x2=x2;
	r.y1=y1;
	r.y2=y2;

	return r;
}

void Decoy::update(double dt)
{
	MovingEntity::update(dt);
}
