/*
 * SpaceZoneContainerComponent.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "SpaceZoneContainerComponent.h"

#include "server/zone/SpaceZone.h"
#include "server/zone/ActiveAreaOctree.h"
#include "server/zone/objects/building/BuildingObject.h"


bool SpaceZoneContainerComponent::insertActiveArea(Zone* newZone, ActiveArea* activeArea) const {
	if (newZone == nullptr || activeArea == nullptr) {
		return false;
	}

	// newZone->info(true) << "SpaceZoneContainerComponent::insertActiveArea -- ActiveArea: " << activeArea->getAreaName();

	if (!activeArea->isDeployed()) {
		activeArea->deploy();
	}

	Zone* zone = activeArea->getZone();

	ManagedReference<SceneObject*> thisLocker = activeArea;

	Locker zoneLocker(newZone);

	if (zone != nullptr && newZone != zone) {
		activeArea->error("trying to insert area to a different zone areaOctree than its current zone");

		activeArea->destroyObjectFromWorld(true);
	}

	activeArea->setZone(newZone);

	auto areaOctree = newZone->getActiveAreaOctree();

	areaOctree->insert(activeArea);

	// lets update area to the in range players
	SortedVector<TreeEntry*> objects;
	float range = activeArea->getRadius() + 1024;

	newZone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionZ(), activeArea->getPositionY(), range, &objects, false);

	// newZone->info(true) << "SpaceZoneContainerComponent::insertActiveArea -- total in range objects: " << objects.size();

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = static_cast<SceneObject*>(objects.get(i));

		if (object == nullptr || !object->isTangibleObject())
			continue;

		TangibleObject* tano = object->asTangibleObject();

		if (tano == nullptr) {
			continue;
		}

		Vector3 worldPos = tano->getWorldPosition();

		if (!activeArea->containsPoint(worldPos.getX(), worldPos.getZ(), worldPos.getY()))
			continue;

		if (!tano->hasActiveArea(activeArea)) {
			tano->addActiveArea(activeArea);
			activeArea->enqueueEnterEvent(object);
		}
	}

	// info(true) << newZone->getZoneName() << " -- Inserted Active area: " << activeArea->getAreaName() << " Location: " << activeArea->getAreaCenter().toString();

	newZone->addSceneObject(activeArea);

	return true;
}

bool SpaceZoneContainerComponent::removeActiveArea(Zone* zone, ActiveArea* activeArea) const {
	if (activeArea == nullptr)
		return false;

	if (zone == nullptr) {
		activeArea->error("trying to remove activeArea from a null space zone");
		return false;
	}

	if (zone != activeArea->getZone())
		activeArea->error("trying to remove activeArea from the wrong zone areaTree");

	ManagedReference<SceneObject*> thisLocker = activeArea;

	Locker zoneLocker(zone);

	auto areaOctree = zone->getActiveAreaOctree();

	areaOctree->remove(activeArea);

	// Remove active area from in range objects
	SortedVector<TreeEntry*> objects;
	float range = activeArea->getRadius() + 500;

	zone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionZ(), activeArea->getPositionY(), range, &objects, false);

	zone->dropSceneObject(activeArea);

	zoneLocker.release();

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = static_cast<SceneObject*>(objects.get(i));

		if (object == nullptr || !object->isTangibleObject())
			continue;

		TangibleObject* tano = object->asTangibleObject();

		if (tano == nullptr)
			continue;

		if (!tano->hasActiveArea(activeArea))
			continue;


		tano->dropActiveArea(activeArea);
		activeArea->enqueueExitEvent(object);
	}

	activeArea->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, nullptr, 0);

	activeArea->setZone(nullptr);

	return true;
}


bool SpaceZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	if (sceneObject == nullptr) {
		return false;
	}

	auto newSpaceZone = sceneObject->asSpaceZone();

	if (newSpaceZone == nullptr) {
		return false;
	}

	// newSpaceZone->info(true) << "SpaceZoneContainerComponent::transferObject -- Object: " << object->getDisplayedName() << "  Containment Type: " << containmentType;

	auto zone = object->getZone();

	if (object->isActiveArea())
		return insertActiveArea(newSpaceZone, dynamic_cast<ActiveArea*>(object));

	Locker zoneLocker(newSpaceZone);

	if (object->isInOctree() && newSpaceZone != zone) {
		object->error() << "trying to insert object to newSpaceZone but is already in another space zone";

		object->destroyObjectFromWorld(true);
		//StackTrace::printStackTrace();

		return false;
	}

	ManagedReference<SceneObject*> parent = object->getParent().get();

	if (parent != nullptr) {
		uint64 parentID = object->getParentID();

		if (containmentType == -2)
			parent->removeObject(object, sceneObject, false);
		else
			parent->removeObject(object, sceneObject, true);

		if (parent != nullptr && parent->containsChildObject(object))
			return false;
		else
			object->setParent(nullptr, false);

		if (parent->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(parent->getParent().get().get());

			if (build != nullptr) {
				CreatureObject* creature = cast<CreatureObject*>(object);

				if (creature != nullptr)
					build->onExit(creature, parentID);
			}
		}
	} else {
		object->setParent(nullptr, false);
	}

	object->setZone(newSpaceZone);

	newSpaceZone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == nullptr) {
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());
	}

	// Inserts object into the Octree node for its given location
	newSpaceZone->insert(object);

	// Updates objects in range
	newSpaceZone->inRange(object, ZoneServer::SPACESTATIONRANGE);

	TangibleObject* tanoObject = object->asTangibleObject();

	if (tanoObject != nullptr) {
		newSpaceZone->updateActiveAreas(tanoObject);
	}

	zoneLocker.release();

	if (notifyClient) {
		object->notifyInsertToZone(newSpaceZone);
	}

	object->notifyObservers(ObserverEventType::PARENTCHANGED, nullptr);

	return true;
}

bool SpaceZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient, bool nullifyParent) const {
	SpaceZone* spaceZone = sceneObject->asSpaceZone();

	if (object->isActiveArea())
		return removeActiveArea(spaceZone, dynamic_cast<ActiveArea*>(object));

	ManagedReference<SceneObject*> parent = object->getParent().get();

	try {
		Locker locker(object);

		if (spaceZone == nullptr)
			return false;

		object->debug("removing from space zone");

		Locker zoneLocker(spaceZone);

		if (parent != nullptr) {
			parent->removeObject(object, nullptr, false);
		} else
			spaceZone->remove(object);

		SpaceZone* oldZone = spaceZone;

		auto closeObjects = object->getCloseObjects();

		if (closeObjects != nullptr) {
			SortedVector<ManagedReference<TreeEntry*> > closeSceneObjects;

			SpaceZoneComponent::removeAllObjectsFromCOV(closeObjects, closeSceneObjects, sceneObject, object);
		} else {
#ifdef COV_DEBUG
			object->info("Null closeobjects vector in SpaceZoneContainerComponent::removeObject", true);
#endif
			SortedVector<ManagedReference<TreeEntry*> > closeSceneObjects;

			// Updates objects in range
			spaceZone->getInRangeObjects(object->getPositionX(), object->getPositionZ(), object->getPositionY(), ZoneServer::SPACESTATIONRANGE, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				TreeEntry* obj = closeSceneObjects.get(i);

				if (obj != nullptr && obj != object && obj->getCloseObjects() != nullptr)
					obj->removeInRangeObject(object);
			}
		}

		spaceZone = nullptr;

		oldZone->dropSceneObject(object);

		zoneLocker.release();

		SortedVector<ManagedReference<SceneObject*> >* childObjects = object->getChildObjects();

		//Remove all outdoor child objects from zone
		for (int i = 0; i < childObjects->size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

			if (outdoorChild == nullptr)
				continue;

			if (outdoorChild->isInOctree()) {
				Locker locker(outdoorChild);

				outdoorChild->destroyObjectFromWorld(true);
			}
		}

	} catch (Exception& e) {
		object->error("exception in SpaceZoneContainerComponent::removeObject: " + e.getMessage());
	}

	object->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, nullptr, 0);

	VectorMap<uint32, ManagedReference<Facade*> >* objectActiveSessions = object->getObjectActiveSessions();

	while (objectActiveSessions->size()) {
		ManagedReference<Facade*> facade = objectActiveSessions->remove(0).getValue();

		if (facade == nullptr)
			continue;

		facade->cancelSession();
	}

	object->debug("removed from zone");

	object->notifyRemoveFromZone();

	object->setZone(nullptr);

	return true;
}
