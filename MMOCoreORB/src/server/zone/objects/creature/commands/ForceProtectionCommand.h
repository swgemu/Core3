/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEPROTECTIONCOMMAND_H_
#define FORCEPROTECTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceProtectionCommand : public QueueCommand {
public:

	ForceProtectionCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEPROTECTIONCOMMAND_H_
