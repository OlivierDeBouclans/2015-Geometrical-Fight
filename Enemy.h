
#ifndef Enemy_h__
#define Enemy_h__

#include "movingentity.h"
#include "Macros.h"
#include "SteeringBehavior.h"

class Map;

class Enemy: public MovingEntity
{
	public:
		Enemy(int x=DEFAULT_X, int y=DEFAULT_Y, Map* world=NULL);

		~Enemy(void);

		Vector2D getSteeringForce();
		void draw(BITMAP* target) const;
		Rect boundingRect() const;

		SteeringBehavior steeringBehavior;
};

#endif // Enemy_h__

