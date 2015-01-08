
#include "FPSHandler.h"
#include "allegro.h"

FPSHandler::FPSHandler(int AimedFrameRate): m_iAimedFrameRate(AimedFrameRate), m_iRestTime(0), m_lPreviousTime(clock()) 
{

}

//--------------------------------------------------------------------------------

void FPSHandler::update()
{
	//Calculate the time between 2 frames (update) to determine the current fps
	m_fFrameRate=1000/(clock()-m_lPreviousTime);

	//Dont change the resting time if the current frame rate is close enough to the targeted one
	if(m_fFrameRate > m_iAimedFrameRate)
		{
			m_iRestTime++;
		}

	m_lPreviousTime = clock();
}

