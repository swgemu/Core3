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
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/object/ShowFlyText.h"

#include "server/zone/ZoneClientSession.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneReference.h"

#include "variables/StringId.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/ChildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/scene/components/AiDummyComponent.h"
#include "PositionUpdateTask.h"

#include "server/zone/objects/tangible/sign/SignObject.h"

#include "variables/ContainerPermissions.h"

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	// FIXME: temp hack
	server = Core::lookupObject<ZoneProcessServer>("ZoneProcessServer");

	templateObject = TemplateManager::instance()->getTemplate(serverObjectCRC);

	if (templateObject != NULL) {
		containerComponent = cast<ContainerComponent*>(templateObject->getContainerComponent());

		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);

		if (zoneComponent == NULL) {
			zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
		}

		objectMenuComponent = cast<ObjectMenuComponent*>(templateObject->getObjectMenuComponent());
	}

	if(dataObjectComponent != NULL) {
		dataObjectComponent->setParent(_this.get());
		dataObjectComponent->initializeTransientMembers();
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

	sendToClient = true;

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

	dataObjectComponent = ComponentManager::instance()->getDataObjectComponent(templateData->getDataObjectComponent());
}

void SceneObjectImplementation::createContainerComponent() {
	containerComponent = cast<ContainerComponent*>(templateObject->getContainerComponent());
}

void SceneObjectImplementation::createComponents() {
	if (templateObject != NULL) {
		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);
		//zoneComponent->initialize(_this.get());

		if (zoneComponent == NULL) {
			info("zone component null " + zoneComponentClassName + " in " + templateObject->getFullTemplateString());
		}

		objectMenuComponent = cast<ObjectMenuComponent*>(templateObject->getObjectMenuComponent());

		String attributeListComponentName = templateObject->getAttributeListComponent();
		attributeListComponent = ComponentManager::instance()->getComponent<AttributeListComponent*>(attributeListComponentName);

		if (attributeListComponent == NULL) {
			info("attributeList component null for " + templateObject->getFullTemplateString());
		}

		createContainerComponent();

	} else
		error("NULL TEMPLATE OBJECT");

	if (zoneComponent == NULL) {
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
	}
}

void SceneObjectImplementation::close(SceneObject* client) {
	BaseMessage* msg = new SceneObjectCloseMessage(_this.get());

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(SceneObject* client, uint32 containmentType) {
	BaseMessage* msg = new UpdateContainmentMessage(_this.get(), getParent().get(), containmentType);
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
	server->updateObjectToDatabase(_this.get());*/
}

void SceneObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	/*if (!isPersistent())
		return;

	Time start;

	ZoneServer* server = getZoneServer();
	server->updateObjectToDatabase(_this.get());

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

void SceneObjectImplementation::destroyPlayerCreatureFromDatabase(bool destroyContainedObjects) {
	if (!isPlayerCreature())
		return;

	if(dataObjectComponent != NULL) {
		dataObjectComponent->notifyObjectDestroyingFromDatabase();
	}

	ZoneServer* server = getZoneServer();

	server->destroyObjectFromDatabase(getObjectID());

	_this.get()->setPersistent(0);

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

void SceneObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	//info("deleting from database", true);

	if (isPlayerCreature()) {
		assert(0 && "attempting to delete a player creature from database");
	}

	if(dataObjectComponent != NULL) {
		dataObjectComponent->notifyObjectDestroyingFromDatabase();
	}

	ZoneServer* server = getZoneServer();

	server->destroyObjectFromDatabase(getObjectID());

	_this.get()->setPersistent(0);

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
	return _this.get()->_getObjectID();
}

void SceneObjectImplementation::sendWithoutParentTo(SceneObject* player) {
	BaseMessage* msg = new SceneObjectCreateMessage(_this.get());
	player->sendMessage(msg);

	/*if (parent != NULL)
		link(client.get(), containmentType);*/

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (isStaticObject() || !sendToClient)
		return;

	/*StringBuffer msgInfo;
	if (parent != NULL)
		msgInfo << "with parent " << getParent()->getLoggingName() << " ";
	msgInfo << "sending 0x" << hex << getClientObjectCRC() << " to " << player->getLoggingName();
	info(msgInfo.toString(), true);*/

	BaseMessage* msg = new SceneObjectCreateMessage(_this.get());
	player->sendMessage(msg);

	if (parent != NULL)
		link(player, containmentType);

	try {
		sendBaselinesTo(player);

		sendContainerObjectsTo(player);

		sendSlottedObjectsTo(player);
	} catch (Exception& e) {

	}

	if (doClose) {
		SceneObjectImplementation::close(player);
		//info("sending close", true);
	}
}

void SceneObjectImplementation::sendWithoutContainerObjectsTo(SceneObject* player) {
	if (isStaticObject() || !sendToClient)
		return;

	BaseMessage* msg = new SceneObjectCreateMessage(_this.get());
	player->sendMessage(msg);

	if (parent != NULL)
		link(player, containmentType);

	sendBaselinesTo(player);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::notifyLoadFromDatabase() {
	for (int i = 0; i < slottedObjects.size(); ++i) {
		ManagedReference<SceneObject* > obj = slottedObjects.get(i);

		if (obj->getParent().get() != _this.get()) {
			obj->setParent(_this.get());
			//			obj->setContainmentType(4);

			if (obj->isPlayerCreature())
				obj->setContainmentType(5);
			else
				obj->setContainmentType(4);
		}
	}

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject* > obj = containerObjects.get(i);

		if (obj->getParent() != _this.get()) {
			obj->setParent(_this.get());
			obj->setContainmentType(-1);
			//			obj->setContainmentType(4);
		}
	}

	for (int i = 0; i < activeAreas.size(); ++i) {
		activeAreas.get(i)->notifyExit(_this.get());
	}

	activeAreas.removeAll();

	if (zone != NULL) {
		zone->transferObject(_this.get(), -1, true);
	} /*else if (parent != NULL && getParent()->isCellObject()) {
		getRootParent()->notifyObjectInsertedToChild(_this.get(), getParent(), NULL);

	}*/



	//for (int i = 0; i < )
}

void SceneObjectImplementation::setObjectMenuComponent(const String& name) {
	objectMenuComponent = ComponentManager::instance()->getComponent<ObjectMenuComponent*>(name);

	if (objectMenuComponent == NULL) {
		Lua* lua = DirectorManager::instance()->getLuaInstance();
		LuaObject test = lua->getGlobalObject(name);

		if (test.isValidTable()) {
			objectMenuComponent = new LuaObjectMenuComponent(name);
			info("New Lua ObjectMenuComponent created: '" + name + "' for " + templateObject->getFullTemplateString());
			ComponentManager::instance()->putComponent(name, objectMenuComponent);
		} else {
			error("ObjectMenuComponent not found: '" + name + "' for " + templateObject->getFullTemplateString());
		}

		test.pop();
	}
}

void SceneObjectImplementation::setContainerComponent(const String& name) {
	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>(name);

	if (containerComponent == NULL) {
		Lua* lua = DirectorManager::instance()->getLuaInstance();
		LuaObject test = lua->getGlobalObject(name);

		if (test.isValidTable()) {
			containerComponent = new LuaContainerComponent(name);
			info("New Lua ContainerComponent created: '" + name + "' for " + templateObject->getFullTemplateString());
			ComponentManager::instance()->putComponent(name, containerComponent);
		} else {
			error("ContainerComponent not found: '" + name + "' for " + templateObject->getFullTemplateString());
		}

		test.pop();
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
	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* containerObject = getContainerObject(j);

		if (containerObject->isInQuadTree()) {
			notifyInsert(containerObject);
		} else {
			containerObject->sendTo(player, true);
		}
	}
}

void SceneObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (staticObject)
		return;

	/*StringBuffer msg;
	msg << "sending destroy to " << player->getLoggingName();
	info(msg.toString(), true);*/

	BaseMessage* msg = new SceneObjectDestroyMessage(_this.get());
	player->sendMessage(msg);
}

void SceneObjectImplementation::sendAttributeListTo(CreatureObject* object) {

	AttributeListMessage* alm = new AttributeListMessage(_this.get());

	try {

		attributeListComponent->fillAttributeList(alm, object, _this.get());

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

void SceneObjectImplementation::broadcastObjectPrivate(SceneObject* object, SceneObject* selfObject) {
	if (parent != NULL) {
		ManagedReference<SceneObject*> grandParent = cast<SceneObject*>(getRootParentUnsafe());

		if (grandParent != NULL) {
			grandParent->broadcastObjectPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

//	bool readlock = !zone->isLockedByCurrentThread();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

	int maxInRangeObjectCount = 0;

//	zone->rlock(readlock);

	//Locker zoneLocker(zone);

	try {

		if (closeobjects == NULL) {
			zone->getInRangeObjects(getPositionX(), getPositionY(), 192, &closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else {
			CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
			closeSceneObjects.removeAll(vec->size(), 10);
			
			//closeSceneObjects.addAll(*closeobjects);
			vec->safeCopyTo(closeSceneObjects);
			
			maxInRangeObjectCount = closeSceneObjects.size(); //closeobjects->size();

		}

	} catch (...) {
//		zone->runlock(readlock);

		throw;
	}

	//zone->runlock(readlock);

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (selfObject == scno)
			continue;

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL) {
			object->sendTo(scno, true);
		}
	}
}

void SceneObjectImplementation::broadcastObject(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? NULL : _this.get();
	broadcastObjectPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastDestroyPrivate(SceneObject* object, SceneObject* selfObject) {
	if (parent != NULL) {
		ManagedReference<SceneObject*> grandParent = cast<SceneObject*>(getRootParentUnsafe());

		if (grandParent != NULL) {
			grandParent->broadcastDestroyPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

	//Locker zoneLocker(zone);

//	bool readlock = !zone->isLockedByCurrentThread();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

//	zone->rlock(readlock);

	try {
		if (closeobjects == NULL) {
			zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else {
			
			CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
			closeSceneObjects.removeAll(vec->size(), 10);
//			closeSceneObjects.addAll(*closeobjects);
			vec->safeCopyTo(closeSceneObjects);
			
			maxInRangeObjectCount = closeSceneObjects.size();//closeobjects->size();

		}


	} catch (...) {
		//zone->runlock(readlock);

		throw;
	}

//	zone->runlock(readlock);

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (selfObject == scno)
			continue;

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL) {
			object->sendDestroyTo(scno);
		}
	}
}

void SceneObjectImplementation::broadcastDestroy(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? NULL : _this.get();
	broadcastDestroyPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastMessagePrivate(BasePacket* message, SceneObject* selfObject, bool lockZone) {
	if (parent != NULL) {
		ManagedReference<SceneObject*> grandParent = cast<SceneObject*>(getRootParentUnsafe());

		if (grandParent != NULL) {
			grandParent->broadcastMessagePrivate(message, selfObject, lockZone);

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

	//Locker zoneLocker(zone);

	//getZone()->rlock(lockZone);

//	bool readlock = lockZone && !zone->isLockedByCurrentThread();

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeSceneObjects = NULL;
	SortedVector<QuadTreeEntry*>* closeNoneReference = NULL;
	int maxInRangeObjectCount = 0;
	bool deleteVector = true;

	try {
//		zone->rlock(readlock);

		if (closeobjects == NULL) {
			closeSceneObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
			zone->getInRangeObjects(getPositionX(), getPositionY(), 192, closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects->size();
			deleteVector = true;
		} else {
//			maxInRangeObjectCount = closeobjects->size();
			//closeSceneObjects = closeobjects;
			
			closeNoneReference = new SortedVector<QuadTreeEntry*>(maxInRangeObjectCount, 50);
			

/*			for (int i = 0; i < closeobjects->size(); ++i) {
				closeNoneReference->add(closeobjects->get(i).get());
			}
			*/
			
			closeobjects->safeCopyTo(*closeNoneReference);
			maxInRangeObjectCount = closeNoneReference->size();

			//closeSceneObjects.removeAll(maxInRangeObjectCount, 10);
			//closeSceneObjects.addAll(*closeobjects);
		}
/*		
		for (int i = 0; i < maxInRangeObjectCount; ++i) {
			SceneObject* scno = cast<SceneObject*>(closeSceneObjects->get(i).get());
			
			if (selfObject == scno)
				continue;
				
			ManagedReference<ZoneClientSession*> client = scno->getClient();
			
			if (client != NULL || scno->isVehicleObject()) {
				scno->sendMessage(message->clone());
			}
				
		}
			*/

		//zone->runlock(readlock);

	} catch (...) {
//		zone->runlock(readlock);

		delete message;

		throw;
		
	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;
		
		if (closeSceneObjects != NULL)
			scno  = cast<SceneObject*>(closeSceneObjects->get(i).get());
		else
			scno = cast<SceneObject*>(closeNoneReference->get(i));

		if (selfObject == scno)
			continue;

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if ((dynamic_cast<VehicleObject*>(scno) != NULL) || client != NULL)
			scno->sendMessage(message->clone());
	}

	delete message;
	
	if (closeSceneObjects != NULL)
		delete closeSceneObjects;	
	else
		delete closeNoneReference;
}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	SceneObject* selfObject = sendSelf ? NULL : _this.get();

	broadcastMessagePrivate(message, selfObject, lockZone);
}

void SceneObjectImplementation::broadcastMessagesPrivate(Vector<BasePacket*>* messages, SceneObject* selfObject) {
	if (parent != NULL) {
		ManagedReference<SceneObject*> grandParent = cast<SceneObject*>(getRootParentUnsafe());

		if (grandParent != NULL) {
			grandParent->broadcastMessagesPrivate(messages, selfObject);

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
	//Locker zoneLocker(zone);

	bool readlock = !zone->isLockedByCurrentThread();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

//	zone->rlock(readlock);

	try {

		if (closeobjects == NULL) {
			zone->getInRangeObjects(getPositionX(), getPositionY(), 192, &closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else {
			maxInRangeObjectCount = closeobjects->size();

			closeSceneObjects.removeAll(maxInRangeObjectCount, 10);
			//closeSceneObjects.addAll(*closeobjects);
			closeobjects->safeCopyTo(closeSceneObjects);
			
			maxInRangeObjectCount = closeSceneObjects.size();
			
		}

	} catch (Exception& e) {

	}

	//getZone()->runlock();
	//zoneLocker.release();
//	zone->runlock(readlock);

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (selfObject == scno)
			continue;

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL) {
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

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? NULL : _this.get();

	broadcastMessagesPrivate(messages, selfObject);
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	if (getZone() == NULL)
		return 0;

	int numberOfObjects = 0;

	Locker zoneLocker(getZone());

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		zone->getInRangeObjects(getPositionX(), getPositionY(), range, &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else
		maxInRangeObjectCount = closeobjects->size();

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeobjects != NULL)
			scno = cast<SceneObject*>( closeobjects->get(i).get());
		else
			scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (scno->isInRange(_this.get(), range) && scno->getGameObjectType() == gameObjectType)
			++numberOfObjects;
	}

	return numberOfObjects;
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
	/*for (int i = 0; i < containerObjects.size(); ++i) {
		containerObjects.get(i)->sendMessage(msg->clone());
	}

	SortedVector<SceneObject*> objects(slottedObjects.size(), slottedObjects.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slottedObjects.size(); ++i) {
		//slottedObjects.get(i)->sendMessage()
		SceneObject* object = slottedObjects.get(i);

		if (objects.put(object) != -1)
			object->sendMessage(msg->clone());
	}*/

	delete msg;
}

void SceneObjectImplementation::updateVehiclePosition(bool sendPackets) {
	ManagedReference<SceneObject*> parent = getParent();

	if (parent == NULL || !parent->isVehicleObject())
		return;

	Locker locker(parent);

	parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
	parent->setPosition(getPositionX(), getPositionZ(), getPositionY());

	parent->incrementMovementCounter();

	parent->updateZone(false, sendPackets);
}

void SceneObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZone(_this.get(), lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifySelfPositionUpdate() {
	notifyObservers(ObserverEventType::POSITIONCHANGED);
}

void SceneObjectImplementation::notifyCloseContainer(CreatureObject* player) {
	notifyObservers(ObserverEventType::CLOSECONTAINER, player);
}

void SceneObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	if (entry == NULL || _this.getReferenceUnsafe() == entry)
		return;

	//#ifdef WITH_STM
	notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
	//#else

	//Core::getTaskManager()->executeTask(new PositionUpdateTask(_this.get(), entry));
	//#endif
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZoneWithParent(_this.get(), newParent, lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifyInsertToZone(Zone* newZone) {
	zoneComponent->notifyInsertToZone(_this.get(), newZone);
}

void SceneObjectImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->teleport(_this.get(), newPositionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::switchZone(const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->switchZone(_this.get(), newTerrainName, newPostionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::updateDirection(float fw, float fx, float fy, float fz) {
	setDirection(fw, fx, fy, fz);

	++movementCounter;

	if (parent != NULL) {
		DataTransformWithParent* pack = new DataTransformWithParent(_this.get());
		broadcastMessage(pack, true, true);
	} else {
		DataTransform* pack = new DataTransform(_this.get());
		broadcastMessage(pack, true, true);
	}
}

void SceneObjectImplementation::updateDirection(float angleHeadingRadians) {
	setDirection(angleHeadingRadians);

	++movementCounter;

	if (parent != NULL) {
		DataTransformWithParent* pack = new DataTransformWithParent(_this.get());
		broadcastMessage(pack, true, true);
	} else {
		DataTransform* pack = new DataTransform(_this.get());
		broadcastMessage(pack, true, true);
	}
}

void SceneObjectImplementation::notifyRemoveFromZone() {
	zoneComponent->notifyRemoveFromZone(_this.get());
}

int SceneObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	return containerComponent->canAddObject(_this.get(), object, containmentType, errorDescription);
}

bool SceneObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient) {
	return containerComponent->transferObject(_this.get(), object, containmentType, notifyClient);
}

bool SceneObjectImplementation::removeObject(SceneObject* object, SceneObject* destination, bool notifyClient) {
	return containerComponent->removeObject(_this.get(), object, destination, notifyClient);
}

void SceneObjectImplementation::openContainerTo(CreatureObject* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this.get());
	player->sendMessage(cont);

	sendContainerObjectsTo(player);
}

void SceneObjectImplementation::closeContainerTo(CreatureObject* player, bool notify) {

	if(notify) {
		ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(_this.get(), true);
		player->sendMessage(cont);
	}
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getRootParent() {
	ManagedReference<SceneObject*> grandParent = getParent();
	ManagedReference<SceneObject*> tempParent = NULL;

	if (grandParent == NULL)
		return NULL;

	while ((tempParent = grandParent->getParent()) != NULL)
		grandParent = tempParent;

	ManagedWeakReference<SceneObject*> weak = grandParent.get();

	return weak;
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParentRecursively(uint32 gameObjectType) {
	ManagedReference<SceneObject*> temp = getParent();

	if (temp == NULL)
		return NULL;

	if (temp->getGameObjectType() == gameObjectType)
		return temp.get();

	while ((temp = temp->getParent()) != NULL) {
		if (temp->getGameObjectType() == gameObjectType) {
			ManagedWeakReference<SceneObject*> weak = temp.get();

			return weak;
		}
	}

	return NULL;
}

bool SceneObjectImplementation::isASubChildOf(SceneObject* object) {
	ManagedReference<SceneObject*> temp = getParent();

	if (temp == NULL)
		return false;

	if (temp == object)
		return true;

	ManagedReference<SceneObject*> grandParent = temp;

	while ((temp = grandParent->getParent()) != NULL) {
		grandParent = temp;

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
	return objectMenuComponent->fillObjectMenuResponse(_this.get(), menuResponse, player);
}

int SceneObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	return objectMenuComponent->handleObjectMenuSelect(_this.get(), player, selectedID);
}

void SceneObjectImplementation::setObjectName(StringId& stringID) {
	objectName = stringID;
}

Vector3 SceneObjectImplementation::getWorldPosition() {
	if (parent == NULL)
		return getPosition();

	ManagedReference<SceneObject*> root = getRootParent().castTo<SceneObject*>();

	if (root == NULL || !root->isBuildingObject())
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
	float newAngle = angleRads + (M_PI / 2) - direction.getRadians();

	float newX = getPositionX() + (cos(newAngle) * distance); // client has x/y inverted
	float newY = getPositionY() + (sin(newAngle) * distance);
	float newZ = getZone()->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

Vector3 SceneObjectImplementation::getWorldCoordinate(float distance, float angleDegrees) {
	float angleRads = angleDegrees * (M_PI / 180.0f);
	float newAngle = angleRads + (M_PI / 2) - direction.getRadians();

	float newX = getWorldPositionX() + (cos(newAngle) * distance); // client has x/y inverted
	float newY = getWorldPositionY() + (sin(newAngle) * distance);
	float newZ = getZone()->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

float SceneObjectImplementation::getWorldPositionX() {
	if (parent == NULL)
		return getPositionX();

	ManagedReference<SceneObject*> root = cast<SceneObject*>(getRootParentUnsafe());

	if (root == NULL || !root->isBuildingObject())
		return getPositionX();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionX() + (sin(angle) * length);
}

float SceneObjectImplementation::getWorldPositionY() {
	if (parent == NULL)
		return getPositionY();

	ManagedReference<SceneObject*> root = cast<SceneObject*>(getRootParentUnsafe());

	if (root == NULL || !root->isBuildingObject())
		return getPositionY();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionY() + (cos(angle) * length);
}

float SceneObjectImplementation::getWorldPositionZ() {
	if (parent == NULL)
		return getPositionZ();

	ManagedReference<SceneObject*> root = cast<SceneObject*>(getRootParentUnsafe());

	if (root == NULL || !root->isBuildingObject())
		return getPositionZ();

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
		childObjects.put(obj);
		obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
		obj->setDirection(child->getDirection());

		if (isBuildingObject() && child->getCellId() >= 0) {
			BuildingObject* buildingObject = cast<BuildingObject*>( (_this.get().get()));

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

		//childObjects.put(obj);
		ContainerPermissions* permissions = obj->getContainerPermissions();
		permissions->setOwner(getObjectID());
		permissions->setInheritPermissionsFromParent(false);
		permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

		obj->initializeChildObject(_this.get());
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
	bool lock = !containerLock.isLockedByCurrentThread();

	containerLock.rlock(lock);

	objects = slottedObjects;

	containerLock.runlock(lock);
}

SceneObject* SceneObjectImplementation::getSlottedObject(const String& slot) {
	SceneObject* obj = NULL;

	bool lock = !containerLock.isLockedByCurrentThread();

	containerLock.rlock(lock);

	try {
		obj = slottedObjects.get(slot);
	} catch (...) {
		containerLock.runlock(lock);

		throw;
	}

	containerLock.runlock(lock);

	return obj;
}


SceneObject* SceneObjectImplementation::getSlottedObject(int idx) {
	SceneObject* obj = NULL;

	bool lock = !containerLock.isLockedByCurrentThread();

	containerLock.rlock(lock);

	try {
		obj = slottedObjects.get(idx);
	} catch (...) {
		containerLock.runlock(lock);

		throw;
	}

	containerLock.runlock(lock);

	return obj;
}

void SceneObjectImplementation::dropSlottedObject(const String& arrengementDescriptor) {
	Locker locker(&containerLock);

	slottedObjects.drop(arrengementDescriptor);
}

void SceneObjectImplementation::removeSlottedObject(int index) {
	Locker locker(&containerLock);

	slottedObjects.remove(index);
}

void SceneObjectImplementation::setZone(Zone* zone) {
	this->zone = zone;
}

void SceneObjectImplementation::showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	ShowFlyText* fly = new ShowFlyText(_this.get(), file, aux, red, green, blue);

	broadcastMessage(fly, true);
}

/*SortedVector<ManagedReference<SceneObject*> >* SceneObjectImplementation::getOutdoorChildObjects() {
	return &outdoorChildObjects;
}*/

void SceneObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParent() {
	ManagedReference<QuadTreeEntry*> parent = this->parent;

	if (parent == NULL)
		return NULL;

	return ManagedWeakReference<SceneObject*>(dynamic_cast<SceneObject*>(parent.get()));
}

SortedVector<ManagedReference<Observer* > >* SceneObjectImplementation::getObservers(unsigned int eventType) {
	return observerEventMap.getObservers(eventType);
}

bool SceneObjectImplementation::isInWater() {
	if (getZone() == NULL) {
		error("Zone is NULL SceneObjectImplementation::isInWater");
		return false;
	}

	ManagedReference<PlanetManager*> planetManager = getZone()->getPlanetManager();

	if (planetManager == NULL) {
		error("Unable to get PlanetManager SceneObjectImplementation::isInWater");
		return false;
	}

	return planetManager->isInWater(getPositionX(), getPositionY());
}

String SceneObjectImplementation::getDisplayedName() {
	if(!customName.isEmpty())
		return customName.toString();

	return objectName.getFullPath();
}

bool SceneObjectImplementation::setTransformForCollisionMatrixIfNull(Matrix4* mat) {
	return transformForCollisionMatrix.compareAndSet(NULL, mat);
}

void SceneObjectImplementation::addActiveArea(ActiveArea* area) {
	if (!area->isDeplyoed())
		area->deploy();

	activeAreas.put(area);
}
