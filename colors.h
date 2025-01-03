#ifndef __COLOR__
#define __COLOR__
#include "main.h"
#define WHITE 255,255,255
#define BLACK 0,0,0
#define BLUE 0,0,255
#define GREEN 0,255,0
#define RED 255,0,0
#define YELLOW 255,255,0
#define PURPLE 255,255,0

class RGBColor {
protected:
	int r, g, b;
public:
	RGBColor();
	RGBColor(double r, double g, double b);
	void setRGB(double r, double g, double b);
	void setRGB(tuple<double, double, double>rgb);
	tuple<double, double, double> getRGB();
	int getR();
	int getG();
	int getB();
};
#endif