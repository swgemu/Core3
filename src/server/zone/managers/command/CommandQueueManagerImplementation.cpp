/*
 * CommandQueueManagerImplementation.cpp
 *
 *  Created on: 29/07/2009
 *      Author: victor
 */

#include "CommandQueueManager.h"
#include "CommandList.h"
#include "CommandConfigManager.h"

CommandQueueManagerImplementation::CommandQueueManagerImplementation(ZoneProcessServerImplementation* serv)
	: ManagedObjectImplementation() {

	server = serv;
	configManager = new CommandConfigManager(server);
	slashCommands = new CommandList();
	configManager->loadSlashCommandsFile(slashCommands);
}

/*CommandQueueManagerImplementation::~CommandQueueManagerImplementation() {
	delete configManager;

	slashCommands->resetIterator();

	while (slashCommands->hasNext())
		delete slashCommands->getNextValue();
}*/

void CommandQueueManagerImplementation::addQueueCommand(QueueCommand* command) {
	slashCommands->put(command);
}

QueueCommand* CommandQueueManagerImplementation::getQueueCommand(const String& name) {
	return slashCommands->getSlashCommand(name);
}

QueueCommand* CommandQueueManagerImplementation::getQueueCommand(uint32 crc) {
	return slashCommands->getSlashCommand(crc);
}
