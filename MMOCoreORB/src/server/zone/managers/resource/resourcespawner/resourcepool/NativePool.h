/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file NativePool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef NATIVEPOOL_H_
#define NATIVEPOOL_H_

#include "engine/engine.h"
#include "ResourcePool.h"

class ResourceSpawner;

/**
 * The native pool class represents all of the
 * planet specific organic resources
 */
class NativePool : public ResourcePool {
private:

	/// Current zones with active resources
	Vector<String> activeResourceZones;

	VectorMap<String, VectorMap<String, ManagedReference<ResourceSpawn*> > > spawnsPerZone;

public:

	/**
	 * Ctor
	 * \param spawner The pointer to the resource spawner object
	 */
	NativePool(ResourceSpawner* spawner);

	/**
	 * Dtor
	 */
	~NativePool();

	/**
	 * Initialized what the pool spawns, and what is excluded
	 * \param includes Comma delimited list of resources to include
	 * \param excludes Comma delimited list of resources to exclude
	 */
	void initialize(const String& includes, const String& excludes);


	void addZone(const String& zoneName);

	void addZoneMap(const String& zoneName);

	void removeZone(const String& zoneName);

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

#endif /* NATIVEPOOL_H_ */
