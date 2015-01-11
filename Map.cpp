#include "Map.h"
#include "allegro.h"


Map::Map(int width, int height): m_iWidth(width), m_iHeight(height)
{
	int x1=OFFSET_X;
	int x2=OFFSET_X+m_iWidth;
	int y1=OFFSET_Y;
	int y2=OFFSET_Y+m_iHeight;

	m_boundingRect.x1=x1;
	m_boundingRect.x2=x2;
	m_boundingRect.y1=y1;
	m_boundingRect.y2=y2;
}


Map::~Map(void)
{
}

void Map::draw(BITMAP* target) const
{
	rectfill(target,OFFSET_X-BORDER_WIDTH,OFFSET_Y-BORDER_WIDTH,OFFSET_X+m_iWidth+BORDER_WIDTH,OFFSET_Y+m_iHeight+BORDER_WIDTH, makecol(255,255,255));
	rectfill(target,OFFSET_X,OFFSET_Y,OFFSET_X+m_iWidth,OFFSET_Y+m_iHeight, makecol(0,0,0));
	//textprintf(screenBuffer, font, 200, 10, makecol(255,255,255),"FPS: %f - Rest: %d",m_Fps->getFrameRate(),m_Fps->getRestTime());
	rect(target,m_boundingRect.x1,m_boundingRect.y1,m_boundingRect.x2,m_boundingRect.y2,makecol(255,0,0));
}

bool Map::collide(Entity* e) const
{
	return collide(m_boundingRect,e->boundingRect());
}

//////////////////////////////////////////////////////////////////////////

bool Map::collide(Rect r1, Rect r2)
{
	//r1.x1>r2.x1

	return !((r1.x1<r2.x2)&&(r1.x2>r2.x1)&&(r1.y1<r2.y2)&&(r1.y2>r2.y1)); 
}
