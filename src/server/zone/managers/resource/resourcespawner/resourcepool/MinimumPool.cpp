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

#include "MinimumPool.h"
#include "../ResourceSpawner.h"

MinimumPool::MinimumPool(ResourceSpawner* spawner, ResourceTree* tree) : ResourcePool(spawner, tree) {

}

MinimumPool::~MinimumPool() {

}

void MinimumPool::initialize(const String& includes, const String& excludes) {
	ResourcePool::initialize(includes, excludes);

}

bool MinimumPool::update() {
	/**
	 * Create resources for any included type that doesn't exist in
	 * the VectorMap
	 */
	for(int ii = 0; ii < includedResources.size(); ++ii) {
		String type = includedResources.get(ii);
		System::out << "Checking type " << type << endl;
		if(!spawnedResources.contains(type)) {
			ManagedReference<ResourceSpawn* > newSpawn = resourceSpawner->createResourceSpawn(type, excludedResources);
			spawnedResources.put(type, newSpawn);
			System::out << "Spawning " << type << endl;
		}
	}

	/**
	 * We remove any resources that have despawned from the
	 * pool
	 */
	for(int ii = 0; ii < spawnedResources.size(); ++ii) {
		ManagedReference<ResourceSpawn* > spawn = spawnedResources.get(ii);
		if(!spawn->inShift()) {
			String type = spawnedResources.elementAt(ii).getKey();
			spawnedResources.drop(type);
			ManagedReference<ResourceSpawn* > newSpawn;// =
					//resourceSpawner->getFromRandomPool(type);
			if(newSpawn != NULL) {
				spawnedResources.put(type, newSpawn);
				//newSpawn->setSpawnPool("minimum");
				continue;
			}
			newSpawn = resourceSpawner->createResourceSpawn(type, excludedResources);
			spawnedResources.put(type, newSpawn);
			newSpawn->print();
		}
	}
	return true;
}
