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

SpaceZoneImplementation::SpaceZoneImplementation(ZoneProcessServer* serv, const String& name) : ZoneImplementation(serv, name) {
	octTree = new server::zone::OctTree(-8192, -8192, -8192, 8192, 8192, 8192);

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
	octTree = nullptr;
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

	octTree->insert(entry);

	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "Inserting object into Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/
}

void SpaceZoneImplementation::remove(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (entry->isInOctTree()) {
		octTree->remove(entry);

		/*
		SceneObject* sceneO = cast<SceneObject*>(entry);

		if (sceneO != nullptr)
			info(true) << "Removing object from Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
		*/
	}
}

void SpaceZoneImplementation::update(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	octTree->update(entry);

	/*
	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "Updating object in Octree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	*/
}

void SpaceZoneImplementation::inRange(TreeEntry* entry, float range) {
	octTree->safeInRange(entry, range);
}

void SpaceZoneImplementation::updateActiveAreas(TangibleObject* tano) {

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

		octTree->inRange(x, y, z, range, *objects);

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

			if (sceno->getGameObjectType() == SceneObjectType::FURNITURE) {
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

		octTree->inRange(x, y, z, range, *objects);

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

		octTree->inRange(x, y, z, range, *objects);

		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	} catch (...) {
		_this.getReferenceUnsafeStaticCast()->runlock(readlock);
	}

	return objects->size();
}

int SpaceZoneImplementation::getInRangePlayers(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* players) {
	Reference<SortedVector<ManagedReference<TreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<TreeEntry*> >();

	/*
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
	*/

	return players->size();
}

int SpaceZoneImplementation::getInRangeActiveAreas(float x, float z, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	return 0;
}

int SpaceZoneImplementation::getInRangeActiveAreas(float x, float z, float y, ActiveAreasVector* objects, bool readLockZone) {
	return 0;
}

/*

	Shared Functions

*/

bool SpaceZoneImplementation::isWithinBoundaries(const Vector3& position) {
	return false;
}

float SpaceZoneImplementation::getBoundingRadius() {
	return 0.0;
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
