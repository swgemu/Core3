/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POINTBLANKSINGLE1COMMAND_H_
#define POINTBLANKSINGLE1COMMAND_H_

#include "CombatQueueCommand.h"

class PointBlankSingle1Command : public CombatQueueCommand {
public:

	PointBlankSingle1Command(const String& name, ZoneProcessServer* server)
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

#endif //POINTBLANKSINGLE1COMMAND_H_
