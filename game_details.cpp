#include "game_details.h"

GameDetails::GameDetails()
	{
		GAMEOVER = false;
		score = 0;
		increment = 10;
	}
	int GameDetails::getScreenHeight()
	{
		return screenHeight;
	}
	int GameDetails::getScreenWidth()
	{
		return screenWidth;
	}
	void GameDetails::setScreenHeight()
	{
		screenHeight = iG::iGetWindowHeight();
	}
	void GameDetails::setScreenWidth()
	{
		screenWidth = iG::iGetWindowWidth();
	}
	int GameDetails::getScore()
	{
		return score;
	}
	void GameDetails::incrementScore()
	{
		score += increment;
	}
	bool GameDetails::isOver()
	{
		return GAMEOVER;
	}
	void GameDetails::save()
	{
		ofstream out;
		out.open("Data\\RESUME.txt", ios::out);

		out.close();

	}
	void GameDetails::load()
	{
		ifstream in;
		in.open("Data\\RESUME.txt", ios::in);

		in.close();
	}
	void GameDetails::Over()
	{
		GAMEOVER = true;
	}
	void GameDetails::reset()
	{
		GAMEOVER = false;
		score = 0;

	}