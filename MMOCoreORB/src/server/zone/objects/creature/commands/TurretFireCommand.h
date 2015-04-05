/*
 * TurretFireCommand.h
 *
 *  Created on: Dec 21, 2012
 *      Author: root
 */

#ifndef TURRETFIRECOMMAND_H_
#define TURRETFIRECOMMAND_H_
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class TurretFireCommand : public CombatQueueCommand {
public:

	TurretFireCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return 0;
	}

};





#endif /* TURRETFIRECOMMAND_H_ */
