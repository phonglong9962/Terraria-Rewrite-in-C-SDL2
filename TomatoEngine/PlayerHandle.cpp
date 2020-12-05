#include "PlayerHandle.h"

PlayerHandle *PlayerHandle::instance = nullptr;

void PlayerHandle::createPlayer(std::string filename, std::string name)
{
	SDL_Log("Creating Player!");

	std::ofstream wf(filename, std::ios::out | std::ios::binary);
	if (!wf) {
		std::cout << "Cannot open file!" << std::endl;
		return;
	}

	Character player;

	player.name = reinterpret_cast<char*>(&name);

	wf.write(reinterpret_cast<char*>(&player), sizeof(Character));
	wf.close();
	if (!wf.good()) {
		std::cout << "Error occurred at writing time!" << std::endl;
		return;
	}

	SDL_Log("Done creating sample Player!");
}

void PlayerHandle::loadPlayer(std::string filename)
{
	std::ifstream rf(filename, std::ios::out | std::ios::binary);
	if (!rf) {
		std::cout << "Cannot open file!" << std::endl;
		return;
	}

	rf.read(reinterpret_cast<char*>(&playerInstance), sizeof(Character));
	rf.close();
	if (!rf.good()) {
		std::cout << "Error occurred at reading time!" << std::endl;
		return;
	}
}
