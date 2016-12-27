/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSPACETRAINER_H_
#define REQUESTSPACETRAINER_H_

#include "CombatQueueCommand.h"

class RequestSpaceTrainerCommand : public CombatQueueCommand {
public:

	RequestSpaceTrainerCommand(const String& name, ZoneProcessServer* server)
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

#endif //REQUESTSPACETRAINER_H_
