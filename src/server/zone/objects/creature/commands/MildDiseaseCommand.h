/*
 * MildDiseaseCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MILDDISEASECOMMAND_H_
#define MILDDISEASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class MildDiseaseCommand : public CombatQueueCommand {
public:

	MildDiseaseCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 10;
		dotType = CreatureState::DISEASED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 30;
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

#endif /* MILDDISEASECOMMAND_H_ */
