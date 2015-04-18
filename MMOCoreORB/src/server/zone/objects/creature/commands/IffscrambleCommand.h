/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef IFFSCRAMBLE_H_
#define IFFSCRAMBLE_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class IffscrambleCommand : public CombatQueueCommand {
public:

	IffscrambleCommand(const String& name, ZoneProcessServer* server)
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

#endif //IFFSCRAMBLE_H_
