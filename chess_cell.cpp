#include "chess_cell.h"
#include "chess_board.h"
extern ChessBoard board;
ChessCell::ChessCell()
{
	piece=NULL;
}

void ChessCell::draw()
{
	iG::ISetColor::iSolid(getColor());
	iG::IDraw::IFilled::iRectangle(x,y,width,height);
}

void ChessCell::setPiece(ChessPiece* piece)
{
	this->piece=piece;
}
void ChessCell::clear()
{
	piece=NULL;
}
bool ChessCell::empty()
{
	return piece==NULL;
}
void ChessCell::setRow(int row)
{
	this->row=row;
}

void ChessCell::setCol(int col)
{
	this->col=col;
}

bool ChessCell::isMovable(int row,int col,ChessPiece* piece)
{	
	if(piece->isValidMove(row,col,this->row,this->col))
	{
		return true;
	}
	else
	{
		return false;
	}
}

ChessPiece* ChessCell::getPiece()
{
	return piece;
}