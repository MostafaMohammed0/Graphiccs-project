#ifndef __CHESS_CELL__
#define __CHESS_CELL__
#include "chess_piece.h"
#include "main.h"
#include "Box.h"


class ChessCell:public Box{
private:
	int row,col;
	ChessPiece* piece;
public:
	ChessCell();
	void draw();
	bool empty();
	void clear();
	void setPiece(ChessPiece* piece);
	void setRow(int);
	void setCol(int);
	bool isMovable(int,int,ChessPiece*);
	ChessPiece* getPiece();
};
#endif