
/**----------------------------------------------------------------------
// @Class: MovingEntity (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Description for every moving entitie of the game. These
// entities use the steering behaviors to update their speed and position.
//----------------------------------------------------------------------**/

#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "Entity.h"
#include "Vector2D.h"
#include "SteeringBehavior.h"
#include "Obstacle.h"

#include <vector>
#include <iostream>

#define DEF_MASS 50
#define DEF_MAXSPEED 1.5
#define DEF_MAXFORCE 5000

class MovingEntity : public Entity
{
    public:
        //Constructor
        MovingEntity(int size, int x, int y, int col)
        {
            m_steeringBehavior = new SteeringBehavior(this);
            m_size = size;
            m_coor = Point2D(x,y);
            m_radius=1.5*size;
            m_mass = DEF_MASS;
            m_maxSpeed = DEF_MAXSPEED;
            m_maxForce = DEF_MAXFORCE;
            m_speed = Vector2D(0,0);
            m_head = Vector2D(rand() % 1000,rand() % 1000).Normalize();
            m_side = m_head.Ortho();
            m_color = col;
        }
        //Destructor
        ~MovingEntity() {delete(m_steeringBehavior);}

        //Setter
        void SetMaxSpeed(double val)    { m_maxSpeed = val; }
        void SetMaxForce(double val)    { m_maxForce = val; }
        void SetMass(double val)        { m_mass     = val; }
        void SetSpeed(Vector2D val)     { m_speed    = val; }
        void SetHead(Vector2D val)      { m_head     = val; }
        void SetSide(Vector2D val)      { m_side     = val; }

        //Getter
        double GetMass()                { return m_mass; }
        double GetMaxSpeed()            { return m_maxSpeed; }
        double GetMaxForce()            { return m_maxForce; }
        Vector2D GetSpeed()             { return m_speed; }
        Vector2D GetSide()              { return m_side; }
        Vector2D GetHead()              { return m_head; }
        SteeringBehavior* GetBehavior() { return m_steeringBehavior;}

        /**----------------------------------------------------------------------
        // @Function: Update
        // @Description: Update the speed,position and direction of the enitity
        // according to the elapsed time between each update
        //----------------------------------------------------------------------**/
        void Update(double Dt)
        {
            //Calculate resulting steering force
            Vector2D SteeringForce = m_steeringBehavior->Calculate();

            //Caculate accelaration with newton law
            Vector2D acceleration = (SteeringForce)/ m_mass;

            //and so speed
            m_speed += acceleration * Dt;

            //take care not to exceed max speed
            m_speed.Truncate(m_maxSpeed);

            //update coordinate
            m_coor = m_coor + m_speed*Dt;

            //Change orientation if speed>0
            double n=m_speed.NormSquared();
            if(n > 0.00000001)
            {
                m_head = m_speed / sqrtf(n);
                m_side = m_head.Ortho();
            }
        };

        /**----------------------------------------------------------------------
        // @Function: Draw
        // @Description: Render the entity on the target
        //----------------------------------------------------------------------**/
        void Draw( BITMAP * target)
        {
            Point2D p1=m_coor+(m_head*1.5)*m_size;
            Point2D p2=m_coor-(m_side/2)*m_size;
            Point2D p3=m_coor+(m_side/2)*m_size;

            triangle(target, ( (int) p3.x), ( (int) p3.y), ( (int) p1.x ), ( (int) p1.y), ( (int) p2.x ), ( (int) p2.y), m_color);
        }

    protected:

    private:
        double m_mass;                        //Mass
        double m_maxSpeed;                    //Maximum speed
        double m_maxForce;                    //Maximum force the entity can produce
        int m_size;                           //Size of the entity (size*1.5=collision radius)
        Vector2D m_speed;                     //Current Speed of the entity
        Vector2D m_head;                      //Current direction of the entity
        Vector2D m_side;                      //Vector othogonal to the current direction
        SteeringBehavior *m_steeringBehavior; //Handling of the steering force to apply each update
};

#endif // MOVINGENTITY_H
