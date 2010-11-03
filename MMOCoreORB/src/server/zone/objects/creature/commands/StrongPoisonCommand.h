/*
 * StrongPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef STRONGPOISONCOMMAND_H_
#define STRONGPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class StrongPoisonCommand : public CombatQueueCommand {
public:

	StrongPoisonCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 20;
		dotType = CreatureState::DISEASED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 80;
		dotPotency = 80;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* STRONGPOISONCOMMAND_H_ */
