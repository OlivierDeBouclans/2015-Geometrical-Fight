
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
	if(m_fFrameRate > m_iAimedFrameRate*1.2)
		m_iRestTime++;
	else if(m_iRestTime>0 && m_fFrameRate<m_iAimedFrameRate*0.8)
		m_iRestTime--;

	m_lPreviousTime = clock();
}

//////////////////////////////////////////////////////////////////////////

void FPSHandler::draw(BITMAP* target)
{
	textprintf(target, font, 0, 10, makecol(255,255,255),"FPS:%f -Rest:%d",m_fFrameRate,m_iRestTime);
}

