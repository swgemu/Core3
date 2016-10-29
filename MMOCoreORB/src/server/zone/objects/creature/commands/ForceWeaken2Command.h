/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEWEAKEN2COMMAND_H_
#define FORCEWEAKEN2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceWeaken2Command : public ForcePowersQueueCommand {
public:

	ForceWeaken2Command(const String& name, ZoneProcessServer* server)
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

		ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();
		if (creatureTarget->hasBuff(STRING_HASHCODE("forceweaken1"))) {
			return NOSTACKJEDIBUFF;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Setup debuff.

			if (creatureTarget != NULL) {
				Locker clocker(creatureTarget, creature);

				ManagedReference<Buff*> buff = new Buff(creatureTarget, getNameCRC(), 120, BuffType::JEDI);

				int currentHealth = creatureTarget->getHAM(CreatureAttribute::HEALTH);
				int currentAction = creatureTarget->getHAM(CreatureAttribute::ACTION);
				int currentMind = creatureTarget->getHAM(CreatureAttribute::MIND);

				Locker locker(buff);

				if (currentHealth > 25000) {
					int currentStr = creatureTarget->getHAM(CreatureAttribute::STRENGTH);
					int currentCon = creatureTarget->getHAM(CreatureAttribute::CONSTITUTION);
					int currentQui = creatureTarget->getHAM(CreatureAttribute::QUICKNESS);
					int currentStam = creatureTarget->getHAM(CreatureAttribute::STAMINA);
					int currentFoc = creatureTarget->getHAM(CreatureAttribute::FOCUS);
					int currentWill = creatureTarget->getHAM(CreatureAttribute::WILLPOWER);

					if (creatureTarget->isKneeling() || creatureTarget->isSitting()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 18.25)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 18.25)) * 0.10) * -1);
					} else if (creatureTarget->isProne() || creatureTarget->isKnockedDown()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 24.5)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 24.5)) * 0.10) * -1);
					} else if (creatureTarget->isStanding() || creatureTarget->isRidingMount()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 12)) * 0.10) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 12)) * 0.10) * -1);
					}
				} else if (currentHealth <= 25000) {
					if (creatureTarget->isKneeling() || creatureTarget->isSitting()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (300 + (System::random(50) * 6.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (300 + (System::random(50) * 6.25)) * -1);
					} else if (creatureTarget->isProne() || creatureTarget->isKnockedDown()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (300 + (System::random(50) * 6.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (300 + (System::random(50) * 6.5)) * -1);
					} else if (creatureTarget->isStanding() || creatureTarget->isRidingMount()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (300 + (System::random(50) * 6)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (300 + (System::random(50) * 6)) * -1);
					}
				}

				creatureTarget->addBuff(buff);

			}

		}

		return res;
	}

};

#endif //FORCEWEAKEN2COMMAND_H_
