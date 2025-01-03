#ifndef __CHESS_BOARD__
#define __CHESS_BOARD__
#include "chess_cell.h"
#include "main.h"
#include "Grid.h"
#include "Box.h"
class ChessBoard:public Grid,public Box{
private:
	ChessCell cell[8][8];
	PieceColor turn;
	int selectedCellR,selectedCellC;
	int selectedPieceR,selectedPieceC;
	bool checkMate,upDown;
public:
	ChessBoard();
	void draw();
	void setBoard();
	void select(int,int);
	int getSelectedCellR();
	int getSelectedCellC();
	int getSelectedPieceR();
	int getSelectedPieceC();
	void selectCell(int,int);
	void selectPiece(int,int);
	void deSelectPiece();
	void keyControl(unsigned char);
	void specialKeyControl(unsigned char);
	void rotate();
	bool isRotated();
	bool isCheckMate();
	PieceColor getTurn();
	ChessCell at(int,int);
};
#endif