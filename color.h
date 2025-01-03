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

class Color {
protected:
	int r, g, b;
public:
	Color();
	Color(double r, double g, double b);
	void setColor(double r, double g, double b);
	void setColor(tuple<double, double, double>rgb);
	tuple<double, double, double> getColor();
	static tuple<double, double, double> random();
	int getR();
	int getG();
	int getB();

};
#endif