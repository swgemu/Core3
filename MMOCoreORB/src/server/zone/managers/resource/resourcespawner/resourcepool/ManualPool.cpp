/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ManualPool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ManualPool.h"
#include "../ResourceSpawner.h"

ManualPool::ManualPool(ResourceSpawner* spawner) : ResourcePool(spawner) {
	setLoggingName("ManualPool");
}

ManualPool::~ManualPool() {

}

void ManualPool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot) {
	includedResources.put("any", resourceSpawn);
	resourceSpawn->setSpawnPool(ResourcePool::MANUALPOOL, "any");
}

bool ManualPool::update() {
	/**
	 * The manual pool doesn't spawn anything on it's own
	 * it just removes anything that happens to be expired
	 */

	StringBuffer buffer;
	buffer << "ManualPool updating: ";
	int despawnedCount = 0;

	for (int i = 0; i < includedResources.size(); ++i) {

		ManagedReference<ResourceSpawn* > spawn = includedResources.get(i);

		if (!spawn->inShift()) {

			includedResources.drop(includedResources.elementAt(i).getKey());
			i--;
			resourceSpawner->despawn(spawn);
			despawnedCount++;
		}
	}

	buffer << "Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);

	return true;
}

String ManualPool::healthCheck() {

	StringBuffer buffer;
	buffer << "****** ManualPool " << "(" <<  includedResources.size() << ") ************" << endl;
	for(int i = 0; i < includedResources.size(); ++i) {
		String resourceType = includedResources.elementAt(i).getKey();
		ManagedReference<ResourceSpawn* > spawn = includedResources.elementAt(i).getValue();

		if (spawn != NULL) {
			buffer << "   " << i << ". " << resourceType << " : "
					<< "Pass ("
					<< spawn->getType() << endl;
		} else {
			buffer << "   " << i << ". " << resourceType << " : " << ("Fail")
					<< " ()" << endl;
		}
	}
	buffer << "***************************************" << endl;

	return buffer.toString();
}

void ManualPool::print() {
	info("**** ManualPool ****", true);

	for (int i = 0; i < includedResources.size(); ++i) {
		ManagedReference<ResourceSpawn* > spawn = includedResources.get(i);

		StringBuffer msg;

		if (spawn != NULL)
			msg << spawn->getName() << " : " << spawn->getType();
		else
			msg << "EMPTY";

		info(msg.toString(), true);
	}

	info("**********************", true);
}
