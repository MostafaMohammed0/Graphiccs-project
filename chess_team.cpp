#include "chess_team.h"
#include "chess_piece.h"
ChessTeam::ChessTeam(PieceColor team)
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==1)
			{
				piece[i][j]=new Pawn(team);
			}
			else
			{
				switch(j)
				{
					case 0:
					case 7:
						piece[i][j]=new Rook(team);
						break;
					case 1:
					case 6:
						piece[i][j]=new Knight(team);
						break;
					case 2:
					case 5:
						piece[i][j]=new Bishop(team);
						break;
					case 3:
						piece[i][j]=new King(team);
						break;
					case 4:
						piece[i][j]=new Queen(team);
						break;
				}
			}		
		}
	}
}

ChessPiece* ChessTeam::at(int i,int j)
{
	return piece[i][j];
}