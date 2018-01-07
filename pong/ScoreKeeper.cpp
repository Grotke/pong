#include "ScoreKeeper.h"

/*Initialize scores here since 
they can't be set in header unless they were const
and can't be set in constructor 
since the constructor is never called for this static class.*/
int ScoreKeeper::p1Score = 0;
int ScoreKeeper::p2Score = 0;
bool ScoreKeeper::scoreMade = false;

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

/*Used by outside code to check if post-score 
processing should be done.*/
bool ScoreKeeper::scoreWasMade()
{
	return scoreMade;
}

/*scoreMade should be set and unset by outside code.*/
void ScoreKeeper::setScoreMade(bool scoreStatus)
{
	scoreMade = scoreStatus;
}