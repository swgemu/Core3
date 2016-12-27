/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file NativePool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "NativePool.h"
#include "server/zone/managers/resource/resourcespawner/ResourceSpawner.h"

NativePool::NativePool(ResourceSpawner* spawner) : ResourcePool(spawner) {
	setLoggingName("NativePool");
}

NativePool::~NativePool() {
	spawnsPerZone.removeAll();
}

void NativePool::initialize(const String& includes, const String& excludes) {

	ResourcePool::initialize(includes, excludes);

	for(int i = 0; i < activeResourceZones.size(); ++i) {
		addZoneMap(activeResourceZones.get(i));
	}

}

void NativePool::addZone(const String& zoneName) {

	activeResourceZones.add(zoneName);

	if(includedResources.size() != 0) {
		addZoneMap(zoneName);
	}
}

void NativePool::addZoneMap(const String& zoneName) {
	VectorMap<String, ManagedReference<ResourceSpawn*> > spawnZone;

	for(int j = 0; j < includedResources.size(); ++j) {
		String resource = includedResources.elementAt(j).getKey() + "_" + zoneName;
		spawnZone.put(resource, NULL);
	}

	spawnsPerZone.put(zoneName, spawnZone);
}

void NativePool::removeZone(const String& zoneName) {
	activeResourceZones.removeElement(zoneName);
	spawnsPerZone.drop(zoneName);
}

void NativePool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot) {

	String planet = resourceSpawn->getZoneRestriction();
	VectorMap<String, ManagedReference<ResourceSpawn*> >* spawnZone = &spawnsPerZone.get(planet);

	if(poolSlot.isEmpty()) {
		resourceSpawn->setSpawnPool(ResourcePool::NOPOOL, "");
		return;
	}

	int index = spawnZone->find(poolSlot);
	if(index >= 0) {
		VectorMapEntry<String, ManagedReference<ResourceSpawn*> > newEntry(poolSlot, resourceSpawn);
		spawnZone->setElementAt(index, newEntry);
	} else {
		resourceSpawn->setSpawnPool(ResourcePool::NOPOOL, "");
	}

}

bool NativePool::update() {

	int despawnedCount = 0, spawnedCount = 0;
	StringBuffer buffer;
	buffer << "NativePool updating: ";

	for(int i = 0; i < spawnsPerZone.size(); ++i) {
		VectorMap<String, ManagedReference<ResourceSpawn*> >* spawnZone = &spawnsPerZone.get(i);

		for(int j = 0; j < spawnZone->size(); ++j) {

			String resourceType = spawnZone->elementAt(j).getKey();
			ManagedReference<ResourceSpawn* > spawn = spawnZone->elementAt(j).getValue();

			if (spawn == NULL || !spawn->inShift()) {

				if(spawn != NULL) {
					resourceSpawner->despawn(spawn);
					despawnedCount++;
					//buffer << "Removing: " << spawn->getName() << " : " << spawn->getType();
				}

				ManagedReference<ResourceSpawn* > newSpawn = resourceSpawner->createResourceSpawn(resourceType, excludedResources);
				if(newSpawn != NULL) {
					Locker locker(newSpawn);
					newSpawn->setSpawnPool(ResourcePool::NATIVEPOOL, resourceType);
					spawnedCount++;

					//buffer << " and replacing with " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

					VectorMapEntry<String, ManagedReference<ResourceSpawn*> > newEntry(resourceType, newSpawn);
					spawnZone->setElementAt(j, newEntry);
				} else {
					warning("Couldn't spawn resource type in NativePool: " + resourceType);
				}
			}
		}
	}

	buffer << "Spawned " << spawnedCount << " Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);
	return true;
}

String NativePool::healthCheck() {

	StringBuffer buffer;
	buffer << "****** Native Pool Zones " << "(" <<  spawnsPerZone.size() << ") ************" << endl;

	bool heathly = true;

	for(int i = 0; i < spawnsPerZone.size(); ++i) {
		VectorMap<String, ManagedReference<ResourceSpawn*> > spawnZone = spawnsPerZone.get(i);

		buffer << spawnsPerZone.elementAt(i).getKey() << endl;

		for(int i = 0; i < spawnZone.size(); ++i) {
			String resourceType = spawnZone.elementAt(i).getKey();
			ManagedReference<ResourceSpawn* > spawn = spawnZone.elementAt(i).getValue();

			bool pass = spawn->isType(resourceType);
			if(!pass)
				heathly = false;

			if(spawn != NULL) {
				buffer << "   " << i << ". " << resourceType << " : "
					   << (pass ? "Pass" : "Fail") << "  " << spawn->getName()
					   << " Zones: " << String::valueOf(spawn->getSpawnMapSize())
					   << " (" << spawn->getType() << ")" << endl;
				if(spawn->getSpawnMapSize() == 0)
					heathly = false;
			} else {
				buffer << "   " << i << ". " << resourceType << " : "
					   << ("Fail")
					   << " ()" << endl;
				heathly = false;
			}
		}
	}
	buffer << "***********" << (heathly ? "HEALTHY!" : "ERRORS!") << "*****************" << endl;

	return buffer.toString();
}

void NativePool::print() {
	info("**** Native Pool ****", true);

	for (int i = 0; i < spawnsPerZone.size(); ++i) {

		VectorMap<String, ManagedReference<ResourceSpawn*> > spawnZone = spawnsPerZone.get(i);

		StringBuffer msg2;
		msg2 << "Zone " << spawnsPerZone.elementAt(i).getKey();
		info(msg2.toString(), true);

		for (int j = 0; j < spawnZone.size(); ++j) {

			ManagedReference<ResourceSpawn* > spawn = spawnZone.get(j);

			StringBuffer msg3;

			if (spawn != NULL)
				msg3 <<  spawn->getName() << " : "<< spawn->getType();
			else
				msg3 << "EMPTY";

			info(msg3.toString(), true);
		}
	}

	info("**********************", true);
}
