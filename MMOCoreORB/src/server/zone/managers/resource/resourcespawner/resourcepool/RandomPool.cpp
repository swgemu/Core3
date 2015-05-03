/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file RandomPool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "RandomPool.h"
#include "../ResourceSpawner.h"

RandomPool::RandomPool(ResourceSpawner* spawner) : ResourcePool(spawner) {
	setLoggingName("RandomPool");
}

RandomPool::~RandomPool() {

}

void RandomPool::initialize(LuaObject includes, const String& excludes, int size) {
	ResourcePool::initializeByTable(includes, excludes);

	for(int i = 0; i < size; ++i)
		pool.add(NULL);
}

void RandomPool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot) {

	bool hasRoom = false;

	for (int i = 0; i < pool.size(); ++i) {

		ManagedReference<ResourceSpawn* > spawninpool = pool.get(i);

		if(spawninpool == NULL) {
			pool.setElementAt(i, resourceSpawn);
			hasRoom = true;
			break;
		}
	}

	if(!hasRoom)
		resourceSpawn->setSpawnPool(ResourcePool::NOPOOL, "");
}

bool RandomPool::update() {
	/**
	 * Create resources for any included type that doesn't exist in
	 * the VectorMap
	 */

	int despawnedCount = 0, spawnedCount = 0;

	StringBuffer buffer;
	buffer << "RandomPool updating: ";

	for(int i = 0; i < pool.size(); ++i) {

		ManagedReference<ResourceSpawn* > resourceSpawn = pool.get(i);

		if (resourceSpawn == NULL || !resourceSpawn->inShift()) {

			if(resourceSpawn != NULL) {
				resourceSpawner->despawn(resourceSpawn);
				despawnedCount++;
				//buffer << "Removing: " << spawn->getName() << " : " << spawn->getType();
			}

			String resourceType = includedResources.elementAt(System::random(includedResources.size() - 1)).getKey();
			ManagedReference<ResourceSpawn* > newSpawn = resourceSpawner->createResourceSpawn(resourceType, excludedResources);
			if(newSpawn != NULL) {
				Locker locker(newSpawn);
				newSpawn->setSpawnPool(ResourcePool::RANDOMPOOL, "");
				spawnedCount++;

				//buffer << " and replacing with " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

				pool.setElementAt(i, newSpawn);
			} else {
				warning("Couldn't spawn resource type in RandomPool: " + resourceType);
			}
		}
	}

	buffer << "Spawned " << spawnedCount << " Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);
	return true;
}

ResourceSpawn* RandomPool::removeSpawn(const String& type) {
	ManagedReference<ResourceSpawn* > spawn = NULL;

	for(int i = 0; i < pool.size(); ++i) {
		spawn = pool.get(i);
		if(spawn != NULL && spawn->isType(type)) {
			pool.setElementAt(i, NULL);
			return spawn;
		}
	}
	return NULL;
}

String RandomPool::healthCheck() {

	StringBuffer buffer;
	buffer << "****** RandomPool " << "(" <<  includedResources.size() << ") ************" << endl;

	bool heathly = true;

	for(int i = 0; i < pool.size(); ++i) {
		ManagedReference<ResourceSpawn* > spawn = pool.get(i);
		String resourceType = "";

		bool isRightType = false;

		if(spawn != NULL) {
			resourceType = spawn->getType();

			for(int j = 0; j < includedResources.size(); ++j) {
				String included = includedResources.elementAt(j).getKey();
				if(spawn->isType(included)) {
					isRightType = true;
					break;
				}
			}
		}

		if(!isRightType)
			heathly = false;

		if (spawn != NULL) {
			buffer << "   " << i << ". " << resourceType << " : "
					<< (isRightType ? "Pass" : "Fail")
					<< "  " << spawn->getName() << " Zones: " << String::valueOf(spawn->getSpawnMapSize())
					<< " (" << spawn->getType() << ")" << endl;
			if(spawn->getSpawnMapSize() == 0)
				heathly = false;
		} else {
			buffer << "   " << i << ". " << resourceType << " : " << ("Fail")
					<< " ()" << endl;
			heathly = false;
		}

	}
	buffer << "***********" << (heathly ? "HEALTHY!" : "ERRORS!") << "*****************" << endl;

	return buffer.toString();
}

void RandomPool::print() {
	info("**** RandomPool ****", true);

	for (int i = 0; i < pool.size(); ++i) {
		ManagedReference<ResourceSpawn* > spawn = pool.get(i);

		StringBuffer msg;

		if (spawn != NULL)
			msg << spawn->getName() << " : " << spawn->getType();
		else
			msg << "EMPTY";

		info(msg.toString(), true);
	}

	info("**********************", true);
}
