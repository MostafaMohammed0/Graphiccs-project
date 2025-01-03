#include "main.h"
#include "color.h"
#include "chess_board.h"
#include "chess_team.h"
ChessTeam teamWhite(__WHITE__),teamBlack(__BLACK__);
ChessBoard board;

void Logic()
{
}

void iG::windowSetup()
{
	iG::iSetScreenHeight(GetSystemMetrics(SM_CYFULLSCREEN));
	iG::iSetScreenWidth(GetSystemMetrics(SM_CXFULLSCREEN));
	iG::iSetWindowX(0);
	iG::iSetWindowY(0);
	iG::iSetWindowHeight(iScreenHeight);
	iG::iSetWindowWidth(iScreenWidth);
	iG::iSetClearColor(BLACK);
}

void setup()
{
	board.setUnit(120);
	board.setWidth(8*board.getUnit());
	board.setHeight(8*board.getUnit());
	board.setPoint(iG::iGetWindowWidth()/2-board.getWidth()/2,iG::iGetWindowHeight()/2-board.getHeight()/2);
	board.setBoard();
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	iG::windowSetup();
	setup();
	glutInit(&argc, argv);
	iG::iInitialize("snake");
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
}

	