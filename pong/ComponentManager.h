#pragma once
#include "ColliderComponent.h"
#include "GraphicComponent.h"
#include "AIComponent.h"
#include "PlayerComponent.h"
#include "MovementComponent.h"
#include "AudioComponent.h"
#include "GameObject.h"
#include <vector>
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
		static TransformComponent& getTransformByParent(const GameObject& parent);
		static ColliderComponent& getColliderByParent(const GameObject& parent);
		static MovementComponent& getMovementByParent(const GameObject& parent);
		static GraphicComponent& getGraphicByParent(const GameObject& parent);
		static AIComponent& getAIByParent(const GameObject& parent);
		static PlayerComponent& getPlayerByParent(const GameObject& parent);
		static AudioComponent& getAudioByParent(const GameObject& parent);

		static TransformComponent& getTransformById(int parentId);
		static ColliderComponent& getColliderById(int parentId);
		static MovementComponent& getMovementById(int parentId);
		static GraphicComponent& getGraphicById(int parentId);
		static AIComponent& getAIById(int parentId);
		static PlayerComponent& getPlayerById(int parentId);
		static AudioComponent& getAudioById(int parentId);

		static const GameObject& getParentById(int parentId);
		static void addTransformTo(const GameObject& object, const sf::Vector2f& startPos, float height, float width);
		static void addColliderTo(const GameObject& object);
		static void addMovementTo(const GameObject& object, const sf::Vector2f& startDir, float startSpeed, float topSpeed, bool isBouncy);
		static void addPlayerTo(const GameObject& object, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
		static void addAITo(const GameObject& object, const Ball& ball);
		static void addGraphicTo(const GameObject& object, bool isCircle);
		static void addAudioTo(const GameObject& object);
		
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
		static std::map<const GameObject * const, int> objectMap;
		static std::map<int, const GameObject *> idMap;
		static int getOrAddObjectId(const GameObject& object);
		static int getNextId();
		static int nextId;
};

