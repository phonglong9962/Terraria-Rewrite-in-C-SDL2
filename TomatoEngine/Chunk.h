#pragma once

#include "Tile.h"

#define CHUNK_SIZE 16
#define TILE_SIZE 16

class Chunk
{
public:
	unsigned short x, y;
	Chunk(unsigned short, unsigned short);
	void update();

private:
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
};