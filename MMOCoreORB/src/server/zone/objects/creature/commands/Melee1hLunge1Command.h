/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MELEE1HLUNGE1COMMAND_H_
#define MELEE1HLUNGE1COMMAND_H_

#include "CombatQueueCommand.h"

class Melee1hLunge1Command : public CombatQueueCommand {
public:

	Melee1hLunge1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS)
			creature->notifyObservers(ObserverEventType::ABILITYUSED, nullptr, STRING_HASHCODE("melee1hlunge1"));

		return result;
	}


};

#endif //MELEE1HLUNGE1COMMAND_H_
