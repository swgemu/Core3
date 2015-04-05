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

#endif /* MEDIUMPOISONCOMMAND_H_ */
