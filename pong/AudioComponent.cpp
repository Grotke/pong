#include "AudioComponent.h"
#include "ComponentManager.h"
#include "SoundManager.h"

AudioComponent::AudioComponent(int parentId)
	: Component(parentId)
{
}

AudioComponent::~AudioComponent()
{
}

/*Plays a different sound depending on the type of object being hit.*/
void AudioComponent::update(float secondsPassed)
{
	if (ComponentManager::getColliderById(parentId).getPrevCollisionType() == "")
	{
	}
	else if (ComponentManager::getColliderById(parentId).getPrevCollisionType() == "Wall")
	{
		SoundManager::playHitWall();
	}
	else
	{
		SoundManager::playHitPaddle();
	}

	/*Reset prev collision type.
	Otherwise sounds will continously play until another object is hit.*/
	ComponentManager::getColliderById(parentId).setPrevCollisionType("");
}
