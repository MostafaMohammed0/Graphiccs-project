#ifndef __BUTTON__
#define __BUTTON__
#include "Box.h"
#include "MAIN.h"
class Button: public Box {
protected:
	bool selected;
	string name;
public:
	Button();
	Button(string name);
	void select();
	void deSelect();
	bool isSelected();
	void draw();
	void setName(string name);
};
#endif