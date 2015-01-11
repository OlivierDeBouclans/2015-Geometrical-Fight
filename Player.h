
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"

#define PLAYER_RADIUS 20

class Vector2D;
class Joystick;
class Weapon;

class Player:public MovingEntity
{
	public:
		Player(int x, int y, const Map* world,Joystick* joystick=NULL);
		~Player();

		Vector2D getSteeringForce() const;
		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

	private:
		Joystick* m_pJoystick;
		Weapon* m_pWeapon;
};

#endif // Player_h__

