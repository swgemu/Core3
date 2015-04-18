/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERITEMCOMMAND_H_
#define TRANSFERITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TransferItemCommand : public QueueCommand {
public:

	TransferItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->info("transfer item command");
		return SUCCESS;
	}

};

#endif //TRANSFERITEMCOMMAND_H_
