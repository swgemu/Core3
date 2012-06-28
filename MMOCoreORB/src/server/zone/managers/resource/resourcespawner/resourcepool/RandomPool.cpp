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

void RandomPool::initialize(const String& includes, const String& excludes, int size) {
	ResourcePool::initialize(includes, excludes);

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
				newSpawn->setSpawnPool(ResourcePool::RANDOMPOOL, "");
				spawnedCount++;

				//buffer << " and replacing with " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

				pool.setElementAt(i, newSpawn);
			} else {
				warning("Couldn't spawn resource type in FixedPool: " + resourceType);
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
			spawn->setSpawnPool(ResourcePool::NOPOOL, "");
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
