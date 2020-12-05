#pragma once

#include "Types.h"
#include "ComponentData.h"

class ComponentManager
{
public:
	ComponentManager()
	{
		componentData.resize(MAX_COMPONENTS);
	}

	template<typename T>
	void registerComponent()
	{
		componentTypes.emplace(typeid(T).name(), currentComponentType);
		componentData[currentComponentType] = std::make_shared<ComponentData<T>>();

		++currentComponentType;
	}

	template<typename T>
	ComponentType getComponentType()
	{
		return componentTypes.at(typeid(T).name());
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		GetComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return GetComponentArray<T>()->getData(entity);
	}

	void entityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : componentData)
		{
			pair->entityDestroyed(entity);
		}
	}

private:
	std::map<const char*, ComponentType> componentTypes;
	std::vector<std::shared_ptr<IComponentData>> componentData;
	ComponentType currentComponentType = 0;

	template<typename T>
	ComponentData<T>* GetComponentArray()
	{
		return static_cast<ComponentData<T>*>(componentData.at(componentTypes.at(typeid(T).name())).get());
	}
};