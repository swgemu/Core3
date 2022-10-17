/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/scene/UpdateContainmentMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/scene/ClientOpenContainerMessage.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/object/ShowFlyText.h"

#include "server/zone/ZoneClientSession.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

#include "variables/StringId.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "templates/ChildObject.h"
#include "templates/appearance/MeshAppearanceTemplate.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/LuaObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/scene/components/LuaContainerComponent.h"
#include "server/zone/objects/scene/SceneObjectType.h"
//#include "PositionUpdateTask.h"

#include "variables/ContainerPermissions.h"

#include <fstream>
#include <sys/stat.h>
#include <iomanip>

void SceneObjectImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	receiverFlags = getReceiverFlags();

	// FIXME: temp hack
	if (server == nullptr)
		server = Core::lookupObject<ZoneProcessServer>("ZoneProcessServer").get();

	templateObject = TemplateManager::instance()->getTemplate(serverObjectCRC);

	if (templateObject != nullptr) {
		createContainerComponent();

		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);

		if (zoneComponent == nullptr) {
			zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
		}

		createObjectMenuComponent();
	}

	if (dataObjectComponent != nullptr) {
		dataObjectComponent->setParent(asSceneObject());
		dataObjectComponent->initializeTransientMembers();
	}

	movementCounter = 0;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");

	if (originalObjectID == 0) {
		originalObjectID = getObjectID();
	}
}

void SceneObjectImplementation::initializePrivateData() {
	pendingTasks = nullptr;

	objectActiveSessions.setNullValue(nullptr);
	objectActiveSessions.setNoDuplicateInsertPlan();

	server = nullptr;

	templateObject = nullptr;

	parent = nullptr;

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

	forceSend = false;
	staticObject = false;

	zone = nullptr;

	containerType = 0;
	containerVolumeLimit = 0;
	containmentType = 0;

	savedRootParent = nullptr;

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("SceneObject");

	childObjects.setNoDuplicateInsertPlan();

	collidableObject = false;

	originalObjectID = 0;

	forceNoTrade = false;
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

	if (templateData->getPlanetMapCategory() != nullptr)
		planetMapCategory = templateData->getPlanetMapCategory()->getCrc();

	if (templateData->getPlanetMapSubCategory() != nullptr)
		planetMapSubCategory = templateData->getPlanetMapSubCategory()->getCrc();

	templateObject = templateData;

	dataObjectComponent = ComponentManager::instance()->getDataObjectComponent(templateData->getDataObjectComponent());

	if (!isCreatureObject() && !isLairObject() && gameObjectType != SceneObjectType::FURNITURE) {
		if (templateData->getCollisionMaterialFlags() && templateData->getCollisionMaterialBlockFlags() && templateData->isNavUpdatesEnabled()) {
			collidableObject = true;
		}
	}

	if (templateObject->getDelayedContainerLoad()) {
		containerObjects.setDelayedLoadOperationMode();
	}
}

void SceneObjectImplementation::setZoneComponent(const String& name) {
	if(name.isEmpty())
		return;

	zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(name);
}

void SceneObjectImplementation::createContainerComponent() {
	setContainerComponent(templateObject->getContainerComponent());
}

void SceneObjectImplementation::createObjectMenuComponent() {
	setObjectMenuComponent(templateObject->getObjectMenuComponent());
}

void SceneObjectImplementation::createComponents() {
	if (templateObject != nullptr) {
		String zoneComponentClassName = templateObject->getZoneComponent();
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>(zoneComponentClassName);
		//zoneComponent->initialize(_this.getReferenceUnsafe());

		if (zoneComponent == nullptr) {
			info() << "zone component \'" << zoneComponentClassName << "\' null in " <<
			       	templateObject->getFullTemplateString();
		}

		createObjectMenuComponent();

		String attributeListComponentName = templateObject->getAttributeListComponent();
		if (!attributeListComponentName.isEmpty()) {
			attributeListComponent = ComponentManager::instance()->getComponent<AttributeListComponent*>(attributeListComponentName);

			if (attributeListComponent == nullptr) {
				info() << "attributeList component null for " << templateObject->getFullTemplateString();
			}
		}

		createContainerComponent();

	} else
		error("nullptr TEMPLATE OBJECT");

	if (zoneComponent == nullptr) {
		zoneComponent = ComponentManager::instance()->getComponent<ZoneComponent*>("ZoneComponent");
	}
}

void SceneObjectImplementation::close(SceneObject* client) {
	BaseMessage* msg = new SceneObjectCloseMessage(asSceneObject());

	client->sendMessage(msg);
}

void SceneObjectImplementation::link(SceneObject* client, uint32 containmentType) {
	auto ref = getParent().get();

	if (ref == nullptr)
		return;

	BaseMessage* msg = new UpdateContainmentMessage(asSceneObject(), ref, containmentType);
	client->sendMessage(msg);
}

BaseMessage* SceneObjectImplementation::link(uint64 objectID, uint32 containmentType) {
	return new UpdateContainmentMessage(getObjectID(), objectID, containmentType);
}

void SceneObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	debug() << "deleting from database";

	fatal(!isPlayerCreature()) << "attempting to delete a player creature from database";

	containerObjects.cancelUnloadTask();

	if(dataObjectComponent != nullptr) {
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

		if (child == nullptr)
			continue;

		Locker locker(child);

		child->destroyObjectFromDatabase(true);
	}
}

void SceneObjectImplementation::sendWithoutParentTo(SceneObject* player) {
	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player, true);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	if ((isClientObject() && !forceSend) || !sendToClient || player == nullptr || player->getClient() == nullptr)
		return;

	/*StringBuffer msgInfo;
	if (parent != nullptr)
		msgInfo << "with parent " << getParent()->getLoggingName() << " ";
	msgInfo << "sending 0x" << hex << getClientObjectCRC() << " to " << player->getLoggingName();
	info(msgInfo.toString(), true);*/

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	link(player, containmentType);

	try {
		sendBaselinesTo(player);

		sendContainerObjectsTo(player, forceLoadContainer);

		sendSlottedObjectsTo(player);
	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (doClose) {
		SceneObjectImplementation::close(player);
	}
}

void SceneObjectImplementation::sendWithoutContainerObjectsTo(SceneObject* player) {
	if (isClientObject() || !sendToClient)
		return;

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	if (parent.get() != nullptr)
		link(player, containmentType);

	sendBaselinesTo(player);

	SceneObjectImplementation::close(player);
}

void SceneObjectImplementation::notifyLoadFromDatabase() {
	if (!containerObjects.hasDelayedLoadOperationMode()) {
		for (int i = 0; i < slottedObjects.size(); ++i) {
			ManagedReference<SceneObject* > obj = slottedObjects.get(i);

			if (obj->getParent() != asSceneObject()) {
				obj->setParent(asSceneObject(), false);

				if (obj->isPlayerCreature())
					obj->setContainmentType(5);
				else
					obj->setContainmentType(4);
			}
		}

		for (int i = 0; i < containerObjects.size(); ++i) {
			ManagedReference<SceneObject* > obj = containerObjects.get(i);

			if (obj->getParent() != asSceneObject()) {
				obj->setParent(asSceneObject(), false);
				obj->setContainmentType(-1);
			}
		}

	}

	if (zone != nullptr) {
		class InsertZoneTask : public Task {
			Reference<SceneObject*> obj;
			Zone* zone;

			public:

			InsertZoneTask(SceneObject* s, Zone* z) : obj(s), zone(z) {
				setCustomTaskQueue(zone->getZoneName().toCharArray());
			}

			void run() {
				if (!zone->hasManagersStarted()) {
					schedule(500);

					return;
				}

				Locker locker(obj);

				zone->transferObject(obj, -1, true);
			}
		};

		auto task = new InsertZoneTask(asSceneObject(), zone);
		task->execute();
	}
}

void SceneObjectImplementation::setObjectMenuComponent(const String& name) {
	if (name.isEmpty())
		return;

	objectMenuComponent = ComponentManager::instance()->getComponent<ObjectMenuComponent*>(name);

	if (objectMenuComponent == nullptr) {
		Lua* lua = DirectorManager::instance()->getLuaInstance();
		LuaObject test = lua->getGlobalObject(name);

		if (test.isValidTable()) {
			objectMenuComponent = new LuaObjectMenuComponent(name);
			debug() << "New Lua ObjectMenuComponent created: '" << name << "' for " << templateObject->getFullTemplateString();

			ComponentManager::instance()->putComponent(name, objectMenuComponent);
		} else {
			error() << "ObjectMenuComponent not found: '" << name << "' for " << templateObject->getFullTemplateString();
		}

		test.pop();
	}
}

void SceneObjectImplementation::setContainerComponent(const String& name) {
	if (name.isEmpty())
		return;

	containerComponent = ComponentManager::instance()->getComponent<ContainerComponent*>(name);

	if (containerComponent == nullptr) {
		Lua* lua = DirectorManager::instance()->getLuaInstance();
		LuaObject test = lua->getGlobalObject(name);

		if (test.isValidTable()) {
			containerComponent = new LuaContainerComponent(name);
			debug() << "New Lua ContainerComponent created: '" << name << "' for " << templateObject->getFullTemplateString();

			ComponentManager::instance()->putComponent(name, containerComponent);
		} else {
			error() << "ContainerComponent not found: '" <<  name << "' for " << templateObject->getFullTemplateString();
		}

		test.pop();
	}
}

void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<uint64> objects(slotted.size(), slotted.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slotted.size(); ++i) {
		SceneObject* object = slotted.get(i);

		if (objects.put(object->getObjectID()) != -1) {
			if (object->isInQuadTree()) {
				notifyInsert(object);
			} else {
				object->sendTo(player, true, false);
			}
		}
	}
}

void SceneObjectImplementation::sendContainerObjectsTo(SceneObject* player, bool forceLoad) {
	if (forceLoad || containerObjects.isLoaded() || isASubChildOf(player)) {
		//sending all objects by default
		VectorMap<uint64, ManagedReference<SceneObject* > > objects;
		getContainerObjects(objects);

		for (int j = 0; j < objects.size(); ++j) {
			SceneObject* containerObject = objects.get(j);

			if (containerObject == nullptr)
				continue;

			if (containerObject->isInQuadTree()) {
				notifyInsert(containerObject);
			} else {
				containerObject->sendTo(player, true, false);
			}
		}
	}
}

void SceneObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (staticObject)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(asSceneObject());
	player->sendMessage(msg);
}

void SceneObjectImplementation::sendAttributeListTo(CreatureObject* object) {
	AttributeListMessage* alm = new AttributeListMessage(asSceneObject());

	try {
        	if (attributeListComponent == nullptr) {
			throw Exception("nullptr attribute list component");
		}

		attributeListComponent->fillAttributeList(alm, object, asSceneObject());

	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		delete alm;
		alm = nullptr;
	} catch (...) {
		delete alm;
		alm = nullptr;

		throw;
	}

	if (alm != nullptr)
		object->sendMessage(alm);
}

void SceneObjectImplementation::broadcastObjectPrivate(SceneObject* object, SceneObject* selfObject) {
	const ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown())
		return;

	if (parent != nullptr) {
		ManagedReference<SceneObject*> grandParent = getRootParent();

		if (grandParent != nullptr) {
			grandParent->broadcastObjectPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == nullptr)
		return;

	SortedVector<QuadTreeEntry*> closeSceneObjects;

	int maxInRangeObjectCount = 0;

	if (closeobjects == nullptr) {
#ifdef COV_DEBUG
		info("Null closeobjects vector in SceneObjectImplementation::broadcastObjectPrivate", true);
#endif
		zone->getInRangeObjects(getPositionX(), getPositionY(), getOutOfRangeDistance(), &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else {
		CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
		closeSceneObjects.removeAll(vec->size(), 10);

		vec->safeCopyReceiversTo(closeSceneObjects, CloseObjectsVector::PLAYERTYPE);

		maxInRangeObjectCount = closeSceneObjects.size(); //closeobjects->size();
	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.get(i));
		object->sendTo(scno, true, false);
	}
}

void SceneObjectImplementation::broadcastObject(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? nullptr : asSceneObject();
	broadcastObjectPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastDestroyPrivate(SceneObject* object, SceneObject* selfObject) {
	const ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown())
		return;

	if (parent != nullptr) {
		ManagedReference<SceneObject*> grandParent = getRootParent();

		if (grandParent != nullptr) {
			grandParent->broadcastDestroyPrivate(object, selfObject);

			return;
		} else {
			return;
		}
	}

	if (zone == nullptr)
		return;

	SortedVector<QuadTreeEntry*> closeSceneObjects;
	int maxInRangeObjectCount = 0;

	if (closeobjects == nullptr) {
#ifdef COV_DEBUG
		info("Null closeobjects vector in SceneObjectImplementation::broadcastDestroyPrivate", true);
#endif
		zone->getInRangeObjects(getPositionX(), getPositionY(), getOutOfRangeDistance() + 64, &closeSceneObjects, true);

		maxInRangeObjectCount = closeSceneObjects.size();
	} else {

		CloseObjectsVector* vec = (CloseObjectsVector*) closeobjects;
		closeSceneObjects.removeAll(vec->size(), 10);

		vec->safeCopyReceiversTo(closeSceneObjects, CloseObjectsVector::PLAYERTYPE);

		maxInRangeObjectCount = closeSceneObjects.size();

	}

	for (int i = 0; i < maxInRangeObjectCount; ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.get(i));

		if (selfObject != object)
			object->sendDestroyTo(scno);
	}
}

void SceneObjectImplementation::broadcastDestroy(SceneObject* object, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? nullptr : asSceneObject();
	broadcastDestroyPrivate(object, selfObject);
}

void SceneObjectImplementation::broadcastMessagePrivate(BasePacket* message, SceneObject* selfObject, bool lockZone) {
	const ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		delete message;
		return;
	}

	if (parent != nullptr) {
		ManagedReference<SceneObject*> grandParent = getRootParent();

		if (grandParent != nullptr) {
			grandParent->broadcastMessagePrivate(message, selfObject, lockZone);

			return;
		} else {
			delete message;

			return;
		}
	}

	if (zone == nullptr) {
		delete message;

		return;
	}

#ifdef LOCKFREE_BCLIENT_BUFFERS
	if (closeobjects) {
		closeobjects->safeRunForEach([pack = Reference<BasePacket*>(message) ](auto value) {
				SceneObject* scno = static_cast<SceneObject*>(value);
				scno->sendMessage(pack);
			}, CloseObjectsVector::PLAYERTYPE);

		return;
	}

#endif

	SortedVector<QuadTreeEntry*> closeNoneReference;

	try {
		if (closeobjects == nullptr) {
#ifdef COV_DEBUG
			info(String::valueOf(getObjectID()) + " Null closeobjects vector in SceneObjectImplementation::broadcastMessagePrivate", true);
#endif
			zone->getInRangeObjects(getPositionX(), getPositionY(), getOutOfRangeDistance(), &closeNoneReference, true);
		} else {
			closeobjects->safeCopyReceiversTo(closeNoneReference, CloseObjectsVector::PLAYERTYPE);
		}

	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		delete message;

		throw;
	} catch (...) {
		delete message;

		throw;
	}

#ifdef LOCKFREE_BCLIENT_BUFFERS
	Reference<BasePacket*> pack = message;
#endif

	for (int i = 0; i < closeNoneReference.size(); ++i) {
		SceneObject* sceneO = static_cast<SceneObject*>(closeNoneReference.getUnsafe(i));

		if (sceneO == nullptr || sceneO == selfObject)
			continue;

#ifdef LOCKFREE_BCLIENT_BUFFERS
		sceneO->sendMessage(pack);
#else
		sceneO->sendMessage(message->clone());
#endif
	}

#ifndef LOCKFREE_BCLIENT_BUFFERS
	delete message;
#endif
}

void SceneObjectImplementation::broadcastMessage(BasePacket* message, bool sendSelf, bool lockZone) {
	SceneObject* selfObject = sendSelf ? nullptr : asSceneObject();

	broadcastMessagePrivate(message, selfObject, lockZone);
}

void SceneObjectImplementation::broadcastMessagesPrivate(Vector<BasePacket*>* messages, SceneObject* selfObject) {
	const ZoneServer* zoneServer = getZoneServer();

	static const auto clearMessages = [](auto messages) {
		messages->forEach([](auto message) { delete message; });
		messages->removeAll();
	};

	if (zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		clearMessages(messages);

		return;
	}

	if (parent != nullptr) {
		ManagedReference<SceneObject*> grandParent = getRootParent();

		if (grandParent != nullptr) {
			grandParent->broadcastMessagesPrivate(messages, selfObject);

			return;
		} else {
			clearMessages(messages);

			return;
		}
	}

	if (zone == nullptr) {
		clearMessages(messages);

		return;
	}

	SortedVector<QuadTreeEntry*> closeSceneObjects;

	try {

		if (closeobjects == nullptr) {
#ifdef COV_DEBUG
			info(true) << getObjectID() << " Null closeobjects vector in SceneObjectImplementation::broadcastMessagesPrivate";
#endif
			zone->getInRangeObjects(getPositionX(), getPositionY(), getOutOfRangeDistance(), &closeSceneObjects, true);
		} else {
			closeobjects->safeCopyReceiversTo(closeSceneObjects, CloseObjectsVector::PLAYERTYPE);
		}

	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

#ifdef LOCKFREE_BCLIENT_BUFFERS
	for (int j = 0; j < messages->size(); ++j) {
		BasePacket* msg = messages->getUnsafe(j);
		msg->acquire();
	}
#endif

	for (int i = 0; i < closeSceneObjects.size(); ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeSceneObjects.getUnsafe(i));

		if (selfObject == scno)
			continue;

		for (int j = 0; j < messages->size(); ++j) {
			BasePacket* msg = messages->getUnsafe(j);
#ifdef LOCKFREE_BCLIENT_BUFFERS
			scno->sendMessage(msg);
#else
			scno->sendMessage(msg->clone());
#endif
		}
	}

	for (int j = 0; j < messages->size(); ++j) {
		auto message = messages->getUnsafe(j);
#ifdef LOCKFREE_BCLIENT_BUFFERS
		message->release();
#else
		delete message;
#endif
	}

	messages->removeAll();
}

void SceneObjectImplementation::broadcastMessages(Vector<BasePacket*>* messages, bool sendSelf) {
	SceneObject* selfObject = sendSelf ? nullptr : asSceneObject();

	broadcastMessagesPrivate(messages, selfObject);
}

int SceneObjectImplementation::inRangeObjects(unsigned int gameObjectType, float range) {
	auto zone = getZoneUnsafe();

	if (zone == nullptr)
		return 0;

	int numberOfObjects = 0;

	SortedVector<QuadTreeEntry*> closeSceneObjects;

	if (closeobjects == nullptr) {
#ifdef COV_DEBUG
		info("Null closeobjects vector in SceneObjectImplementation::inRangeObjects", true);
#endif
		zone->getInRangeObjects(getPositionX(), getPositionY(), range, &closeSceneObjects, true);
	} else {
		closeobjects->safeCopyTo(closeSceneObjects);
	}

	auto asScene = asSceneObject();

	for (int i = 0; i < closeSceneObjects.size(); ++i) {
		SceneObject* scno;

		scno = static_cast<SceneObject*>(closeSceneObjects.getUnsafe(i));

		if (scno->isInRange(asScene, range) && scno->getGameObjectType() == gameObjectType)
			++numberOfObjects;
	}

	return numberOfObjects;
}

void SceneObjectImplementation::sendMessage(BasePacket* msg) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
	if (!msg->getReferenceCount())
#endif
	delete msg;
}

void SceneObjectImplementation::updateVehiclePosition(bool sendPackets) {
	ManagedReference<SceneObject*> parent = getParent().get();

	if (parent == nullptr || (!parent->isVehicleObject() && !parent->isMount()))
		return;

	Locker locker(parent);

	parent->setDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
	parent->setPosition(getPositionX(), getPositionZ(), getPositionY());

	parent->incrementMovementCounter();

	parent->updateZone(false, sendPackets);
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
	if (entry == nullptr || asSceneObject() == entry)
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

	if (parent.get() != nullptr) {
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

	if (parent.get() != nullptr) {
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

bool SceneObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) {
	return containerComponent->transferObject(asSceneObject(), object, containmentType, notifyClient, allowOverflow, notifyRoot);
}

bool SceneObjectImplementation::removeObject(SceneObject* object, SceneObject* destination, bool notifyClient) {
	return containerComponent->removeObject(asSceneObject(), object, destination, notifyClient);
}

void SceneObjectImplementation::removeObjectFromZone(Zone* zone, SceneObject* par) {
	zoneComponent->removeObjectFromZone(asSceneObject(), zone, par);
}

void SceneObjectImplementation::openContainerTo(CreatureObject* player) {
	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(asSceneObject());
	player->sendMessage(cont);

	sendContainerObjectsTo(player, true);
}

void SceneObjectImplementation::closeContainerTo(CreatureObject* player, bool notify) {
	if (notify) {
		ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(asSceneObject(), true);
		player->sendMessage(cont);
	}
}

SceneObject* SceneObjectImplementation::getRootParent() {
	if (savedRootParent != nullptr) {
		return savedRootParent;
	}

	ManagedReference<SceneObject*> grandParent = getParent().get();
	ManagedReference<SceneObject*> tempParent = nullptr;

	if (grandParent == nullptr)
		return nullptr;

#ifdef DEBUG_GETROOT_PARENT
	SortedVector<ManagedReference<SceneObject*> > parents;
	parents.setNoDuplicateInsertPlan();
#endif

	while ((tempParent = grandParent->getParent().get()) != nullptr && grandParent != asSceneObject()) {
		grandParent = tempParent;

#ifdef DEBUG_GETROOT_PARENT
		if (parents.contains(grandParent))
			return nullptr;
		else
			parents.put(grandParent);
#endif
	}

	if (grandParent == asSceneObject())
		return nullptr;

	return grandParent;
}

SceneObject* SceneObjectImplementation::getRootParentUnsafe() {
	if (savedRootParent != nullptr) {
		return savedRootParent;
	}

	return static_cast<SceneObject*>(QuadTreeEntryImplementation::getRootParentUnsafe());
}

void SceneObjectImplementation::updateSavedRootParentRecursive(SceneObject* newRoot, int maxDepth) {
	if (maxDepth <= 0) {
		StringBuffer msg;

		msg << "maxDepth reached in updateSavedRootParentRecursive("
			<< getObjectID() << ") newRoot = "
		    << (newRoot == nullptr ? 0 : newRoot->getObjectID())
		;
		throw Exception(msg.toString());
	}

	Locker locker(&parentLock);

	if (newRoot == asSceneObject())
		savedRootParent = nullptr;
	else
		savedRootParent = newRoot;

	locker.release();

	if (containerObjects.isLoaded()) {
		for (int j = 0; j < getContainerObjectsSize(); ++j) {
			ManagedReference<SceneObject*> object = getContainerObject(j);

			object->updateSavedRootParentRecursive(newRoot, maxDepth - 1);
		}

		for (int i = 0; i < getSlottedObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object = getSlottedObject(i);

			object->updateSavedRootParentRecursive(newRoot, maxDepth - 1);
		}
	}
}

uint64 SceneObjectImplementation::getParentID() {
	return QuadTreeEntryImplementation::parent.getSavedObjectID();
}

Reference<SceneObject*> SceneObjectImplementation::getParentRecursively(uint32 gameObjectType) {
	ManagedReference<SceneObject*> temp = getParent().get();

	if (temp == nullptr)
		return nullptr;

	if (temp->getGameObjectType() == gameObjectType)
		return std::move(temp);

	while ((temp = temp->getParent().get()) != nullptr && temp != asSceneObject()) {
		if (temp->getGameObjectType() == gameObjectType) {
			return std::move(temp);
		}
	}

	if (temp == asSceneObject())
		return nullptr;

	return nullptr;
}

bool SceneObjectImplementation::isASubChildOf(SceneObject* object) {
	ManagedReference<SceneObject*> temp = getParent().get();

	if (temp == nullptr)
		return false;

	if (temp == object)
		return true;

	ManagedReference<SceneObject*> grandParent = temp;

	while ((temp = grandParent->getParent().get()) != nullptr) {
		grandParent = temp;

		if (grandParent == object)
			return true;
	}

	return false;
}

Zone* SceneObjectImplementation::getZone() {
	auto root = getRootParent();

	if (root != nullptr) {
		return root->getZone();
	} else {
		return zone;
	}
}

Zone* SceneObjectImplementation::getZoneUnsafe() const {
	auto root = const_cast<SceneObjectImplementation*>(this)->getRootParentUnsafe();

	if (root != nullptr) {
		return root->getZoneUnsafe();
	} else {
		return zone;
	}
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
 bool SceneObjectImplementation::isInRangeZoneless(SceneObject* object, float range) {
	Vector3 worldPos = object->getWorldPosition();
	worldPos.setZ(0);
	Vector3 thisPos = getWorldPosition();
	thisPos.setZ(0);

	if (thisPos.squaredDistanceTo(worldPos) <= range * range)
		return true;

	return false;
}
bool SceneObjectImplementation::isInRange3d(SceneObject* object, float range) {
	if (getZoneUnsafe() != object->getZoneUnsafe()) {
		return false;
	}

	Vector3 worldPos = object->getWorldPosition();
	Vector3 thisPos = getWorldPosition();

	if (thisPos.squaredDistanceTo(worldPos) <= range * range)
		return true;

	return false;
}

float SceneObjectImplementation::getDistanceTo(SceneObject* targetCreature) {
	auto targetWorldPosition = targetCreature->getWorldPosition();
	float x = targetWorldPosition.getX();
	float y = targetWorldPosition.getY();

	auto worldPosition = getWorldPosition();

	float deltaX = x - worldPosition.getX();
	float deltaY = y - worldPosition.getY();

	return Math::sqrt(deltaX * deltaX + deltaY * deltaY);
}

float SceneObjectImplementation::getDistanceTo(Coordinate* coordinate) {
	// TEMP till
	float x = coordinate->getPositionX();
	float y = coordinate->getPositionY();

	auto worldPosition = getWorldPosition();

	float deltaX = x - worldPosition.getX();
	float deltaY = y - worldPosition.getY();

	return Math::sqrt(deltaX * deltaX + deltaY * deltaY);
}

const Quaternion* SceneObjectImplementation::getDirection() const {
	return &direction;
}

void SceneObjectImplementation::setDirection(const Quaternion& dir) {
	direction = dir;
}

void SceneObjectImplementation::rotate(int degrees) {
	Vector3 unity(0, 1, 0);
	direction.rotate(unity, degrees);
}

void SceneObjectImplementation::rotatePitch(int degrees) {
	Vector3 unity(0, 0, 1);
	direction.rotate(unity, degrees);
}

void SceneObjectImplementation::rotateRoll(int degrees) {
	Vector3 unity(1, 0, 0);
	direction.rotate(unity, degrees);
}

void SceneObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (objectMenuComponent == nullptr) {
		error("no object menu component set for " + templateObject->getTemplateFileName());

		return;
	} else {
		return objectMenuComponent->fillObjectMenuResponse(asSceneObject(), menuResponse, player);
	}
}

int SceneObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (objectMenuComponent == nullptr) {
		error("no object menu component set for " + templateObject->getTemplateFileName());

		return 1;
	} else {
		return objectMenuComponent->handleObjectMenuSelect(asSceneObject(), player, selectedID);
	}
}

void SceneObjectImplementation::setObjectName(const StringId& stringID, bool notifyClient) {
	objectName = stringID;
}

Vector3 SceneObjectImplementation::getWorldPosition() {
	auto root = getRootParentUnsafe();

	if (root == nullptr || !root->isBuildingObject())
		return getPosition();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	float posX = root->getPositionX() + (sin(angle) * length);
	float posY = root->getPositionY() + (cos(angle) * length);
	float posZ = root->getPositionZ() + getPositionZ();

	Vector3 position(posX, posY, posZ);

	return position;
}

Vector3 SceneObjectImplementation::getCoordinate(float distance, float angleDegrees, bool includeZ) const {
	float angleRads = angleDegrees * (M_PI / 180.0f);
	float newAngle = angleRads + (M_PI / 2) - direction.getRadians();

	float newX = getPositionX() + (cos(newAngle) * distance); // client has x/y inverted
	float newY = getPositionY() + (sin(newAngle) * distance);
	float newZ = 0.0f;

	if (includeZ)
		newZ = getZoneUnsafe()->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

Vector3 SceneObjectImplementation::getWorldCoordinate(float distance, float angleDegrees, bool includeZ) {
	float angleRads = angleDegrees * (M_PI / 180.0f);
	float newAngle = angleRads + (M_PI / 2) - direction.getRadians();

	float newX = getWorldPositionX() + (cos(newAngle) * distance); // client has x/y inverted
	float newY = getWorldPositionY() + (sin(newAngle) * distance);
	float newZ = 0.0f;

	if (includeZ)
		newZ = getZoneUnsafe()->getHeight(newX, newY);

	return Vector3(newX, newY, newZ);
}

float SceneObjectImplementation::getWorldPositionX() {
	auto root = getRootParentUnsafe();

	if (root == nullptr || !root->isBuildingObject())
		return getPositionX();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionX() + (sin(angle) * length);
}

float SceneObjectImplementation::getWorldPositionY() {
	auto root = getRootParentUnsafe();

	if (root == nullptr || !root->isBuildingObject())
		return getPositionY();

	float length = Math::sqrt(getPositionX() * getPositionX() + getPositionY() * getPositionY());
	float angle = root->getDirection()->getRadians() + atan2(getPositionX(), getPositionY());

	return root->getPositionY() + (cos(angle) * length);
}

float SceneObjectImplementation::getWorldPositionZ() {
	auto root = getRootParentUnsafe();

	if (root == nullptr || !root->isBuildingObject())
		return getPositionZ();

	return root->getPositionZ() + getPositionZ();
}

uint32 SceneObjectImplementation::getPlanetCRC() const {
	if (getZoneUnsafe() == nullptr)
		return 0;

	return getZoneUnsafe()->getZoneCRC();
}

void SceneObjectImplementation::createChildObjects() {
	if (getZoneUnsafe() == nullptr)
		return;

	ZoneServer* zoneServer = getZoneUnsafe()->getZoneServer();
	bool client = isClientObject();

	for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
		const auto child = templateObject->getChildObject(i);

		if (child == nullptr)
			continue;

		ManagedReference<SceneObject*> obj = nullptr;

		if (client)
			obj = zoneServer->createObject(child->getTemplateFile().hashCode(), "clientobjects", getPersistenceLevel());
		else
			obj = zoneServer->createObject(child->getTemplateFile().hashCode(), getPersistenceLevel());

		if (obj == nullptr)
			continue;

		Locker objLocker(obj, asSceneObject());

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

					if (cellObject != nullptr) {
						if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
							obj->destroyObjectFromDatabase(true);
							continue;
						}
						//cellObject->broadcastObject(obj, false);
					} else {
						error("nullptr CELL OBJECT");
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

			if (obj->isBuildingObject()) {
				BuildingObject* building = obj->asBuildingObject();

				if (building != nullptr) {
					building->createCellObjects();
				}
			}

			if (!getZoneUnsafe()->transferObject(obj, -1, true)) {
				obj->destroyObjectFromDatabase(true);
				continue;
			}
		}

		//childObjects.put(obj);
		ContainerPermissions* permissions = obj->getContainerPermissionsForUpdate();
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

		if (child == nullptr)
			continue;

		Locker clocker(child, asSceneObject());

		childObjects.drop(child);
		child->destroyObjectFromDatabase(true);
		child->destroyObjectFromWorld(true);
	}
}

bool SceneObjectImplementation::isFacingObject(SceneObject* obj) const {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float dx = targetPos.getX() - thisPos.getX();
	float dy = targetPos.getY() - thisPos.getY();
	float directionAngle = atan2(dy, dx);

	directionAngle = M_PI / 2 - directionAngle;

	if (directionAngle < 0) {
		float a = M_PI + directionAngle;
		directionAngle = M_PI + a;
	}

	return fabs(directionAngle - direction.getRadians()) < (M_PI / 2);
}

void SceneObjectImplementation::faceObject(SceneObject* obj, bool notifyClient) {
	Vector3 thisPos = getPosition();
	Vector3 targetPos = obj->getPosition();

	float dx = targetPos.getX() - thisPos.getX();
	float dy = targetPos.getY() - thisPos.getY();
	float directionAngle = atan2(dy, dx);

	directionAngle = M_PI / 2 - directionAngle;

	if (directionAngle < 0) {
		float a = M_PI + directionAngle;
		directionAngle = M_PI + a;
	}

	float error = fabs(directionAngle - direction.getRadians());

	if (error < 0.05) {
		debug() << "Direction below error - not updating " << directionAngle;
		return;
	}

	// info("Error Value = " + String::valueOf(error), true);
	// info("Setting New Direction angle = " + String::valueOf(directionAngle), true);

	if (notifyClient) {
		if (isAiAgent()) {
			setDirection(directionAngle);
			asAiAgent()->broadcastNextPositionUpdate(nullptr);
		} else {
			updateDirection(directionAngle);
		}
	} else {
		direction.setHeadingDirection(directionAngle);
	}
}

void SceneObjectImplementation::getContainerObjects(VectorMap<uint64, ManagedReference<SceneObject*> >& objects) {
	ReadLocker locker(&containerLock);

	if (containerObjects.isLoaded(false)) {
		objects = *containerObjects.getContainerObjects();
	} else {
		locker.release();

		Locker writeLocker(&containerLock);

		objects = *containerObjects.getContainerObjects();
	}
}

void SceneObjectImplementation::getSlottedObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	ReadLocker locker(&containerLock);

	objects = slottedObjects;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(const String& slot) {
	Reference<SceneObject*> obj;

	ReadLocker locker(&containerLock);

	obj = slottedObjects.get(slot);

	return obj;
}

Reference<SceneObject*> SceneObjectImplementation::getSlottedObject(int idx) {
	Reference<SceneObject*> obj;

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

	if (zone == nullptr)
		updateSavedRootParentRecursive(nullptr);
	else
		updateSavedRootParentRecursive(asSceneObject());
}

void SceneObjectImplementation::showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue, bool isPrivate) {

	if (!isPrivate) {
		ShowFlyText* fly = new ShowFlyText(asSceneObject(), file, aux, red, green, blue, 1.0f);
		broadcastMessage(fly, true);
	} else {
		ShowFlyText* fly = new ShowFlyText(asSceneObject(), file, aux, red, green, blue, 0);
		sendMessage(fly);
	}
}

void SceneObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
}

void SceneObjectImplementation::setParent(QuadTreeEntry* entry) {
	Locker locker(&parentLock);

	savedRootParent = nullptr;

	QuadTreeEntryImplementation::setParent(entry);

	locker.release();

	updateSavedRootParentRecursive(getRootParent());
}

void SceneObjectImplementation::setParent(QuadTreeEntry* entry, bool updateRecursively) {
	if (updateRecursively) {
		setParent(entry);
	} else {
		Locker locker(&parentLock);

		QuadTreeEntryImplementation::setParent(entry);
	}
}

ManagedWeakReference<SceneObject*> SceneObjectImplementation::getParent() {
	/*Locker locker(&parentLock);

	ManagedReference<QuadTreeEntry*> parent = this->parent.get();

	if (parent == nullptr)
		return nullptr;

	assert(parent != asSceneObject());*/

	return this->parent.staticCastToWeak<SceneObject*>();
}

SortedVector<ManagedReference<Observer* > > SceneObjectImplementation::getObservers(unsigned int eventType) const {
	return observerEventMap.getObservers(eventType);
}

bool SceneObjectImplementation::isInWater() const {
	auto zone = getZoneUnsafe();

	if (zone == nullptr) {
		error("Zone is nullptr SceneObjectImplementation::isInWater");
		return false;
	}

	auto planetManager = zone->getPlanetManager();

	if (planetManager == nullptr) {
		error("Unable to get PlanetManager SceneObjectImplementation::isInWater");
		return false;
	}

	return planetManager->isInWater(getPositionX(), getPositionY());
}

bool SceneObjectImplementation::containsNoTradeObjectRecursive() {
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

String SceneObjectImplementation::getDisplayedName() const {
	if (!customName.isEmpty())
		return customName.toString();

	return StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
}

bool SceneObjectImplementation::setTransformForCollisionMatrixIfNull(Matrix4* mat) {
	return transformForCollisionMatrix.compareAndSet(nullptr, mat);
}

int SceneObjectImplementation::getCountableObjectsRecursive() {
	int count = 0;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		if (obj != nullptr) {
			++count;

			count += obj->getCountableObjectsRecursive();
		}
	}

	return count;
}

int SceneObjectImplementation::getContainedObjectsRecursive() {
	int count = 0;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		++count;

		count += obj->getContainedObjectsRecursive();
	}

	return count;
}

int SceneObjectImplementation::getSizeOnVendorRecursive() {
	int count = 0;

	if (containerObjects.size() == 0)
		++count;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = containerObjects.get(i);

		count += obj->getSizeOnVendorRecursive();
	}

	return count;
}

bool SceneObjectImplementation::isDecoration() const {
	return (templateObject != nullptr &&
			(templateObject->getFullTemplateString().contains("object/tangible/furniture/city") ||
					templateObject->getFullTemplateString().contains("object/building/player/city/garden")));
}

Reference<SceneObject*> SceneObjectImplementation::getContainerObjectRecursive(uint64 oid) {
	Reference<SceneObject*> obj = containerObjects.get(oid);

	if (obj != nullptr)
		return obj;

	for (int i = 0; i < containerObjects.size(); ++i) {
		ManagedReference<SceneObject*> inContainerObject = containerObjects.get(i);

		obj = inContainerObject->getContainerObjectRecursive(oid);

		if (obj != nullptr)
			break;
	}

	return obj;
}

const Vector<String>* SceneObjectImplementation::getArrangementDescriptor(int idx) const {
	return &templateObject->getArrangementDescriptors().get(idx);
}

bool SceneObjectImplementation::hasObjectInSlottedContainer(SceneObject* object) {
	int arrangementSize = object->getArrangementDescriptorSize();

	if (arrangementSize == 0) {
		return false;
	}

	ManagedReference<SceneObject* > obj = nullptr;

	Locker _locker(&containerLock);

	for (int i = 0; i < arrangementSize; ++i) {
		const Vector<String>* descriptors = object->getArrangementDescriptor(i);

		for (int j = 0; j < descriptors->size(); ++j) {
			if (slottedObjects.get(descriptors->get(j)) != nullptr)
				return true;
		}
	}

	return false;
}

void SceneObjectImplementation::onContainerLoaded() {
	updateSavedRootParentRecursive(getRootParent());
}

Reference<SceneObject*> SceneObjectImplementation::getCraftedComponentsSatchel() {
	Reference<SceneObject*> sceno = asSceneObject();
	if (sceno == nullptr)
		return nullptr;

	Reference<ZoneServer*> zServer = getZoneServer();

	if(zServer == nullptr)
		return nullptr;

	ManagedReference<SceneObject*> craftingComponents = sceno->getSlottedObject("crafted_components");
	ManagedReference<SceneObject*> craftingComponentsSatchel = nullptr;


	if(craftingComponents == nullptr) {

		/// Add Components to crafted object
		String craftingComponentsPath = "object/tangible/crafting/crafting_components_container.iff";
		craftingComponents = zServer->createObject(craftingComponentsPath.hashCode(), 1);

		Locker componentsLocker(craftingComponents);

		craftingComponents->setSendToClient(false);
		sceno->transferObject(craftingComponents, 4, false);

		craftingComponents->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDefaultAllowPermission(0);
		craftingComponents->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDenyPermission("admin", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerAllowPermission("owner", 0);
		craftingComponents->setContainerAllowPermission("admin", 0);
		craftingComponents->setContainerInheritPermissionsFromParent(false);

		//String craftingComponentsSatchelPath = "object/tangible/container/base/base_container_volume.iff";
		String craftingComponentsSatchelPath = "object/tangible/hopper/crafting_station_hopper/crafting_station_ingredient_hopper_large.iff";
		craftingComponentsSatchel = zServer->createObject(craftingComponentsSatchelPath.hashCode(), 1);

		Locker satchelLocker(craftingComponentsSatchel, craftingComponents);

		craftingComponentsSatchel->setContainerInheritPermissionsFromParent(false);
		craftingComponentsSatchel->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerDefaultAllowPermission(0);
		craftingComponentsSatchel->setContainerAllowPermission("admin", ContainerPermissions::OPEN);
		craftingComponentsSatchel->setContainerDenyPermission("admin", ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerAllowPermission("owner", 0);
		craftingComponentsSatchel->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);

		craftingComponents->transferObject(craftingComponentsSatchel, -1, false);

	} else {
		craftingComponentsSatchel = craftingComponents->getContainerObject(0);
	}

	return std::move(craftingComponentsSatchel);
}

int SceneObjectImplementation::getArrangementDescriptorSize() const {
	return templateObject->getArrangementDescriptors().size();
}

bool SceneObjectImplementation::isDataPad() const {
	return templateObject->getFullTemplateString().contains("datapad");
}

float SceneObjectImplementation::getTemplateRadius() {
	if (templateObject == nullptr || templateObject->getAppearanceTemplate() == nullptr)
		return 0.f;

	MeshAppearanceTemplate* app = cast<MeshAppearanceTemplate*>(templateObject->getAppearanceTemplate());

	if (app == nullptr || app->getBoundingSphere() == nullptr)
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

bool SceneObjectImplementation::isPlayerCreature() {
	return false;
}

bool SceneObject::isPlayerCreature() {
	return false;
}

bool SceneObjectImplementation::isAiAgent() {
	return false;
}

bool SceneObject::isAiAgent() {
	return false;
}

bool SceneObjectImplementation::isVehicleObject() {
	return false;
}

bool SceneObject::isVehicleObject() {
	return false;
}

bool SceneObjectImplementation::isCreatureObject() {
	return false;
}

bool SceneObject::isCreatureObject() {
	return false;
}

bool SceneObjectImplementation::isBuildingObject() {
	return false;
}

bool SceneObject::isBuildingObject() {
	return false;
}

AiAgent* SceneObjectImplementation::asAiAgent() {
	return nullptr;
}

AiAgent* SceneObject::asAiAgent() {
	return nullptr;
}

SceneObject* SceneObjectImplementation::asSceneObject() {
	return _this.getReferenceUnsafeStaticCast();
}

SceneObject* SceneObject::asSceneObject() {
	return this;
}

CreatureObject* SceneObjectImplementation::asCreatureObject() {
	return nullptr;
}

CreatureObject* SceneObject::asCreatureObject() {
	return nullptr;
}

Vector<Reference<MeshData*> > SceneObjectImplementation::getTransformedMeshData(const Matrix4* parentTransform) const {
	const AppearanceTemplate *appearance = getObjectTemplate()->getAppearanceTemplate();
	if(appearance == nullptr) {
		Vector<Reference<MeshData*> > emptyData;
		return emptyData;
	}

	Quaternion directionRecast(direction.getW(), direction.getX(), direction.getY(), -direction.getZ());

	Matrix4 transform;
	transform.setRotationMatrix(directionRecast.toMatrix3());
	transform.setTranslation(getPositionX(), getPositionZ(), -getPositionY());

	const auto fullTransform = transform * *parentTransform;

	Vector<Reference<MeshData*>> data = appearance->getTransformedMeshData(fullTransform);

	FloorMesh *floor = TemplateManager::instance()->getFloorMesh(appearance->getFloorMesh());
	if (floor != nullptr)
		data.addAll(floor->getTransformedMeshData(fullTransform));

	return data;
}

const BaseBoundingVolume* SceneObjectImplementation::getBoundingVolume() {
	if (templateObject != nullptr) {
		AppearanceTemplate *appr = templateObject->getAppearanceTemplate();
		if (appr != nullptr) {
			return appr->getBoundingVolume();
		}
	}
	return nullptr;
}

void SceneObjectImplementation::executeOrderedTask(const StdFunction& function, const String& name) {
	auto taskObject = new LambdaTask(function, name.toCharArray());
	executeOrderedTask(taskObject);
}

bool SceneObjectImplementation::isInNavMesh() {
	Zone* zone = getZone();

	if (zone == nullptr)
		return false;

	SortedVector<ManagedReference<NavArea*> > areas;
	int ret = zone->getInRangeNavMeshes(getWorldPositionX(), getWorldPositionY(), &areas, false);

	return ret > 0;
}

int SceneObject::compareTo(SceneObject* obj) {
	if (getObjectID() < obj->getObjectID())
		return 1;
	else if (getObjectID() > obj->getObjectID())
		return -1;
	else
		return 0;
}

int SceneObjectImplementation::compareTo(SceneObject* obj) {
	return asSceneObject()->compareTo(obj);
}

int SceneObjectImplementation::writeRecursiveJSON(JSONSerializationType& j, int maxDepth, bool pruneCreo, bool pruneCraftedComponents, Vector<uint64>* oidPath) {
	if (maxDepth <= 0)
		return 0;

	if (oidPath == nullptr)
		oidPath = new Vector<uint64>();

	int count = 0;

	Locker lock(asSceneObject());

	JSONSerializationType thisObject;
	writeJSON(thisObject);
	thisObject["_maxDepth"] = maxDepth;
	thisObject["_depth"] = oidPath->size();
	thisObject["_oid"] = getObjectID();
	thisObject["_className"] = _className;
	thisObject["_observerCount"] = observerEventMap.getFullObserverCount();
	thisObject["_templateObject"] = templateObject ? templateObject->getFullTemplateString() : "null";

	oidPath->add(getObjectID());

	auto childObjects = *getChildObjects(); // Get a copy before we release the lock
	auto craftingComponents = getSlottedObject("crafted_components");

	lock.release();

	auto oidPathJSON = JSONSerializationType::array();

	for (int i = 0;i < oidPath->size();i++) {
		oidPathJSON.push_back(oidPath->get(i));
	}

	thisObject["_oidPath"] = oidPathJSON;

	j[String::valueOf(getObjectID()).toCharArray()] = thisObject;

	count++;

	if (pruneCreo && isCreatureObject()) {
		return count;
	}

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		auto obj = getContainerObject(i);

		if (obj != nullptr) {
			count += obj->writeRecursiveJSON(j, maxDepth - 1, pruneCreo, pruneCraftedComponents, oidPath);
		}
	}

	for (int i = 0;i < childObjects.size(); ++i) {
		auto obj = childObjects.get(i);

		if (obj != nullptr) {
			count += obj->writeRecursiveJSON(j, maxDepth - 1, pruneCreo, pruneCraftedComponents, oidPath);
		}
	}

	for (int i = 0;i < getSlottedObjectsSize(); ++i) {
		auto obj =  getSlottedObject(i);

		if (obj != nullptr) {
			if (pruneCraftedComponents && obj == craftingComponents) {
				continue;
			}

			count += obj->writeRecursiveJSON(j, maxDepth - 1, pruneCreo, pruneCraftedComponents, oidPath);
		}
	}

	oidPath->remove(oidPath->size() - 1);

	if (oidPath->size() == 0) {
		delete oidPath;
	}

	return count;
}

String SceneObjectImplementation::exportJSON(const String& exportNote, int maxDepth, bool pruneCreo, bool pruneCraftedComponents) {
	static AtomicInteger sequence;

	Time startTime;
	uint64 oid = getObjectID();

	// Collect object and all children to maxDepth
	nlohmann::json exportedObjects = nlohmann::json::object();

	if (maxDepth <= 0)
		maxDepth = 1000;

	int count = 0;

	try {
		count = writeRecursiveJSON(exportedObjects, maxDepth, pruneCreo, pruneCraftedComponents);
	} catch (Exception& e) {
		error() << "SceneObjectImplementation::writeRecursiveJSON(): failed:" << e.getMessage();
	}

	// Metadata
	nlohmann::json metaData = nlohmann::json::object();
	metaData["exportTime"] = startTime.getFormattedTimeFull();
	metaData["exportNote"] = exportNote;
	metaData["rootObjectID"] = oid;
	metaData["rootObjectClassName"] = _className;
	metaData["objectCount"] = count;
	metaData["maxDepth"] = maxDepth;
	metaData["msExport"] = startTime.miliDifference();

	if (pruneCreo) {
		metaData["pruneCreatures"] = true;
	}

	if (pruneCraftedComponents) {
		metaData["pruneCraftedComponents"] = true;
	}

	// Root object is meta "exportObject"
	nlohmann::json exportObject;
	exportObject["metadata"] = metaData;
	exportObject["objects"] = exportedObjects;

	auto exportBasedir = ConfigManager::instance()->getString("Core3.SceneObject.exportDir", "log/exports/%Y-%m-%d/%H/");

	// Save to file...
	Time now;
	StringBuffer fileNameBuf;

	fileNameBuf << now.getFormattedTime(exportBasedir) << oid << "/";

	String dirName = fileNameBuf.toString();

	if (File::directorySeparator() != '/') {
		dirName.replaceAll("/", String().concat(File::directorySeparator()));
	}

	File::mkpath(dirName, 0755);

	fileNameBuf << oid << "-" << now.getMiliTime() << "-" << sequence.increment() << ".json";

	String fileName = fileNameBuf.toString();
	std::ofstream jsonFile(fileName.toCharArray());
	jsonFile << std::setw(4) << exportObject << std::endl;
	jsonFile.close();

	return fileName;
}

void SceneObjectImplementation::getChildrenRecursive(SortedVector<uint64>& childObjectsFound, int maxDepth, bool pruneCreo, bool pruneCraftedComponents) {
	if (maxDepth <= 0)
		return;

	Locker lock(asSceneObject());

	if (pruneCreo && isCreatureObject()) {
		return;
	}

	auto childObjects = *getChildObjects(); // Get a copy before we release the lock
	auto craftingComponents = getSlottedObject("crafted_components");

	lock.release();

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		auto obj = getContainerObject(i);

		if (obj != nullptr) {
			childObjectsFound.put(obj->getObjectID());
			obj->getChildrenRecursive(childObjectsFound, maxDepth - 1, pruneCreo, pruneCraftedComponents);
		}
	}

	for (int i = 0;i < childObjects.size(); ++i) {
		auto obj = childObjects.get(i);

		if (obj != nullptr) {
			childObjectsFound.put(obj->getObjectID());
			obj->getChildrenRecursive(childObjectsFound, maxDepth - 1, pruneCreo, pruneCraftedComponents);
		}
	}

	for (int i = 0;i < getSlottedObjectsSize(); ++i) {
		auto obj =  getSlottedObject(i);

		if (obj != nullptr) {
			if (pruneCraftedComponents && obj == craftingComponents) {
				continue;
			}

			childObjectsFound.put(obj->getObjectID());
			obj->getChildrenRecursive(childObjectsFound, maxDepth - 1, pruneCreo, pruneCraftedComponents);
		}
	}
}

String SceneObjectImplementation::getGameObjectTypeStringID() {
	return SceneObjectType::typeToString(gameObjectType);
}
