/*
 * SpaceZoneContainerComponent.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "SpaceZoneContainerComponent.h"

#include "server/zone/SpaceZone.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/objects/intangible/TheaterObject.h"

bool SpaceZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	SpaceZone* newZone = dynamic_cast<SpaceZone*>(sceneObject);

//	Logger::console.info("spaceZone transferObject", true);

	if (newZone == nullptr)
		return false;

	SpaceZone* zone = object->getSpaceZone();
/*
	if (object->isActiveArea())
		return insertActiveArea(newZone, dynamic_cast<ActiveArea*>(object));
*/
	Locker zoneLocker(newZone);

	if (object->isInOctTree() && newZone != zone) {
		object->error("trying to insert to zone an object that is already in a different octtree");

		object->destroyObjectFromWorld(true);

		return false;

		//StackTrace::printStackTrace();
	}

	ManagedReference<SceneObject*> parent = object->getParent().get();

	if (parent != nullptr/* && parent->isCellObject()*/) {
		uint64 parentID = object->getParentID();

		if (containmentType == -2)
			parent->removeObject(object, sceneObject, false);
		else
			parent->removeObject(object, sceneObject, true);

		if (object->getParent() != nullptr && parent->containsChildObject(object))
			return false;
		else
			object->setParent(nullptr, false);

		if (parent->isCellObject()) {
			// Ship Object?
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
///here
	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == nullptr)
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());

	zone->insert(object);

	zone->inRange(object, ZoneServer::SPACEOBJECTRANGE);

	zoneLocker.release();

	object->notifyInsertToZone(zone);

	object->notifyObservers(ObserverEventType::PARENTCHANGED, nullptr);

	return true;
}

bool SpaceZoneContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) const {

	SpaceZone* zone = dynamic_cast<SpaceZone*>(sceneObject);

	ManagedReference<SceneObject*> parent = object->getParent().get();

	try {
		Locker locker(object);

		if (zone == nullptr)
			return false;

		object->debug("removing from space zone");

		Locker zoneLocker(zone);

		if (parent != nullptr) {
			parent->removeObject(object, nullptr, false);
		} else
			zone->remove(object);

		SpaceZone* oldZone = zone;

		auto closeObjects = object->getCloseObjects();

		if (closeObjects != nullptr) {
			SortedVector<ManagedReference<TreeEntry*> > closeSceneObjects;

			ZoneComponent::removeAllObjectsFromCOV(closeObjects, closeSceneObjects, sceneObject, object);
		} else {
#ifdef COV_DEBUG
			object->info("Null closeobjects vector in SpaceZoneContainerComponent::removeObject", true);
#endif
			SortedVector<ManagedReference<TreeEntry*> > closeSceneObjects;

			zone->getInRangeObjects(object->getPositionX(), object->getPositionY(), object->getPositionZ(), 512, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				TreeEntry* obj = closeSceneObjects.get(i);

				if (obj != nullptr && obj != object && obj->getCloseObjects() != nullptr)
					obj->removeInRangeObject(object);
			}
		}

		zone = nullptr;

		oldZone->dropSceneObject(object);

		zoneLocker.release();

		SortedVector<ManagedReference<SceneObject*> >* childObjects = object->getChildObjects();

		//Remove all outdoor child objects from zone
		for (int i = 0; i < childObjects->size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

			if (outdoorChild == nullptr)
				continue;

			if (outdoorChild->isInOctTree()) {
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
