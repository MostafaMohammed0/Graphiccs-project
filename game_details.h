#ifndef __GAME_DETAILS__
#define __GAME_DETAILS__
#include "MAIN.h"
class GameDetails {
private:
	bool GAMEOVER;
	int score, increment;
	int screenHeight,screenWidth;
public:
	GameDetails();
	int getScore();
	void incrementScore();
	bool isOver();
	void save();
	void load();
	void Over();
	void reset();
	int getScreenHeight();
	int getScreenWidth();
	void setScreenHeight();
	void setScreenWidth();
};
#endif