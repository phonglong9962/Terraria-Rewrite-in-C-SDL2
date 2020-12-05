#pragma once

class Camera
{
public:
	static Camera *get() { return instance = (instance == nullptr ? new Camera : instance); }
	Vector2<float> position;

private:
	static Camera *instance;
};