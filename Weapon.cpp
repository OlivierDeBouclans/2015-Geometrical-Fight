#include "Weapon.h"

#include "Bullet.h"
#include "Map.h"
#include "Macros.h"
#include "Player.h"
#include "CoolDown.h"

#include "allegro.h"

using namespace std;

Weapon::Weapon(Player* owner): m_pOwner(owner), m_dFireRate(DEFAULT_FIRE_RATE)
{
	cd.add(FIRE,DEFAULT_FIRE_RATE);
}

//////////////////////////////////////////////////////////////////////////

Weapon::~Weapon(void)
{
}

//////////////////////////////////////////////////////////////////////////

void Weapon::update(double dt)
{
	for(unsigned int i=0;i<m_pBullet.size();i++)
		{
			m_pBullet[i].update(dt);

			unsigned int s=m_pOwner->pMap->vEnemies.size();
			unsigned int j;
			for(j=0;j<s;j++)
			{
				if(Map::collide(m_pOwner->pMap->vEnemies[j]->boundingRect(),m_pBullet[i].boundingRect()))
				{
					if(m_pBullet[i].cd.isAvailable(0))
						{
							m_pOwner->pMap->hitEnemy(j);
							m_pBullet[i].cd.launch(0);
						}

					if(!m_pOwner->agressive_piercing)
						m_pBullet.erase(m_pBullet.begin()+i);

					break;
				}
			}

			if(j==s&&m_pOwner->pMap->collide(&m_pBullet[i]))
					m_pBullet.erase(m_pBullet.begin()+i);
		}
}

//////////////////////////////////////////////////////////////////////////

void Weapon::fire(bool ahead)
{
	if(!cd.isAvailable(FIRE))
		return;

	if(m_pOwner->sneaky_phantom)
		return;

	if(m_pOwner->form==Player::AGRESSIVE)
	{
		Point2D p1=Point2D(m_pOwner->x,m_pOwner->y)-m_pOwner->vSide*m_pOwner->radius/2;
		Point2D p2=Point2D(m_pOwner->x,m_pOwner->y)+m_pOwner->vSide*m_pOwner->radius/2;

		Bullet b1(p1.x,p1.y,m_pOwner->pMap);
		Bullet b2(p2.x,p2.y,m_pOwner->pMap);

		b1.launch(*m_pOwner, ahead?1:-1);
		m_pBullet.push_back(b1);

		b2.launch(*m_pOwner, ahead?1:-1);
		m_pBullet.push_back(b2);

		play_sample(m_pOwner->pMap->vSoundList[Map::FIRE],20,128,1500,FALSE);
	}
	else
	{
		Bullet b(m_pOwner->x,m_pOwner->y,m_pOwner->pMap);

		if(m_pOwner->form==Player::SNEAKY)
			b.iBounceTime=2;

		b.launch(*m_pOwner, ahead?1:-1);
		m_pBullet.push_back(b);

		play_sample(m_pOwner->pMap->vSoundList[Map::FIRE],20,128,500,FALSE);
	}

	cd.launch(FIRE);
}

//////////////////////////////////////////////////////////////////////////

void Weapon::draw(BITMAP* target) const
{
	for(unsigned int i=0;i<m_pBullet.size();i++)
		m_pBullet[i].draw(target);
}

//////////////////////////////////////////////////////////////////////////

void Weapon::setFireRate(double d)
{
	m_dFireRate=d;
	cd.setCoolDown(FIRE,d);
}

//////////////////////////////////////////////////////////////////////////

void Weapon::specialFire(int nbBullets)
{
	double stepAngle=2*3.14/nbBullets;
	for(int i=0; i<nbBullets;i++)
	{
		Point2D p=Point2D(m_pOwner->x,m_pOwner->y);

		Bullet b(p.x,p.y,m_pOwner->pMap);

		b.vSpeed.x=cos(i*stepAngle)*BULLET_SPEED;
		b.vSpeed.y=sin(i*stepAngle)*BULLET_SPEED;
		m_pBullet.push_back(b);
	}

	play_sample(m_pOwner->pMap->vSoundList[Map::EXPLOSION],60,128,1500,FALSE);
}

//////////////////////////////////////////////////////////////////////////