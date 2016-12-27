/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSPACERELOAD_H_
#define INSPACERELOAD_H_

#include "CombatQueueCommand.h"

class InspacereloadCommand : public CombatQueueCommand {
public:

	InspacereloadCommand(const String& name, ZoneProcessServer* server)
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

#endif //INSPACERELOAD_H_
