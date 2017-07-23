/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ForceHealQueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/collision/CollisionManager.h"

ForceHealQueueCommand::ForceHealQueueCommand(const String& name, ZoneProcessServer* server) : JediQueueCommand(name, server) {
	speed = 3;
	allowedTarget = TARGET_AUTO;

	forceCost = 0;
	forceCostMultiplier = 0;

	statesToHeal = 0;
	healStateCost = 0;

	healBleedingCost = 0;
	healPoisonCost = 0;
	healDiseaseCost = 0;
	healFireCost = 0;

	attributesToHeal = 0;
	woundAttributesToHeal = 0;

	healBattleFatigue = 0;
	healAmount = 0;
	healWoundAmount = 0;

	bleedHealIterations = 1;
	poisonHealIterations = 1;
	diseaseHealIterations = 1;
	fireHealIterations = 1;

	visMod = 10;

	range = 0;

	clientEffect = "clienteffect/pl_force_heal_self.cef";
	animationCRC = STRING_HASHCODE("force_healing_1");
}

int ForceHealQueueCommand::runCommand(CreatureObject* creature, CreatureObject* targetCreature) const {
	ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

	if (playerObject == NULL)
		return GENERALERROR;

	int currentForce = playerObject->getForcePower();
	int totalCost = forceCost;
	bool healPerformed = false;

	// Attribute Wound Healing
	for (int i = 0; i < 3; i++) {
		// Attrib Values: Health = 1, Action = 2, Mind = 4
		if (woundAttributesToHeal & (1 << i)) {
			for (int j = 0; j < 3; j++) {
				if (totalCost < currentForce) {
					uint8 attrib = (i * 3) + j;
					int woundAmount = targetCreature->getWounds(attrib);

					if (healWoundAmount > 0 && woundAmount > healWoundAmount)
						woundAmount = healWoundAmount;

					totalCost += woundAmount * forceCostMultiplier;

					if (totalCost > currentForce) {
						int forceDiff = totalCost - currentForce;
						totalCost -= forceDiff;
						woundAmount -= forceDiff / forceCostMultiplier;
					}

					if (woundAmount > 0) {
						targetCreature->healWound(creature, attrib, woundAmount, true);
						healPerformed = true;
						sendHealMessage(creature, targetCreature, HEAL_WOUNDS, attrib, woundAmount);
					}
				}
			}
		}
	}

	// HAM Attribute Healing
	for (int i = 0; i < 3; i++) {
		// Attrib Values: Health = 1, Action = 2, Mind = 4
		if (attributesToHeal & (1 << i)) {
			if (totalCost < currentForce) {
				uint8 attrib = i * 3;
				int curHam = targetCreature->getHAM(attrib);
				int maxHam = targetCreature->getMaxHAM(attrib) - targetCreature->getWounds(attrib);
				int amtToHeal = maxHam - curHam;

				if (healAmount > 0 && amtToHeal > healAmount)
					amtToHeal = healAmount;

				totalCost += amtToHeal * forceCostMultiplier;

				if (totalCost > currentForce) {
					int forceDiff = totalCost - currentForce;
					totalCost -= forceDiff;
					amtToHeal -= forceDiff / forceCostMultiplier;
				}

				if (amtToHeal > 0) {
					targetCreature->healDamage(creature, attrib, amtToHeal, true);
					healPerformed = true;
					sendHealMessage(creature, targetCreature, HEAL_DAMAGE, attrib, amtToHeal);
				}
			}
		}
	}

	// Battle fatigue
	if (totalCost < currentForce && healBattleFatigue != 0) {
		int battleFatigue = targetCreature->getShockWounds();

		if (healBattleFatigue > 0 && battleFatigue > healBattleFatigue)
			battleFatigue = healBattleFatigue;

		totalCost += battleFatigue * forceCostMultiplier;

		if (totalCost > currentForce) {
			int forceDiff = totalCost - currentForce;
			totalCost -= forceDiff;
			battleFatigue -= forceDiff / forceCostMultiplier;
		}

		if (battleFatigue > 0) {
			targetCreature->addShockWounds(-battleFatigue, true, false);
			sendHealMessage(creature, targetCreature, HEAL_FATIGUE, 0, battleFatigue);
			healPerformed = true;
		}
	}

	// States - Stun, Blind, Dizzy, Intim
	if (totalCost < currentForce) {
		int totalStates = 0;
		int healedStates = 0;
		for (int i = 12; i <= 15; i++) {
			int state = (1 << i);

			if ((statesToHeal & state) && targetCreature->hasState(state)) {
				totalStates++;
				int newTotal = totalCost + healStateCost;

				if (newTotal < currentForce) {
					targetCreature->removeStateBuff(state);
					totalCost = newTotal;
					healPerformed = true;
					healedStates++;
				}
			}
		}

		if (healedStates > 0 && healedStates == totalStates)
			sendHealMessage(creature, targetCreature, HEAL_STATES, 0, 0);
	}

	// Bleeding
	if (targetCreature->isBleeding() && healBleedingCost > 0 && totalCost + healBleedingCost < currentForce) {
		bool result = false;
		int iteration = 1;

		while (!result && (totalCost + healBleedingCost < currentForce) && (bleedHealIterations == -1 || iteration <= bleedHealIterations)) {
			result = targetCreature->healDot(CreatureState::BLEEDING, 250, false);
			totalCost += healBleedingCost;
			iteration++;
		}

		if (result) {
			sendHealMessage(creature, targetCreature, HEAL_BLEEDING, 0, 1);
		} else {
			sendHealMessage(creature, targetCreature, HEAL_BLEEDING, 0, 0);
		}

		healPerformed = true;
	}

	// Poison
	if (targetCreature->isPoisoned() && healPoisonCost > 0 && totalCost + healPoisonCost < currentForce) {
		bool result = false;
		int iteration = 1;

		while (!result && (totalCost + healPoisonCost < currentForce) && (poisonHealIterations == -1 || iteration <= poisonHealIterations)) {
			result = targetCreature->healDot(CreatureState::POISONED, 250, false);
			totalCost += healPoisonCost;
			iteration++;
		}

		if (result) {
			sendHealMessage(creature, targetCreature, HEAL_POISON, 0, 1);
		} else {
			sendHealMessage(creature, targetCreature, HEAL_POISON, 0, 0);
		}

		healPerformed = true;
	}

	// Disease
	if (targetCreature->isDiseased() && healDiseaseCost > 0 && totalCost + healDiseaseCost < currentForce) {
		bool result = false;
		int iteration = 1;

		while (!result && (totalCost + healDiseaseCost < currentForce) && (diseaseHealIterations == -1 || iteration <= diseaseHealIterations)) {
			result = targetCreature->healDot(CreatureState::DISEASED, 200, false);
			totalCost += healDiseaseCost;
			iteration++;
		}

		if (result) {
			sendHealMessage(creature, targetCreature, HEAL_DISEASE, 0, 1);
		} else {
			sendHealMessage(creature, targetCreature, HEAL_DISEASE, 0, 0);
		}

		healPerformed = true;
	}

	// Fire
	if (targetCreature->isOnFire() && healFireCost > 0 && totalCost + healFireCost < currentForce) {
		bool result = false;
		int iteration = 1;

		while (!result && (totalCost + healFireCost < currentForce) && (fireHealIterations == -1 || iteration <= fireHealIterations)) {
			result = targetCreature->healDot(CreatureState::ONFIRE, 500, false);
			totalCost += healFireCost;
			iteration++;
		}

		if (result) {
			sendHealMessage(creature, targetCreature, HEAL_FIRE, 0, 1);
		} else {
			sendHealMessage(creature, targetCreature, HEAL_FIRE, 0, 0);
		}

		healPerformed = true;
	}

	bool selfHeal = creature->getObjectID() == targetCreature->getObjectID();

	if (healPerformed) {
		if (selfHeal)
			creature->playEffect(clientEffect, "");
		else
			creature->doCombatAnimation(targetCreature, animationCRC, 0, 0xFF);

		if (currentForce < totalCost) {
			playerObject->setForcePower(0);
			creature->error("Did not have enough force to pay for the healing he did. Total cost of command: " + String::valueOf(totalCost) + ", player's current force: " + String::valueOf(currentForce));
		} else {
			playerObject->setForcePower(currentForce - totalCost);
		}

		VisibilityManager::instance()->increaseVisibility(creature, visMod);
		return SUCCESS;
	} else {
		if (selfHeal) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self");
		} else {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_other");
		}

		return GENERALERROR;
	}
}

void ForceHealQueueCommand::sendHealMessage(CreatureObject* creature, CreatureObject* target, int healType, int healSpec, int amount) const {
	if (creature == NULL || target == NULL || amount < 0)
		return;

	uint64 playerID = creature->getObjectID();
	uint64 targetID = target->getObjectID();
	const bool selfHeal = playerID == targetID;

	if (healType == HEAL_DAMAGE || healType == HEAL_WOUNDS || healType == HEAL_FATIGUE) {
		String strVal = "@jedi_spam:";

		switch (healType) {
		case HEAL_DAMAGE: strVal = strVal + CreatureAttribute::getName(healSpec) + "_damage"; break;
		case HEAL_WOUNDS: strVal = strVal + CreatureAttribute::getName(healSpec) + "_wounds"; break;
		default: strVal = strVal + "battle_fatigue";
		}

		String statStr = StringIdManager::instance()->getStringId(strVal.hashCode()).toString();

		if (selfHeal) {
			StringIdChatParameter message("jedi_spam", "heal_self");
			message.setTO(statStr);
			message.setDI(amount);
			creature->sendSystemMessage(message);
		} else {
			StringIdChatParameter message("jedi_spam", "heal_other_self");
			message.setTO(statStr);
			message.setDI(amount);
			message.setTT(targetID);
			creature->sendSystemMessage(message);

			if (target->isPlayerCreature()) {
				StringIdChatParameter message("jedi_spam", "heal_other_other");
				message.setTO(statStr);
				message.setDI(amount);
				message.setTT(playerID);
				target->sendSystemMessage(message);
			}
		}
	} else if (healType == HEAL_STATES && amount == 0 && !selfHeal) {
		StringIdChatParameter message("jedi_spam", "stop_states_other");
		message.setTT(targetID);
		creature->sendSystemMessage(message);
	} else if (healType == HEAL_POISON && !selfHeal) {
		if (amount == 1) {
			StringIdChatParameter message("jedi_spam", "stop_poison_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		} else {
			StringIdChatParameter message("jedi_spam", "staunch_poison_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		}
	} else if (healType == HEAL_DISEASE && !selfHeal) {
		if (amount == 1) {
			StringIdChatParameter message("jedi_spam", "stop_disease_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		} else {
			StringIdChatParameter message("jedi_spam", "staunch_disease_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		}
	} else if (healType == HEAL_BLEEDING && !selfHeal) {
		if (amount == 1) {
			StringIdChatParameter message("jedi_spam", "stop_bleeding_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		} else {
			StringIdChatParameter message("jedi_spam", "staunch_bleeding_other");
			message.setTT(targetID);
			creature->sendSystemMessage(message);
		}
	}

	if (amount == 0) {
		if (healType == HEAL_POISON) {
			target->getDamageOverTimeList()->sendDecreaseMessage(target, CreatureState::POISONED);
		} else if (healType == HEAL_DISEASE) {
			target->getDamageOverTimeList()->sendDecreaseMessage(target, CreatureState::DISEASED);
		} else if (healType == HEAL_BLEEDING) {
			target->getDamageOverTimeList()->sendDecreaseMessage(target, CreatureState::BLEEDING);
		} else if (healType == HEAL_FIRE) {
			target->getDamageOverTimeList()->sendDecreaseMessage(target, CreatureState::ONFIRE);
		}
	}
}

int ForceHealQueueCommand::runCommandWithTarget(CreatureObject* creature, CreatureObject* targetCreature) const {
	if (creature == NULL || targetCreature == NULL)
		return GENERALERROR;

	if (creature->getObjectID() == targetCreature->getObjectID()) // no self healing
		return GENERALERROR;

	if ((!targetCreature->isPlayerCreature() && !targetCreature->isPet()) || targetCreature->isDroidObject() || targetCreature->isWalkerSpecies())
		return INVALIDTARGET;

	if (targetCreature->isDead() || targetCreature->isAttackableBy(creature))
		return GENERALERROR;

	Locker crossLocker(targetCreature, creature);

	if (creature->isKnockedDown())
		return GENERALERROR;

	if(!checkDistance(creature, targetCreature, range))
		return TOOFAR;

	if (!targetCreature->isHealableBy(creature)) {
		creature->sendSystemMessage("@healing:pvp_no_help"); // It would be unwise to help such a patient.
		return GENERALERROR;
	}

	if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
		creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
		return GENERALERROR;
	}

	return runCommand(creature, targetCreature);
}

int ForceHealQueueCommand::doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	if (creature == NULL || !creature->isPlayerCreature())
		return GENERALERROR;

	if (!checkInvalidLocomotions(creature))
		return INVALIDLOCOMOTION;

	int comResult = doCommonJediSelfChecks(creature);

	if (comResult != SUCCESS)
		return comResult;

	ManagedReference<CreatureObject*> targetCreature = NULL;
	bool isRemoteHeal = range > 0 && ((allowedTarget == TARGET_AUTO) || (allowedTarget & TARGET_OTHER));

	if (isRemoteHeal && target != 0 && target != creature->getObjectID()) {
		ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(target);

		if (sceno != NULL && sceno->isCreatureObject()) {
			targetCreature = sceno.castTo<CreatureObject*>();
		}
	}

	const bool selfHealingAllowed = (allowedTarget & TARGET_SELF) || !isRemoteHeal;
	if (!isRemoteHeal || (targetCreature == NULL && selfHealingAllowed) || (targetCreature != NULL && (!targetCreature->isHealableBy(creature)) && selfHealingAllowed)) {
		isRemoteHeal = false;
		targetCreature = creature;
	}

	if (targetCreature == NULL)
		return GENERALERROR;

	int retval = GENERALERROR;

	if (isRemoteHeal)
		retval = runCommandWithTarget(creature, targetCreature);
	else
		retval = runCommand(creature, targetCreature);

	return retval;
}
