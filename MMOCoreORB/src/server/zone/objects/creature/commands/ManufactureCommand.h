/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MANUFACTURECOMMAND_H_
#define MANUFACTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ManufactureCommand : public QueueCommand {
public:

	ManufactureCommand(const String& name, ZoneProcessServer* server)
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

#endif //MANUFACTURECOMMAND_H_
