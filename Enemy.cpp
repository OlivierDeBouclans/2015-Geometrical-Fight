#include "Enemy.h"

#include "Macros.h"
#include "Map.h"
#include "SteeringBehavior.h"
#include "Player.h"

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

/************************************************************************/
/* TRACKER                                                              */
/************************************************************************/

Tracker::Tracker(int x,int y, Map* world): Enemy(x,y,world)
{
	radius        =TRACKER_RADIUS;
	maxSpeed      =TRACKER_SPEED;
	color         =TRACKER_COL;
	health        =TRACKER_HEALTH;
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

	#ifdef DRAW_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif
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
	defense       =DREAMER_DEFENSE;
	fireDamage    =DREAMER_FIRE_DAMAGE;
	contactDamage =DREAMER_CONTACT_DAMAGE;

	steeringBehavior.OnWander(30+rand()%10,200+rand()%50);
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

	#ifdef DRAW_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif
}