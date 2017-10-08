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
	ComponentManager::getColliderById(parentId).setPrevCollisionType("");
}
