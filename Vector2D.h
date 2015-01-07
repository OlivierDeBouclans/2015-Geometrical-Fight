
/**----------------------------------------------------------------------
// @Class: VectorD2 and Point2D
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Handling of 2D points and vector
//----------------------------------------------------------------------**/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include <iostream>

/**--------------------------------
// @Class: Vector2D
// @Description: Represent a 2D vector
//---------------------------------**/
class Vector2D
{
    public:
        //Constructors
        Vector2D() {}
        Vector2D(float a, float b): x(a),y(b) {};

        //Coordinates
        float x;
        float y;

        //Operators
        Vector2D operator -(void) const { return (Vector2D(-x, -y)); }
        Vector2D operator +(const Vector2D& v) const { return (Vector2D(x + v.x, y + v.y)); }
        Vector2D operator -(const Vector2D& v) const { return (Vector2D(x - v.x, y - v.y)); }
        Vector2D operator *(const float& t) const { return (Vector2D(x * t, y * t));}
        Vector2D operator /(const float& t) const { float f = 1.0F / t; return (Vector2D(x * f, y * f));}
        bool operator ==(const Vector2D& v) const { return ((x == v.x) && (y == v.y));}
        bool operator !=(const Vector2D& v) const { return ((x != v.x) || (y != v.y));}

        Vector2D& operator +=(const Vector2D& v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }

        Vector2D& operator -=(const Vector2D& v)
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }

        Vector2D& operator *=(float t)
        {
            x *= t;
            y *= t;
            return (*this);
        }

        Vector2D& operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            return (*this);
        }

        Vector2D& operator &=(const Vector2D& v)
        {
            x *= v.x;
            y *= v.y;
            return (*this);
        }

        //Other functions

        //Norm
        float Norm() const { return (sqrtf(x * x + y * y)); }
        float NormSquared() const { return (x * x + y * y);}

        //Dot operator
        float operator *(const Vector2D& v) const { return (x * v.x + y * v.y);}

        //Normalization
        Vector2D Normalize() { return (*this) / sqrtf(x * x + y * y);}

        //Roation
        Vector2D& Rotate(float angle);

        //Truncate
        void Truncate( double max);

        //Return an orthogonal vector
        Vector2D Ortho() { return Vector2D(y,-x);}

        //Convert global vector to local vector in base (e1,e2)
        Vector2D VectorToLocalSpace( Vector2D e1, Vector2D e2);

        Vector2D VectorToGlobalSpace( Vector2D e1, Vector2D e2)
        {
            return Vector2D((x*e1.x+y*e2.x),(x*e1.y+y*e2.y));
        }
};

/**--------------------------------
// @Class: Point2D
// @Description: Represent a 2D point
//---------------------------------**/
class Point2D
{
    public:
        //Constructors
        Point2D() {}
        Point2D(float a, float b) : x(a),y(b) {}

        //Coordinate
        float x;
        float y;

        //Operators
        Point2D operator -(void) const { return (Point2D(-x, -y)); }
        Point2D operator +(const Vector2D& v) const { return (Point2D(x + v.x, y + v.y));}
        Point2D operator -(const Vector2D& v) const { return (Point2D(x - v.x, y - v.y));}
        Vector2D operator -(const Point2D& p) const { return (Vector2D(x - p.x, y - p.y));}
        Point2D operator *(float t) const { return (Point2D(x * t, y * t));}
        Point2D operator /(float t) const { float f = 1.0F / t; return (Point2D(x * f, y * f));}

        Point2D& operator =(const Vector2D& v)
        {
            x = v.x;
            y = v.y;
            return (*this);
        }

        Point2D& operator *=(float t)
        {
            x *= t;
            y *= t;
            return (*this);
        }

        Point2D& operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            return (*this);
        }

        //Other functions

        //Conversion point to vector in global space
        Vector2D Vector() { return Vector2D(x,y);}

        //Return if the 2 segments intersect and give the intersection point in the current point
        bool Segment2segment(Point2D A,Point2D B,Point2D C,Point2D D);
};

#endif //VECTOR2D_H
