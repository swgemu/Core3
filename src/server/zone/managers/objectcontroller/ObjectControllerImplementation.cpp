/*
 * ObjectControllerImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "ObjectController.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/objectcontroller/command/CommandConfigManager.h"
#include "server/zone/managers/objectcontroller/command/CommandList.h"


ObjectControllerImplementation::ObjectControllerImplementation(ZoneProcessServerImplementation* server) : ManagedObjectImplementation() {
	setLoggingName("ObjectController");

	ObjectControllerImplementation::server = server;

	configManager = new CommandConfigManager(server);
	queueCommands = new CommandList();

	setLogging(true);
	setGlobalLogging(true);

	info("loading queue commands...", true);
	configManager->loadSlashCommandsFile(queueCommands);

	StringBuffer infoMsg;
	infoMsg << "loaded " << queueCommands->size() << " commands";
	info(infoMsg.toString(), true);
}

bool ObjectControllerImplementation::transferObject(SceneObject* objectToTransfer, SceneObject* destinationObject, int containmentType, bool notifyClient) {
	ManagedReference<SceneObject*> parent = objectToTransfer->getParent();

	if (parent == NULL) {
		error("objectToTransfer parent is NULL in ObjectManager::transferObject");
		return false;
	}

	uint32 oldContainmentType = objectToTransfer->getContainmentType();

	if (!parent->removeObject(objectToTransfer)) {
		error("could not remove objectToTransfer from parent in ObjectManager::transferObject");
		return false;
	}

	if (!destinationObject->addObject(objectToTransfer, containmentType, notifyClient)) {
		error("could not add objectToTransfer to destinationObject in ObjectManager::transferObject");
		parent->addObject(objectToTransfer, oldContainmentType);
		return false;
	}

	return true;
}

void ObjectControllerImplementation::addQueueCommand(QueueCommand* command) {
	queueCommands->put(command);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(const String& name) {
	return queueCommands->getSlashCommand(name);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(uint32 crc) {
	return queueCommands->getSlashCommand(crc);
}
