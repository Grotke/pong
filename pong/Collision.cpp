#include "Collision.h"
#include <array>
#include "Collider.h"
#include <iostream>


Collision::Collision(const std::array<const Collider const *, 5>& inColliders)
	: colliders(inColliders)
{
}


Collision::~Collision()
{
}


Collision::Contact Collision::resolve(const CircleCollider& actor) const
{
	for (auto other : colliders)
	{
		if ((Collider*)&actor != other)
		{
			if (other->collidesWith(actor))
			{
				return Contact(1.f);
				//Calculate interpenetration
				//Calculate whatever else is needed
				//Read physics book about collision detection
			}
		}
	}
	return Contact(0.f);
}

Collision::Contact Collision::resolve(const BoxCollider& actor) const
{
	for (auto other : colliders)
	{
		if ((Collider*)&actor != other)
		{
			if (other->collidesWith(actor))
			{
				std::cout << "Collision Made!" << std::endl;
				return Contact(1.f);
				//Calculate interpenetration
				//Calculate whatever else is needed
				//Read physics book about collision detection
			}
		}
	}
	return Contact(0.f);
}