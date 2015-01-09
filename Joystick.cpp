#include "Joystick.h"
#include "allegro.h"


Joystick::Joystick(void)
{
}


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
