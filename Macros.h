
#ifndef Macros_h__
#define Macros_h__

#define DEFAULT_COLOR makecol(128,128,128)
#define DEFAULT_X -1
#define DEFAULT_Y -1

#define BULLET_SPEED 10
#define BULLET_SIZE 6

#define DEFAULT_DELAY_SPAWN 1500

/************************************************************************/
/*SYSTEM MACROS                                                       */
/************************************************************************/

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define UPDATE_PER_SECOND_LOGIC 60
#define GAME_TIME_REFRESH_MS 100

#define CPU_USAGE_MEAN 30

/************************************************************************/
/* ENTITIES DEFAUTL STATS                                               */
/************************************************************************/

#define DEFAULT_FIRE_RATE 100
#define COOLDOWN_FORM 500
#define COOLDOWN_SPECIAL 1000
#define COOLDOWN_CONTACT_DAMAGE 333
#define COOLDOWN_FURY_DECREASE 250

#define ACTIVE_SPEEDY_LENGTH 1000
#define ACTIVE_DEFENSIVE_LENGTH 2500
#define ACTIVE_SNEAKY_LENGTH 1000

#define PLAYER_FURY 100
#define PLAYER_HEALTH 100

#define PLAYER_DEFAULT_COL   makecol(128,128,128)
#define PLAYER_AGRESSIVE_COL makecol(0,128,0)
#define PLAYER_DEFENSIVE_COL makecol(0,0,128)
#define PLAYER_SPEEDY_COL    makecol(128,128,0)
#define PLAYER_SNEAKY_COL    makecol(128,0,0)

#define PLAYER_DEFAULT_RADIUS 15
#define PLAYER_AGRESSIVE_RADIUS 16
#define PLAYER_DEFENSIVE_RADIUS 19
#define PLAYER_SPEEDY_RADIUS 13
#define PLAYER_SNEAKY_RADIUS 10

#define PLAYER_SPEED 3
#define PLAYER_DEFENSE 1.2
#define PLAYER_FIRE_DAMAGE 10
#define PLAYER_CONTACT_DAMAGE 1

#define PLAYER_AGRESSIVE_FIRE_DAMAGE_COEF 2
#define PLAYER_AGRESSIVE_CONTACT_DAMAGE_COEF 0.5
#define PLAYER_AGRESSIVE_DEFENSE_COEF 0.6

#define PLAYER_DEFENSIVE_FIRE_DAMAGE_COEF 0.5
#define PLAYER_DEFENSIVE_CONTACT_DAMAGE_COEF 2
#define PLAYER_DEFENSIVE_DEFENSE_COEF 1.7
#define PLAYER_DEFENSIVE_SPEED_COEF 0.8
#define PLAYER_DEFENSIVE_LIFE_STEAL 0.1
#define PLAYER_DEFENSIVE_SHIELD_MAX 10

#define PLAYER_SNEAKY_FIRE_DAMAGE_COEF 0.5
#define PLAYER_SNEAKY_CONTACT_DAMAGE_COEF 0.5
#define PLAYER_SNEAKY_DEFENSE_COEF 0.8
#define PLAYER_SNEAKY_SPEED_COEF 1.3
 
#define PLAYER_SPEEDY_CONTACT_DAMAGE_COEF 3 
#define PLAYER_SPEEDY_DEFENSE_COEF 0.5
#define PLAYER_SPEEDY_SPEED_COEF 1.7
#define PLAYER_SPEEDY_FIRE_RATE_COEF 2

#define TRACKER_RADIUS 15
#define TRACKER_SPEED 2
#define TRACKER_COL	makecol(255,0,0)
#define TRACKER_HEALTH 30
#define TRACKER_DEFENSE 1
#define TRACKER_FIRE_DAMAGE 0
#define TRACKER_CONTACT_DAMAGE 10

#define DREAMER_RADIUS 20
#define DREAMER_SPEED 1.8
#define DREAMER_COL makecol(0,0,255)
#define DREAMER_HEALTH 50
#define DREAMER_DEFENSE 1.5
#define DREAMER_FIRE_DAMAGE 0
#define DREAMER_CONTACT_DAMAGE 20

#define XP_RADIUS 4
#define XP_SPEED 3
#define XP_COL makecol(0,255,0)
#define XP_HEALTH 1
#define XP_DEFENSE 1
#define XP_FIRE_DAMAGE 0
#define XP_CONTACT_DAMAGE 0 
#define XP_PURSUE_RADIUS 50

/************************************************************************/
/*LEVEL MACROS                                                      */
/************************************************************************/

#define LEVEL_XP_INCREASE 1.3
#define LEVEL_STATS_INCREASE 1.2

#define FURY_DESTROY_ENEMY 10
#define FURY_FIRE_DAMAGE_ENEMY 1
#define FURY_CONTACT_DAMAGE_ENEMY 3
#define FURY_GET_XP 3
#define FURY_ACTIVE_COST 20
#define FURY_SPECIAL_COST 30

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

#define BAR_LENGTH 200
#define BAR_WIDTH  15
#define BAR_BORDER 2

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

//#define DEBUG_BOUNDING_RECT
#define DEBUG_FPS

/************************************************************************/
/* MISC MACROS                                                          */
/************************************************************************/

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

#endif // Macros_h__