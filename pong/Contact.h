#pragma once

#include <string>

/*A Contact is generated when two objects collide and is used to resolve the collision.
Contains:
- The amount of interobject penetration (so the objects can be separated by that amount)
- The axis of reflection (X or Y) which is used to correctly change 
	the movement vector of the ball after a collision (simulating a bounce)
 - The object type, which is used by audio to determine which sound should play on collision
*/
struct Contact
{
	Contact(char axis, float pen, const std::string& type) : lastAxisOfReflection(axis), penetration(pen), objectType(type) {}
	char lastAxisOfReflection;
	float penetration;
	std::string objectType;

	/*Convenience function to get a Contact that counts as null (no collision)
	so we don't risk breaking on a null pointer.*/
	static Contact getNullContact() { return Contact('0', 0, ""); }
};
