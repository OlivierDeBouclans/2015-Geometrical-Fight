
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"
#include "Macros.h"
#include "CoolDown.h"
#include "DelayCall.h"

#include <list>
#include <vector>

class Vector2D;
class Joystick;
class Weapon;
class Animation;

class Player:public MovingEntity
{
	public:
		Player(Animation* sprite, int x=DEFAULT_X, int y=DEFAULT_Y,Joystick* joystick=NULL);
		~Player();

		enum Form {NORMAL, AGRESSIVE, DEFENSIVE, SPEEDY, SNEAKY};
		enum {NORMAL_TO_AGRESSIVE,NORMAL_TO_DEFENSIVE, NORMAL_TO_SPEEDY, NORMAL_TO_SNEAKY}; 

		Vector2D getSteeringForce();
		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

		void special();
		void specialSpeedy();
		void specialDefensive();
			void specialDefensiveUnchange();
		void specialAgressive();
			void specialAgressiveUnchange();
		void specialSneaky();
			void specialSneakyUnchange();

		void steal(int damage);

		void setJoystick(Joystick* joy) {m_pJoystick=joy;}

		void change(Form wantedForm);
			void changeAgressive();
			void changeDefensive();
			void changeSneaky();
			void changeSpeedy();

		void unchange();
			void unchangeAgressive();
			void unchangeDefensive();
			void unchangeSneaky();
			void unchangeSpeedy();

		void getXp(int value);
		void increaseFury(int value);
		void decreaseFury(int value);

		void activeSpeedy();
		void activeSpeedyUnchange();

		void activeDefensive();
		void activeDefensiveUnchange();

		void activeSneaky();
		void activeSneakyUnchange();

		void activeAgressive();

		void getDamage(int damage);

		int xp;
		int xpNextLevel;
		int fury;
		int furyMax;

		float lifeSteal;

		Form form;

		float agressive_fire_coef;
		float agressive_contact_coef;
		float agressive_defense_coef;
		bool  agressive_piercing;

		float sneaky_fire_coef;
		float sneaky_contact_coef;
		float sneaky_defense_coef;
		float sneaky_speed_coef;
		bool  sneaky_phantom;

		float defensive_fire_coef;
		float defensive_contact_coef;
		float defensive_defense_coef;
		float defensive_speed_coef;
		float defensive_shield;
		float defensive_shield_max;
		
		float speedy_contact_coef;
		float speedy_defense_coef;
		float speedy_speed_coef;

		Animation* pSprite;

		std::vector< std::list<int> > lAnimation;

	private:
		Joystick* m_pJoystick;
		Weapon*   m_pWeapon;
		DelayCall<Player>* m_delay;

		enum {CHANGE_AGRESSIVE,CHANGE_SPEEDY,CHANGE_SNEAKY, CHANGE_DEFENSIVE,UNCHANGE,SPECIAL_SPEEDY, SPECIAL_DEFENSIVE,DECREASE_FURY,SPECIAL_AGRESSIVE,SPECIAL_SNEAKY};
		CoolDown cd;

};

#endif // Player_h__

