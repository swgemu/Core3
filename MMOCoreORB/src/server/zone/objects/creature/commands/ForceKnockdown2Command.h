/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEKNOCKDOWN2COMMAND_H_
#define FORCEKNOCKDOWN2COMMAND_H_

#include "ForcePowersQueueCommand.h"

class ForceKnockdown2Command : public ForcePowersQueueCommand {
public:

	ForceKnockdown2Command(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		return doCombatAction(creature, target);
	}

};

#endif //FORCEKNOCKDOWN2COMMAND_H_
