/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MAXCOMBATABILITYCOMMAND_H_
#define MAXCOMBATABILITYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MaxCombatAbilityCommand : public QueueCommand {
public:

	MaxCombatAbilityCommand(const String& name, ZoneProcessServer* server)
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

#endif //MAXCOMBATABILITYCOMMAND_H_
