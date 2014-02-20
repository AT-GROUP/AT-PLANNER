
#include "geometry.h"

APoint operator+(APoint p1, APoint p2)
{
	return APoint(p1.x() + p2.x(), p1.y() + p2.y());
}