#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>

#include "TextureDetails.h"
#include "SDL.h"
#include "pugixml.hpp"
#include "Defs.h"

class AssetsPool
{
public:
	static AssetsPool *get() { return instance = (instance == nullptr ? new AssetsPool() : instance); }
	void loadTextureData(std::string);
	TextureDetails getTextureDetails(int index) { return textureDetails.at(index); }

private:
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	static AssetsPool *instance;
	std::array<TextureDetails, MAX_NPC_TEXTURE> textureDetails;
};

