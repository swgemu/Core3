/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file RandomPool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RANDOMPOOL_H_
#define RANDOMPOOL_H_

#include "ResourcePool.h"

class ResourceSpawner;

/**
 * The random pool consists of a pool of X size
 * the spawns anything in the included list.  Unlike
 * other pools that have a certain resource type
 * this pool is completely random
 */
class RandomPool : public ResourcePool {
private:

	/// SIze of pool (From script)
	Vector<ManagedReference<ResourceSpawn*> > pool;

public:
	/**
	 * Ctor
	 * \param spawner The pointer to the resource spawner object
	 */
	RandomPool(ResourceSpawner* spawner);

	/**
	 * Dtor
	 */
	~RandomPool();

	/**
	 * Initialized what the pool spawns, and what is excluded
	 * \param includes Comma delimited list of resources to include
	 * \param excludes Comma delimited list of resources to exclude
	 * \param size The size of the pool
	 */
	void initialize(LuaObject includes, const String& excludes, int size);

	/**
	 * The minimum pool likes to extract resource from
	 * the random pool before spawning new resources
	 * This function is only used in MinimumPool::update()
	 */
	ResourceSpawn* removeSpawn(const String& type);

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
	 */
	bool update();

	friend class ResourceSpawner;
};

#endif /* RANDOMPOOL_H_ */
