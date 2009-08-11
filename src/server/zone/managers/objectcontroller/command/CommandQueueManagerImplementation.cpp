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
	: ManagedObjectImplementation(), Logger("CommandQueueManager") {

	server = serv;
	configManager = new CommandConfigManager(server);
	slashCommands = new CommandList();

	setLogging(true);
	setGlobalLogging(true);

	info("loading queue commands...", true);
	configManager->loadSlashCommandsFile(slashCommands);

	StringBuffer infoMsg;
	infoMsg << "loaded " << slashCommands->size() << " commands";
	info(infoMsg.toString(), true);
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
