/*
 * ZoneContainerComponent.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "ZoneContainerComponent.h"

#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"

bool ZoneContainerComponent::insertActiveArea(Zone* newZone, ActiveArea* activeArea) {
	if (newZone == NULL)
		return false;

	if (!activeArea->isDeplyoed())
		activeArea->deploy();

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
	float range = activeArea->getRadius() + 64;

	newZone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), range, &objects, false);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(objects.get(i).get());

		if (!object->isTangibleObject()) {
			continue;
		}

		TangibleObject* tano = cast<TangibleObject*>(object);
		Vector3 worldPos = object->getWorldPosition();

		if (!tano->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getY())) {
			tano->addActiveArea(activeArea);
			activeArea->enqueueEnterEvent(object);
		}
	}

	newZone->addSceneObject(activeArea);

	return true;
}

bool ZoneContainerComponent::removeActiveArea(Zone* zone, ActiveArea* activeArea) {
	if (zone == NULL)
		return false;

	ManagedReference<SceneObject*> thisLocker = activeArea;

	Locker zoneLocker(zone);

	QuadTree* regionTree = zone->getRegionTree();

	regionTree->remove(activeArea);

	// lets remove the in range active areas of players
	SortedVector<ManagedReference<QuadTreeEntry*> > objects;
	float range = activeArea->getRadius() + 64;

	zone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), range, &objects, false);

	zone->dropSceneObject(activeArea);

	zoneLocker.release();

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(objects.get(i).get());

	//	Locker olocker(object);

		if (!object->isTangibleObject()) {
			continue;
		}

		TangibleObject* tano = cast<TangibleObject*>(object);

		if (tano->hasActiveArea(activeArea)) {
			tano->dropActiveArea(activeArea);
			activeArea->enqueueExitEvent(object);
		}
	}

	activeArea->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, NULL, 0);

	activeArea->setZone(NULL);

	return true;
}

bool ZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow) {
	Zone* newZone = dynamic_cast<Zone*>(sceneObject);
	Zone* zone = object->getZone();

	if (object->isActiveArea())
		return insertActiveArea(newZone, dynamic_cast<ActiveArea*>(object));

	Locker zoneLocker(newZone);

	if (object->isInQuadTree() && newZone != zone) {
		object->error("trying to insert to zone an object that is already in a different quadtree");

		object->destroyObjectFromWorld(true);

		return false;

		//StackTrace::printStackTrace();
	}

	ManagedReference<SceneObject*> parent = object->getParent().get();

	if (parent != NULL/* && parent->isCellObject()*/) {
		uint64 parentID = object->getParentID();

		if (containmentType == -2)
			parent->removeObject(object, sceneObject, false);
		else
			parent->removeObject(object, sceneObject, true);

		if (object->getParent() != NULL && parent->containsChildObject(object))
			return false;
		else
			object->setParent(NULL);

		if (object->getParent() != NULL && parent->containsChildObject(object))
			return false;
		else
			object->setParent(NULL);

		if (parent->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(parent->getParent().get().get());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(object);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}
	} else {
		object->setParent(NULL);
	}

	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == NULL)
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());

	zone->insert(object);

	zone->inRange(object, 192);

	if (object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);

		zone->updateActiveAreas(tano);
	}

	SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(object->getObjectTemplate());

	if (objtemplate != NULL) {
		String modFile = objtemplate->getTerrainModificationFile();

		if (!modFile.isEmpty()) {
			newZone->getPlanetManager()->getTerrainManager()->addTerrainModification(object->getWorldPositionX(), object->getWorldPositionY(), modFile, object->getObjectID());
		}
	}

	object->notifyInsertToZone(zone);

	return true;
}


bool ZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) {
	Zone* zone = dynamic_cast<Zone*>(sceneObject);

	if (object->isActiveArea())
		return removeActiveArea(zone, dynamic_cast<ActiveArea*>(object));

	ManagedReference<SceneObject*> parent = object->getParent();
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
			
		Zone* oldZone = zone;
			
//		oldZone->dropSceneObject(object);
		
//		zoneLocker.release();

		SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = object->getCloseObjects();

		if (closeObjects != NULL) {
			try {
				while (closeObjects->size() > 0) {
					ManagedReference<QuadTreeEntry*> obj = closeObjects->get(0);

					if (obj != NULL && obj != object && obj->getCloseObjects() != NULL)
						obj->removeInRangeObject(object);

					object->removeInRangeObject((int) 0);
				}
			} catch (...) {
			}
		} else {
			object->info("Null closeobjects vector in ZoneContainerComponent::removeObject", true);
			SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

			zone->getInRangeObjects(object->getPositionX(), object->getPositionY(), 512, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				QuadTreeEntry* obj = closeSceneObjects.get(i);

				if (obj != NULL && obj != object && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(object);
			}
		}

//		Zone* oldZone = zone;
		zone = NULL;

		oldZone->dropSceneObject(object);

		SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(object->getObjectTemplate());

		if (objtemplate != NULL) {
			String modFile = objtemplate->getTerrainModificationFile();

			if (!modFile.isEmpty()) {
				oldZone->getPlanetManager()->getTerrainManager()->removeTerrainModification(object->getObjectID());
			}
		}

		zoneLocker.release();

		if (object->isTangibleObject()) {
			TangibleObject* tano = cast<TangibleObject*>(object);
			Vector<ManagedReference<ActiveArea*> >* activeAreas = tano->getActiveAreas();

			while (activeAreas->size() > 0) {
				Locker _alocker(object->getContainerLock());

				ManagedReference<ActiveArea*> area = activeAreas->get(0);
				activeAreas->remove(0);

				_alocker.release();

				area->enqueueExitEvent(object);
			}
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
