
#ifndef Weapon_h__
#define Weapon_h__

#include <vector>
#include "allegro.h"

#define DEFAULT_FIRE_RATE 100

class Bullet;
class MovingEntity;

class Weapon
{
	public:
		Weapon(MovingEntity* owner);
		~Weapon(void);

		void fire();
		void update(double dt);
		void draw(BITMAP* target) const;

	protected:
		MovingEntity* m_pOwner;
		std::vector<Bullet> m_pBullet;
		double m_bLastFire;
		double m_bFireRate;
};

#endif // Weapon_h__

