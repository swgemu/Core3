/*
 * StrongDiseaseCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef STRONGDISEASECOMMAND_H_
#define STRONGDISEASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class StrongDiseaseCommand : public CombatQueueCommand {
public:

	StrongDiseaseCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 50;
		dotType = CreatureState::DISEASED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 80;
		dotPotency = 100;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* STRONGDISEASECOMMAND_H_ */
