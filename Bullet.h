
#ifndef Bullet_h__
#define Bullet_h__

#include "movingentity.h"
#include "Macros.h"

class Map;
class Vector2D;

class Bullet:public MovingEntity
{
	public:
		Bullet(int x, int y, Map* world=NULL);
		~Bullet();

		void draw(BITMAP* target) const;
		Vector2D getSteeringForce();
		Rect boundingRect() const;
		void update(double dt);

		void launch(const MovingEntity& owner, int way);

		int iBounceTime;
};

#endif // Bullet_h__

