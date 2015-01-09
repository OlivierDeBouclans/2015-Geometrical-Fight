#include "Player.h"
#include "allegro.h"

Player::Player(int x, int y):MovingEntity(x,y)
{
	color=makecol(0,255,0);
}


Player::~Player(void)
{
}

void Player::draw(BITMAP* target)
{
    /**----------------------------------------------------------------------
	/*@Function: Draw
	/*@Description: Render the entity on the target
	/*----------------------------------------------------------------------**/
	Point2D coor=Point2D(x,y);
	Point2D p1=coor+(vHead*1.5)*radius*1.5;
	Point2D p2=coor-(vSide/2)*radius*1.5;
	Point2D p3=coor+(vSide/2)*radius*1.5;

	triangle(target, ( (int) p3.x), ( (int) p3.y), ( (int) p1.x ), ( (int) p1.y), ( (int) p2.x ), ( (int) p2.y), color);
	//rectfill(target,5,25,SCREEN_W-5,SCREEN_H-5, makecol(0,255,0));
}

Vector2D Player::getSteeringForce()
{
	return Vector2D(1,0);
}
