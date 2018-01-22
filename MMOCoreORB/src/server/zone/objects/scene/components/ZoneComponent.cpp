/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "ZoneComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/objects/intangible/TheaterObject.h"

void ZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* newZone) const {
	debug("inserting to zone");

	if (newZone == nullptr)
		return;

	sceneObject->teleport(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), sceneObject->getParentID());

	insertChildObjectsToZone(sceneObject, newZone);
}

void ZoneComponent::insertChildObjectsToZone(SceneObject* sceneObject, Zone* zone) const {
	SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();

	//Insert all outdoor child objects to zone
	for (int i = 0; i < childObjects->size(); ++i) {
		ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

		if (outdoorChild == nullptr)
			continue;

		if (outdoorChild->getContainmentType() != 4 && outdoorChild->getParent() == nullptr) {
			Locker clocker(outdoorChild, sceneObject);
			
			zone->transferObject(outdoorChild, -1, true);
		}
	}
}

void ZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) const {
	ZoneServer* zoneServer = sceneObject->getZoneServer();
	Zone* zone = sceneObject->getZone();

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

		//sceneObject->info("sending data transform with parent", true);

		DataTransformWithParent* pack = new DataTransformWithParent(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	} else {
		if (newPositionX != sceneObject->getPositionX() || newPositionZ != sceneObject->getPositionZ() || newPositionY != sceneObject->getPositionY()) {
			sceneObject->setPosition(newPositionX, newPositionZ, newPositionY);
			sceneObject->updateZone(false, false);
		}

		//sceneObject->info("sending data transform", true);

		DataTransform* pack = new DataTransform(sceneObject);
		sceneObject->broadcastMessage(pack, true, false);
	}
}

void ZoneComponent::updateInRangeObjectsOnMount(SceneObject* sceneObject) const {
	try {
		CloseObjectsVector* parentCloseObjectsVector = sceneObject->getRootParent()->getCloseObjects();
		SortedVector<QuadTreeEntry*> parentCloseObjects(parentCloseObjectsVector->size(), 10);

		parentCloseObjectsVector->safeCopyTo(parentCloseObjects);

		//insert new ones
		for (int i = 0; i < parentCloseObjects.size(); ++i) {
			QuadTreeEntry* o = parentCloseObjects.getUnsafe(i);

			if (sceneObject->getCloseObjects() != nullptr)
				sceneObject->addInRangeObject(o, false);

			if (o->getCloseObjects() != nullptr)
				o->addInRangeObject(sceneObject, true);
		}
	} catch (Exception& e) {
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}
}

void ZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) const {
	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();
	Zone* zone = sceneObject->getZone();
	ManagedReference<SceneObject*> sceneObjectRootParent = sceneObject->getRootParent();

	if (zone == nullptr) {
		if (sceneObjectRootParent == nullptr)
			return;

		zone = sceneObjectRootParent->getZone();
	}

	if (parent != nullptr && (parent->isVehicleObject() || parent->isMount()))
		sceneObject->updateVehiclePosition(sendPackets);

	Locker _locker(zone);

	bool zoneUnlocked = false;

	if (parent != nullptr && parent->isCellObject()) {
		SceneObject* rootParent = parent->getRootParent();

		if (rootParent == nullptr)
			return;

		zone = rootParent->getZone();

		zone->transferObject(sceneObject, -1, false);

		zone->unlock();
		zoneUnlocked = true;
	} else {
		if (sceneObject->getLocalZone() != nullptr) {
			zone->update(sceneObject);

			zone->unlock();
			zoneUnlocked = true;

			try {
				zone->inRange(sceneObject, ZoneServer::CLOSEOBJECTRANGE);
			} catch (Exception& e) {
				sceneObject->error(e.getMessage());
				e.printStackTrace();
			}
		} else if (parent != nullptr) {
			zone->unlock();
			zoneUnlocked = true;

			updateInRangeObjectsOnMount(sceneObject);
		}
	}

	try {
		bool isInvis = false;

		TangibleObject* tano = sceneObject->asTangibleObject();

		if (tano != nullptr) {
			zone->updateActiveAreas(tano);

			if (tano->isInvisible())
				isInvis = true;
		}

		if (!isInvis && sendPackets && (parent == nullptr || (!parent->isVehicleObject() && !parent->isMount()))) {
			if (lightUpdate) {
				LightUpdateTransformMessage* message = new LightUpdateTransformMessage(sceneObject);
				sceneObject->broadcastMessage(message, false, true);
			} else {
				UpdateTransformMessage* message = new UpdateTransformMessage(sceneObject);
				sceneObject->broadcastMessage(message, false, true);
			}
		}

		try {
			notifySelfPositionUpdate(sceneObject);
		} catch (Exception& e) {
			sceneObject->error("Exception caught while calling notifySelfPositionUpdate(sceneObject) in ZoneComponent::updateZone");
			sceneObject->error(e.getMessage());
		}
	} catch (Exception& e) {
		sceneObject->error(e.getMessage());
		e.printStackTrace();
	}

	if (zoneUnlocked)
		zone->wlock();
}

void ZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	ManagedReference<Zone*> zone = sceneObject->getZone();
	ManagedReference<SceneObject*> oldParent = sceneObject->getParent().get();

	if (oldParent != nullptr && !oldParent->isCellObject())
		return;

	if (zone == nullptr)
		zone = newParent->getRootParent()->getZone();

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
					zone->updateActiveAreas(tano);
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
			SortedVector<QuadTreeEntry*> objects(closeObjects->size(), 10);
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
}

void ZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility) const {
	Zone* zone = sceneObject->getZone();
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	Zone* newZone = sceneObject->getZoneServer()->getZone(newTerrainName);

	if (newZone == nullptr) {
		sceneObject->error("attempting to switch to unkown/disabled zone " + newTerrainName);
		return;
	}

	ManagedReference<SceneObject*> newParent = sceneObject->getZoneServer()->getObject(parentID);

	if (newParent != nullptr && newParent->getZone() == nullptr)
		return;

	if (newParent != nullptr && !newParent->isCellObject())
		newParent = nullptr;

	if (newPositionZ == 0 && newParent == nullptr) {
		newPositionZ = newZone->getHeight(newPostionX, newPositionY);
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

void ZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
}

void ZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const {
	ManagedReference<SceneObject*> par = sceneObject->getParent().get();

	if (!sceneObject->isActiveArea()) {
		sceneObject->broadcastDestroy(sceneObject, sendSelfDestroy);
	}

	Zone* rootZone = sceneObject->getZone();
	Zone* zone = sceneObject->getLocalZone();

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
	} else if (zone != nullptr) {
		zone->removeObject(sceneObject, nullptr, false);
	}

	removeObjectFromZone(sceneObject, rootZone, par);
}

void ZoneComponent::removeObjectFromZone(SceneObject* sceneObject, Zone* zone, SceneObject* par) const {
	if (zone == nullptr)
		return;

	Locker locker(zone);

	zone->dropSceneObject(sceneObject);

	if (sceneObject->isActiveArea()) {
		return;
	}

	zone->remove(sceneObject);

	SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(sceneObject->getObjectTemplate());

	if (objtemplate != nullptr) {
		String modFile = objtemplate->getTerrainModificationFile();

		if (!modFile.isEmpty()) {
			zone->getPlanetManager()->getTerrainManager()->removeTerrainModification(sceneObject->getObjectID());
		}
	}

	if (sceneObject->isTheaterObject()) {
		TheaterObject* theater = static_cast<TheaterObject*>(sceneObject);

		if (theater != nullptr && theater->shouldFlattenTheater()) {
			zone->getPlanetManager()->getTerrainManager()->removeTerrainModification(theater->getObjectID());
		}
	}

	locker.release();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

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

		zone->getInRangeObjects(sceneObject->getPositionX(), sceneObject->getPositionY(), ZoneServer::CLOSEOBJECTRANGE + 64, &closeSceneObjects, false);

		for (int i = 0; i < closeSceneObjects.size(); ++i) {
			QuadTreeEntry* obj = closeSceneObjects.getUnsafe(i);

			if (obj != sceneObject && obj->getCloseObjects() != nullptr)
				obj->removeInRangeObject(sceneObject);
		}
	}

	TangibleObject* tano = sceneObject->asTangibleObject();

	if (tano != nullptr) {
		SortedVector<ManagedReference<ActiveArea*> >* activeAreas = tano->getActiveAreas();

		while (activeAreas->size() > 0) {
			Locker _alocker(sceneObject->getContainerLock());
			ManagedReference<ActiveArea*> area = activeAreas->get(0);
			activeAreas->remove(0);

			_alocker.release();

			area->enqueueExitEvent(sceneObject);
		}
	} else if (sceneObject->isStaticObjectClass()) {
		// hack to get around notifyEnter/Exit only working with tangible objects
		Vector3 worldPos = sceneObject->getWorldPosition();
		SortedVector<ActiveArea* > objects;
		zone->getInRangeActiveAreas(worldPos.getX(), worldPos.getY(), 5, &objects, false);

		for(auto& area : objects) {
			NavArea *mesh = area->asNavArea();

			if (mesh != nullptr) {
				if (mesh->containsPoint(worldPos.getX(), worldPos.getY())) {
					mesh->updateNavMesh(sceneObject, true);
				}
			}
		}
	}
}

void ZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) const {
	sceneObject->notifySelfPositionUpdate();
}

void ZoneComponent::removeAllObjectsFromCOV(CloseObjectsVector *closeobjects,
											SortedVector<ManagedReference<QuadTreeEntry *> > &closeSceneObjects,
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
