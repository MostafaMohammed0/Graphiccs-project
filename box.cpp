#include "Box.h"
Box::Box()
{
	this->width = 0;
	this->height = 0;
}
Box::Box(int width, int height)
{
	this->width = width;
	this->height = height;
}
void Box::setWidth(int width)
{
	this->width = width;
}
void Box::setHeight(int height)
{
	this->height = height;
}
int Box::getHeight()
{
	return this->height;
}
int Box::getWidth()
{
	return this->width;
}
void Box::draw()
{
	iG::ISetColor::iSolid(getColor());
	// cout<<width<<" "<<height<<endl;
	iG::IDraw::iRectangle(x,y,width,height);
}
void Box::setBounds(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}