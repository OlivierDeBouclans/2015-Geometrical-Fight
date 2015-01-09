
/**
 * @Project: Geometrical War
 * @Author: Le Bas de Bouclans Olivier
 * @Date: 08/01/2015
 *
 */

#include "allegro.h"
#include "Game.h"

int main(void)
{
	Game game;

	game.init();
	game.play();
	game.exit();

	return 0;
}
END_OF_MAIN()
