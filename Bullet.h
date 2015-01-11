
#ifndef Bullet_h__
#define Bullet_h__

#include "movingentity.h"

#define BULLET_SPEED 15
#define BULLET_SIZE 10

class Vector2D;

class Bullet:public MovingEntity
{
	public:
		Bullet(int x, int y);
		~Bullet();

		void draw(BITMAP* target) const;
		Vector2D getSteeringForce() const;
		Rect boundingRect() const;

		void launch(const MovingEntity& owner);
};

#endif // Bullet_h__

