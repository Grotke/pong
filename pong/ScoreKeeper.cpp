#include "ScoreKeeper.h"

int ScoreKeeper::p1Score = 0;
int ScoreKeeper::p2Score = 0;
bool ScoreKeeper::scoreMade = false;

ScoreKeeper::ScoreKeeper()
{
}


ScoreKeeper::~ScoreKeeper()
{
}

void ScoreKeeper::incrementScore(int player)
{
	if (player == 1)
	{
		p1Score++;
	}
	else
	{
		p2Score++;
	}
}

void ScoreKeeper::resetScores()
{
	p1Score = 0;
	p2Score = 0;
}

int ScoreKeeper::getPlayerScore(int player)
{
	if (player == 1)
	{
		return p1Score;
	}
	return p2Score;
}

bool ScoreKeeper::scoreWasMade()
{
	return scoreMade;
}

void ScoreKeeper::setScoreMade(bool scoreStatus)
{
	scoreMade = scoreStatus;
}

