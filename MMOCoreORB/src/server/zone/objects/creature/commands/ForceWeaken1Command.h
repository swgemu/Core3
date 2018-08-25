/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEWEAKEN1COMMAND_H_
#define FORCEWEAKEN1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/buffs/ForceWeakenDebuff.h"

class ForceWeaken1Command : public ForcePowersQueueCommand {
public:

	ForceWeaken1Command(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		CreatureObject* creatureTarget = targetObject.castTo<CreatureObject*>();

		if (creatureTarget->hasBuff(STRING_HASHCODE("forceweaken1")) || creatureTarget->hasBuff(STRING_HASHCODE("forceweaken2"))) {
			return ALREADYAFFECTEDJEDIPOWER;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			Locker clocker(creatureTarget, creature);

			ManagedReference<Buff*> buff = new ForceWeakenDebuff(creatureTarget, getNameCRC(), 300, 500, 90);

			Locker locker(buff);

			creatureTarget->addBuff(buff);

			CombatManager::instance()->broadcastCombatSpam(creature, creatureTarget, NULL, 0, "cbt_spam", combatSpam + "_hit", 1);
		}

		return res;
	}

};

#endif //FORCEWEAKEN1COMMAND_H_
