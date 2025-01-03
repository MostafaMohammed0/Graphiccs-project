#include "Point.h"
Point::Point()
{
	this->x=this->y=0;
}
Point::Point(int x,int y)
{
	this->x=x;
	this->y=y;
}
int Point::getX()
{
	return x;
}
int Point::getY()
{
	return y;
}
void Point::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::setX(int x)
{
	this->x = x;
}
void Point::setY(int y)
{
	this->y = y;
}
void Point::changeX(int x)
{
	this->x += x;
}
void Point::changeY(int y)
{
	this->y += y;
}