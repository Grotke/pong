#include "ComponentManager.h"
#include "Config.h"
#include "Wall.h"

/*Wall is simple with a transform, graphic and collider.*/
Wall::Wall(float x, float y): GameObject("Wall")
{
	float width = Config::SCREEN_WIDTH;
	float height = Config::SCREEN_HEIGHT /20;
	ComponentManager::addTransformTo(*this, sf::Vector2f(x, y), height, width);
	ComponentManager::addGraphicTo(*this, false);
	ComponentManager::addColliderTo(*this);
}

Wall::~Wall()
{
}