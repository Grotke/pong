#pragma once

/*This class keeps track of current player scores. 
It tracks and changes the player scores.
It also tracks whether a score was made recently 
(and still needs to be processed).*/
class ScoreKeeper
{
public:
	/*No custom constructor needed. 
	It's never called since all methods should be static.*/
	static void incrementScore(int player);
	static void resetScores();
	static int getPlayerScore(int player);
	static bool scoreWasMade();
	static void setScoreMade(bool scoreStatus);

private:
	static int p1Score;
	static int p2Score;
	static bool scoreMade;
};

