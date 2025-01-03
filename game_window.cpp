#include "game_window.h"
void GameWindow::draw()
{
	iG::ISetColor::iSolid(border.getColor());
	border.draw();
}