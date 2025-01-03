#include "Colors.h"
RGBColor::RGBColor()
{
	r = g = b = 255;
}
RGBColor::RGBColor(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void RGBColor::setRGB(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void RGBColor::setRGB(tuple<double, double, double>rgb)
{
	this->r = get<0>(rgb);
	this->g = get<1>(rgb);
	this->b = get<2>(rgb);
}

tuple<double, double, double> RGBColor::getRGB()
{
	return make_tuple(r, g, b);
}
int RGBColor::getR()
{
	return r;
}
int RGBColor::getG()
{
	return g;
}
int RGBColor::getB()
{
	return b;
}