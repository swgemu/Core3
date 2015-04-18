/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERPOLEARMHIT2COMMAND_H_
#define SABERPOLEARMHIT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SaberPolearmHit2Command : public CombatQueueCommand {
public:

	SaberPolearmHit2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();


		if (!weapon->isJediPolearmWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //SABERPOLEARMHIT2COMMAND_H_
