#pragma once
class BoxCollider;
class CircleCollider;

class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual bool collidesWith(const BoxCollider& other) const { return true; }
	virtual bool collidesWith(const CircleCollider& other) const { return true; }
};

