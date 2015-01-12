
#ifndef Macros_h__
#define Macros_h__

#define DEFAULT_FIRE_RATE 100

#define DEFAULT_COLOR makecol(128,128,128)
#define DEFAULT_X -1
#define DEFAULT_Y -1

#define BULLET_SPEED 5
#define BULLET_SIZE 10

#define DEFAULT_DELAY_SPAWN 1500

/************************************************************************/
/*SYSTEM MACROS                                                       */
/************************************************************************/

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

/************************************************************************/
/* ENTITIES DEFAUTL STATS                                               */
/************************************************************************/

#define PLAYER_RADIUS 15
#define PLAYER_SPEED 3
#define PLAYER_COL makecol(0,255,0)
#define PLAYER_HEALTH 100
#define PLAYER_DEFENSE 1.2
#define PLAYER_FIRE_DAMAGE 10
#define PLAYER_CONTACT_DAMAGE 1

#define TRACKER_RADIUS 15
#define TRACKER_SPEED 2
#define TRACKER_COL	makecol(255,0,0)
#define TRACKER_HEALTH 30
#define TRACKER_DEFENSE 1
#define TRACKER_FIRE_DAMAGE 0
#define TRACKER_CONTACT_DAMAGE 10

#define DREAMER_RADIUS 20
#define DREAMER_SPEED 1
#define DREAMER_COL makecol(0,0,255)
#define DREAMER_HEALTH 50
#define DREAMER_DEFENSE 1.5
#define DREAMER_FIRE_DAMAGE 0
#define DREAMER_CONTACT_DAMAGE 20

/************************************************************************/
/* MOVING ENTITY MACROS                                                 */
/************************************************************************/

#define DEFAULT_MASS 50
#define DEFAULT_MAX_SPEED 3
#define DEFAULT_MAX_FORCE 5000

/************************************************************************/
/* MAP MACROS                                                           */
/************************************************************************/

#define BORDER_WIDTH 7
#define OFFSET_X 17
#define OFFSET_Y 17
#define MAP_WIDTH  1300  
#define MAP_HEIGHT 860

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