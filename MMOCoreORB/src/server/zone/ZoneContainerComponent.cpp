/*
 * ZoneContainerComponent.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "ZoneContainerComponent.h"

#include "Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/area/ActiveArea.h"

bool ZoneContainerComponent::insertActiveArea(Zone* newZone, ActiveArea* activeArea) {
	if (newZone == NULL)
		return false;

	Zone* zone = activeArea->getZone();

	ManagedReference<SceneObject*> thisLocker = activeArea;

	Locker zoneLocker(newZone);

	if (activeArea->isInQuadTree() && newZone != zone) {
		activeArea->error("trying to insert to zone an object that is already in a different quadtree");

		activeArea->destroyObjectFromWorld(true);

		//StackTrace::printStackTrace();
	}

	activeArea->setZone(newZone);

	QuadTree* regionTree = newZone->getRegionTree();

	regionTree->insert(activeArea);

	//regionTree->inRange(activeArea, 512);

	// lets update area to the in range players
	SortedVector<ManagedReference<QuadTreeEntry*> > objects;

	newZone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), 512, &objects, false);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(objects.get(i).get());

		Vector3 worldPos = object->getWorldPosition();

		if (!object->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getY())) {
			object->addActiveArea(activeArea);
			activeArea->enqueueEnterEvent(object);
		}
	}

	newZone->addSceneObject(activeArea);

	activeArea->notifyInsertToZone(zone);

	return true;
}

bool ZoneContainerComponent::removeActiveArea(Zone* zone, ActiveArea* activeArea) {
	if (zone == NULL)
		return false;

	ManagedReference<SceneObject*> thisLocker = activeArea;

	Locker zoneLocker(zone);

	QuadTree* regionTree = zone->getRegionTree();

	regionTree->remove(activeArea);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = activeArea->getCloseObjects();

	if (closeObjects != NULL) {
		while (closeObjects->size() > 0) {
			QuadTreeEntry* obj = closeObjects->get(0);

			if (obj != activeArea && obj->getCloseObjects() != NULL)
				obj->removeInRangeObject(activeArea);

			activeArea->removeInRangeObject((int)0);
		}
	}

	// lets remove the in range active areas of players
	SortedVector<ManagedReference<QuadTreeEntry*> > objects;

	zone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), 512, &objects, false);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(objects.get(i).get());

		if (object->hasActiveArea(activeArea)) {
			object->dropActiveArea(activeArea);
			activeArea->enqueueExitEvent(object);
		}
	}

	activeArea->setZone(NULL);

	zone->dropSceneObject(activeArea);

	activeArea->notifyRemoveFromZone();

	return true;
}

bool ZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient) {
	Zone* newZone = dynamic_cast<Zone*>(sceneObject);
	Zone* zone = object->getZone();

	if (object->isActiveArea())
		return insertActiveArea(newZone, dynamic_cast<ActiveArea*>(object));

	Vector<ManagedReference<ActiveArea*> >* activeAreas = object->getActiveAreas();

	activeAreas->removeAll();

	Locker zoneLocker(newZone);

	if (object->isInQuadTree() && newZone != zone) {
		object->error("trying to insert to zone an object that is already in a different quadtree");

		object->destroyObjectFromWorld(true);

		return false;

		//StackTrace::printStackTrace();
	}

	ManagedReference<SceneObject*> parent = object->getParent();

	if (parent != NULL/* && parent->isCellObject()*/) {
		uint64 parentID = object->getParentID();
		parent->removeObject(object, sceneObject, true);

		if (parent->isCellObject()) {
			BuildingObject* build = cast<BuildingObject*>(parent->getParent());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(object);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}
	}

	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == NULL)
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());

	zone->insert(object);

	zone->inRange(object, 512);

	zone->updateActiveAreas(object);

	object->notifyInsertToZone(zone);

	return true;
}


bool ZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) {
	Zone* zone = dynamic_cast<Zone*>(sceneObject);

	if (object->isActiveArea())
		return removeActiveArea(zone, dynamic_cast<ActiveArea*>(object));

	SceneObject* parent = object->getParent();
	Vector<ManagedReference<ActiveArea*> >* activeAreas = object->getActiveAreas();
	//SortedVector<ManagedReference<SceneObject*> >* notifiedSentObjects = sceneObject->getNotifiedSentObjects();

	try {
		Locker locker(object);

		if (zone == NULL)
			return false;

		object->info("removing from zone");

		Locker zoneLocker(zone);

		if (parent != NULL) {
			parent->removeObject(object, NULL, false);
		} else
			zone->remove(object);

		SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = object->getCloseObjects();

		if (closeObjects != NULL) {
			while (closeObjects->size() > 0) {
				ManagedReference<QuadTreeEntry*> obj = closeObjects->get(0);

				if (obj != object && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(object);

				object->removeInRangeObject((int) 0);
			}
		} else {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

			zone->getInRangeObjects(object->getPositionX(), object->getPositionY(), 512, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				QuadTreeEntry* obj = closeSceneObjects.get(i);

				if (obj != object && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(object);
			}
		}

		while (activeAreas->size() > 0) {
			ManagedReference<ActiveArea*> area = activeAreas->get(0);
			area->enqueueExitEvent(object);

			activeAreas->remove(0);
		}

		SortedVector<ManagedReference<SceneObject*> >* childObjects = object->getChildObjects();

		//Remove all outdoor child objects from zone
		for (int i = 0; i < childObjects->size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

			if (outdoorChild == NULL)
				continue;

			if (outdoorChild->isInQuadTree())
				outdoorChild->destroyObjectFromWorld(true);
		}

		Zone* oldZone = zone;
		zone = NULL;

		oldZone->dropSceneObject(object);
	} catch (Exception& e) {

	}

	object->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, NULL, 0);

	VectorMap<uint32, ManagedReference<Facade*> >* objectActiveSessions = object->getObjectActiveSessions();

	while (objectActiveSessions->size()) {
		ManagedReference<Facade*> facade = objectActiveSessions->remove(0).getValue();

		if (facade == NULL)
			continue;

		facade->cancelSession();
	}

	//activeAreas.removeAll();

	object->info("removed from zone");

	object->notifyRemoveFromZone();

	object->setZone(NULL);

	return true;
}
