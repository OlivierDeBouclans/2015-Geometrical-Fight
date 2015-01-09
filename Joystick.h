#ifndef Joystick_h__
#define Joystick_h__

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
};

#endif // Joystick_h__

