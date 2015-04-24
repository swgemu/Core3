/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONFUSIONSHOTCOMMAND_H_
#define CONFUSIONSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class ConfusionShotCommand : public CombatQueueCommand {
public:

	ConfusionShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //CONFUSIONSHOTCOMMAND_H_
