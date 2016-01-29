/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECHOKECOMMAND_H_
#define FORCECHOKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceChokeCommand : public ForcePowersQueueCommand {
public:

	ForceChokeCommand(const String& name, ZoneProcessServer* server)
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

		// Each tick's damage should be random amount in between 100-500 ??
		int damage = System::random(10);
		int tickDamage = 100 + (damage * 40);

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			targetObject->playEffect("clienteffect/pl_force_choke.cef", "");
			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget != NULL) {

				Locker crossLocker(creature, creatureTarget);

				if (creatureTarget->hasAttackDelay())
					creatureTarget->removeAttackDelay();

				ManagedReference<Buff*> choke = new Buff(creatureTarget, getNameCRC(), 30, BuffType::STATE);

				Locker locker(choke);

				choke->applyStates();
				creatureTarget->inflictDamage(creature, CreatureAttribute::HEALTH, tickDamage, true);
				creatureTarget->addCooldown("forceChoke", 5000);

				if (creatureTarget->hasBuff(STRING_HASHCODE("forceChoke"))) {
					return 0;
				} else {
					creatureTarget->addBuff(choke);
					creatureTarget->sendSystemMessage("@combat_effects:choke_single"); // You are choking!
				}

			}

		}

		return res;

	}

};

#endif //FORCECHOKECOMMAND_H_
