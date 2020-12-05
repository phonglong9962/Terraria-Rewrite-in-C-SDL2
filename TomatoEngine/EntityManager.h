#pragma once

#include "Types.h"

class EntityManager
{
public:
	EntityManager()
	{
		for (Entity i = 0; i < MAX_ENTITIES; ++i)
		{
			availableEntities.push(i);
		}
	}

	Entity createEntity()
	{
		Entity entity = availableEntities.front();
		availableEntities.pop();
		++currentLivingEntities;

		return entity;
	}

	void destroyEntity(Entity entity)
	{
		entitiesSignature[entity].reset();
		availableEntities.push(entity);
		--currentLivingEntities;
	}

	void setSignature(Entity entity, Signature signature)
	{
		entitiesSignature[entity] = signature;
	}

	Signature getSignature(Entity entity)
	{
		return entitiesSignature.at(entity);
	}

private:
	std::queue<Entity> availableEntities;
	std::array<Signature, MAX_ENTITIES> entitiesSignature;
	Entity currentLivingEntities = 0;
};