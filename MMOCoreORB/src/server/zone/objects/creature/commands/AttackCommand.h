/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTACKCOMMAND_H_
#define ATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class AttackCommand : public CombatQueueCommand {
public:

	AttackCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int result = doCombatAction(creature, target);

		// evidence shows that this has a custom OOR message.
		if (result == TOOFAR) {
			creature->sendSystemMessage("@cbt_spam:out_of_range_single"); // That target is out of range.
			return GENERALERROR;
		}

		return result;
	}
};

#endif //ATTACKCOMMAND_H_
