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

void ZoneComponent::insertToZone(SceneObject* sceneObject, Zone* newZone) {
	info("inserting to zone");

	if (newZone == NULL)
		return;

	Zone* zone = sceneObject->getZone();

	Vector<ManagedReference<ActiveArea*> >* activeAreas = sceneObject->getActiveAreas();

	activeAreas->removeAll();

	Locker zoneLocker(newZone);

	if (sceneObject->isInQuadTree() && newZone != zone) {
		error("trying to insert to zone an object that is already in a different quadtree");

		removeFromZone(sceneObject);

		//StackTrace::printStackTrace();
	}

	sceneObject->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(sceneObject);

	SceneObject* parent = sceneObject->getParent();

	if (parent != NULL && parent->isCellObject())
		parent->addObject(sceneObject, -1, false);

	SortedVector<ManagedReference<SceneObject*> >* notifiedSentObjects = sceneObject->getNotifiedSentObjects();

	notifiedSentObjects->removeAll();

	sceneObject->sendToOwner(true);

	if (sceneObject->isInQuadTree()) {
		for (int i = 0; i < sceneObject->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) sceneObject->getInRangeObject(i);

			sceneObject->notifyInsert(object);

			if (object != sceneObject) {
				if (object->getParentRecursively(SceneObject::BUILDING) != NULL) {
					if (notifiedSentObjects->put(object) != -1)
						object->sendTo(sceneObject, true);
				}

				if (object->isPlayerCreature()) {
					object->notifyDissapear(sceneObject);
					object->notifyInsert(sceneObject);
				}
			}
		}
	} else {
		sceneObject->initializePosition(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY());

		//movementCounter = 0;
		sceneObject->setMovementCounter(0);

		if (parent == NULL || !parent->isCellObject() || parent->getParent() == NULL) {
			zone->insert(sceneObject);

			zone->inRange(sceneObject, 192);
		} else if (parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();
			sceneObject->insertToBuilding(building);

			building->notifyInsertToZone(sceneObject);
		}
	}

	SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();

	//Insert all outdoor child objects to zone
	for (int i = 0; i < childObjects->size(); ++i) {
		ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

		if (outdoorChild == NULL)
			continue;

		outdoorChild->insertToZone(zone);
	}

	zone->updateActiveAreas(sceneObject);

	sceneObject->teleport(sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), sceneObject->getParentID());
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

void ZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) {
	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		return;

	SceneObject* parent = sceneObject->getParent();

	if (parent != NULL && parent->isVehicleObject())
		sceneObject->updateVehiclePosition();

	Locker zoneLocker(zone);

	if (parent != NULL && parent->isCellObject()) {
		CellObject* cell = (CellObject*) parent;

		if (cell->getParent() != NULL)
			removeFromBuilding(sceneObject, (BuildingObject*)cell->getParent());

		sceneObject->setParent(NULL);

		zone->insert(sceneObject);
	} else
		zone->update(sceneObject);

	parent = sceneObject->getParent();

	zone->inRange(sceneObject, 192);

	if (sendPackets && (parent == NULL || !parent->isVehicleObject())) {
		if (lightUpdate) {
			LightUpdateTransformMessage* message = new LightUpdateTransformMessage(sceneObject);
			sceneObject->broadcastMessage(message, false, false);
		} else {
			UpdateTransformMessage* message = new UpdateTransformMessage(sceneObject);
			sceneObject->broadcastMessage(message, false, false);
		}
	}

	zone->updateActiveAreas(sceneObject);

	//zoneLocker.release();

	zone->unlock();

	try {
		notifySelfPositionUpdate(sceneObject);
	} catch (Exception& e) {

	}

	zone->wlock();

	//notifySelfPositionUpdate();
}

void ZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		return;

	/*SceneObject* parent = sceneObject->getParent();*/

	if (sceneObject->getParent() != NULL && sceneObject->getParent()->isVehicleObject())
		return;

	bool insert = false;

	/*StringBuffer msg;
	msg << "world posx: " << getWorldPositionX() << " wolrd posy: " << getWorldPositionY() << " posz: " << getWorldPositionZ();
	info(msg.toString(), true);

	StringBuffer msg2;
	msg2 << "cell x: " << positionX << " cell y: " << positionY;
	info(msg2.toString(), true);*/

	Locker zoneLocker(zone);

	if (newParent != sceneObject->getParent()) {
		if (sceneObject->getParent() == NULL) {
			zone->remove(sceneObject);
			insert = true;
		} else {
			if (sceneObject->getParent()->isCellObject()) {
				BuildingObject* building = (BuildingObject*) sceneObject->getParent()->getParent();
				SceneObject* newObj = newParent->getParent();

				BuildingObject* newBuilding = (BuildingObject*) newObj;

				if (building != newBuilding) {
					//System::out << "Does this actually ever happen when someone goes from one building to another?" << endl;

					removeFromBuilding(sceneObject, building);

					insert = true;
				}

				// remove from old cell
				if (sceneObject->getParent() != NULL)
					sceneObject->getParent()->removeObject(sceneObject, false);
			} else
				insert = true;
		}

		//System::out << "Cell Transition.  Old: " << hex << parent <<  dec << " New: " << hex << newParent << dec << endl;
		// add to new cell
		//parent = newParent;
		if (!newParent->addObject(sceneObject, -1, false)) {
			error("could not add to parent " + newParent->getLoggingName());
		}

		sceneObject->broadcastMessage(sceneObject->link(sceneObject->getParent()->getObjectID(), 0xFFFFFFFF), true, false);
	}

	ManagedReference<BuildingObject*> building = (BuildingObject*) sceneObject->getParent()->getParent();

	if (insert) {
		info("insertToBuilding from updateZoneWithParent");
		insertToBuilding(sceneObject, building);
	} else {
		building->update(sceneObject);

		building->inRange(sceneObject, 192);
	}

	if (sendPackets) {
		if (lightUpdate) {
			LightUpdateTransformWithParentMessage* message = new LightUpdateTransformWithParentMessage(sceneObject);
			sceneObject->broadcastMessage(message, false, false);
		} else {
			UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(sceneObject);
			sceneObject->broadcastMessage(message, false, false);
		}
	}

	zone->updateActiveAreas(sceneObject);

	//zoneLocker.release();

	zone->unlock();

	try {
		notifySelfPositionUpdate(sceneObject);
	} catch (Exception& e) {

	}

	zone->wlock();
}

void ZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	Zone* zone = sceneObject->getZone();
	ManagedReference<SceneObject*> thisLocker = sceneObject;

	if (zone == NULL)
		return;

	Zone* newZone = sceneObject->getZoneServer()->getZone(newTerrainName);

	if (newZone == NULL)
		return;

	removeFromZone(sceneObject);

	SceneObject* newParent = sceneObject->getZoneServer()->getObject(parentID);

	Locker locker(newZone);

	if (newParent != NULL && newParent->isCellObject())
		newParent->addObject(sceneObject, -1, false);

	sceneObject->initializePosition(newPostionX, newPositionZ, newPositionY);

	insertToZone(sceneObject, newZone);
}

void ZoneComponent::insertToBuilding(SceneObject* sceneObject, BuildingObject* building) {
	SceneObject* parent = sceneObject->getParent();

	if (sceneObject->isInQuadTree() || !parent->isCellObject())
		return;

	try {
		//info("SceneObjectImplementation::insertToBuilding");

		//parent->addObject(_this, 0xFFFFFFFF);

		building->insert(sceneObject);

		building->inRange(sceneObject, 192);

		sceneObject->broadcastMessage(sceneObject->link(parent->getObjectID(), 0xFFFFFFFF), true, false);

		//info("sent cell link to everyone else");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void ZoneComponent::removeFromZone(SceneObject* sceneObject) {
	ManagedReference<SceneObject*> thisLocker = sceneObject;
	SceneObject* parent = sceneObject->getParent();
	Zone* zone = sceneObject->getZone();
	Vector<ManagedReference<ActiveArea*> >* activeAreas = sceneObject->getActiveAreas();
	SortedVector<ManagedReference<SceneObject*> >* notifiedSentObjects = sceneObject->getNotifiedSentObjects();

	try {
		Locker locker(sceneObject);

		if (zone == NULL)
			return;

		info("removing from zone");

		Locker zoneLocker(zone);

		//ManagedReference<SceneObject*> par = parent.get();

		if (parent != NULL && parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*)parent->getParent();

			//par = parent;
			if (building != NULL)
				removeFromBuilding(sceneObject, building);
			else
				zone->remove(sceneObject);
		} else
			zone->remove(sceneObject);

		while (sceneObject->inRangeObjectCount() > 0) {
			QuadTreeEntry* obj = sceneObject->getInRangeObject(0);

			if (obj != sceneObject)
				obj->removeInRangeObject(sceneObject);

			sceneObject->removeInRangeObject((int) 0);
		}

		while (activeAreas->size() > 0) {
			ManagedReference<ActiveArea*> area = activeAreas->get(0);
			area->enqueueExitEvent(sceneObject);

			activeAreas->remove(0);
		}

		SortedVector<ManagedReference<SceneObject*> >* childObjects = sceneObject->getChildObjects();

		//Remove all outdoor child objects from zone
		for (int i = 0; i < childObjects->size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = childObjects->get(i);

			if (outdoorChild == NULL)
				continue;

			outdoorChild->removeFromZone();
		}

		//removeInRangeObjects();

		notifiedSentObjects->removeAll();

		Zone* oldZone = zone;
		zone = NULL;

		oldZone->dropSceneObject(sceneObject);
	} catch (Exception& e) {

	}

	sceneObject->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, NULL, 0);

	VectorMap<uint32, ManagedReference<Facade*> >* objectActiveSessions = sceneObject->getObjectActiveSessions();

	while (objectActiveSessions->size()) {
		ManagedReference<Facade*> facade = objectActiveSessions->remove(0).getValue();

		if (facade == NULL)
			continue;

		facade->cancelSession();
		//objectActiveSessions.remove(0);
	}

	//activeAreas.removeAll();

	info("removed from zone");
}

void ZoneComponent::removeFromBuilding(SceneObject* sceneObject, BuildingObject* building) {
	SceneObject* parent = sceneObject->getParent();
	Zone* zone = sceneObject->getZone();

	if (/*!sceneObject->isInQuadTree() || */!parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

    sceneObject->broadcastMessage(sceneObject->link((uint64)0, (uint32)0xFFFFFFFF), true, false);

    parent->removeObject(sceneObject);

    if (building != NULL) {
    	building->remove(sceneObject);

    	building->removeNotifiedSentObject(sceneObject);
    }
}

void ZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) {
	sceneObject->notifySelfPositionUpdate();
}
