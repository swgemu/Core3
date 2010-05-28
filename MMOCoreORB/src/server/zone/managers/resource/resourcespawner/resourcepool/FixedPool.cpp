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
 * \file FixedPool.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "FixedPool.h"
#include "../ResourceSpawner.h"

FixedPool::FixedPool(ResourceSpawner* spawner) : ResourcePool(spawner) {
	setLoggingName("FixedPool");
}

FixedPool::~FixedPool() {

}

void FixedPool::initialize(const String& includes, const String& excludes) {
	ResourcePool::initialize(includes, excludes);

	/// We need to add a NULL item for each object the pool will fill
	for (int ii = 0; ii < includedResources.size(); ++ii)
		this->add(NULL);
}

void FixedPool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn) {

	for (int ii = 0; ii < includedResources.size(); ++ii) {

		ManagedReference<ResourceSpawn*> spawninpool = this->get(ii);

		if (resourceSpawn->isType(includedResources.get(ii)) && spawninpool == NULL) {
			this->setElementAt(ii, resourceSpawn);
			break;
		}
	}

}

bool FixedPool::update() {

	int despawnedCount = 0, spawnedCount = 0;

	StringBuffer buffer;
	buffer << "Fixed pool updating: ";

	for(int ii = 0; ii < size(); ++ii) {

		ManagedReference<ResourceSpawn* > resourceSpawn = get(ii);

		if(resourceSpawn == NULL) {
			ManagedReference<ResourceSpawn* > newSpawn =
					resourceSpawner->createResourceSpawn(includedResources.get(ii), excludedResources);

			if (newSpawn != NULL) {

				newSpawn->setSpawnPool(ResourcePool::FIXEDPOOL);
				newSpawn->updateToDatabase();
				spawnedCount++;

				setElementAt(ii, newSpawn);

				//buffer << "Added: " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

			} else
				resourceSpawner->info("Resource not valid for Fixed Pool: " + includedResources.get(ii));
		}
	}

	/**
	 * We remove any resources that have despawned from the
	 * pool
	 */
	for(int ii = 0; ii < size(); ++ii) {
		ManagedReference<ResourceSpawn* > spawn = get(ii);

		if (spawn != NULL && !spawn->inShift()) {

			//buffer << "Removing: " << spawn->getName() << " : " << spawn->getType();

			setElementAt(ii, NULL);
			spawn->setSpawnPool(ResourcePool::NOPOOL);
			spawn->updateToDatabase();
			despawnedCount++;

			ManagedReference<ResourceSpawn* > newSpawn = NULL;

			if(newSpawn == NULL)
				newSpawn = resourceSpawner->createResourceSpawn(includedResources.get(ii), excludedResources);

			newSpawn->setSpawnPool(ResourcePool::FIXEDPOOL);
			newSpawn->updateToDatabase();
			spawnedCount++;

			//buffer << " and replacing with " << newSpawn->getName() << " : " << newSpawn->getType() << endl;

			setElementAt(ii, newSpawn);
		}
	}
	buffer << "Spawned " << spawnedCount << " Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);
	return true;
}

void FixedPool::print() {

	info("**** Fixed Pool ****");
	ResourcePool::print();
	info("**********************");
}
