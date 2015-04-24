/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PANICSHOTCOMMAND_H_
#define PANICSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class PanicShotCommand : public CombatQueueCommand {
public:

	PanicShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //PANICSHOTCOMMAND_H_
