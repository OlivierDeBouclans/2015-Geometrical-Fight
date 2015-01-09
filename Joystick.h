#ifndef Joystick_h__
#define Joystick_h__

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_LB 4
#define BUTTON_RB 5
#define BUTTON_BACK 6
#define BUTTON_START 7

class Joystick
{
	public:
		Joystick();
		~Joystick();

		void init();

	private:
		bool _a;
		bool _b;
		bool _x;
		bool _y;
		bool _l;
		bool _r;
		bool _start;
		bool _back;
};

#endif // Joystick_h__

