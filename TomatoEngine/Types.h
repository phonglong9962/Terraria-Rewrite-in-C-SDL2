#pragma once

#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <bitset>
#include <memory>
#include <vector>
#include <queue>
#include <array>
#include <map>

using Entity = std::uint16_t;
const Entity MAX_ENTITIES = 500;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class System
{
public:
	std::unordered_set<Entity> entities;
	virtual void update() = 0;
};