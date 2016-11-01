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

		ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();
		if (creatureTarget->hasBuff(STRING_HASHCODE("forceweaken2"))) {
			return NOSTACKJEDIBUFF;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Setup debuffs...

			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget != NULL) {

				Locker clocker(creatureTarget, creature);

				ManagedReference<Buff*> buff = new Buff(creatureTarget, getNameCRC(), 90, BuffType::JEDI);

				int currentHealth = creatureTarget->getHAM(CreatureAttribute::HEALTH);
				int currentAction = creatureTarget->getHAM(CreatureAttribute::ACTION);
				int currentMind = creatureTarget->getHAM(CreatureAttribute::MIND);

				if (!creatureTarget->hasBuff(STRING_HASHCODE("forceweaken1"))) {
					int duration = 90;
					int randTick = System::random(30);
					String buffname = "forceweaken1b";

					if (currentHealth <= 25000) {
						int debuffHam = 25 + (randTick * 5);// debuff of HAMs should TICK between 25-150 per weaken1, 50-250 weaken2

						ManagedReference<Buff*> hamDebuff = new ForceWeakenDebuff(creatureTarget, buffname, buffname.hashCode(), debuffHam, duration);

						Locker locker(hamDebuff);

						creatureTarget->addBuff(hamDebuff);

					} else if (currentHealth > 25000) {
						int debuffHam = (randTick * currentHealth) * .001;// but for higher level mobs, debuff of HAMs should 'scale' up

						ManagedReference<Buff*> hamDebuff = new ForceWeakenDebuff(creatureTarget, buffname, buffname.hashCode(), debuffHam, duration);

						Locker locker(hamDebuff);

						creatureTarget->addBuff(hamDebuff);

					}

				}

				Locker locker(buff);

				if (currentHealth > 25000) {
					int currentStr = creatureTarget->getHAM(CreatureAttribute::STRENGTH);
					int currentCon = creatureTarget->getHAM(CreatureAttribute::CONSTITUTION);
					int currentQui = creatureTarget->getHAM(CreatureAttribute::QUICKNESS);
					int currentStam = creatureTarget->getHAM(CreatureAttribute::STAMINA);
					int currentFoc = creatureTarget->getHAM(CreatureAttribute::FOCUS);
					int currentWill = creatureTarget->getHAM(CreatureAttribute::WILLPOWER);

					if (creatureTarget->isKneeling() || creatureTarget->isSitting()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 18.25)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 18.25)) * 0.05) * -1);
					} else if (creatureTarget->isProne() || creatureTarget->isKnockedDown()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 24.5)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 24.5)) * 0.05) * -1);
					} else if (creatureTarget->isStanding() || creatureTarget->isRidingMount()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, ((currentHealth + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, ((currentStr + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, ((currentCon + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, ((currentAction + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, ((currentQui + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, ((currentStam + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, ((currentMind + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, ((currentFoc + (System::random(50) * 12)) * 0.05) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, ((currentWill + (System::random(50) * 12)) * 0.05) * -1);
					}
				} else if (currentHealth <= 25000) {
					if (creatureTarget->isKneeling() || creatureTarget->isSitting()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (100 + (System::random(50) * 4.25)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (100 + (System::random(50) * 4.25)) * -1);
					} else if (creatureTarget->isProne() || creatureTarget->isKnockedDown()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (100 + (System::random(50) * 4.5)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (100 + (System::random(50) * 4.5)) * -1);
					} else if (creatureTarget->isStanding() || creatureTarget->isRidingMount()) {
						buff->setAttributeModifier(CreatureAttribute::HEALTH, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STRENGTH, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::ACTION, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::QUICKNESS, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::STAMINA, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::MIND, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::FOCUS, (100 + (System::random(50) * 4)) * -1);
						buff->setAttributeModifier(CreatureAttribute::WILLPOWER, (100 + (System::random(50) * 4)) * -1);
					}
				}

				creatureTarget->addBuff(buff);

			}

		}

		return res;
	}

};

#endif //FORCEWEAKEN1COMMAND_H_
