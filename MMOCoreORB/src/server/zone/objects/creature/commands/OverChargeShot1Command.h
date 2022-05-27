/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OVERCHARGESHOT1COMMAND_H_
#define OVERCHARGESHOT1COMMAND_H_

#include "CombatQueueCommand.h"

class OverChargeShot1Command : public CombatQueueCommand {
public:

	OverChargeShot1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS)
			creature->notifyObservers(ObserverEventType::ABILITYUSED, nullptr, STRING_HASHCODE("overchargeshot1"));

		return result;
	}

};

#endif //OVERCHARGESHOT1COMMAND_H_
