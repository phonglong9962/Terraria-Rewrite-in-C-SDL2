#include "GraphicsHandle.h"

void GraphicsHandle::loadSprite(short type, short id, std::string filename)
{
	if (sprites[type][id] == NULL)
	{
		SDL_Surface *surface = IMG_Load(filename.c_str());
		sprites[type][id] = SDL_CreateTextureFromSurface(Window::get()->getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
}

void GraphicsHandle::cleanSprite(short type, short id)
{
	if (sprites[type][id] != NULL)
	{
		SDL_DestroyTexture(sprites.at(type).at(id));
		sprites[type][id] = NULL;
	}
}

void GraphicsHandle::showSprite(short type, short id, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Window::get()->getRenderer(), sprites.at(type).at(id), NULL, NULL, 0, NULL, flip);
}

void GraphicsHandle::showSprite(short type, short id, Vector2<float> position, Vector2<int> size, SDL_RendererFlip flip)
{
	SDL_Rect pos = { int(position.x), int(position.y), int(size.x * Window::get()->scaling), int(size.y * Window::get()->scaling) };
	SDL_RenderCopyEx(Window::get()->getRenderer(), sprites.at(type).at(id), NULL, &pos, 0, NULL, flip);
}

void GraphicsHandle::showSprite(short type, short id, Vector2<float> position, Vector2<int> size, Vector2<int> index, SDL_RendererFlip flip)
{
	auto scale = Window::get()->scaling;
	SDL_Rect indexing = { int(index.x * size.x) + int(2 * index.x), int(index.y * size.y) + int(2 * index.y), int(size.x), int(size.y) };
	SDL_FRect pos = { (position.x * scale - (int)Camera::get()->position.x) + (size.x - (size.x * scale)) / 2.0f,
		(position.y * scale - (int)Camera::get()->position.y) + (size.y - (size.y * scale)) / 4.0f,
		size.x * scale, size.y * scale };
	SDL_RenderCopyExF(Window::get()->getRenderer(), sprites.at(type).at(id), &indexing, &pos, 0, NULL, flip);
}