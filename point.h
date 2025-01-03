#ifndef __POINT__
#define __POINT__
#include "Main.h"
class Point {
protected:
	int x, y;
public:
	Point();
	Point(int x,int y);
	int getX();
	int getY();
	void setPoint(int x, int y);
	void setX(int x);
	void setY(int y);
	void changeX(int x);
	void changeY(int y);
};
#endif