/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "SpaceZoneComponent.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "templates/params/creature/PlayerArrangement.h"

void SpaceZoneComponent::notifyInsertToZone(SceneObject* sceneObject, SpaceZone* newSpaceZone) const {
	if (newSpaceZone == nullptr)
		return;

	sceneObject->teleport(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), sceneObject->getParentID());

	insertChildObjectsToZone(sceneObject, newSpaceZone);
}

void SpaceZoneComponent::insertChildObjectsToZone(SceneObject* sceneObject, SpaceZone* spaceZone) const {
	SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();

	for (int i = 0; i < childObjects->size(); ++i) {
		ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

		if (outdoorChild == nullptr)
			continue;

		if (outdoorChild->getContainmentType() != 4 && outdoorChild->getParent() == nullptr) {
			Locker clocker(outdoorChild, sceneObject);

			spaceZone->transferObject(outdoorChild, -1, true);
		}
	}
}

void SpaceZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) const {
	ZoneServer* zoneServer = sceneObject->getZoneServer();
	SpaceZone* spaceZone = sceneObject->getSpaceZone();

	if (spaceZone == nullptr)
		return;

	if (parentID != 0) {
		Reference<SceneObject*> newParent = zoneServer->getObject(parentID);

		if (newParent == nullptr || !newParent->isCellObject())
			return;

		if (newPositionX != sceneObject->getPositionX() || newPositionZ != sceneObject->getPositionZ() || newPositionY != sceneObject->getPositionY()) {
			sceneObject->setPosition(newPositionX, newPositionZ, newPositionY);
			sceneObject->updateZoneWithParent(newParent, false, false);
		}

		//sceneObject->incrementMovementCounter();

		DataTransformWithParent* pack = new DataTransformWithParent(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	} else {
		if (newPositionX != sceneObject->getPositionX() || newPositionZ != sceneObject->getPositionZ() || newPositionY != sceneObject->getPositionY()) {
			sceneObject->setPosition(newPositionX, newPositionZ, newPositionY);
			sceneObject->updateZone(false, false);
		}

		//sceneObject->incrementMovementCounter();

		DataTransform* pack = new DataTransform(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	}
}

void SpaceZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) const {
	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

	Zone* zone = sceneObject->getZone();
	ManagedReference<SceneObject*> sceneObjectRootParent = sceneObject->getRootParent();

	if (zone == nullptr) {
		if (sceneObjectRootParent == nullptr)
			return;

		zone = sceneObjectRootParent->getZone();
	}

	if (zone == nullptr || !zone->isSpaceZone())
		return;

	SpaceZone* spaceZone = cast<SpaceZone*>(zone);

	if (spaceZone == nullptr)
		return;

	Locker _locker(spaceZone);
	bool zoneUnlocked = false;

	/*
	// in POB ship or spacestation?
	if (parent != nullptr && parent->isCellObject()) {
		SceneObject* rootParent = parent->getRootParent();

		if (rootParent == nullptr)
			return;

		spaceZone = rootParent->getZone();
		spaceZone->transferObject(sceneObject, -1, false);
		spaceZone->unlock();
		zoneUnlocked = true;
	} else {
		// Normal Ship
	*/

		/*if (parent != nullptr && parent->isShipObject()) {
			spaceZone->update(parent);
			spaceZone->inRange(parent, ZoneServer::SPACEOBJECTRANGE);
		} else */

	try {
		if (sceneObject->isShipObject()) {
			spaceZone->update(sceneObject);
			spaceZone->inRange(sceneObject, ZoneServer::SPACEOBJECTRANGE);

			ShipObject* ship = sceneObject->asShipObject();

			if (ship != nullptr) {
				SceneObject* pilot = nullptr;

				if (ship->getPilotChair().get() != nullptr) {
					SceneObject* pilotChair = ship->getPilotChair().get();

					if (pilotChair != nullptr)
						pilot = pilotChair->getSlottedObject("ship_pilot_pob");
				} else {
					pilot = sceneObject->getSlottedObject("ship_pilot");
				}

				if (pilot != nullptr) {
					spaceZone->update(pilot);
					spaceZone->inRange(pilot, ZoneServer::SPACEOBJECTRANGE);
				}
			}
		}

		spaceZone->unlock();
		zoneUnlocked = true;

		notifySelfPositionUpdate(sceneObject);
	} catch (Exception& e) {
		info("error", true);
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}

	/*
	bool isInvis = false;

	TangibleObject* tano = sceneObject->asTangibleObject();

	if (tano != nullptr) {
		spaceZone->updateActiveAreas(tano);

		if (tano->isInvisible())
			isInvis = true;
	}*/

	if (zoneUnlocked)
		spaceZone->wlock();
}

void SpaceZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	ManagedReference<SceneObject*> oldParent = sceneObject->getParent().get();
	Zone* zone = sceneObject->getZone();

	if (zone == nullptr || !zone->isSpaceZone())
		return;

	SpaceZone* spaceZone = cast<SpaceZone*>(zone);

	if (oldParent != nullptr && !oldParent->isCellObject())
		return;

	if (spaceZone == nullptr)
		spaceZone = cast<SpaceZone*>(newParent->getRootParent()->getZone());

	Locker _locker(spaceZone);

	if (oldParent == nullptr) { // we are in zone, enter cell
		newParent->transferObject(sceneObject, -1, true);
	// we are in cell already
	} else if (newParent->isCellObject() && oldParent != newParent) {
		newParent->transferObject(sceneObject, -1, true);
	}

	/*try {
		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			spaceZone->updateActiveAreas(tano);
		}
	} catch (Exception& e) {
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}*/

	spaceZone->unlock();

	//notify in range objects that i moved
	try {
		CloseObjectsVector* closeObjects = sceneObject->getCloseObjects();

		if (closeObjects != nullptr) {
			SortedVector<TreeEntry*> objects(closeObjects->size(), 10);
			closeObjects->safeCopyTo(objects);

			for (int i = 0; i < objects.size(); ++i) {
				auto object = static_cast<SceneObject*>(objects.getUnsafe(i));

				try {
					object->notifyPositionUpdate(sceneObject);
				} catch (Exception& e) {
					object->error("exception while calling notifyPositionUpdate: " + e.getMessage());
				}
			}
		}

		bool isInvis = false;

		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			if (tano->isInvisible())
				isInvis = true;
		}

		if (sendPackets && !isInvis) {
			if (lightUpdate) {
				LightUpdateTransformWithParentMessage* message = new LightUpdateTransformWithParentMessage(sceneObject);
				sceneObject->broadcastMessage(message, false, true);
			} else {
				UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(sceneObject);
				sceneObject->broadcastMessage(message, false, true);
			}
		}

		try {
			notifySelfPositionUpdate(sceneObject);
		} catch (Exception& e) {
			sceneObject->error("Exception caught while calling notifySelfPositionUpdate(sceneObject) in ZoneComponent::updateZoneWithParent");
			sceneObject->error(e.getMessage());
		}
	} catch (Exception& e) {
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}

	spaceZone->wlock();

}

void SpaceZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility) const {
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr)
		return;

	Zone* zone = zoneServer->getZone(newTerrainName);

	if (zone == nullptr || !zone->isSpaceZone())
		return;

	SpaceZone* newZone = cast<SpaceZone*>(zone);

	if (newZone == nullptr) {
		sceneObject->error("attempting to switch to unkown/disabled space zone " + newTerrainName);
		return;
	}

	ManagedReference<SceneObject*> newParent = zoneServer->getObject(parentID);

	if (newParent != nullptr && (!newParent->isShipObject() && !newParent->isCellObject() && newParent->getGameObjectType() != SceneObjectType::PILOTCHAIR)) {
		return;
	}

	sceneObject->destroyObjectFromWorld(false);

	if (toggleInvisibility) {
		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			tano->setInvisible(!tano->isInvisible());
		}
	}

	Locker locker(newZone);

	sceneObject->initializePosition(newPostionX, newPositionZ, newPositionY);

	// Object needs to be in zone before being inserted into parent
	newZone->transferObject(sceneObject, -1, true);

	if (newParent != nullptr) {
		if (newParent->isShipObject()) {
			newParent->transferObject(sceneObject, PlayerArrangement::SHIP_PILOT, true);
			newParent->sendTo(sceneObject, true);

			//info(true) << "SpaceZoneComponent::switchZone object transferred into ship";
		} else if (newParent->getGameObjectType() == SceneObjectType::PILOTCHAIR) {
			newParent->transferObject(sceneObject, PlayerArrangement::SHIP_PILOT_POB, true);
			sceneObject->setDirection(*newParent->getDirection());

			SceneObject* rootParent = newParent->getRootParent();

			if (rootParent != nullptr) {
				rootParent->sendTo(sceneObject, true);;
			}

			//info(true) << "SpaceZoneComponent::switchZone object transferred into POB ship with new parent: " << newParent->getDisplayedName();
		} else if (newParent->isCellObject()) {
			// group members should have their locations set in launch
			newParent->transferObject(sceneObject, -1, true);
			sceneObject->sendToOwner(true);

			//info(true) << "SpaceZoneComponent::switchZone object transferred into ship CELL";
		}
	}

	sceneObject->setMovementCounter(0);
}

void SpaceZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
}

void SpaceZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const {
	ManagedReference<SceneObject*> par = sceneObject->getParent().get();

	if (!sceneObject->isActiveArea()) {
		sceneObject->broadcastDestroy(sceneObject, sendSelfDestroy);
	}

	Zone* rootZone = sceneObject->getZone();

	if (rootZone == nullptr || !rootZone->isSpaceZone())
		return;

	SpaceZone* rootSpaceZone = dynamic_cast<SpaceZone*>(rootZone);

	if (rootSpaceZone == nullptr)
		return;

	SpaceZone* spaceZone = sceneObject->getLocalSpaceZone();

	if (par != nullptr) {
		uint64 parentID = sceneObject->getParentID();
		par->removeObject(sceneObject, nullptr, false);

		if (par->isCellObject()) {
			ManagedReference<BuildingObject*> build = par->getParent().get().castTo<BuildingObject*>();

			if (build != nullptr) {
				CreatureObject* creature = sceneObject->asCreatureObject();

				if (creature != nullptr)
					build->onExit(creature, parentID);
			}
		}

		sceneObject->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, sceneObject, 0);
	} else if (spaceZone != nullptr) {
		spaceZone->removeObject(sceneObject, nullptr, false);
	}

	removeObjectFromZone(sceneObject, rootSpaceZone, par);
}

void SpaceZoneComponent::removeObjectFromZone(SceneObject* sceneObject, SpaceZone* spaceZone, SceneObject* par) const {
	if (spaceZone == nullptr) {
		return;
	}

	Locker locker(spaceZone);

	spaceZone->dropSceneObject(sceneObject);

	if (sceneObject->isActiveArea()) {
		return;
	}

	spaceZone->remove(sceneObject);

	locker.release();

	SortedVector<ManagedReference<TreeEntry*> > closeSceneObjects;

	CloseObjectsVector* closeobjects = sceneObject->getCloseObjects();
	ManagedReference<SceneObject*> vectorOwner = sceneObject;

	if (closeobjects == nullptr && par != nullptr) {
		vectorOwner = par;
		closeobjects = vectorOwner->getCloseObjects();
	}

	while (closeobjects == nullptr && vectorOwner != nullptr) {
		vectorOwner = vectorOwner->getParent().get();

		if (vectorOwner != nullptr) {
			closeobjects = vectorOwner->getCloseObjects();
		}
	}

	if (closeobjects != nullptr) {
		removeAllObjectsFromCOV(closeobjects, closeSceneObjects, sceneObject, vectorOwner);
	} else {
#ifdef COV_DEBUG
		String templateName = "none";
		if (sceneObject->getObjectTemplate() != nullptr)
			templateName = sceneObject->getObjectTemplate()->getTemplateFileName();

		sceneObject->info("Null closeobjects vector in ZoneComponent::destroyObjectFromWorld with template: " + templateName + " and OID: " + String::valueOf(sceneObject->getObjectID()), true);
#endif

		spaceZone->getInRangeObjects(sceneObject->getPositionX(), sceneObject->getPositionY(), sceneObject->getPositionZ(), ZoneServer::SPACEOBJECTRANGE, &closeSceneObjects, false);

		for (int i = 0; i < closeSceneObjects.size(); ++i) {
			TreeEntry* obj = closeSceneObjects.getUnsafe(i);

			if (obj != sceneObject && obj->getCloseObjects() != nullptr)
				obj->removeInRangeObject(sceneObject);
		}
	}
}

void SpaceZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) const{
	sceneObject->notifySelfPositionUpdate();
}

void SpaceZoneComponent::removeAllObjectsFromCOV(CloseObjectsVector *closeobjects, SortedVector<ManagedReference<TreeEntry *> > &closeSceneObjects, SceneObject *sceneObject, SceneObject *vectorOwner) {
	for (int i = 0; closeobjects->size() != 0 && i < 100; i++) {
		closeobjects->safeCopyTo(closeSceneObjects);

		for (auto& obj : closeSceneObjects) {
			if (obj != nullptr && obj != sceneObject && obj->getCloseObjects() != nullptr) {
				obj->removeInRangeObject(sceneObject);
			}

			if (vectorOwner == sceneObject) {
				try {
					vectorOwner->removeInRangeObject(obj, false);
				} catch (ArrayIndexOutOfBoundsException &e) {
					Logger::console.error("exception removing in range object: " + e.getMessage());
				}
			}
		}

		closeSceneObjects.removeAll();
	}
}
