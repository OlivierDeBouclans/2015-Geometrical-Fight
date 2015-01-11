#include "Weapon.h"
#include "Bullet.h"
#include "Map.h"

using namespace std;

Weapon::Weapon(MovingEntity* owner): m_pOwner(owner), m_bLastFire(0), m_bFireRate(DEFAULT_FIRE_RATE)
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
			if(m_pOwner->map->collide(&m_pBullet[i]))
				{
					m_pBullet[i].vSpeed=Vector2D(0,0);
					m_pBullet.erase(m_pBullet.begin()+i);
				}
		}
}

//////////////////////////////////////////////////////////////////////////

void Weapon::fire()
{
	double t=clock();
	if(m_bLastFire+m_bFireRate>t)
		return;
	m_bLastFire=t;
	
	Bullet b(m_pOwner->x,m_pOwner->y);
	b.launch(*m_pOwner);
	m_pBullet.push_back(b);
}

//////////////////////////////////////////////////////////////////////////

void Weapon::draw(BITMAP* target) const
{
	for(unsigned int i=0;i<m_pBullet.size();i++)
		m_pBullet[i].draw(target);

	//textprintf(target, font, 200, 10, makecol(255,255,255),"%d",m_pBullet.size());
}

//////////////////////////////////////////////////////////////////////////