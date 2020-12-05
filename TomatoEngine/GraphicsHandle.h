#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Window.h"
#include "Vector2.h"
#include "Vector4.h"
#include "AssetsPool.h"
#include "Camera.h"

#include <unordered_map>
#include <cmath>

class GraphicsHandle
{
public:
	static GraphicsHandle *get() { return instance = (instance == nullptr ? new GraphicsHandle() : instance); }

	void loadSprite(short, short, std::string filename);

	void cleanSprite(short, short);

	void showSprite(short, short, SDL_RendererFlip = SDL_FLIP_NONE);

	void showSprite(short, short, Vector2<float>, Vector2<int>, SDL_RendererFlip = SDL_FLIP_NONE);

	void showSprite(short, short, Vector2<float>, Vector2<int>, Vector2<int>, SDL_RendererFlip = SDL_FLIP_NONE);

	//void showTile(int, Vector2<float>, Vector2<int>, char = 1);

private:
	GraphicsHandle()
	{
		sprites.resize(ALL_TEXTURE_TYPE);
		sprites[TEXTURE_TYPE_NPC].resize(MAX_NPC_TEXTURE);
		sprites[TEXTURE_TYPE_ARMOR_HEAD].resize(MAX_ARMOR_HEAD_TEXTURE);
		sprites[TEXTURE_TYPE_ARMOR_BODY].resize(MAX_ARMOR_BODY_TEXTURE);
		sprites[TEXTURE_TYPE_ARMOR_LEGS].resize(MAX_ARMOR_LEGS_TEXTURE);
		sprites[TEXTURE_TYPE_FREED].resize(MAX_FREED_TEXTURE);
		sprites[TEXTURE_TYPE_TILE].resize(MAX_TILE_TEXTURE);
	}
	static GraphicsHandle *instance;
	std::vector<std::vector<SDL_Texture*>> sprites;
};

