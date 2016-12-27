/*
 * MediumDiseaseCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MEDIUMDISEASECOMMAND_H_
#define MEDIUMDISEASECOMMAND_H_

#include "CombatQueueCommand.h"

class MediumDiseaseCommand : public CombatQueueCommand {
public:

	MediumDiseaseCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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

#endif /* MEDIUMDISEASECOMMAND_H_ */
