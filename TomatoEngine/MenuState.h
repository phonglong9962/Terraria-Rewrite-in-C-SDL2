#pragma once

#include "State.h"
#include "WorldHandle.h"

#include <cstdlib>
#include <ctime>

class MenuState : public State
{
public:
	MenuState();

	virtual void init();
	virtual void initInternal();
	virtual void update();
	virtual void updateInternal();
};

