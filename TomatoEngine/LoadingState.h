#pragma once

#include "State.h"
#include "SDL_thread.h"
#include "Distributor.h"
#include "System.h"
#include "Component.h"
#include "Camera.h"

class LoadingState : public State
{
public:
	int loadingType;
	LoadingState(int);

	virtual void init();
	virtual void initInternal();
	virtual void update();
	virtual void updateInternal();

private:
	SDL_Thread *loadingThread;
};

