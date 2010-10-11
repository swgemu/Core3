/*
 * MildPoisonCommand.h
 *
 *  Created on: Oct 9, 2010
 *      Author: da
 */

#ifndef MILDPOISONCOMMAND_H_
#define MILDPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class MildPoisonCommand : public CombatQueueCommand {
public:

	MildPoisonCommand(const String& name, ZoneProcessServerImplementation* server)
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


#endif /* MILDPOISONCOMMAND_H_ */
