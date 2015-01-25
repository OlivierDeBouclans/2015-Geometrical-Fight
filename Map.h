
#ifndef Map_h__
#define Map_h__

#include "Entity.h"
#include "Macros.h"
#include <vector>
#include "Vector2D.h"
#include "CoolDown.h"

class MovingEntity;
class Xp;
class Player;
class Joystick;
class Decoy;
class Sprite;

struct SAMPLE;
struct BITMAP;

class Map
{
	public:
		Map(int width, int height);
		~Map(void);

		void draw(BITMAP* target) const;
		bool collide(Entity* e) const;
		void update(double dt);

		void drawPlayerStats(BITMAP* target) const;

		static bool collide(Rect r1, Rect r2);

		void addPlayer();
		void addEnemies();

		Player* getPlayer() {return m_pPlayer;}
		Rect getBoundingRect() {return m_boundingRect;}

		void hitEnemy(int EnemyIndex, bool fireDamage=true);
		void destroyEnemy(int EnemyIndex);

		void hitPlayer(int damage);
		void getXp(Xp* xp);

		void createSprite();
		void loadSound();

		Point2D getTopLeft() {return Point2D(OFFSET_X,OFFSET_Y);}
		Point2D getTopRight() {return Point2D(OFFSET_X+m_iWidth,OFFSET_Y);}
		Point2D getBotLeft() {return Point2D(OFFSET_X,OFFSET_Y+m_iHeight);}
		Point2D getBotRight() {return Point2D(OFFSET_X+m_iWidth,OFFSET_Y+m_iHeight);}

		Joystick* joystick;
		std::vector<MovingEntity*> vEnemies;
		std::vector<Xp*> vXp;
		std::map<int,Sprite*> vSpriteList;
		std::map<int,SAMPLE*> vSoundList;

		enum {PLAYER_SPRITE,XP_SPRITE};
		enum {FIRE, EXPLOSION, SPEED, XP, DAMAGE};

		bool bPause;
		Decoy* decoy;

	protected:
		int m_iWidth;
		int m_iHeight;
		Rect m_boundingRect;

		double m_dLastSpawn;

		Player* m_pPlayer;

		enum {HIT_ENEMY, HIT_PLAYER};
		CoolDown cd;

		BITMAP* background;
};

#endif // Map_h__

