#include "chess_board.h"
#include "chess_team.h"
extern ChessTeam teamWhite, teamBlack;
void ChessBoard::rotate()
{
	for (int i = 0; i < row / 2; i++)
	{
		for (int j = 0; j < col; j++)
		{
			ChessCell temp;
			temp.setPiece(cell[i][j].getPiece());
			cell[i][j].setPiece(cell[row - i - 1][col - j - 1].getPiece());
			cell[row - i - 1][col - j - 1].setPiece(temp.getPiece());
		}
	}
	upDown = !upDown;
}

bool ChessBoard::isCheckMate()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (!cell[i][j].empty())
			{
				if (cell[i][j].getPiece()->getTeam() == turn && cell[i][j].getPiece()->getType() == KING)
				{
					for (int p = 0; p < row; p++)
					{
						for (int q = 0; q < col; q++)
						{
							if (!cell[p][q].empty())
							{
								if (cell[p][q].getPiece()->getTeam() != turn && cell[i][j].isMovable(p, q, cell[p][q].getPiece()))
								{
									return true;
								}
							}
						}
					}
				}
			}

		}
	}
	return false;
}
ChessBoard::ChessBoard()
{
	this->row = this->col = 8;
	selectedCellR = selectedCellC = 0;
	selectedPieceR = selectedPieceC = -1;
	turn = __WHITE__;
	checkMate = false;
	upDown = false;
}
bool ChessBoard::isRotated()
{
	return upDown;
}
int ChessBoard::getSelectedCellR()
{
	return selectedCellR;
}
int ChessBoard::getSelectedCellC()
{
	return selectedCellC;
}
int ChessBoard::getSelectedPieceR()
{
	return selectedPieceR;
}
int ChessBoard::getSelectedPieceC()
{
	return selectedPieceC;
}

PieceColor ChessBoard::getTurn()
{
	return turn;
}

void ChessBoard::draw()
{
	iG::ISetColor::iSolid(98, 52, 18);
	iG::IDraw::iRectangle(x, y, width, height, 60);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cell[i][j].draw();
		}
	}
	iG::ISetColor::iSolid(BLACK);
	iG::IDraw::iRectangle(x, y, width, height, 5);
	for (int i = 0; i <= row; i++)
	{
		iG::IDraw::iLine(x, y + i * unit, x + width, y + i * unit, 3);
	}
	for (int i = 0;  i <= col; i++)
	{
		iG::IDraw::iLine(x + i * unit, y, x + i * unit, y + height, 3);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (selectedPieceR == i && selectedPieceC == j)
			{
				iG::ISetColor::iTrans(BLACK, .5);
				iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
			}
			else if (selectedPieceR != -1)
			{
				/* Guideline for moving */
				if (cell[i][j].empty())
				{
					if (cell[i][j].isMovable(selectedPieceR, selectedPieceC, cell[selectedPieceR][selectedPieceC].getPiece()))
					{
						ChessPiece* temp1 = cell[i][j].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
						cell[i][j].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
						cell[selectedPieceR][selectedPieceC].clear();
						if (!isCheckMate())
						{
							iG::ISetColor::iTrans(BLUE, .4);
							iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
						}
						cell[i][j].setPiece(temp1);
						cell[selectedPieceR][selectedPieceC].setPiece(temp2);
					}
				}

				/* Guideline for capturing */
				else if (cell[i][j].getPiece()->getTeam() != cell[selectedPieceR][selectedPieceC].getPiece()->getTeam())
				{
					if (cell[i][j].isMovable(selectedPieceR, selectedPieceC, cell[selectedPieceR][selectedPieceC].getPiece()))
					{
						ChessPiece* temp1 = cell[i][j].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
						cell[i][j].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
						cell[selectedPieceR][selectedPieceC].clear();
						if (!isCheckMate())
						{
							iG::ISetColor::iTrans(RED, .4);
							iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
						}
						cell[i][j].setPiece(temp1);
						cell[selectedPieceR][selectedPieceC].setPiece(temp2);
					}
				}

				/* Castling */
				else if (cell[i][j].getPiece()->getType() == ROOK && cell[selectedPieceR][selectedPieceC].getPiece()->getType() == KING && i == 0 && (j == 0 || j == col - 1) && selectedPieceR == 0 && selectedPieceC == (col - 1) / 2)
				{
					if (!isCheckMate())
					{
						if (cell[selectedPieceR][selectedPieceC].isMovable(i, j, cell[i][j].getPiece()))
						{
							ChessPiece* temp1 = cell[i][j].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
							if (selectedPieceC > j)
							{
								cell[selectedPieceR][selectedPieceC - 2].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
								cell[selectedPieceR][selectedPieceC - 1].setPiece(cell[i][j].getPiece());
								cell[selectedPieceR][selectedPieceC].clear();
								cell[i][j].clear();
								if (!isCheckMate())
								{
									iG::ISetColor::iTrans(GREEN, .4);
									iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
								}
								cell[selectedPieceR][selectedPieceC - 2].setPiece(NULL);
								cell[selectedPieceR][selectedPieceC - 1].setPiece(NULL);
							}
							else
							{
								cell[selectedPieceR][selectedPieceC + 2].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
								cell[selectedPieceR][selectedPieceC + 1].setPiece(cell[i][j].getPiece());
								cell[selectedPieceR][selectedPieceC].clear();
								cell[i][j].clear();
								if (!isCheckMate())
								{
									iG::ISetColor::iTrans(GREEN, .4);
									iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
								}
								cell[selectedPieceR][selectedPieceC + 2].setPiece(NULL);
								cell[selectedPieceR][selectedPieceC + 1].setPiece(NULL);
							}
							cell[i][j].setPiece(temp1);
							cell[selectedPieceR][selectedPieceC].setPiece(temp2);
						}
					}

				}
			}
		}


		/* Check */
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (!cell[i][j].empty())
				{
					if (cell[i][j].getPiece()->getTeam() == turn && cell[i][j].getPiece()->getType() == KING)
					{
						if (isCheckMate())
						{
							iG::ISetColor::iTrans(RED, .4);
							iG::IDraw::IFilled::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight());
						}
					}
				}
			}
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (selectedCellR == i && selectedCellC == j)
				{
					iG::ISetColor::iSolid(BLACK);
					iG::IDraw::IDashed::iRectangle(cell[i][j].getX(), cell[i][j].getY(), cell[i][j].getWidth(), cell[i][j].getHeight(), 12, 30);
				}
			}
		}


		for (int i = row - 1; i > -1; i--)
		{
			for (int j = 0; j < col; j++)
			{
				if (!cell[i][j].empty())
				{
					if ((cell[i][j].getPiece()->getTeam() == turn && selectedPieceR == -1 && selectedCellR == i && selectedCellC == j) || (selectedPieceR == i && selectedPieceC == j))
					{
						cell[i][j].getPiece()->draw(cell[i][j].getX() + cell[i][j].getWidth() / 4, cell[i][j].getY()  + cell[i][j].getHeight() / 6);
					}
					else
					{
						cell[i][j].getPiece()->draw(cell[i][j].getX() + cell[i][j].getWidth() / 4, cell[i][j].getY() );
					}
				}
			}
		}

		/* Draw dead white pieces outside the board */
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (teamWhite.at(i, j)->isDead())
				{
					teamWhite.at(i, j)->draw(iG::iGetWindowWidth() - 150 - unit - unit * i, 50 + unit * j);
				}
			}
		}

		/* Draw dead black pieces outside the board */
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (teamBlack.at(i, j)->isDead())
				{
					teamBlack.at(i, j)->draw(200 + unit * i, 50 + unit * j);
				}
			}
		}
	}
}
void ChessBoard::setBoard()
{
	selectedCellR = selectedCellC = 0;
	selectedPieceR = selectedPieceC = -1;
	turn = __WHITE__;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if ((i + j) % 2)
			{
				cell[i][j].setColor(98, 52, 18);
			}
			else
			{
				cell[i][j].setColor(180, 134, 72);
			}

			cell[i][j].setX(x + j * unit);
			cell[i][j].setY(y + i * unit);
			cell[i][j].setWidth(unit);
			cell[i][j].setHeight(unit);
			cell[i][j].setRow(i);
			cell[i][j].setCol(j);
			cell[i][j].setPiece(NULL);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cell[i][j].setPiece(teamWhite.at(i, j));
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cell[row - i - 1][col - j - 1].setPiece(teamBlack.at(i, j));
		}
	}
}
void ChessBoard::specialKeyControl(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_END:
		exit(0);
		break;
	case GLUT_KEY_UP:
		if (selectedCellR < row - 1)
		{
			selectedCellR++;
			if (!cell[selectedCellR][selectedCellC].empty() && cell[selectedCellR][selectedCellC].getPiece()->getTeam() == turn && selectedPieceR == -1)
				PlaySound("Data\\Music\\PickUp.wav", NULL, SND_ASYNC);
		}

		break;
	case GLUT_KEY_DOWN:
		if (selectedCellR > 0)
		{

			selectedCellR--;
			if (!cell[selectedCellR][selectedCellC].empty() && cell[selectedCellR][selectedCellC].getPiece()->getTeam() == turn && selectedPieceR == -1)
				PlaySound("Data\\Music\\PickUp.wav", NULL, SND_ASYNC);
		}

		break;
	case GLUT_KEY_LEFT:
		if (selectedCellC > 0)
		{
			selectedCellC--;
			if (!cell[selectedCellR][selectedCellC].empty() && cell[selectedCellR][selectedCellC].getPiece()->getTeam() == turn && selectedPieceR == -1)
				PlaySound("Data\\Music\\PickUp.wav", NULL, SND_ASYNC);
		}

		break;
	case GLUT_KEY_RIGHT:
		if (selectedCellC < col - 1)
		{
			selectedCellC++;
			if (!cell[selectedCellR][selectedCellC].empty() && cell[selectedCellR][selectedCellC].getPiece()->getTeam() == turn && selectedPieceR == -1)
				PlaySound("Data\\Music\\PickUp.wav", NULL, SND_ASYNC);
		}

		break;
	}
}

void ChessBoard::selectCell(int r, int c)
{
	selectedCellR = r;
	selectedCellC = c;
}

void ChessBoard::selectPiece(int r, int c)
{
	selectedPieceR = r;
	selectedPieceC = c;
}

void ChessBoard::deSelectPiece()
{
	selectedPieceR = selectedPieceC = -1;
}

void ChessBoard::keyControl(unsigned char key)
{
	switch (key)
	{
	case  '\r':
		if (!cell[selectedCellR][selectedCellC].empty())
		{
			if (selectedPieceR == -1)
			{

				if (cell[selectedCellR][selectedCellC].getPiece()->getTeam() == turn)
				{
					if (checkMate)
					{
						if (cell[selectedCellR][selectedCellC].getPiece()->getType() == KING)
						{
							selectPiece(selectedCellR, selectedCellC);
						}
					}
					else
					{
						selectPiece(selectedCellR, selectedCellC);
					}
				}
			}
			else if (selectedCellR == selectedPieceR && selectedCellC == selectedPieceC)
			{
				// PlaySound("Data\\Music\\PutDown.wav", NULL, SND_ASYNC);
				deSelectPiece();
			}


			/* Capturing */
			else if (cell[selectedCellR][selectedCellC].getPiece()->getTeam() != cell[selectedPieceR][selectedPieceC].getPiece()->getTeam())
			{
				if (cell[selectedCellR][selectedCellC].isMovable(selectedPieceR, selectedPieceC, cell[selectedPieceR][selectedPieceC].getPiece()))
				{
					ChessPiece *temp1 = cell[selectedCellR][selectedCellC].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
					cell[selectedCellR][selectedCellC].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
					cell[selectedPieceR][selectedPieceC].clear();

					if (isCheckMate())
					{
						cell[selectedCellR][selectedCellC].setPiece(temp1);
						cell[selectedPieceR][selectedPieceC].setPiece(temp2);
					}
					else
					{
						PlaySound("Data\\Music\\PutDown.wav", NULL, SND_ASYNC);
						cell[selectedCellR][selectedCellC].getPiece()->die();
						if (turn == __BLACK__)
						{
							turn = __WHITE__;
						}
						else
						{
							turn = __BLACK__;
						}
						deSelectPiece();
						rotate();
					}

				}
			}
			/* Castling */
			else if (cell[selectedCellR][selectedCellC].getPiece()->getType() == ROOK && cell[selectedPieceR][selectedPieceC].getPiece()->getType() == KING && selectedCellR == 0 && (selectedCellC == 0 || selectedCellC == col - 1) && selectedPieceR == 0 && selectedPieceC == (col - 1) / 2)
			{

				if (cell[selectedPieceR][selectedPieceC].isMovable(selectedCellR, selectedCellC, cell[selectedCellR][selectedCellC].getPiece()))
				{
					if (!isCheckMate())
					{
						
						ChessPiece* temp1 = cell[selectedCellR][selectedCellC].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
						if (selectedPieceC > selectedCellC)
						{
							cell[selectedPieceR][selectedPieceC - 2].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
							cell[selectedPieceR][selectedPieceC - 1].setPiece(cell[selectedCellR][selectedCellC].getPiece());
							cell[selectedPieceR][selectedPieceC].clear();
							cell[selectedCellR][selectedCellC].clear();
							if (isCheckMate())
							{
								cell[selectedCellR][selectedCellC].setPiece(temp1);
								cell[selectedPieceR][selectedPieceC].setPiece(temp2);
								cell[selectedPieceR][selectedPieceC - 2].setPiece(NULL);
								cell[selectedPieceR][selectedPieceC - 1].setPiece(NULL);
							}
							else
							{
								PlaySound("Data\\Music\\PutDown.wav", NULL, SND_ASYNC);
								if (turn == __BLACK__)
								{
									turn = __WHITE__;
								}
								else
								{
									turn = __BLACK__;
								}
								deSelectPiece();
								rotate();
							}
						}
						else
						{
							cell[selectedPieceR][selectedPieceC + 2].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
							cell[selectedPieceR][selectedPieceC + 1].setPiece(cell[selectedCellR][selectedCellC].getPiece());
							cell[selectedPieceR][selectedPieceC].clear();
							cell[selectedCellR][selectedCellC].clear();
							if (isCheckMate())
							{
								cell[selectedCellR][selectedCellC].setPiece(temp1);
								cell[selectedPieceR][selectedPieceC].setPiece(temp2);
								cell[selectedPieceR][selectedPieceC + 2].setPiece(NULL);
								cell[selectedPieceR][selectedPieceC + 1].setPiece(NULL);
							}
							else
							{
								PlaySound("Data\\Music\\PutDown.wav", NULL, SND_ASYNC);
								if (turn == __BLACK__)
								{
									turn = __WHITE__;
								}
								else
								{
									turn = __BLACK__;
								}
								deSelectPiece();
								rotate();
							}
						}
					}
				}
			}
		}
		else if (selectedPieceR != -1)
		{
			if (cell[selectedCellR][selectedCellC].isMovable(selectedPieceR, selectedPieceC, cell[selectedPieceR][selectedPieceC].getPiece()))
			{

				ChessPiece* temp1 = cell[selectedCellR][selectedCellC].getPiece(), *temp2 = cell[selectedPieceR][selectedPieceC].getPiece();
				cell[selectedCellR][selectedCellC].setPiece(cell[selectedPieceR][selectedPieceC].getPiece());
				cell[selectedPieceR][selectedPieceC].clear();

				if (isCheckMate())
				{
					cell[selectedCellR][selectedCellC].setPiece(temp1);
					cell[selectedPieceR][selectedPieceC].setPiece(temp2);
				}
				else
				{
					PlaySound("Data\\Music\\PutDown.wav", NULL, SND_ASYNC);
					if (turn == __BLACK__)
					{
						turn = __WHITE__;
					}
					else
					{
						turn = __BLACK__;
					}
					deSelectPiece();
					rotate();
				}

			}
		}
		break;
	case 'c':
		deSelectPiece();
		break;
	case 'x':
		setBoard();
		break;
	}
}
ChessCell ChessBoard::at(int i, int j)
{
	return cell[i][j];
}
