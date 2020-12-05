#pragma once

#include <vector>

#include "Vector2.h"
#include "Vector4.h"

struct Input{};

struct PlayerTag
{
	bool isAlive = false;
	bool isArmorBody = false;
	bool isArmorHead = false;
	bool isArmorLegs = false;
	float meleeSpeed = 1.0f;
};

struct Transform
{
	Vector2<float> velocity;
	Vector4<float> accelerate;
	Vector2<float> position;
	unsigned action;
	bool isAttack;
	float stillAttack;
	int direction;
};

struct RenderAble
{
	unsigned type;
	// if type is PLAYER
	// BODY HEAD LEGS EYE1 EYE2 HAIR SHOES
	unsigned spriteId;
	Vector2<int> size;
	Vector2<int> index;
};

struct CameraTracking
{
	bool alive;
};

struct RigidBody
{
	Vector2<char> size;
};