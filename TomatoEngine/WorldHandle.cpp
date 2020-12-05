#include "WorldHandle.h"

WorldHandle *WorldHandle::instance = nullptr;

void WorldHandle::createWorld(std::string filename, short _w, short _h)
{
	SDL_Log("Creating World!");

	std::ofstream file(filename + ".wld", std::ios::out | std::ios::binary);

	file.write((char*)&filename, sizeof(std::string));
	file.write((char*)&_w, sizeof(short));
	file.write((char*)&_h, sizeof(short));

	std::vector<std::vector<short>> tiles;
	tiles.resize(_w);
	for (unsigned short i = 0; i < tiles.size(); i++)
	{
		tiles.at(i).resize(_h);
	}

	for (unsigned short i = 0; i < _w; ++i)
	{
		for (unsigned short j = 0; j < _h; ++j)
		{
			if (j < 30)
			{
				tiles[i][j] = -1;
				continue;
			}
			tiles[i][j] = 0;
		}
	}

	for (unsigned short i = 0; i < _w; ++i)
	{
		for (unsigned short j = 0; j < _h; ++j)
		{
			file.write((char*)&tiles[i][j], sizeof(short));
		}
	}

	file.close();

	SDL_Log("Done creating sample World!");
}

void WorldHandle::loadWorld(std::string filename)
{
	SDL_Log("Loading Sample World!");

	std::ifstream file(filename + ".wld", std::ios::in | std::ios::binary);

	if (!worldInstance.packed)
	{
		file.read((char*)&worldInstance.name, sizeof(std::string));
		file.read((char*)&worldInstance.width, sizeof(short));
		file.read((char*)&worldInstance.height, sizeof(short));

		worldInstance.tiles.resize(worldInstance.width);
		for (unsigned short i = 0; i < worldInstance.tiles.size(); i++)
		{
			worldInstance.tiles.at(i).resize(worldInstance.height);
		}

		for (unsigned short i = 0; i < worldInstance.width; ++i)
		{
			for (unsigned short j = 0; j < worldInstance.height; ++j)
			{
				file.read((char*)&worldInstance.tiles[i][j], sizeof(short));
			}
		}
		worldInstance.packed = true;
	}

	file.close();

	SDL_Log("Done loading Sample World!");
}

void WorldHandle::pullTexture()
{
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_TILE, DIRT_TILE_TEXTURE, "assets/Tiles_0.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_TILE, STONE_TILE_TEXTURE, "assets/Tiles_1.png");
}

void WorldHandle::update()
{
	// check chunk
	bool needReload = false;

	unsigned short x = unsigned short(pos.x / CHUNK_SIZE / TILE_SIZE);
	unsigned short y = unsigned short(pos.y / CHUNK_SIZE / TILE_SIZE);

	if ((x != lastX || y != lastY) && x >= 0 && y >= 0 &&
		x < worldInstance.width / CHUNK_SIZE && y < worldInstance.height / CHUNK_SIZE)
	{
		needReload = true;
	}

	if (needReload)
	{
		lastX = x;
		lastY = y;
		auto xp = x + 1, xm = x - 1, yp = y + 1, ym = y - 1;

		// clean chunk
		for (auto &it = chunks.begin(); it != chunks.end();)
		{
			auto &chunk = *it;
			if (chunk.first != x * DIVINE + y &&
				chunk.first != xm * DIVINE + y && chunk.first != xp * DIVINE + y &&
				chunk.first != x * DIVINE + ym && chunk.first != x * DIVINE + yp &&
				chunk.first != xm * DIVINE + ym && chunk.first != xm * DIVINE + yp &&
				chunk.first != xp * DIVINE + ym && chunk.first != xp * DIVINE + yp)
			{
				it = chunks.erase(it);
			}
			else
			{
				++it;
			}
		}

		// load chunk
		// Center
		if (!chunks.count(short(x * DIVINE + y)))
			chunks.emplace(short(x * DIVINE + y), Chunk(x, y));
		// Cross +
		if (xm >= 0 && y >= 0 && 
			xm < worldInstance.width / CHUNK_SIZE && y < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xm * DIVINE + y)))
			chunks.emplace(short(xm * DIVINE + y), Chunk(xm, y));
		if (xp >= 0 && y >= 0 &&
			xp < worldInstance.width / CHUNK_SIZE && y < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xp * DIVINE + y)))
			chunks.emplace(short(xp * DIVINE + y), Chunk(xp, y));
		if (x >= 0 && ym >= 0 &&
			x < worldInstance.width / CHUNK_SIZE && ym < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(x * DIVINE + ym)))
			chunks.emplace(short(x * DIVINE + ym), Chunk(x, ym));
		if (x >= 0 && yp >= 0 &&
			x < worldInstance.width / CHUNK_SIZE && yp< worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(x * DIVINE + yp)))
			chunks.emplace(short(x * DIVINE + yp), Chunk(x, yp));
		// Cross x
		if (xm >= 0 && ym >= 0 &&
			xm < worldInstance.width / CHUNK_SIZE && ym < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xm * DIVINE + ym)))
			chunks.emplace(short(xm * DIVINE + ym), Chunk(xm, ym));
		if (xp >= 0 && yp >= 0 &&
			xp < worldInstance.width / CHUNK_SIZE && yp < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xp * DIVINE + yp)))
			chunks.emplace(short(xp * DIVINE + yp), Chunk(xp, yp));
		if (xp >= 0 && ym >= 0 &&
			xp < worldInstance.width / CHUNK_SIZE && ym < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xp * DIVINE + ym)))
			chunks.emplace(short(xp * DIVINE + ym), Chunk(xp, ym));
		if (xm >= 0 && yp >= 0 &&
			xm < worldInstance.width / CHUNK_SIZE && yp < worldInstance.height / CHUNK_SIZE &&
			!chunks.count(short(xm * DIVINE + yp)))
			chunks.emplace(short(xm * DIVINE + yp), Chunk(xm, yp));
	}

	// update chunk
	for (auto &chunk : chunks)
	{
		chunk.second.update();
	}
}