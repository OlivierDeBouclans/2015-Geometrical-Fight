
/**----------------------------------------------------------------------
// @Class: Obstacle (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Description for the obstacles of the game
//----------------------------------------------------------------------**/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Allegro.h"
#include "Entity.h"

#define COLOR makecol(120,120,120)

class Obstacle : public Entity
{
    public:
        //Constructor
        Obstacle(int x, int y, int radius)
        {
            m_coor =Point2D(x,y);
            m_radius =radius;
            m_color = COLOR;
        }
        //Destructor
        ~Obstacle() {}

        //Render the obstacle on the target
        void Draw( BITMAP *target) { circlefill(target,m_coor.x,m_coor.y,m_radius,m_color); }
        //No update needed for an obstacle
        void Update(double Dt) {};

    protected:

    private:
};

#endif // OBSTACLE_H
