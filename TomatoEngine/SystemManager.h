#pragma once

#include "Types.h"

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		auto system = std::make_shared<T>();
		systems.emplace(typeid(T).name(), system);
		return system;
	}

	template<typename T>
	void setSignature(Signature signature)
	{
		systemsSignature.emplace(typeid(T).name(), signature);
	}

	void entityDestroyed(Entity entity)
	{
		for (auto const& pair : systems)
		{
			pair.second->entities.erase(entity);
		}
	}

	void entitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : systems)
		{
			auto const& system = pair.second;
			auto const& systemSignature = systemsSignature[pair.first];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.insert(entity);
			}
			else
			{
				if (std::find(system->entities.begin(), system->entities.end(), entity) != system->entities.end())
				{
					system->entities.erase(entity);
				}
			}
		}
	}

	void updateAllSystem()
	{
		for (auto const& system : systems)
		{
			system.second->update();
		}
	}

private:
	std::unordered_map<const char*, Signature> systemsSignature;
	std::map<const char*, std::shared_ptr<System>> systems;
};