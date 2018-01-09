#pragma once

/*Base class for components.*/
class Component
{
	public:
		Component(int parentId);
		virtual ~Component();
		virtual void update(float secondsPassed);
		virtual int getParentId() const { return parentId; }

	protected:
		int parentId;
};

