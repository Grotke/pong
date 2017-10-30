#include "ComponentManager.h"

int ComponentManager::nextId = 1;
std::map<int, ColliderComponent *> ComponentManager::colliders;
std::map<int, TransformComponent *> ComponentManager::transforms;
std::map<int, MovementComponent *> ComponentManager::movements;
std::map<int, GraphicComponent *> ComponentManager::graphics;
std::map<int, AIComponent *> ComponentManager::ais;
std::map<int, PlayerComponent *> ComponentManager::players;
std::map<int, AudioComponent *> ComponentManager::audios;
std::map<const GameObject * const, int> ComponentManager::objectMap;
std::map<int, const GameObject *> ComponentManager::idMap;

ComponentManager::ComponentManager()
{
}


ComponentManager::~ComponentManager()
{
}

const std::map<int, ColliderComponent *> ComponentManager::getColliders()
{
	return colliders;
}

const std::map<int, TransformComponent *> ComponentManager::getTransforms()
{
	return transforms;
}

const std::map<int, MovementComponent *> ComponentManager::getMovements()
{
	return movements;
}

const std::map<int, GraphicComponent *> ComponentManager::getGraphics()
{
	return graphics;
}

const std::map<int, PlayerComponent *> ComponentManager::getPlayers()
{
	return players;
}

const std::map<int, AIComponent *> ComponentManager::getAIs()
{
	return ais;
}

const std::map<int, AudioComponent *> ComponentManager::getAudios()
{
	return audios;
}

TransformComponent& ComponentManager::getTransformByParent(const GameObject& parent)
{
	return *(transforms[objectMap[&parent]]);
}

ColliderComponent& ComponentManager::getColliderByParent(const GameObject& parent)
{
	return *colliders[objectMap[&parent]];
}

MovementComponent& ComponentManager::getMovementByParent(const GameObject& parent)
{
	return *movements[objectMap[&parent]];
}

GraphicComponent& ComponentManager::getGraphicByParent(const GameObject& parent)
{
	return *graphics[objectMap[&parent]];
}

AIComponent& ComponentManager::getAIByParent(const GameObject& parent)
{
	return *ais[objectMap[&parent]];
}

PlayerComponent& ComponentManager::getPlayerByParent(const GameObject& parent)
{
	return *players[objectMap[&parent]];
}

AudioComponent& ComponentManager::getAudioByParent(const GameObject& parent)
{
	return *audios[objectMap[&parent]];
}

void ComponentManager::addTransformTo(const GameObject& object, const sf::Vector2f& startPos, float height, float width)
{
	int id = getOrAddObjectId(object);
	TransformComponent* transform = new TransformComponent(id, startPos, height, width);
	transforms[id] = transform;
}

void ComponentManager::addColliderTo(const GameObject& object)
{
	int id = getOrAddObjectId(object);
	ColliderComponent* collider = new ColliderComponent(id);
	colliders[id] = collider;
}

void ComponentManager::addMovementTo(const GameObject& object, const sf::Vector2f& startDir, float startSpeed, float topSpeed, bool isBouncy)
{
	int id = getOrAddObjectId(object);
	MovementComponent* movement = new MovementComponent(id, startDir, startSpeed, topSpeed, isBouncy);
	movements[id] = movement;
}

void ComponentManager::addPlayerTo(const GameObject& object, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
{
	int id = getOrAddObjectId(object);
	PlayerComponent* player = new PlayerComponent(id, upKey, downKey);
	players[id] = player;
}

void ComponentManager::addAITo(const GameObject& object, const Ball& ball)
{
	int id = getOrAddObjectId(object);
	int ballId = getOrAddObjectId(ball);
	AIComponent* ai = new AIComponent(id, ballId);
	ais[id] = ai;
}

void ComponentManager::removeAIFrom(const GameObject& object)
{
	int id = getOrAddObjectId(object);
	delete ais[id];
	ais.erase(id);
}

void ComponentManager::removePlayerFrom(const GameObject& object)
{
	int id = getOrAddObjectId(object);
	delete players[id];
	players.erase(id);
}

void ComponentManager::removeControlComponents(const GameObject& object)
{
	int id = getOrAddObjectId(object);
	if (ais.count(id))
	{
		removeAIFrom(object);
	}
	if (players.count(id))
	{
		removePlayerFrom(object);
	}
}

void ComponentManager::addGraphicTo(const GameObject& object, bool isCircle)
{
	int id = getOrAddObjectId(object);
	GraphicComponent* graphic = new GraphicComponent(id, isCircle);
	graphics[id] = graphic;
}

void ComponentManager::addAudioTo(const GameObject& object)
{
	int id = getOrAddObjectId(object);
	AudioComponent* audio = new AudioComponent(id);
	audios[id] = audio;
}

TransformComponent& ComponentManager::getTransformById(int parentId)
{
	return *transforms[parentId];
}

ColliderComponent& ComponentManager::getColliderById(int parentId)
{
	return *colliders[parentId];
}

MovementComponent& ComponentManager::getMovementById(int parentId)
{
	return *movements[parentId];
}

GraphicComponent& ComponentManager::getGraphicById(int parentId)
{
	return *graphics[parentId];
}

AIComponent& ComponentManager::getAIById(int parentId)
{
	return *ais[parentId];
}

PlayerComponent& ComponentManager::getPlayerById(int parentId)
{
	return *players[parentId];
}

AudioComponent& ComponentManager::getAudioById(int parentId)
{
	return *audios[parentId];
}

const GameObject& ComponentManager::getParentById(int parentId)
{
	return *idMap[parentId];
}

int ComponentManager::getOrAddObjectId(const GameObject& object)
{
	if (objectMap.count(&object))
	{
		return objectMap[&object];
	}
	int newId = getNextId();
	objectMap[&object] = newId;
	idMap[newId] = &object;
	return newId;
}

int ComponentManager::getNextId()
{
	return nextId++;
}

