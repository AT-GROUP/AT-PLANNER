
#ifndef ATCore_geometry_h
#define ATCore_geometry_h

#include "../config.h"

struct AT_CORE_API APoint
{
	int mX, mY;

	APoint(int _x = 0, int _y = 0)
		:mX(_x), mY(_y)
	{

	}

	void setX(const int new_x)
	{
		mX = new_x;
	}

	void setY(const int new_y)
	{
		mY = new_y;
	}

	int x() const
	{
		return mX;
	}

	int y() const
	{
		return mY;
	}
};

AT_CORE_API APoint operator+(APoint p1, APoint p2);

#endif
