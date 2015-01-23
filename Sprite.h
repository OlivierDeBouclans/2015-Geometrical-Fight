#ifndef SPRITE_H
#define SPRITE_H

#include "Allegro.h"

class Sprite
{
    public:
        Sprite(char* filename, int width, int height, int NBrow);
        ~Sprite();
        void Draw(BITMAP* target,int frame, int x, int y);
        void Draw(BITMAP* target,int frame, int x, int y, float coef);

        int getNbRow();
        int getHeight();
        int getWidth();

    protected:

    private:
        BITMAP* m_bmp;
        int m_height;
        int m_width;
        int m_row;
};

#endif // SPRITE_H
