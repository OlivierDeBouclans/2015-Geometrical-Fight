
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"

class Vector2D;
class Joystick;

class Player:public MovingEntity
{
	public:
		Player(int x, int y, Joystick* joystick=NULL);
		~Player();

		Vector2D getSteeringForce();
		void draw(BITMAP* target);

	private:
		Joystick* m_pJoystick;
};

#endif // Player_h__

