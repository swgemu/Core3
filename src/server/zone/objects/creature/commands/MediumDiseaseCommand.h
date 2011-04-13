/*
 * MediumDiseaseCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MEDIUMDISEASECOMMAND_H_
#define MEDIUMDISEASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class MediumDiseaseCommand : public CombatQueueCommand {
public:

	MediumDiseaseCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		dotDuration = 30;
		dotType = CreatureState::DISEASED;
		dotPool = CombatManager::HEALTH;
		dotStrength = 50;
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

#endif /* MEDIUMDISEASECOMMAND_H_ */
