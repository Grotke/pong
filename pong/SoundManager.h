#pragma once

#include <SFML/Audio.hpp>

/*This class loads sounds and 
has a convenient interface for other code to play sounds at the right time.
Can't easily change sounds without changing source, 
doesn't limit the number of sounds generated at a time,
or anything smart. Just a dumb sound player that 
prettifies buffer setting and playing sounds.*/
class SoundManager
{
public:
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

