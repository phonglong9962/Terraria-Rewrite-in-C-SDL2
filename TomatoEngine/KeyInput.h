#pragma once

#include "SDL.h"

class KeyInput
{
public:
	bool keyLeft, keyRight, keyUp, keyDown, keyJump;

public:
	static KeyInput *get() { return instance = (instance != nullptr ? instance : new KeyInput()); }

	void updateEvent(SDL_Event e)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				keyUp = true;
				break;
			case SDLK_s:
				keyDown = true;
				break;
			case SDLK_a:
				keyLeft = true;
				break;
			case SDLK_d:
				keyRight = true;
				break;
			case SDLK_SPACE:
				keyJump = true;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				keyUp = false;
				break;
			case SDLK_s:
				keyDown = false;
				break;
			case SDLK_a:
				keyLeft = false;
				break;
			case SDLK_d:
				keyRight = false;
				break;
			case SDLK_SPACE:
				keyJump = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
private:
	KeyInput() 
	{
		keyLeft = false;
		keyRight = false;
		keyUp = false;
		keyDown = false;
		keyJump = false;
	}
	static KeyInput *instance;
};