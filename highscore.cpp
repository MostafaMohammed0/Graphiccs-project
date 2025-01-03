#include "main.h"
struct ScoreType
	{
		string name;
		int score;
	};
void saveScore()
{
	
	vector<ScoreType> ScoreSheet;
	int i, j, k;
	ifstream in;
	in.open("Data\\HIGHSCORE.txt", ios::in);
	while (!in.eof())
	{
		string name;
		int score;
		in >> name >> score;
		if (name != "")
		{
			ScoreSheet.push_back({name, score});
		}
	}
	in.close();

	for (j = 0; j < ScoreSheet.size(); j++)
	{
		if (game.getScore() > ScoreSheet[j].score)
		{
			break;
		}
	}
	if (j == ScoreSheet.size() && j < 10)
	{
		
	}
	ofstream out;
	out.open("Data\\HIGHSCORE.txt", ios::out);
	for (i = 0; i < ScoreSheet.size() - 1&&i<9; i++)
	{
		out << ScoreSheet[i].name << " " << ScoreSheet[i].score << endl;
	}
	out << ScoreSheet[i].name << " " << ScoreSheet[i].score;
	out.close();
}

bool isHighScore()
{
	vector<ScoreType> ScoreSheet;
	int i, j, k;
	ifstream in;
	in.open("Data\\HIGHSCORE.txt", ios::in);
	while (!in.eof())
	{
		string name;
		int score;
		in >> name >> score;
		if (name != "")
		{
			ScoreSheet.push_back({name, score});
		}
	}
	in.close();

	for (j = 0; j < ScoreSheet.size(); j++)
	{
		
	}
	if (j == ScoreSheet.size() && j < 10)
	{
		return true;
	}

	return false;
}