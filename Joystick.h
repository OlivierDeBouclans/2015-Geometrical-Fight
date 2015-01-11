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
		void update();

		//Const reference
		const int& a;
		const int& b;
		const int& x;
		const int& y;
		const int& lb;
		const int& rb;
		const int& start;
		const int& back;
		const int& lt;
		const int& rt;

		const int& stick_x;
		const int& stick_y;
		const int& throttle;	

	private:
		int _a;
		int _b;
		int _x;
		int _y;
		int _lb;
		int _rb;
		int _start;
		int _back;
		int _lt;
		int _rt;
		
		int _stick_x;
		int _stick_y;
		int _throttle;	
};

#endif // Joystick_h__

