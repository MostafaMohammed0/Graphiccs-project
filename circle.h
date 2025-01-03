#ifndef __CIRCLE__
#define __CIRCLE__
#include "Object.h"
#include "MAIN.h"
class Circle: public Object {
protected:
	int radius;
public:
	int getRadius();
	int setRadius(int radius);
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif