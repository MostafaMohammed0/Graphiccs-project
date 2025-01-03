#include "main.h"
#include "chess_board.h"
extern ChessBoard board;
void iG::iKeyboard(unsigned char key)
{
	board.keyControl(key);
}
void iG::iKeyboardUp(unsigned char key)
{
	
}

void iG::iSpecialKeyboard(unsigned char key)
{
	board.specialKeyControl(key);
}

void iG::iSpecialKeyboardUp(unsigned char key)
{
	switch (key)
		{
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
		}
}