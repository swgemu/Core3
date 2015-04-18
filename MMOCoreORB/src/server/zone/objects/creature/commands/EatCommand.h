/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EATCOMMAND_H_
#define EATCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EatCommand : public QueueCommand {
public:

	EatCommand(const String& name, ZoneProcessServer* server)
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

#endif //EATCOMMAND_H_
