#include "Sprite.h"

#include <iostream>

/**idea: use rle bitmap**/

Sprite::Sprite(char* filename, int a, int b, CallMethode methode)
{
	//Loading the sprite and checking for error
	m_BMP = load_bitmap(filename,NULL);
	if (m_BMP == NULL)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message ("Can't find %s",filename);
		exit(1);
	}

	//Initialize the attributes depending on the call
	if(methode==WIDTH_HEIGHT)
	{
		m_iFrameHeight= a;
		m_iFrameWidth= b;
		m_iNumberOfLine= m_BMP->h / a;
		m_iNumberOfRow= m_BMP->w / b;
	}
	else
	{
		m_iNumberOfLine= a;
		m_iNumberOfRow= b;
		m_iFrameHeight= m_BMP->h / a;
		m_iFrameWidth= m_BMP->w / b;
	}
}

//////////////////////////////////////////////////////////////////////////

Sprite::Sprite(BITMAP* bmp, int a, int b, CallMethode methode)
{
	m_BMP = bmp;

	//Initialize the attributes depending on the call
	if(methode==WIDTH_HEIGHT)
	{
		m_iFrameHeight= a;
		m_iFrameWidth= b;
		m_iNumberOfLine= m_BMP->h / a;
		m_iNumberOfRow= m_BMP->w / b;
	}
	else
	{
		m_iNumberOfLine= a;
		m_iNumberOfRow= b;
		m_iFrameHeight= m_BMP->h / a;
		m_iFrameWidth= m_BMP->w / b;
	}
}

Sprite::~Sprite()
{
     destroy_bitmap(m_BMP);
}

//////////////////////////////////////////////////////////////////////////

void Sprite::draw(BITMAP* target,int frame, int x, int y, float StretchCoef /*= 1.0*/, float RotationAngle /*= 0.0*/)
{
	//Get the frame coordinate
	int frame_x = (frame % m_iNumberOfRow)*m_iFrameWidth;
	int frame_y = (frame / m_iNumberOfRow)*m_iFrameHeight;

	//Select the needed function for blitting
	if( StretchCoef == 1.0 && RotationAngle == 0.0)
	{
		masked_blit(m_BMP,target,frame_x,frame_y,x,y,m_iFrameWidth,m_iFrameHeight);
	}
	else if( RotationAngle == 0.0)
	{
		int NewWidth  = StretchCoef*m_iFrameWidth;
		int NewHeight = StretchCoef*m_iFrameHeight;

		masked_stretch_blit(m_BMP,target,frame_x,frame_y,m_iFrameWidth,m_iFrameHeight,x,y,NewWidth,NewHeight);
	}
	else
	{
		//Convert 360° clockwise angle in the allegro format
		fixed angle = ftofix(258*RotationAngle/360);

		//Extract the sprite for rotation (check for error)
		BITMAP *sprite =create_sub_bitmap(m_BMP,frame_x,frame_y,m_iFrameWidth,m_iFrameHeight);
		if (sprite == NULL)
		{
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message ("Can't create the sub-bitmap for rotation");
			exit(1);
		}

		if( StretchCoef == 1.0)
		{
			rotate_sprite(target,sprite,x,y,angle);
		}
		else
		{
			fixed scale= ftofix(StretchCoef);
			rotate_scaled_sprite(target,sprite,x,y,angle,scale);
		}

		//Delete the sprite
		destroy_bitmap(sprite);
	}
}

//////////////////////////////////////////////////////////////////////////