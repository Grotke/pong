#pragma once
#include <string>

struct Contact
{
	Contact(char axis, float pen, const std::string& type) : lastAxisOfReflection(axis), penetration(pen), objectType(type) {}
	char lastAxisOfReflection;
	float penetration;
	std::string objectType;
	static Contact getNullContact() { return Contact('0', 0, ""); }
};
