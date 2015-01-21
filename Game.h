
/**
 * Main game loop
 */

#ifndef GAME_H
#define GAME_H

class Map;
struct BITMAP;

/************************************************************************/
/*                              Game                                    */
/************************************************************************/

void countLogicUpdate();
void countGameTime();

//volatile int gameTime=0;

class Game
{
	public:
		//Constructor
		Game(void);	

		//Destructor
		~Game(void);

		//Methods
		void init();
		void play();
		void exit();

	private:
		Map*    m_pMap;
		BITMAP* m_pScreenBuffer;
};

#endif

