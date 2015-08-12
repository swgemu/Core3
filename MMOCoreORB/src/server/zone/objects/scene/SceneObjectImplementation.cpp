/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/scene/SceneObject.h"

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
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
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
#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "PositionUpdateTask.h"

#include "server/zone/objects/tangible/sign/SignObject.h"

#include "variables/ContainerPermissions.h"

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	// FIXME: temp hack
	server = Core::lookupObject<ZoneProcessServer>("ZoneProcessServer").get();

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
		dataObjectComponent->setParent(asSceneObject());
		dataObjectComponent->initializeTransientMembers();
	}

	movementCounter = 0;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");
}

void SceneObjectImplementation::initializePrivateData() {
	pendingTasks = NULL;

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

	containmentType = 4;

	initializePosition(0.f, 0.f, 0.f);

	movementCounter = 0;

	staticObject = false;

	zone = NULL;

	containerType = 0;
	containerVolumeLimit = 0;
	containmentType = 0;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");

	childObjects.setNoDuplicateInsertPlan();
}

void SceneObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	objectName.setStringId(templateData->getObjectName());
	customName = templateData->getCustomName();
	//detailedDescription.setStringId(templateData->getDetailedDescription());

	gameObjectType = templateData->getGameObjectType();
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

void SceneObjectImplementation::setZoneComponent(const String& name) {
	zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(name);
}

void SceneObjectImplementation::createComponents() {
	if (templateObject != NULL) {
		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);
		//zoneComponent->initialize(_this.getReferenceUnsafe());

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
	BaseMessage* msg = new SceneObjectCloseMessage(asSceneObject());

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(SceneObject* client, uint32 containmentType) {
	BaseMessage* msg = new UpdateContainmentMessage(asSceneObject(), getParent().get(), containmentType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(uint64 objectID, uint32 containmentType) {
	return new UpdateContainmentMessage(getObjectID(), objectID, containmentType);
}

//deprecated methods, updates are automatic now
void SceneObjectImplementation::updateToDatabase() {
}

void SceneObjectImplementation::updateToDatabaseWithoutChildren() {
}

void SceneObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
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

	asSceneObject()->setPersistent(0);

	if (!destroyContainedObjects)
		return;

	SortedVector<ManagedReference<SceneObject*> > destroyedObjects;
	destroyedObjects.setNoDuplicateInsertPlan();

	for (int i = 0; i < getSlottedObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = getSlottedObject(i);

		if (destroyedObjects.put(object) != -1) {
			Locker locker(object);
			object->destroyObjectFromDatabase(true);
		}
	}

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		ManagedReference<SceneObject*> object = getContainerObject(j);

		if (destroyedObjects.put(object) != -1) {
			Locker locker(object);
			object->destroyObjectFromDatabase(true);
		}
	}

	//Remove all child objects from database
	for (int i = 0; i < childObjects.size(); ++i) {
		ManagedReference<SceneObject*> child = childObjects.get(i);

		if (child == NULL)
			continue;

		Locker locker(child);

		child->destroyObjectFromDatabase(true);
	}
}

uint64 SceneObjectImplementation::getObjectID() {
	return asSceneObject()->_getObjectID();
}

void SceneObjectImplementation::sendWithoutParentTo(SceneObject* player) {
	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (isStaticObject() || !sendToClient || player->getClient() == NULL)
		return;

	/*StringBuffer msgInfo;
	if (parent != NULL)
		msgInfo << "with parent " << getParent()->getLoggingName() << " ";
	msgInfo << "sending 0x" << hex << getClientObjectCRC() << " to " << player->getLoggingName();
	info(msgInfo.toString(), true);*/

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	if (parent.get() != NULL)
		link(player, containmentType);

	try {
		sendBaselinesTo(player);

		sendContainerObjectsTo(player);

		sendSlottedObjectsTo(player);
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (doClose) {
		SceneObjectImplementation::close(player);
	}
}

void SceneObjectImplementation::sendWithoutContainerObjectsTo(SceneObject* player) {
	if (isStaticObject() || !sendToClient)
		return;

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	if (parent.get() != NULL)
		link(player, containmentType);

	sendBaselinesTo(player);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::notifyLoadFromDatabase() {
	if (!containerObjects.hasDelayedLoadOperationMode()) {
		for (int i = 0; i < slottedObjects.size(); ++i) {
			ManagedReference<SceneObject* > obj = slottedObjects.get(i);

			if (obj->getParent().get() != asSceneObject()) {
				obj->setParent(asSceneObject());

				if (obj->isPlayerCreature())
					obj->setContainmentType(5);
				else
					obj->setContainmentType(4);
			}
		}

		for (int i = 0; i < containerObjects.size(); ++i) {
			ManagedReference<SceneObject* > obj = containerObjects.get(i);

			if (obj->getParent() != asSceneObject()) {
				obj->setParent(asSceneObject());
				obj->setContainmentType(-1);
			}
		}

	}

	if (zone != NULL) {
		zone->transferObject(asSceneObject(), -1, true);
	}
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
	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<SceneObject*> objects(slotted.size(), slotted.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slotted.size(); ++i) {
		SceneObject* object = slotted.get(i);

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
	VectorMap<uint64, ManagedReference<SceneObject* > > objects;
	getContainerObjects(objects);

	for (int j = 0; j < objects.size(); ++j) {
		SceneObject* containerObject = objects.get(j);

		if (containerObject == NULL)
			continue;

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

	BaseMessage* msg = new SceneObjectDestroyMessage(asSceneObject());
	player->sendMessage(msg);
}

void SceneObjectImplementation::sendAttributeListTo(CreatureObject* object) {

	AttributeListMessage* alm = new AttributeListMessage(asSceneObject());

	try {

		attributeListComponent->fillAttributeList(alm, object, asSceneObject());

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
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != NULL && zoneServer->isServerLoading())
		return;

	if (parent != NULL) {
		ManagedReference<SceneObject*> grandParent = getRootParent().get();

		if (grandParent != NULL) {
			grandParent->broadcastObjectPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		info("Null closeobjects vector in SceneObjectImplementation::broadcastObjectPrivate", true);
		zone->getInRangeObjects(getPositionX(), getPositionY(), ZoneServer::CLOSEOBJECTRANGE, &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else {
		CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
		closeSceneObjects.removeAll(vec->size(), 10);

		vec->safeCopyTo(closeSceneObjects);

		maxInRangeObjectCount = closeSceneObjects.size(); //closeobjects->size();

	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.get(i).get());

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL || scno->isMount()) {
			object->sendTo(scno, true);
		}
	}
}

void SceneObjectImplementation::broadcastObject(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? NULL : asSceneObject();
	broadcastObjectPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastDestroyPrivate(SceneObject* object, SceneObject* selfObject) {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != NULL && zoneServer->isServerLoading())
		return;

	if (parent.get() != NULL) {
		ManagedReference<SceneObject*> grandParent = getRootParent().get();

		if (grandParent != NULL) {
			grandParent->broadcastDestroyPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == NULL)
		return;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		info("Null closeobjects vector in SceneObjectImplementation::broadcastDestroyPrivate", true);
		zone->getInRangeObjects(getPositionX(), getPositionY(), ZoneServer::CLOSEOBJECTRANGE + 64, &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else {

		CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
		closeSceneObjects.removeAll(vec->size(), 10);

		vec->safeCopyTo(closeSceneObjects);

		maxInRangeObjectCount = closeSceneObjects.size();

	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.get(i).get());

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL || scno->isMount()) {
			object->sendDestroyTo(scno);
		}
	}
}

void SceneObjectImplementation::broadcastDestroy(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? NULL : asSceneObject();
	broadcastDestroyPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastMessagePrivate(BasePacket* message, SceneObject* selfObject, bool lockZone) {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != NULL && zoneServer->isServerLoading())
		return;

	if (parent.get() != NULL) {
		ManagedReference<SceneObject*> grandParent = getRootParent().get();

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

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeSceneObjects = NULL;
	SortedVector<QuadTreeEntry*>* closeNoneReference = NULL;
	int maxInRangeObjectCount = 0;
	bool deleteVector = true;

	try {
		if (closeobjects == NULL) {
			info(String::valueOf(getObjectID()) + " Null closeobjects vector in SceneObjectImplementation::broadcastMessagePrivate", true);
			closeSceneObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
			zone->getInRangeObjects(getPositionX(), getPositionY(), ZoneServer::CLOSEOBJECTRANGE, closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects->size();
			deleteVector = true;
		} else {
			maxInRangeObjectCount = closeobjects->size();
			closeNoneReference = new SortedVector<QuadTreeEntry*>(maxInRangeObjectCount, 50);

			closeobjects->safeCopyTo(*closeNoneReference);
			maxInRangeObjectCount = closeNoneReference->size();
		}


	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		delete message;

		throw;
	} catch (...) {
		delete message;

		throw;
	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeSceneObjects != NULL)
			scno = static_cast<SceneObject*>(closeSceneObjects->get(i).get());
		else
			scno = static_cast<SceneObject*>(closeNoneReference->get(i));

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL || scno->isMount())
			scno->sendMessage(message->clone());
	}

	delete message;

	if (closeSceneObjects != NULL)
		delete closeSceneObjects;	
	else
		delete closeNoneReference;
}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	SceneObject* selfObject = sendSelf ? NULL : asSceneObject();

	broadcastMessagePrivate(message, selfObject, lockZone);
}

void SceneObjectImplementation::broadcastMessagesPrivate(Vector<BasePacket*>* messages, SceneObject* selfObject) {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != NULL && zoneServer->isServerLoading())
		return;

	if (parent.get() != NULL) {
		ManagedReference<SceneObject*> grandParent = getRootParent().get();

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

	bool readlock = !zone->isLockedByCurrentThread();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	try {

		if (closeobjects == NULL) {
			info(String::valueOf(getObjectID()) + " Null closeobjects vector in SceneObjectImplementation::broadcastMessagesPrivate", true);
			zone->getInRangeObjects(getPositionX(), getPositionY(), ZoneServer::CLOSEOBJECTRANGE, &closeSceneObjects, true);

			maxInRangeObjectCount = closeSceneObjects.size();
		} else {
			maxInRangeObjectCount = closeobjects->size();

			closeSceneObjects.removeAll(maxInRangeObjectCount, 10);

			closeobjects->safeCopyTo(closeSceneObjects);

			maxInRangeObjectCount = closeSceneObjects.size();
		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (selfObject == scno)
			continue;

		ManagedReference<ZoneClientSession*> client = scno->getClient();

		if (scno->isVehicleObject() || client != NULL || scno->isMount()) {
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
	SceneObject* selfObject = sendSelf ? NULL : asSceneObject();

	broadcastMessagesPrivate(messages, selfObject);
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	if (getZone() == NULL)
		return 0;

	int numberOfObjects = 0;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == NULL) {
		info("Null closeobjects vector in SceneObjectImplementation::inRangeObjects", true);
		zone->getInRangeObjects(getPositionX(), getPositionY(), range, &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else
		maxInRangeObjectCount = closeobjects->size();

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno;

		if (closeobjects != NULL)
			scno = static_cast<SceneObject*>(closeobjects->get(i).get());
		else
			scno = static_cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (scno->isInRange(asSceneObject(), range) && scno->getGameObjectType() == gameObjectType)
			++numberOfObjects;
	}

	return numberOfObjects;
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
	delete msg;
}

void SceneObjectImplementation::updateVehiclePosition(bool sendPackets) {
	ManagedReference<SceneObject*> parent = getParent().get();

	if (parent == NULL || (!parent->isVehicleObject() && !parent->isMount()))
		return;

	Vector3 position = getPosition();

	parent->setPosition(getPositionX(), getPositionZ(), getPositionY());
	Quaternion dir = direction;
	EXECUTE_TASK_4(parent, position, dir, sendPackets, {
			Locker locker(parent_p);

			parent_p->setDirection(dir_p.getW(),
					dir_p.getX(), dir_p.getY(), dir_p.getZ());
			parent_p->setPosition(position_p.getX(), position_p.getZ(), position_p.getY());

			parent_p->incrementMovementCounter();

			parent_p->updateZone(false, sendPackets_p);
		}
	);
}

void SceneObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZone(asSceneObject(), lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifySelfPositionUpdate() {
	notifyObservers(ObserverEventType::POSITIONCHANGED);
}

void SceneObjectImplementation::notifyCloseContainer(CreatureObject* player) {
	notifyObservers(ObserverEventType::CLOSECONTAINER, player);
}

void SceneObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	if (entry == NULL || asSceneObject() == entry)
		return;

	//#ifdef WITH_STM
	notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
	//#else

	//Core::getTaskManager()->executeTask(new PositionUpdateTask(asSceneObject(), entry));
	//#endif

	zoneComponent->notifyPositionUpdate(asSceneObject(), entry);
}

void SceneObjectImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	zoneComponent->updateZoneWithParent(asSceneObject(), newParent, lightUpdate, sendPackets);
}

void SceneObjectImplementation::notifyInsertToZone(Zone* newZone) {
	zoneComponent->notifyInsertToZone(asSceneObject(), newZone);
}

void SceneObjectImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	zoneComponent->teleport(asSceneObject(), newPositionX, newPositionZ, newPositionY, parentID);
}

void SceneObjectImplementation::switchZone(const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility) {
	zoneComponent->switchZone(asSceneObject(), newTerrainName, newPostionX, newPositionZ, newPositionY, parentID, toggleInvisibility);
}

void SceneObjectImplementation::updateDirection(float fw, float fx, float fy, float fz) {
	setDirection(fw, fx, fy, fz);

	++movementCounter;

	if (parent.get() != NULL) {
		DataTransformWithParent* pack = new DataTransformWithParent(asSceneObject());
		broadcastMessage(pack, true, true);
	} else {
		DataTransform* pack = new DataTransform(asSceneObject());
		broadcastMessage(pack, true, true);
	}
}

void SceneObjectImplementation::updateDirection(float angleHeadingRadians) {
	setDirection(angleHeadingRadians);

	++movementCounter;

	if (parent.get() != NULL) {
		DataTransformWithParent* pack = new DataTransformWithParent(asSceneObject());
		broadcastMessage(pack, true, true);
	} else {
		DataTransform* pack = new DataTransform(asSceneObject());
		broadcastMessage(pack, true, true);
	}
}

void SceneObjectImplementation::notifyRemoveFromZone() {
	zoneComponent->notifyRemoveFromZone(asSceneObject());
}

int SceneObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	return containerComponent->canAddObject(asSceneObject(), object, containmentType, errorDescription);
}

bool SceneObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow) {
	return containerComponent->transferObject(asSceneObject(), object, containmentType, notifyClient, allowOverflow);
}

bool SceneObjectImplementation::removeObject(SceneObject* object, SceneObject* destination, bool notifyClient) {
	return containerComponent->removeObject(asSceneObject(), object, destination, notifyClient);
}

void SceneObjectImplementation::openContainerTo(CreatureObject* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(asSceneObject());
	player->sendMessage(cont);

	sendContainerObjectsTo(player);
}

void SceneObjectImplementation::closeContainerTo(CreatureObject* player, bool notify) {
	if (notify) {
		ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(asSceneObject(), true);
		player->sendMessage(cont);
	}
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getRootParent() {
	ManagedReference<SceneObject*> grandParent = getParent();
	ManagedReference<SceneObject*> tempParent = NULL;

	if (grandParent == NULL)
		return NULL;

#ifdef DEBUG_GETROOT_PARENT
	SortedVector<ManagedReference<SceneObject*> > parents;
	parents.setNoDuplicateInsertPlan();
#endif

	while ((tempParent = grandParent->getParent()) != NULL && grandParent != asSceneObject()) {
		grandParent = tempParent;

#ifdef DEBUG_GETROOT_PARENT
		if (parents.contains(grandParent))
			return NULL;
		else
			parents.put(grandParent);
#endif
	}

	if (grandParent == asSceneObject())
		return NULL;

	ManagedWeakReference<SceneObject*> weak = grandParent.get();

	return weak;
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParentRecursively(uint32 gameObjectType) {
	ManagedReference<SceneObject*> temp = getParent();

	if (temp == NULL)
		return NULL;

	if (temp->getGameObjectType() == gameObjectType)
		return temp.get();

	while ((temp = temp->getParent()) != NULL && temp != asSceneObject()) {
		if (temp->getGameObjectType() == gameObjectType) {
			ManagedWeakReference<SceneObject*> weak = temp.get();

			return weak;
		}
	}

	if (temp == asSceneObject())
		return NULL;

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
	if (getZone() != object->getZone()) {
		return false;
	}

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
	return objectMenuComponent->fillObjectMenuResponse(asSceneObject(), menuResponse, player);
}

int SceneObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	return objectMenuComponent->handleObjectMenuSelect(asSceneObject(), player, selectedID);
}

void SceneObjectImplementation::setObjectName(StringId& stringID) {
	objectName = stringID;
}

Vector3 SceneObjectImplementation::getWorldPosition() {
	if (parent.get() == NULL)
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
	if (parent.get() == NULL)
		return getPositionX();

	ManagedReference<SceneObject*> root = cast<SceneObject*>(getRootParentUnsafe());

	if (root == NULL || !root->isBuildingObject())
		return getPositionX();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionX() + (sin(angle) * length);
}

float SceneObjectImplementation::getWorldPositionY() {
	if (parent.get() == NULL)
		return getPositionY();

	ManagedReference<SceneObject*> root = cast<SceneObject*>(getRootParentUnsafe());

	if (root == NULL || !root->isBuildingObject())
		return getPositionY();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionY() + (cos(angle) * length);
}

float SceneObjectImplementation::getWorldPositionZ() {
	if (parent.get() == NULL)
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

		Locker objLocker(obj);

		Vector3 childPosition = child->getPosition();
		childObjects.put(obj);
		obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
		obj->setDirection(child->getDirection());

		if (isBuildingObject() && child->getCellId() >= 0) {
			BuildingObject* buildingObject = asBuildingObject();

			int totalCells = buildingObject->getTotalCellNumber();

			try {
				if (totalCells >= child->getCellId()) {
					ManagedReference<CellObject*> cellObject = buildingObject->getCell(child->getCellId());

					if (cellObject != NULL) {
						if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
							obj->destroyObjectFromDatabase(true);
							continue;
						}
						//cellObject->broadcastObject(obj, false);
					} else {
						error("NULL CELL OBJECT");
						obj->destroyObjectFromDatabase(true);
						continue;
					}
				}
			} catch (Exception& e) {
				error("unreported exception caught in void SceneObjectImplementation::createChildObjects()!");
				e.printStackTrace();
			}
		} else {
			//Create the object outdoors in relation to its parent.
			Vector3 position;
			if (obj->isActiveArea())
				position = getWorldPosition();
			else
				position = getPosition();

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

			if (!getZone()->transferObject(obj, -1, false)) {
				obj->destroyObjectFromDatabase(true);
				continue;
			}
		}

		//childObjects.put(obj);
		ContainerPermissions* permissions = obj->getContainerPermissions();
		permissions->setOwner(getObjectID());
		permissions->setInheritPermissionsFromParent(false);
		permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

		obj->initializeChildObject(asSceneObject());
	}
}

void SceneObjectImplementation::destroyChildObjects() {
	int size = childObjects.size();

	for (int i = 0; i < size; i++) {
		ManagedReference<SceneObject*> child = childObjects.get(0);

		if (child == NULL)
			continue;

		Locker clocker(child, asSceneObject());

		childObjects.drop(child);
		child->destroyObjectFromDatabase(true);
		child->destroyObjectFromWorld(true);
	}
}

bool SceneObjectImplementation::isFacingObject(SceneObject* obj) {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float directionangle = atan2(targetPos.getX() - thisPos.getX(), targetPos.getY() - thisPos.getY());

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	return fabs(directionangle - direction.getRadians()) < (M_PI / 2);
}

void SceneObjectImplementation::faceObject(SceneObject* obj, bool notifyClient) {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float directionangle = atan2(targetPos.getX() - thisPos.getX(), targetPos.getY() - thisPos.getY());

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	float err = fabs(directionangle - direction.getRadians());

	if (err < 0.05) {
		//info("not updating " + String::valueOf(directionangle), true);
		return;
	}

	if (notifyClient) {
		updateDirection(directionangle);
	} else {
		direction.setHeadingDirection(directionangle);
	}
}

void SceneObjectImplementation::getContainerObjects(VectorMap<uint64, ManagedReference<SceneObject*> >& objects) {
	containerObjects.loadObjects();

	ReadLocker locker(&containerLock);

	objects = *containerObjects.getContainerObjects();
}

void SceneObjectImplementation::getSlottedObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	ReadLocker locker(&containerLock);

	objects = slottedObjects;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(const String& slot) {
	ManagedReference<SceneObject*> obj = NULL;

	ReadLocker locker(&containerLock);

	obj = slottedObjects.get(slot);

	return obj;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(int idx) {
	ManagedReference<SceneObject*> obj = NULL;

	ReadLocker locker(&containerLock);

	obj = slottedObjects.get(idx);

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
	ShowFlyText* fly = new ShowFlyText(asSceneObject(), file, aux, red, green, blue);

	broadcastMessage(fly, true);
}

void SceneObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
}

void SceneObjectImplementation::setParent(QuadTreeEntry* entry) {
	Locker locker(&parentLock);

	QuadTreeEntryImplementation::setParent(entry);
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParent() {
	Locker locker(&parentLock);

	ManagedReference<QuadTreeEntry*> parent = this->parent.get();

	if (parent == NULL)
		return NULL;

	assert(parent != asSceneObject());

	return ManagedWeakReference<SceneObject*>(parent.castTo<SceneObject*>());
}

SortedVector<ManagedReference<Observer* > > SceneObjectImplementation::getObservers(unsigned int eventType) {
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

bool SceneObjectImplementation::containsNoTradeObjectRecursive() {
	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		if (obj->isNoTrade()){
			return true;
		}

		if (obj->containsNoTradeObjectRecursive()) {
			return true;
		}
	}

	return false;

}
String SceneObjectImplementation::getDisplayedName() {
	if (!customName.isEmpty())
		return customName.toString();

	return StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
}

bool SceneObjectImplementation::setTransformForCollisionMatrixIfNull(Matrix4* mat) {
	return transformForCollisionMatrix.compareAndSet(NULL, mat);
}

int SceneObjectImplementation::getCountableObjectsRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		if (obj != NULL) {
			++count;

			count += obj->getCountableObjectsRecursive();
		}
	}

	return count;
}

int SceneObjectImplementation::getContainedObjectsRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		++count;

		count += obj->getContainedObjectsRecursive();
	}

	return count;
}

int SceneObjectImplementation::getSizeOnVendorRecursive() {
	int count = 0;

	Locker locker(&containerLock);

	if (containerObjects.size() == 0)
		++count;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		count += obj->getSizeOnVendorRecursive();
	}

	return count;
}

bool SceneObjectImplementation::isDecoration() {
	return (templateObject != NULL &&
			(templateObject->getFullTemplateString().contains("object/tangible/furniture/city") ||
					templateObject->getFullTemplateString().contains("object/building/player/city/garden")));
}

Reference<SceneObject*> SceneObjectImplementation::getContainerObjectRecursive(uint64 oid) {
	ManagedReference<SceneObject*> obj = containerObjects.get(oid);

	if (obj != NULL)
		return obj;

	for (int i = 0; i < containerObjects.size(); ++i) {
		Locker locker(&containerLock);

		ManagedReference<SceneObject*> inContainerObject = containerObjects.get(i);

		obj = inContainerObject->getContainerObjectRecursive(oid);

		if (obj != NULL)
			break;
	}

	return obj;
}

const Vector<String>* SceneObjectImplementation::getArrangementDescriptor(int idx) {
	return &templateObject->getArrangementDescriptors()->get(idx);
}

bool SceneObjectImplementation::hasObjectInSlottedContainer(SceneObject* object) {
	int arrangementSize = object->getArrangementDescriptorSize();

	if (arrangementSize == 0) {
		return false;
	}

	ManagedReference<SceneObject* > obj = NULL;

	Locker _locker(&containerLock);

	for (int i = 0; i < arrangementSize; ++i) {
		const Vector<String>* descriptors = object->getArrangementDescriptor(i);

		for (int j = 0; j < descriptors->size(); ++j) {
			if (slottedObjects.get(descriptors->get(j)) != NULL)
				return true;
		}
	}

	return false;
}

int SceneObjectImplementation::getArrangementDescriptorSize() {
	return templateObject->getArrangementDescriptors()->size();
}

bool SceneObjectImplementation::isDataPad() {
	return templateObject->getFullTemplateString().contains("datapad");
}

float SceneObjectImplementation::getTemplateRadius() {
	if (templateObject == NULL || templateObject->getAppearanceTemplate() == NULL)
		return 0.f;

	MeshAppearanceTemplate* app = cast<MeshAppearanceTemplate*>(templateObject->getAppearanceTemplate());

	if (app == NULL || app->getBoundingSphere() == NULL)
		return 0.f;

	// we currently don't scale these, so we have no scale variable
	return app->getBoundingSphere()->getRadius();
}

void SceneObjectImplementation::playEffect(const String& file,
		const String& aux) {
	PlayClientEffectObjectMessage* effect = new PlayClientEffectObjectMessage(
			asSceneObject(), file, aux);

	broadcastMessage(effect, true);
}

SceneObject* SceneObjectImplementation::asSceneObject() {
	return _this.getReferenceUnsafeStaticCast();
}

SceneObject* SceneObject::asSceneObject() {
	return this;
}

