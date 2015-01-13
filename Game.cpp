#include "Game.h"

#include "Map.h"
#include "Joystick.h"
#include "Player.h"
#include "Enemy.h"
#include "FPSHandler.h"

#include "allegro.h"


//////////////////////////////////////////////////////////////////////////

Game::Game(void)
{
	m_pMap=new Map(MAP_WIDTH, MAP_HEIGHT);
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
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0))
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
	Joystick joystick;
	joystick.init();
	m_pMap->joystick=&joystick;
	m_pMap->addPlayer();

	FPSHandler fps(60);

	while(!key[KEY_ESC])
	{
		clear(m_pScreenBuffer);

		m_pMap->addEnemies();
		m_pMap->update(1);
		m_pMap->draw(m_pScreenBuffer);

		#ifdef DEBUG_FPS
			fps.draw(m_pScreenBuffer);
		#endif

		//Buffer's bliting on screen
		acquire_screen();
			blit (m_pScreenBuffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
		release_screen();

		//Adjust fps
		fps.update();
		rest(fps.getRestTime());
	}
}
