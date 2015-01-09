#include "Map.h"
#include "allegro.h"


Map::Map(void)
{
}


Map::~Map(void)
{
}

void Map::draw(BITMAP* target)
{
	rectfill(target,5,25,SCREEN_W-5,SCREEN_H-5, makecol(255,255,255));
	rectfill(target,5+5,25+5,SCREEN_W-5-5,SCREEN_H-5-5, makecol(0,0,0));
	//textprintf(screenBuffer, font, 200, 10, makecol(255,255,255),"FPS: %f - Rest: %d",m_Fps->getFrameRate(),m_Fps->getRestTime());
}
