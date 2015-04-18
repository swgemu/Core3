/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATMODECHECKCOMMAND_H_
#define COMBATMODECHECKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CombatModeCheckCommand : public QueueCommand {
public:

	CombatModeCheckCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //COMBATMODECHECKCOMMAND_H_
