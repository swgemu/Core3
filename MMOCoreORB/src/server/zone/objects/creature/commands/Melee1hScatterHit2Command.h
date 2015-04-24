/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MELEE1HSCATTERHIT2COMMAND_H_
#define MELEE1HSCATTERHIT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"


class Melee1hScatterHit2Command : public CombatQueueCommand {
public:

	Melee1hScatterHit2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;
		
		float mods[3] = {0.f, 0.f, 0.f};
		
		for (int i = 0; i < 3; i++)
			mods[System::random(2)] += 0.34f;
			
		UnicodeString args = "healthDamageMultiplier=" + String::valueOf(mods[0]) + ";actionDamageMultiplier=" + String::valueOf(mods[1]) + ";mindDamageMultiplier=" + String::valueOf(mods[2]) + ";";

		return doCombatAction(creature, target, args);
	}

};

#endif //MELEE1HSCATTERHIT2COMMAND_H_
