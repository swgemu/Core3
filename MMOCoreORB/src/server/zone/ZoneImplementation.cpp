/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/Zone.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/packets/player/GetMapLocationsResponseMessage.h"
#include "server/zone/managers/gcw/GCWManager.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"

#include "server/zone/managers/structure/StructureManager.h"

#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/managers/minigames/ForageManager.h"

ZoneImplementation::ZoneImplementation(ZoneProcessServer* serv, const String& name) {
	processor = serv;
	server = processor->getZoneServer();

	zoneName = name;
	zoneCRC = name.hashCode();

	regionTree = new QuadTree(-8192, -8192, 8192, 8192);
	quadTree = new QuadTree(-8192, -8192, 8192, 8192);

	objectMap = new ObjectMap();

	mapLocations = new MapLocationTable();

	managersStarted = false;

	//galacticTime = new Time();

	planetManager = NULL;

	gcwManager = NULL;

	setLoggingName("Zone " + name);
}

void ZoneImplementation::createContainerComponent() {
	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>("ZoneContainerComponent");
}

void ZoneImplementation::initializePrivateData() {
	if (zoneName.contains("space_")) {
		planetManager = new SpaceManager(_this.getReferenceUnsafeStaticCast(), processor);
	} else {
		planetManager = new PlanetManager(_this.getReferenceUnsafeStaticCast(), processor);
	}

	creatureManager = new CreatureManager(_this.getReferenceUnsafeStaticCast());
	creatureManager->deploy("CreatureManager " + zoneName);
	creatureManager->setZoneProcessor(processor);

	gcwManager = new GCWManager(_this.getReferenceUnsafeStaticCast());
}

void ZoneImplementation::finalize() {
	//System::out << "deleting height map\n";
}

void ZoneImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	mapLocations = new MapLocationTable();

	//heightMap->load("planets/" + planetName + "/" + planetName + ".hmap");
}

void ZoneImplementation::startManagers() {
	gcwManager->start();

	planetManager->initialize();

	creatureManager->initialize();

	StructureManager::instance()->loadPlayerStructures(getZoneName());

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	managersStarted = true;
}

void ZoneImplementation::stopManagers() {
	//if (zoneID > 45) //TODO: Change back to 9 sometimes. We use Zone 10 (Space Corellia) as a "prison" for the CSRs sending bad players there
	//	return;

	/*if (creatureManager != NULL) {
		creatureManager->stop();

		creatureManager->finalize();
		creatureManager = NULL;
	}

	if (planetManager != NULL) {
		planetManager->stop();

		planetManager->finalize();
		planetManager = NULL;
	}*/
}

float ZoneImplementation::getHeight(float x, float y) {
	if (planetManager != NULL) {
		TerrainManager* manager = planetManager->getTerrainManager();

		if (manager != NULL)
			return manager->getHeight(x, y);
	}

	return 0;
}

void ZoneImplementation::insert(QuadTreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	quadTree->insert(entry);
}

void ZoneImplementation::remove(QuadTreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (entry->isInQuadTree())
		quadTree->remove(entry);
}

void ZoneImplementation::update(QuadTreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	quadTree->update(entry);
}

void ZoneImplementation::inRange(QuadTreeEntry* entry, float range) {
	quadTree->safeInRange(entry, range);
}

int ZoneImplementation::getInRangeObjects(float x, float y, float range, SortedVector<ManagedReference<QuadTreeEntry*> >* objects, bool readLockZone) {
	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Vector<ManagedReference<QuadTreeEntry*> > buildingObjects;

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		quadTree->inRange(x, y, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	for (int i = 0; i < objects->size(); ++i) {
		SceneObject* sceneObject = cast<SceneObject*>(objects->get(i).get());
		BuildingObject* building = dynamic_cast<BuildingObject*>(sceneObject);

		if (building != NULL) {
			for (int j = 1; j <= building->getMapCellSize(); ++j) {
				CellObject* cell = building->getCell(j);

				if (cell != NULL) {
					try {
						ReadLocker rlocker(cell->getContainerLock());

						for (int h = 0; h < cell->getContainerObjectsSize(); ++h) {
							ManagedReference<SceneObject*> obj = cell->getContainerObject(h);

							if (obj != NULL)
								buildingObjects.add(obj.get());
						}

					} catch (...) {
					}
				}
			}
		} else if (sceneObject != NULL && (sceneObject->isVehicleObject() || sceneObject->isMount())) {
			ManagedReference<SceneObject*> rider = sceneObject->getSlottedObject("rider");

			if (rider != NULL)
				buildingObjects.add(rider.get());
		}
	}

	//_this.getReferenceUnsafeStaticCast()->runlock(readlock);

	for (int i = 0; i < buildingObjects.size(); ++i)
		objects->put(buildingObjects.get(i));

	return objects->size();
}

int ZoneImplementation::getInRangeObjects(float x, float y, float range, InRangeObjectsVector* objects, bool readLockZone) {
	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Vector<QuadTreeEntry*> buildingObjects;

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		quadTree->inRange(x, y, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	for (int i = 0; i < objects->size(); ++i) {
		SceneObject* sceneObject = static_cast<SceneObject*>(objects->get(i));

		BuildingObject* building = dynamic_cast<BuildingObject*>(sceneObject);

		if (building != NULL) {
			for (int j = 1; j <= building->getMapCellSize(); ++j) {
				CellObject* cell = building->getCell(j);

				if (cell != NULL) {
					try {
						ReadLocker rlocker(cell->getContainerLock());

						for (int h = 0; h < cell->getContainerObjectsSize(); ++h) {
							ManagedReference<SceneObject*> obj = cell->getContainerObject(h);

							if (obj != NULL)
								buildingObjects.add(obj.get());
						}

					} catch (...) {
					}
				}
			}
		} else if (sceneObject != NULL && (sceneObject->isVehicleObject() || sceneObject->isMount())) {
			ManagedReference<SceneObject*> rider = sceneObject->getSlottedObject("rider");

			if (rider != NULL)
				buildingObjects.add(rider.get());
		}
	}

	for (int i = 0; i < buildingObjects.size(); ++i)
		objects->put(buildingObjects.get(i));

	return objects->size();
}

int ZoneImplementation::getInRangeActiveAreas(float x, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	//_this.getReferenceUnsafeStaticCast()->rlock(readlock);

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		SortedVector<ManagedReference<QuadTreeEntry*> > entryObjects;

		regionTree->inRange(x, y, entryObjects);

		thisZone->runlock(readlock);

		for (int i = 0; i < entryObjects.size(); ++i) {
			ActiveArea* obj = dynamic_cast<ActiveArea*>(entryObjects.get(i).get());
			objects->put(obj);
		}
	}catch (...) {
//		_this.getReferenceUnsafeStaticCast()->runlock(readlock);

		throw;
	}

//	_this.getReferenceUnsafeStaticCast()->runlock(readlock);

	return objects->size();
}

int ZoneImplementation::getInRangeActiveAreas(float x, float y, ActiveAreasVector* objects, bool readLockZone) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	//_this.getReferenceUnsafeStaticCast()->rlock(readlock);

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		SortedVector<QuadTreeEntry*> entryObjects;

		regionTree->inRange(x, y, entryObjects);

		thisZone->runlock(readlock);

		for (int i = 0; i < entryObjects.size(); ++i) {
			ActiveArea* obj = dynamic_cast<ActiveArea*>(entryObjects.get(i));
			objects->put(obj);
		}
	}catch (...) {
//		_this.getReferenceUnsafeStaticCast()->runlock(readlock);

		throw;
	}

//	_this.getReferenceUnsafeStaticCast()->runlock(readlock);

	return objects->size();
}

int ZoneImplementation::getInRangeActiveAreas(float x, float y, float range, ActiveAreasVector* objects, bool readLockZone) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	//_this.getReferenceUnsafeStaticCast()->rlock(readlock);

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		SortedVector<QuadTreeEntry*> entryObjects;

		regionTree->inRange(x, y, range, entryObjects);

		thisZone->runlock(readlock);

		for (int i = 0; i < entryObjects.size(); ++i) {
			ActiveArea* obj = dynamic_cast<ActiveArea*>(entryObjects.get(i));
			objects->put(obj);
		}
	}catch (...) {
		//		_this.getReferenceUnsafeStaticCast()->runlock(readlock);

		throw;
	}

	//	_this.getReferenceUnsafeStaticCast()->runlock(readlock);

	return objects->size();
}

int ZoneImplementation::getInRangeActiveAreas(float x, float y, float range, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	//_this.getReferenceUnsafeStaticCast()->rlock(readlock);
	
	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);
		
		SortedVector<ManagedReference<QuadTreeEntry*> > entryObjects;

		regionTree->inRange(x, y, range, entryObjects);
		
		thisZone->runlock(readlock);

		for (int i = 0; i < entryObjects.size(); ++i) {
			ActiveArea* obj = dynamic_cast<ActiveArea*>(entryObjects.get(i).get());
			objects->put(obj);
		}
	}catch (...) {
//		_this.getReferenceUnsafeStaticCast()->runlock(readlock);

		throw;
	}

//	_this.getReferenceUnsafeStaticCast()->runlock(readlock);

	return objects->size();
}

void ZoneImplementation::updateActiveAreas(TangibleObject* tano) {
	//Locker locker(_this.getReferenceUnsafeStaticCast());

	Locker _alocker(tano->getContainerLock());

	SortedVector<ManagedReference<ActiveArea* > > areas = *dynamic_cast<SortedVector<ManagedReference<ActiveArea* > >* >(tano->getActiveAreas());

	_alocker.release();

	Vector3 worldPos = tano->getWorldPosition();

	SortedVector<ManagedReference<QuadTreeEntry*> > entryObjects;

	Zone* managedRef = _this.getReferenceUnsafeStaticCast();

	bool readlock = !managedRef->isLockedByCurrentThread();

	managedRef->rlock(readlock);

	try {
		regionTree->inRange(worldPos.getX(), worldPos.getY(), entryObjects);
	} catch (...) {
		error("unexpeted error caught in void ZoneImplementation::updateActiveAreas(SceneObject* object) {");
	}

	managedRef->runlock(readlock);

	//locker.release();


	managedRef->unlock(!readlock);

	try {

		// update old ones
		for (int i = 0; i < areas.size(); ++i) {
			ManagedReference<ActiveArea*> area = areas.get(i);
//			Locker lockerO(object);

//			Locker locker(area, object);

			if (!area->containsPoint(worldPos.getX(), worldPos.getY(), tano->getParentID())) {
				tano->dropActiveArea(area);
				area->enqueueExitEvent(tano);
//				area->notifyExit(object);
			} else {
				area->notifyPositionUpdate(tano);
			}
		}

		// we update the ones in quadtree.
		for (int i = 0; i < entryObjects.size(); ++i) {
			//update in new ones
			ActiveArea* activeArea = dynamic_cast<ActiveArea*>(entryObjects.get(i).get());

			if (!tano->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getY(), tano->getParentID())) {
				//Locker lockerO(object);

				//Locker locker(activeArea, object);

				tano->addActiveArea(activeArea);
				activeArea->enqueueEnterEvent(tano);
				//activeArea->notifyEnter(object);
			}
		}

		// update world areas
		if (creatureManager != NULL) {
			Vector<ManagedReference<SpawnArea*> >* worldAreas = creatureManager->getWorldSpawnAreas();

			if (worldAreas != NULL) {
				for (int i = 0; i < worldAreas->size(); ++i) {
					ActiveArea* activeArea = worldAreas->get(i);
					Locker lockerO(tano);

					//			Locker locker(activeArea, object);

					if (!tano->hasActiveArea(activeArea)) {
						tano->addActiveArea(activeArea);
						//activeArea->enqueueEnterEvent(object);
						activeArea->notifyEnter(tano);
					} else {
						activeArea->notifyPositionUpdate(tano);
					}
				}
			}
		}
	} catch (...) {
		error("unexpected exception caught in void ZoneImplementation::updateActiveAreas(SceneObject* object) {");
		managedRef->wlock(!readlock);
		throw;
	}

	managedRef->wlock(!readlock);
}

void ZoneImplementation::addSceneObject(SceneObject* object) {
	SceneObject* old = objectMap->put(object->getObjectID(), object);

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
		if (controlledObject != NULL && controlledObject->isStructureObject()) {
			StructureObject* structure = controlledObject.castTo<StructureObject*>();
			if (structure->isCivicStructure())
				return;
		}
	} else if (old == NULL && object->isAiAgent()) {
		spawnedAiAgents.increment();
	}

	registerObjectWithPlanetaryMap(object);
}

//TODO: Do we need to send out some type of update when this happens?
void ZoneImplementation::registerObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->transferObject(object);
}

void ZoneImplementation::unregisterObjectWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->dropObject(object);
}

bool ZoneImplementation::isObjectRegisteredWithPlanetaryMap(SceneObject* object) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	return mapLocations->containsObject(object);
}

void ZoneImplementation::updatePlanetaryMapIcon(SceneObject* object, byte icon) {
#ifndef WITH_STM
	Locker locker(mapLocations);
#endif
	mapLocations->updateObjectsIcon(object, icon);
}

void ZoneImplementation::dropSceneObject(SceneObject* object)  {
	SceneObject* oldObject = objectMap->remove(object->getObjectID());

	unregisterObjectWithPlanetaryMap(object);

	if (oldObject != NULL && oldObject->isAiAgent()) {
		spawnedAiAgents.decrement();
	}
}

void ZoneImplementation::sendMapLocationsTo(SceneObject* player) {
	GetMapLocationsResponseMessage* gmlr = new GetMapLocationsResponseMessage(zoneName, mapLocations, player);
	player->sendMessage(gmlr);
}

Reference<SceneObject*> ZoneImplementation::getNearestPlanetaryObject(SceneObject* object, const String& mapObjectLocationType) {
	Reference<SceneObject*> planetaryObject = NULL;

#ifndef WITH_STM
	mapLocations->rlock();
#endif

	SortedVector<MapLocationEntry>& sortedVector = mapLocations->getLocation(mapObjectLocationType);

	float distance = 16000.f;

	for (int i = 0; i < sortedVector.size(); ++i) {
		SceneObject* obj = sortedVector.get(i).getObject();

		float objDistance = object->getDistanceTo(obj);

		if (objDistance < distance) {
			planetaryObject = obj;
			distance = objDistance;
		}
	}

#ifndef WITH_STM
	mapLocations->runlock();
#endif

	return planetaryObject;
}

SortedVector<ManagedReference<SceneObject*> > ZoneImplementation::getPlanetaryObjectList(const String& mapObjectLocationType) {
	SortedVector<ManagedReference<SceneObject*> > retVector;
	retVector.setNoDuplicateInsertPlan();

#ifndef WITH_STM
	mapLocations->rlock();
#endif

	try {
		SortedVector<MapLocationEntry>& entryVector = mapLocations->getLocation(mapObjectLocationType);

		for (int i = 0; i < entryVector.size(); ++i) {
			MapLocationEntry entry = entryVector.get(i);
			retVector.put(entry.getObject());
		}
	} catch (...) {

	}

#ifndef WITH_STM
	mapLocations->runlock();
#endif

	return retVector;
}

float ZoneImplementation::getMinX() {
	return planetManager->getTerrainManager()->getMin();
}

float ZoneImplementation::getMaxX() {
	return planetManager->getTerrainManager()->getMax();
}

float ZoneImplementation::getMinY() {
	return planetManager->getTerrainManager()->getMin();
}

float ZoneImplementation::getMaxY() {
	return planetManager->getTerrainManager()->getMax();
}

void ZoneImplementation::updateCityRegions() {
	info("scheduling updates for " + String::valueOf(cityRegionUpdateVector.size()) + " cities", true);

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

bool ZoneImplementation::isWithinBoundaries(const Vector3& position) {
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

float ZoneImplementation::getBoundingRadius() {
	return planetManager->getTerrainManager()->getMax();
}
