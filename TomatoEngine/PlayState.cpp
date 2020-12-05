#include "PlayState.h"

PlayState::PlayState()
{
	id = 1;
}

void PlayState::init()
{
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE, "assets/SplashScreens/Splash_9_0.png");
}

void PlayState::initInternal()
{
	std::cout << "PlayState Initializing!" << std::endl;
	SDL_SetRenderDrawColor(Window::get()->getRenderer(), 0, 0, 0, 255);
	init();
}

void PlayState::update()
{
	GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);
	WorldHandle::get()->update();
	Distributor::get()->updateAllSystem();
}

void PlayState::updateInternal()
{
	update();
}