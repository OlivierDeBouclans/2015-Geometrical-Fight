
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"
#include "Macros.h"

class Vector2D;
class Joystick;
class Weapon;

class Player:public MovingEntity
{
	public:
		Player(int x=DEFAULT_X, int y=DEFAULT_Y,Joystick* joystick=NULL);
		~Player();

		Vector2D getSteeringForce();
		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

		void setJoystick(Joystick* joy) {m_pJoystick=joy;}

		int xp;
		int xpNextLevel;
		int fury;
		int furyMax;

	private:
		Joystick* m_pJoystick;
		Weapon* m_pWeapon;
};

#endif // Player_h__

