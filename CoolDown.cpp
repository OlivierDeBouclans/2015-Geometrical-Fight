#include "CoolDown.h"

#include "allegro.h"

CoolDown::CoolDown(void)
{
}


CoolDown::~CoolDown(void)
{
}

//////////////////////////////////////////////////////////////////////////

void CoolDown::add(int index,double cd)
{
	mCoolDownList[index].first=cd;
	mCoolDownList[index].second=0;
}

//////////////////////////////////////////////////////////////////////////

void CoolDown::launch(int index)
{
	try
	{
		std::pair<double,double> &p=mCoolDownList.at(index);    
		p.second=clock();
	}
	catch (std::out_of_range e)
	{
		return;
	}
}

//////////////////////////////////////////////////////////////////////////

bool CoolDown::isAvailable(int index)
{
	try
	{
		std::pair<double,double> &p=mCoolDownList.at(index);    

		double t=clock();
		if(t-p.second>=p.first)
			return true;
		else
			return false;
	}
	catch (std::out_of_range e)
	{
		return false;
	}	
}

//////////////////////////////////////////////////////////////////////////

void CoolDown::setCoolDown(int index, int cd)
{
	try
	{
		std::pair<double,double> &p=mCoolDownList.at(index); 
		p.first=cd;
	}
	catch (std::out_of_range e)
	{
		return;
	}
}
