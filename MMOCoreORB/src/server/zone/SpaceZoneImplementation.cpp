/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/SpaceZone.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/InRangeObjectsVector.h"
#include "server/zone/managers/components/ComponentManager.h"

#include "server/zone/objects/cell/CellObject.h"
#include "templates/SharedObjectTemplate.h"
/// TEST

SpaceZoneImplementation::SpaceZoneImplementation(ZoneProcessServer* serv, const String& name) {
	processor = serv;
	server = processor->getZoneServer();

	zoneName = name;
	zoneCRC = name.hashCode();
	octTree = new server::zone::OctTree(-8192, -8192, -8192, 8192, 8192, 8192);

	objectMap = new ObjectMap();

	managersStarted = false;
	zoneCleared = false;

	//galacticTime = new Time();

	spaceManager = nullptr;

	setLoggingName("Space Zone " + name);

	Core::getTaskManager()->initializeCustomQueue(zoneName, 1, true);
}

void SpaceZoneImplementation::createContainerComponent() {
	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>("SpaceZoneContainerComponent");
}

void SpaceZoneImplementation::initializePrivateData() {
	spaceManager = new SpaceManager(_this.getReferenceUnsafeStaticCast(), processor);
}

void SpaceZoneImplementation::finalize() {
	//System::out << "deleting height map\n";
}

void SpaceZoneImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void SpaceZoneImplementation::startManagers() {
	spaceManager->initialize();
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

void SpaceZoneImplementation::insert(TreeEntry* entry) {
	if (entry == nullptr)
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	octTree->insert(entry);

	SceneObject* sceneO = cast<SceneObject*>(entry);

	if (sceneO != nullptr)
		info(true) << "Inserting object into Oct Tree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
}

void SpaceZoneImplementation::remove(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (entry->isInOctTree()) {
		octTree->remove(entry);

		SceneObject* sceneO = cast<SceneObject*>(entry);

		if (sceneO != nullptr)
			info(true) << "Removing object from Oct Tree: " + sceneO->getDisplayedName() << " ID: " << sceneO->getObjectID();
	}
}

void SpaceZoneImplementation::update(TreeEntry* entry) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	octTree->update(entry);
}

void SpaceZoneImplementation::inRange(TreeEntry* entry, float range) {
	octTree->safeInRange(entry, range);
}

int SpaceZoneImplementation::getInRangeSolidObjects(float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {
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

int SpaceZoneImplementation::getInRangeObjects(float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {
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

int SpaceZoneImplementation::getInRangeObjects(float x, float y, float z, float range, InRangeObjectsVector* objects, bool readLockZone) {
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

float SpaceZoneImplementation::getMinX() {
	return planetManager->getTerrainManager()->getMin();
}

float SpaceZoneImplementation::getMaxX() {
	return planetManager->getTerrainManager()->getMax();
}

float SpaceZoneImplementation::getMinY() {
	return planetManager->getTerrainManager()->getMin();
}

float SpaceZoneImplementation::getMaxY() {
	return planetManager->getTerrainManager()->getMax();
}

float SpaceZoneImplementation::getMinZ() {
	return planetManager->getTerrainManager()->getMin();
}

float SpaceZoneImplementation::getMaxZ() {
	return planetManager->getTerrainManager()->getMax();
}

bool SpaceZoneImplementation::isWithinBoundaries(const Vector3& position) {
	//Remove 1/16th of the size to match client limits. NOTE: it has not been verified to work like this in the client.
	//Normal zone size is 8192, 1/16th of that is 512 resulting in 7680 as the boundary value.
	float maxX = getMaxX() * 15 / 16;
	float minX = getMinX() * 15 / 16;
	float maxY = getMaxY() * 15 / 16;
	float minY = getMinY() * 15 / 16;
	float maxZ = getMaxZ() * 15 / 16;
	float minZ = getMinZ() * 15 / 16;

	if (maxX >= position.getX() && minX <= position.getX() &&
			maxY >= position.getY() && minY <= position.getY() &&
				maxZ >= position.getZ() && minZ <= position.getZ())
			 {
		return true;
	} else {
		return false;
	}
}

void SpaceZoneImplementation::addSceneObject(SceneObject* object) {
	ManagedReference<SceneObject*> old = objectMap->put(object->getObjectID(), object);
}

void SpaceZoneImplementation::dropSceneObject(SceneObject* object)  {
	ManagedReference<SceneObject*> oldObject = objectMap->remove(object->getObjectID());
}