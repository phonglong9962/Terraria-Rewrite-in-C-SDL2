#pragma once

#include "System.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "WorldHandle.h"

void InputSystem::update()
{
	for (auto &entity : entities)
	{
		auto &transform = Distributor::get()->getComponent<Transform>(entity);

		if (KeyInput::get()->keyLeft && !KeyInput::get()->keyRight)
		{
			transform.direction = -1;
			transform.velocity.x = transform.velocity.x > 0 ?
				transform.velocity.x -= (transform.accelerate.x + transform.accelerate.x * 2) :
				transform.velocity.x -= transform.accelerate.x;
		}
		else if (KeyInput::get()->keyRight && !KeyInput::get()->keyLeft)
		{
			transform.direction = 1;
			transform.velocity.x = transform.velocity.x < 0 ?
				transform.velocity.x += (transform.accelerate.x + transform.accelerate.x * 2) :
				transform.velocity.x += transform.accelerate.x;
		}
		else
		{
			transform.velocity.x = transform.velocity.x < -1 ? transform.velocity.x += (transform.accelerate.x * 2) :
				transform.velocity.x > 1 ? transform.velocity.x -= (transform.accelerate.x * 2) : 0;
		}

		if (MouseInput::get()->leftClick)
		{
			transform.isAttack = true;
			float scale = Window::get()->scaling;
			if (MouseInput::get()->GetCoordX() < (transform.position.x) * scale + 20 - Camera::get()->position.x)
			{
				transform.direction = -1;
			}
			else if (MouseInput::get()->GetCoordX() > (transform.position.x) * scale + 20 - Camera::get()->position.x)
			{
				transform.direction = 1;
			}
		}

		if (KeyInput::get()->keyJump)
		{
			transform.velocity.y -= 0.5f;
		}

		/*if (KeyInput::get()->keyUp)
		{
			transform.velocity.y -= transform.accelerate.y;
		}
		else if (KeyInput::get()->keyDown)
		{
			transform.velocity.y += transform.accelerate.y;
		}
		else
		{
			transform.velocity.y = 0;
		}*/
	}
}