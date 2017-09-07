#pragma once
#include <string>
class BoxCollider;
class CircleCollider;

class Collider
{
public:
	Collider();
	virtual ~Collider();

	struct Contact
	{
		Contact(int axis, float pen, const std::string& type) : lastAxisOfReflection(axis), penetration(pen), objectType(type) {}
		int lastAxisOfReflection;
		float penetration;
		const std::string& objectType;
	};

	virtual float collidesWith(const BoxCollider& other) const { return true; }
	virtual Contact collidesWith(const CircleCollider& other) const { return Contact(0,0, std::string("")); }
};

