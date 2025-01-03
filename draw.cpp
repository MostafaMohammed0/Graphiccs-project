#include "main.h"
#include "color.h"

#include "chess_board.h"
extern ChessBoard board;
void iG::iDraw()
{
	iClear();
	board.draw();
}
