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

void ManualPool::addResource(ManagedReference<ResourceSpawn*> resourceSpawn) {
	add(resourceSpawn);
	resourceSpawn->setSpawnPool(ResourcePool::MANUALPOOL);
}

bool ManualPool::update() {
	/**
	 * The manual pool doesn't spawn anything on it's own
	 * it just removes anything that happens to be expired
	 */

	StringBuffer buffer;
	buffer << "Manual pool updating: ";
	int despawnedCount = 0;

	for (int ii = 0; ii < size(); ++ii) {

		ManagedReference<ResourceSpawn* > spawn = get(ii);

		if (!spawn->inShift()) {

			removeElement(spawn);
			spawn->setSpawnPool(ResourcePool::NOPOOL);
			spawn->updateToDatabase();
			despawnedCount++;
		}
	}

	buffer << "Despawned " << despawnedCount;
	resourceSpawner->info(buffer.toString(), true);

	return true;
}

void ManualPool::print() {
	info("**** Manual Pool ****", true);

	for (int ii = 0; ii < this->size(); ++ii) {
		ManagedReference<ResourceSpawn* > spawn = this->get(ii);

		StringBuffer msg;

		if (spawn != NULL)
			msg << spawn->getName() << " : " << spawn->getType();
		else
			msg << "EMPTY";

		info(msg.toString(), true);
	}

	info("**********************", true);
}
