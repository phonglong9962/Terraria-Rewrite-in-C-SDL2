#pragma once

#include "Types.h"
#include "Distributor.h"
#include "Component.h"

class RenderSystem : public System
{
public:
	void update() override;
};
class MovementSystem : public System
{
public:
	void update() override;
};
class InputSystem : public System
{
public:
	void update() override;
};
class CameraTrackingSystem : public System
{
public:
	void update() override;
};
class PhysicsSystem : public System
{
public:
	void update() override;
};
