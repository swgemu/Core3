/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDLIST_H_
#define COMMANDLIST_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

namespace server {
namespace zone {
namespace managers {
namespace objectcontroller {
namespace command {


class CommandList : public Logger, public Object {
	HashTable<uint32, Reference<QueueCommand*> > commands;

public:
	CommandList() : commands(700) {
		setLoggingName("CommandList");

		setGlobalLogging(true);
		setLogging(false);
	}

	void put(QueueCommand* value) {
		uint32 crc = value->getNameCRC();

		StringBuffer infoMsg;
		infoMsg << "adding queueCommand 0x" << hex << crc << " " << value->getQueueCommandName();
		info(infoMsg);

		commands.put(crc, value);
	}

	void put(const String& name, QueueCommand* value) {
		uint32 crc = name.hashCode();

		StringBuffer infoMsg;
		infoMsg << "adding queueCommand 0x" << hex << crc << " " << name;
		info(infoMsg);

		commands.put(crc, value);
	}

	QueueCommand* getSlashCommand(const String& aname) {
		uint32 crc = aname.hashCode();

		return commands.get(crc);
	}

	QueueCommand* getSlashCommand(uint32 crc) {
		return commands.get(crc);
	}

	HashTableIterator<uint32, Reference<QueueCommand*> > iterator() {
		return commands.iterator();
	}

	int size() {
		return commands.size();
	}
};


}
}
}
}
}

using namespace server::zone::managers::objectcontroller::command;

#endif /*SLASHCOMMANDLIST_H_*/
