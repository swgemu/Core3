/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POLEARMLUNGE1COMMAND_H_
#define POLEARMLUNGE1COMMAND_H_

#include "CombatQueueCommand.h"

class PolearmLunge1Command : public CombatQueueCommand {
public:

	PolearmLunge1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS)
			creature->notifyObservers(ObserverEventType::ABILITYUSED, nullptr, STRING_HASHCODE("polearmlunge1"));

		return result;
	}

};

#endif //POLEARMLUNGE1COMMAND_H_
