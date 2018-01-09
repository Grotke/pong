#pragma once

#include <string>

/*All game entities that will have components attached to them 
need to inherit from GameObject to be created.*/
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
