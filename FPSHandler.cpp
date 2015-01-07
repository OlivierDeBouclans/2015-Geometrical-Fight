
#include "FPSHandler.h"
#include "allegro.h"

//Constructor
FPSHandler::FPSHandler(int AimedFrameRate, float Precision): m_iAimedFrameRate(AimedFrameRate),m_lTime(clock()),m_iRestTime(0), m_pMeanFrameRate(new float[FPS_NUM_ELEMENT_FOR_MEAN]), m_iIndex(0), m_fFrameRate(0.0), m_fPrecision(Precision)
{
	for(int k=0; k<FPS_NUM_ELEMENT_FOR_MEAN; k++)
			m_pMeanFrameRate[k] = 0;
};

//Desctructor
FPSHandler::~FPSHandler() 
{ 
	delete[] m_pMeanFrameRate;
}

void FPSHandler::Update()
{
	//Remove the oldest fps count from the mean
	int olderindex=
	m_fFrameRate -= m_pMeanFrameRate[m_iIndex] / FPS_NUM_ELEMENT_FOR_MEAN;

	//Calculate the time between 2 frames (update) to determine the current fps
	m_pMeanFrameRate[m_iIndex] = 1000 / ( clock() - m_lTime );

	//Then add it to the mean 
	m_fFrameRate += m_pMeanFrameRate[m_iIndex] / FPS_NUM_ELEMENT_FOR_MEAN;

	//Dont change the resting time if the current frame rate is close enough to the targeted one
	if(m_fFrameRate < (1-m_fPrecision)*m_iAimedFrameRate || m_fFrameRate > (1+m_fPrecision)*m_iAimedFrameRate)
		{
			//Adjust the resting time
			if(m_pMeanFrameRate[m_iIndex] > m_iAimedFrameRate)
				{
					m_iRestTime++;
				}
			else if( m_pMeanFrameRate[m_iIndex] < m_iAimedFrameRate && m_iRestTime>0)
				{
					m_iRestTime--;
				}
		}

	m_iIndex++;
	if( m_iIndex == FPS_NUM_ELEMENT_FOR_MEAN )
		m_iIndex = 0;

	m_lTime = clock();
}

