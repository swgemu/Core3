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
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isAiAgent())
			return GENERALERROR;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* MILDDISEASECOMMAND_H_ */
