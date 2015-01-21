
#ifndef CoolDown_h__
#define CoolDown_h__

#include <map>

class CoolDown
{
	public:
		CoolDown(void);

		~CoolDown(void);

		void add(int index,double cd);
		void launch(int index);
		bool isAvailable(int index);
		void setCoolDown(int index, int cd);

	protected:
		std::map<int,std::pair<double,double> > mCoolDownList;
};
#endif // CoolDown_h__

