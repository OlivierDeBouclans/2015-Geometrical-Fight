
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

struct BITMAP;

class FPSHandler
{
    public:
        //Constructor
		FPSHandler(int AimedFrameRate);

        //Destructor
		~FPSHandler() {}

        //Get
		const float& getFrameRate() const {return m_fFrameRate;}
        const int& getRestTime() const {return m_iRestTime;}

        //Set
        void setAimedFrameRate(const int& val) {m_iAimedFrameRate=val;}

        //Update the fps
		//The output fps is the mean over FPS_NUM_ELEMENT_FOR_MEAN element
		//but the adjustment for the rest time is based on the instantaneous fps
        void update();

		void draw(BITMAP* target);

    private:
        int m_iAimedFrameRate;
        int m_iRestTime;
		float m_fFrameRate;
        long m_lPreviousTime;
};

#endif // FPSHANDLER_H
