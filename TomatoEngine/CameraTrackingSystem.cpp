#pragma once

#include "System.h"
#include "WorldHandle.h"

void CameraTrackingSystem::update()
{
	for (auto &entity : entities)
	{
		auto &transform = Distributor::get()->getComponent<Transform>(entity);

		WorldHandle::get()->pos = transform.position;
		auto &cam_pos = Camera::get()->position;
		cam_pos.x = transform.position.x * Window::get()->scaling - Window::get()->getWindowWidth() / 2;
		cam_pos.y = transform.position.y * Window::get()->scaling - Window::get()->getWindowHeight() / 2;
		
		auto worldWidthPixel = WorldHandle::get()->getWorldWidth() * TILE_SIZE;
		auto worldHeightPixel = WorldHandle::get()->getWorldHeight() * TILE_SIZE;

		cam_pos.x = cam_pos.x < 0 ? 0 : cam_pos.x + Window::get()->getWindowWidth() >= worldWidthPixel ?
			(float)worldWidthPixel - Window::get()->getWindowWidth() : cam_pos.x;
		cam_pos.y = cam_pos.y < 0 ? 0 : cam_pos.y + Window::get()->getWindowHeight() >= worldHeightPixel ?
			(float)worldHeightPixel - Window::get()->getWindowHeight() : cam_pos.y;
	}
}