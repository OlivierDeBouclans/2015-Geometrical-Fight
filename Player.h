
#ifndef Player_h__
#define Player_h__

#include "movingentity.h"
#include "Macros.h"
#include "CoolDown.h"

class Vector2D;
class Joystick;
class Weapon;

class Player:public MovingEntity
{
	public:
		Player(int x=DEFAULT_X, int y=DEFAULT_Y,Joystick* joystick=NULL);
		~Player();

		enum Form {NORMAL, AGRESSIVE, DEFENSIVE, SPEEDY, SNEAKY};

		Vector2D getSteeringForce();
		void draw(BITMAP* target) const;
		Rect boundingRect() const;
		void update(double dt);

		void special();
		void specialSpeedy();
		void specialDefensive();
		void specialAgressive();

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

		int xp;
		int xpNextLevel;
		int fury;
		int furyMax;

		float lifeSteal;

		Form form;

		float agressive_fire_coef;
		float agressive_contact_coef;
		float agressive_defense_coef;

		float sneaky_fire_coef;
		float sneaky_contact_coef;
		float sneaky_defense_coef;
		float sneaky_speed_coef;

		float defensive_fire_coef;
		float defensive_contact_coef;
		float defensive_defense_coef;
		float defensive_speed_coef;

		float speedy_contact_coef;
		float speedy_defense_coef;
		float speedy_speed_coef;

	private:
		Joystick* m_pJoystick;
		Weapon*   m_pWeapon;

		enum {CHANGE_AGRESSIVE,CHANGE_SPEEDY,CHANGE_SNEAKY, CHANGE_DEFENSIVE,UNCHANGE};
		CoolDown cd;
};

#endif // Player_h__

