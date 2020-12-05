#pragma once

#include "Types.h"

class IComponentData
{
public:
	virtual ~IComponentData() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentData : public IComponentData
{
public:
	ComponentData()
	{
		mEntityToIndexMap.resize(MAX_ENTITIES);
		mIndexToEntityMap.resize(MAX_ENTITIES);
	}

	void insertData(Entity entity, T component)
	{
		Entity newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		componentData[newIndex] = component;
		++mSize;
	}

	void removeData(Entity entity)
	{
		Entity indexOfRemovedEntity = mEntityToIndexMap.at(entity);
		Entity indexOfLastElement = mSize - 1;
		componentData[indexOfRemovedEntity] = componentData[indexOfLastElement];

		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap[entity] = 0;
		mIndexToEntityMap[entity] = indexOfLastElement;

		--mSize;
	}

	T& getData(Entity entity)
	{
		return componentData.at(mEntityToIndexMap.at(entity));
	}

	void entityDestroyed(Entity entity) override
	{
		if (std::find(mEntityToIndexMap.begin(), mEntityToIndexMap.end(), entity) != mEntityToIndexMap.end())
		{
			removeData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> componentData;
	std::vector<Entity> mEntityToIndexMap;
	std::vector<Entity> mIndexToEntityMap;
	Entity mSize = 0;
};;