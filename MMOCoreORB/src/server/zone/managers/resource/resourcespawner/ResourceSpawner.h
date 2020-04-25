/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceSpawner.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCESPAWNER_H_
#define RESOURCESPAWNER_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "resourcetree/ResourceTree.h"
#include "resourcemap/ResourceMap.h"

#include "resourcepool/MinimumPool.h"
#include "resourcepool/FixedPool.h"
#include "resourcepool/RandomPool.h"
#include "resourcepool/NativePool.h"
#include "resourcepool/ManualPool.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sui {
namespace listbox {
	class SuiListBox;
}
}
}
}
}
}

using namespace server::zone::objects::player::sui::listbox;

/**
 * The ResourceSpawner class represents all the functions related to ResourceSpawns
 * Including spawning, despawning rules,
 */
class ResourceSpawner : public Logger, public Object {
private:
	ManagedReference<ZoneServer* > server;
	ManagedReference<ZoneProcessServer*> processor;

	NameManager* nameManager;
	ObjectManager* objectManager;

	ResourceTree* resourceTree;
	ObjectDatabaseManager* databaseManager;

	ResourceMap* resourceMap;

	Vector<String> jtlResources;
	Vector<String> activeResourceZones;

	MinimumPool* minimumPool;
	FixedPool* fixedPool;
	RandomPool* randomPool;
	NativePool* nativePool;
	ManualPool* manualPool;

	bool scriptLoading;

	int shiftDuration, lowerGateOverride, maxSpawnAmount, spawnThrottling;

	int samplingMultiplier;

public:
	ResourceSpawner(ManagedReference<ZoneServer* > serv,
			ZoneProcessServer* impl);
	~ResourceSpawner();

	void init();

	void initializeMinimumPool(LuaObject includes, const String& excludes);
	void initializeFixedPool(LuaObject includes, const String& excludes);
	void initializeRandomPool(LuaObject includes, const String& excludes, const int size);
	void initializeNativePool(const String& includes, const String& excludes);

	void addZone(const String& zoneName);
	void removeZone(const String& zoneName);
	void addJtlResource(const String& resourceName);
	void setSpawningParameters(bool loadFromScript, const int dur, const int throt,
			const int override, const int spawnquantity);

	void spawnScriptResources();
	bool writeAllSpawnsToScript();

	void start();
	void shiftResources();

	ResourceSpawn* createResourceSpawn(const String& type, const String& zonerestriction = "");
	ResourceSpawn* createResourceSpawn(const String& type, const Vector<String>& excludes, const String& zonerestriction = "");
	ResourceSpawn* createResourceSpawn(const Vector<String>& includes, const Vector<String>& excludes = 0, const String& zonerestriction = "");

	void despawn(ResourceSpawn* spawn);

	ResourceSpawn* manualCreateResourceSpawn(CreatureObject* player, const UnicodeString& args);

	ResourceSpawn* createRecycledResourceSpawn(const ResourceTreeEntry* entry) const;

	ResourceSpawn* getRecycledVersion(const ResourceSpawn* resource) const;

	bool isRecycledResource(const ResourceSpawn* resource) const;

	int sendResourceRecycleType(const ResourceSpawn* resource) const;

	void sendResourceListForSurvey(CreatureObject* player, const int toolType, const String& surveyType) const;

	void sendSurvey(CreatureObject* player, const String& resname) const;
	void sendSample(CreatureObject* player, const String& resname, const String& sampleAnimation) const;
	void sendSampleResults(TransactionLog& trx, CreatureObject* player, const float density, const String& resname) const;

	Reference<ResourceContainer*> harvestResource(CreatureObject* player, const String& type, const int quantity);
	bool harvestResource(TransactionLog& trx, CreatureObject* player, ResourceSpawn* resourceSpawn, int quantity);
	bool addResourceToPlayerInventory(TransactionLog& trx, CreatureObject* player, ResourceSpawn* resourceSpawn, int unitsExtracted) const;

	ResourceSpawn* getCurrentSpawn(const String& restype, const String& zoneName) const;
	ResourceSpawn* getFromRandomPool(const String& type);

	void addNodeToListBox(SuiListBox* sui, const String& nodeName) const;
	void addPlanetsToListBox(SuiListBox* sui) const;

	String addParentNodeToListBox(SuiListBox* sui, const String& currentNode) const;

	inline ResourceMap* getResourceMap() {
		return resourceMap;
	}

	inline const ResourceMap* getResourceMap() const {
		return resourceMap;
	}

	void listResourcesForPlanetOnScreen(CreatureObject* creature, const String& planet) const;

	String healthCheck();

	String dumpResources() {
		if(writeAllSpawnsToScript())
			return "Resources Dumped";

		return "Error Dumping resources";
	}

	String getPlanetByIndex(int index) const;
private:

	void loadResourceSpawns();
	String makeResourceName(const String& randomNameClass);
	int randomizeValue(int min, int max);
	long getRandomExpirationTime(const ResourceTreeEntry* resourceEntry);
	long getRandomUnixTimestamp(int min, int max) const;

	const Vector<String>& getJtlResources() const;
	const Vector<String>& getActiveResourceZones() const;

	friend class ResourceTree;
	friend class ResourceManager;
	friend class NativePool;
};

#endif /* RESOURCESPAWNER_H_ */
