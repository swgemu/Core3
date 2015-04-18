/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourcePool.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCEPOOL_H_
#define RESOURCEPOOL_H_

#include "engine/engine.h"
#include "server/zone/objects/resource/ResourceSpawn.h"

class ResourceSpawner;

/**
 * Abstract parent of all ResourcePool objects
 */
class ResourcePool : public Logger {

protected:

	/**
	 * List of resources this pool can spawn
	 */
	VectorMap<String, ManagedReference<ResourceSpawn* > > includedResources;

	/**
	 * List of resources this pool can't spawn
	 */
	Vector<String> excludedResources;

	/**
	 * resourceSpawner is a pointer to the ResourceSpawner object defined in ResourceManager.
	 */
	ResourceSpawner* resourceSpawner;

public:

	enum {
		NOPOOL,
		MINIMUMPOOL,
		RANDOMPOOL,
		FIXEDPOOL,
		NATIVEPOOL,
		MANUALPOOL
	};

public:
	  /** Constructor
	   * \param spawner pointer to the ResourceSpawner object defined in ResourceManager
	   */
	ResourcePool(ResourceSpawner* spawner) : Logger("ResourcePool") {
		resourceSpawner = spawner;
		includedResources.setNullValue(NULL);
		includedResources.setAllowDuplicateInsertPlan();
		setGlobalLogging(true);
		setLogging(true);
	}
	/**
	 * Deconstructor
	 */
	virtual ~ResourcePool() {
		resourceSpawner = NULL;
		includedResources.removeAll();
		excludedResources.removeAll();
	}

	/**
	 * Initialize pool to contain needed resources
	 */
	void initialize(const String& includes, const String& excludes) {
		StringTokenizer includeTokens(includes);
		includeTokens.setDelimeter(",");

		String token;
		while (includeTokens.hasMoreTokens()) {
			includeTokens.getStringToken(token);
			includedResources.put(token, NULL);
		}

		StringTokenizer excludeTokens(excludes);
		excludeTokens.setDelimeter(",");

		while (excludeTokens.hasMoreTokens()) {
			excludeTokens.getStringToken(token);
			excludedResources.add(token);
		}
	}

	//Initialize pool using a table of resource names and a number of occurrences
	void initializeByTable(LuaObject includes, const String& excludes) {
		if (!includes.isValidTable()) {
			info("Error initializing resources, not a valid table.", true);
			return;
		}

		for (int i = 1; i <= includes.getTableSize(); i++) {
			LuaObject resourceNameAndNumber = includes.getObjectAt(i);

			if (resourceNameAndNumber.isValidTable()) {
				String name = includes.getStringAt(1);
				int number = includes.getIntAt(2);

				for (unsigned int j = 1; j <= number; j++) {
					includedResources.put(name, NULL);
				}
			}

			resourceNameAndNumber.pop();
		}

		String token;
		StringTokenizer excludeTokens(excludes);
		excludeTokens.setDelimeter(",");

		while (excludeTokens.hasMoreTokens()) {
			excludeTokens.getStringToken(token);
			excludedResources.add(token);
		}
	}

	void print() {

		for(int i = 0; i < includedResources.size(); ++i) {

			ManagedReference<ResourceSpawn* > spawn = includedResources.elementAt(i).getValue();

			StringBuffer msg;

			if (spawn != NULL) {
				msg << spawn->getName() << " : " << spawn->getType() << endl;
			} else {
				msg << "EMPTY : " << includedResources.elementAt(i).getKey() << endl;
			}

			info(msg.toString());
		}
	}

private:
	/**
	 * Remove expired resources and spawn replacements.
	 * \return Whether update completed successfully
	 */
	virtual bool update() = 0;


	/**
	 * Get the position of incoming resource type
	 * This function should only be used when loading
	 * from database.
	 * \param resourceSpawn The resource to add to this pool
	 */
	virtual void addResource(ManagedReference<ResourceSpawn*> resourceSpawn, const String& poolSlot) = 0;

	virtual String healthCheck() = 0;

	friend class ResourceSpawner;
};

#endif /* RESOURCEPOOL_H_ */
