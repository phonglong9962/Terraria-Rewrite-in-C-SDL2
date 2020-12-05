#include "Chunk.h"
#include "GraphicsHandle.h"

Chunk::Chunk(unsigned short _x, unsigned short _y)
{
	x = _x;
	y = _y;
	for (unsigned short i = 0; i < CHUNK_SIZE; ++i)
	{
		for (unsigned short j = 0; j < CHUNK_SIZE; ++j)
		{
			auto &tile = tiles[i][j];
			tile.id = WorldHandle::get()->worldInstance.tiles[(x * CHUNK_SIZE) + i][(y * CHUNK_SIZE) + j];
			tile.index.x = 1;
			tile.index.y = 1;
			tile.size.x = TILE_SIZE;
			tile.size.y = TILE_SIZE;
		}
	}
}

void Chunk::update()
{
	for (unsigned short i = 0; i < CHUNK_SIZE; ++i)
	{
		for (unsigned short j = 0; j < CHUNK_SIZE; ++j)
		{
			auto tile = tiles[i][j];
			if (tile.id == -1) continue;
			GraphicsHandle::get()->showSprite(TEXTURE_TYPE_TILE, tile.id,
				Vector2<float>(float((x * CHUNK_SIZE * TILE_SIZE + i * TILE_SIZE)), 
								float((y * CHUNK_SIZE * TILE_SIZE + j * TILE_SIZE))),
				tile.size, tile.index);
		}
	}
}