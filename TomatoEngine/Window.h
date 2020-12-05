#pragma once

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#include "SDL.h"
#include "State.h"
#include "LoadingState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "Defs.h"
#include "SDL_ttf.h"

#include <iostream>
#include <vector>
#include <Windows.h>

class Window
{
public:
	float scaling = 1.0f;
	bool doneLoading = false;

public:
	static Window *get() { return instance = (instance == nullptr ? new Window(): instance); }

	bool init();

	void clean();

	void events();

	void update();

	void changeState(State*);

	void setState(State*);

	inline bool isRunning() { return running; }
	inline bool setRunning(bool run) { running = run; }
	SDL_Renderer *getRenderer() { return renderer; }
	SDL_Window *getWindow() { return window; }
	int getWindowWidth() { return w; }
	int getWindowHeight() { return h; }

private:
	Window(){}
	static Window *instance;
	bool running = false;
	bool fullscreen;
	int w, h;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	std::vector<State*> currentState;
	SDL_DisplayMode fsmode;
};

