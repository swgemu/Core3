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
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/ChildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "PositionUpdateTask.h"

#include "server/zone/objects/tangible/sign/SignObject.h"

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

		if (zoneComponent == NULL) {
			zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
		}

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

	childObjects.setNoDuplicateInsertPlan();
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

	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>(containerComp);
}

void SceneObjectImplementation::createComponents() {
	if (templateObject != NULL) {
		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);
		//zoneComponent->initialize(_this);

		if (zoneComponent == NULL) {
			info("zone component null " + zoneComponentClassName + " in " + templateObject->getFullTemplateString());
		}

		String objectMenuComponentName = templateObject->getObjectMenuComponent();
		objectMenuComponent = ComponentManager::instance()->getComponent<ObjectMenuComponent*>(objectMenuComponentName);
		//objectMenuComponent->initialize(_this);

		createContainerComponent();
	} else
		error("NULL TEMPLATE OBJECT");

	if (zoneComponent == NULL) {
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
	}
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
	BaseMessage* msg = new UpdateContainmentMessage(_this, getParent(), containmentType);
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

	//Remove all child objects from database
	for (int i = 0; i < childObjects.size(); ++i) {
		ManagedReference<SceneObject*> child = childObjects.get(i);

		if (child == NULL)
			continue;

		child->destroyObjectFromDatabase(true);
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
		msg << "with parent " << getParent()->getLoggingName() << " ";
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
	if (zone != NULL) {
		//insertToZone(getZone());
		zone->transferObject(_this, -1, true);
	} else if (parent != NULL && getParent()->isCellObject()) {
		getRootParent()->notifyObjectInsertedToChild(_this, getParent(), NULL);
	}
}

void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	SortedVector<SceneObject*> objects(getSlottedObjectsSize(), getSlottedObjectsSize());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < getSlottedObjectsSize(); ++i) {
		SceneObject* object = getSlottedObject(i);

		if (objects.put(object) != -1) {
			if (object->isInQuadTree()) {
				notifyInsert(object);
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

		if (objects.put(containerObject->getObjectID()) != -1) {
			if (containerObject->isInQuadTree()) {
				notifyInsert(containerObject);
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

void SceneObjectImplementation::sendAttributeListTo(CreatureObject* object) {
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

	//info("sending destroy", true);

	BaseMessage* msg = new SceneObjectDestroyMessage(_this);
	client->sendMessage(msg);
}

void SceneObjectImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	ManagedReference<SceneObject*> par = getParent();

	broadcastDestroy(_this, sendSelfDestroy);

	ManagedReference<Zone*> rootZone = getZone();

	if (par != NULL) {
		par->removeObject(_this, false);

		if (par->isCellObject()) {
			BuildingObject* build = cast<BuildingObject*>(par->getParent());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(_this.get());

				if (creature != NULL)
					build->onExit(creature);
			}
		}
	} else if (zone != NULL) {
		zone->removeObject(_this, false);
	}

	if (rootZone != NULL) {
		Locker locker(rootZone);

		rootZone->remove(_this);

		if (closeobjects != NULL) {
			while (closeobjects->size() > 0) {
				ManagedReference<QuadTreeEntry*> obj = closeobjects->get(0);

				if (obj != _this && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(_this);

				removeInRangeObject((int) 0);
			}
		} else {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

			rootZone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				QuadTreeEntry* obj = closeSceneObjects.get(i);

				if (obj != _this && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(_this);
			}
		}

		while (activeAreas.size() > 0) {
			ManagedReference<ActiveArea*> area = activeAreas.get(0);
			area->enqueueExitEvent(_this);

			activeAreas.remove(0);
		}

		rootZone->dropSceneObject(_this);
	}
}

void SceneObjectImplementation::broadcastObject(SceneObject* object, bool sendSelf) {
	if (parent != NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastObject(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

	Locker zoneLocker(zone);

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else
		maxInRangeObjectCount = closeobjects->size();

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeobjects != NULL)
			scno = cast<SceneObject*>( closeobjects->get(i).get());
		else
			scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (!sendSelf && scno == _this)
			continue;

		if (scno->isPlayerCreature()) {
			object->sendTo(scno, true);
		}
	}

}

void SceneObjectImplementation::broadcastDestroy(SceneObject* object, bool sendSelf) {
	if (parent != NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastDestroy(object, sendSelf);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

	Locker zoneLocker(zone);

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else
		maxInRangeObjectCount = closeobjects->size();

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeobjects != NULL)
			scno = cast<SceneObject*>( closeobjects->get(i).get());
		else
			scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (!sendSelf && scno == _this)
			continue;

		if (scno->isPlayerCreature()) {
			object->sendDestroyTo(scno);
		}
	}


}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	if (parent != NULL) {
		SceneObject* grandParent = getRootParent();

		if (grandParent != NULL) {
			grandParent->broadcastMessage(message, sendSelf, lockZone);

			return;
		} else {
			delete message;

			return;
		}
	}

	if (zone == NULL) {
		delete message;

		return;
	}

	Locker zoneLocker(zone);

	//getZone()->rlock(lockZone);

	try {
		SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
		int maxInRangeObjectCount = 0;

		if (closeobjects == NULL) {
			zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else
			maxInRangeObjectCount = closeobjects->size();

		for (int i = 0; i < maxInRangeObjectCount; ++i) {
			SceneObject* scno;

			if (closeobjects != NULL)
				scno = cast<SceneObject*>( closeobjects->get(i).get());
			else
				scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

			if (!sendSelf && scno == _this)
				continue;

			scno->sendMessage(message->clone());
		}

	} catch (...) {
		delete message;

		throw;
	}

	delete message;
}

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	if (parent != NULL) {
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


	if (zone == NULL) {
		while (!messages->isEmpty()) {
			delete messages->remove(0);
		}

		return;
	}

	//getZone()->rlock();
	Locker zoneLocker(zone);

	try {
		SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
		int maxInRangeObjectCount = 0;

		if (closeobjects == NULL) {
			zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else
			maxInRangeObjectCount = closeobjects->size();

		for (int i = 0; i < maxInRangeObjectCount; ++i) {
			SceneObject* scno;

			if (closeobjects != NULL)
				scno = cast<SceneObject*>( closeobjects->get(i).get());
			else
				scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

			if (!sendSelf && scno == _this)
				continue;

			//if (scno->isPlayerCreature()) {
			for (int j = 0; j < messages->size(); ++j) {
				BasePacket* msg = messages->get(j);
				scno->sendMessage(msg->clone());
			}
		}

	} catch (Exception& e) {

	}

	//getZone()->runlock();
	zoneLocker.release();

	while (!messages->isEmpty()) {
		delete messages->remove(0);
	}
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	if (getZone() == NULL)
		return 0;

	int numberOfObjects = 0;

	Locker zoneLocker(getZone());

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else
		maxInRangeObjectCount = closeobjects->size();

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeobjects != NULL)
			scno = cast<SceneObject*>( closeobjects->get(i).get());
		else
			scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (scno->isInRange(_this, range) && scno->getGameObjectType() == gameObjectType)
			++numberOfObjects;
	}

	return numberOfObjects;
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
	for (int i = 0; i < containerObjects.size(); ++i) {
		containerObjects.get(i)->sendMessage(msg->clone());
	}

	SortedVector<SceneObject*> objects(slottedObjects.size(), slottedObjects.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slottedObjects.size(); ++i) {
		//slottedObjects.get(i)->sendMessage()
		SceneObject* object = slottedObjects.get(i);

		if (objects.put(object) != -1)
			object->sendMessage(msg->clone());
	}

	delete msg;
}

void SceneObjectImplementation::updateVehiclePosition() {
	SceneObject* parent = getParent();

	if (parent == NULL || !parent->isVehicleObject())
		return;

	Locker locker(parent);

	parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
	parent->setPosition(getPositionX(), getPositionZ(), getPositionY());

	parent->incrementMovementCounter();

	parent->updateZone(false);
}

void SceneObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZone(_this, lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifySelfPositionUpdate() {
	notifyObservers(ObserverEventType::POSITIONCHANGED);
}

void SceneObjectImplementation::notifyCloseContainer(CreatureObject* player) {
	notifyObservers(ObserverEventType::CLOSECONTAINER, player);
}

void SceneObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	if (_this == NULL || entry == NULL || _this == entry)
		return;

//#ifdef WITH_STM
	notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
//#else


	//Core::getTaskManager()->executeTask(new PositionUpdateTask(_this, entry));
//#endif
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZoneWithParent(_this, newParent, lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifyInsertToZone(Zone* newZone) {
	zoneComponent->notifyInsertToZone(_this, newZone);
}

void SceneObjectImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->teleport(_this, newPositionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::switchZone(const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->switchZone(_this, newTerrainName, newPostionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::updateDirection(float fw, float fx, float fy, float fz) {
	setDirection(fw, fx, fy, fz);

	++movementCounter;

	if (parent != NULL) {
		DataTransformWithParent* pack = new DataTransformWithParent(_this);
		broadcastMessage(pack, true, true);
	} else {
		DataTransform* pack = new DataTransform(_this);
		broadcastMessage(pack, true, true);
	}
}

void SceneObjectImplementation::notifyRemoveFromZone() {
	zoneComponent->notifyRemoveFromZone(_this);
}

int SceneObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	return containerComponent->canAddObject(_this, object, containmentType, errorDescription);
}

bool SceneObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient) {
	return containerComponent->transferObject(_this, object, containmentType, notifyClient);
}

bool SceneObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	return containerComponent->removeObject(_this, object, notifyClient);
}

void SceneObjectImplementation::openContainerTo(CreatureObject* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this);
	player->sendMessage(cont);

	sendContainerObjectsTo(player);
}

void SceneObjectImplementation::closeContainerTo(CreatureObject* player, bool notify) {

	if(notify) {
		ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this, true);
		player->sendMessage(cont);
	}
}

SceneObject* SceneObjectImplementation::getRootParent() {
	if (parent == NULL)
		return NULL;

	SceneObject* grandParent = getParent();

	while (grandParent->getParent() != NULL)
		grandParent = grandParent->getParent();

	return grandParent;
}

SceneObject* SceneObjectImplementation::getParentRecursively(uint32 gameObjectType) {
	if (parent == NULL)
		return NULL;

	SceneObject* temp = getParent();

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

	SceneObject* grandParent = getParent();

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

void SceneObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	return objectMenuComponent->fillObjectMenuResponse(_this, menuResponse, player);
}

int SceneObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
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
			BuildingObject* buildingObject = cast<BuildingObject*>( (_this.get()));

			int totalCells = buildingObject->getTotalCellNumber();

			try {
				if (totalCells >= child->getCellId()) {
					ManagedReference<CellObject*> cellObject = buildingObject->getCell(child->getCellId());

					if (cellObject != NULL) {
						cellObject->transferObject(obj, child->getContainmentType(), true);
						//cellObject->broadcastObject(obj, false);
					} else
						error("NULL CELL OBJECT");
				}
			} catch (Exception& e) {
				error("unreported exception caught in void SceneObjectImplementation::createChildObjects()!");
				e.printStackTrace();
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

			getZone()->transferObject(obj, -1, false);
		}

		childObjects.put(obj);

		obj->initializeChildObject(_this);
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

void SceneObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
}

SceneObject* SceneObjectImplementation::getParent() {
	return dynamic_cast<SceneObject*>(parent.get());
}

SortedVector<ManagedReference<Observer* > >* SceneObjectImplementation::getObservers(unsigned int eventType) {
	return observerEventMap.getObservers(eventType);
}
