/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file MinimumPool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef MINIMUMPOOL_H_
#define MINIMUMPOOL_H_

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

#endif /* MINIMUMPOOL_H_ */
