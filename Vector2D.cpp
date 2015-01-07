
#include "Vector2D.h"

Vector2D& Vector2D::Rotate(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	float nx = c * x - s * y;
	float ny = s * x + c * y;

	x = nx;
	y = ny;

	return (*this);
}

//Truncate
void Vector2D::Truncate( double max)
{
	float n = NormSquared();

	if(n > max*max )
		(*this) = ((*this) / sqrtf(n)) * max;

}

Vector2D Vector2D::VectorToLocalSpace( Vector2D e1, Vector2D e2)
{
    double det= -e1.x*e2.y+e1.y*e2.x;

    if( det != 0)
    return Vector2D((x*e1.x+y*e2.x)/det,(x*e1.y+y*e2.y)/det);
}

//Return if the 2 segments intersect and give the intersection point in the current point
bool Point2D::Segment2segment(Point2D A,Point2D B,Point2D C,Point2D D)
{
    float Ax = A.x;
    float Ay = A.y;
    float Bx = B.x;
    float By = B.y;
    float Cx = C.x;
    float Cy = C.y;
    float Dx = D.x;
    float Dy = D.y;

    double Sx;
    double Sy;

    if(Ax==Bx)
    {
        if(Cx==Dx) return false;
        else
        {
            double pCD = (Cy-Dy)/(Cx-Dx);
            Sx = Ax;
            Sy = pCD*(Ax-Cx)+Cy;
        }
    }
    else
    {
        if(Cx==Dx)
        {
            double pAB = (Ay-By)/(Ax-Bx);
            Sx = Cx;
            Sy = pAB*(Cx-Ax)+Ay;
        }
        else
        {
            double pCD = (Cy-Dy)/(Cx-Dx);
            double pAB = (Ay-By)/(Ax-Bx);
            double oCD = Cy-pCD*Cx;
            double oAB = Ay-pAB*Ax;
            Sx = (oAB-oCD)/(pCD-pAB);
            Sy = pCD*Sx+oCD;
        }
    }

    if((Sx<Ax && Sx<Bx)|(Sx>Ax && Sx>Bx) | (Sx<Cx && Sx<Dx)|(Sx>Cx && Sx>Dx) | (Sy<Ay && Sy<By)|(Sy>Ay && Sy>By) | (Sy<Cy && Sy<Dy)|(Sy>Cy && Sy>Dy))
        return false;

    x=Sx;
    y=Sy;
    return true;
}