#pragma once
#include <SFML/Audio.hpp>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static void playHitPaddle();
	static bool initialize();
	static void playHitWall();
	static void playScoreIncrease();
	static void playBallScored();

private:
	static sf::Sound hitPaddleSound;
	static sf::Sound hitWallSound;
	static sf::Sound scoreIncreaseSound;
	static sf::Sound ballScoredSound;

	static sf::SoundBuffer hitPaddleBuffer;
	static sf::SoundBuffer hitWallBuffer;
	static sf::SoundBuffer scoreIncreaseBuffer;
	static sf::SoundBuffer ballScoredBuffer;
};

