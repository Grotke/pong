#pragma once
class ScoreKeeper
{
public:
	ScoreKeeper();
	~ScoreKeeper();

	static void incrementScore(int player);
	static void resetScores();
	static int getPlayerScore(int player);

//private:
	static int p1Score;
	static int p2Score;
};

