#include "ColliderComponent.h"
#include "Contact.h"
#include "ComponentManager.h"


ColliderComponent::ColliderComponent(int parentId) : Component(parentId)
{
}


ColliderComponent::~ColliderComponent()
{
}

const std::string& ColliderComponent::getPrevCollisionType() const
{
	return prevCollisionType;
}

Contact ColliderComponent::resolve()
{
	prevCollisionType = "";
	for (auto other : ComponentManager::getColliders())
	{
		auto otherCollider = other.second;
		if (this != otherCollider)
		{
			Contact contact = collidesWith(*otherCollider);
			if (contact.penetration)
			{
				prevCollisionType = contact.objectType;
				return contact;
			}
		}
	}
	//OUTLINE OF VELOCITY TRANSFER
	//Velocity of paddle should transfer to velocity of ball
	//Paddle (and maybe ball too) should have current velocity and max speed
	//What happens when ball hits corner of paddle versus head on
	return Contact::getNullContact();
}

Contact ColliderComponent::collidesWith(const ColliderComponent& other) const
{
	float lengthBothX = other.getHalfLengthX() + getHalfLengthX();
	float lengthBothY = other.getHalfLengthY() + getHalfLengthY();
	float centerDistanceX = abs(other.getCenterX() - getCenterX());
	float centerDistanceY = abs(other.getCenterY() - getCenterY());
	float overlapX = lengthBothX - centerDistanceX;
	float overlapY = lengthBothY - centerDistanceY;

	if (overlapX < 0 || overlapY < 0)
	{
		return Contact::getNullContact();
	}
	else
	{
		GameObject otherParent = ComponentManager::getParentById(other.getParentId());
		if (overlapX < overlapY)
		{
			return Contact('X', overlapX, otherParent.getType());
		}
		else
		{
			return Contact('Y', overlapY, otherParent.getType());
		}
	}
}

float ColliderComponent::getHalfLengthX() const
{
	return ComponentManager::getTransformById(parentId).getWidth() / 2;
}

float ColliderComponent::getHalfLengthY() const
{
	return ComponentManager::getTransformById(parentId).getHeight() / 2;

}

float ColliderComponent::getCenterX() const
{
	return ComponentManager::getTransformById(parentId).getPosition().x;

}

float ColliderComponent::getCenterY() const
{
	return ComponentManager::getTransformById(parentId).getPosition().y;

}

void ColliderComponent::setPrevCollisionType(const std::string& newCollision)
{
	prevCollisionType = newCollision;
}


