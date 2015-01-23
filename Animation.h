#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"

class Animation
{
    public:
        Animation();
        Animation(Sprite *s,int curframe);
        ~Animation();

        void draw(BITMAP *target, int frameRow, int x, int y);

        void startAnimation(int animtype, int direction, int framedelay, bool restart=false);
        bool isAnimated();
        void update();

        int getFrameWidth();
        int getFrameHeight();

    protected:

    private:
        Sprite *m_sprite;

        int m_curframe;
        int m_prevframe;
        int m_animdir;
        int m_animtype;
        int m_framecount;
        int m_framedelay;
};

#endif // ANIMATION_H
