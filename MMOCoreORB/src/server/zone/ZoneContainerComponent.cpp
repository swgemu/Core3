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

		activeArea->removeFromZone();

		//StackTrace::printStackTrace();
	}

	activeArea->setZone(newZone);

	QuadTree* regionTree = newZone->getRegionTree();

	regionTree->insert(activeArea);

	regionTree->inRange(activeArea, 512);

	// lets update area to the in range players
	SortedVector<ManagedReference<SceneObject*> > objects;

	newZone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), 512, &objects);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = objects.get(i);

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

	while (activeArea->inRangeObjectCount() > 0) {
		QuadTreeEntry* obj = activeArea->getInRangeObject(0);

		if (obj != activeArea)
			obj->removeInRangeObject(activeArea);

		activeArea->removeInRangeObject((int)0);
	}

	// lets remove the in range active areas of players
	SortedVector<ManagedReference<SceneObject*> > objects;

	zone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), 512, &objects);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = objects.get(i);

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

bool ZoneContainerComponent::addObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient) {
	Zone* newZone = dynamic_cast<Zone*>(sceneObject);
	Zone* zone = object->getZone();

	if (object->isActiveArea())
		return insertActiveArea(newZone, dynamic_cast<ActiveArea*>(object));

	Vector<ManagedReference<ActiveArea*> >* activeAreas = object->getActiveAreas();

	activeAreas->removeAll();

	Locker zoneLocker(newZone);

	if (object->isInQuadTree() && newZone != zone) {
		object->error("trying to insert to zone an object that is already in a different quadtree");

		object->removeFromZone();

		return false;

		//StackTrace::printStackTrace();
	}

	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	SceneObject* parent = object->getParent();

	if (parent != NULL && parent->isCellObject())
		parent->addObject(object, -1, false);

	/*SortedVector<ManagedReference<SceneObject*> >* notifiedSentObjects = sceneObject->getNotifiedSentObjects();

		notifiedSentObjects->removeAll();*/

	object->sendToOwner(true);

	if (object->isInQuadTree()) {
		for (int i = 0; i < object->inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) object->getInRangeObject(i);

			if (obj != object->getRootParent()) //our building is sent in sendToOwner
				object->notifyInsert(obj);

			if (obj != object) {
				/*if (object->getParentRecursively(SceneObject::BUILDING) != NULL) {
						if (notifiedSentObjects->put(object) != -1)
							object->sendTo(sceneObject, true);
					}*/

				if (obj->isPlayerCreature()) { //we need to destroy object to reset movement counter on near clients
					obj->notifyDissapear(object);
					//object->sendTo(sceneObject, true);
					object->sendTo(obj, true);
				} else
					obj->notifyInsert(object);
			}
		}
	} else {
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());
		object->removeInRangeObjects();

		//movementCounter = 0;
		object->setMovementCounter(0);

		if (parent == NULL || !parent->isCellObject() || parent->getParent() == NULL) {
			zone->insert(object);

			zone->inRange(object, 192);
		} else if (parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();
			object->insertToBuilding(building);

			building->notifyObjectInsertedToZone(object);
		}
	}

	zone->updateActiveAreas(object);

	object->notifyInsertToZone(zone);

	return true;
}


bool ZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, bool notifyClient) {
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

		//ManagedReference<SceneObject*> par = parent.get();

		if (parent != NULL && parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*)parent->getParent();

			//par = parent;
			if (building != NULL)
				object->removeFromBuilding(building);
			else
				zone->remove(object);
		} else
			zone->remove(object);

		while (object->inRangeObjectCount() > 0) {
			QuadTreeEntry* obj = object->getInRangeObject(0);

			if (obj != object)
				obj->removeInRangeObject(object);

			object->removeInRangeObject((int) 0);
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

			outdoorChild->removeFromZone();
		}

		//removeInRangeObjects();

		//notifiedSentObjects->removeAll();

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
		//objectActiveSessions.remove(0);
	}

	//activeAreas.removeAll();

	object->info("removed from zone");

	object->notifyRemoveFromZone();

	return true;
}
