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
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* MEDIUMDISEASECOMMAND_H_ */
