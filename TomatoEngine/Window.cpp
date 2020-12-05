#include "Window.h"

Window *Window::instance = nullptr;
GraphicsHandle *GraphicsHandle::instance = nullptr;
KeyInput *KeyInput::instance = nullptr;
MouseInput *MouseInput::instance = nullptr;

bool Window::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL has failed to initialize!");
		return false;
	}

	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		SDL_Log("Failed to create window!");
		return false;
	}
	SDL_GetCurrentDisplayMode(0, &fsmode);
	SDL_SetWindowDisplayMode(window, &fsmode);

	w = SDL_GetWindowSurface(window)->w;
	h = SDL_GetWindowSurface(window)->h;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer!");
		return false;
	}

	TTF_Init();

	Window::get()->setState(new MenuState());

	return running = true;
}

void Window::setState(State *state)
{
	currentState.push_back(state);
	currentState.back()->initInternal();
}

void Window::changeState(State *state)
{
	if (currentState.back()->id != state->id)
	{
		delete currentState.back();
		currentState.pop_back();
		currentState.push_back(state);
		currentState.back()->initInternal();
	}
}

void Window::clean()
{
	SDL_DestroyWindow(window);

	SDL_Quit();

	SDL_Log("SDL cleaned!");
}

void Window::events()
{
	MouseInput::get()->update();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
			return;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			// Update Current SDL_Window Size
			w = SDL_GetWindowSurface(window)->w;
			h = SDL_GetWindowSurface(window)->h;
		}
		KeyInput::get()->updateEvent(event);
		MouseInput::get()->updateEvent(event);
	}
}

void Window::update()
{
	if (MouseInput::get()->GetWheelY() < 0)
	{
		scaling = 0.8f;
	} 
	else if (MouseInput::get()->GetWheelY() > 0)
	{
		scaling = 1.0f;
	}
	if (MouseInput::get()->rightClick)
	{
		/*double mouseX = MouseInput::get()->GetCoordX() * 100.0 / SDL_GetWindowSurface(window)->w;
		double mouseY = MouseInput::get()->GetCoordY() * 100.0 / SDL_GetWindowSurface(window)->h;

		SDL_SetWindowFullscreen(window, fullscreen = !fullscreen);
		SDL_GetCurrentDisplayMode(0, &fsmode);
		SDL_SetWindowDisplayMode(window, &fsmode);

		mouseX = mouseX * SDL_GetWindowSurface(window)->w / 100.0;
		mouseY = mouseY * SDL_GetWindowSurface(window)->h / 100.0;

		SDL_WarpMouseInWindow(window, (int)mouseX, (int)mouseY);*/

		// Get Window-Desktop Resulotion
		RECT desktop;
		HWND hd = GetDesktopWindow();
		GetWindowRect(hd, &desktop);
		
		// Get SDL_Window Position
		int offsetX, offsetY;
		SDL_GetWindowPosition(window, &offsetX, &offsetY);
		
		// Get Mouse Position In SDL_Window
		int mouseX = MouseInput::get()->GetCoordX() + offsetX;
		int mouseY = MouseInput::get()->GetCoordY() + offsetY;

		// Change SDL_Window Display
		SDL_SetWindowFullscreen(window, fullscreen = !fullscreen);
		SDL_GetCurrentDisplayMode(0, &fsmode);
		SDL_SetWindowDisplayMode(window, &fsmode);

		// Update Current SDL_Window Size
		w = SDL_GetWindowSurface(window)->w;
		h = SDL_GetWindowSurface(window)->h;

		// Re Get SDL_Window Position
		SDL_GetWindowPosition(window, &offsetX, &offsetY);

		// Re Get Mouse Position In SDL_Window
		mouseX = mouseX - offsetX;
		mouseY = mouseY - offsetY;

		// Update Mouse Position
		SDL_WarpMouseInWindow(window, mouseX, mouseY);
	}
	SDL_RenderClear(renderer);
	currentState.back()->updateInternal();
	SDL_RenderPresent(renderer);
}