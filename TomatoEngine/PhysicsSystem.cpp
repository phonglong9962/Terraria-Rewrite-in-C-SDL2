#pragma once

#include "Window.h"
#include "System.h"
#include "SDL.h"

void PhysicsSystem::update()
{
	for (auto &entity : entities)
	{
		auto &transform = Distributor::get()->getComponent<Transform>(entity);
		auto &rigidbody = Distributor::get()->getComponent<RigidBody>(entity);
		
		// Apply Gravity
		transform.velocity.y += 0.3f;
		transform.velocity.y = transform.velocity.y >= 5.0f ? 5.0f : transform.velocity.y;


		// Rect box
		float scale = Window::get()->scaling;

		SDL_FRect rect;
		rect.x = transform.position.x * scale - Camera::get()->position.x + (rigidbody.size.x - rigidbody.size.x * scale) / 2.0f;
		rect.y = transform.position.y * scale - Camera::get()->position.y + (rigidbody.size.y - rigidbody.size.y * scale) / 4.0f;
		rect.w = rigidbody.size.x * scale;
		rect.h = rigidbody.size.y * scale;

		SDL_RenderDrawRectF(Window::get()->getRenderer(), &rect);
	}
}