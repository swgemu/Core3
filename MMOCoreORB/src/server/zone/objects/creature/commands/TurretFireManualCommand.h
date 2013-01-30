/*
 * TurretFireManualCommand.h
 *
 *  Created on: Jan 27, 2013
 *      Author: root
 */

#ifndef TURRETFIREMANUALCOMMAND_H_
#define TURRETFIREMANUALCOMMAND_H_
#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"


class TurretFireManualCommand : public CombatQueueCommand {
public:

	TurretFireManualCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};





#endif /* TURRETFIREMANUALCOMMAND_H_ */
