/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEATHCOUNTCOMMAND_H_
#define DEATHCOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DeathCountCommand : public QueueCommand {
public:

	DeathCountCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEATHCOUNTCOMMAND_H_
