#include "Controller.h"
#include "Paddle.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::attachParent(Paddle* parent) {
	if (parent)
	{
		this->parent = parent;
	}
}
