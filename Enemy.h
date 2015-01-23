
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
		virtual void draw(BITMAP* target) const;
		virtual Rect boundingRect() const=0;
		virtual void update(double dt);

		SteeringBehavior steeringBehavior;
};

class Tracker: public Enemy
{
	public:
		Tracker(int x,int y, Map* world);

		void draw(BITMAP* target) const;
		Rect boundingRect() const;
};

class Dreamer: public Enemy
{
	public:
		Dreamer(int x,int y, Map* world);

		void draw(BITMAP* target) const;
		Rect boundingRect() const;
};

class Xp: public Enemy
{
	public:
		Xp(int x, int y, Map* world);

		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

		int value;
};

class Decoy: public Enemy
{
	public:
		Decoy(int x, int y, Map* world);

		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

};

#endif // Enemy_h__

