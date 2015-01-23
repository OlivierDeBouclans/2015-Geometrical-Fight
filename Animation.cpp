#include "Animation.h"



Animation::Animation(Sprite *s,int curframe)
{
    m_sprite=s;
    m_curframe=curframe;

    m_framecount=-1;
    m_framedelay=-1;
}

Animation::Animation()
{

}

Animation::~Animation()
{

}

int Animation::getFrameHeight()
{
    return m_sprite->getFrameHeight();
}

int Animation::getFrameWidth()
{
    return m_sprite->getFrameWidth();
}

bool Animation::isAnimated()
{
    return !m_frames.empty();
}

int Animation::remainingTime()
{
	return m_frames.size()*m_framedelay;
}

void Animation::startAnimation(std::list<int> frames, int framedelay, bool reverseorder, bool restart)
{
   // if(m_frames.empty() || restart)
    {
		if(reverseorder)
			frames.reverse();

        m_frames.insert(m_frames.end(),frames.begin(),frames.end());
        m_framecount=clock();
        m_framedelay=framedelay;

		m_curframe=m_frames.front();
		m_frames.pop_front();

    }
}

void Animation::update()
{
    if(!m_frames.empty())
        if(clock()-m_framecount >= m_framedelay)
        {
            m_framecount=clock();

			m_curframe=m_frames.front();
			m_frames.pop_front();
        }
}

void Animation::draw(BITMAP *target, int frameRow, int x, int y)
{
    m_sprite->draw(target,frameRow+m_curframe,x,y);
}


