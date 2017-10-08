#pragma once
#include "Component.h"
#include "Contact.h"
#include "TransformComponent.h"

class ColliderComponent :
	public Component
{
public:
	ColliderComponent(int parentId);
	virtual ~ColliderComponent();

	Contact resolve();

	Contact collidesWith(const ColliderComponent& other) const;
	float getHalfLengthX() const;
	float getHalfLengthY() const;
	float getCenterX() const;
	float getCenterY() const;
	const std::string& getPrevCollisionType() const;
	void setPrevCollisionType(const std::string& newCollision);

private:
	std::string prevCollisionType;
};

