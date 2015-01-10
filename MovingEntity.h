
/**----------------------------------------------------------------------
// @Class: MovingEntity (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Description for every moving entities of the game. These
// entities use the steering behaviors to update their speed and position.
//----------------------------------------------------------------------**/

#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "Entity.h"
#include "Vector2D.h"

#define DEFAULT_MASS 80
#define DEFAULT_MAX_SPEED 100
#define DEFAULT_MAX_FORCE 100

class MovingEntity: public Entity
{
    public:
        //Constructor
        MovingEntity(int x, int y);
        //Destructor
        ~MovingEntity() {}

        
        virtual Vector2D getSteeringForce()=0;

        /**----------------------------------------------------------------------
        // @Function: Update
        // @Description: Update the speed,position and direction of the entity
        // according to the elapsed time between each update
        //----------------------------------------------------------------------**/
        void update(double Dt);

		virtual void draw(BITMAP* target)=0;

		//Public attributes
        double mass;                        //Mass
        double maxSpeed;                    //Maximum speed
        double maxForce;                    //Maximum force the entity can produce

        Vector2D vSpeed;                     //Current Speed of the entity
        Vector2D vHead;                      //Current direction of the entity
        Vector2D vSide;                      //Vector orthogonal to the current direction
};

#endif // MOVINGENTITY_H
