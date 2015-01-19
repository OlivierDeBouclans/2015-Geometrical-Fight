
#ifndef Weapon_h__
#define Weapon_h__

#include <vector>

class Bullet;
class Player;
struct BITMAP;

class Weapon
{
	public:
		Weapon(Player* owner);
		~Weapon(void);

		void fire(bool ahead=true);
		void update(double dt);
		void draw(BITMAP* target) const;

		double dFireRate;
	protected:
		Player* m_pOwner;
		std::vector<Bullet> m_pBullet;
		double m_bLastFire;
};

#endif // Weapon_h__

