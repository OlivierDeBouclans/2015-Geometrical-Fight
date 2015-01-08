
/**----------------------------------------------------------------------
// @Projet: Steering Behaviors
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 19/10/13
//
// @Description: This projet is an implementation of various steering
// behaviours. The obstacles and starting position of each entity is
// initialize randomly. The project show a flocking behavior with
// a pursuer and two entity hidding from it
//----------------------------------------------------------------------**/

//Include
#include "allegro.h"
#include "MovingEntity.h"
#include "Obstacle.h"
#include "FPSHandler.h"

#include <vector>

#define NB_OBSTACLE 15
#define NB_FLOCK 1

#define COLOR_PURSUER makecol(0,255,0)
#define COLOR_FLOCK   makecol(255,0,0)
#define COLOR_HIDER   makecol(0,0,255)

#define AIMED_FPS 60

/**--------------------------------
// @Function: Main
// @Description: Game's loop
//---------------------------------**/
int main(void)
{
    //init random
    srand(time(NULL));

    //initialize Allegro
    allegro_init();

    //init keyboard
    install_keyboard();
	install_joystick(JOY_TYPE_AUTODETECT);

    // init graphics
    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0))
    {
        allegro_message(allegro_error);
        return 1;
    }

    //Entities initialisation
    //static obstacles
    std::vector<Obstacle> obstacles;
    for(int k=0;k<NB_OBSTACLE;k++)
        obstacles.push_back(Obstacle((rand() % (SCREEN_W-200))+100, (rand() % (SCREEN_H-200))+100, rand() % 30+20));

    //pursue the flock
    MovingEntity pursuer(12,rand() % (SCREEN_W-10)+10, rand() % (SCREEN_H-10)+10,COLOR_PURSUER);
        pursuer.GetBehavior()->OnWallAvoidance();
        pursuer.GetBehavior()->OnObstacleAvoidance(&obstacles,2);
        pursuer.SetMaxSpeed(0.8);

    //hide from the pursuer
    MovingEntity hider1(10,rand() % (SCREEN_W-10)+10, rand() % (SCREEN_H-10)+10,COLOR_HIDER);
        hider1.GetBehavior()->OnWallAvoidance();
        hider1.GetBehavior()->OnObstacleAvoidance(&obstacles,10);
        hider1.GetBehavior()->OnHide(&pursuer);
        hider1.GetBehavior()->OnWander(30+rand()%10,200+rand()%50);
        hider1.SetMaxSpeed(1);

    MovingEntity hider2(10,rand() % (SCREEN_W-10)+10, rand() % (SCREEN_H-10)+10,COLOR_HIDER);
        hider2.GetBehavior()->OnWallAvoidance();
        hider2.GetBehavior()->OnObstacleAvoidance(&obstacles,10);
        hider2.GetBehavior()->OnHide(&pursuer);
        hider2.GetBehavior()->OnWander(30+rand()%10,200+rand()%50,2);
        hider2.SetMaxSpeed(1);

    //flock
    std::vector<MovingEntity*> flock;
    for(int k=0;k<NB_FLOCK;k++)
    {
        MovingEntity *a= new MovingEntity(5,rand() % (SCREEN_W-10)+10, rand() % (SCREEN_H-10)+10,COLOR_FLOCK);
            a->GetBehavior()->OnWander(30+rand()%10,200+rand()%50);
            a->GetBehavior()->OnWallAvoidance();
            a->GetBehavior()->OnObstacleAvoidance(&obstacles,50);
            a->GetBehavior()->OnAlignment(&flock);
            a->GetBehavior()->OnSeparation(&flock);
            a->GetBehavior()->OnCohesion(&flock,0.2);
            a->GetBehavior()->OnEvade(&pursuer);
        flock.push_back(a);
    }
    pursuer.GetBehavior()->OnPursue(flock.at(rand() % NB_FLOCK));

    FPSHandler *m_Fps = new FPSHandler(AIMED_FPS);

    //Game loop
    BITMAP *buffer= create_bitmap(SCREEN_W, SCREEN_H);
    while(!key[KEY_ESC])
    {
        clear(buffer);
        int timeelapse = 3.5;

        //Wall and info display
        rectfill(buffer,5,25,SCREEN_W-5,SCREEN_H-5, makecol(255,255,255));
        rectfill(buffer,5+5,25+5,SCREEN_W-5-5,SCREEN_H-5-5, makecol(0,0,0));
        circlefill(buffer,20,12,5,COLOR_FLOCK);
        textprintf(buffer,font,30,10,makecol(255,255,255),"Flock");
        circlefill(buffer,80,12,5,COLOR_PURSUER);
        textprintf(buffer,font,90,10,makecol(255,255,255),"Pursue");
        circlefill(buffer,150,12,5,COLOR_HIDER);
        textprintf(buffer,font,160,10,makecol(255,255,255),"Hide");
		textprintf(buffer, font, 200, 10, makecol(255,255,255),"FPS: %f - Rest: %d",m_Fps->getFrameRate(),m_Fps->getRestTime());

        //Obstacle display
        for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
            (*it).Draw(buffer);

        //Entities update
        for (std::vector<MovingEntity*>::iterator it = flock.begin(); it != flock.end(); it++)
            (*it)->Update(timeelapse);
        pursuer.Update(timeelapse);
        hider1.Update(timeelapse);
        hider2.Update(timeelapse);

        //Entities display
        for (std::vector<MovingEntity*>::iterator it = flock.begin(); it != flock.end(); it++)
            (*it)->Draw(buffer);
        pursuer.Draw(buffer);
        hider1.Draw(buffer);
        hider2.Draw(buffer);

        //Buffer's blitting on screen
        acquire_screen();
            blit (buffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
        release_screen();

        //Adjust fps
        m_Fps->update();

        rest(m_Fps->getRestTime());
    }

    for (std::vector<MovingEntity*>::iterator it = flock.begin(); it != flock.end(); it++)
            delete(*it);

    //end program
    allegro_exit();

    return 0;
}
END_OF_MAIN()
