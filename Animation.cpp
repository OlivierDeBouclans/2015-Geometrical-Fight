#include "Animation.h"

Animation::Animation(Sprite *s,int curframe)
{
    m_sprite=s;
    m_curframe=curframe;

    m_prevframe=curframe;
    m_animdir=-1;
    m_animtype=-1;
    m_framecount=-1;
    m_framedelay=-1;
}

Animation::Animation()
{

}

Animation::~Animation()
{

}

int Animation::getHeight()
{
    return m_sprite->getHeight();
}

int Animation::getWidth()
{
    return m_sprite->getWidth();
}

bool Animation::isAnimated()
{
    return m_animtype != -1;
}

bool Animation::isAttacking()
{
    return m_animtype == 1;
}

void Animation::startAnimation(int animtype, int direction, int framedelay, bool restart)
{
    if( m_animtype == -1 || (animtype == 1 && m_animtype == 0) ||(m_animtype !=1 && restart))
    {
        m_animtype=animtype;
        m_framecount=0;
        m_framedelay=framedelay;

        if( direction == 0)
            m_curframe=49;
        else if( direction == 1)
            m_curframe=61;
        else if( direction == 2)
            m_curframe=73;
        else if( direction == 3)
            m_curframe=85;

        switch(m_animtype)
        {
            case 0:

                m_prevframe= m_curframe;
                m_curframe+=m_animdir;

            break;

            case 1:

                m_prevframe= m_curframe;
                m_curframe = (m_curframe / m_sprite->getNbRow() - 4 )*m_sprite->getNbRow() + m_sprite->getNbRow() - 1;

            break;

        }
    }
}

void Animation::update()
{
    if(m_animtype != -1)
    {
        m_framecount++;

        if(m_framecount >= m_framedelay)
        {
            m_framecount=0;

            switch(m_animtype)
            {
                case 0:

                    if(m_curframe==m_prevframe)
                    {
                        m_animtype=-1;
                    }
                    else
                    {
                        m_animdir = - m_animdir;
                        m_curframe=m_prevframe;
                        m_framecount=m_framedelay/2;
                    }

                break;

                case 1:

                    m_curframe-=3;

                    if( (m_curframe < 0 || (m_curframe % m_sprite->getNbRow()) == m_sprite->getNbRow() - 1))
                    {
                        m_animtype=-1;
                        m_curframe=m_prevframe;
                    }

                break;

            }
        }
    }
}

void Animation::Draw(BITMAP *target, int x, int y)
{
    m_sprite->Draw(target,m_curframe,x,y);
}

void Animation::Draw(BITMAP *target, int x, int y, float coeff)
{
    m_sprite->Draw(target,m_curframe,x,y,coeff);
}


