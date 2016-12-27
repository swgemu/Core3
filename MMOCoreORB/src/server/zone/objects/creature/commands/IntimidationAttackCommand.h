/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTIMIDATIONATTACKCOMMAND_H_
#define INTIMIDATIONATTACKCOMMAND_H_

#include "CombatQueueCommand.h"

class IntimidationAttackCommand : public CombatQueueCommand {
public:

	IntimidationAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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

#endif //INTIMIDATIONATTACKCOMMAND_H_
