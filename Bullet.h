
#ifndef Bullet_h__
#define Bullet_h__

#include "movingentity.h"
#include "Macros.h"

class Vector2D;

class Bullet:public MovingEntity
{
	public:
		Bullet(int x, int y);
		~Bullet();

		void draw(BITMAP* target) const;
		Vector2D getSteeringForce();
		Rect boundingRect() const;

		void launch(const MovingEntity& owner, int way);
};

#endif // Bullet_h__

