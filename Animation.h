#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"
#include <list>

class Animation
{
    public:
        Animation();
        Animation(Sprite *s,int curframe);
        ~Animation();

        void draw(BITMAP *target, int frameRow, int x, int y);

        void startAnimation(std::list<int> frames, int framedelay, bool reversOrded=false, bool restart=false);
        bool isAnimated();
        void update();

        int getFrameWidth();
        int getFrameHeight();
		int getNumberOfRow() {return m_sprite->getNumberOfRow();}

		int remainingTime();

    protected:

    private:
        Sprite *m_sprite;

        int m_curframe;
        bool m_bReversOrder;
        int m_framecount;
        int m_framedelay;

		std::list<int> m_frames;
};

#endif // ANIMATION_H
