/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DIZZYATTACKCOMMAND_H_
#define DIZZYATTACKCOMMAND_H_

#include "CombatQueueCommand.h"

class DizzyAttackCommand : public CombatQueueCommand {
public:

	DizzyAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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

#endif //DIZZYATTACKCOMMAND_H_
