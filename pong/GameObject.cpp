#include <string>

#include "GameObject.h"

GameObject::GameObject(const std::string& type): type(type)
{
}

GameObject::~GameObject()
{
}

const std::string& GameObject::getType() const
{
	return type;
}

