#pragma once

#include <vector>

#include "AIComponent.h"
#include "AudioComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "GraphicComponent.h"
#include "MovementComponent.h"
#include "PlayerComponent.h"
#include "NetworkComponent.h"

/*This class manages the game's components,
associating an object to its different components.

You can immediately start adding components to an object 
without prepopulating the object into the manager,
but don't try to get a component without setting it since 
it'd probably crash.

This class looks more complex than it is since 
most of these methods are just setters or getters for the different components.
This class could probably be done better with templates.
*/
class ComponentManager
{
	public:
		ComponentManager();
		~ComponentManager();
		static const std::map<int, ColliderComponent *> getColliders();
		static const std::map<int, TransformComponent *> getTransforms();
		static const std::map<int, MovementComponent *> getMovements();
		static const std::map<int, GraphicComponent *> getGraphics();
		static const std::map<int, PlayerComponent *> getPlayers();
		static const std::map<int, AIComponent *> getAIs();
		static const std::map<int, AudioComponent *> getAudios();
		static const std::map<int, NetworkComponent *> getNetworks();

		/*Components must be added before they can be fetched
		because these getters don't verify that a component exists
		before trying to access them.*/
		static TransformComponent& getTransformByParent(const GameObject& parent);
		static ColliderComponent& getColliderByParent(const GameObject& parent);
		static MovementComponent& getMovementByParent(const GameObject& parent);
		static GraphicComponent& getGraphicByParent(const GameObject& parent);
		static AIComponent& getAIByParent(const GameObject& parent);
		static PlayerComponent& getPlayerByParent(const GameObject& parent);
		static AudioComponent& getAudioByParent(const GameObject& parent);
		static NetworkComponent& getNetworkByParent(const GameObject& parent);

		static TransformComponent& getTransformById(int parentId);
		static ColliderComponent& getColliderById(int parentId);
		static MovementComponent& getMovementById(int parentId);
		static GraphicComponent& getGraphicById(int parentId);
		static AIComponent& getAIById(int parentId);
		static PlayerComponent& getPlayerById(int parentId);
		static AudioComponent& getAudioById(int parentId);
		static NetworkComponent& getNetworkById(int parentId);

		static const GameObject& getParentById(int parentId);
		static void addTransformTo(const GameObject& object, const sf::Vector2f& startPos, float height, float width);
		static void addColliderTo(const GameObject& object);
		static void addMovementTo(const GameObject& object, const sf::Vector2f& startDir, float startSpeed, float topSpeed, bool isBouncy);
		static void addPlayerTo(const GameObject& object, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
		static void addAITo(const GameObject& object, const Ball& ball);
		static void addGraphicTo(const GameObject& object, bool isCircle);
		static void addAudioTo(const GameObject& object);
		static void addNetworkTo(const GameObject& object, const NetworkComponent::NetworkMode& mode);
		
		static void removeAIFrom(const GameObject& object);
		static void removePlayerFrom(const GameObject& object);
		static void removeControlComponents(const GameObject& object);

	private:
		static std::map<int, ColliderComponent *> colliders;
		static std::map<int, TransformComponent *> transforms;
		static std::map<int, MovementComponent *> movements;
		static std::map<int, GraphicComponent *> graphics;
		static std::map<int, AIComponent *> ais;
		static std::map<int, PlayerComponent *> players;
		static std::map<int, AudioComponent *> audios;
		static std::map<int, NetworkComponent *> networks;
		static std::map<const GameObject * const, int> objectMap;
		static std::map<int, const GameObject *> idMap;
		static int getOrAddObjectId(const GameObject& object);
		static int getNextId();
		static int nextId;
};

