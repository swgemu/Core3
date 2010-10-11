/*
 * StrongPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef STRONGPOISONCOMMAND_H_
#define STRONGPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class StrongPoisonCommand : public CombatQueueCommand {
public:

	StrongPoisonCommand(const String& name, ZoneProcessServerImplementation* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return doCombatAction(creature, target, arguments);
	}

};

#endif /* STRONGPOISONCOMMAND_H_ */
