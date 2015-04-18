/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEADSHOT3COMMAND_H_
#define HEADSHOT3COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class HeadShot3Command : public CombatQueueCommand {
public:

	HeadShot3Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isRifleWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //HEADSHOT3COMMAND_H_
