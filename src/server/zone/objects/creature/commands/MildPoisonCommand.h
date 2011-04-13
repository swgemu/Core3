/*
 * MildPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MILDPOISONCOMMAND_H_
#define MILDPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class MildPoisonCommand : public CombatQueueCommand {
public:

	MildPoisonCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 10;
		dotType = CreatureState::POISONED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 30;
		dotPotency = 30;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return doCombatAction(creature, target, arguments);
	}

};


#endif /* MILDPOISONCOMMAND_H_ */
