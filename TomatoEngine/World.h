#pragma once

#include <string>
#include <vector>
#include <array>

class World
{
public:
	bool packed = false;
	std::string name;
	short width, height;
	std::vector<std::vector<short>> tiles;
};

