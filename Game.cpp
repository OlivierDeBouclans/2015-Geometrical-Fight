#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Joystick.h"

#include "allegro.h"


//////////////////////////////////////////////////////////////////////////

Game::Game(void)
{
	m_pMap=new Map();
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

	//Init screen
	set_color_depth(32);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0))
	{
		allegro_message(allegro_error);
		return;
	}

	m_pScreenBuffer=create_bitmap(SCREEN_W, SCREEN_H);
}

//////////////////////////////////////////////////////////////////////////

void Game::exit()
{
	allegro_exit();
}

//////////////////////////////////////////////////////////////////////////

void Game::play()
{
	Player player(100,100);
	Joystick joystick;
	joystick.init();

	while(!key[KEY_ESC])
	{
		clear(m_pScreenBuffer);
		int timeelapse = 3.5;
		player.update(1);

		m_pMap->draw(m_pScreenBuffer);
		player.draw(m_pScreenBuffer);

		poll_joystick();//joy[0].button[1], joy[0].button[2]
		float a=joy[0].button[8].b;
		float b=joy[0].button[9].b;
		float c=0;//joy[0].stick[0].axis[1].pos;
		float d=0;//joy[0].stick[0].axis[1].d2;
		textprintf(m_pScreenBuffer, font, 200, 10, makecol(255,255,255),
			"1:%f - 2:%f - 3:%f - 4:%f ",a,b,c,d);

		//Buffer's bliting on screen
		acquire_screen();
			blit (m_pScreenBuffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
		release_screen();

		//Adjust fps
		//m_Fps->update();
		//rest(m_Fps->getRestTime());
	}
}
