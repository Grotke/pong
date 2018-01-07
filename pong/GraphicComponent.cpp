#include "ComponentManager.h"
#include "GraphicComponent.h"

GraphicComponent::GraphicComponent(int parentId, bool isCircle)
	: Component(parentId), isCircle(isCircle)
{
}

GraphicComponent::~GraphicComponent()
{
}

/*A new sprite is created each time one is requested, for no particular reason 
(it was easier than checking if one already existed).
Of course, updating it would be more efficient.*/
sf::Shape& GraphicComponent::getSprite()
{
	TransformComponent transform = ComponentManager::getTransformById(parentId);
	float width = transform.getWidth();
	float height = transform.getHeight();
	if (isCircle)
	{
		float radius = width / 2;
		circleSprite = sf::CircleShape(radius);
		circleSprite.setOrigin(radius, radius);
		circleSprite.setPosition(transform.getPosition());
		circleSprite.setFillColor(fillColor);
		return circleSprite;
	}
	else
	{
		recSprite = sf::RectangleShape(sf::Vector2f(width, height));
		recSprite.setOrigin(width / 2, height / 2);
		recSprite.setFillColor(fillColor);
		recSprite.setPosition(transform.getPosition());
		return recSprite;
	}
}