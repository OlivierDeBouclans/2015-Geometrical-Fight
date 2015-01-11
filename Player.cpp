#include "Player.h"
#include "Joystick.h"
#include "Weapon.h"

#include "allegro.h"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

using namespace std;


Player::Player(int x, int y, const Map* world, Joystick* joystick):MovingEntity(x,y), m_pJoystick(joystick)
{
	color=makecol(0,255,0);
	m_pJoystick->init();
	m_pWeapon=new Weapon(this);
	radius=PLAYER_RADIUS;
	map=world;
}


Player::~Player(void)
{
	delete m_pWeapon;
}

void Player::draw(BITMAP* target) const
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
	//rectfill(target,5,25,SCREEN_W-5,SCREEN_H-5, makecol(0,255,0));
	/*textprintf(target, font, 200, 10, makecol(255,255,255),"%d",
		m_pWeapon->m_pBullet.size());*/

	m_pWeapon->draw(target);
}

Vector2D Player::getSteeringForce() const
{
	if(!m_pJoystick)
		return Vector2D(0,0);
																			   
	const int& x=m_pJoystick->stick_x;
	const int& y=m_pJoystick->stick_y;

	Vector2D steeringForce=Vector2D(1,0)*x+Vector2D(0,1)*y;
	steeringForce.Normalize();

	return (steeringForce*2)-(vSpeed*vSpeed.Norm()*2);
}

//////////////////////////////////////////////////////////////////////////

void Player::update(double dt)
{
	m_pJoystick->update();

	if(m_pJoystick->a)
		m_pWeapon->fire();
	m_pWeapon->update(dt);

	MovingEntity::update(dt);
}

//////////////////////////////////////////////////////////////////////////

Rect Player::boundingRect() const
{
	Point2D coor(x,y);
	Point2D p1=coor+vHead*radius;
	Point2D p2=coor-(vSide/2)*radius;
	Point2D p3=coor+(vSide/2)*radius;

	int x1=min(p1.x,p2.x);
	x1=min(x1,p3.x);

	int x2=max(p1.x,p2.x);
	x2=max(x1,p3.x);

	int y1=min(p1.y,p2.y);
	y1=min(x1,p3.y);

	int y2=max(p1.y,p2.y);
	y2=max(x1,p3.y);

	Rect r;
	r.x1=x1;
	r.x2=x2;
	r.y1=y1;
	r.y2=y2;

	return r;
}
