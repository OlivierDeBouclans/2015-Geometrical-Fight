
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"

class Vector2D;

class Player:public MovingEntity
{
	public:
		Player(int x, int y);
		~Player();

		Vector2D getSteeringForce();
		void draw(BITMAP* target);
};

#endif // Player_h__

