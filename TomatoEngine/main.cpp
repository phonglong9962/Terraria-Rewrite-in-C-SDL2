#pragma once

#include <Windows.h>
#include <chrono>

#include "Window.h"
#include "AssetsPool.h"

#undef main

double getTime()
{
	return (double) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv)
{
	// Hide console window
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	AssetsPool::get()->loadTextureData("textures_info.xml");
	Window::get()->init();

	double now, last = getTime();
	double delta = 0, second = 0;
	double FPS = 1000.0f / 60.0f;

	int count = 0;

	while (Window::get()->isRunning())
	{
		now = getTime();
		delta += now - last;
		second += now - last;

		//std::cout << delta << std::endl;
		if (delta >= FPS)
		{
			delta -= FPS;
			Window::get()->events();
			Window::get()->update();
			count++;
		}

		if (second >= 1000)
		{
			second -= 1000;
			if (count > 60)
			{
				delta -= FPS * (count - 60);
			}
			//std::cout << "FPS: " << count << std::endl;
			count = 0;
		}

		if (delta < FPS - 3)
		{
			SDL_Delay((Uint32) (FPS - delta - 3));
		}

		last = now;
	}

	Window::get()->clean();

	//system("pause");

	return 0;
}