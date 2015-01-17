#include "Player.h"

#include "Joystick.h"
#include "Weapon.h"
#include "Macros.h"
#include "Map.h"

#include "allegro.h"

using namespace std;


Player::Player(int x, int y, Joystick* joystick):MovingEntity(x,y), m_pJoystick(joystick)
{
	m_pWeapon=new Weapon(this);
	
	form          =NORMAL;

	radius        =PLAYER_DEFAULT_RADIUS;
	maxSpeed      =PLAYER_SPEED;
	color         =PLAYER_DEFAULT_COL;
	health        =PLAYER_HEALTH;
	healthMax     =PLAYER_HEALTH;
	defense       =PLAYER_DEFENSE;
	fireDamage    =PLAYER_FIRE_DAMAGE;
	contactDamage =PLAYER_CONTACT_DAMAGE;

	furyMax       =PLAYER_FURY;
	fury          =0;
	xp            =0;
	xpNextLevel   =1000;

	agressive_fire_coef     =PLAYER_AGRESSIVE_FIRE_DAMAGE_COEF;
	agressive_contact_coef  =PLAYER_AGRESSIVE_CONTACT_DAMAGE_COEF;
	agressive_defense_coef  =PLAYER_AGRESSIVE_DEFENSE_COEF;
							 
	defensive_fire_coef     =PLAYER_DEFENSIVE_FIRE_DAMAGE_COEF;
	defensive_contact_coef  =PLAYER_DEFENSIVE_CONTACT_DAMAGE_COEF;
	defensive_defense_coef  =PLAYER_DEFENSIVE_DEFENSE_COEF;
	defensive_speed_coef    =PLAYER_DEFENSIVE_SPEED_COEF;
							 
	sneaky_fire_coef        =PLAYER_SNEAKY_FIRE_DAMAGE_COEF;
	sneaky_contact_coef     =PLAYER_SNEAKY_CONTACT_DAMAGE_COEF;
	sneaky_defense_coef     =PLAYER_SNEAKY_DEFENSE_COEF;
	sneaky_speed_coef       =PLAYER_SNEAKY_SPEED_COEF;
							 
	speedy_contact_coef     =PLAYER_SPEEDY_CONTACT_DAMAGE_COEF; 
	speedy_defense_coef     =PLAYER_SPEEDY_DEFENSE_COEF;
	speedy_speed_coef       =PLAYER_SPEEDY_SPEED_COEF;
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
		if(m_pJoystick->rt)
			m_pWeapon->fire();
		else if(m_pJoystick->lt)
			m_pWeapon->fire(false);

		if(m_pJoystick->a)
		{
			unchange();
			change(AGRESSIVE);
		}
		else if(m_pJoystick->b)
		{
			unchange();
			change(SNEAKY);
		}
		else if(m_pJoystick->y)
		{
			unchange();
			change(SPEEDY);
		}
		else if(m_pJoystick->x)
		{
			unchange();
			change(DEFENSIVE);
		}

	}

	m_pWeapon->update(dt);

	if(form!=NORMAL)
		decreaseFury(1);
	if(fury==0)
		unchange();

	for(unsigned int i=0; i<pMap->vEnemies.size();++i)
	if(Map::collide(boundingRect(),pMap->vEnemies[i]->boundingRect()))
		pMap->hitEnemy(i,false);

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

//////////////////////////////////////////////////////////////////////////

void Player::unchange()
{
	switch(form)
	{
		case AGRESSIVE:
			unchangeAgressive();
		break;

		case DEFENSIVE:
			unchangeDefensive();
		break;

		case SNEAKY:
			unchangeSneaky();
		break;

		case SPEEDY:
			unchangeSpeedy();
		break;
	}

	form=NORMAL;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeAgressive()
{
	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;

	fireDamage/=agressive_fire_coef;
	contactDamage/=agressive_contact_coef;
	defense/=agressive_defense_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeSneaky()
{
	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;

	fireDamage/=sneaky_fire_coef;
	contactDamage/=sneaky_contact_coef;
	defense/=sneaky_defense_coef;
	maxSpeed/=sneaky_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeSpeedy()
{
	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;

	contactDamage/=speedy_contact_coef;
	defense/=speedy_defense_coef;
	maxSpeed/=speedy_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeDefensive()
{
	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;

	fireDamage/=defensive_fire_coef;
	contactDamage/=defensive_contact_coef;
	defense/=defensive_defense_coef;
	maxSpeed/=defensive_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::change(Form wantedForm)
{
	switch(wantedForm)
	{
	case AGRESSIVE:
		changeAgressive();
	break;

	case DEFENSIVE:
		changeDefensive();
	break;

	case SNEAKY:
		changeSneaky();
	break;

	case SPEEDY:
		changeSpeedy();
	break;
	}
}


//////////////////////////////////////////////////////////////////////////

void Player::changeAgressive()
{
	color=PLAYER_AGRESSIVE_COL;
	radius=PLAYER_AGRESSIVE_RADIUS;
	form=AGRESSIVE;

	fireDamage*=agressive_fire_coef;
	contactDamage*=agressive_contact_coef;
	defense*=agressive_defense_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::changeSneaky()
{
	color=PLAYER_SNEAKY_COL;
	radius=PLAYER_SNEAKY_RADIUS;
	form=SNEAKY;

	fireDamage*=sneaky_fire_coef;
	contactDamage*=sneaky_contact_coef;
	defense*=sneaky_defense_coef;
	maxSpeed*=sneaky_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::changeSpeedy()
{
	color=PLAYER_SPEEDY_COL;
	radius=PLAYER_SPEEDY_RADIUS;
	form=SPEEDY;

	contactDamage*=speedy_contact_coef;
	defense*=speedy_defense_coef;
	maxSpeed*=speedy_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::changeDefensive()
{
	color=PLAYER_DEFENSIVE_COL;
	radius=PLAYER_DEFENSIVE_RADIUS;
	form=DEFENSIVE;

	fireDamage*=defensive_fire_coef;
	contactDamage*=defensive_contact_coef;
	defense*=defensive_defense_coef;
	maxSpeed*=defensive_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::getXp(int value)
{
	xp+=value;

	if(xp>=xpNextLevel)
	{
		xp-=xpNextLevel;
		level++;
		xpNextLevel*=LEVEL_XP_INCREASE;

		healthMax     =PLAYER_HEALTH;
		health        =healthMax;
		defense       *=LEVEL_STATS_INCREASE;
		fireDamage    *=LEVEL_STATS_INCREASE;
		contactDamage *=LEVEL_STATS_INCREASE;
	}
}

//////////////////////////////////////////////////////////////////////////

void Player::increaseFury(int value)
{
	fury+=value;

	if(fury>furyMax)
		fury=furyMax;
}

//////////////////////////////////////////////////////////////////////////

void Player::decreaseFury(int value)
{
	fury-=value;

	if(fury<0)
		fury=0;
}

