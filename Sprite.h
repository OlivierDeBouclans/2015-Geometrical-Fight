#ifndef SPRITE_H
#define SPRITE_H

#include "Allegro.h"

class Sprite
{
    public:
		enum CallMethode { WIDTH_HEIGHT, ROW_LINE};

		//If FrameSizeCall==true arguments are
		//a:Frame width size (px)
		//b:Frame height size (px)
		//If FrameSizeCall==false arguments are
		//a:Number of row
		//b:Number of line
		Sprite(char* filename, int a, int b, CallMethode methode=WIDTH_HEIGHT);
		//Same constructor but with the bmp
		Sprite(BITMAP* bmp, int a, int b, CallMethode methode=WIDTH_HEIGHT);

        ~Sprite();

		//Drawing function (the rotation is given in degree clockwise)
		void draw(BITMAP* target,int frame, int x, int y, float StretchCoef = 1.0, float RotationAngle = 0.0);

		//Get
		int getNumberOfRow() { return m_iNumberOfRow; }
		int getFrameHeight() { return m_iFrameHeight; }
		int getFrameWidth()  { return m_iFrameWidth;  }

    protected:

    private:
		BITMAP* m_BMP;        //pointer to the bitmap
		int m_iFrameHeight;   //Size in px of the frame's height
		int m_iFrameWidth;    //Size in px of the frame's width
		int m_iNumberOfLine;  //Number of frame in the bitmap's height (number of lines)
		int m_iNumberOfRow;   //Number of frame in the bitmap's width  (number of rows)
};

#endif // SPRITE_H
