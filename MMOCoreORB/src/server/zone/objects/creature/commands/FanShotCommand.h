/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FANSHOTCOMMAND_H_
#define FANSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class FanShotCommand : public CombatQueueCommand {
public:

	FanShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //FANSHOTCOMMAND_H_
