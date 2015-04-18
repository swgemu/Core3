/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MULTITARGETSHOTCOMMAND_H_
#define MULTITARGETSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MultiTargetShotCommand : public CombatQueueCommand {
public:

	MultiTargetShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //MULTITARGETSHOTCOMMAND_H_
