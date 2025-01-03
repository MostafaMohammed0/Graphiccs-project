#ifndef __RECTANGLE__
#define __RECTANGLE__
#include "Object.h"
#include "Main.h"
class Box: public Object {
protected:
	int height, width;
public:
	Box();
	Box(int width, int height);
	void setWidth(int width);
	void setHeight(int height);
	int getHeight();
	int getWidth();
	void draw();
	void setBounds(int x, int y, int width, int height);
};
#endif