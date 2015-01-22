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
	m_delay=new DelayCall<Player>(*this);
	
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
	lifeSteal     =0;

	agressive_fire_coef     =PLAYER_AGRESSIVE_FIRE_DAMAGE_COEF;
	agressive_contact_coef  =PLAYER_AGRESSIVE_CONTACT_DAMAGE_COEF;
	agressive_defense_coef  =PLAYER_AGRESSIVE_DEFENSE_COEF;
							 
	defensive_fire_coef     =PLAYER_DEFENSIVE_FIRE_DAMAGE_COEF;
	defensive_contact_coef  =PLAYER_DEFENSIVE_CONTACT_DAMAGE_COEF;
	defensive_defense_coef  =PLAYER_DEFENSIVE_DEFENSE_COEF;
	defensive_speed_coef    =PLAYER_DEFENSIVE_SPEED_COEF;
	defensive_shield_max    =PLAYER_DEFENSIVE_SHIELD_MAX;
	defensive_shield        =0;
							 
	sneaky_fire_coef        =PLAYER_SNEAKY_FIRE_DAMAGE_COEF;
	sneaky_contact_coef     =PLAYER_SNEAKY_CONTACT_DAMAGE_COEF;
	sneaky_defense_coef     =PLAYER_SNEAKY_DEFENSE_COEF;
	sneaky_speed_coef       =PLAYER_SNEAKY_SPEED_COEF;
	sneaky_phantom          =false;
							 
	speedy_contact_coef     =PLAYER_SPEEDY_CONTACT_DAMAGE_COEF; 
	speedy_defense_coef     =PLAYER_SPEEDY_DEFENSE_COEF;
	speedy_speed_coef       =PLAYER_SPEEDY_SPEED_COEF;

	cd.add(CHANGE_AGRESSIVE,COOLDOWN_FORM);
	cd.add(CHANGE_SNEAKY,COOLDOWN_FORM);
	cd.add(CHANGE_SPEEDY,COOLDOWN_FORM);
	cd.add(CHANGE_DEFENSIVE,COOLDOWN_FORM);
	cd.add(UNCHANGE,COOLDOWN_FORM);

	cd.add(SPECIAL_SPEEDY,COOLDOWN_SPECIAL);
	cd.add(SPECIAL_DEFENSIVE,COOLDOWN_SPECIAL);
}


Player::~Player(void)
{
	delete m_pWeapon;
	delete m_delay;
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

	int col=color;
	if(sneaky_phantom)
		col/=2;

	triangle(target, ( (int) p3.x), ( (int) p3.y), ( (int) p1.x ), ( (int) p1.y), ( (int) p2.x ), ( (int) p2.y), col);

	/*textprintf(target, font, 200, 10, makecol(255,255,255),"%d",
		m_pWeapon->m_pBullet.size());*/

	#ifdef DEBUG_BOUNDING_RECT
		Rect m_boundingRect=boundingRect();
		rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
	#endif

	if(defensive_shield>0)
	{
		Rect r=boundingRect();
		int x1=r.x1;
		int x2=r.x2;
		int l=defensive_shield;
		rectfill(target,x1,r.y1-7,x1+l,r.y1-3, makecol(128,128,128));
	}

	m_pWeapon->draw(target);
}

//////////////////////////////////////////////////////////////////////////

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
			if(form==AGRESSIVE && cd.isAvailable(UNCHANGE))
			{
				unchangeAgressive();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_AGRESSIVE);
			}
			else if(cd.isAvailable(CHANGE_AGRESSIVE))
			{
				unchange();
				changeAgressive();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_AGRESSIVE);
			}
		}
		else if(m_pJoystick->x)
		{
			if(form==DEFENSIVE && cd.isAvailable(UNCHANGE))
			{
				unchangeDefensive();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_DEFENSIVE);
			}
			else if(cd.isAvailable(CHANGE_DEFENSIVE))
			{
				unchange();
				changeDefensive();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_DEFENSIVE);
			}
		}
		else if(m_pJoystick->y)
		{
			if(form==SPEEDY && cd.isAvailable(UNCHANGE))
			{
				unchangeSpeedy();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_SPEEDY);
			}
			else if(cd.isAvailable(CHANGE_SPEEDY))
			{
				unchange();
				changeSpeedy();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_SPEEDY);
			}
		}
		else if(m_pJoystick->b)
		{
			if(form==SNEAKY && cd.isAvailable(UNCHANGE))
			{
				unchangeSneaky();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_SNEAKY);
			}
			else if(cd.isAvailable(CHANGE_SNEAKY))
			{
				unchange();
				changeSneaky();
				cd.launch(UNCHANGE);
				cd.launch(CHANGE_SNEAKY);
			}
		}

		if(m_pJoystick->lb)
			special();

	}

	m_pWeapon->update(dt);

	if(form!=NORMAL)
		decreaseFury(1);
	if(fury==0)
		unchange();

	for(unsigned int i=0; i<pMap->vEnemies.size();++i)
	if(Map::collide(boundingRect(),pMap->vEnemies[i]->boundingRect()))
		pMap->hitEnemy(i,false);

	m_delay->update();

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
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeAgressive()
{
	if(form!=AGRESSIVE)
		return;

	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;
	form=NORMAL;

	fireDamage/=agressive_fire_coef;
	contactDamage/=agressive_contact_coef;
	defense/=agressive_defense_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeSneaky()
{
	if(form!=SNEAKY)
		return;

	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;
	form=NORMAL;

	fireDamage/=sneaky_fire_coef;
	contactDamage/=sneaky_contact_coef;
	defense/=sneaky_defense_coef;
	maxSpeed/=sneaky_speed_coef;
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeSpeedy()
{
	if(form!=SPEEDY)
		return;

	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;
	form=NORMAL;

	contactDamage/=speedy_contact_coef;
	defense/=speedy_defense_coef;
	maxSpeed/=speedy_speed_coef;

	m_pWeapon->setFireRate(m_pWeapon->fireRate()*PLAYER_SPEEDY_FIRE_RATE_COEF);
}

//////////////////////////////////////////////////////////////////////////

void Player::unchangeDefensive()
{
	if(form!=DEFENSIVE)
		return;

	color=PLAYER_DEFAULT_COL;
	radius=PLAYER_DEFAULT_RADIUS;
	form=NORMAL;

	fireDamage/=defensive_fire_coef;
	contactDamage/=defensive_contact_coef;
	defense/=defensive_defense_coef;
	maxSpeed/=defensive_speed_coef;
	lifeSteal=0;
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

	activeSneaky();
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

	m_pWeapon->setFireRate(m_pWeapon->fireRate()/PLAYER_SPEEDY_FIRE_RATE_COEF);
	
	activeSpeedy();
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
	lifeSteal=PLAYER_DEFENSIVE_LIFE_STEAL;

	activeDefensive();
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

//////////////////////////////////////////////////////////////////////////

void Player::specialSpeedy()
{
	if(!cd.isAvailable(SPECIAL_SPEEDY))
		return;

	Point2D c(x,y);
	c=c+vSpeed*10;

	x=c.x;
	y=c.y;

	cd.launch(SPECIAL_SPEEDY);
}

//////////////////////////////////////////////////////////////////////////

void Player::special()
{
	switch(form)
	{
	case AGRESSIVE:
		//specialeAgressive();
		break;

	case DEFENSIVE:
		specialDefensive();
		break;

	case SNEAKY:
		//specialSneaky();
		break;

	case SPEEDY:
		specialSpeedy();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

void Player::specialDefensive()
{
	if(!cd.isAvailable(SPECIAL_DEFENSIVE))
		return;

	lifeSteal*=2;
	maxSpeed/=100;

	m_delay->call(&Player::specialDefensiveUnchange,2000);
	cd.launch(SPECIAL_DEFENSIVE);
}

//////////////////////////////////////////////////////////////////////////

void Player::steal(int damage)
{
	static float life=0;

	life+=damage*lifeSteal;

	int iLife=(int)life;
	if(iLife>=1)
	{
		health+=iLife;
		life-=iLife;
		if(health>healthMax)
			health=healthMax;
	}
}

//////////////////////////////////////////////////////////////////////////

void Player::specialAgressive()
{

}

//////////////////////////////////////////////////////////////////////////

void Player::specialDefensiveUnchange()
{
	lifeSteal/=2;
	maxSpeed*=100;	
}

//////////////////////////////////////////////////////////////////////////

void Player::activeSpeedy()
{
	maxSpeed*=2;

	m_delay->call(&Player::activeSpeedyUnchange,ACTIVE_SPEEDY_LENGTH);
}

void Player::activeSpeedyUnchange()
{
	maxSpeed/=2;
}

//////////////////////////////////////////////////////////////////////////

void Player::activeDefensive()
{
	defensive_shield=defensive_shield_max;
	m_delay->call(&Player::activeDefensiveUnchange,ACTIVE_DEFENSIVE_LENGTH);
}

void Player::activeDefensiveUnchange()
{
	defensive_shield=0;
}

//////////////////////////////////////////////////////////////////////////

void Player::activeSneaky()
{
	sneaky_phantom=true;
	m_delay->call(&Player::activeSneakyUnchange,ACTIVE_SNEAKY_LENGTH);
}

//////////////////////////////////////////////////////////////////////////

void Player::activeSneakyUnchange()
{
	sneaky_phantom=false;
}

//////////////////////////////////////////////////////////////////////////

void Player::getDamage(int damage)
{
	damage=damage/defense;
	defensive_shield-=damage;

	if(defensive_shield<0)
	{
		health+=defensive_shield;
		defensive_shield=0;
	}
}

