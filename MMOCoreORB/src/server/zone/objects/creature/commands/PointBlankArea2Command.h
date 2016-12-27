/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POINTBLANKAREA2COMMAND_H_
#define POINTBLANKAREA2COMMAND_H_

#include "CombatQueueCommand.h"

class PointBlankArea2Command : public CombatQueueCommand {
public:

	PointBlankArea2Command(const String& name, ZoneProcessServer* server)
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

#endif //POINTBLANKAREA2COMMAND_H_
