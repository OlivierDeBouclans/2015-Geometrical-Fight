
#include "MovingEntity.h"
#include "Entity.h"
#include "Vector2D.h"

MovingEntity::MovingEntity(int x, int y) : Entity(x,y)
{
	mass     =DEFAULT_MASS;
	maxSpeed =DEFAULT_MAX_SPEED;
	maxForce =DEFAULT_MAX_FORCE;
	vSpeed   =Vector2D(0,0);
	vHead    =Vector2D(rand() % 1000,rand() % 1000).Normalize();
	vSide    =vHead.Ortho();
	health       =DEFAULT_HP;
}

//////////////////////////////////////////////////////////////////////////

void MovingEntity::update(double Dt)
{
	//Calculate resulting steering force
	Vector2D SteeringForce = getSteeringForce();

	//Calculate acceleration with newton law
	Vector2D acceleration = (SteeringForce)/ mass;
								  
	//and so speed
	vSpeed += acceleration * Dt;

	//take care not to exceed max speed
	vSpeed.Truncate(maxSpeed);

	//update coordinate
	Vector2D mouvement=vSpeed*Dt;
	x+=mouvement.x<0?ceil(mouvement.x):floor(mouvement.x);
	y+=mouvement.y<0?ceil(mouvement.y):floor(mouvement.y);

	//Change orientation if speed>0
	double n=vSpeed.NormSquared();
	if(n > 0.00000001)
	{
		vHead = vSpeed / sqrtf(n);
		vSide = vHead.Ortho();
	}
}
