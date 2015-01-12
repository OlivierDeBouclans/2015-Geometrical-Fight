
#ifndef Macros_h__
#define Macros_h__

#define DEFAULT_RADIUS 15
#define ENEMY_RADIUS 25
#define PLAYER_RADIUS 20

#define DEFAULT_FIRE_RATE 100

#define DEFAULT_COLOR makecol(128,128,128)
#define DEFAULT_X -1
#define DEFAULT_Y -1

#define BULLET_SPEED 5
#define BULLET_SIZE 10

#define DEFAULT_DELAY_SPAWN 1500

#define DEFAULT_HP 5

/************************************************************************/
/* MOVING ENTITY MACROS                                                 */
/************************************************************************/

#define DEFAULT_MASS 50
#define DEFAULT_MAX_SPEED 3
#define DEFAULT_MAX_FORCE 5000

/************************************************************************/
/* MAP MACROS                                                           */
/************************************************************************/

#define BORDER_WIDTH 10
#define OFFSET_X 200
#define OFFSET_Y 50

/************************************************************************/
/* JOYSTICK MACRO                                                       */
/************************************************************************/

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_LB 4
#define BUTTON_RB 5
#define BUTTON_BACK 6
#define BUTTON_START 7

/************************************************************************/
/*STEERING BEHAVIOR MACROS                                              */
/************************************************************************/

#define MAX_DOUBLE 99999999999999999

#define FLEE_DISTANCE 100

#define ARRIVE_RADIUS 300
#define ARRIVE_BRAKE  10000

#define WANDER_JITER 3.14/64

#define OBSTACLE_MINDETECTION 100

#define WALL_FEELERLENGTH 10

#define HIDE_DISTANCE 50
#define HIDE_DISTANCETOFLEE 5000

#define FOLLOW_DISTANCE 50

#define SEPARATION_RADIUS 100
#define ALIGNMENT_RADIUS 100
#define COHESION_RADIUS 100

/************************************************************************/
/* DEBUG MACRO                                                          */
/************************************************************************/

#define DRAW_BOUNDING_RECT

/************************************************************************/
/* MISC MACROS                                                          */
/************************************************************************/

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

#endif // Macros_h__