/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file MinimumPool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "MinimumPool.h"
#include "server/zone/managers/resource/resourcespawner/ResourceSpawner.h"

MinimumPool::MinimumPool(ResourceSpawner* spawner) : ResourcePool(spawner) {
	setLoggingName("MinimumPool");
}

MinimumPool::~MinimumPool() {

}

void MinimumPool::initialize(LuaObject includes, const String& excludes) {
	ResourcePool::initializeByTable(includes, excludes);
}

void MinimumPool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot) {

	if(poolSlot.isEmpty()) {
		resourceSpawn->setSpawnPool(ResourcePool::NOPOOL, "");
		return;
	}

	int index = -1;

	for(int i = 0; i < includedResources.size(); ++i) {
		String resourceType = includedResources.elementAt(i).getKey();
		ManagedReference<ResourceSpawn* > spawn = includedResources.elementAt(i).getValue();

		if(resourceType == poolSlot && spawn == NULL) {
			index = i;
			break;
		}
	}

	if(index >= 0) {
		VectorMapEntry<String, ManagedReference<ResourceSpawn*> > newEntry(poolSlot, resourceSpawn);
		includedResources.setElementAt(index, newEntry);
	} else {
		resourceSpawn->setSpawnPool(ResourcePool::NOPOOL, "");
	}
}

bool MinimumPool::update() {

	int despawnedCount = 0, spawnedCount = 0;

	StringBuffer buffer;
	buffer << "MinimumPool updating: ";

	/**
	 * We remove any resources that have despawned from the
	 * pool.
	 */
	for(int i = 0; i < includedResources.size(); ++i) {

		String resourceType = includedResources.elementAt(i).getKey();
		ManagedReference<ResourceSpawn* > spawn = includedResources.elementAt(i).getValue();

		if (spawn == NULL || !spawn->inShift()) {

			ManagedReference<ResourceSpawn* > newSpawn = NULL;

			if(spawn != NULL) {
				resourceSpawner->despawn(spawn);
				despawnedCount++;
				newSpawn = resourceSpawner->getFromRandomPool(spawn->getType());
				//buffer << "Removing: " << spawn->getName() << " : " << spawn->getType();
			}

			if(newSpawn == NULL)
				newSpawn = resourceSpawner->createResourceSpawn(resourceType, excludedResources);

			if(newSpawn != NULL) {
				Locker locker(newSpawn);
				newSpawn->setSpawnPool(ResourcePool::MINIMUMPOOL, resourceType);
				spawnedCount++;

				//buffer << " and replacing with " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

				VectorMapEntry<String, ManagedReference<ResourceSpawn*> > newEntry(resourceType, newSpawn);
				includedResources.setElementAt(i, newEntry);
			} else {
				warning("Couldn't spawn resource type in MinumumPool: " + resourceType);
			}
		}
	}


	buffer << "Spawned " << spawnedCount << " Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);
	return true;
}

String MinimumPool::healthCheck() {

	StringBuffer buffer;
	buffer << "****** Minimum Pool " << "(" <<  includedResources.size() << ") ************" << endl;

	bool heathly = true;

	for(int i = 0; i < includedResources.size(); ++i) {
		String resourceType = includedResources.elementAt(i).getKey();
		ManagedReference<ResourceSpawn* > spawn = includedResources.elementAt(i).getValue();

		bool pass = spawn->isType(resourceType);
		if(!pass)
			heathly = false;

		if (spawn != NULL) {
			buffer << "   " << i << ". " << resourceType << " : "
					<< (pass ? "Pass" : "Fail") << "  " << spawn->getName()
					<< " Zones: " << String::valueOf(spawn->getSpawnMapSize())
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

void MinimumPool::print() {

	info("**** Minimum Pool ****");
	ResourcePool::print();
	info("**********************");
}
