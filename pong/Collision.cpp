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


Collider::Contact Collision::resolve(const CircleCollider& actor) const
{
	for (auto other : colliders)
	{
		if ((Collider*)&actor != other)
		{
			auto contact  = other->collidesWith(actor);
			if (contact.penetration)
			{
				return contact;
			}
		}
	}
	return Collider::Contact(0,0);
}

float Collision::resolve(const BoxCollider& actor) const
{
	for (auto other : colliders)
	{
		if ((Collider*)&actor != other)
		{
			if (other->collidesWith(actor))
			{
				float value = other->collidesWith(actor);
				if (value)
				{
					return value;
				}
				//Calculate interpenetration
				//Calculate whatever else is needed
				//Read physics book about collision detection
			}
		}
	}
	return 0.f;
}