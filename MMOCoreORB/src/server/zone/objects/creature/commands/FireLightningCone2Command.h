/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIRELIGHTNINGCONE2COMMAND_H_
#define FIRELIGHTNINGCONE2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class FireLightningCone2Command : public CombatQueueCommand {
public:

	FireLightningCone2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isLightningRifle()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //FIRELIGHTNINGCONE2COMMAND_H_
