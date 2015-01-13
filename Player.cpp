#include "Player.h"

#include "Joystick.h"
#include "Weapon.h"
#include "Macros.h"

#include "allegro.h"

using namespace std;


Player::Player(int x, int y, Joystick* joystick):MovingEntity(x,y), m_pJoystick(joystick)
{
	m_pWeapon=new Weapon(this);
	
	radius        =PLAYER_RADIUS;
	maxSpeed      =PLAYER_SPEED;
	color         =PLAYER_COL;
	health        =PLAYER_HEALTH;
	healthMax     =PLAYER_HEALTH;
	defense       =PLAYER_DEFENSE;
	fireDamage    =PLAYER_FIRE_DAMAGE;
	contactDamage =PLAYER_CONTACT_DAMAGE;

	furyMax       =PLAYER_FURY;
	fury          =0;
	xp            =0;
	xpNextLevel   =1000;
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

	/*textprintf(target, font, 200, 10, makecol(255,255,255),"%d",
		m_pWeapon->m_pBullet.size());*/

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	m_pWeapon->draw(target);
}

Vector2D Player::getSteeringForce()
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
	if (m_pJoystick)
	{
		m_pJoystick->update();
		if(m_pJoystick->a)
			m_pWeapon->fire();
	}

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
