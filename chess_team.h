#ifndef __CHESS_TEAM__
#define __CHESS_TEAM__
#include "chess_piece.h"
class ChessTeam{
private:
	ChessPiece* piece[2][8];
public:
	ChessTeam(PieceColor);
	ChessPiece* at(int,int);
};
#endif