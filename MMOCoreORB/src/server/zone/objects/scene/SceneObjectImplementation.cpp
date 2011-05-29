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
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/object/ShowFlyText.h"

#include "server/zone/ZoneClientSession.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneReference.h"

#include "variables/StringId.h"
#include "events/ObjectUpdateToDatabaseTask.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/ChildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "PositionUpdateTask.h"

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	// FIXME: temp hack
	server = Core::lookupObject<ZoneProcessServer>("ZoneProcessServer");

	templateObject = TemplateManager::instance()->getTemplate(serverObjectCRC);

	if (templateObject != NULL) {
		String containerComp = templateObject->getContainerComponent();
		containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>(containerComp);

		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);

		String objectMenuComponentName = templateObject->getObjectMenuComponent();
		objectMenuComponent = ComponentManager::instance()->getComponent<ObjectMenuComponent*>(objectMenuComponentName);
	}

	movementCounter = 0;

	//activeAreas.removeAll();

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");
}

void SceneObjectImplementation::initializePrivateData() {
	pendingTasks.setNoDuplicateInsertPlan();
	pendingTasks.setNullValue(NULL);
	objectActiveSessions.setNullValue(NULL);
	objectActiveSessions.setNoDuplicateInsertPlan();

	server = NULL;

	templateObject = NULL;

	parent = NULL;

	movementCounter = 0;

	serverObjectCRC = 0;
	clientObjectCRC = 0;

	planetMapCategory = 0;
	planetMapSubCategory = 0;

	gameObjectType = 0;
	clientGameObjectType = 0;

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
	objectName.setStringId(templateData->getObjectName());
	//detailedDescription.setStringId(templateData->getDetailedDescription());

	gameObjectType = templateData->getGameObjectType();
	clientGameObjectType = templateData->getClientGameObjectType();
	clientObjectCRC = templateData->getClientObjectCRC();

	containerType = templateData->getContainerType();
	containerVolumeLimit = templateData->getContainerVolumeLimit();

	if (templateData->getCollisionActionBlockFlags() == 255) { //loading meshes for line of sight
		templateData->getPortalLayout();
		templateData->getAppearanceTemplate();
	}

	if (templateData->getPlanetMapCategory() != NULL)
		planetMapCategory = templateData->getPlanetMapCategory()->getCrc();

	if (templateData->getPlanetMapSubCategory() != NULL)
		planetMapSubCategory = templateData->getPlanetMapSubCategory()->getCrc();

	templateObject = templateData;
}

void SceneObjectImplementation::createContainerComponent() {
	String containerComp = templateObject->getContainerComponent();

	/*containerComponent = dynamic_cast<ContainerComponent*>(ObjectManager::instance()->createObject(containerComp, 1, "sceneobjectcomponents"));
	containerComponent->initialize(_this);
	containerComponent->setContainerVolumeLimit(containerVolumeLimit);
	containerComponent->setContainerType(containerType);*/

	//containerComponent = new ContainerComponent();
	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>(containerComp);
}

void SceneObjectImplementation::createComponents() {
	if (templateObject != NULL) {
		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);
		//zoneComponent->initialize(_this);

		String objectMenuComponentName = templateObject->getObjectMenuComponent();
		objectMenuComponent = ComponentManager::instance()->getComponent<ObjectMenuComponent*>(objectMenuComponentName);
		//objectMenuComponent->initialize(_this);

		createContainerComponent();
	} else
		error("NULL TEMPLATE OBJECT");

	/*if (zoneComponent == NULL) {
		zoneComponent = dynamic_cast<ZoneComponent*>(ObjectManager::instance()->createObject("ZoneComponent", 1, "sceneobjectcomponents"));
		zoneComponent->initialize(_this);
	}*/

	/*if (objectMenuComponent == NULL) {
		objectMenuComponent = dynamic_cast<ObjectMenuComponent*>(ObjectManager::instance()->createObject("ObjectMenuComponent", 1, "sceneobjectcomponents"));
		objectMenuComponent->initialize(_this);
	}*/

	/*if (containerComponent == NULL) {
		containerComponent = dynamic_cast<ContainerComponent*>(ObjectManager::instance()->createObject("ContainerComponent", 1, "sceneobjectcomponents"));
		containerComponent->initialize(_this);
		containerComponent->setContainerVolumeLimit(0);
		containerComponent->setContainerType(0);
	}*/
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

	for (int i = 0; i < getSlottedObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = getSlottedObject(i);

		if (destroyedObjects.put(object) != -1)
			object->destroyObjectFromDatabase(true);
	}

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		ManagedReference<SceneObject*> object = getContainerObject(j);

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

	if (containerComponent != NULL) {
		for (int i = 0; i < getSlottedObjectsSize(); ++i) {
			SceneObject* object = getSlottedObject(i);

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
						//containerComponent->dropSlottedObject(object->getArrangementDescriptor(j));
						slottedObjects.drop(object->getArrangementDescriptor(j));

					for (int j = 0; j < getSlottedObjectsSize(); ++j) {
						if (getSlottedObject(j) == object) {
							slottedObjects.remove(j);
							//containerComponent->removeSlottedObject(j);
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

		for (int i = 0; i < getContainerObjectsSize(); ++i) {
			SceneObject* object = getContainerObject(i);

			bool inSlotted = false, inContainer = false;

			if (object->getParent() == NULL) {
				object->setParent(_this);
				object->setContainmentType(-1);
			} else if (object->getParent() != _this) {
				if ((inSlotted = object->getParent()->hasObjectInSlottedContainer(object))
						|| (inContainer = object->getParent()->hasObjectInContainer(object->getObjectID()))) {
					containerObjects.removeElementAt(i);
					//containerComponent->removeFromContainerObjects(i);
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
	}

	if (parent == NULL && getZone() != NULL) {
		insertToZone(getZone());
	}
}

void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	SortedVector<SceneObject*> objects(getSlottedObjectsSize(), getSlottedObjectsSize());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < getSlottedObjectsSize(); ++i) {
		SceneObject* object = getSlottedObject(i);

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
	SortedVector<uint64> objects(getContainerObjectsSize(), getContainerObjectsSize());
	objects.setNoDuplicateInsertPlan();

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* containerObject = getContainerObject(j);

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
	if (getZone() == NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	Locker zoneLocker(getZone());

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
	if (getZone() == NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	Locker zoneLocker(getZone());

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
	if (getZone() == NULL) {
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

	getZone()->rlock(lockZone);

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
		getZone()->runlock(lockZone);

		delete message;

		throw;
	}

	getZone()->runlock(lockZone);

	delete message;
}

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	if (getZone() == NULL) {
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

	getZone()->rlock();

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

	getZone()->runlock();

	while (!messages->isEmpty()) {
		delete messages->remove(0);
	}
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	if (getZone() == NULL)
		return 0;

	int numberOfObjects = 0;

	Locker zoneLocker(getZone());

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
	zoneComponent->removeFromBuilding(_this, building);
}

void SceneObjectImplementation::updateVehiclePosition() {
	if (parent == NULL || !parent->isVehicleObject())
		return;

	Locker locker(parent);

	parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
	parent->setPosition(getPositionX(), getPositionZ(), getPositionY());

	parent->incrementMovementCounter();

	parent->updateZone(true);
}

void SceneObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZone(_this, lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifySelfPositionUpdate() {
	notifyObservers(ObserverEventType::POSITIONCHANGED);
}

void SceneObjectImplementation::notifyCloseContainer(PlayerCreature* player) {
	notifyObservers(ObserverEventType::CLOSECONTAINER, player);
}

void SceneObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	//notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
	if (_this == NULL || entry == NULL || _this == entry)
		return;

	Core::getTaskManager()->executeTask(new PositionUpdateTask(_this, entry));
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZoneWithParent(_this, newParent, lightUpdate, sendPackets);
}

void SceneObjectImplementation::insertToZone(Zone* newZone) {
	zoneComponent->insertToZone(_this, newZone);
}

void SceneObjectImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->teleport(_this, newPositionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::switchZone(const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->switchZone(_this, newTerrainName, newPostionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::insertToBuilding(BuildingObject* building) {
	zoneComponent->insertToBuilding(_this, building);
}

void SceneObjectImplementation::removeFromZone() {
	zoneComponent->removeFromZone(_this);
}

void SceneObjectImplementation::notifyAddedToCloseObjects() {
	//_this->acquire();
}

void SceneObjectImplementation::notifyRemovedFromCloseObjects() {
	//_this->release();
}

int SceneObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	return containerComponent->canAddObject(_this, object, containmentType, errorDescription);
}

bool SceneObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	return containerComponent->addObject(_this, object, containmentType, notifyClient);
}

bool SceneObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	return containerComponent->removeObject(_this, object, notifyClient);
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
	return objectMenuComponent->fillObjectMenuResponse(_this, menuResponse, player);
}

int SceneObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return objectMenuComponent->handleObjectMenuSelect(_this, player, selectedID);
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

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	float posX = root->getPositionX() + (sin(angle) * length);
	float posY = root->getPositionY() + (cos(angle) * length);
	float posZ = root->getPositionZ() + getPositionZ();

	Vector3 position(posX, posY, posZ);

	return position;
}

Vector3 SceneObjectImplementation::getCoordinate(float distance, float angleDegrees) {
	float angleRads = angleDegrees * (M_PI / 180.0f);
	float newAngle = angleRads + direction.getRadians();

	float newX = getPositionX() + (cos(newAngle) * distance); // client has x/y inverted
	float newY = getPositionY() + (sin(newAngle) * distance);
	float newZ = getZone()->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

float SceneObjectImplementation::getWorldPositionX() {
	if (parent == NULL)
		return getPositionX();

	SceneObject* root = getRootParent();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionX() + (sin(angle) * length);
}

float SceneObjectImplementation::getWorldPositionY() {
	if (parent == NULL)
		return getPositionY();

	SceneObject* root = getRootParent();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionY() + (cos(angle) * length);
}

float SceneObjectImplementation::getWorldPositionZ() {
	if (parent == NULL)
		return getPositionZ();

	SceneObject* root = getRootParent();

	return root->getPositionZ() + getPositionZ();
}

uint32 SceneObjectImplementation::getPlanetCRC() {
	if (getZone() == NULL)
		return 0;

	return getZone()->getZoneCRC();
}

void SceneObjectImplementation::createChildObjects() {
	if (getZone() == NULL)
		return;

	ZoneServer* zoneServer = getZone()->getZoneServer();

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

		obj->insertToZone(getZone());
		obj->updateToDatabase();
	}
}

void SceneObjectImplementation::faceObject(SceneObject* obj) {
	Vector3 thisWorldPos = getWorldPosition();
	Vector3 targetWorldPos = obj->getWorldPosition();

	float directionangle = atan2(targetWorldPos.getX() - thisWorldPos.getX(), targetWorldPos.getY() - thisWorldPos.getY());

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	float err = fabs(directionangle - direction.getRadians());

	if (err < 0.05) {
		//info("not updating " + String::valueOf(directionangle), true);
		return;
	}

	direction.setHeadingDirection(directionangle);
}

void SceneObjectImplementation::getSlottedObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	objects = slottedObjects;
}

void SceneObjectImplementation::setZone(Zone* zone) {
	this->zone = zone;
}

void SceneObjectImplementation::showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	ShowFlyText* fly = new ShowFlyText(_this, file, aux, red, green, blue);

	broadcastMessage(fly, true);
}

/*SortedVector<ManagedReference<SceneObject*> >* SceneObjectImplementation::getOutdoorChildObjects() {
	return &outdoorChildObjects;
}*/
