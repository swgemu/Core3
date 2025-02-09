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
	Zone* zone = sceneObject->getZone();

	if (zone == nullptr || !zone->isSpaceZone())
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
	Zone* spaceZone = sceneObject->getZone();
	ManagedReference<SceneObject*> sceneObjectRootParent = sceneObject->getRootParent();

	if (spaceZone == nullptr) {
		if (sceneObjectRootParent == nullptr)
			return;

		spaceZone = sceneObjectRootParent->getZone();
	}

	if (spaceZone == nullptr || !spaceZone->isSpaceZone())
		return;

	Locker _locker(spaceZone);
	bool zoneUnlocked = false;

	// Updates objects in range
	try {
		if (sceneObject->isShipObject()) {
			spaceZone->update(sceneObject);
			spaceZone->inRange(sceneObject, ZoneServer::SPACESTATIONRANGE);

			spaceZone->unlock();
			zoneUnlocked = true;
		}

		notifySelfPositionUpdate(sceneObject);
	} catch (Exception& e) {
		info("error", true);
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}

	TangibleObject* tano = sceneObject->asTangibleObject();

	if (tano != nullptr) {
		spaceZone->updateActiveAreas(tano);
	}

	if (zoneUnlocked)
		spaceZone->wlock();
}

void SpaceZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	ManagedReference<Zone*> spaceZone = sceneObject->getZone();
	ManagedReference<SceneObject*> oldParent = sceneObject->getParent().get();

	ManagedReference<SceneObject*> rootParent = sceneObject->getRootParent();

	if (spaceZone == nullptr) {
		spaceZone = rootParent->getZone();
	}

	if (spaceZone == nullptr || !spaceZone->isSpaceZone()) {
		return;
	}

	// sceneObject->info(true) << "SpaceZoneComponent::updateZoneWithParent - For SceneObject: " << sceneObject->getDisplayedName() << " Containment Type: " << sceneObject->getContainmentType() << " World Position: " << sceneObject->getWorldPosition().toString() << " Position: " << sceneObject->getPosition().toString();

	Locker _locker(spaceZone);

	if (oldParent != newParent) {
		// Player is in POB Ship cell
		if (newParent->isCellObject()) {
			newParent->transferObject(sceneObject, -1, true);
		// Player is in slotted position
		} else if (newParent->isValidJtlParent()) {
			newParent->transferObject(sceneObject, sceneObject->getContainmentType(), true);
		}
	}

	spaceZone->update(sceneObject);
	spaceZone->inRange(sceneObject, spaceZone->getZoneObjectRange());

	spaceZone->unlock();

	// Notify in range objects of the players movement update inside a container in space
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
			sceneObject->error("Exception caught while calling notifySelfPositionUpdate(sceneObject) in SpaceZoneComponent::updateZoneWithParent");
			sceneObject->error(e.getMessage());
		}
	} catch (Exception& e) {
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}

	spaceZone->wlock();
}

void SpaceZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility, int playerArrangement) const {
	// info(true) << "SpaceZoneComponent::switchZone for " << sceneObject->getDisplayedName() << " with new ParentID: " << parentID;

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto zone = sceneObject->getZone();
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	Zone* newZone = zoneServer->getZone(newTerrainName);

	if (newZone == nullptr || !newZone->isSpaceZone()) {
		sceneObject->error() << sceneObject->getDisplayedName() << " ID: " << sceneObject->getObjectID() << " -- ::switchZone - Attempting to transfer object into disabled Space Zone: " << newTerrainName;
		return;
	}

	ManagedReference<SceneObject*> newParent = zoneServer->getObject(parentID);

	if (newParent != nullptr && newParent->getZone() == nullptr) {
		return;
	}

	sceneObject->destroyObjectFromWorld(false);

	if (toggleInvisibility && sceneObject->isTangibleObject()) {
		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			tano->setInvisible(!tano->isInvisible());
		}
	}

	Locker locker(newZone);

	sceneObject->initializePosition(newPositionX, newPositionZ, newPositionY);
	sceneObject->incrementMovementCounter();

	if (newParent != nullptr) {
		// info(true) << "SpaceZoneComponent::switchZone -- starting transfer into new parent... ";

		if (newParent->transferObject(sceneObject, playerArrangement, false, false, false)) {
			sceneObject->sendToOwner(true);

			// info(true) << "SpaceZoneComponent::switchZone transferred into Parent: " << newParent->getDisplayedName() << " Player: " << sceneObject->getDisplayedName() << " Containment Type: " << playerArrangement << " X: " << newPositionX << " Z: " << newPositionZ << " Y: " << newPositionY;

			if (newParent->isPilotChair() || newParent->isCellObject() || newParent->isShipTurret() || newParent->isOperationsChair()) {
				auto rootParent = newParent->getRootParent();

				if (rootParent != nullptr) {
					// info(true) << "SpaceZoneComponent::switchZone notifying root parent: " << rootParent->getDisplayedName();

					rootParent->notifyObjectInsertedToChild(sceneObject, newParent, nullptr);
				}
			}
		}
	} else {
		if (newZone->transferObject(sceneObject, -1, true)) {
			// info(true) << "SpaceZoneComponent::switchZone transferred Object into space: " << sceneObject->getDisplayedName() << " Containment Type: " << playerArrangement;
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

	Zone* spaceZone = sceneObject->getLocalZone();

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

		sceneObject->info("Null closeobjects vector in SpaceZoneComponent::destroyObjectFromWorld with template: " + templateName + " and OID: " + String::valueOf(sceneObject->getObjectID()), true);
#endif

		spaceZone->getInRangeObjects(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), spaceZone->getZoneObjectRange(), &closeSceneObjects, false);

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

void SpaceZoneComponent::removeAllObjectsFromCOV(CloseObjectsVector* closeobjects, SortedVector<ManagedReference<TreeEntry*>>& closeSceneObjects, SceneObject* sceneObject, SceneObject* vectorOwner) {
	for (int i = 0; closeobjects->size() != 0 && i < 100; i++) {
		closeobjects->safeCopyTo(closeSceneObjects);

		for (auto& obj : closeSceneObjects) {
			if (obj != nullptr && obj != sceneObject && obj->getCloseObjects() != nullptr) {
				obj->removeInRangeObject(sceneObject);
			}

			if (vectorOwner == sceneObject) {
				try {
					vectorOwner->removeInRangeObject(obj, false);
				} catch (ArrayIndexOutOfBoundsException& e) {
					Logger::console.error("exception removing in range object: " + e.getMessage());
				}
			}
		}

		closeSceneObjects.removeAll();
	}
}
