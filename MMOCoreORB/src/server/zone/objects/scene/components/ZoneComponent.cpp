/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

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
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/packets/scene/GameSceneChangedMessage.h"

void ZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* newZone) {
	info("inserting to zone");

	if (newZone == NULL)
		return;

	//newZone->transferObject(sceneObject, -1, true);

	sceneObject->teleport(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), sceneObject->getParentID());

	insertChildObjectsToZone(sceneObject, newZone);
}

void ZoneComponent::insertChildObjectsToZone(SceneObject* sceneObject, Zone* zone) {
	SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();

	//Insert all outdoor child objects to zone
	for (int i = 0; i < childObjects->size(); ++i) {
		ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

		if (outdoorChild == NULL)
			continue;

		if (outdoorChild->getContainmentType() != 4 && outdoorChild->getParent() == NULL)
			zone->transferObject(outdoorChild, -1, true);
	}
}

void ZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	ZoneServer* zoneServer = sceneObject->getZoneServer();
	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		return;

	Locker locker(zone);

	if (parentID != 0) {
		ManagedReference<SceneObject*> newParent = zoneServer->getObject(parentID);

		if (newParent == NULL || !newParent->isCellObject())
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

void ZoneComponent::updateInRangeObjectsOnMount(SceneObject* sceneObject) {
	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) sceneObject->getCloseObjects();
	CloseObjectsVector* parentCloseObjectsVector = (CloseObjectsVector*) sceneObject->getRootParent().get()->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects(closeObjectsVector->size(), 10);
	closeObjectsVector->safeCopyTo(closeObjects);

	SortedVector<ManagedReference<QuadTreeEntry*> > parentCloseObjects(parentCloseObjectsVector->size(), 10);
	parentCloseObjectsVector->safeCopyTo(parentCloseObjects);

	//remove old ones
	float rangesq = 192.f * 192.f;

	float x = sceneObject->getPositionX();
	float y = sceneObject->getPositionY();

	float oldx = sceneObject->getPreviousPositionX();
	float oldy = sceneObject->getPreviousPositionY();

	for (int i = 0; i < closeObjects.size(); ++i) {
		ManagedReference<QuadTreeEntry*> o = closeObjects.get(i);
		ManagedReference<QuadTreeEntry*> objectToRemove = o;
		ManagedReference<QuadTreeEntry*> rootParent = o->getRootParent();

		if (rootParent != NULL)
			o = rootParent;

		if (o != sceneObject) {
			float deltaX = x - o->getPositionX();
			float deltaY = y - o->getPositionY();

			if (deltaX * deltaX + deltaY * deltaY > rangesq) {
				float oldDeltaX = oldx - o->getPositionX();
				float oldDeltaY = oldy - o->getPositionY();

				if (oldDeltaX * oldDeltaX + oldDeltaY * oldDeltaY <= rangesq) {

					if (sceneObject->getCloseObjects() != NULL)
						sceneObject->removeInRangeObject(objectToRemove);

					if (objectToRemove->getCloseObjects() != NULL)
						objectToRemove->removeInRangeObject(sceneObject);
				}
			}
		}
	}

	//insert new ones
	for (int i = 0; i < parentCloseObjects.size(); ++i) {
		QuadTreeEntry* o = parentCloseObjects.get(i);

		if (sceneObject->getCloseObjects() != NULL)
			sceneObject->addInRangeObject(o, false);

		if (o->getCloseObjects() != NULL)
			o->addInRangeObject(sceneObject, true);
	}
}

void ZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) {
	ManagedReference<SceneObject*> parent = sceneObject->getParent();
	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		zone = parent->getRootParent().get()->getZone();

	if (parent != NULL && parent->isVehicleObject())
		sceneObject->updateVehiclePosition(sendPackets);

	Locker _locker(zone);

	bool zoneUnlocked = false;

	if (parent != NULL && parent->isCellObject()) {
		//parent->removeObject(sceneObject, true);
		//removeFromBuilding(sceneObject, dynamic_cast<BuildingObject*>(parent->getParent()));

		zone = parent->getRootParent().get()->getZone();

		zone->transferObject(sceneObject, -1, false);

		zone->unlock();
	} else {
		if (sceneObject->getLocalZone() != NULL) {
			zone->update(sceneObject);

			zone->unlock();

			zone->inRange(sceneObject, 192);
		} else if (parent != NULL) {
			zone->unlock();

			updateInRangeObjectsOnMount(sceneObject);
		}
	}

	zone->updateActiveAreas(sceneObject);
	
	bool isInvis = false;

	if (sceneObject->isCreatureObject()) {
		CreatureObject* creo = cast<CreatureObject*>(sceneObject);
		
		if(creo->isInvisible())
			isInvis = true;
		}


	if (!isInvis && sendPackets && (parent == NULL || !parent->isVehicleObject())) {
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

	zone->wlock();
}

void ZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	ManagedReference<Zone*> zone = sceneObject->getZone();
	ManagedReference<SceneObject*> oldParent = sceneObject->getParent();

	if (oldParent != NULL && !oldParent->isCellObject())
		return;

	if (zone == NULL)
		zone = newParent->getRootParent().get()->getZone();

	Locker _locker(zone);

	if (oldParent == NULL) { // we are in zone, enter cell
		//zone->remove(sceneObject);

		newParent->transferObject(sceneObject, -1, true);

		zone->unlock();
		//insertToBuilding(sceneObject, dynamic_cast<BuildingObject*>(newParent->getParent()));
	} else { // we are in cell already
		if (oldParent != newParent) {
			//oldParent->removeObject(sceneObject, false);
			newParent->transferObject(sceneObject, -1, true);

			zone->unlock();
		} else {
			zone->unlock();

			zone->updateActiveAreas(sceneObject);
		}

		//notify in range objects that i moved
	}

	CloseObjectsVector* closeObjects = (CloseObjectsVector*) sceneObject->getCloseObjects();

	if (closeObjects != NULL) {
		SortedVector<ManagedReference<QuadTreeEntry*> > objects(closeObjects->size(), 10);
		closeObjects->safeCopyTo(objects);

		for (int i = 0; i < objects.size(); ++i) {
			QuadTreeEntry* object = objects.get(i);
			try {
				object->notifyPositionUpdate(sceneObject);
			} catch (Exception& e) {

			}
		}
	}

	//zoneLocker.release();

	//zone->unlock();

	bool isInvis = false;

	if (sceneObject->isCreatureObject()) {
		CreatureObject* creo = cast<CreatureObject*>(sceneObject);
		if(creo->isInvisible())
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

	zone->wlock();
}

void ZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	Zone* zone = sceneObject->getZone();
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	/*if (zone == NULL)
		return;*/

	Zone* newZone = sceneObject->getZoneServer()->getZone(newTerrainName);

	if (newZone == NULL) {
		sceneObject->error("attempting to switch to unkown/disabled zone " + newTerrainName);
		return;
	}

	ManagedReference<SceneObject*> newParent = sceneObject->getZoneServer()->getObject(parentID);

	if (newParent != NULL && newParent->getZone() == NULL)
		return;

	if (newParent != NULL && !newParent->isCellObject())
		newParent = NULL;

	if (newParent != NULL)
		sceneObject->sendMessage(new GameSceneChangedMessage());

	if (newPositionZ == 0) {
		newPositionZ = newZone->getHeight(newPostionX, newPositionY);
	}

	sceneObject->destroyObjectFromWorld(false);

	Locker locker(newZone);

	sceneObject->initializePosition(newPostionX, newPositionZ, newPositionY);

	if (newParent != NULL) {
		if (newParent->transferObject(sceneObject, -1, false)) {
			sceneObject->sendToOwner(true);
		}
	} else {
		newZone->transferObject(sceneObject, -1, true);
	}
}

void ZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) {
	/*ManagedReference<SceneObject*> thisLocker = sceneObject;
	Zone* zone = sceneObject->getZone();

	zone->removeObject(sceneObject);*/
}

void ZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) {
	ManagedReference<SceneObject*> par = sceneObject->getParent();

	sceneObject->broadcastDestroy(sceneObject, sendSelfDestroy);

	ManagedReference<Zone*> rootZone = sceneObject->getZone();
	ManagedReference<Zone*> zone = sceneObject->getLocalZone();

	if (par != NULL) {
		uint64 parentID = sceneObject->getParentID();
		par->removeObject(sceneObject, NULL, false);

		if (par->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(par->getParent().get().get());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(sceneObject);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}

		sceneObject->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, sceneObject, 0);
	} else if (zone != NULL) {
		zone->removeObject(sceneObject, NULL, false);
	}

	if (rootZone != NULL) {
		Locker locker(rootZone);

		if (!sceneObject->isActiveArea())
			rootZone->remove(sceneObject);
			
		rootZone->dropSceneObject(sceneObject);
		
		locker.release();


		SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

		CloseObjectsVector* closeobjects = (CloseObjectsVector*) sceneObject->getCloseObjects();

		if (closeobjects != NULL) {
			try {
				closeobjects->safeCopyTo(closeSceneObjects);

				while (closeSceneObjects.size() > 0) {
					ManagedReference<QuadTreeEntry*> obj = closeSceneObjects.get(0);

					if (obj != NULL && obj != sceneObject && obj->getCloseObjects() != NULL)
						obj->removeInRangeObject(sceneObject);
					
					sceneObject->removeInRangeObject((int) 0);

					closeSceneObjects.remove((int) 0);
				}

				closeobjects->removeAll();

			} catch (...) {
			}
		} else {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

			rootZone->getInRangeObjects(sceneObject->getPositionX(), sceneObject->getPositionY(), 512, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				QuadTreeEntry* obj = closeSceneObjects.get(i);

				if (obj != sceneObject && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(sceneObject);
			}
		}

//		rootZone->dropSceneObject(sceneObject);

//		locker.release();

		Vector<ManagedReference<ActiveArea*> >* activeAreas =  sceneObject->getActiveAreas();

		while (activeAreas->size() > 0) {
			ManagedReference<ActiveArea*> area = activeAreas->get(0);
			activeAreas->remove(0);

			area->enqueueExitEvent(sceneObject);
		}
	}
}

void ZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) {
	sceneObject->notifySelfPositionUpdate();
}
