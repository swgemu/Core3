/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VREPAIROTHER_H_
#define VREPAIROTHER_H_

#include "CombatQueueCommand.h"

class VrepairotherCommand : public CombatQueueCommand {
public:

	VrepairotherCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //VREPAIROTHER_H_
