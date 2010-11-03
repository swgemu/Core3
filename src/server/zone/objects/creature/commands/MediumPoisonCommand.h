/*
 * MediumPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MEDIUMPOISONCOMMAND_H_
#define MEDIUMPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class MediumPoisonCommand : public CombatQueueCommand {
public:

	MediumPoisonCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 10;
		dotType = CreatureState::POISONED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 50;
		dotPotency = 50;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* MEDIUMPOISONCOMMAND_H_ */
