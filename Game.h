
/**
 * Main game loop
 */

#ifndef GAME_H
#define GAME_H

#include "allegro.h"
class Map;
//class BITMAP;

/************************************************************************/
/*                              Game                                    */
/************************************************************************/

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

