#include "Weapon.h"

#include "Bullet.h"
#include "Map.h"
#include "Macros.h"
#include "Player.h"

#include "allegro.h"

using namespace std;

Weapon::Weapon(Player* owner): m_pOwner(owner), m_bLastFire(0), dFireRate(DEFAULT_FIRE_RATE)
{
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
					m_pBullet.erase(m_pBullet.begin()+i);
					m_pOwner->pMap->hitEnemy(j);
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
	double t=clock();
	if(m_bLastFire+dFireRate>t)
		return;
	m_bLastFire=t;

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
	}
	else
	{
		Bullet b(m_pOwner->x,m_pOwner->y,m_pOwner->pMap);

		if(m_pOwner->form==Player::SNEAKY)
			b.iBounceTime=2;

		b.launch(*m_pOwner, ahead?1:-1);
		m_pBullet.push_back(b);
	}
}

//////////////////////////////////////////////////////////////////////////

void Weapon::draw(BITMAP* target) const
{
	for(unsigned int i=0;i<m_pBullet.size();i++)
		m_pBullet[i].draw(target);

	//textprintf(target, font, 200, 10, makecol(255,255,255),"%d",m_pBullet.size());
}

//////////////////////////////////////////////////////////////////////////