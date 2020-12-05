#pragma once

class State
{
public:
	int id;

	virtual void init() = 0;
	virtual void initInternal() = 0;
	virtual void update() = 0;
	virtual void updateInternal() = 0;
};

#include <iostream>
#include "Window.h"
#include "GraphicsHandle.h"
#include "KeyInput.h"
#include "MouseInput.h"
