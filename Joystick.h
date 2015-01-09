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
		const bool& a;
		const bool& b;
		const bool& x;
		const bool& y;
		const bool& lb;
		const bool& rb;
		const bool& start;
		const bool& back;
		const bool& lt;
		const bool& rt;

		const int& stick_x;
		const int& stick_y;
		const int& throttle;	

	private:
		bool _a;
		bool _b;
		bool _x;
		bool _y;
		bool _lb;
		bool _rb;
		bool _start;
		bool _back;
		bool _lt;
		bool _rt;
		
		int _stick_x;
		int _stick_y;
		int _throttle;	
};

#endif // Joystick_h__

