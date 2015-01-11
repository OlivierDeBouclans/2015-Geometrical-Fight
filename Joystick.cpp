#include "Joystick.h"
#include "allegro.h"
#include "Macros.h"


Joystick::Joystick(void):a(_a), b(_b), x(_x), y(y), lb(_lb), rb(_rb), start(_start), back(_back), lt(_lt), rt(_rt), stick_x(_stick_x), stick_y(_stick_y), throttle(_throttle)
{
}

//////////////////////////////////////////////////////////////////////////

Joystick::~Joystick(void)
{
}

//////////////////////////////////////////////////////////////////////////

void Joystick::init()
{
	if(install_joystick(JOY_TYPE_AUTODETECT)!=0)
	{
		allegro_message(allegro_error);
		return;
	};
}

//////////////////////////////////////////////////////////////////////////

void Joystick::update()
{
	poll_joystick();
	
	//joy[0].button[1], joy[0].button[2]
	float a=joy[0].stick[0].axis[2].d1;
	float b=joy[0].stick[0].axis[2].d2;
	float c=joy[0].stick[0].axis[2].pos;
	float d=0;

	_a=joy[0].button[BUTTON_A].b;
	_b=joy[0].button[BUTTON_B].b;
	_x=joy[0].button[BUTTON_X].b;
	_y=joy[0].button[BUTTON_Y].b;
	_lb=joy[0].button[BUTTON_LB].b;
	_rb=joy[0].button[BUTTON_RB].b;
	_start=joy[0].button[BUTTON_START].b;
	_back=joy[0].button[BUTTON_BACK].b;

	_lt=-joy[0].stick[0].axis[2].d1;
	_rt=-joy[0].stick[0].axis[2].d2;

	_stick_x=joy[0].stick[0].axis[0].pos;
	_stick_y=joy[0].stick[0].axis[1].pos;
	_throttle=joy[0].stick[0].axis[2].pos;	
}
