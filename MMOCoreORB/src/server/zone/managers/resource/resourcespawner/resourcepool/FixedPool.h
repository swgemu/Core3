/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file FixedPool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef FIXEDPOOL_H_
#define FIXEDPOOL_H_

#include "engine/engine.h"
#include "ResourcePool.h"

class ResourceSpawner;

/**
 * The FixedPool class represents the resource pool
 * containing the "Fixed" resources consisting of
 * Iron and the JTL resources.  It spawns random
 * resources based on the scripted entries.
 */
class FixedPool: public ResourcePool {
private:

public:
	/**
	 * Ctor
	 * \param spawner The pointer to the resource spawner object
	 */
	FixedPool(ResourceSpawner* spawner);

	/**
	 * Dtor
	 */
	~FixedPool();

	/**
	 * Initialized what the pool spawns, and what is excluded
	 * \param includes Comma delimited list of resources to include
	 * \param excludes Comma delimited list of resources to exclude
	 */
	void initialize(LuaObject includes, const String& excludes);

	String healthCheck();

	/**
	 * Print the current state of the Resource Pool
	 */
	void print();

private:

	/**
	 * Adds resource to this pool
	 * \param resourceSpawn Spawn object to add to the pool
	 */
	void addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot);

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

#endif /* FIXEDPOOL_H_ */
