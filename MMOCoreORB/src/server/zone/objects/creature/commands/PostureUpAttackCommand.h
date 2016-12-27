/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POSTUREUPATTACKCOMMAND_H_
#define POSTUREUPATTACKCOMMAND_H_

#include "CombatQueueCommand.h"

class PostureUpAttackCommand : public CombatQueueCommand {
public:

	PostureUpAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isAiAgent())
			return GENERALERROR;

		return doCombatAction(creature, target, arguments);
	}

};

#endif //POSTUREUPATTACKCOMMAND_H_
