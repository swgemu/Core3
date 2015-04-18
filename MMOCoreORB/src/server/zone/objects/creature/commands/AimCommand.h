/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AIMCOMMAND_H_
#define AIMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class AimCommand : public CombatQueueCommand {
public:

	AimCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isRangedWeapon()) {
			return INVALIDWEAPON;
		}

		creature->setAimingState();

		//Send combat spam.
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		if (targetObject != NULL && targetObject->isTangibleObject() && creature != targetObject) {
			TangibleObject* defender = cast<TangibleObject*>( targetObject.get());
			CombatManager::instance()->broadcastCombatSpam(creature, defender, NULL, 0, "cbt_spam", combatSpam, 0);
		}

		return SUCCESS;
	}

};

#endif //AIMCOMMAND_H_
