#ifndef __COORDINATE__
#define __COORDINATE__
#include "MAIN.h"
#include "color.h"
class Grid{
protected:
	int unit, row, col;
public:
	int getUnit();
	void setUnit(int);
	int getRow();
	int getCol();
	void setRow();
	void setCol();
	void draw();
};
#endif