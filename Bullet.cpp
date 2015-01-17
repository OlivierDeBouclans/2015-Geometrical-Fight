#include "Bullet.h"

#include "allegro.h"

using namespace std;

Bullet::Bullet(int x, int y): MovingEntity(x,y)
{
	color=makecol(255,255,0);
	radius=BULLET_SIZE;
	maxSpeed=BULLET_SPEED*2;
}

//////////////////////////////////////////////////////////////////////////

Bullet::~Bullet(void)
{
}

//////////////////////////////////////////////////////////////////////////

void Bullet::draw(BITMAP* target) const
{
	Point2D coor=Point2D(x,y);
	Point2D p1=(coor+(vHead)*(radius/2))-(vSide)*(radius/4);
	Point2D p2=(coor+(vHead)*(radius/2))+(vSide)*(radius/4);
	Point2D p3=(coor-(vHead)*(radius/2))+(vSide)*(radius/4);
	Point2D p4=(coor-(vHead)*(radius/2))-(vSide)*(radius/4);

	int poly[8]={p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y};

	polygon(target,4,poly,color);

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif
}

//////////////////////////////////////////////////////////////////////////

Vector2D Bullet::getSteeringForce()
{
	return Vector2D(0,0);	
}

//////////////////////////////////////////////////////////////////////////

void Bullet::launch(const MovingEntity& owner, int way)
{
	//double n=owner.vSpeed.Norm();
	vSpeed=owner.vSpeed*BULLET_SPEED*way;
}

//////////////////////////////////////////////////////////////////////////

Rect Bullet::boundingRect() const
{
	Point2D coor(x,y);
	Point2D p1=(coor+(vHead)*(radius/2))-(vSide)*(radius/4);
	Point2D p2=(coor+(vHead)*(radius/2))+(vSide)*(radius/4);
	Point2D p3=(coor-(vHead)*(radius/2))+(vSide)*(radius/4);
	Point2D p4=(coor-(vHead)*(radius/2))-(vSide)*(radius/4);

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
