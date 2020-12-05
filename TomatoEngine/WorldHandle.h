#pragma once

#include "World.h"
#include "SDL.h"
#include "GraphicsHandle.h"
#include "Chunk.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>

#define DIVINE 1000

class WorldHandle
{
public:
	Vector2<float> pos;
	static WorldHandle *get() { return instance = (instance == nullptr ? new WorldHandle() : instance); }

	void createWorld(std::string, short, short);
	void loadWorld(std::string);
	int getWorldWidth() { return worldInstance.width; }
	int getWorldHeight() { return worldInstance.height; }

	void pullTexture();

	void update();

private:
	WorldHandle() {}

	static WorldHandle *instance;
	World worldInstance;
	std::unordered_map<short, Chunk> chunks;

	short lastX = -1, lastY = -1;

	friend class Chunk;
};

