#include "Game.h"

#include "Map.h"
#include "Joystick.h"
#include "Player.h"
#include "Enemy.h"

#include "allegro.h"


//////////////////////////////////////////////////////////////////////////
				
volatile int logicUpdateToDo=0;
void countLogicUpdate()
{
	++logicUpdateToDo;
}
END_OF_FUNCTION(countLogicUpdate)

//////////////////////////////////////////////////////////////////////////

volatile int gameTime=0;
void countGameTime()
{
	++gameTime;	 
}
END_OF_FUNCTION(countGameTime)

//////////////////////////////////////////////////////////////////////////

Game::Game(void)
{
}

//////////////////////////////////////////////////////////////////////////

Game::~Game(void)
{
	delete m_pMap;
	delete m_pScreenBuffer;  
}

//////////////////////////////////////////////////////////////////////////

void Game::init()
{
	//Init Allegro
	srand(time(NULL));	 //init random
	allegro_init();
	install_keyboard();
	install_timer();

	LOCK_VARIABLE(logicUpdateToDo);
	LOCK_FUNCTION(countLogicUpdate);
	install_int_ex(countLogicUpdate,BPS_TO_TIMER(UPDATE_PER_SECOND_LOGIC));

	LOCK_VARIABLE(gameTime);
	LOCK_VARIABLE(waiting_time);
	LOCK_FUNCTION(countGameTime);
	install_int(countGameTime,GAME_TIME_REFRESH_MS);

	//Init screen
	set_color_depth(32);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0))
	{
		allegro_message(allegro_error);
		return;
	}

	install_sound(DIGI_AUTODETECT, MIDI_NONE, "");

	m_pScreenBuffer=create_bitmap(SCREEN_W, SCREEN_H);
	clear_bitmap(m_pScreenBuffer);

	m_pMap=new Map(MAP_WIDTH, MAP_HEIGHT);
}

//////////////////////////////////////////////////////////////////////////

void Game::exit()
{
	allegro_exit();
}

//////////////////////////////////////////////////////////////////////////

void Game::play()
{
	Joystick joystick;
	joystick.init();
	m_pMap->joystick=&joystick;
	m_pMap->addPlayer();


	int fps=0;
	int frames_done=0;
	int old_time=0;

	int waiting_time[CPU_USAGE_MEAN];
	int	  logic_time[CPU_USAGE_MEAN];
	int drawing_time[CPU_USAGE_MEAN];

	int ind=0;
	for(unsigned int i=0;i<CPU_USAGE_MEAN;i++)
	{
		waiting_time[i]=0;
		logic_time[i]=0;
		drawing_time[i]=0;
	}

	//int volume=128;
	//int panning=128;
	//int pitch=1000;
	//SAMPLE* samp=load_sample("Sound/Fire.wav");
	//play_sample(samp,128,128,1000,TRUE);

	while(!key[KEY_ESC])
	{
		waiting_time[ind]=clock();
		while(logicUpdateToDo==0)
		{
			rest(1);
		}
		////change the panning
		//if ((key[KEY_LEFT]) && (panning > 0))
		//	panning--;
		//else if ((key[KEY_RIGHT]) && (panning < 255))
		//	panning++;
		////change the pitch (rounding at 512)
		//if ((key[KEY_UP]) && (pitch < 16384))
		//	pitch = ((pitch * 513) / 512) + 1;
		//else if ((key[KEY_DOWN]) && (pitch > 64))
		//	pitch = ((pitch * 511) / 512) - 1;
		////change the volume
		//if (key[KEY_Q] && volume < 255)
		//	volume++;
		//else if (key[KEY_A] && volume > 0)
		//	volume--;
		////adjust the sample
		//adjust_sample(samp, volume, panning, pitch, TRUE);
		//int WHITE=makecol(255,255,255);
		//textout(screen,font,"PlayWave Program (ESC to quit)",0,0,WHITE);
		//textprintf(screen,font,0,10,WHITE,"Sound Driver: %s",digi_driver->name);
		//textout(screen,font,"Playing clapping.wav...",0,20,WHITE);
		//	textout(screen,font,"Left,Right - Pan Left,Right",0,50,WHITE);
		//	textout(screen,font,"Up,Down - Pitch Raise,Lower",0,60,WHITE);
		//	textout(screen,font,"-,+ - Volume Down,Up",0,70,WHITE);

		////display status
		//textprintf(screen,font,0,100,WHITE,"PITCH: %5d", pitch);
		//textprintf(screen,font,0,110,WHITE,"PAN: %5d", panning);
		//textprintf(screen,font,0,120,WHITE,"VOLUME:%5d", volume);

		waiting_time[ind]=clock()-waiting_time[ind];

		logic_time[ind]=clock();
		while(logicUpdateToDo>0)
		{
			int old_logicUpdateToDo=logicUpdateToDo;

			//LOGIC
			if(key[KEY_P])
				m_pMap->bPause=!m_pMap->bPause;

			if(!m_pMap->bPause)
			{
				m_pMap->addEnemies();
				m_pMap->update(1);
			}
			//END

			logicUpdateToDo--;
			if(old_logicUpdateToDo<=logicUpdateToDo)
				break; 
		}
		
		if(gameTime-old_time>=1000/GAME_TIME_REFRESH_MS)//i.e. a second has passed since we last measured the frame rate
		{
			fps=frames_done;
			//fps now holds the the number of frames done in the last second

			//reset for the next second
			frames_done=0;
			old_time=gameTime;
		}
		logic_time[ind]=clock()-logic_time[ind];

		drawing_time[ind]=clock();
		m_pMap->draw(m_pScreenBuffer);
		drawing_time[ind]=clock()-drawing_time[ind];

		ind=(ind+1)%CPU_USAGE_MEAN;
		#ifdef DEBUG_FPS
			int totalGameTime=(gameTime*GAME_TIME_REFRESH_MS/1000);

			int totalW=waiting_time[0];
			int totalL=logic_time[0];
			int totalD=drawing_time[0];
			for(unsigned int i=1;i<CPU_USAGE_MEAN;i++)
			{
				totalW+=waiting_time[i];
				totalL+=logic_time[i];
				totalD+=drawing_time[i];
			}

			float total=totalW+totalL+totalD;
			if(total!=0)
				total=100/total;

			int logic=totalL*total;
			int drawing=totalD*total;
			int waiting=totalW*total;
			textprintf(m_pScreenBuffer, font, 0, 10, makecol(255,255,255),"FPS:%d - Game Time:%d - Logic:%d%% Drawing:%d%% Waiting:%d%%",fps,totalGameTime,logic,drawing,waiting);
		#endif
			
		//Buffer's bliting on screen
		acquire_screen();
			blit (m_pScreenBuffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
		release_screen();

		frames_done++;//we drew a frame!
	}
}

//////////////////////////////////////////////////////////////////////////
