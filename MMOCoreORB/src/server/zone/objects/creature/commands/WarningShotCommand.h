/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WARNINGSHOTCOMMAND_H_
#define WARNINGSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class WarningShotCommand : public CombatQueueCommand {
public:

	WarningShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //WARNINGSHOTCOMMAND_H_
