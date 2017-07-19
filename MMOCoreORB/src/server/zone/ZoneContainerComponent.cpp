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
#include "terrain/manager/TerrainManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/objects/pathfinding/NavArea.h"
#include "server/zone/objects/intangible/TheaterObject.h"

bool ZoneContainerComponent::insertActiveArea(Zone* newZone, ActiveArea* activeArea) const {
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
	SortedVector<QuadTreeEntry*> objects;
	float range = activeArea->getRadius() + 64;

	newZone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), range, &objects, false);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = static_cast<SceneObject*>(objects.get(i));

		TangibleObject* tano = object->asTangibleObject();

		if (tano == nullptr && activeArea->isNavArea()) {
			if (object->isStaticObjectClass()) {
				Vector3 worldPos = object->getWorldPosition();

				if (activeArea->containsPoint(worldPos.getX(), worldPos.getY())) {
					activeArea->enqueueEnterEvent(object);
				}
			}

			continue;
		} else if (tano == nullptr) {
			continue;
		}

		Vector3 worldPos = object->getWorldPosition();

		if (!tano->hasActiveArea(activeArea) && activeArea->containsPoint(worldPos.getX(), worldPos.getY())) {
			tano->addActiveArea(activeArea);
			activeArea->enqueueEnterEvent(object);
		}
	}

	auto navArea = activeArea->asNavArea();

	if (navArea) {
		navArea->setAreaTerrainHeight(newZone->getHeight(activeArea->getPositionX(), activeArea->getPositionY()));
	}

	newZone->addSceneObject(activeArea);

	return true;
}

bool ZoneContainerComponent::removeActiveArea(Zone* zone, ActiveArea* activeArea) const {
	if (zone == NULL)
		return false;

	ManagedReference<SceneObject*> thisLocker = activeArea;

	if (!activeArea->isInQuadTree())
		return false;

	Locker zoneLocker(zone);

	QuadTree* regionTree = zone->getRegionTree();

	regionTree->remove(activeArea);

	// lets remove the in range active areas of players
	SortedVector<QuadTreeEntry*> objects;
	float range = activeArea->getRadius() + 64;

	zone->getInRangeObjects(activeArea->getPositionX(), activeArea->getPositionY(), range, &objects, false);

	zone->dropSceneObject(activeArea);

	zoneLocker.release();

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = static_cast<SceneObject*>(objects.get(i));

		TangibleObject* tano = object->asTangibleObject();

		if (tano == nullptr && activeArea->isNavArea()) {
			if (object->isStaticObjectClass()) {
				Vector3 worldPos = object->getWorldPosition();

				if (activeArea->containsPoint(worldPos.getX(), worldPos.getY())) {
					activeArea->enqueueExitEvent(object);
				}
			}

			continue;
		} else if (tano == nullptr) {
			continue;
		}

		if (tano->hasActiveArea(activeArea)) {
			tano->dropActiveArea(activeArea);
			activeArea->enqueueExitEvent(object);
		}
	}

	activeArea->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, NULL, 0);

	activeArea->setZone(NULL);

	return true;
}

bool ZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	Zone* newZone = dynamic_cast<Zone*>(sceneObject);

	if (newZone == NULL)
		return false;

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
			object->setParent(NULL, false);

		if (parent->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(parent->getParent().get().get());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(object);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}
	} else {
		object->setParent(NULL, false);
	}

	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == NULL)
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());

	zone->insert(object);

	zone->inRange(object, ZoneServer::CLOSEOBJECTRANGE);

	TangibleObject* tanoObject = object->asTangibleObject();
	if (tanoObject != nullptr) {
		zone->updateActiveAreas(tanoObject);
	} else if (object->isStaticObjectClass()) {
		// hack to get around notifyEnter/Exit only working with tangible objects
		Vector3 worldPos = object->getWorldPosition();

		SortedVector<ManagedReference<NavArea*> > meshes;
		zone->getInRangeNavMeshes(worldPos.getX(), worldPos.getY(), &meshes, false);

		for(auto& mesh : meshes) {
			if (mesh->containsPoint(worldPos.getX(), worldPos.getY())) {
				mesh->enqueueEnterEvent(object);
			}
		}
	} else if (object->isTheaterObject()) {
		TheaterObject* theater = static_cast<TheaterObject*>(object);

		if (theater != NULL && theater->shouldFlattenTheater()) {
			zone->getPlanetManager()->getTerrainManager()->addTerrainModification(object->getWorldPositionX(), object->getWorldPositionY(), "terrain/poi_small.lay", object->getObjectID());
		}
	}

	SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(object->getObjectTemplate());

	if (objtemplate != NULL) {
		String modFile = objtemplate->getTerrainModificationFile();

		if (!modFile.isEmpty()) {
			newZone->getPlanetManager()->getTerrainManager()->addTerrainModification(object->getWorldPositionX(), object->getWorldPositionY(), modFile, object->getObjectID());
		}
	}

	zoneLocker.release();

	object->notifyInsertToZone(zone);

	object->notifyObservers(ObserverEventType::PARENTCHANGED, NULL);

	return true;
}


bool ZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) const {
	Zone* zone = dynamic_cast<Zone*>(sceneObject);

	if (object->isActiveArea())
		return removeActiveArea(zone, dynamic_cast<ActiveArea*>(object));

	ManagedReference<SceneObject*> parent = object->getParent().get();
	//SortedVector<ManagedReference<SceneObject*> >* notifiedSentObjects = sceneObject->getNotifiedSentObjects();

	try {
		Locker locker(object);

		if (zone == NULL)
			return false;

		object->debug("removing from zone");

		Locker zoneLocker(zone);

		if (parent != NULL) {
			parent->removeObject(object, NULL, false);
		} else
			zone->remove(object);
			
		Zone* oldZone = zone;
			
//		oldZone->dropSceneObject(object);
		
//		zoneLocker.release();

		auto closeObjects = object->getCloseObjects();

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
#ifdef COV_DEBUG
			object->info("Null closeobjects vector in ZoneContainerComponent::removeObject", true);
#endif
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
			SortedVector<ManagedReference<ActiveArea*> >* activeAreas = tano->getActiveAreas();

			while (activeAreas->size() > 0) {
				Locker _alocker(object->getContainerLock());

				ManagedReference<ActiveArea*> area = activeAreas->get(0);
				activeAreas->remove(0);

				_alocker.release();

				area->enqueueExitEvent(object);
			}
		} else if (object->isStaticObjectClass()) {
			SortedVector<ManagedReference<NavArea*> > meshes;
			oldZone->getInRangeNavMeshes(object->getPositionX(), object->getPositionY(), &meshes, true);

			for(auto& mesh : meshes) {
				if (mesh->containsPoint(object->getPositionX(), object->getPositionY())) {
					mesh->enqueueExitEvent(object);
				}
			}
		}

		SortedVector<ManagedReference<SceneObject*> >* childObjects = object->getChildObjects();

		//Remove all outdoor child objects from zone
		for (int i = 0; i < childObjects->size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

			if (outdoorChild == NULL)
				continue;

			if (outdoorChild->isInQuadTree()) {
				Locker locker(outdoorChild);

				outdoorChild->destroyObjectFromWorld(true);
			}
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

	object->debug("removed from zone");

	object->notifyRemoveFromZone();

	object->setZone(NULL);

	return true;
}
