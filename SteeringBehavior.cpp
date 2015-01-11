
/**----------------------------------------------------------------------
// @Class: Steering Behavior (cpp file)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: /10/13
//
// @Description: Describe all of the possible steering behavior
//----------------------------------------------------------------------**/

#include "SteeringBehavior.h"
#include "MovingEntity.h"
#include "Macros.h"

#include <iostream>

Vector2D SteeringBehavior::Seek(Point2D target)
{
    Vector2D desiredSpeed = (target - m_owner->getCoor());
    desiredSpeed = desiredSpeed.Normalize()* m_owner->maxSpeed;

    return desiredSpeed - m_owner->vSpeed;
}

Vector2D SteeringBehavior::Flee(Point2D target)
{
    double FleeDistanceSquared = FLEE_DISTANCE*FLEE_DISTANCE;
    Vector2D desiredSpeed = (m_owner->getCoor() - target);

    if(desiredSpeed.NormSquared() > FleeDistanceSquared)
        return Vector2D(0,0);

    desiredSpeed = desiredSpeed.Normalize()* m_owner->maxSpeed;

    return desiredSpeed - m_owner->vSpeed;
}

Vector2D SteeringBehavior::Arrive(Point2D target)
{
    double radius = ARRIVE_RADIUS;

    Vector2D Totarget = target - m_owner->getCoor();
    double distance = Totarget.Norm();

    if( distance > radius )
        return Seek(target);

    double Speed = distance / ARRIVE_BRAKE;

    if(Speed > m_owner->maxSpeed)
        Speed = m_owner->maxSpeed;

    Vector2D desiredSpeed = Totarget * Speed;

    return desiredSpeed - m_owner->vSpeed ;
}

Vector2D SteeringBehavior::Pursue()
{
    Vector2D ToTarget = m_PursueEntity->getCoor() - m_owner->getCoor();

    double RelativeHeading = m_owner->vHead * m_PursueEntity->vHead;

    //if ahead just go the the target position
    if ((ToTarget * m_owner->vHead > 0) && (RelativeHeading < -0.95)) //acos(0.95)=18 degs
        return Seek(m_PursueEntity->getCoor());


    double LookAheadTime = ToTarget.Norm()*1.5 / (m_owner->maxSpeed + m_PursueEntity->vSpeed.Norm());
    //now seek to the predicted future position of the evader
    return Seek(m_PursueEntity->getCoor() + m_PursueEntity->vSpeed * LookAheadTime);
}

Vector2D SteeringBehavior::Evade()
{
    Vector2D ToTarget = m_EvadeEntity->getCoor() - m_owner->getCoor();

    double LookAheadTime = ToTarget.Norm() / (m_owner->maxSpeed + m_EvadeEntity->vSpeed.Norm());
    //now seek to the predicted future position of the evader
    return Flee(m_EvadeEntity->getCoor() + m_EvadeEntity->vSpeed * LookAheadTime);
}

Vector2D SteeringBehavior::Wander()
{    double jitter = WANDER_JITER;

    static double WanderAngle = 0;

    WanderAngle += jitter*((rand()%1000)-500)/500;

    Point2D m_WanderPoint(m_owner->getCoor()+m_owner->vHead*m_WanderDistance+ m_owner->vSide*m_WanderRadius*sin(WanderAngle)+m_owner->vHead*m_WanderRadius*cos(WanderAngle));

    return Seek(m_WanderPoint);
}

//Vector2D SteeringBehavior::ObstacleAvoidance()
//{
//    double MinDetection = OBSTACLE_MINDETECTION;
//    double DetectionBox = MinDetection + MinDetection*m_owner->vSpeed.NormSquared() / m_owner->maxSpeed*m_owner->maxSpeed;
//
//    /*double locx = DetectionBox;
//    double locy = m_owner->radius;
//
//    Point2D p = m_owner->getCoor() + m_owner->vHead*locx + m_owner->vSide*locy;
//    Point2D p1 = m_owner->getCoor() + m_owner->vSide*locy;
//    Point2D p2 = m_owner->getCoor() + m_owner->vHead*locx;
//    int point[8]={m_owner->getCoor().x,m_owner->getCoor().y,p1.x,p1.y,p.x,p.y,p2.x,p2.y};
//    polygon(buffer, 4, point, makecol(0,255,0));*/
//
//    Obstacle ClosestObject(0,0,0);
//    double MinDistance = MAX_DOUBLE;
//    Point2D LocaleCoor(0,0);
//
//    for (std::vector<Obstacle>::iterator it = m_Obstacles->begin(); it != m_Obstacles->end(); it++)
//    {
//        Vector2D ToTarget = (*it).getCoor() - m_owner->getCoor();
//        double distance = ToTarget.Norm()-(*it).radius;
//
//        if( distance < DetectionBox)
//        {
//            Vector2D p = ToTarget.VectorToLocalSpace(m_owner->vHead,m_owner->vSide);
//            int x= p.x;
//            int y= p.y;
//
//            if( x >= 0)
//            {
//                double expandedRadius = (*it).radius;
//
//                if( y*y < expandedRadius*expandedRadius)
//                {
//                    double SqrtPart = sqrt(expandedRadius*expandedRadius - y*y);
//
//                    double ip = x - SqrtPart;
//                    if (ip <= 0)
//                        ip = x + SqrtPart;
//
//                    if(ip < MinDistance)
//                    {
//                        MinDistance = ip;
//                        ClosestObject = (*it);
//                        LocaleCoor.x=x;
//                        LocaleCoor.y=y;
//                    }
//                }
//            }
//        }
//    }
//
//    if( MinDistance < DetectionBox)
//    {
//        double multiplier = 0.001 + 0.001*(DetectionBox - LocaleCoor.x) / DetectionBox;
//        double BrakingWeight = 1;
//
//        Vector2D SteeringForceLocal( BrakingWeight / (ClosestObject.radius - LocaleCoor.x+0.0000001),(ClosestObject.radius - LocaleCoor.y) * multiplier);
//
//        return SteeringForceLocal.VectorToGlobalSpace(m_owner->vHead,m_owner->vSide);
//    }
//
//    return Vector2D(0,0);
//}

Vector2D SteeringBehavior::WallAvoidance()
{
    double FeelersLength = WALL_FEELERLENGTH;
    Point2D Feelers[3];
    Feelers[0]=m_owner->getCoor() + m_owner->vHead*FeelersLength - m_owner->vSide*FeelersLength;
    Feelers[1]=m_owner->getCoor() + m_owner->vHead*2*FeelersLength;
    Feelers[2]=m_owner->getCoor() + m_owner->vHead*FeelersLength + m_owner->vSide*FeelersLength;

   /* line(buffer,m_owner->getCoor().x,m_owner->getCoor().y,Feelers[0].x,Feelers[0].y,makecol(255,255,255));
    line(buffer,m_owner->getCoor().x,m_owner->getCoor().y,Feelers[1].x,Feelers[1].y,makecol(255,255,255));
    line(buffer,m_owner->getCoor().x,m_owner->getCoor().y,Feelers[2].x,Feelers[2].y,makecol(255,255,255));*/

    /** WALL SPECIFIC **/
    Point2D ScreenTL(10,30);
    Point2D ScreenTR(SCREEN_W-10,30);
    Point2D ScreenBL(10,SCREEN_H-10);
    Point2D ScreenBR(SCREEN_W-10,SCREEN_H-10);

    Point2D Walls[4][2];
    Walls[0][0]=ScreenTL; Walls[0][1]=ScreenTR;
    Walls[1][0]=ScreenTR; Walls[1][1]=ScreenBR;
    Walls[2][0]=ScreenBL; Walls[2][1]=ScreenBR;
    Walls[3][0]=ScreenTL; Walls[3][1]=ScreenBL;

    Vector2D WallsNormal[4];
    WallsNormal[0]=Vector2D(0,1);
    WallsNormal[1]=Vector2D(-1,0);
    WallsNormal[2]=Vector2D(0,-1);
    WallsNormal[3]=Vector2D(1,0);
    /** WALL SPECIFIC **/

    double DistToThisIP = 0.0;
    double DistToClosestIP = MAX_DOUBLE;
    int ClosestWall = -1;
    Vector2D SteeringForce(0,0);
    Point2D IP, ClosestPoint;

    //examine each feeler in turn
    for (int flr=0; flr<3; flr++)
    {
        //run through each wall checking for any intersection points
        for (int w=0; w<4; w++)
        {
            if (IP.Segment2segment(m_owner->getCoor(),Feelers[flr],Walls[w][0], Walls[w][1]))
            {
                DistToThisIP = (m_owner->getCoor() - IP).Norm();
                //is this the closest found so far? If so keep a record
                if (DistToThisIP < DistToClosestIP)
                {
                    DistToClosestIP = DistToThisIP;
                    ClosestWall = w;
                    ClosestPoint = IP;
                }
            }
        }//next wall

        //if an intersection point has been detected, calculate a force
        //that will direct the agent away
        if (ClosestWall >=0)
        {
            //calculate by what distance the projected position of the agent
            //will overshoot the wall
            Vector2D OverShoot = Feelers[flr] - ClosestPoint;

            //create a force in the direction of the wall normal, with a
            //magnitude of the overshoot
            SteeringForce = WallsNormal[ClosestWall] * OverShoot.Norm();
        }
    }//next feeler

    return SteeringForce;
}

Vector2D SteeringBehavior::Interpose()
{
    //first we need to figure out where the two agents are going to be at
    //time T in the future. This is approximated by determining the time
    //taken to reach the midway point at the current time at max speed.
    Vector2D MidPoint = ((m_InterposeEntity1->getCoor()-Point2D(0,0)) + (m_InterposeEntity2->getCoor()-Point2D(0,0))) / 2.0;

    double TimeToReachMidPoint = (m_owner->getCoor() - Point2D(MidPoint.x,MidPoint.y)).Norm() /m_owner->maxSpeed;

    //now we have T, we assume that agent A and agent B will continue on a
    //straight trajectory and extrapolate to get their future positions
    Vector2D APos = (m_InterposeEntity1->getCoor()-Point2D(0,0)) + m_InterposeEntity1->vSpeed * TimeToReachMidPoint;
    Vector2D BPos = (m_InterposeEntity2->getCoor()-Point2D(0,0)) + m_InterposeEntity2->vSpeed * TimeToReachMidPoint;
    //calculate the midpoint of these predicted positions
    MidPoint = (APos + BPos) / 2.0;

    //then steer to arrive at it
    return Arrive(Point2D(MidPoint.x,MidPoint.y));
}

//Vector2D SteeringBehavior::Hide()
//{
//    double HideDistance = HIDE_DISTANCE;
//
//    double MinDistance = MAX_DOUBLE;
//    Point2D ClosestHidePoint(0,0);
//
//    for (std::vector<Obstacle>::iterator it = m_Obstacles->begin(); it != m_Obstacles->end(); it++)
//    {
//        Vector2D ToTarget = ((*it).getCoor() - m_HideEntity->getCoor()).Normalize();
//        Point2D HidePoint = (*it).getCoor() + ToTarget*( (*it).radius + HideDistance);
//
//        double distance = (m_owner->getCoor() - HidePoint).NormSquared();
//        if( distance < MinDistance)
//        {
//            ClosestHidePoint = HidePoint;
//            MinDistance = distance;
//        }
//    }
//
//   //if no suitable obstacles found then evade the target
//   /* if (MinDistance >= HIDE_DISTANCETOFLEE*HIDE_DISTANCETOFLEE)
//    {
//        return Evade(m_HideEntity);
//    }*/
//    //else use Arrive on the hiding spot
//    return Arrive(ClosestHidePoint);
//}

Vector2D SteeringBehavior::FollowPath()
{
    static int i=0;
    static Point2D current=*m_path.begin();
    double MinDistance = FOLLOW_DISTANCE;

    if((m_owner->getCoor() - current).Norm() < MinDistance && i!=-1)
        i++;

    if(i==m_path.size() && m_bPathIsClosed)
        i=0;
    if(i==m_path.size() && !m_bPathIsClosed)
        i=-1;

    if(i==m_path.size()-1 && !m_bPathIsClosed)
    {
        current=m_path.at(i);
        return Arrive(current);
    }
    else if(i!=-1)
    {
        current=m_path.at(i);
        return Seek(current);
    }
	
	return Vector2D(0,0);
}

Vector2D SteeringBehavior::OffsetPursuit()
{
    //calculate the offset’s position in world space
    Point2D GlobOffset = m_PursueEntity->getCoor()+m_PursueEntity->vHead*m_PursueOffset.x + m_PursueEntity->vSide*m_PursueOffset.y;

    Vector2D ToOffset = GlobOffset - m_owner->getCoor();

    //the look-ahead time is proportional to the distance between the m_PursueEntity
    //and the pursuer; and is inversely proportional to the sum of both
    //agents’ velocities
    double LookAheadTime = ToOffset.Norm() / (m_owner->maxSpeed + m_PursueEntity->vSpeed.Norm());

    //now arrive at the predicted future position of the offset
    return Arrive(GlobOffset + m_PursueEntity->vSpeed * LookAheadTime);
}

Vector2D SteeringBehavior::Separation()
{
    Vector2D SteeringForce(0,0);
    double Radius = SEPARATION_RADIUS;

    for (std::vector<MovingEntity*>::iterator it = m_Entities->begin(); it != m_Entities->end(); it++)
    {
        if( (*it) != m_owner)
        {
            Vector2D ToAgent = m_owner->getCoor() - (*it)->getCoor();
            //scale the force inversely proportional to the agent's distance
            //from its neighbor.
            double distance=ToAgent.NormSquared();
            if( distance < (Radius+(*it)->radius)*(Radius+(*it)->radius))
                    SteeringForce += ToAgent / distance;
        }
    }

    return SteeringForce;
}

Vector2D SteeringBehavior::Alignment()
{
    //used to record the average heading of the neighbors
    Vector2D AverageHeading(0,0);
    double Radius = ALIGNMENT_RADIUS;

    //used to count the number of vehicles in the neighborhood
    int NeighborCount = 0;

    //iterate through all the tagged vehicles and sum their heading vectors
    for (std::vector<MovingEntity*>::iterator it = m_Entities->begin(); it != m_Entities->end(); it++)
    {
        if( (*it) != m_owner)
        {
            Vector2D ToAgent = m_owner->getCoor() - (*it)->getCoor();

            double distance=ToAgent.NormSquared();
            if( distance < (Radius+(*it)->radius)*(Radius+(*it)->radius))
            {
                AverageHeading +=(*it)->vHead;
                NeighborCount++;
            }
        }
    }
    //if the neighborhood contained one or more vehicles, average their heading vectors.
    if (NeighborCount > 0)
    {
        AverageHeading /= (double)NeighborCount;
        AverageHeading -= m_owner->vHead;
    }

    return AverageHeading;
}

Vector2D SteeringBehavior::Cohesion()
{
    //first find the center of mass of all the agents
    Point2D CenterOfMass(0,0);
    Vector2D SteeringForce(0,0);
    double Radius = COHESION_RADIUS;
    int NeighborCount = 0;

    //iterate through the neighbors and sum up all the position vectors
    for (std::vector<MovingEntity*>::iterator it = m_Entities->begin(); it != m_Entities->end(); it++)
    {
        if( (*it) != m_owner)
        {
            Vector2D ToAgent = m_owner->getCoor() - (*it)->getCoor();

            double distance=ToAgent.NormSquared();
            if( distance < (Radius+(*it)->radius)*(Radius+(*it)->radius))
            {
                CenterOfMass = CenterOfMass + ( (*it)->getCoor() - Point2D(0,0) );
                NeighborCount++;
            }
        }
    }

    if (NeighborCount > 0)
    {
        //the center of mass is the average of the sum of positions
        CenterOfMass /= (double)NeighborCount;
        //now seek toward that position
        SteeringForce = Seek(CenterOfMass);
    }

    return SteeringForce;
}

Vector2D SteeringBehavior::getSteeringForce()
{
    Vector2D SteeringForce(0,0);
    Vector2D force;

    if (m_bWallAvoidance)
    {
        force = WallAvoidance() * m_dWallAvoidance;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    //if (m_bObstacleAvoidance)
    //{
    //    force = ObstacleAvoidance() * m_dObstacleAvoidance;

    //    if (!AccumulateForce(&SteeringForce, force))
    //        return SteeringForce;
    //}
    //if (m_bHide)
    //{
    //    force = Hide() * m_dHide;

    //    if (!AccumulateForce(&SteeringForce, force))
    //        return SteeringForce;
    //}
    if (m_bPursue)
    {
        force = Pursue() * m_dPursue;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bEvade)
    {
        force = Evade()* m_dEvade;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bInterpose)
    {
        force = Interpose() * m_dInterpose;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bOffsetPursuit)
    {
        force = OffsetPursuit() * m_dOffsetPursuit;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bFollowPath)
    {
        force = FollowPath() * m_dFollowPath;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bSeparation)
    {
        force = Separation() * m_dSeparation;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bCohesion)
    {
        force = Cohesion() * m_dCohesion;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bAlignment)
    {
        force = Alignment()* m_dAlignment;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }
    if (m_bWander)
    {
        force = Wander() * m_dWander;

        if (!AccumulateForce(&SteeringForce, force))
            return SteeringForce;
    }

    return SteeringForce;
}

bool SteeringBehavior::AccumulateForce(Vector2D *RunningTot, Vector2D ForceToAdd)
{
    //calculate how much steering force the vehicle has used so far
    double MagnitudeSoFar = RunningTot->Norm();

    //calculate how much steering force remains to be used by this vehicle
    double MagnitudeRemaining = m_owner->maxForce - MagnitudeSoFar;

    //return false if there is no more force left to use
    if (MagnitudeRemaining <= 0.0)
        return false;

    //calculate the magnitude of the force we want to add
    double MagnitudeToAdd = ForceToAdd.Norm();

    //if the magnitude of the sum of ForceToAdd and the running total
    //does not exceed the maximum force available to this vehicle, just
    //add together. Otherwise add as much of the ForceToAdd vector as
    //possible without going over the max.
    if (MagnitudeToAdd < MagnitudeRemaining)
    {
        *RunningTot += ForceToAdd;
    }
    else
    {
        //add it to the steering force
        *RunningTot += (ForceToAdd / MagnitudeToAdd) * MagnitudeRemaining;
    }

    return true;
}

SteeringBehavior::SteeringBehavior(MovingEntity *owner/*=NULL*/):m_owner(owner)
{
	m_bPursue = false;
	m_bEvade = false;
	m_bWander = false;
	//m_bObstacleAvoidance = false;
	m_bWallAvoidance = false;
	m_bInterpose = false;
	m_bHide = false;
	m_bFollowPath = false;
	m_bOffsetPursuit = false;
	m_bSeparation = false;
	m_bAlignment = false;
	m_bCohesion = false;
}
