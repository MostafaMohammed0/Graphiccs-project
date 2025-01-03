#include "color.h"
Color::Color()
{
	r = g = b = 255;
}
Color::Color(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void Color::setColor(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void Color::setColor(tuple<double, double, double>rgb)
{
	this->r = get<0>(rgb);
	this->g = get<1>(rgb);
	this->b = get<2>(rgb);
}

tuple<double, double, double> Color::getColor()
{
	return make_tuple(r, g, b);
}

tuple<double, double, double> Color::random()
{
	return make_tuple(rand()%256,rand()%256,rand()%256);
}
int Color::getR()
{
	return r;
}
int Color::getG()
{
	return g;
}
int Color::getB()
{
	return b;
}