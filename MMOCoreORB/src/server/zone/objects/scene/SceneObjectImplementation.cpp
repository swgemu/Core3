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

#include "engine/util/Facade.h"

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
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/ZoneClientSession.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"

#include "variables/StringId.h"
#include "events/ObjectUpdateToDatabaseTask.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/ChildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	// FIXME: temp hack
	server = Core::lookupObject<ZoneProcessServer>("ZoneProcessServer");

	templateObject = TemplateManager::instance()->getTemplate(serverObjectCRC);

	movementCounter = 0;

	//activeAreas.removeAll();

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");
}

void SceneObjectImplementation::initializePrivateData() {
	notifiedSentObjects.setNoDuplicateInsertPlan();
	slottedObjects.setNullValue(NULL);
	slottedObjects.setNoDuplicateInsertPlan();
	containerObjects.setNullValue(NULL);
	containerObjects.setNoDuplicateInsertPlan();
	pendingTasks.setNoDuplicateInsertPlan();
	pendingTasks.setNullValue(NULL);
	objectActiveSessions.setNullValue(NULL);
	objectActiveSessions.setNoDuplicateInsertPlan();
	activeAreas.setNoDuplicateInsertPlan();

	server = NULL;

	templateObject = NULL;

	parent = NULL;

	movementCounter = 0;

	serverObjectCRC = 0;
	clientObjectCRC = 0;

	containerType = 0;
	containerVolumeLimit = 0;
	gameObjectType = 0;
	clientGameObjectType = 0;
	containmentType = 0;

	zone = NULL;

	containmentType = 4;

	initializePosition(0.f, 0.f, 0.f);

	movementCounter = 0;

	staticObject = false;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");

	outdoorChildObjects.setNoDuplicateInsertPlan();
}

void SceneObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	slottedObjects.setNullValue(NULL);
	objectName.setStringId(templateData->getObjectName());

	//detailedDescription.setStringId(templateData->getDetailedDescription());

	containerType = templateData->getContainerType();
	containerVolumeLimit = templateData->getContainerVolumeLimit();

	if (containerVolumeLimit == 0 || containerVolumeLimit == 1)
		containerObjects.removeAll(1, 1);

	gameObjectType = templateData->getGameObjectType();
	clientGameObjectType = templateData->getClientGameObjectType();
	clientObjectCRC = templateData->getClientObjectCRC();

	/*arrangementDescriptors = templateData->getArrangementDescriptors();

	slotDescriptors = templateData->getSlotDescriptors();*/

	if (templateData->getCollisionActionBlockFlags() == 255) { //loading meshes for line of sight
		templateData->getPortalLayout();
		templateData->getAppearanceTemplate();
	}

	templateObject = templateData;
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
	//updateToDatabaseAllObjects(true);
}

void SceneObjectImplementation::updateToDatabaseWithoutChildren() {
	/*ZoneServer* server = getZoneServer();
	server->updateObjectToDatabase(_this);*/
}

void SceneObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	/*if (!isPersistent())
		return;

	Time start;

	ZoneServer* server = getZoneServer();
	server->updateObjectToDatabase(_this);

	SortedVector<SceneObject*> savedObjects(slottedObjects.size() + 1, 5);
	savedObjects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slottedObjects.size(); ++i) {
		ManagedReference<SceneObject*> object = slottedObjects.get(i);

		if (savedObjects.put(object) != -1) {
			object->updateToDatabaseAllObjects(false);
		}
	}

	for (int j = 0; j < containerObjects.size(); ++j) {
		ManagedReference<SceneObject*> object = containerObjects.get(j);

		object->updateToDatabaseAllObjects(false);
	}

	if (startTask)
		queueUpdateToDatabaseTask();
		*/

	//info("saved in " + String::valueOf(start.miliDifference()) + " ms");
}

void SceneObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	//info("deleting from database", true);

	ZoneServer* server = getZoneServer();

	server->destroyObjectFromDatabase(getObjectID());

	_this->setPersistent(0);

	if (!destroyContainedObjects)
		return;

	SortedVector<ManagedReference<SceneObject*> > destroyedObjects;
	destroyedObjects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slottedObjects.size(); ++i) {
		ManagedReference<SceneObject*> object = slottedObjects.get(i);

		if (destroyedObjects.put(object) != -1)
			object->destroyObjectFromDatabase(true);
	}

	for (int j = 0; j < containerObjects.size(); ++j) {
		ManagedReference<SceneObject*> object = containerObjects.get(j);

		if (destroyedObjects.put(object) != -1)
			object->destroyObjectFromDatabase(true);
	}

	//Remove all outdoor child objects from database
	while (outdoorChildObjects.size() > 0) {
		ManagedReference<SceneObject*> outdoorChild = outdoorChildObjects.get(0);

		if (outdoorChild == NULL)
			continue;

		outdoorChild->destroyObjectFromDatabase(true);
		outdoorChildObjects.remove(0);
	}
}

uint64 SceneObjectImplementation::getObjectID() {
	return _this->_getObjectID();
}

void SceneObjectImplementation::sendWithoutParentTo(SceneObject* player) {
	ManagedReference<ZoneClientSession*> client = player->getClient();

	if (client == NULL)
		return;

	create(client);

	/*if (parent != NULL)
		link(client.get(), containmentType);*/

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player);

	SceneObjectImplementation::close(client);
}

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (isStaticObject())
		return;

	ManagedReference<ZoneClientSession*> client = player->getClient();

	if (client == NULL)
		return;

	/*StringBuffer msg;
	if (parent != NULL)
		msg << "with parent " << parent->getLoggingName() << " ";
	msg << "sending 0x" << hex << getClientObjectCRC() << " to " << player->getLoggingName();
	info(msg.toString(), true);*/

	create(client);

	if (parent != NULL)
		link(client.get(), containmentType);

	sendBaselinesTo(player);

	sendContainerObjectsTo(player);

	sendSlottedObjectsTo(player);

	if (doClose) {
		SceneObjectImplementation::close(client);
		//info("sending close", true);
	}
}

void SceneObjectImplementation::sendWithoutContainerObjectsTo(SceneObject* player) {
	if (isStaticObject())
		return;

	ManagedReference<ZoneClientSession*> client = player->getClient();

	if (client == NULL)
		return;

	create(client);

	if (parent != NULL)
		link(client.get(), containmentType);

	sendBaselinesTo(player);

	SceneObjectImplementation::close(client);
}

void SceneObjectImplementation::notifyLoadFromDatabase() {

	//Correcting linked list errors becaused of DB errors
	for (int i = 0; i < slottedObjects.size(); ++i) {
		SceneObject* object = slottedObjects.get(i);

		//object->setContainmentType(4);

		bool inSlotted = false, inContainer = false;

		if (object->getParent() == NULL) {
			object->setParent(_this);
			object->setContainmentType(4);
		} else if (object->getParent() != _this) {
			if ((inSlotted = object->getParent()->hasObjectInSlottedContainer(object))
					|| (inContainer = object->getParent()->hasObjectInContainer(object->getObjectID()))) {
				int arrangementSize = object->getArrangementDescriptorSize();

				for (int j = 0; j < arrangementSize; ++j)
					slottedObjects.drop(object->getArrangementDescriptor(j));

				for (int j = 0; j < slottedObjects.size(); ++j) {
					if (slottedObjects.get(j) == object) {
						slottedObjects.remove(j);
						--j;
					}
				}

				i -= arrangementSize;

				i = (i < -1) ? -1 : i;

				if (inSlotted)
					object->setContainmentType(4);
				else
					object->setContainmentType(-1);
			} else {
				object->setParent(_this);
				object->setContainmentType(4);
			}

		} else
			object->setContainmentType(4);
	}

	for (int i = 0; i < containerObjects.size(); ++i) {
		SceneObject* object = containerObjects.get(i);

		bool inSlotted = false, inContainer = false;

		if (object->getParent() == NULL) {
			object->setParent(_this);
			object->setContainmentType(-1);
		} else if (object->getParent() != _this) {
			if ((inSlotted = object->getParent()->hasObjectInSlottedContainer(object))
					|| (inContainer = object->getParent()->hasObjectInContainer(object->getObjectID()))) {
				containerObjects.removeElementAt(i);
				//containerObjects.drop(object->getObjectID());
				--i;

				i = (i < -1) ? -1 : i;

				if (inSlotted)
					object->setContainmentType(4);
				else
					object->setContainmentType(-1);
			} else {
				object->setParent(_this);
				object->setContainmentType(-1);
			}
		} else
			object->setContainmentType(-1);
	}

	if (zone != NULL) {
		insertToZone(zone);
	}

}

void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	SortedVector<SceneObject*> objects(slottedObjects.size(), slottedObjects.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slottedObjects.size(); ++i) {
		SceneObject* object = slottedObjects.get(i);

		if (object->getParent() == NULL)
			object->setParent(_this);

		if (object->getContainmentType() != 4)
			object->setContainmentType(4);

		if (objects.put(object) != -1) {
			if (object->isInQuadTree()) {
				notifyInsert((QuadTreeEntry*) object->_getImplementation());
			} else {
				object->sendTo(player, true);
			}
		}
	}
}

void SceneObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	//sending all objects by default
	SortedVector<uint64> objects(containerObjects.size(), containerObjects.size());
	objects.setNoDuplicateInsertPlan();

	for (int j = 0; j < containerObjects.size(); ++j) {
		SceneObject* containerObject = containerObjects.get(j);

		if (containerObject->getParent() == NULL)
			containerObject->setParent(_this);

		if (containerObject->getContainmentType() != -1)
			containerObject->setContainmentType(-1);

		if (objects.put(containerObject->getObjectID()) != -1) {
			if (containerObject->isInQuadTree()) {
				notifyInsert((QuadTreeEntry*) containerObject->_getImplementation());
			} else {
				containerObject->sendTo(player, true);
			}
		}
	}
}

void SceneObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (staticObject)
		return;

	/*StringBuffer msg;
	msg << "sending destroy to " << player->getLoggingName();
	info(msg.toString(), true);*/

	destroy(player->getClient());
}

void SceneObjectImplementation::sendAttributeListTo(PlayerCreature* object) {
	info("sending attribute list");

	AttributeListMessage* alm = new AttributeListMessage(_this);

	try {
		fillAttributeList(alm, object);
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		delete alm;
		alm = NULL;
	} catch (...) {
		error("unreported exception caught in SceneObjectImplementation::sendAttributeListTo");
		delete alm;
		alm = NULL;

		throw;
	}

	if (alm != NULL)
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
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* scno = (SceneObject*) getInRangeObject(i);

		if (!sendSelf && scno == _this)
			continue;

		if (scno->isPlayerCreature()) {
			object->sendTo(scno, true);
		}
	}

}

void SceneObjectImplementation::broadcastDestroy(SceneObject* object, bool sendSelf) {
	if (zone == NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* scno = (SceneObject*) getInRangeObject(i);

		if (!sendSelf && scno == _this)
			continue;

		if (scno->isPlayerCreature()) {
			object->sendDestroyTo(scno);
		}
	}

}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	if (zone == NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastMessage(message, sendSelf, lockZone);

			return;
		} else {
			delete message;

			return;
		}
	}

	//Locker zoneLocker(zone);

	zone->rlock(lockZone);

	try {
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* scno = (SceneObject*) getInRangeObject(i);

			if (!sendSelf && scno == _this)
				continue;

			if (scno->isPlayerCreature()) {
				scno->sendMessage(message->clone());
			}
		}
	} catch (...) {
		zone->runlock(lockZone);

		delete message;

		throw;
	}

	zone->runlock(lockZone);

	delete message;
}

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	if (zone == NULL) {
		SceneObject* grandParent = getRootParent();

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

	zone->rlock();

	try {

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* scno = (SceneObject*) getInRangeObject(i);

			if (!sendSelf && scno == _this)
				continue;

			if (scno->isPlayerCreature()) {
				for (int j = 0; j < messages->size(); ++j) {
					BasePacket* msg = messages->get(j);
					scno->sendMessage(msg->clone());
				}
			}
		}

	} catch (Exception& e) {

	}

	zone->runlock();

	while (!messages->isEmpty()) {
		delete messages->remove(0);
	}
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	if (zone == NULL)
		return 0;

	int numberOfObjects = 0;

	Locker zoneLocker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* scno = (SceneObject*) getInRangeObject(i);

		if (scno->isInRange(_this, range) && scno->getGameObjectType() == gameObjectType)
			++numberOfObjects;
	}

	return numberOfObjects;
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
	delete msg;
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (/*!isInQuadTree() || */!parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

    broadcastMessage(link((uint64)0, (uint32)0xFFFFFFFF), true, false);

    parent->removeObject(_this);

    if (building != NULL) {
    	building->remove(_this);

    	building->removeNotifiedSentObject(_this);
    }
}

void SceneObjectImplementation::updateVehiclePosition() {
	if (parent == NULL || !parent->isVehicleObject())
		return;

	Locker locker(parent);

	parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
	parent->setPosition(positionX, positionZ, positionY);

	parent->incrementMovementCounter();

	parent->updateZone(true);
}

void SceneObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	if (zone == NULL)
		return;

	if (parent != NULL && parent->isVehicleObject())
		updateVehiclePosition();

	Locker zoneLocker(zone);

	if (parent != NULL && parent->isCellObject()) {
		CellObject* cell = (CellObject*)parent.get();

		if (cell->getParent() !=NULL)
			removeFromBuilding((BuildingObject*)cell->getParent());

		setParent(NULL);

		zone->insert(_this);
	} else
		zone->update(_this);

	zone->inRange(_this, 192);

	if (sendPackets && (parent == NULL || !parent->isVehicleObject())) {
		if (lightUpdate) {
			LightUpdateTransformMessage* message = new LightUpdateTransformMessage(_this);
			broadcastMessage(message, false, false);
		} else {
			UpdateTransformMessage* message = new UpdateTransformMessage(_this);
			broadcastMessage(message, false, false);
		}
	}

	zone->updateActiveAreas(_this);

	//zoneLocker.release();

	zone->unlock();

	try {
		notifySelfPositionUpdate();
	} catch (Exception& e) {

	}

	zone->wlock();

	//notifySelfPositionUpdate();
}

void SceneObjectImplementation::notifySelfPositionUpdate() {
	notifyObservers(ObserverEventType::POSITIONCHANGED);
}

void SceneObjectImplementation::notifyCloseContainer(PlayerCreature* player) {
	notifyObservers(ObserverEventType::CLOSECONTAINER, player);
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	if (zone == NULL)
		return;

	if (parent != NULL && parent->isVehicleObject())
		return;

	bool insert = false;

	/*StringBuffer msg;
	msg << "world posx: " << getWorldPositionX() << " wolrd posy: " << getWorldPositionY() << " posz: " << getWorldPositionZ();
	info(msg.toString(), true);

	StringBuffer msg2;
	msg2 << "cell x: " << positionX << " cell y: " << positionY;
	info(msg2.toString(), true);*/

	Locker zoneLocker(zone);

	if (newParent != parent) {
		if (parent == NULL) {
			zone->remove(_this);
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
					parent->removeObject(_this, false);
			} else
				insert = true;
		}

		//System::out << "Cell Transition.  Old: " << hex << parent <<  dec << " New: " << hex << newParent << dec << endl;
		// add to new cell
		//parent = newParent;
		if (!newParent->addObject(_this, -1, false)) {
			error("could not add to parent " + newParent->getLoggingName());
		}

		broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true, false);
	}

	ManagedReference<BuildingObject*> building = (BuildingObject*) parent->getParent();

	if (insert) {
		info("insertToBuilding from updateZoneWithParent");
		insertToBuilding(building);
	} else {
		building->update(_this);

		building->inRange(_this, 192);
	}

	if (sendPackets) {
		if (lightUpdate) {
			LightUpdateTransformWithParentMessage* message = new LightUpdateTransformWithParentMessage(_this);
			broadcastMessage(message, false, false);
		} else {
			UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(_this);
			broadcastMessage(message, false, false);
		}
	}

	zone->updateActiveAreas(_this);

	//zoneLocker.release();

	zone->unlock();

	try {
		notifySelfPositionUpdate();
	} catch (Exception& e) {

	}

	zone->wlock();
}

void SceneObjectImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {

	ZoneServer* zoneServer = getZoneServer();

	if (zone == NULL)
		return;

	Locker locker(zone);

	if (parentID != 0) {
		ManagedReference<SceneObject*> newParent = zoneServer->getObject(parentID);

		if (newParent == NULL || !newParent->isCellObject())
			return;

		if (newPositionX != positionX || newPositionZ != positionZ || newPositionY != positionY) {
			setPosition(newPositionX, newPositionZ, newPositionY);
			updateZoneWithParent(newParent, false, false);
		}

		DataTransformWithParent* pack = new DataTransformWithParent(_this);
		broadcastMessage(pack, true, false);
	} else {
		if (newPositionX != positionX || newPositionZ != positionZ || newPositionY != positionY) {
			setPosition(newPositionX, newPositionZ, newPositionY);
			updateZone(false, false);
		}

		DataTransform* pack = new DataTransform(_this);
		broadcastMessage(pack, true, false);
	}
}

void SceneObjectImplementation::insertToZone(Zone* newZone) {
	info("inserting to zone");

	if (newZone == NULL)
		return;

	activeAreas.removeAll();

	Locker zoneLocker(newZone);

	if (isInQuadTree() && newZone != zone) {
		error("trying to insert to zone an object that is already in a different quadtree");

		removeFromZone();

		//StackTrace::printStackTrace();
	}

	SceneObjectImplementation::zone = newZone;

	zone->addSceneObject(_this);

	if (parent != NULL && parent->isCellObject())
		parent->addObject(_this, -1, false);

	notifiedSentObjects.removeAll();

	sendToOwner(true);

	if (isInQuadTree()) {
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) getInRangeObject(i);

			notifyInsert(object);

			if (object != _this) {
				if (object->getParentRecursively(SceneObject::BUILDING) != NULL) {
					if (notifiedSentObjects.put(object) != -1)
						object->sendTo(_this, true);
				}

				if (object->isPlayerCreature()) {
					object->notifyDissapear(_this);
					object->notifyInsert(_this);
				}
			}
		}
	} else {
		initializePosition(positionX, positionZ, positionY);

		movementCounter = 0;

		if (parent == NULL || !parent->isCellObject() || parent->getParent() == NULL) {
			zone->insert(_this);

			zone->inRange(_this, 192);
		} else if (parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();
			insertToBuilding(building);

			building->notifyInsertToZone(_this);
		}
	}

	//Insert all outdoor child objects to zone
	for (int i = 0; i < outdoorChildObjects.size(); ++i) {
		ManagedReference<SceneObject*> outdoorChild = outdoorChildObjects.get(i);

		if (outdoorChild == NULL)
			continue;

		outdoorChild->insertToZone(zone);
	}

	zone->updateActiveAreas(_this);

	teleport(positionX, positionZ, positionY, getParentID());
}

void SceneObjectImplementation::switchZone(const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	ManagedReference<SceneObject*> thisLocker = _this;

	if (zone == NULL)
		return;

	Zone* newZone = getZoneServer()->getZone(newTerrainName);

	if (newZone == NULL)
		return;

	removeFromZone();

	SceneObject* newParent = getZoneServer()->getObject(parentID);

	Locker locker(newZone);

	if (newParent != NULL && newParent->isCellObject())
		newParent->addObject(_this, -1, false);

	initializePosition(newPostionX, newPositionZ, newPositionY);

	insertToZone(newZone);
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	if (isInQuadTree() || !parent->isCellObject())
		return;

	try {
		//info("SceneObjectImplementation::insertToBuilding");

		//parent->addObject(_this, 0xFFFFFFFF);

		building->insert(_this);

		building->inRange(_this, 192);

		broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true, false);

		//info("sent cell link to everyone else");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void SceneObjectImplementation::removeFromZone() {
	ManagedReference<SceneObject*> thisLocker = _this;

	try {
		Locker locker(_this);

		if (zone == NULL)
			return;

		info("removing from zone");

		Locker zoneLocker(zone);

		//ManagedReference<SceneObject*> par = parent.get();

		if (parent != NULL && parent->isCellObject()) {
			BuildingObject* building = (BuildingObject*)parent->getParent();

			//par = parent;
			if (building != NULL)
				removeFromBuilding(building);
			else
				zone->remove(_this);
		} else
			zone->remove(_this);

		while (inRangeObjectCount() > 0) {
			QuadTreeEntry* obj = getInRangeObject(0);

			if (obj != _this)
				obj->removeInRangeObject(_this);

			QuadTreeEntryImplementation::removeInRangeObject((int) 0);
		}

		while (activeAreas.size() > 0) {
			ManagedReference<ActiveArea*> area = activeAreas.get(0);
			area->enqueueExitEvent(_this);

			activeAreas.remove(0);
		}

		//Remove all outdoor child objects from zone
		for (int i = 0; i < outdoorChildObjects.size(); ++i) {
			ManagedReference<SceneObject*> outdoorChild = outdoorChildObjects.get(i);

			if (outdoorChild == NULL)
				continue;

			outdoorChild->removeFromZone();
		}

		//removeInRangeObjects();

		notifiedSentObjects.removeAll();

		Zone* oldZone = zone;
		zone = NULL;

		oldZone->dropSceneObject(_this);
	} catch (Exception& e) {

	}

	notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, NULL, 0);

	while (objectActiveSessions.size()) {
		ManagedReference<Facade*> facade = objectActiveSessions.remove(0).getValue();

		if (facade == NULL)
			continue;

		facade->cancelSession();
		//objectActiveSessions.remove(0);
	}

	//activeAreas.removeAll();

	info("removed from zone");
}

void SceneObjectImplementation::notifyAddedToCloseObjects() {
	//_this->acquire();
}

void SceneObjectImplementation::notifyRemovedFromCloseObjects() {
	//_this->release();
}

int SceneObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (_this == object) {
		errorDescription = "@container_error_message:container02";

		return TransferErrorCode::CANTADDTOITSELF;
	}

	if (containmentType == 4) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement)) {
				errorDescription = "@container_error_message:container04";

				return TransferErrorCode::SLOTOCCUPIED;
			}
		}
	} else if (containmentType == -1) {
		if (containerObjects.size() >= containerVolumeLimit) {
			errorDescription = "@container_error_message:container03";

			return TransferErrorCode::CONTAINERFULL;
		}

	} else {
		error("unkown containmentType type");

		errorDescription = "DEBUG: cant move item unkown containmentType type";
		return TransferErrorCode::UNKNOWNCONTAIMENTTYPE;
	}

	return 0;
}

bool SceneObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	if (_this == object)
		return false;

	if (object->getParent() != NULL && object->getParent() != _this) {
		ManagedReference<SceneObject*> objParent = object->getParent();

		if (objParent->hasObjectInContainer(object->getObjectID()) || objParent->hasObjectInSlottedContainer(object)) {
			error("trying to add an object with a parent already");
			objParent->info("the object is in here", true);
			return false;
		} else
			object->setParent(NULL);
	}

	bool update = true;

	//if (containerType == 1 || containerType == 5) {
	if (containmentType == 4) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement)) {
				return false;
			}
		}

		for (int i = 0; i < arrangementSize; ++i) {
			slottedObjects.put(object->getArrangementDescriptor(i), object);
		}
	} else if (containmentType == -1) { /* else if (containerType == 2 || containerType == 3) {*/
		if (containerObjects.size() >= containerVolumeLimit)
			return false;

		/*if (containerObjects.contains(object->getObjectID()))
			return false*/

		if (containerObjects.put(object->getObjectID(), object) == -1)
			update = false;

	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(_this);
	object->setContainmentType(containmentType);

	if (notifyClient)
		broadcastMessage(object->link(getObjectID(), containmentType), true);

	notifyObjectInserted(object);

	if (update) {
		updateToDatabase();
		//object->updateToDatabaseWithoutChildren()();
	}

	return true;
}

bool SceneObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	ManagedReference<SceneObject*> objectKeeper = object;

	if (object->getParent() != _this && object->getParent() != NULL) {
		ManagedReference<SceneObject*> objParent = object->getParent();

		containerObjects.drop(object->getObjectID());

		if (objParent->hasObjectInContainer(object->getObjectID()) || objParent->hasObjectInSlottedContainer(object)) {
			error("trying to remove an object that is in a different object");
			objParent->info("i am the parent", true);

			return false;
		} else
			object->setParent(NULL);
	}

	int containedType = object->getContainmentType();

	//info("trying to remove object with containedType " + String::valueOf(containedType), true);

	if (containedType == 4/*containerType == 1 || containerType == 5*/) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.get(childArrangement) != object) {
				//info("sloted objects contains a different object", true);
				return false;
			}
		}

		for (int i = 0; i < arrangementSize; ++i)
			slottedObjects.drop(object->getArrangementDescriptor(i));
	} else if (containedType == -1/*containerType == 2 || containerType == 3*/) {
		if (!containerObjects.contains(object->getObjectID())) {
			//info("containerObjects doesnt contain specified object", true);
			return false;
		}

		containerObjects.drop(object->getObjectID());
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(NULL);

	if (notifyClient)
		broadcastMessage(object->link((uint64) 0, 0xFFFFFFFF), true);

	notifyObjectRemoved(object);

	updateToDatabase();
	object->updateToDatabase();

	return true;
}

void SceneObjectImplementation::openContainerTo(PlayerCreature* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this);
	player->sendMessage(cont);

	sendContainerObjectsTo(player);
}

void SceneObjectImplementation::closeContainerTo(PlayerCreature* player, bool notify) {

	if(notify) {
		ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this, true);
		player->sendMessage(cont);
	}
}

void SceneObjectImplementation::getContainmentObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	objects = slottedObjects;
}

SceneObject* SceneObjectImplementation::getRootParent() {
	if (parent == NULL)
		return NULL;

	SceneObject* grandParent = parent;

	while (grandParent->getParent() != NULL)
		grandParent = grandParent->getParent();

	return grandParent;
}

SceneObject* SceneObjectImplementation::getParentRecursively(uint32 gameObjectType) {
	if (parent == NULL)
		return NULL;

	SceneObject* temp = parent;

	if (temp->getGameObjectType() == gameObjectType)
		return temp;

	while (temp->getParent() != NULL) {
		temp = temp->getParent();

		if (temp->getGameObjectType() == gameObjectType)
			return temp;
	}

	return NULL;
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

bool SceneObjectImplementation::isInRange(SceneObject* object, float range) {
	Vector3 worldPos = object->getWorldPosition();
	worldPos.setZ(0);
	Vector3 thisPos = getWorldPosition();
	thisPos.setZ(0);

	if (thisPos.squaredDistanceTo(worldPos) <= range * range)
		return true;

	return false;
}

float SceneObjectImplementation::getDistanceTo(SceneObject* targetCreature) {
	// TEMP till
	float x = targetCreature->getWorldPositionX();
	float y = targetCreature->getWorldPositionY();

	float deltaX = x - getWorldPositionX();
	float deltaY = y - getWorldPositionY();

	return Math::sqrt(deltaX * deltaX + deltaY * deltaY);
}

float SceneObjectImplementation::getDistanceTo(Coordinate* coordinate) {
	// TEMP till
	float x = coordinate->getPositionX();
	float y = coordinate->getPositionY();

	float deltaX = x - getWorldPositionX();
	float deltaY = y - getWorldPositionY();

	return Math::sqrt(deltaX * deltaX + deltaY * deltaY);
}

Quaternion* SceneObjectImplementation::getDirection() {
	return &direction;
}

void SceneObjectImplementation::setDirection(const Quaternion& dir) {
	direction = dir;
}

void SceneObjectImplementation::rotate(int degrees) {
	Vector3 unity(0, 1, 0);
	direction.rotate(unity, degrees);
}

void SceneObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//All objects in a cell can be picked up, if the player is on the structures permission list.
	//This opens the door to allow admins to be able to drop/pickup items in public structures
	if (parent == NULL || !parent->isCellObject())
		return;

	ManagedReference<SceneObject*> obj = parent->getParent();

	if (!obj->isBuildingObject())
		return;

	ManagedReference<BuildingObject*> buio = (BuildingObject*) obj.get();

	//Is this player on the permission list?
	if (!buio->isOnAdminList(player))
		return;

	if (isPlayerCreature())
		return;

	menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup"); //Pick up

	menuResponse->addRadialMenuItem(54, 1, "@ui_radial:item_move"); //Move
	menuResponse->addRadialMenuItem(51, 1, "@ui_radial:item_rotate"); //Rotate

	menuResponse->addRadialMenuItemToRadialID(54, 55, 3, "@ui_radial:item_move_forward"); //Move Forward
	menuResponse->addRadialMenuItemToRadialID(54, 56, 3, "@ui_radial:item_move_back"); //Move Back
	menuResponse->addRadialMenuItemToRadialID(54, 57, 3, "@ui_radial:item_move_up"); //Move Up
	menuResponse->addRadialMenuItemToRadialID(54, 58, 3, "@ui_radial:item_move_down"); //Move Down

	menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@ui_radial:item_rotate_left"); //Rotate Left
	menuResponse->addRadialMenuItemToRadialID(51, 53, 3, "@ui_radial:item_rotate_right"); //Rotate Right
}

int SceneObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	case 10: //Pick Up
	{
		//String actionName = "transferitemmisc";
		//player->executeObjectControllerAction(actionName.hashCode(), getObjectID(), "");
		//transferitem
		break;
	}
	}

	return 0;
}

void SceneObjectImplementation::setObjectName(StringId& stringID) {
	objectName = stringID;
}

Vector3 SceneObjectImplementation::getWorldPosition() {
	if (parent == NULL)
		return getPosition();

	SceneObject* root = getRootParent();

	if (!root->isBuildingObject())
		return getPosition();

	float length = Math::sqrt(positionX * positionX + positionY * positionY);
	float angle = root->getDirection()->getRadians() + atan2(positionX, positionY);

	float posX = root->getPositionX() + (sin(angle) * length);
	float posY = root->getPositionY() + (cos(angle) * length);
	float posZ = root->getPositionZ() + positionZ;

	Vector3 position(posX, posY, posZ);

	return position;
}

Vector3 SceneObjectImplementation::getCoordinate(float distance, float angleDegrees) {
	float angleRads = angleDegrees * (M_PI / 180.0f);
	float newAngle = angleRads + direction.getRadians();

	float newX = positionX + (cos(newAngle) * distance); // client has x/y inverted
	float newY = positionY + (sin(newAngle) * distance);
	float newZ = zone->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

float SceneObjectImplementation::getWorldPositionX() {
	if (parent == NULL)
		return positionX;

	SceneObject* root = getRootParent();

	float length = Math::sqrt(positionX * positionX + positionY * positionY);
	float angle = root->getDirection()->getRadians() + atan2(positionX, positionY);

	return root->getPositionX() + (sin(angle) * length);
}

float SceneObjectImplementation::getWorldPositionY() {
	if (parent == NULL)
		return positionY;

	SceneObject* root = getRootParent();

	float length = Math::sqrt(positionX * positionX + positionY * positionY);
	float angle = root->getDirection()->getRadians() + atan2(positionX, positionY);

	return root->getPositionY() + (cos(angle) * length);
}

float SceneObjectImplementation::getWorldPositionZ() {
	if (parent == NULL)
		return positionZ;

	SceneObject* root = getRootParent();

	return root->getPositionZ() + positionZ;
}

uint32 SceneObjectImplementation::getPlanetCRC() {
	if (zone == NULL)
		return 0;

	return zone->getZoneCRC();
}

void SceneObjectImplementation::createChildObjects() {
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();

	for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
		ChildObject* child = templateObject->getChildObject(i);

		if (child == NULL)
			continue;

		ManagedReference<SceneObject*> obj = zoneServer->createObject(child->getTemplateFile().hashCode(), 1);

		if (obj == NULL)
			continue;

		Vector3 childPosition = child->getPosition();

		obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
		obj->setDirection(child->getDirection());

		if (isBuildingObject() && child->getCellId() >= 0) {
			BuildingObject* buildingObject = (BuildingObject*) _this;

			int totalCells = buildingObject->getTotalCellNumber();

			if (totalCells > child->getCellId()) {
				ManagedReference<CellObject*> cellObject = buildingObject->getCell(child->getCellId());

				if (cellObject != NULL) {
					cellObject->addObject(obj, child->getContainmentType(), true);
					cellObject->broadcastObject(obj, false);
				}
			}
		} else {
			//Create the object outdoors in relation to its parent.
			Vector3 position = getPosition();

			float angle = direction.getRadians();

			float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
			float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

			x += position.getX();
			y += position.getY();

			float z = position.getZ() + childPosition.getZ();

			float degrees = direction.getDegrees();

			Quaternion dir = child->getDirection();

			obj->initializePosition(x, z, y);
			obj->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));

			//Add the object to the outdoorChildObjects vector
			outdoorChildObjects.put(obj);
		}

		//TODO: Is there a better way of handling this?
		//If we are inserting a terminal, set it's controlled object to this object by default.
		if (obj->isTerminal()) {
			Terminal* terminal = (Terminal*) obj.get();
			terminal->setControlledObject(_this);
		}

		obj->insertToZone(zone);
		obj->updateToDatabase();
	}
}

SortedVector<ManagedReference<SceneObject*> >* SceneObjectImplementation::getOutdoorChildObjects() {
	return &outdoorChildObjects;
}
