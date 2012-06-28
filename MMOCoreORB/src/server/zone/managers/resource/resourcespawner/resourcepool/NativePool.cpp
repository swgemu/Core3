/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

/**
 * \file NativePool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "NativePool.h"
#include "../ResourceSpawner.h"

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
					   << " (" << spawn->getType() << ")" << endl;
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
