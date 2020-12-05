#pragma once

#include "State.h"

class PlayState : public State
{
public:
	PlayState();

	virtual void init();
	virtual void initInternal();
	virtual void update();
	virtual void updateInternal();

private:
};

