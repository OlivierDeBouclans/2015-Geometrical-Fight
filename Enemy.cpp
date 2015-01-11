#include "Enemy.h"
#include "Map.h"
#include "Macros.h"
#include "SteeringBehavior.h"

Enemy::Enemy(int x, int y, Map* world): MovingEntity(x,y)
{
	color=makecol(0,0,255);
	radius=ENEMY_RADIUS;
	pMap=world;

	steeringBehavior.setOwner(this);
	steeringBehavior.setMap(pMap);
	steeringBehavior.OnWander(1,1);
	//steeringBehavior.OnWallAvoidance();
}


Enemy::~Enemy(void)
{
}


void Enemy::draw(BITMAP* target) const
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

Vector2D Enemy::getSteeringForce()
{
	return steeringBehavior.getSteeringForce()/100;
}

//////////////////////////////////////////////////////////////////////////

Rect Enemy::boundingRect() const
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

