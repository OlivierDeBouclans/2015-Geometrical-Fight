
#ifndef Map_h__
#define Map_h__

#include "allegro.h"
#include "Entity.h"
#include "Macros.h"
#include <vector>

class MovingEntity;
class Player;
class Joystick;

class Map
{
	public:
		Map(int width, int height);
		~Map(void);

		void draw(BITMAP* target) const;
		bool collide(Entity* e) const;
		void update(double dt);

		static bool collide(Rect r1, Rect r2);

		void addPlayer();
		void addEnemies();

		void hitEnemy(int EnemyIndex);

		Joystick* joystick;
		std::vector<MovingEntity*> vEnemies;

	protected:
		int m_iWidth;
		int m_iHeight;
		Rect m_boundingRect;

		double m_dLastSpawn;

		Player* m_pPlayer;


};

#endif // Map_h__

