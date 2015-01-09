
#ifndef Map_h__
#define Map_h__
#include "allegro.h"
//class BITMAP;

class Map
{
	public:
		Map(void);
		~Map(void);

		void draw(BITMAP* target);
};

#endif // Map_h__

