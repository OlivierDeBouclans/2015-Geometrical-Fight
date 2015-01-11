#ifndef Joystick_h__
#define Joystick_h__

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

