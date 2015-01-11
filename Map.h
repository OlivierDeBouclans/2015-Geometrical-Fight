
#ifndef Map_h__
#define Map_h__

#include "allegro.h"

#define BORDER_WIDTH 10
#define OFFSET_X 200
#define OFFSET_Y 50

#include "Entity.h"

class Map
{
	public:
		Map(int width, int height);
		~Map(void);

		void draw(BITMAP* target) const;
		bool collide(Entity* e) const;

		static bool collide(Rect r1, Rect r2);

	protected:
		int m_iWidth;
		int m_iHeight;
		Rect m_boundingRect;


};

#endif // Map_h__

