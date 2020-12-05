#include "MenuState.h"

MenuState::MenuState()
{
	id = 0;
}

void MenuState::init()
{
	srand(static_cast<unsigned int>(time(NULL)));
	int rand = std::rand() % 3;
	std::string filename;
	switch (rand)
	{
	case 0:
		filename = "assets/SplashScreens/Splash_1.png";
		break;
	case 1:
		filename = "assets/SplashScreens/Splash_6_0.png";
		break;
	case 2:
		filename = "assets/SplashScreens/Splash_8_0.png";
		break;
	default:break;
	}
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE, filename);
}

void MenuState::initInternal()
{
	std::cout << "MenuState Initializing!" << std::endl;
	SDL_SetRenderDrawColor(Window::get()->getRenderer(), 255, 255, 255, 255);
	init();
}

void MenuState::update()
{
	GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);
	if (MouseInput::get()->leftClick)
	{
		GraphicsHandle::get()->cleanSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);
		Window::get()->changeState(new LoadingState(0));
	} 
	else if (KeyInput::get()->keyUp)
	{
		GraphicsHandle::get()->cleanSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);
		Window::get()->changeState(new LoadingState(1));
	}
}

void MenuState::updateInternal()
{
	update();
}