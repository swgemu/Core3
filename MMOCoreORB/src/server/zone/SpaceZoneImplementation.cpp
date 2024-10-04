/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/SpaceZone.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/InRangeObjectsVector.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "templates/SharedObjectTemplate.h"
#include "server/zone/ActiveAreaOctree.h"

// #define DEBUG_SPACE_AA

SpaceZoneImplementation::SpaceZoneImplementation(ZoneProcessServer* serv, const String& name) : ZoneImplementation(serv, name) {
	areaOctree = new server::zone::ActiveAreaOctree(-8192, -8192, -8192, 8192, 8192, 8192);
	octree = new server::zone::Octree(-8192, -8192, -8192, 8192, 8192, 8192);

	spaceManager = nullptr;

	String capName = name;
	capName = capName.replaceFirst("_", "");
	capName[0] = toupper(capName[0]);
	capName[5] = toupper(capName[5]);

	int numThreads = ConfigManager::instance()->getInt("Core3.SpaceZone.ThreadsDefault", 1);
	numThreads = ConfigManager::instance()->getInt("Core3.SpaceZone.Threads" + capName, numThreads);

	setLoggingName("SpaceZone " + name);

	if (numThreads != 1) {
		info(true) << "SpaceZone " << capName << " using " << numThreads << " threads.";
	}

	Core::getTaskManager()->initializeCustomQueue(zoneName, numThreads, true);
}

/*

	Zone Management

*/

void SpaceZoneImplementation::createContainerComponent() {
	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>("SpaceZoneContainerComponent");
}

void SpaceZoneImplementation::initializePrivateData() {
	spaceManager = new SpaceManager(_this.getReferenceUnsafeStaticCast(), processor);
}

void SpaceZoneImplementation::finalize() {
}

void SpaceZoneImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void SpaceZoneImplementation::startManagers() {
	spaceManager->initialize();

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	spaceManager->start();

	managersStarted = true;
}

void SpaceZoneImplementation::stopManagers() {
	info("Shutting down.. ", true);

	if (spaceManager != nullptr) {
		spaceManager->finalize();
		spaceManager = nullptr;
	}

	processor = nullptr;
	server = nullptr;
	objectMap = nullptr;
	octree = nullptr;
	areaOctree = nullptr;
}

void SpaceZoneImplementation::clearZone() {
	Locker zonelocker(_this.getReferenceUnsafeStaticCast());

	info("clearing space zone", true);

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

	info("space zone clear", true);
}

/*

	Object Management in Zone

*/

void SpaceZoneImplementation::insert(TreeEntry* entry) {
	if (entry == nullptr)
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	octree->insert(entry);

	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "Inserting object into Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/
}

void SpaceZoneImplementation::remove(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (entry->isInOctree()) {
		octree->remove(entry);

		/*
		SceneObject* sceneO = cast<SceneObject*>(entry);

		if (sceneO != nullptr)
			info(true) << "Removing object from Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
		*/
	}
}

void SpaceZoneImplementation::update(TreeEntry* entry) {
	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "Updating object in Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/

	Locker locker(_this.getReferenceUnsafeStaticCast());

	octree->update(entry);
}

void SpaceZoneImplementation::inRange(TreeEntry* entry, float range) {
	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "SpaceZoneImplementation::inRange - zone check: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/

	octree->safeInRange(entry, range);
}

void SpaceZoneImplementation::updateActiveAreas(TangibleObject* tano) {
	if (tano == nullptr) {
		return;
	}

	Locker _alocker(tano->getContainerLock());

	SortedVector<ManagedReference<ActiveArea* > > areas = *tano->getActiveAreas();

	_alocker.release();

	Vector3 worldPos = tano->getWorldPosition();

#ifdef DEBUG_SPACE_AA
	info(true) << "\n---------- SpaceZoneImplementation::updateActiveAreas called: " << tano->getDisplayedName() << " WorldPosition: " << worldPos.toString() << " ----------";
#endif

	SortedVector<ActiveArea*> entryObjects;

	Zone* managedRef = _this.getReferenceUnsafeStaticCast();

	bool readlock = !managedRef->isLockedByCurrentThread();

	managedRef->rlock(readlock);

	try {
		areaOctree->getActiveAreas(worldPos.getX(), worldPos.getZ(), worldPos.getY(), entryObjects);

	} catch (...) {
		error("unexpeted error caught in void SpaceZoneImplementation::updateActiveAreas(SceneObject* object) {");
	}

	managedRef->runlock(readlock);

	managedRef->unlock(!readlock);

#ifdef DEBUG_SPACE_AA
	info(true) << "updateActiveAreas -- areasSize: " << areas.size() << " TanO Pos: X = " << worldPos.getX() << " Z = " << worldPos.getZ() << " Y = " << worldPos.getY();
#endif

	try {
		// update old ones
		for (int i = 0; i < areas.size(); ++i) {
			ManagedReference<ActiveArea*>& area = areas.getUnsafe(i);

			if (area == nullptr)
				continue;

			if (!area->containsPoint(worldPos.getX(), worldPos.getZ(), worldPos.getY(), tano->getParentID())) {
				tano->dropActiveArea(area);
				area->enqueueExitEvent(tano);

#ifdef DEBUG_SPACE_AA
				info(true) << "updateActiveAreas -- Dropping area: " << area->getAreaName();
#endif
			} else {
#ifdef DEBUG_SPACE_AA
				info(true) << "updateActiveAreas -- Area position updated called for: " << area->getAreaName();
#endif

				area->notifyPositionUpdate(tano);
			}
		}

#ifdef DEBUG_SPACE_AA
		info(true) << "updateActiveAreas -- entryObjects size: " << entryObjects.size();
#endif

		// we update the ones in octree.
		for (int i = 0; i < entryObjects.size(); ++i) {
			//update in new ones
			ActiveArea* activeArea = static_cast<ActiveArea*>(entryObjects.getUnsafe(i));

			if (!tano->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getZ(), worldPos.getY(), tano->getParentID())) {
#ifdef DEBUG_SPACE_AA
				info(true) << "updateActiveAreas -- ADDING area: " << activeArea->getAreaName();
#endif

				tano->addActiveArea(activeArea);
				activeArea->enqueueEnterEvent(tano);
			}
		}
	} catch (...) {
		error("unexpected exception caught in void SpaceZoneImplementation::updateActiveAreas(SceneObject* object) {");
		managedRef->wlock(!readlock);
		throw;
	}

	managedRef->wlock(!readlock);

#ifdef DEBUG_SPACE_AA
	info(true) << "---------- END SpaceZoneImplementation::updateActiveAreas called ----------\n";
#endif
}

void SpaceZoneImplementation::addSceneObject(SceneObject* object) {
	ManagedReference<SceneObject*> old = objectMap->put(object->getObjectID(), object);

	if (old == nullptr && object->isShipAiAgent()) {
		spawnedAiAgents.increment();
	}
}

void SpaceZoneImplementation::dropSceneObject(SceneObject* object)  {
	ManagedReference<SceneObject*> oldObject = objectMap->remove(object->getObjectID());

	if (oldObject != nullptr && object->isShipAiAgent()) {
		spawnedAiAgents.decrement();
	}
}

/*

	Object Tracking

*/

int SpaceZoneImplementation::getInRangeSolidObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		octree->inRange(x, y, z, range, *objects);

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

int SpaceZoneImplementation::getInRangeObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone, bool includeBuildingObjects) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		octree->inRange(x, y, z, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	return objects->size();
}

int SpaceZoneImplementation::getInRangeObjects(float x, float z, float y, float range, InRangeObjectsVector* objects, bool readLockZone, bool includeBuildingObjects) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	try {
		_this.getReferenceUnsafeStaticCast()->rlock(readlock);

		octree->inRange(x, y, z, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	return objects->size();
}

int SpaceZoneImplementation::getInRangePlayers(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* players) {
	Reference<SortedVector<ManagedReference<TreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<TreeEntry*> >();

	getInRangeObjects(x, z, y, range, closeObjects, true);

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

int SpaceZoneImplementation::getInRangeActiveAreas(float x, float z, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		areaOctree->getActiveAreas(x, z, y, *objects);

		thisZone->runlock(readlock);
	} catch (...) {
		thisZone->runlock(readlock);

		throw;
	}

	return objects->size();
}

int SpaceZoneImplementation::getInRangeActiveAreas(float x, float z, float y, ActiveAreasVector* objects, bool readLockZone) {
	objects->setNoDuplicateInsertPlan();

	bool readlock = readLockZone && !_this.getReferenceUnsafeStaticCast()->isLockedByCurrentThread();

	Zone* thisZone = _this.getReferenceUnsafeStaticCast();

	try {
		thisZone->rlock(readlock);

		areaOctree->getActiveAreas(x, z, y, *objects);

		thisZone->runlock(readlock);
	} catch (...) {
		thisZone->runlock(readlock);

		throw;
	}

	return objects->size();
}

/*

	Shared Functions

*/

bool SpaceZoneImplementation::isWithinBoundaries(const Vector3& position) {
	bool runTestX = (position.getX() >= -8192 && position.getX() < 8192);
	bool runTestY = (position.getY() >= -8192 && position.getY() < 8192);
	bool runTestZ = (position.getZ() >= -8192 && position.getZ() < 8192);

	return runTestX && runTestY && runTestZ;
}

float SpaceZoneImplementation::getBoundingRadius() {
	return 0.5;
}

float SpaceZoneImplementation::getZoneObjectRange() {
	return ZoneServer::SPACEOBJECTRANGE;
}

SpaceZone* SpaceZoneImplementation::asSpaceZone() {
	return _this.getReferenceUnsafeStaticCast();
}

SpaceZone* SpaceZone::asSpaceZone() {
	return this;
}
