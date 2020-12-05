#pragma once

#include "SystemManager.h"
#include "ComponentManager.h"
#include "EntityManager.h"

class Distributor
{
public:
	static Distributor *get() { return instance = (instance == nullptr ? new Distributor() : instance); }

	void init()
	{
		// Create pointers to each manager
		mComponentManager = std::make_shared<ComponentManager>();
		mEntityManager = std::make_shared<EntityManager>();
		mSystemManager = std::make_shared<SystemManager>();
	}


	// Entity methods
	Entity createEntity()
	{
		return mEntityManager->createEntity();
	}

	void destroyEntity(Entity entity)
	{
		mEntityManager->destroyEntity(entity);

		mComponentManager->entityDestroyed(entity);

		mSystemManager->entityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void registerComponent()
	{
		mComponentManager->registerComponent<T>();
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		mComponentManager->addComponent<T>(entity, component);

		auto signature = mEntityManager->getSignature(entity);
		signature.set(mComponentManager->getComponentType<T>(), true);
		mEntityManager->setSignature(entity, signature);
	}

	template<typename T>
	void addComponentAndUpdateSignature(Entity entity, T component)
	{
		mComponentManager->addComponent<T>(entity, component);

		auto signature = mEntityManager->getSignature(entity);
		signature.set(mComponentManager->getComponentType<T>(), true);
		mEntityManager->setSignature(entity, signature);

		mSystemManager->entitySignatureChanged(entity, signature);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		mComponentManager->removeComponent<T>(entity);

		auto signature = mEntityManager->getSignature(entity);
		signature.set(mComponentManager->getComponentType<T>(), false);
		mEntityManager->setSignature(entity, signature);
	}

	template<typename T>
	void removeComponentAndUpdateSignature(Entity entity)
	{
		mComponentManager->removeComponent<T>(entity);

		auto signature = mEntityManager->getSignature(entity);
		signature.set(mComponentManager->getComponentType<T>(), false);
		mEntityManager->setSignature(entity, signature);

		mSystemManager->entitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return mComponentManager->getComponent<T>(entity);
	}

	template<typename T>
	ComponentType getComponentType()
	{
		return mComponentManager->getComponentType<T>();
	}

	void refreshEntityInAllSystem(Entity entity)
	{
		mSystemManager->entitySignatureChanged(entity, mEntityManager->getSignature(entity));
	}

	// System methods
	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		return mSystemManager->registerSystem<T>();
	}

	template<typename T>
	void setSystemSignature(Signature signature)
	{
		mSystemManager->setSignature<T>(signature);
	}

	void updateAllSystem()
	{
		mSystemManager->updateAllSystem();
	}

private:
	static Distributor *instance;

	std::shared_ptr<ComponentManager> mComponentManager;
	std::shared_ptr<EntityManager> mEntityManager;
	std::shared_ptr<SystemManager> mSystemManager;
};