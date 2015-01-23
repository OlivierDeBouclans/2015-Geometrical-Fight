#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"

class Animation
{
    public:
        Animation();
        Animation(Sprite *s,int curframe);
        ~Animation();

        void Draw(BITMAP *target, int x, int y);
        void Draw(BITMAP *target, int x, int y, float coeff);

        void startAnimation(int animtype, int direction, int framedelay, bool restart=false);
        bool isAnimated();
        bool isAttacking();
        void update();

        int getWidth();
        int getHeight();

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
