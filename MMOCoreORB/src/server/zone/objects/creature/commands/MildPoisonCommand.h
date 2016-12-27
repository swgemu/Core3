/*
 * MildPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MILDPOISONCOMMAND_H_
#define MILDPOISONCOMMAND_H_

#include "CombatQueueCommand.h"

class MildPoisonCommand : public CombatQueueCommand {
public:

	MildPoisonCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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


#endif /* MILDPOISONCOMMAND_H_ */
