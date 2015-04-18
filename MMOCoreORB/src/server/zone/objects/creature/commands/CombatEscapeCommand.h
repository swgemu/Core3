/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATESCAPECOMMAND_H_
#define COMBATESCAPECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CombatEscapeCommand : public QueueCommand {
public:

	CombatEscapeCommand(const String& name, ZoneProcessServer* server)
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

#endif //COMBATESCAPECOMMAND_H_
