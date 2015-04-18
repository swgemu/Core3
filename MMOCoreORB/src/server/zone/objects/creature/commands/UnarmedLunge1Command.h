/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNARMEDLUNGE1COMMAND_H_
#define UNARMEDLUNGE1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"


class UnarmedLunge1Command : public CombatQueueCommand {
public:

	UnarmedLunge1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isUnarmedWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //UNARMEDLUNGE1COMMAND_H_
