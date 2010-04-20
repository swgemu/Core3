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

#include "SceneObject.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/scene/UpdateContainmentMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/scene/ClientOpenContainerMessage.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"

#include "server/zone/ZoneClientSession.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServerImplementation.h"

#include "variables/StringId.h"
#include "events/ObjectUpdateToDatabaseTask.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	notifiedSentObjects.setNoDuplicateInsertPlan();
	slottedObjects.setNullValue(NULL);
	slottedObjects.setNoDuplicateInsertPlan();
	containerObjects.setNullValue(NULL);
	containerObjects.setNoDuplicateInsertPlan();
	positionChangedObservers.setNoDuplicateInsertPlan();

	server = ZoneProcessServerImplementation::instance;

	movementCounter = 0;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");
}

void SceneObjectImplementation::loadTemplateData(LuaObject* templateData) {
	SceneObjectImplementation::parent = NULL;

	slottedObjects.setNullValue(NULL);
	objectName.setStringId(String(templateData->getStringField("objectName")));

	detailedDescription.setStringId(String(templateData->getStringField("detailedDescription")));

	containerType = templateData->getIntField("containerType");
	containerVolumeLimit = templateData->getIntField("containerVolumeLimit");

	gameObjectType = templateData->getIntField("gameObjectType");

	clientObjectCRC = templateData->getIntField("clientObjectCRC");

	LuaObject arrangements = templateData->getObjectField("arrangementDescriptors");

	for (int i = 1; i <= arrangements.getTableSize(); ++i) {
		arrangementDescriptors.add(arrangements.getStringAt(i));
	}

	arrangements.pop();

	LuaObject slots = templateData->getObjectField("slotDescriptors");

	for (int i = 1; i <= slots.getTableSize(); ++i) {
		slotDescriptors.add(slots.getStringAt(i));
	}

	slots.pop();

	zone = NULL;

	containmentType = 4;

	initializePosition(0.f, 0.f, 0.f);

	movementCounter = 0;

	staticObject = false;
}

void SceneObjectImplementation::create(ZoneClientSession* client) {
	BaseMessage* msg = new SceneObjectCreateMessage(_this);

	client->sendMessage(msg);
}

void SceneObjectImplementation::close(ZoneClientSession* client) {
	BaseMessage* msg = new SceneObjectCloseMessage(_this);

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(ZoneClientSession* client, uint32 containmentType) {
	BaseMessage* msg = new UpdateContainmentMessage(_this, parent, containmentType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(uint64 objectID, uint32 containmentType) {
	return new UpdateContainmentMessage(getObjectID(), objectID, containmentType);
}

void SceneObjectImplementation::updateToDatabase() {
	updateToDatabaseAllObjects(true);
}

void SceneObjectImplementation::updateToDatabaseWithoutChildren() {
	ZoneServer* server = getZoneServer();
	server->updateObjectToDatabase(_this);
}

void SceneObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	if (!isPersistent())
		return;

	Time start;

	ZoneServer* server = getZoneServer();
	server->updateObjectToDatabase(_this);

	for (int i = 0; i < slottedObjects.size(); ++i) {
		ManagedReference<SceneObject*> object = slottedObjects.get(i);

		object->updateToDatabaseAllObjects(false);
	}

	for (int j = 0; j < containerObjects.size(); ++j) {
		ManagedReference<SceneObject*> object = containerObjects.get(j);

		object->updateToDatabaseAllObjects(false);
	}

	if (startTask)
		queueUpdateToDatabaseTask();

	info("saved in " + String::valueOf(start.miliDifference()) + " ms");
}

void SceneObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	info("deleting from database", true);

	ZoneServer* server = getZoneServer();

	server->destroyObjectFromDatabase(getObjectID());

	_this->setPersistent(0);

	if (!destroyContainedObjects)
		return;

	for (int i = 0; i < slottedObjects.size(); ++i) {
		ManagedReference<SceneObject*> object = slottedObjects.get(i);

		object->destroyObjectFromDatabase(true);
	}

	for (int j = 0; j < containerObjects.size(); ++j) {
		ManagedReference<SceneObject*> object = containerObjects.get(j);

		object->destroyObjectFromDatabase(true);
	}
}

uint64 SceneObjectImplementation::getObjectID() {
	return _this->_getObjectID();
}

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (isStaticObject())
		return;

	ManagedReference<ZoneClientSession*> client = player->getClient();

	if (client == NULL)
		return;

	/*StringBuffer msg;
	msg << "sending 0x" << hex << getClientObjectCRC() << " oid 0x" << hex << getObjectID();
	info(msg.toString());*/

	create(client);

	if (parent != NULL)
		link(client.get(), containmentType);

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player);

	if (doClose)
		SceneObjectImplementation::close(client);
}

void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	for (int i = 0; i < slottedObjects.size(); ++i) {
		SceneObject* object = slottedObjects.get(i);

		object->sendTo(player);
	}
}

void SceneObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	//sending all objects by default
	for (int j = 0; j < containerObjects.size(); ++j) {
		SceneObject* containerObject = containerObjects.get(j);

		containerObject->sendTo(player);
	}
}

void SceneObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (staticObject)
		return;

	destroy(player->getClient());
}

void SceneObjectImplementation::sendAttributeListTo(PlayerCreature* object) {
	info("sending attribute list", true);

	AttributeListMessage* alm = new AttributeListMessage(_this);

	fillAttributeList(alm, object);

	object->sendMessage(alm);
}

void SceneObjectImplementation::destroy(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::broadcastObject(SceneObject* object, bool sendSelf) {
	if (zone == NULL) {
		SceneObject* grandParent = getGrandParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

		if (!sendSelf && scno == this)
			continue;

		if (scno->isPlayerCreature()) {
			object->sendTo((SceneObject*) scno->_getStub());
		}
	}

}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf) {
	if (zone == NULL) {
		SceneObject* grandParent = getGrandParent();

		if (grandParent != NULL) {
			grandParent->broadcastMessage(message, sendSelf);

			return;
		} else {
			delete message;

			return;
		}
	}

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

		if (!sendSelf && scno == this)
			continue;

		if (scno->isPlayerCreature()) {
			scno->sendMessage(message->clone());
		}
	}

	delete message;
}

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	if (zone == NULL) {
		SceneObject* grandParent = getGrandParent();

		if (grandParent != NULL) {
			grandParent->broadcastMessages(messages, sendSelf);

			return;
		} else {
			while (!messages->isEmpty()) {
				delete messages->remove(0);
			}

			return;
		}
	}

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

		if (!sendSelf && scno == this)
			continue;

		if (scno->isPlayerCreature()) {
			for (int j = 0; j < messages->size(); ++j) {
				BasePacket* msg = messages->get(j);
				scno->sendMessage(msg->clone());
			}
		}
	}

	while (!messages->isEmpty()) {
		delete messages->remove(0);
	}
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
	delete msg;
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (!isInQuadTree() || !parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

    broadcastMessage(link((uint64)0, (uint32)0xFFFFFFFF), true);

    parent->removeObject(_this);

    building->remove(this);
    building->removeNotifiedSentObject(_this);
}

void SceneObjectImplementation::updateVehiclePosition() {
	if (parent == NULL || !parent->isVehicleObject())
		return;

	try {
		parent->wlock();

		parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
		parent->setPosition(positionX, positionZ, positionY);

		parent->incrementMovementCounter();

		parent->updateZone(true);

		parent->unlock();
	} catch (...) {
		error("Unreported exception in SceneObjectImplementation::updateVehiclePosition()");
		parent->unlock();
	}
}

void SceneObjectImplementation::updateZone(bool lightUpdate) {
	if (zone == NULL)
		return;

	if (parent != NULL && parent->isVehicleObject())
		updateVehiclePosition();

	Locker zoneLocker(zone);

	if (parent != NULL && parent->isCellObject()) {
		CellObject* cell = (CellObject*)parent.get();

		removeFromBuilding((BuildingObject*)cell->getParent());

		setParent(NULL);

		zone->insert(this);
	} else
		zone->update(this);

	zone->inRange(this, 128);

	if (parent == NULL || !parent->isVehicleObject()) {
		if (lightUpdate) {
			LightUpdateTransformMessage* message = new LightUpdateTransformMessage(_this);
			broadcastMessage(message, false);
		} else {
			UpdateTransformMessage* message = new UpdateTransformMessage(_this);
			broadcastMessage(message, false);
		}
	}

	zoneLocker.release();

	onPositionUpdate();
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate) {
	if (zone == NULL)
		return;

	if (parent != NULL && parent->isVehicleObject())
		return;

	bool insert = false;

	Locker zoneLocker(zone);

	if (newParent != parent) {
		if (parent == NULL) {
			zone->remove(this);
			insert = true;
		} else {
			if (parent->isCellObject()) {
				BuildingObject* building = (BuildingObject*) parent->getParent();
				SceneObject* newObj = newParent->getParent();

				BuildingObject* newBuilding = (BuildingObject*) newObj;

				if (building != newBuilding) {
					//System::out << "Does this actually ever happen when someone goes from one building to another?" << endl;

					removeFromBuilding(building);

					insert = true;
				}

				// remove from old cell
				if (parent != NULL)
					parent->removeObject(_this);
			} else
				insert = true;
		}

		//System::out << "Cell Transition.  Old: " << hex << parent <<  dec << " New: " << hex << newParent << dec << endl;
		// add to new cell
		//parent = newParent;
		newParent->addObject(_this, -1);

		broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true);
	}

	BuildingObject* building = (BuildingObject*) parent->getParent();

	if (insert) {
		info("insertToBuilding from updateZoneWithParent");
		insertToBuilding(building);
	} else {
		building->update(this);
		building->inRange(this, 128);
	}

	if (lightUpdate) {
		LightUpdateTransformWithParentMessage* message = new LightUpdateTransformWithParentMessage(_this);
		broadcastMessage(message, false);
	} else {
		UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(_this);
		broadcastMessage(message, false);
	}

	onPositionUpdate();
}

void SceneObjectImplementation::insertToZone(Zone* newZone) {
	Locker zoneLocker(newZone);

	if (isInQuadTree() && newZone != zone) {
		error("trying to insert to zone an object that is already in a different quadtree");
		StackTrace::printStackTrace();
	}

	SceneObjectImplementation::zone = newZone;

	zone->addSceneObject(_this);

	initializePosition(positionX, positionZ, positionY);

	sendToOwner(true);

	if (isInQuadTree()) {
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			notifyInsert(getInRangeObject(i));
		}
	}

	if (parent == NULL || !parent->isCellObject()) {
		zone->insert(this);
		zone->inRange(this, 128);
	} else if (parent->isCellObject()) {
		BuildingObject* building = (BuildingObject*) parent->getParent();
		insertToBuilding(building);
	}

	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();
	positionChangedObservers.put(terrainManager);

	movementCounter = 0;
}

void SceneObjectImplementation::switchZone(int newZoneID, float newPostionX, float newPositionZ, float newPositionY) {
	if (zone == NULL)
		return;

	removeFromZone();

	ZoneServer* server = getZoneServer();
	Zone* zone = server->getZone(newZoneID);

	initializePosition(newPostionX, newPositionZ, newPositionY);

	insertToZone(zone);
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	if (isInQuadTree() || !parent->isCellObject())
		return;

	try {
		//info("SceneObjectImplementation::insertToBuilding");

		//parent->addObject(_this, 0xFFFFFFFF);

		building->insert(this);
		building->inRange(this, 128);

		building->notifyInsertToZone(_this);

		broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true);

		//info("sent cell link to everyone else");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	} catch (...) {
		error("exception SceneObjectImplementation::insertToBuilding(BuildingObject* building)");
	}
}

void SceneObjectImplementation::removeFromZone() {
	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> thisLocker = _this;

	info("removing from zone");

	Locker zoneLocker(zone);

	ManagedReference<SceneObject*> par = parent.get();

	if (parent != NULL && parent->isCellObject()) {
		BuildingObject* building = (BuildingObject*)parent->getParent();

		par = parent;

		removeFromBuilding(building);
	} else
		zone->remove(this);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);

		if (obj != this)
			obj->removeInRangeObject(this);
	}

	removeInRangeObjects();

	zone->dropSceneObject(getObjectID());

	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();
	positionChangedObservers.drop(terrainManager);

	zone = NULL;

	info("removed from zone");
}

bool SceneObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	if (containerType == 1 || containerType == 5) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement))
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i) {
			slottedObjects.put(object->getArrangementDescriptor(i), object);
		}
	} else if (containerType == 2 || containerType == 3) {
		if (containerObjects.size() >= containerVolumeLimit)
			return false;

		if (containerObjects.contains(object->getObjectID()))
			return false;

		containerObjects.put(object->getObjectID(), object);
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(_this);
	object->setContainmentType(containmentType);

	if (notifyClient)
		broadcastMessage(object->link(getObjectID(), containmentType), true);

	return true;
}

bool SceneObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	ManagedReference<SceneObject*> objectKeeper = object;

	if (containerType == 1 || containerType == 5) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.get(childArrangement) != object)
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i)
			slottedObjects.drop(object->getArrangementDescriptor(i));
	} else if (containerType == 2 || containerType == 3) {
		if (!containerObjects.contains(object->getObjectID()))
			return false;

		containerObjects.drop(object->getObjectID());
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(NULL);

	if (notifyClient)
		broadcastMessage(object->link((uint64) 0, 0xFFFFFFFF), true);

	return true;
}

void SceneObjectImplementation::openContainerTo(PlayerCreature* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this);
	player->sendMessage(cont);
}

void SceneObjectImplementation::closeContainerTo(PlayerCreature* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this, true);
	player->sendMessage(cont);
}

void SceneObjectImplementation::getContainmentObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	objects = slottedObjects;
}

SceneObject* SceneObjectImplementation::getGrandParent() {
	if (parent == NULL)
		return NULL;

	SceneObject* grandParent = parent;

	while (grandParent->getParent() != NULL)
		grandParent = grandParent->getParent();

	return grandParent;
}

bool SceneObjectImplementation::isASubChildOf(SceneObject* object) {
	if (parent == NULL)
		return false;

	if (parent == object)
		return true;

	SceneObject* grandParent = parent;

	while (grandParent->getParent() != NULL) {
		grandParent = grandParent->getParent();

		if (grandParent == object)
			return true;
	}

	return false;
}

float SceneObjectImplementation::getDistanceTo(SceneObject* targetCreature) {
	// TEMP till
	float x = targetCreature->getPositionX();
	float y = targetCreature->getPositionY();

	float deltaX = x - positionX;
	float deltaY = y - positionY;

	return Math::sqrt(deltaX * deltaX + deltaY * deltaY);
}
