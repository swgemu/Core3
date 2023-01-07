/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "SpaceZoneComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/objects/intangible/TheaterObject.h"

void SpaceZoneComponent::notifyInsertToZone(SceneObject* sceneObject, SpaceZone* newZone) const {

	if (newZone == nullptr)
		return;

	if (sceneObject->isPlayerCreature() && newZone != nullptr) {
		PlayerObject* ghost = sceneObject->asCreatureObject()->getPlayerObject();
		if (ghost != nullptr)
			ghost->setSavedTerrainName(newZone->getZoneName());
	}
	if (sceneObject->getGameObjectType() != SceneObjectType::PLAYEROBJECT)
		sceneObject->teleport(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), sceneObject->getParentID());

	insertChildObjectsToZone(sceneObject, newZone);
}

void SpaceZoneComponent::insertChildObjectsToZone(SceneObject* sceneObject, SpaceZone* zone) const {
	SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();
	for (int i = 0; i < childObjects->size(); ++i) {

		ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);
		if (outdoorChild == nullptr)
			continue;

		if (outdoorChild->getContainmentType() != 4 && outdoorChild->getParent() == nullptr) {
			Locker clocker(outdoorChild, sceneObject);

			Logger::console.info("InsertChildObjectsToZone: Position X: " + outdoorChild->getDisplayedName() + " "+ String::valueOf(outdoorChild->getPositionX()), true);

			zone->transferObject(outdoorChild, -1, true);
		}
	}
}

void SpaceZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) const {
	ZoneServer* zoneServer = sceneObject->getZoneServer();
	SpaceZone* zone = sceneObject->getSpaceZone();

	CreatureObject* player = nullptr;

	if (sceneObject->isPlayerCreature()) {
		player = sceneObject->asCreatureObject();
	}

	ManagedReference<SceneObject*> par = sceneObject->getParent().get();

	if (player != nullptr) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			ghost->setTeleporting(true);
			ghost->updateLastValidatedPosition();
			ghost->setClientLastMovementStamp(0);
		}

		player->setMovementCounter(0);
	}

	if (zone == nullptr)
		return;

	Locker locker(zone);

	if (parentID != 0) {
		Reference<SceneObject*> newParent = zoneServer->getObject(parentID);

		if (newParent == nullptr || !newParent->isCellObject())
			return;

		if (newPositionX != sceneObject->getPositionX() || newPositionZ != sceneObject->getPositionZ() || newPositionY != sceneObject->getPositionY()) {
			sceneObject->setPosition(newPositionX, newPositionZ, newPositionY);
			sceneObject->updateZoneWithParent(newParent, false, false);
		}
		DataTransformWithParent* pack = new DataTransformWithParent(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	} else {
		if (newPositionX != sceneObject->getPositionX() || newPositionZ != sceneObject->getPositionZ() || newPositionY != sceneObject->getPositionY()) {
			sceneObject->setPosition(newPositionX, newPositionZ, newPositionY);
			sceneObject->updateZone(false, false);
		}
		DataTransform* pack = new DataTransform(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	}
}

void SpaceZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) const {
	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();
	SpaceZone* zone = sceneObject->getSpaceZone();
	ManagedReference<SceneObject*> sceneObjectRootParent = sceneObject->getRootParent();


	if (zone == nullptr) {
		if (sceneObjectRootParent == nullptr)
			return;

		zone = sceneObjectRootParent->getSpaceZone();
	}

	Locker _locker(zone);
	bool zoneUnlocked = false;

	// in POB ship or spacestation?
	if (parent != nullptr && parent->isCellObject()) {
		SceneObject* rootParent = parent->getRootParent();
		if (rootParent == nullptr)
			return;
		zone = rootParent->getSpaceZone();
		zone->transferObject(sceneObject, -1, false);
		zone->unlock();
		zoneUnlocked = true;
	} else {
		// Normal Ship
		zone->unlock();
		zoneUnlocked = true;
		try {
			if (parent != nullptr && parent->isShipObject()) {
				zone->update(parent);
				zone->inRange(parent, ZoneServer::SPACEOBJECTRANGE);

			} else if (sceneObject->isShipObject()) {
				zone->update(sceneObject);
				zone->inRange(sceneObject, ZoneServer::SPACEOBJECTRANGE);
			}
		} catch (Exception& e) {
			info("error", true);
			sceneObject->error(e.getMessage());
			e.printStackTrace();
			}
	}
		try {
			notifySelfPositionUpdate(sceneObject);
		} catch (Exception& e) {
			sceneObject->error("Exception caught while calling notifySelfPositionUpdate(sceneObject) in ZoneComponent::updateZone");
			sceneObject->error(e.getMessage());
		}

	if (zoneUnlocked)
		zone->wlock();

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr)
			ghost->setSavedParentID(0);
	}
}

void SpaceZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	ManagedReference<SpaceZone*> zone = sceneObject->getSpaceZone();
	ManagedReference<SceneObject*> oldParent = sceneObject->getParent().get();

	if (oldParent != nullptr && !oldParent->isCellObject())
		return;

	if (zone == nullptr)
		zone = newParent->getRootParent()->getSpaceZone();

	Locker _locker(zone);

	if (oldParent == nullptr) { // we are in zone, enter cell
		newParent->transferObject(sceneObject, -1, true);

		zone->unlock();
	} else { // we are in cell already
		if (oldParent != newParent) {
			newParent->transferObject(sceneObject, -1, true);

			zone->unlock();
		} else {
			zone->unlock();

			try {
				TangibleObject* tano = sceneObject->asTangibleObject();

				if (tano != nullptr) {
					//zone->updateActiveAreas(tano);
				}
			} catch (Exception& e) {
				sceneObject->error(e.getMessage());
				e.printStackTrace();
			}
		}
	}

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

	zone->wlock();

	if (sceneObject->getParent() != nullptr && sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr)
			ghost->setSavedParentID(sceneObject->getParentID());
	}
}

void SpaceZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility) const {
	SpaceZone* zone = sceneObject->getSpaceZone();
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<SceneObject*> par = sceneObject->getParent().get();

		if (par != nullptr && par->isShipObject() && !!newTerrainName.contains("space")) {
			player->executeObjectControllerAction(STRING_HASHCODE("landShip"));
		}

		if (ghost != nullptr) {
			ghost->setSavedParentID(0);

			ghost->setTeleporting(true);
			ghost->setOnLoadScreen(true);
			ghost->updateLastValidatedPosition();
			ghost->setClientLastMovementStamp(0);

			ghost->unloadSpawnedChildren();
			ghost->setSavedTerrainName(newTerrainName);
		}

		player->setMovementCounter(0);

		player->notifyObservers(ObserverEventType::ZONESWITCHED);
	}


	SpaceZone* newZone = sceneObject->getZoneServer()->getSpaceZone(newTerrainName);

	if (newZone == nullptr) {
		sceneObject->error("attempting to switch to unknown/disabled zone " + newTerrainName);
		return;
	}

	ManagedReference<SceneObject*> newParent = sceneObject->getZoneServer()->getObject(parentID);

	if (newParent != nullptr && newParent->getZone() == nullptr)
		return;

	if (newParent != nullptr && !newParent->isCellObject())
		newParent = nullptr;

	sceneObject->destroyObjectFromWorld(false);

	if (toggleInvisibility) {
		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			tano->setInvisible(!tano->isInvisible());
		}
	}

	Locker locker(newZone);

	sceneObject->initializePosition(newPostionX, newPositionZ, newPositionY);


	if (newParent != nullptr) {
		if (zone == newZone) {
			if (newParent->transferObject(sceneObject, -1, false)) {
				sceneObject->sendToOwner(true);
			}
		} else {
			if (newParent->transferObject(sceneObject, -1, false, false, false)) {
				sceneObject->sendToOwner(true);

				if (newParent->isCellObject()) {
					auto rootParent = sceneObject->getRootParent();

					if (rootParent != nullptr)
						rootParent->notifyObjectInsertedToChild(sceneObject, newParent, nullptr);
				}
			}
		}
	} else {
		newZone->transferObject(sceneObject, -1, true);
	}
}

void SpaceZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
}

void SpaceZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const {
	ManagedReference<SceneObject*> par = sceneObject->getParent().get();

	if (!sceneObject->isActiveArea()) {
		sceneObject->broadcastDestroy(sceneObject, sendSelfDestroy);
	}

	SpaceZone* rootSpaceZone = sceneObject->getSpaceZone();
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

void SpaceZoneComponent::removeAllObjectsFromCOV(CloseObjectsVector *closeobjects,
											SortedVector<ManagedReference<TreeEntry *> > &closeSceneObjects,
											SceneObject *sceneObject, SceneObject *vectorOwner) {
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
