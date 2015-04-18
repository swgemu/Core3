/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATENPCCOMMAND_H_
#define CREATENPCCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreateNPCCommand : public QueueCommand {
public:

	CreateNPCCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //CREATENPCCOMMAND_H_
