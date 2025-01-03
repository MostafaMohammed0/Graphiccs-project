#include "Button.h"
Button::Button()
{
	selected = false;
	setColor(GREEN);
}
Button::Button(string name)
{
	selected = false;
	this->name = name;
	setColor(GREEN);
}
void Button::select()
{
	selected = true;
}
void Button::deSelect()
{
	selected = false;
}
bool Button::isSelected()
{
	return selected;
}
void Button::draw()
{
	if (isSelected())
	{
		iG::ISetColor::iTrans(getColor(), .5);
		iG::IDraw::IFilled::iRectangle(x, y, width, height);
	}

	iG::ISetColor::iSolid(getColor());
	iG::IDraw::iRectangle(x, y, width, height);
	iG::ISetColor::iSolid(WHITE);
	char *Temp = &name[0];
	iG::IText::iSmall(x + 15, y + height / 3, Temp);
}
void Button::setName(string name)
{
	this->name = name;
}