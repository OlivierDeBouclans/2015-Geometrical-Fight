
/**----------------------------------------------------------------------
// @Class: Steering Behavior
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: Describe all of the possible steering behavior, calculate
// the resulting steering force. Behaviors are:
// Seek: go to a certain point
// Flee: flee from a certain point
// Arrive: go to a certain point and stop there
// Pursue: follow a given entity
// Evade: flee from a given entity
// Wander: move arround randomly
// Obstacle avoidance: avoid obstacles
// Wall avoidance: avoid walls
// Interpose: go between two entities
// Hide: hide behind an obstacle from a given entity
// Follow path: go to each point of path (cirlce path if path is closed)
// Offset puisuite: follow a given entity with a certain offset
// Separation: keep an entity away from its neighbors
// Alignement: keep an entity align with its neighboors
// Cohesion: keep an entity close to it's neighbors
//----------------------------------------------------------------------**/

#ifndef STEERINGBEHAVIOR_H
#define STEERINGBEHAVIOR_H

#include "Vector2D.h"
#include <vector>

class MovingEntity;
class Map;

class SteeringBehavior
{
    public:
        //Constructor
        SteeringBehavior(MovingEntity *owner=NULL);
        //Destructor
        ~SteeringBehavior() {}

        //Behavior function
        Vector2D Seek(Point2D target);
        Vector2D Flee(Point2D target);
        Vector2D Arrive(Point2D target);
        Vector2D Pursue();
        Vector2D Evade();
        Vector2D Wander();
        //Vector2D ObstacleAvoidance();
        Vector2D WallAvoidance();
        Vector2D Interpose();
        //Vector2D Hide();
        Vector2D FollowPath();
        Vector2D OffsetPursuit();
        Vector2D Separation();
        Vector2D Alignment();
        Vector2D Cohesion();

        //Calculate the resultant force of all behaviors
        Vector2D getSteeringForce();

		void setOwner(MovingEntity* owner) {m_owner=owner;}
		void setMap(Map* world) {m_pMap=world;}

        //Activation for each behavior
        void  OnPursue(MovingEntity *target, double weight=1)
            {
                m_bPursue = true;
                m_dPursue = weight;
                m_PursueEntity = target;
            }
        void  OnEvade(MovingEntity *target, double weight=1)
            {
                m_bEvade  = true;
                m_dEvade  = weight;
                m_EvadeEntity = target;
            }
        void  OnWander(double WanderRadius,double WanderDistance, double weight=1)
            {
                m_bWander = true;
                m_dWander = weight;
                m_WanderDistance = WanderDistance;
                m_WanderRadius = WanderRadius;
            }
       /* void  OnObstacleAvoidance(std::vector<Obstacle> *Obstacles, double weight=1)
            {
                m_bObstacleAvoidance = true;
                m_dObstacleAvoidance = weight;
                m_Obstacles=Obstacles;
            }*/
        void  OnWallAvoidance(double weight=1)
            {
                m_bWallAvoidance = true;
                m_dWallAvoidance = weight;
            }
        void  OnInterpose(MovingEntity* AgentA, MovingEntity* AgentB, double weight=1)
            {
                m_bInterpose = true;
                m_dInterpose = weight;
                m_InterposeEntity1 = AgentA;
                m_InterposeEntity2 = AgentB;
            }
       /* void  OnHide(MovingEntity *target, double weight=1)
            {
                m_bHide = true;
                m_dHide = weight;
                m_HideEntity = target;
            }*/
        void  OnFollowPath(std::vector<Point2D> Path, bool closed, double weight=1)
            {
                m_bFollowPath = true;
				m_dFollowPath = weight;
                m_bPathIsClosed = closed;
                m_path = Path;
            }
        void  OnOffsetPursuit(MovingEntity* leader, Vector2D offset, double weight=1)
            {
                m_bOffsetPursuit = true;
                m_dOffsetPursuit = weight;
                m_PursueEntity = leader;
                m_PursueOffset = offset;
            }
        void  OnSeparation(std::vector<MovingEntity*> *EntityList, double weight=1)
            {
                m_bSeparation = true;
                m_dSeparation = weight;
                m_Entities = EntityList;
            }
        void  OnAlignment(std::vector<MovingEntity*> *EntityList, double weight=1)
            {
                m_bAlignment = true;
                m_dAlignment = weight;
                m_Entities = EntityList;
            }
        void  OnCohesion(std::vector<MovingEntity*> *EntityList, double weight=1)
            {
                m_bCohesion = true;
                m_dCohesion = weight;
                m_Entities = EntityList;
            }

    protected:

        //Accumulate force function
        bool AccumulateForce(Vector2D *RunningTot, Vector2D ForceToAdd);

    private:

        //boolean for each behavior
        bool m_bPursue;
        bool m_bEvade;
        bool m_bWander;
        bool m_bObstacleAvoidance;
        bool m_bWallAvoidance;
        bool m_bInterpose;
        bool m_bHide;
        bool m_bFollowPath;
        bool m_bOffsetPursuit;
        bool m_bSeparation;
        bool m_bAlignment;
        bool m_bCohesion;

        //weight for each behavior
        double m_dPursue;
        double m_dEvade;
        double m_dWander;
        double m_dObstacleAvoidance;
        double m_dWallAvoidance;
        double m_dInterpose;
        double m_dHide;
        double m_dFollowPath;
        double m_dOffsetPursuit;
        double m_dSeparation;
        double m_dAlignment;
        double m_dCohesion;

		Map* m_pMap;
        MovingEntity *m_owner;                  //pointer to owner
       // std::vector<Obstacle> *m_Obstacles;     //list of obstacles
		std::vector<MovingEntity*> *m_Entities;     //list of obstacles

        MovingEntity *m_PursueEntity;       //Entity to pursue
        Vector2D m_PursueOffset;            //Offset for pursuit
        MovingEntity *m_EvadeEntity;        //Entity to flee from
        double m_WanderRadius;              //radius of the wander circle
        double m_WanderDistance;            //distance of the wander circle from the entity
        MovingEntity *m_InterposeEntity1;   //Entities to interpose
        MovingEntity *m_InterposeEntity2;   //Entities to interpose
        MovingEntity *m_HideEntity;         //Entity to hide from
        std::vector<Point2D> m_path;        //List of points to follow
        bool m_bPathIsClosed;               //Path is closed for path follow
};

#endif // STEERINGBEHAVIOR_H
