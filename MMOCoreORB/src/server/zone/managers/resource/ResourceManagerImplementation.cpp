/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/managers/resource/ResourceManager.h"
#include "ResourceShiftTask.h"
#include "resourcespawner/SampleTask.h"
#include "resourcespawner/SampleResultsTask.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void ResourceManagerImplementation::initialize() {
	if (!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	resourceSpawner->init();

	startResourceSpawner();
	loadSurveyData();
}

void ResourceManagerImplementation::loadSurveyData() {
	info("Loading survey data form surveys.db");
	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* surveyDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("surveys", true);
	if (surveyDatabase == NULL) {
		error("Could not load the survey database.");
		return;
	}
	int i = 0;
	try {
		ObjectDatabaseIterator iterator(surveyDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Core::getObjectBroker()->lookUp(objectID);
			++i;
		}
	} catch (DatabaseException& e) {
		error("Database exception in DirectorManager::loadSurveyData(): "	+ e.getMessage());
	}
	info(String::valueOf(i) + " surveys loaded.", true);
}

int ResourceManagerImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::POSTURECHANGED) {
		CreatureObject* creature = cast<CreatureObject*>( observable);

		if (creature == NULL) {
			return 0;
		}

		// Cancel Sampling on posture change
		Reference<SampleTask*> task = creature->getPendingTask("sample").castTo<SampleTask*>( );
		Reference<SampleResultsTask*> sampleResultsTask = creature->getPendingTask("sampleresults").castTo<SampleResultsTask*>( );

		if (task != NULL) {

			task->stopSampling();
			//creature->removePendingTask("sample");

			if(sampleResultsTask != NULL) {
				sampleResultsTask->cancel();
				creature->removePendingTask("sampleresults");
			}

			creature->sendSystemMessage("@survey:sample_cancel");
		}

		return 1;
	}

	return 0;
}

bool ResourceManagerImplementation::loadConfigData() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/resource_manager.lua")) {
		delete lua;
		return false;
	}

	bool loadFromScript = lua->getGlobalInt("buildInitialResourcesFromScript");

	String zonesString = lua->getGlobalString("activeZones");

	StringTokenizer zonesTokens(zonesString);
	zonesTokens.setDelimeter(",");

	while(zonesTokens.hasMoreTokens()) {
		String zoneName;
		zonesTokens.getStringToken(zoneName);
		resourceSpawner->addZone(zoneName);
	}

	shiftInterval = lua->getGlobalInt("averageShiftTime");

	int aveduration = lua->getGlobalInt("aveduration");
	int spawnThrottling = lua->getGlobalInt("spawnThrottling");
	int lowerGateOverride = lua->getGlobalInt("lowerGateOverride");
	int maxSpawnQuantity = lua->getGlobalInt("maxSpawnQuantity");

	resourceSpawner->setSpawningParameters(loadFromScript, aveduration,
			spawnThrottling, lowerGateOverride, maxSpawnQuantity);

	String jtlResources = lua->getGlobalString("jtlresources");

	StringTokenizer jtlTokens(jtlResources);
	jtlTokens.setDelimeter(",");

	while(jtlTokens.hasMoreTokens()) {
		String token;
		jtlTokens.getStringToken(token);
		resourceSpawner->addJtlResource(token);
	}

	LuaObject minpoolinc = lua->getGlobalObject("minimumpoolincludes");
	String minpoolexc = lua->getGlobalString("minimumpoolexcludes");
	resourceSpawner->initializeMinimumPool(minpoolinc, minpoolexc);

	LuaObject randpoolinc = lua->getGlobalObject("randompoolincludes");
	String randpoolexc = lua->getGlobalString("randompoolexcludes");
	int randpoolsize = lua->getGlobalInt("randompoolsize");
	resourceSpawner->initializeRandomPool(randpoolinc, randpoolexc, randpoolsize);

	LuaObject fixedpoolinc = lua->getGlobalObject("fixedpoolincludes");
	String fixedpoolexc = lua->getGlobalString("fixedpoolexcludes");
	resourceSpawner->initializeFixedPool(fixedpoolinc, fixedpoolexc);

	String natpoolinc = lua->getGlobalString("nativepoolincludes");
	String natpoolexc = lua->getGlobalString("nativepoolexcludes");
	resourceSpawner->initializeNativePool(natpoolinc, natpoolexc);

	delete lua;

	return true;
}

void ResourceManagerImplementation::loadDefaultConfig() {

	resourceSpawner->addZone("corellia");
	resourceSpawner->addZone("lok");
	resourceSpawner->addZone("yavin4");
	resourceSpawner->addZone("dantooine");
	resourceSpawner->addZone("dathomir");
	resourceSpawner->addZone("naboo");
	resourceSpawner->addZone("rori");
	resourceSpawner->addZone("talus");
	resourceSpawner->addZone("tatooine");
	resourceSpawner->addZone("endor");

	shiftInterval = 7200000;
	resourceSpawner->setSpawningParameters(1, 86400, 90, 1000, 0);
}

void ResourceManagerImplementation::stop() {
	processor = NULL;
	zoneServer = NULL;
	resourceSpawner = NULL;
}

void ResourceManagerImplementation::startResourceSpawner() {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	resourceSpawner->start();

	Reference<ResourceShiftTask*> resourceShift = new ResourceShiftTask(_this.getReferenceUnsafeStaticCast());
	resourceShift->schedule(shiftInterval);
}

void ResourceManagerImplementation::shiftResources() {
	Timer timer(Time::MONOTONIC_TIME);

	info("starting resource shift");

	timer.start();

	Locker _locker(_this.getReferenceUnsafeStaticCast());

	resourceSpawner->shiftResources();

	auto elapsed = timer.stop();

	info("resource shift ended in " + String::valueOf(elapsed) + "ns");

	Reference<ResourceShiftTask*> resourceShift = new ResourceShiftTask(_this.getReferenceUnsafeStaticCast());
	resourceShift->schedule(shiftInterval);
}

int ResourceManagerImplementation::getResourceRecycleType(ResourceSpawn* resource) {
	return resourceSpawner->sendResourceRecycleType(resource);
}

void ResourceManagerImplementation::sendResourceListForSurvey(CreatureObject* playerCreature, const int toolType, const String& surveyType) {
	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	resourceSpawner->sendResourceListForSurvey(playerCreature, toolType, surveyType);
}

ResourceContainer* ResourceManagerImplementation::harvestResource(CreatureObject* player, const String& type, const int quantity) {
	return resourceSpawner->harvestResource(player, type, quantity);
}
bool ResourceManagerImplementation::harvestResourceToPlayer(CreatureObject* player, ResourceSpawn* resourceSpawn, const int quantity) {
	return resourceSpawner->harvestResource(player, resourceSpawn, quantity);
}

void ResourceManagerImplementation::sendSurvey(CreatureObject* playerCreature, const String& resname) {
	resourceSpawner->sendSurvey(playerCreature, resname);
}

void ResourceManagerImplementation::sendSample(CreatureObject* playerCreature, const String& resname, const String& sampleAnimation) {
	resourceSpawner->sendSample(playerCreature, resname, sampleAnimation);

	playerCreature->registerObserver(ObserverEventType::POSTURECHANGED, _this.getReferenceUnsafeStaticCast());
}

void ResourceManagerImplementation::createResourceSpawn(CreatureObject* playerCreature, const UnicodeString& args) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	ResourceSpawn* resourceSpawn = resourceSpawner->manualCreateResourceSpawn(playerCreature, args);

	if (resourceSpawn != NULL) {
		StringBuffer buffer;
		buffer << "Spawned " << resourceSpawn->getName() << " of type " << resourceSpawn->getType();

		playerCreature->sendSystemMessage(buffer.toString());
	} else {
		playerCreature->sendSystemMessage("Could not create resource spawn, invalid arguments");
	}

}

ResourceSpawn* ResourceManagerImplementation::getResourceSpawn(const String& spawnName) {
	ResourceSpawn* spawn = NULL;

	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	ResourceMap* resourceMap = resourceSpawner->getResourceMap();

	spawn = resourceMap->get(spawnName.toLowerCase());

	return spawn;
}

ResourceSpawn* ResourceManagerImplementation::getCurrentSpawn(const String& restype, const String& zoneName) {
	return resourceSpawner->getCurrentSpawn(restype, zoneName);
}

void ResourceManagerImplementation::getResourceListByType(Vector<ManagedReference<ResourceSpawn*> >& list, int type, const String& zoneName) {
	list.removeAll();

	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	ManagedReference<ResourceSpawn*> resourceSpawn;

	try {
		ResourceMap* resourceMap = resourceSpawner->getResourceMap();

		ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(zoneName);

		if (zoneMap != NULL) {
			for (int i = 0; i < zoneMap->size(); ++i) {
				resourceSpawn = zoneMap->get(i);

				if (!resourceSpawn->inShift())
					continue;

				if (type == 9){
					if (resourceSpawn->isType("radioactive"))
						list.add(resourceSpawn);
				}

				else if (resourceSpawn->getSurveyToolType() == type) {
					list.add(resourceSpawn);
				}
			}

		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

uint32 ResourceManagerImplementation::getAvailablePowerFromPlayer(CreatureObject* player) {
	SceneObject* inventory = player->getSlottedObject("inventory");
	uint32 power = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> obj =  inventory->getContainerObject(i).castTo<SceneObject*>();

		if (obj == NULL || !obj->isResourceContainer())
			continue;

		ResourceContainer* rcno = cast<ResourceContainer*>( obj.get());
		ManagedReference<ResourceSpawn*> spawn = rcno->getSpawnObject();

		if (spawn == NULL || !spawn->isEnergy())
			continue;

		int quantity = rcno->getQuantity();
		int pe = spawn->getValueOf(CraftingManager::PE); // potential energy

		float modifier = Math::max(1.0f, pe / 500.0f);

		power += (uint32) (modifier * quantity);
	}

	return power;
}

void ResourceManagerImplementation::removePowerFromPlayer(CreatureObject* player, uint32 power) {
	if (power == 0)
		return;

	SceneObject* inventory = player->getSlottedObject("inventory");

	uint32 containerPower = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize() && power > 0; ++i) {
		ManagedReference<SceneObject*> obj = inventory->getContainerObject(i);

		if (obj == NULL || !obj->isResourceContainer())
			continue;

		ResourceContainer* rcno = cast<ResourceContainer*>( obj.get());

		Locker locker(rcno);

		ManagedReference<ResourceSpawn*> spawn = rcno->getSpawnObject();

		if (spawn == NULL || !spawn->isEnergy())
			continue;

		int quantity = rcno->getQuantity();
		int pe = spawn->getValueOf(CraftingManager::PE); // potential energy

		float modifier = Math::max(1.0f, pe / 500.0f);

		containerPower = modifier * quantity;

		if (containerPower > power) {
			uint32 consumedUnits = (uint64) power / modifier;
			rcno->setQuantity(quantity - consumedUnits);

			ResourceContainerObjectDeltaMessage3* drcno3 = new ResourceContainerObjectDeltaMessage3(rcno);
			drcno3->updateQuantity();
			drcno3->close();
			player->sendMessage(drcno3);
			return;
		} else {
			rcno->destroyObjectFromWorld(true);
			rcno->destroyObjectFromDatabase(true);
		}

		power -= containerPower;
	}
}
void ResourceManagerImplementation::givePlayerResource(CreatureObject* playerCreature, const String& restype, const int quantity) {
	ManagedReference<ResourceSpawn* > spawn = getResourceSpawn(restype);

	if(spawn == NULL) {
		playerCreature->sendSystemMessage("Selected spawn does not exist.");
		return;
	}

	ManagedReference<SceneObject*> inventory = playerCreature->getSlottedObject("inventory");

	if(inventory != NULL && !inventory->isContainerFullRecursive()) {
		Locker locker(spawn);

		Reference<ResourceContainer*> newResource = spawn->createResource(quantity);

		if(newResource != NULL) {
			spawn->extractResource("", quantity);

			Locker rlocker(newResource);

			if (inventory->transferObject(newResource, -1, true)) {
				inventory->broadcastObject(newResource, true);
			} else {
				newResource->destroyObjectFromDatabase(true);
			}
		}
	}
}

bool ResourceManagerImplementation::isRecycledResource(ResourceSpawn* resource) {
	return resourceSpawner->isRecycledResource(resource);
}

ResourceSpawn* ResourceManagerImplementation::getRecycledVersion(ResourceSpawn* resource) {
	return resourceSpawner->getRecycledVersion(resource);
}

/// Resource Deed Methods
void ResourceManagerImplementation::addNodeToListBox(SuiListBox* sui, const String& nodeName) {
	resourceSpawner->addNodeToListBox(sui, nodeName);
}

void ResourceManagerImplementation::addPlanetsToListBox(SuiListBox* sui) {
	resourceSpawner->addPlanetsToListBox(sui);
}
String ResourceManagerImplementation::getPlanetByIndex(int idx) {
	return resourceSpawner->getPlanetByIndex(idx);
}
String ResourceManagerImplementation::addParentNodeToListBox(SuiListBox* sui, const String& currentNode) {
	return resourceSpawner->addParentNodeToListBox(sui, currentNode);
}

void ResourceManagerImplementation::listResourcesForPlanetOnScreen(CreatureObject* creature, const String& planet) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	resourceSpawner->listResourcesForPlanetOnScreen(creature, planet);
}

String ResourceManagerImplementation::healthCheck() {
	return resourceSpawner->healthCheck();
}

String ResourceManagerImplementation::dumpResources() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	return resourceSpawner->dumpResources();
}

String ResourceManagerImplementation::despawnResource(String& resourceName) {

	ManagedReference<ResourceSpawn*> spawn = getResourceSpawn(resourceName);
	if(spawn == NULL) {
		return "Spawn not Found";
	}

	spawn->setDespawned(time(0) - 1);
	resourceSpawner->shiftResources();

	return resourceName + " despawned.";
}
