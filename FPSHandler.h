
/**----------------------------------------------------------------------
// @Class: FPS handler
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 5/11/13
//
// @Description: Calculate the frame rate and the rest time needed in the
// main loop to obtain the target Frame Rate.
//----------------------------------------------------------------------**/

#ifndef FPSHANDLER_H
#define FPSHANDLER_H

#define FPS_NUM_ELEMENT_FOR_MEAN 100


class FPSHandler
{
    public:
        //Constructor
		FPSHandler(int AimedFrameRate, float Precision = 0.05);

        //Destructor
		~FPSHandler();

        //Get
		const float& getFrameRate() const    { return m_fFrameRate; }
		const float& getImmediateFrameRate() { return m_pMeanFrameRate[m_iIndex];}
        const int&   getRestTime()  const    { return m_iRestTime;  }
		int          getPrecision() const    { return (( 100 * m_fFrameRate ) / m_iAimedFrameRate )- 100 ;}

        //Set
        void setAimedFrameRate(const int& val) { m_iAimedFrameRate = val; }

        //Update the fps
		//The output fps is the mean over FPS_NUM_ELEMENT_FOR_MEAN element
		//but the adjustment for the rest time is based on the instantaneous fps
        void Update();

    private:
        int m_iAimedFrameRate;
        int m_iRestTime;
		int m_iIndex;
		float* m_pMeanFrameRate; //array of the FPS_NUM_ELEMENT_FOR_MEAN last fps
		float  m_fFrameRate;     //contain the mean
		float  m_fPrecision;
        long m_lTime;
};

#endif // FPSHANDLER_H
