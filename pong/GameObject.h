#pragma once
#include <string>

class GameObject
{
public:
	GameObject(const std::string& type);
	virtual ~GameObject();
	const std::string& getType() const;
	virtual void reset() {}

protected:
	const std::string type;
};
