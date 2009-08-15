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

#include "../../managers/object/ObjectManager.h"

#include "../../packets/scene/SceneObjectCreateMessage.h"
#include "../../packets/scene/SceneObjectDestroyMessage.h"
#include "../../packets/scene/SceneObjectCloseMessage.h"
#include "../../packets/scene/UpdateContainmentMessage.h"
#include "../../packets/scene/UpdateTransformMessage.h"
#include "../../packets/scene/UpdateTransformWithParentMessage.h"
#include "../../packets/scene/LightUpdateTransformMessage.h"
#include "../../packets/scene/LightUpdateTransformWithParentMessage.h"
#include "../../packets/scene/AttributeListMessage.h"


#include "../../ZoneClientSession.h"
#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "variables/StringId.h"

#include "../cell/CellObject.h"
#include "../building/BuildingObject.h"

SceneObjectImplementation::SceneObjectImplementation(LuaObject* templateData) : Logger("SceneObject"){
	SceneObjectImplementation::parent = NULL;

	containmentSlots = new VectorMap<String, SceneObject*>();
	containmentSlots->setNullValue(NULL);

	direction = new Quaternion();

	objectName = new StringId(String(templateData->getStringField("objectName")));
	detailedDescription = new StringId(String(templateData->getStringField("detailedDescription")));

	containerType = templateData->getIntField("containerType");
	containerVolumeLimit = templateData->getIntField("containerVolumeLimit");

	containerObjects = new VectorMap<uint64, SceneObject*>(containerVolumeLimit >> 2, containerVolumeLimit / 10);

	gameObjectType = templateData->getIntField("gameObjectType");

	clientObjectCRC = templateData->getIntField("clientObjectCRC");
	serverObjectCRC = 0;

	arrangementDescriptors = new Vector<String>();

	LuaObject arrangements = templateData->getObjectField("arrangementDescriptors");

	for (int i = 1; i <= arrangements.getTableSize(); ++i) {
		arrangementDescriptors->add(arrangements.getStringAt(i));
	}

	arrangements.pop();


	slotDescriptors = new Vector<String>();

	LuaObject slots = templateData->getObjectField("slotDescriptors");

	for (int i = 1; i <= slots.getTableSize(); ++i) {
		slotDescriptors->add(slots.getStringAt(i));
	}

	slots.pop();

	zone = NULL;

	containmentType = 4;

	initializePosition(0.f, 0.f, 0.f);

	setGlobalLogging(true);
	setLogging(false);
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

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose) {
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
	for (int i = 0; i < containmentSlots->size(); ++i) {
		SceneObject* object = containmentSlots->get(i);

		object->sendTo(player);
	}
}

void SceneObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	//sending all objects by default
	for (int j = 0; j < containerObjects->size(); ++j) {
		SceneObject* containerObject = containerObjects->get(j);

		containerObject->sendTo(player);
	}
}

void SceneObjectImplementation::sendDestroyTo(SceneObject* player) {
	destroy(player->getClient());
}

void SceneObjectImplementation::sendAttributeListTo(SceneObject* object) {
	if (!object->isPlayerCreature())
		return;

	info("sending attribute list");

	AttributeListMessage* alm = new AttributeListMessage(_this);

	//addAttributes(alm);

	object->sendMessage(alm);
}

void SceneObjectImplementation::destroy(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	if (zone == NULL) {
		SceneObject* grandParent = getGrandParent();

		if (grandParent != NULL) {
			grandParent->broadcastMessage(message, sendSelf, lockZone);

			return;
		} else {
			message->finalize();

			return;
		}
	}

	try {
		zone->lock(lockZone);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

			if (!sendSelf && scno == this)
				continue;

			if (scno->isPlayerCreature()) {
				scno->sendMessage(message->clone());
			}
		}

		zone->unlock(lockZone);
	} catch (...) {
		error("unreported exception caught in SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone)");
		zone->unlock(lockZone);
	}
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (!isInQuadTree() || !parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

    broadcastMessage(link((uint64)0, (uint32)0xFFFFFFFF), true, false);

    parent->removeObject(_this);

    building->remove(this);
}

void SceneObjectImplementation::updateZone(bool lightUpdate) {
	if (zone == NULL)
		return;

	try {
		zone->lock();

        if (parent != NULL && parent->isCellObject()) {
            CellObject* cell = (CellObject*)parent.get();

            removeFromBuilding((BuildingObject*)cell->getParent());

            parent = NULL;

            zone->insert(this);
        } else
        	zone->update(this);

		zone->inRange(this, 128);

		if (lightUpdate) {
			LightUpdateTransformMessage* message = new LightUpdateTransformMessage(_this);
			broadcastMessage(message, true, false);
		} else {
			UpdateTransformMessage* message = new UpdateTransformMessage(_this);
			broadcastMessage(message, true, false);
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate) {
	if (zone == NULL)
		return;

	bool insert = false;

	try {
		zone->lock();

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

			broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true, false);

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
			broadcastMessage(message, true, false);
		} else {
			UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(_this);
			broadcastMessage(message, true, false);
		}
		zone->unlock();
	} catch (...) {
		zone->unlock();
		error("Exception in PlayerImplementation::updateZoneWithParent");
	}
}

void SceneObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::zone = zone;

	try {
		zone->lock();

		initializePosition(positionX, positionZ, positionY);

		sendToOwner(true);

		if (parent == NULL || !parent->isCellObject()) {
			zone->insert(this);
			zone->inRange(this, 128);
		} else if (parent->isCellObject()) {
            BuildingObject* building = (BuildingObject*) parent->getParent();
            insertToBuilding(building);
		}

		zone->unlock();
	} catch (...) {
		error("unreported exception caught in SceneObjectImplementation::insertToZone(Zone* zone)");
		zone->unlock();
	}
}

void SceneObjectImplementation::switchZone(int newZoneID, float newPostionX, float newPositionZ, float newPositionY) {
	if (zone == NULL)
		return;

	removeFromZone();

	ZoneServer* server = zone->getZoneServer();
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

		broadcastMessage(link(parent->getObjectID(), 0xFFFFFFFF), true, false);

		//info("sent cell link to everyone else");
	} catch (...) {
		error("exception SceneObjectImplementation::insertToBuilding(BuildingObject* building)");
	}
}

void SceneObjectImplementation::removeFromZone(bool lockZone) {
	if (zone == NULL)
		return;

	info("removing from zone");

	try {
		zone->lock(lockZone);

		ManagedReference<SceneObject*> par = parent;

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

		zone->unlock(lockZone);
	} catch (...) {
		zone->unlock(lockZone);
	}

	info("removed from zone");
}

bool SceneObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	if (containerType == 1) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (containmentSlots->contains(childArrangement))
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i) {
			containmentSlots->put(object->getArrangementDescriptor(i), object);
		}
	} else if (containerType == 2) {
		if (containerObjects->size() >= containerVolumeLimit)
			return false;

		if (containerObjects->contains(object->getObjectID()))
			return false;

		containerObjects->put(object->getObjectID(), object);
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(_this);
	object->setContainmentType(containmentType);
	//object->setZone(zone);

	if (notifyClient)
		broadcastMessage(object->link(objectID, containmentType), true, true);

	return true;
}

bool SceneObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	if (containerType == 1) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (containmentSlots->get(childArrangement) != object)
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i)
			containmentSlots->drop(object->getArrangementDescriptor(i));
	} else if (containerType == 2) {
		if (!containerObjects->contains(object->getObjectID()))
			return false;

		containerObjects->drop(object->getObjectID());
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(NULL);

	/*if (notifyClient)
		broadcastMessage(object->link(0, 0xFFFFFFFF));*/

	return true;
}

void SceneObjectImplementation::getContainmentObjects(VectorMap<String, SceneObject* >& objects) {
	objects = *containmentSlots;
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
