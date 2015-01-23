#include "Sprite.h"

#include <iostream>

/**idea: use rle bitmap**/

Sprite::Sprite(char* filename, int width, int height, int NBrow)
{
    m_bmp = load_bitmap(filename,NULL);
    if (m_bmp == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message ("Can’t find %s",filename);
        exit(1);
    }

    std::cout << m_bmp->h << std::endl;

    m_height=height;
    m_width=width;
    m_row=NBrow;
}

Sprite::~Sprite()
{
    delete(m_bmp);
}

int Sprite::getNbRow()
{
    return m_row;
}

int Sprite::getHeight()
{
    return m_height;
}

int Sprite::getWidth()
{
    return m_width;
}

void Sprite::Draw(BITMAP* target,int frame, int x, int y)
{
        int framex = (frame % m_row)*m_width;
        int framey = (frame / m_row)*m_height;

        masked_blit(m_bmp,target,framex,framey,x,y,m_width,m_height);
}

void Sprite::Draw(BITMAP* target,int frame, int x, int y, float coef)
{
        int framex = (frame % m_row)*m_width;
        int framey = (frame / m_row)*m_height;

       masked_stretch_blit(m_bmp,target,framex,framey,m_width,m_height,x,y,(int) (coef*m_width),(int) (coef*m_height));
}

