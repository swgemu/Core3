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

void ObjectControllerImplementation::addQueueCommand(QueueCommand* command) {
	queueCommands->put(command);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(const String& name) {
	return queueCommands->getSlashCommand(name);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(uint32 crc) {
	return queueCommands->getSlashCommand(crc);
}
