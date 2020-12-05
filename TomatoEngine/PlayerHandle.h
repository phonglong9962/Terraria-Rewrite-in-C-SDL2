#pragma once

#include <iostream>
#include <fstream>

#include "SDL.h"
#include "Character.h"

class PlayerHandle
{
public:
	static PlayerHandle *get() { return instance = (instance == nullptr ? new PlayerHandle() : instance); }

	void createPlayer(std::string, std::string);
	void loadPlayer(std::string);
	Character *getPlayer() { return playerInstance; }
private:
	PlayerHandle(){}
	static PlayerHandle *instance;
	Character *playerInstance;
};

