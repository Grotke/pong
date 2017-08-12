#pragma once
#include "Collider.h"
#include <array>

class Collision
{
public:
	Collision(const std::array<const Collider const *, 5>& colliders);
	~Collision();

	Collider::Contact resolve(const CircleCollider& collider) const;
	float resolve(const BoxCollider& collider) const;
private:
	const std::array<const Collider const*, 5>& colliders;

	//Collision Loop:
	//When paddle or ball is moved, call resolve collision and pass collider to function.
	//Test collider against all colliders.
	//If a collision is found, get the contact info from it. Interpenetration distance, contact point, contact normal. (Look at this)
	//Return Contact to the caller's move function.
	//Caller adjusts entity according to contact to move collision to surface.
	//Since a Contact was returned, loop through resolveCollision function and resolve collisions until it no longer occurs.
	//Colision detection is finished.

	//Edge cases: What happens if ball is wedged between wall and paddle.
};

