/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECOMMANDCOMMAND_H_
#define FORCECOMMANDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceCommandCommand : public QueueCommand {
public:

	ForceCommandCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCECOMMANDCOMMAND_H_
