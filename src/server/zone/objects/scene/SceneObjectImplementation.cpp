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

#include "../../../ServerCore.h"

#include "../../ZoneClientSession.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../Zone.h"

#include "../../packets.h"

#include "SceneObjectImplementation.h"

#include "engine/core/ManagedObjectImplementation.h"

#include "../building/cell/CellObject.h"

SceneObjectImplementation::SceneObjectImplementation() : SceneObjectServant(), QuadTreeEntry(), Logger() {
	objectID = 0;
	objectType = 0;

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionX = directionZ = directionY = 0;

	parent = NULL;

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;
}

SceneObjectImplementation::SceneObjectImplementation(uint64 oid, int type) : SceneObjectServant(),QuadTreeEntry(), Logger() {
	objectID = oid;
	objectType = type;

	stringstream name;
	name << "SceneObject(" << objectType << ")  0x" << hex << objectID;
	//setDeployingName(name.str());

	server = NULL;
	zone = NULL;

	positionX = positionZ = positionY = 0;
	directionY = 1;
	directionZ = directionX = directionW = 0;

	parent = NULL;

	linkType = 0x04;

	moving = false;

	undeployEvent = NULL;
	keepObject = false;
}

SceneObjectImplementation::~SceneObjectImplementation() {
	undeploy();
}

bool SceneObject::destroy() {
	bool destroying = ServerCore::getZoneServer()->destroyObject(this);

	if (destroying) {
		//info("destroying object");

		delete this;
	}

	return destroying;
}

bool SceneObjectImplementation::destroy() {
	return _this->destroy();
}

void SceneObjectImplementation::redeploy() {
	info("redeploying object");

	_this->revoke();

	removeUndeploymentEvent();
}

void SceneObjectImplementation::scheduleUndeploy() {
	if (undeployEvent == NULL && !keepObject && server != NULL) {
		info("scheduling uneploy");

		undeployEvent = new UndeploySceneObjectEvent(_this);
		server->addEvent(undeployEvent);
	}
}

void SceneObjectImplementation::undeploy() {
	if (isInQuadTree()) {
		error("Deleting scene object that is in QT");
		raise(SIGSEGV);
	}

	removeUndeploymentEvent();

	/*if (zone != NULL)
		//zone->deleteObject(_this);
		error("object is still in Zone");*/
}

void SceneObjectImplementation::removeUndeploymentEvent() {
	if (undeployEvent != NULL) {
		server->removeEvent(undeployEvent);

		delete undeployEvent;
		undeployEvent = NULL;
	}
}

void SceneObjectImplementation::create(ZoneClientSession* client) {
	BaseMessage* msg = new SceneObjectCreateMessage(_this);

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(ZoneClientSession* client, SceneObject* container) {
	if (client == NULL)
		return;

	parent = container;

	BaseMessage* msg = new UpdateContainmentMessage(container, _this, linkType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(uint64 container, uint32 type) {
	return new UpdateContainmentMessage(objectID, container, type);
}

BaseMessage* SceneObjectImplementation::link(SceneObject* container) {
	return new UpdateContainmentMessage(container, _this, linkType);
}

void SceneObjectImplementation::close(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectCloseMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::destroy(ZoneClientSession* client) {
	if (client == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);
	player->sendMessage(alm);
}

void SceneObjectImplementation::randomizePosition(float radius) {
	Coordinate::randomizePosition(radius);

	previousPositionZ = positionZ;

	if (zone != NULL)
		positionZ = zone->getHeight(positionX, positionY);
	else
		positionZ = 0;

}

void SceneObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}

void SceneObjectImplementation::lock(bool doLock) {
	ManagedObjectImplementation::wlock(doLock);
}

void SceneObjectImplementation::lock(ManagedObject* obj) {
	ManagedObjectImplementation::wlock(obj);
}

void SceneObjectImplementation::wlock(bool doLock) {
	ManagedObjectImplementation::wlock(doLock);
}

void SceneObjectImplementation::wlock(ManagedObject* obj) {
	ManagedObjectImplementation::wlock(obj);
}

void SceneObjectImplementation::unlock(bool doLock) {
	ManagedObjectImplementation::unlock(doLock);
}

void SceneObjectImplementation::setLockName(const string& name) {
	//ManagedObjectImplementation::setLockName(name);
}

void SceneObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::zone = zone;
	zoneID = zone->getZoneID();

	try {
		zone->lock();

		zone->registerObject(_this);

		if (parent != NULL) {
			BuildingObject* building = (BuildingObject*)parent->getParent();

			insertToBuilding(building);

			building->notifyInsertToZone(_this);
		} else {
			zone->insert(this);
			zone->inRange(this, 128);
		}

		zone->unlock();
	} catch (...) {
		cout << "exception SceneObjectImplementation::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	if (isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("inserting to building");

		((CellObject*)parent)->addChild(_this);

		building->insert(this);
		building->inRange(this, 128);

		//building->unlock(doLock);

		linkType = 0xFFFFFFFF;
		broadcastMessage(link(parent), 128, false);

	} catch (...) {
		error("exception SceneObjectImplementation::insertToBuilding(BuildingObject* building)");

		//building->unlock(doLock);
	}
}

void SceneObjectImplementation::broadcastMessage(BaseMessage* msg, int range, bool doLock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//cout << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					//cout << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage(msg->clone());
				}
			}
		}

		delete msg;

		zone->unlock(doLock);

	} catch (...) {
		error("exception SceneObject::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}

	//cout << "finished CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::broadcastMessage(StandaloneBaseMessage* msg, int range, bool doLock) {
	if (zone == NULL) {
		delete msg;
		return;
	}

	try {
		//cout << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);
			SceneObject* object = (SceneObject*) scno->_getStub();

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					//cout << "CreatureObject - sending message to player " << player->getFirstName() << "\n";
					player->sendMessage((StandaloneBaseMessage*)msg->clone());
				}
			}
		}

		delete msg;

		zone->unlock(doLock);

	} catch (...) {
		error("exception SceneObject::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}

	//cout << "finished SceneObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
}

void SceneObjectImplementation::removeFromZone(bool doLock) {
	try {
		if (zone == NULL || !isInQuadTree())
			return;

		//deagro();

		zone->lock(doLock);

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;
			BuildingObject* building = (BuildingObject*)parent->getParent();

			removeFromBuilding(building);
		} else
			zone->remove(this);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->deleteObject(objectID);

		zone->unlock(doLock);
	} catch (...) {
		cout << "exception CreatureImplementation::removeFromZone(bool doLock)\n";

		zone->unlock(doLock);
	}
}

void SceneObjectImplementation::removeFromBuilding(BuildingObject* building) {
	if (building == NULL || !isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("removing from building");

		broadcastMessage(link(0, 0xFFFFFFFF), 128, false);

		((CellObject*)parent)->removeChild(_this);

		building->remove(this);

		//building->unlock(doLock);
	} catch (...) {
		error("exception SceneObjectImplementation::removeFromBuilding(BuildingObject* building, bool doLock)");

		//building->unlock(doLock);
	}
}
