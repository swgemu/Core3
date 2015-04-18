/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATTARGETCOMMAND_H_
#define COMBATTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CombatTargetCommand : public QueueCommand {
public:

	CombatTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //COMBATTARGETCOMMAND_H_
