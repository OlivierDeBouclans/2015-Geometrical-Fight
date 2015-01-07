
/**----------------------------------------------------------------------
// @Class: Entity
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Description for base entity of the game
//----------------------------------------------------------------------**/

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2D.h"
#include "Allegro.h"

class Entity
{
    public:
        //Constructor
        Entity() {}
        //Destructor
        ~Entity() {};

        //Getter
        const int& GetColor()    const { return m_color;  }
        const int& Getx()        const { return m_coor.x; }
        const int& Gety()        const { return m_coor.y; }
        const int& GetRadius()   const { return m_radius; }
        const Point2D& GetCoor() const { return m_coor;   }

        //Setter
        void SetColor(int val)    { m_color  = val; }
        void Setx(int val)        { m_coor.x = val; }
        void Sety(int val)        { m_coor.y = val; }
        void SetRadius(int val)   { m_radius = val; }
        void PlaceAt(const Point2D& val) { m_coor   = val; }

        //Update the entity
        virtual void Update(double Dt)=0;
        //Render the entity on the target
        virtual void Draw( BITMAP * target)=0;

    protected:
        Point2D m_coor; //coordinate
        int m_color;    //color
        int m_radius;   //colision radius

    private:

};

#endif // ENTITY_H
