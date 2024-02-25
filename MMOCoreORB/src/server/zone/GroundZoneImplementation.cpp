/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/GroundZone.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/GroundZoneContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/packets/player/GetMapLocationsResponseMessage.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "templates/SharedObjectTemplate.h"

#include "server/zone/managers/structure/StructureManager.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/ActiveAreaQuadTree.h"

GroundZoneImplementation::GroundZoneImplementation(ZoneProcessServer* serv, const String& name) : ZoneImplementation(serv, name) {
	areaTree = new server::zone::ActiveAreaQuadTree(-8192, -8192, 8192, 8192);
	quadTree = new server::zone::QuadTree(-8192, -8192, 8192, 8192);

	planetManager = nullptr;

	String capName = name;
	capName[0] = toupper(name[0]);

	int numThreads = ConfigManager::instance()->getInt("Core3.Zone.ThreadsDefault", 1);
	numThreads = ConfigManager::instance()->getInt("Core3.Zone.Threads" + capName, numThreads);

	setLoggingName("GroundZone " + name);

	if (numThreads != 1) {
		info(true) << "GroundZone " << capName << " using " << numThreads << " threads.";
	}

	Core::getTaskManager()->initializeCustomQueue(zoneName, numThreads, true);
}

void GroundZoneImplementation::createContainerComponent() {
	containerComponent = ComponentManager::instance()->getComponent<GroundZoneContainerComponent*>("GroundZoneContainerComponent");
}

void GroundZoneImplementation::initializePrivateData() {
	planetManager = new PlanetManager(_this.getReferenceUnsafeStaticCast(), processor);

	creatureManager = new CreatureManager(_this.getReferenceUnsafeStaticCast());
	creatureManager->deploy("CreatureManager " + zoneName);
	creatureManager->setZoneProcessor(processor);
}

void GroundZoneImplementation::finalize() {
}

void GroundZoneImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	mapLocations = new MapLocationTable();

	//heightMap->load("planets/" + planetName + "/" + planetName + ".hmap");
}

void GroundZoneImplementation::startManagers() {
	planetManager->initialize();

	creatureManager->initialize();

	StructureManager::instance()->loadPlayerStructures(getZoneName());

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	planetManager->start();

	managersStarted = true;
}

void GroundZoneImplementation::stopManagers() {
	info("Shutting down.. ", true);

	if (creatureManager != nullptr) {
		creatureManager->stop();
		creatureManager = nullptr;
	}

	if (planetManager != nullptr) {
		//planetManager->finalize();
		planetManager = nullptr;
	}

	processor = nullptr;
	server = nullptr;
	mapLocations = nullptr;
	objectMap = nullptr;
	quadTree = nullptr;
	areaTree = nullptr;
}

void GroundZoneImplementation::clearZone() {
	Locker zonelocker(_this.getReferenceUnsafeStaticCast());

	info("clearing zone", true);

	creatureManager->unloadSpawnAreas();

	HashTable<uint64, ManagedReference<SceneObject*> > tbl;
	tbl.copyFrom(*objectMap->getMap());

	zonelocker.release();

	auto iterator = tbl.iterator();

	while (iterator.hasNext()) {
		ManagedReference<SceneObject*> sceno = iterator.getNextValue();

		if (sceno != nullptr) {
			Locker locker(sceno);
			sceno->destroyObjectFromWorld(false);
		}
	}

	Locker zonelocker2(_this.getReferenceUnsafeStaticCast());

	zoneCleared = true;

	info("zone clear", true);
}

/*

	Object Management in Zone

*/

void GroundZoneImplementation::insert(TreeEntry* entry) {
	if (entry == nullptr)
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	quadTree->insert(entry);

	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr && sceneO->isPlayerCreature())
		info(true) << "Inserting player into Quadtree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/
}

void GroundZoneImplementation::remove(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (entry->isInQuadTree()) {
		quadTree->remove(entry);

		/*
		SceneObject* sceneO = cast<SceneObject*>(entry);

		if (sceneO != nullptr && sceneO->isPlayerCreature())
			info(true) << "Removing player from Quadtree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
		*/
	}
}

void GroundZoneImplementation::update(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	quadTree->update(entry);

	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr && sceneO->isPlayerCreature())
		info(true) << "Inserting player into Quadtree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/
}

void GroundZoneImplementation::inRange(TreeEntry* entry, float range) {
	quadTree->safeInRange(entry, range);
}

void GroundZoneImplementation::updateActiveAreas(TangibleObject* tano) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	Locker _alocker(tano->getContainerLock());

	SortedVector<ManagedReference<ActiveArea* > > areas = *tano->getActiveAreas();

	_alocker.release();

	Vector3 worldPos = tano->getWorldPosition();

	SortedVector<ActiveArea*> entryObjects;

	Zone* managedRef = _this.getReferenceUnsafeStaticCast();

	bool readlock = !managedRef->isLockedByCurrentThread();

	managedRef->rlock(readlock);

	try {
		areaTree->getActiveAreas(worldPos.getX(), worldPos.getY(), entryObjects);

	} catch (...) {
		error("unexpeted error caught in void GroundZoneImplementation::updateActiveAreas(SceneObject* object) {");
	}

	managedRef->runlock(readlock);

	managedRef->unlock(!readlock);

	try {
		// update old ones
		for (int i = 0; i < areas.size(); ++i) {
			ManagedReference<ActiveArea*>& area = areas.getUnsafe(i);

			if (area == nullptr || area->isWorldSpawnArea())
				continue;

			if (!area->containsPoint(worldPos.getX(), worldPos.getY(), tano->getParentID())) {
				tano->dropActiveArea(area);
				area->enqueueExitEvent(tano);
			} else {
				area->notifyPositionUpdate(tano);
			}
		}

		// we update the ones in quadtree.
		for (int i = 0; i < entryObjects.size(); ++i) {
			//update in new ones
			ActiveArea* activeArea = static_cast<ActiveArea*>(entryObjects.getUnsafe(i));

			if (!tano->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getY(), tano->getParentID())) {
				tano->addActiveArea(activeArea);
				activeArea->enqueueEnterEvent(tano);
			}
		}

		// update Zones World Spawn Area
		if (creatureManager != nullptr) {
			auto worldArea = creatureManager->getWorldSpawnArea();

			if (worldArea != nullptr) {
				Reference<TangibleObject*> tanoStrong = tano;
				Reference<ActiveArea*> areaStrong = worldArea;

				Core::getTaskManager()->executeTask([areaStrong, tanoStrong] () {
					Locker lockerO(tanoStrong);

					if (!tanoStrong->hasActiveArea(areaStrong)) {
						tanoStrong->addActiveArea(areaStrong);
						areaStrong->notifyEnter(tanoStrong);
					} else {
						areaStrong->notifyPositionUpdate(tanoStrong);
					}
				}, "UpdateWorldActiveArea", zoneName);
			}
		}
	} catch (...) {
		error("unexpected exception caught in void GroundZoneImplementation::updateActiveAreas(SceneObject* object) {");
		managedRef->wlock(!readlock);
		throw;
	}

	managedRef->wlock(!readlock);
}

void GroundZoneImplementation::addSceneObject(SceneObject* object) {
	ManagedReference<SceneObject*> old = objectMap->put(object->getObjectID(), object);

	//Civic and commercial structures map registration will be handled by their city
	if (object->isStructureObject()) {
		StructureObject* structure = cast<StructureObject*>(object);
		if (structure->isCivicStructure() || structure->isCommercialStructure()) {
			return;
		}
	//Same thing for player city bank/mission terminals
	} else if (object->isTerminal()) {
		Terminal* terminal = cast<Terminal*>(object);
		ManagedReference<SceneObject*> controlledObject = terminal->getControlledObject();
		if (controlledObject != nullptr && controlledObject->isStructureObject()) {
			StructureObject* structure = controlledObject.castTo<StructureObject*>();
			if (structure->isCivicStructure())
				return;
		}
	} else if (old == nullptr && object->isAiAgent()) {
		spawnedAiAgents.increment();
	}

	registerObjectWithPlanetaryMap(object);
}

void GroundZoneImplementation::dropSceneObject(SceneObject* object)  {
	ManagedReference<SceneObject*> oldObject = objectMap->remove(object->getObjectID());

	unregisterObjectWithPlanetaryMap(object);

	if (oldObject != nullptr && oldObject->isAiAgent()) {
		spawnedAiAgents.decrement();
	}
}

/*

	Object Tracking

*/

int GroundZoneImplementation::getInRangeSolidObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		quadTree->inRange(x, y, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	if (objects->size() > 0) {
		for (int i = objects->size() - 1; i >= 0; i--) {
			SceneObject* sceno = static_cast<SceneObject*>(objects->getUnsafe(i).get());

			if (sceno == nullptr || sceno->getParentID() != 0) {
				objects->remove(i);
				continue;
			}

			if (sceno->isCreatureObject() || sceno->isLairObject()) {
				objects->remove(i);
				continue;
			}

			if (sceno->getGameObjectType() == SceneObjectType::LIGHTOBJECT) {
				objects->remove(i);
				continue;
			}

			SharedObjectTemplate *shot = sceno->getObjectTemplate();

			if (shot == nullptr) {
				objects->remove(i);
				continue;
			}

			if (!shot->getCollisionMaterialFlags() || !shot->getCollisionMaterialBlockFlags() || !shot->isNavUpdatesEnabled()) {
				objects->remove(i);
				continue;
			}
		}
	}
	return objects->size();
}

int GroundZoneImplementation::getInRangeObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone, bool includeBuildingObjects) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		quadTree->inRange(x, y, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	if (includeBuildingObjects) {
		Vector<ManagedReference<TreeEntry*> > buildingObjects;

		for (int i = 0; i < objects->size(); ++i) {
			SceneObject* sceneObject = static_cast<SceneObject*>(objects->getUnsafe(i).get());
			BuildingObject* building = sceneObject->asBuildingObject();

			if (building != nullptr) {
				for (int j = 1; j <= building->getMapCellSize(); ++j) {
					CellObject* cell = building->getCell(j);

					if (cell != nullptr && cell->isContainerLoaded()) {
						try {
							ReadLocker rlocker(cell->getContainerLock());

							for (int h = 0; h < cell->getContainerObjectsSize(); ++h) {
								Reference<SceneObject*> obj = cell->getContainerObject(h);

								if (obj != nullptr)
									buildingObjects.emplace(std::move(obj));
							}

						} catch (...) {
						}
					}
				}
			} else if (sceneObject->isVehicleObject() || sceneObject->isMount()) {
				Reference<SceneObject*> rider = sceneObject->getSlottedObject("rider");

				if (rider != nullptr)
					buildingObjects.emplace(std::move(rider));
			}
		}

		//_this.getReferenceUnsafeStaticCast()->runlock(readlock);

		for (int i = 0; i < buildingObjects.size(); ++i)
			objects->put(std::move(buildingObjects.getUnsafe(i)));
	}

	return objects->size();
}

int GroundZoneImplementation::getInRangeObjects(float x, float z, float y, float range, InRangeObjectsVector* objects, bool readLockZone, bool includeBuildingObjects) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		quadTree->inRange(x, y, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	if (includeBuildingObjects) {
		Vector<TreeEntry*> buildingObjects;

		for (int i = 0; i < objects->size(); ++i) {
			SceneObject* sceneObject = static_cast<SceneObject*>(objects->getUnsafe(i));

			BuildingObject* building = sceneObject->asBuildingObject();

			if (building != nullptr) {
				for (int j = 1; j <= building->getMapCellSize(); ++j) {
					CellObject* cell = building->getCell(j);

					if (cell != nullptr && cell->isContainerLoaded()) {
						try {
							ReadLocker rlocker(cell->getContainerLock());

							for (int h = 0; h < cell->getContainerObjectsSize(); ++h) {
								Reference<SceneObject*> obj = cell->getContainerObject(h);

								if (obj != nullptr)
									buildingObjects.add(obj.get());
							}

						} catch (Exception& e) {
							warning("exception in Zone::GetInRangeObjects: " + e.getMessage());
						}
					}
				}
			} else if (sceneObject->isVehicleObject() || sceneObject->isMount()) {
				Reference<SceneObject*> rider = sceneObject->getSlottedObject("rider");

				if (rider != nullptr)
					buildingObjects.add(rider.get());
			}
		}

		for (int i = 0; i < buildingObjects.size(); ++i)
			objects->put(buildingObjects.getUnsafe(i));
	}

	return objects->size();
}

int GroundZoneImplementation::getInRangePlayers(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* players) {
	Reference<SortedVector<ManagedReference<TreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<TreeEntry*> >();

	getInRangeObjects(x, 0, y, range, closeObjects, true);

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* object = cast<SceneObject*>(closeObjects->get(i).get());

		if (object == nullptr || !object->isPlayerCreature())
			continue;

		CreatureObject* player = object->asCreatureObject();

		if (player == nullptr || player->isInvisible())
			continue;

		players->emplace(object);
	}

	return players->size();
}

int GroundZoneImplementation::getInRangeActiveAreas(float x, float z, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		areaTree->getActiveAreas(x, y, *objects);

		thisZone->runlock(readlock);
	} catch (...) {
		thisZone->runlock(readlock);

		throw;
	}

	return objects->size();
}

int GroundZoneImplementation::getInRangeActiveAreas(float x, float z, float y, ActiveAreasVector* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		areaTree->getActiveAreas(x, y, *objects);

		thisZone->runlock(readlock);
	} catch (...) {
		thisZone->runlock(readlock);

		throw;
	}

	return objects->size();
}

/*

	Quadtree

*/

float GroundZoneImplementation::getHeight(float x, float y) {
	if (planetManager != nullptr) {
		TerrainManager* manager = planetManager->getTerrainManager();

		if (manager != nullptr)
			return manager->getHeight(x, y);
	}

	return 0;
}

float GroundZoneImplementation::getHeightNoCache(float x, float y) {
	if (planetManager != nullptr) {
		TerrainManager* manager = planetManager->getTerrainManager();

		if (manager != nullptr) {
			ProceduralTerrainAppearance *appearance = manager->getProceduralTerrainAppearance();
			if (appearance != nullptr)
				return appearance->getHeight(x, y);
		}
	}

	return 0;
}

Reference<SceneObject*> GroundZoneImplementation::getNearestPlanetaryObject(SceneObject* object, const String& mapCategory, const String& mapSubCategory) {
	Reference<SceneObject*> planetaryObject = nullptr;

#ifndef WITH_STM
	ReadLocker rlocker(mapLocations);
#endif

	// info(true) << "getNearestPlanetaryObject - To: " << object->getDisplayedName() << " MapCategory: " << mapCategory << " SubCategory: " << mapSubCategory;

	const SortedVector<MapLocationEntry>& sortedVector = mapLocations->getLocation(mapCategory);

	Vector3 objectPos = object->getWorldPosition();
	int distanceCheck = 16000 * 16000;

	// info(true) << "Sub Category: " << mapSubCategory;

	for (int i = 0; i < sortedVector.size(); ++i) {
		SceneObject* sceneO = sortedVector.getUnsafe(i).getObject();

		if (sceneO == nullptr)
			continue;

		const String subCategory = sceneO->getPlanetMapSubCategoryName();

		// info(true) << " Checking against Object Sub Category: " << subCategory;

		if (!mapSubCategory.isEmpty() && !subCategory.isEmpty() && !subCategory.contains(mapSubCategory))
			continue;

		float objDistanceSq = objectPos.squaredDistanceTo(sceneO->getWorldPosition());

		// info(true) << "Map Object Distance = " << objDistanceSq << " Checking against: " << distanceCheck;

		if (objDistanceSq < distanceCheck) {
			// Set object as our current closest planetary object of that type
			planetaryObject = sceneO;

			// Update the distance to check against
			distanceCheck = objDistanceSq;
		}
	}

	return planetaryObject;
}

int GroundZoneImplementation::getInRangeNavMeshes(float x, float y, SortedVector<ManagedReference<NavArea*> >* objects, bool readlock) {
	objects->setNoDuplicateInsertPlan();

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	SortedVector<ActiveArea*> entryObjects;

	ReadLocker rlocker(thisZone);

	areaTree->getActiveAreas(x, y, entryObjects);

	for (int i = 0; i < entryObjects.size(); ++i) {
		ActiveArea* area = static_cast<ActiveArea*>(entryObjects.getUnsafe(i));
		NavArea* obj = area->asNavArea();

		if (obj && obj->isNavMeshLoaded()) {
			objects->put(obj);
		}
	}

	return objects->size();
}

SortedVector<ManagedReference<SceneObject*> > GroundZoneImplementation::getPlanetaryObjectList(const String& mapCategory) {
	SortedVector<ManagedReference<SceneObject*> > retVector;
	retVector.setNoDuplicateInsertPlan();

#ifndef WITH_STM
	ReadLocker rlocker(mapLocations);
#endif

	const SortedVector<MapLocationEntry>& entryVector = mapLocations->getLocation(mapCategory);

	for (int i = 0; i < entryVector.size(); ++i) {
		const MapLocationEntry& entry = entryVector.getUnsafe(i);
		retVector.put(entry.getObject());
	}

	return retVector;
}

void GroundZoneImplementation::registerObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->transferObject(object);

	// If the object is a valid location for entertainer missions then add it
	// to the planet's mission map.
	if (objectIsValidPlanetaryMapPerformanceLocation(object)) {
		PlanetManager* planetManager = getPlanetManager();
		if (planetManager != nullptr) {
			planetManager->addPerformanceLocation(object);
		}
	}
}

void GroundZoneImplementation::unregisterObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->dropObject(object);

	// If the object is a valid location for entertainer missions then remove it
	// from the planet's mission map.
	if (objectIsValidPlanetaryMapPerformanceLocation(object)) {
		PlanetManager* planetManager = getPlanetManager();
		if (planetManager != nullptr) {
			planetManager->removePerformanceLocation(object);
		}
	}
}

bool GroundZoneImplementation::objectIsValidPlanetaryMapPerformanceLocation(SceneObject* object) {
	BuildingObject* building = object->asBuildingObject();
	if (building == nullptr) {
		return false;
	}

	bool hasPerformanceLocationCategory = false;

	const PlanetMapCategory* planetMapCategory = object->getPlanetMapCategory();
	if (planetMapCategory != nullptr) {
		String category = planetMapCategory->getName();

		if (category == "cantina" || category == "hotel") {
			hasPerformanceLocationCategory = true;
		}
	}

	if (!hasPerformanceLocationCategory) {
		const PlanetMapSubCategory* planetMapSubCategory = object->getPlanetMapSubCategory();

		if (planetMapCategory != nullptr) {
			String subCategory = planetMapSubCategory->getName();

			if (subCategory == "guild_theater") {
				hasPerformanceLocationCategory = true;
			}
		}
	}

	if (hasPerformanceLocationCategory) {
		if (building->isPublicStructure()) {
			return true;
		}
	}

	return false;
}

bool GroundZoneImplementation::isObjectRegisteredWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	return mapLocations->containsObject(object);
}

void GroundZoneImplementation::updatePlanetaryMapIcon(SceneObject* object, byte icon) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->updateObjectsIcon(object, icon);
}

void GroundZoneImplementation::sendMapLocationsTo(CreatureObject* player) {
	GetMapLocationsResponseMessage* gmlr = new GetMapLocationsResponseMessage(zoneName, mapLocations, player);
	player->sendMessage(gmlr);
}

float GroundZoneImplementation::getMinX() {
	return planetManager->getTerrainManager()->getMin();
}

float GroundZoneImplementation::getMaxX() {
	return planetManager->getTerrainManager()->getMax();
}

float GroundZoneImplementation::getMinY() {
	return planetManager->getTerrainManager()->getMin();
}

float GroundZoneImplementation::getMaxY() {
	return planetManager->getTerrainManager()->getMax();
}

void GroundZoneImplementation::updateCityRegions() {
	bool log = cityRegionUpdateVector.size() > 0;
	info("scheduling updates for " + String::valueOf(cityRegionUpdateVector.size()) + " cities", log);

	bool forceRebuild = server->shouldDeleteNavAreas();

	for (int i = 0; i < cityRegionUpdateVector.size(); ++i) {
		CityRegion* city = cityRegionUpdateVector.get(i);

		Locker locker(city);

		Time* nextUpdateTime = city->getNextUpdateTime();
		int seconds = -1 * round(nextUpdateTime->miliDifference() / 1000.f);

		if (seconds < 0) //If the update occurred in the past, force an immediate update.
			seconds = 0;

		city->setRadius(city->getRadius());
		city->setLoaded();

		city->cleanupCitizens();
		//city->cleanupDuplicateCityStructures();

		city->rescheduleUpdateEvent(seconds);

		if (city->hasAssessmentPending()) {
			Time* nextAssessmentTime = city->getNextAssessmentTime();
			int seconds2 = -1 * round(nextAssessmentTime->miliDifference() / 1000.f);

			if (seconds2 < 0)
				seconds2 = 0;

			city->scheduleCitizenAssessment(seconds2);
		}

		city->createNavMesh(NavMeshManager::MeshQueue, forceRebuild);

		if (!city->isRegistered())
			continue;

		if (city->getRegionsCount() == 0)
			continue;

		Region* region = city->getRegion(0);

		unregisterObjectWithPlanetaryMap(region);
		registerObjectWithPlanetaryMap(region);

		for(int i = 0; i < city->getStructuresCount(); i++){
			ManagedReference<StructureObject*> structure = city->getCivicStructure(i);
			unregisterObjectWithPlanetaryMap(structure);
			registerObjectWithPlanetaryMap(structure);
		}

		for(int i = 0; i < city->getCommercialStructuresCount(); i++){
			ManagedReference<StructureObject*> structure = city->getCommercialStructure(i);
			unregisterObjectWithPlanetaryMap(structure);
			registerObjectWithPlanetaryMap(structure);
		}
	}

	cityRegionUpdateVector.removeAll();
}

/*

	Shared Functions

*/

bool GroundZoneImplementation::isWithinBoundaries(const Vector3& position) {
	//Remove 1/16th of the size to match client limits. NOTE: it has not been verified to work like this in the client.
	//Normal zone size is 8192, 1/16th of that is 512 resulting in 7680 as the boundary value.
	float maxX = getMaxX() * 15 / 16;
	float minX = getMinX() * 15 / 16;
	float maxY = getMaxY() * 15 / 16;
	float minY = getMinY() * 15 / 16;

	if (maxX >= position.getX() && minX <= position.getX() &&
			maxY >= position.getY() && minY <= position.getY()) {
		return true;
	} else {
		return false;
	}
}

float GroundZoneImplementation::getBoundingRadius() {
	return planetManager->getTerrainManager()->getMax();
}

GroundZone* GroundZoneImplementation::asGroundZone() {
	return _this.getReferenceUnsafeStaticCast();
}

GroundZone* GroundZone::asGroundZone() {
	return this;
}
