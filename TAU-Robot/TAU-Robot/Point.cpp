#include "Point.h"

Point::Point()
{
	x = -1;
	y = -1;
}
Point::Point(int _x, int _y) 
	: x(_x), y(_y) {}

int Point :: getX() const 
{ 
	return x; 
}
int Point :: getY() const 
{ 
	return y; 
}
void Point :: setXY(int _x, int _y)
{
	x = _x;
	y = _y;
}
Point::~Point()//ToDo:
{
}
