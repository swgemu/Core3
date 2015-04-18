/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETOWNERCOMMAND_H_
#define SETOWNERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetOwnerCommand : public QueueCommand {
public:

	SetOwnerCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETOWNERCOMMAND_H_
