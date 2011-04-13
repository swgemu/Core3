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
 * \file MinimumPool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef MINIMUMPOOL_H_
#define MINIMUMPOOL_H_

#include "engine/engine.h"
#include "ResourcePool.h"

class ResourceSpawner;

/**
 * The Minimum pool represents a fixed size pool
 * that spawns exactly the items included in the
 * scripts.
 */
class MinimumPool : public ResourcePool {

public:
	/**
	 * Ctor
	 * \param spawner The pointer to the resource spawner object
	 */
	MinimumPool(ResourceSpawner* spawner);

	/**
	 * Dtor
	 */
	~MinimumPool();

	/**
	 * Initialized what the pool spawns, and what is excluded
	 * \param includes Comma delimited list of resources to include
	 * \param excludes Comma delimited list of resources to exclude
	 */
	void initialize(const String& includes, const String& excludes);

	/**
	 * Print the current state of the Resource Pool
	 */
	void print();

private:

	/**
	 * Adds resource to this pool
	 * \param resourceSpawn Spawn object to add to the pool
	 */
	void addResource(ManagedReference<ResourceSpawn*> resourceSpawn);

	/**
	 * The update function checks the ResourceSpawn items
	 * in spawnedResources to see if they have expired.
	 * If they have not expired, no action is taken, but if
	 * they have expired, we replace them according to the
	 * rules.
	 * \return if update was successful
	 */
	bool update();


	friend class ResourceSpawner;
};

#endif /* MINIMUMPOOL_H_ */
