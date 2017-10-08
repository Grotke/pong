#include "GraphicComponent.h"
#include "ComponentManager.h"



GraphicComponent::GraphicComponent(int parentId, bool isCircle)
	: Component(parentId), isCircle(isCircle)
{
}


GraphicComponent::~GraphicComponent()
{
}

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
