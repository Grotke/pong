#include "SoundManager.h"

/*Define the data variables since declaration isn't enough.*/
sf::Sound SoundManager::hitPaddleSound;
sf::Sound SoundManager::hitWallSound;
sf::Sound SoundManager::scoreIncreaseSound;
sf::Sound SoundManager::ballScoredSound;

sf::SoundBuffer SoundManager::hitPaddleBuffer;
sf::SoundBuffer SoundManager::hitWallBuffer;
sf::SoundBuffer SoundManager::scoreIncreaseBuffer;
sf::SoundBuffer SoundManager::ballScoredBuffer;

void SoundManager::playHitPaddle()
{
	hitPaddleSound.play();
}

void SoundManager::playHitWall()
{
	hitWallSound.play();
}

void SoundManager::playScoreIncrease()
{
	scoreIncreaseSound.play();
}

void SoundManager::playBallScored()
{
	ballScoredSound.play();
}

/*Load hardcoded sound files and set buffers.
Could be more flexible and robust.*/
bool SoundManager::initialize()
{
	if (!hitPaddleBuffer.loadFromFile("sounds/hit_normal.wav")||
		!hitWallBuffer.loadFromFile("sounds/hit_higher.wav")||
		!ballScoredBuffer.loadFromFile("sounds/score_point_lower.wav")||
		!scoreIncreaseBuffer.loadFromFile("sounds/score_up.wav"))
	{
		return false;
	}
	hitPaddleSound.setBuffer(hitPaddleBuffer);
	hitWallSound.setBuffer(hitWallBuffer);
	ballScoredSound.setBuffer(ballScoredBuffer);
	scoreIncreaseSound.setBuffer(scoreIncreaseBuffer);

	return true;
}
