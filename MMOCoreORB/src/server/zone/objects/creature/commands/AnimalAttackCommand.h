/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALATTACKCOMMAND_H_
#define ANIMALATTACKCOMMAND_H_

#include "server/zone/objects/creature/commands/JediQueueCommand.h"

class AnimalAttackCommand : public JediQueueCommand {
public:

	AnimalAttackCommand(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //ANIMALATTACKCOMMAND_H_
