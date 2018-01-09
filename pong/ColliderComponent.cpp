#include "ColliderComponent.h"
#include "ComponentManager.h"
#include "Contact.h"

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

/*Checks for a collision against every other collidable object.
	Returns data on the first collision 
	and remembers the collision type for audio purposes.*/
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
	return Contact::getNullContact();
}

/*Checks for overlap on the X and Y axis with another collider.
A collision has occured if both axes overlaps.
Overlap occurs if the distance between the centers 
is less than the sum of the half lengths of each collider on the axis being tested.
The axis with the least overlap, along with the amount of overlap, is returned 
since it requires the least adjustment to have both axes no longer overlapping.*/
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


