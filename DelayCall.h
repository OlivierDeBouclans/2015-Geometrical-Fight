

#ifndef DelayCall_h__
#define DelayCall_h__

#include "allegro.h"
#include <vector>

template<class T>
class DelayCall
{
	public:
		DelayCall(T& obj);
		~DelayCall(void);

		void call(void (T::*f)(),double delay);
		void update();

	protected:
		struct functionDelay
		{
			void (T::*function)();
			double delay;
			double startTime;
		};

		std::vector<functionDelay> vFunction;
		T& object; 
};		

template<class T>
DelayCall<T>::DelayCall(T& obj): object(obj)
{
}

template<class T>
DelayCall<T>::~DelayCall(void)
{
}

//////////////////////////////////////////////////////////////////////////

template<class T>
void DelayCall<T>::call(void (T::*f)(),double delay)
{
	functionDelay d;
	d.function=f;
	d.delay=delay;
	d.startTime=clock();

	vFunction.push_back(d);
}

//////////////////////////////////////////////////////////////////////////

template<class T>
void DelayCall<T>::update()
{
	double time=clock();
	for(unsigned int i=0;i<vFunction.size();++i)
	{
		functionDelay d=vFunction[i];
		if(time-d.startTime>=d.delay)
		{
			((object).*(d.function))();
			vFunction.erase(vFunction.begin()+i);
		}
	}
}


#endif // DelayCall_h__

