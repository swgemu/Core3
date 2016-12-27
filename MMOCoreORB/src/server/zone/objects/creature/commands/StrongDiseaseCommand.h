/*
 * StrongDiseaseCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef STRONGDISEASECOMMAND_H_
#define STRONGDISEASECOMMAND_H_

#include "CombatQueueCommand.h"

class StrongDiseaseCommand : public CombatQueueCommand {
public:

	StrongDiseaseCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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

#endif /* STRONGDISEASECOMMAND_H_ */
