/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ManualPool.h
 * \author Kyle Burkhardt
 * \date 5-27-10
 */

#ifndef MANUALPOOL_H_
#define MANUALPOOL_H_

#include "engine/engine.h"
#include "ResourcePool.h"

class ResourceSpawner;

/**
 * The manual pool contains resources manually
 * spawned by admins.  The pool should almost
 * always be empty
 */
class ManualPool : public ResourcePool {
public:
	/**
	 * Ctor
	 * \param spawner The pointer to the resource spawner object
	 */
	ManualPool(ResourceSpawner* spawner);

	/**
	 * Dtor
	 */
	~ManualPool();

	/**
	 * Initialized what the pool spawns, and what is excluded
	 * \param includes Comma delimited list of resources to include
	 * \param excludes Comma delimited list of resources to exclude
	 */
	void initialize(const String& includes, const String& excludes, int size);

	/**
	 * Adds resource to this pool
	 * \param resourceSpawn Spawn object to add to the pool
	 */
	void addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot);


	String healthCheck();

	/**
	 * Print the current state of the Resource Pool
	 */
	void print();

private:

	/**
	 * The update function checks the ResourceSpawn items
	 * in spawnedResources to see if they have expired.
	 * If they have not expired, no action is taken, but if
	 * they have expired, we replace them according to the
	 * rules.
	 */
	bool update();


	friend class ResourceSpawner;
};

#endif /* MANUALPOOL_H_ */
