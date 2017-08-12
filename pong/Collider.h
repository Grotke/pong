#pragma once
class BoxCollider;
class CircleCollider;

class Collider
{
public:
	Collider();
	virtual ~Collider();

	struct Contact
	{
		Contact(int axis, float pen) : lastAxisOfReflection(axis), penetration(pen) {}
		int lastAxisOfReflection;
		float penetration;
	};

	virtual float collidesWith(const BoxCollider& other) const { return true; }
	virtual Contact collidesWith(const CircleCollider& other) const { return Contact(0,0); }
};

