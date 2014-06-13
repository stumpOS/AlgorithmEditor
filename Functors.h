#pragma once
#include<functional>

class CountToLimit
{
public:
	CountToLimit(unsigned limit):_limit(limit){_count = 0;}
	virtual ~CountToLimit(){}
	bool operator()()
	{
		if(_count < _limit)
		{
			_count++;
			return false;
		}
		else
		{
			_count = 0;
			return true;
		}
	}
private:
	unsigned _limit;
	unsigned _count;
};