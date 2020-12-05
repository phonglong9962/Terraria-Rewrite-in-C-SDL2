#pragma once

#include "System.h"

void MovementSystem::update()
{
	for (auto &entity : entities)
	{
		auto &transform = Distributor::get()->getComponent<Transform>(entity);

		transform.velocity.x = transform.velocity.x < -transform.accelerate.w ? -transform.accelerate.w :
			transform.velocity.x > transform.accelerate.w ? transform.accelerate.w : transform.velocity.x;
		transform.position.x += transform.velocity.x;

		transform.position.y += transform.velocity.y;

		transform.action = transform.velocity.y != 0 ? 2 : transform.velocity.x != 0 ? 1 : 0;
	}
}