/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ForceHealQueueCommand.h"

//#define DEBUG_FORCE_HEALS

#ifdef DEBUG_FORCE_HEALS
	inline String dbg_fh_bool2s(bool r) {
		return r?String("true"):String("false");
	}
#endif


ForceHealQueueCommand::ForceHealQueueCommand(const String& name, ZoneProcessServer* server) : JediQueueCommand(name, server) {
	speed = 3;
	allowedTarget = TARGET_AUTO;

	forceCost = 0;
	forceCostDivisor = 0;

	healStates = 0;

	healBleeding = 0;
	healPoison = 0;
	healDisease = 0;
	healFire = 0;

	healAttributes = 0;
	healWoundAttributes = 0;

	healBattleFatigue = 0;
	healAmount = 0;
	healWoundAmount = 0;

	range = 0;

	clientEffect = "clienteffect/pl_force_heal_self.cef";
	animationCRC = STRING_HASHCODE("force_healing_1");
}

void ForceHealQueueCommand::doAnimations(CreatureObject* creature, CreatureObject* creatureTarget, healedAttributes_t& attributes) const {
	if (creature == creatureTarget) {
		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");
	} else
		creature->doCombatAnimation(creatureTarget, animationCRC, 0, 0xFF);
}

int ForceHealQueueCommand::doHealBF(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const {
	if (creature == NULL || target == NULL) return GENERALERROR;

	int currentValue = creature->getShockWounds();
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[doHealBF] currentValue = " + String::valueOf(currentValue));
	creature->sendSystemMessage("[doHealBF] healBattleFatigue = " + String::valueOf(healBattleFatigue));
#endif
	if (currentValue > 0) {
		int healedValue = MIN(currentValue, healBattleFatigue);

#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[doHealBF] healedValue = " + String::valueOf(healedValue));
#endif

		target->addShockWounds(-healedValue, true, false);
		attrs.healedBF = healedValue;
	}

	return SUCCESS;
}


int ForceHealQueueCommand::checkWoundAttributes(CreatureObject* creature, CreatureObject* targetCreature) const {
	int retval = 0;
	if (targetCreature == NULL) return 0;
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkWoundAttributes] healWoundAttributes: " + String::valueOf(healWoundAttributes));
	creature->sendSystemMessage("[checkWoundAttributes] healWoundAttributes & CombatManager::HEALTH = " + dbg_fh_bool2s(healWoundAttributes & CombatManager::HEALTH));
	creature->sendSystemMessage("[checkWoundAttributes] healWoundAttributes & CombatManager::ACTION = " + dbg_fh_bool2s(healWoundAttributes & CombatManager::ACTION));
	creature->sendSystemMessage("[checkWoundAttributes] healWoundAttributes & CombatManager::MIND = " + dbg_fh_bool2s(healWoundAttributes & CombatManager::MIND));
#endif
	if (healWoundAttributes & CombatManager::HEALTH) {
		if (targetCreature->getWounds(CreatureAttribute::HEALTH) ||
		    targetCreature->getWounds(CreatureAttribute::CONSTITUTION) ||
		    targetCreature->getWounds(CreatureAttribute::STRENGTH)
		) {
			retval |= HEALTH;
		}
	}

	if (healWoundAttributes & CombatManager::ACTION) {
		if (targetCreature->getWounds(CreatureAttribute::ACTION) ||
		    targetCreature->getWounds(CreatureAttribute::QUICKNESS) ||
		    targetCreature->getWounds(CreatureAttribute::STAMINA)
		) {
			retval |= ACTION;
		}
	}

	if (healWoundAttributes & CombatManager::MIND) {
		if (targetCreature->getWounds(CreatureAttribute::MIND) ||
		    targetCreature->getWounds(CreatureAttribute::FOCUS) ||
		    targetCreature->getWounds(CreatureAttribute::WILLPOWER)
		) {
			retval |= MIND;
		}
	}
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkWoundAttributes] healWoundAttributes result: " + String::valueOf(retval));
#endif
	return retval;
}


int ForceHealQueueCommand::doHealWounds(CreatureObject* creature, CreatureObject* targetCreature, int healableWounds, healedAttributes_t& attrs) const {
	if (targetCreature == NULL) return GENERALERROR;
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage(name + "[doHealWounds] Healing wounds " + String::valueOf(healWoundAmount) + " " + String::valueOf(healableWounds));
#endif
	if (healableWounds & HEALTH) {
		attrs.healedHealthWounds = targetCreature->healWound(creature, CreatureAttribute::HEALTH, healWoundAmount, true);
		attrs.healedStrengthWounds = targetCreature->healWound(creature, CreatureAttribute::STRENGTH, healWoundAmount, true);
		attrs.healedConstitutionWounds = targetCreature->healWound(creature, CreatureAttribute::CONSTITUTION, healWoundAmount, true);
	}

	if (healableWounds & ACTION) {
		attrs.healedActionWounds = targetCreature->healWound(creature, CreatureAttribute::ACTION, healWoundAmount, true);
		attrs.healedQuicknessWounds = targetCreature->healWound(creature, CreatureAttribute::QUICKNESS, healWoundAmount, true);
		attrs.healedWillpowerWounds = targetCreature->healWound(creature, CreatureAttribute::STAMINA, healWoundAmount, true);
	}

	if (healableWounds & MIND) {
		attrs.healedMindWounds = targetCreature->healWound(creature, CreatureAttribute::MIND, healWoundAmount, true);
		attrs.healedFocusWounds = targetCreature->healWound(creature, CreatureAttribute::FOCUS, healWoundAmount, true);
		attrs.healedWillpowerWounds = targetCreature->healWound(creature, CreatureAttribute::WILLPOWER, healWoundAmount, true);
	}

	return SUCCESS;
}

int ForceHealQueueCommand::checkHAMAttributes(CreatureObject* creature, CreatureObject* targetCreature) const {
	int retval = 0;
	if (healAttributes == 0 || creature == NULL || targetCreature == NULL) return 0;
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("healAttributes:" + String::valueOf(healAttributes)); 
#endif

	// check for the pools that shall be healed and if they are damaged
	// we also translate from CombatManager attributes to our own bitset
	if (healAttributes & CombatManager::HEALTH) {
		if (targetCreature->hasDamage(CreatureAttribute::HEALTH)) {
			retval |= HEALTH;
		}
	}

	if (healAttributes & CombatManager::ACTION) {
		if (targetCreature->hasDamage(CreatureAttribute::ACTION)) {
			retval |= ACTION;
		}
	}

	if (healAttributes & CombatManager::MIND) {
		if (targetCreature->hasDamage(CreatureAttribute::MIND)) {
			retval |= MIND;
		}
	}

	return retval;
}
int ForceHealQueueCommand::doHealHAM(CreatureObject* creature, CreatureObject* target, int healableHAM, healedAttributes_t& attrs) const {
	if (target == NULL) return GENERALERROR;
	creature->sendSystemMessage("Healable HAM:" + String::valueOf(healableHAM));
	if (healableHAM & HEALTH) {
		attrs.healedHealth = target->healDamage(creature, CreatureAttribute::HEALTH, healAmount);
	}

	if (healableHAM & ACTION) {
		attrs.healedAction = target->healDamage(creature, CreatureAttribute::ACTION, healAmount);
	}

	if (healableHAM & MIND) {
		attrs.healedMind = target->healDamage(creature, CreatureAttribute::MIND, healAmount);
	}

	return SUCCESS;
}

int ForceHealQueueCommand::checkStates(CreatureObject* creature, CreatureObject* target) const {
	int retval = 0;
	if (creature == NULL || target == NULL || healStates == 0) return 0;

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkStates] healStates = " + String::valueOf(healStates)); 
	creature->sendSystemMessage("[checkStates] healStates & CS::STUNNED = " + dbg_fh_bool2s(healStates & CreatureState::STUNNED));
	creature->sendSystemMessage("[checkStates] healStates & CS::DIZZY = " + dbg_fh_bool2s(healStates & CreatureState::DIZZY));
	creature->sendSystemMessage("[checkStates] healStates & CS::BLINDED = " + dbg_fh_bool2s(healStates & CreatureState::BLINDED));
	creature->sendSystemMessage("[checkStates] healStates & CS::INTIMIDATED = " + dbg_fh_bool2s(healStates & CreatureState::INTIMIDATED));
#endif

	// translate CreatureState enums to ours while we are at it
	if (healStates & CreatureState::STUNNED) {
		if (target->hasState(CreatureState::STUNNED)) {
			retval |= STUN;
		}
	}

	if (healStates & CreatureState::DIZZY) {
		if (target->hasState(CreatureState::DIZZY)) {
			retval |= DIZZY;
		}
	}

	if (healStates & CreatureState::BLINDED) {
		if (target->hasState(CreatureState::BLINDED)) {
			retval |= BLIND;
		}
	}

	if (healStates & CreatureState::INTIMIDATED) {
		if (target->hasState(CreatureState::INTIMIDATED)) {
			retval |= INTIMIDATE;
		}
	}
#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkStates] result = " + String::valueOf(retval));
	creature->sendSystemMessage("[checkStates] result & STUNN = " + dbg_fh_bool2s(retval & STUN));
	creature->sendSystemMessage("[checkStates] result & DIZZY = " + dbg_fh_bool2s(retval & DIZZY));
	creature->sendSystemMessage("[checkStates] result & BLIND = " + dbg_fh_bool2s(retval & BLIND));
	creature->sendSystemMessage("[checkStates] result & INTIMIDATE = " + dbg_fh_bool2s(retval & INTIMIDATE));
#endif


	return retval;
}

int ForceHealQueueCommand::doHealStates(CreatureObject* creature, CreatureObject* target, int healableStates, healedAttributes_t& attrs) const {
	if (creature == NULL || target == NULL)
		return GENERALERROR;

	if (healableStates & STUN) {
		target->removeStateBuff(CreatureState::STUNNED);
		attrs.healedStates |= STUN;
	}

	if (healableStates & DIZZY) {
		target->removeStateBuff(CreatureState::DIZZY);
		attrs.healedStates |= DIZZY;
	}

	if (healableStates & BLIND) {
		target->removeStateBuff(CreatureState::BLINDED);
		attrs.healedStates |= BLIND;
	}

	if (healableStates & INTIMIDATE) {
		target->removeStateBuff(CreatureState::INTIMIDATED);
		attrs.healedStates |= INTIMIDATE;
	}

	return SUCCESS;
}

int ForceHealQueueCommand::doHealDots(CreatureObject* creature, CreatureObject* target, int healableDots, healedAttributes_t& attrs) const {
	if (creature == NULL || target == NULL)  return GENERALERROR;
	
	if (healableDots & DISEASED) {
		attrs.healedDisease = target->healDot(CreatureState::DISEASED, healDisease); 
	}

	if (healableDots & POISONED) {
		attrs.healedPoison = target->healDot(CreatureState::POISONED, healPoison);
	}

	if (healableDots & ONFIRE) {
		attrs.healedFire = target->healDot(CreatureState::ONFIRE, healFire);
	}

	if (healableDots & BLEEDING) {
		attrs.healedBleeding = target->healDot(CreatureState::BLEEDING, healBleeding);
	}

	return SUCCESS;
}

int ForceHealQueueCommand::checkDots(CreatureObject* creature, CreatureObject* target) const {
	int retval = 0;
	if (creature == NULL || target == NULL) return 0;

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkDots] healDisease: " + String::valueOf(healDisease));
	creature->sendSystemMessage("[checkDots] healPoison: " + String::valueOf(healPoison));
	creature->sendSystemMessage("[checkDots] healBleeding: " + String::valueOf(healBleeding));
	creature->sendSystemMessage("[checkDots] healFire: " + String::valueOf(healFire));
#endif


	if (healDisease > 0) {
		if (target->isDiseased()) {
			retval |= DISEASED;
		}
	}

	if (healPoison > 0) {
		if (target->isPoisoned()) {
			retval |= POISONED;
		}
	}

	if (healBleeding > 0) {
		if (target->isBleeding()) {
			retval |= BLEEDING;
		}
	}

	if (healFire > 0) {
		if (target->isOnFire()) {
			retval |= ONFIRE;
		}
	}

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[checkDots] result = " + String::valueOf(retval));
	creature->sendSystemMessage("[checkDots] result & DISEASED = " + dbg_fh_bool2s(retval & DISEASED));
	creature->sendSystemMessage("[checkDots] result & POISONED = " + dbg_fh_bool2s(retval & POISONED));
	creature->sendSystemMessage("[checkDots] result & BLEEDING = " + dbg_fh_bool2s(retval & BLEEDING));
	creature->sendSystemMessage("[checkDots] result & ONFIRE = " + dbg_fh_bool2s(retval & ONFIRE));
#endif


	return retval;
}

int ForceHealQueueCommand::calculateForceCost(CreatureObject* creature, CreatureObject* targetCreature, healedAttributes_t& attrs) const {
	// we simply assume all attributes that we aren't supposed to have healed
	// are zero since we didn initialize the struct with zero...
	
	int calculatedForceCost = 0;

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[calculateForceCost] forceCostDivisor = " + String::valueOf(forceCostDivisor));
	creature->sendSystemMessage("[calculateForceCost] forceCost = " + String::valueOf(forceCost));
#endif


	if (forceCostDivisor != 0) { //forceCostDivisor < 0 || forceCostDivisor > 0
		
	
		// HAM
		int amountHealed = attrs.sumHAM();
		// Wounds
		amountHealed += attrs.sumWounds();
		// Dots
		amountHealed += attrs.sumDots();
		/*
		 * Is BF being charged for?
		 *
		amountHealed += attrs.healedBF;
		 */

#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[calculatedForceCost] amountHealed = " + String::valueOf(amountHealed));
#endif


		if (forceCostDivisor < 0)
			calculatedForceCost = amountHealed;
		else // forceCostDevisor > 0
			if (forceCostDivisor > 1)
				calculatedForceCost = amountHealed / forceCostDivisor;

		// if forceCost > 0 we will ensure the total costs are never above it
		if (forceCost > 0) {
			calculatedForceCost = MIN(calculatedForceCost, forceCost);
		}

	} else { // forceCostDivisor == 0
		calculatedForceCost = forceCost;
	}

	// if someone figures out how to overflow this make sure they can't earn force with it
	if (calculatedForceCost < 0)
		calculatedForceCost = 0;

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[calculateForceCost] result = " + String::valueOf(calculatedForceCost));
#endif


	return calculatedForceCost;

}
void ForceHealQueueCommand::sendHealMessage(CreatureObject* creature, CreatureObject* target, int attribute, const int amount, const bool wound) const {
	if (creature == NULL || target == NULL || amount <= 0) return;

	// store if we are healing ourselfs or not
	const bool isSame = creature == target;

	StringIdChatParameter message("jedi_spam", (isSame)?"heal_self": "heal_other_self");
	bool res = false;
	if (!wound)
		res = setHealMessageTO(message, attribute);
	else
		res = setWoundHealMessageTO(message, attribute);

	if (!res) {
		creature->error("Tried to send heal message for unknown attribute: " + String::valueOf(attribute));
		return;
	}

	if (!isSame)
		message.setTT(target->getFirstName());

	message.setDI(amount);
	creature->sendSystemMessage(message);

	if (!isSame) {
		// send the 'you've been healed by ...' messages

		StringIdChatParameter message("jedi_spam", "heal_other_other");
		res = false;
		if (!wound)
			res = setHealMessageTO(message, attribute);
		else
			res = setWoundHealMessageTO(message, attribute);

		if (!res) {
			creature->error("Tried to send heal message for unknown attribute:" + String::valueOf(attribute));
			return;
		}
		message.setTT(creature->getFirstName());
		message.setDI(amount);
		target->sendSystemMessage(message);
	}

}

void ForceHealQueueCommand::sendSystemMessage(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const {
	const bool didHealTarget = creature != target;

	// check if we did any healing at all, if not respond
	// with "No damage of that type"
	const int dots = attrs.sumDots();
	const int ham = attrs.sumHAM();
	const int wounds = attrs.sumWounds();

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[sendSystemMessage] dots = " + String::valueOf(dots) + " ham = " + String::valueOf(ham) +
			"wounds = " + String::valueOf(wounds));
	creature->sendSystemMessage("[sendSystemMessage] didHealTarget = " + dbg_fh_bool2s(didHealTarget));
#endif

	if (wounds + dots + ham + attrs.healedStates + attrs.healedBF == 0) {
		if (healAttributes != 0 || healBattleFatigue != 0) {
			if (!didHealTarget) {
				// You have no damage of that type.
				creature->sendSystemMessage("@jedi_spam:no_damage_heal_self");
			} else {
				// Your target has no damage of that type to heal.
				creature->sendSystemMessage("@jedi_spam:no_damage_heal_other");
			}
		} else if (healStates != 0) {
			// was supposed to heal states but there werent any
			if (!didHealTarget) {
				// You have no state of that type to heal.
				creature->sendSystemMessage("@healing_response:healing_response_72");
			} else {
				// %NI has no state of that type to heal.
				StringIdChatParameter msg("healing_response", "healing_response_74");
				msg.setTT(target->getObjectID());
				creature->sendSystemMessage(msg);
			}
		} else if (healBleeding != 0) {
			// was supposed to heal bleeding
			if (!didHealTarget) {
				// You are not bleeding.
				creature->sendSystemMessage("@healing_response:healing_response_78");
			} else {
				// %NT is not bleeding.
				StringIdChatParameter msg("healing_response", "healing_response_80");
				msg.setTT(target->getObjectID());
				creature->sendSystemMessage(msg);
			}
		} else  if (healFire != 0) {
			// there is no such message in case there wasn't fire to heal..
			return;
		} else if (healPoison != 0) {
			// couldn't heal any poison
			if (!didHealTarget) {
				// You are not poisoned.
				creature->sendSystemMessage("@healing_response:healing_response_82");
			} else {
				// %NT is not poisoned
				StringIdChatParameter msg("healing_response", "healing_response_84");
				msg.setTT(target->getObjectID());
				creature->sendSystemMessage(msg);
			}
		} else if (healDisease != 0) {
			if (!didHealTarget) {
				// You are not diseased.
				creature->sendSystemMessage("@healing_response:healing_response_90");
			} else {
				// %NT is nto diseased.
				StringIdChatParameter msg("healing_response", "healing_response_92");
				msg.setTT(target->getObjectID());
				creature->sendSystemMessage(msg);
			}
		} else if (healWoundAttributes != 0) {
			if (!didHealTarget) {
				// You have no wounds of that type to heal.
				creature->sendSystemMessage("@healing_response:healing_response_67");
			} else {
				// Unable to find any wounds which you can heal.
				creature->sendSystemMessage("@healing_response:healing_response_64");
			}
		}
		return;
	} else {
		if (ham != 0) {
			sendHealMessage(creature, target, HEALTH, attrs.healedHealth);
			sendHealMessage(creature, target, ACTION, attrs.healedAction);
			sendHealMessage(creature, target, MIND, attrs.healedMind);
		}
		if (dots != 0) {
			if (attrs.healedBleeding) {
				sendHealDotMessage(creature, target, attrs.healedBleeding,
						"stop_bleeding_other", "staunch_bleeding_other", CreatureState::BLEEDING);
			}

			if (attrs.healedPoison) {
				sendHealDotMessage(creature, target, attrs.healedPoison,
						"stop_poison_other", "staunch_poison_other", CreatureState::POISONED);
			}

			/* FIXME: is there an STF entry for this case?
			if (attrs.healedFire) {
				sendHealDotMessage(creature, target, attrs.healedFire,
						"stop_fire_other", "staunch_fire_other", CreatureState::ONFIRE);
			}*/
			
			if (attrs.healedDisease) {
				sendHealDotMessage(creature, target, attrs.healedDisease,
						"stop_disease_other", "staunch_disease_other", CreatureState::DISEASED);
			}
		}

		if (wounds != 0) {
			sendHealMessage(creature, target, HEALTH, attrs.healedHealthWounds, true);
			sendHealMessage(creature, target, STRENGTH, attrs.healedStrengthWounds, true);
			sendHealMessage(creature, target, CONSTITUTION, attrs.healedConstitutionWounds, true);

			sendHealMessage(creature, target, ACTION, attrs.healedActionWounds, true);
			sendHealMessage(creature, target, QUICKNESS, attrs.healedActionWounds, true);
			sendHealMessage(creature, target, STAMINA, attrs.healedStaminaWounds, true);

			sendHealMessage(creature, target, MIND, attrs.healedMindWounds, true);
			sendHealMessage(creature, target, FOCUS, attrs.healedFocusWounds, true);
			sendHealMessage(creature, target, WILLPOWER, attrs.healedWillpowerWounds, true);
		}

		if (attrs.healedStates != 0) {
			StringIdChatParameter healedStatesMessage("jedi_spam", "stop_states_other");
			if (creature != target) {
				healedStatesMessage.setTT(target->getFirstName());
			} else {
				//TODO: whats the message for self healing?
				healedStatesMessage.setTT("you"); // You cure all negative states on >you<.
			}
			creature->sendSystemMessage(healedStatesMessage);
		}
	}
}

int ForceHealQueueCommand::runCommandWithTarget(CreatureObject* creature, CreatureObject* targetCreature) const {
	if (creature == NULL || targetCreature == NULL) return GENERALERROR;

	if (creature->getObjectID() == targetCreature->getObjectID()) // no self healing
		return GENERALERROR;

	if (targetCreature->isDead() || targetCreature->isAttackableBy(creature))
		return GENERALERROR;

	Locker crossLocker(targetCreature, creature);

	if (creature->isKnockedDown()) {
		return GENERALERROR;
	}

	if (!creature->isInRange(targetCreature, range + targetCreature->getTemplateRadius() + creature->getTemplateRadius())) {
		// out of range
		return TOOFAR;
	}

	if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
		creature->sendSystemMessage("@container_error_message:container18"); // not in sight?!?
		return GENERALERROR;
	}

	if (!targetCreature->isHealableBy(creature)) {
		// TEF etc.? Do we need extra TEF checks?
		creature->sendSystemMessage("@healing:pvp_no_help");
		return GENERALERROR;
	}
	// continue with the common path
	return runCommand(creature, targetCreature);
}

int ForceHealQueueCommand::runCommand(CreatureObject* creature, CreatureObject* targetCreature) const {
	// keep the information about what will be healed and what has been healed so we can make the code a bit cleaner
	healedAttributes_t healedAttributes = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	bool didHeal = false;
	
	if (healAttributes != 0 && healAmount != 0) {
		// create a bitset so we can probe which attributes need healing and are allowed to be healed
		const int healableHAMAttributes = checkHAMAttributes(creature, targetCreature);
		if (healableHAMAttributes != 0) {
			int retval = doHealHAM(creature, targetCreature, healableHAMAttributes, healedAttributes);
			if (retval != SUCCESS) {
				return retval;
			}
#ifdef DEBUG_FORCE_HEALS
			creature->sendSystemMessage("[runCommand] healAttributes sets didHeal = true");
#endif

			didHeal = true;
		}
	}
	
	if (healWoundAttributes != 0 && healWoundAmount != 0) {
		const int healableWounds = checkWoundAttributes(creature, targetCreature);
		if (healableWounds != 0) {
			int retval = doHealWounds(creature, targetCreature, healableWounds, healedAttributes);
			if (retval != SUCCESS) {
				return retval;
			}
#ifdef DEBUG_FORCE_HEALS
			creature->sendSystemMessage("[runCommand] healWounds sets didHeal = true, healableWounds = " + String::valueOf(healableWounds));
#endif

			didHeal = true;
		}
		
	}

	if (healStates != 0) {
		const int healableStates = checkStates(creature, targetCreature);
		if (healableStates != 0) {
			int retval = doHealStates(creature, targetCreature, healableStates, healedAttributes);
			if (retval != SUCCESS) {
				return retval;
			}
#ifdef DEBUG_FORCE_HEALS
			creature->sendSystemMessage("[runCommand] healStates sets didHeal = true");
#endif

			didHeal = true;
		}
	}

	if (healDisease + healPoison + healFire + healBleeding > 0) {
		const bool healableDots = checkDots(creature, targetCreature);
		if (healableDots != 0) {
			int retval = doHealDots(creature, targetCreature, healableDots, healedAttributes);
			if (retval != SUCCESS) {
				return retval;
			}
#ifdef DEBUG_FORCE_HEALS
			creature->sendSystemMessage("[runCommand] healDots sets didHeal = true");
#endif
			didHeal = true;
		}
	}

	if (healBattleFatigue > 0) {
		const int bf = targetCreature->getShockWounds();
		const bool hasBF = bf > 0;
#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[runCommand] healBattleFatigue = " + String::valueOf(healBattleFatigue));
		creature->sendSystemMessage("[runCommand] bf = " + String::valueOf(bf));
#endif

		if (hasBF) {
			int retval = doHealBF(creature, targetCreature, healedAttributes);
			if (retval != SUCCESS) {
				return retval;
			}
#ifdef DEBUG_FORCE_HEALS
			creature->sendSystemMessage("[runCommand] healBattleFatigue sets didHeal = true");
#endif
			didHeal = true;
		}
	}

#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[runCommand] didHeal = " + String::valueOf(didHeal));
#endif
	if (didHeal) {
		int calculatedForceCost = calculateForceCost(creature, targetCreature, healedAttributes);
		applyForceCost(creature, calculatedForceCost);
		doAnimations(creature, targetCreature, healedAttributes);
		sendSystemMessage(creature, targetCreature, healedAttributes);
	} else {
		sendSystemMessage(creature, targetCreature, healedAttributes);
		return GENERALERROR;
	}

	return SUCCESS;
}

int ForceHealQueueCommand::doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

	if (creature == NULL || !creature->isPlayerCreature())
		return GENERALERROR;

	ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

	if (playerObject == NULL)
		return GENERALERROR;

	// do the common stuff
//	int comResult = doCommonMedicalCommandChecks(creature);
	int comResult = doCommonJediSelfChecks(creature);

	if (comResult != SUCCESS) {
#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[doQueueCommand] doCommonJediSelfChecks = " + String::valueOf(comResult));
#endif
		return comResult;
	}

	ManagedReference<CreatureObject*> targetCreature = NULL;
	bool isRemoteHeal = range > 0 && ((allowedTarget == TARGET_AUTO) || (allowedTarget & TARGET_OTHER));

#ifdef DEBUG_FORCE_HEALS
	creature->sendSystemMessage("[doQueueCommand] isRemotHeal = " + dbg_fh_bool2s(isRemoteHeal));
#endif
	if (isRemoteHeal) {
		targetCreature = NULL;
		// we are healing someone else
		if (target != 0) {
			ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(target);
			if (sceno != NULL && sceno->isCreatureObject()) {
				targetCreature = sceno.castTo<CreatureObject*>();
			}
		}
	}


	const bool selfHealingAllowed = (allowedTarget & TARGET_SELF) || !isRemoteHeal;
	if (
			// self healing as per range/TARGET_AUTO
			!isRemoteHeal ||
			// invalid target so we heal self
			(targetCreature == NULL && selfHealingAllowed) ||
			// we are attacking someone and try to heal ourself?
			// in the worst case we call isHealableBy(creature) twice (once here, once in runCommandWithTarget)
			(targetCreature != NULL && (!targetCreature->isHealableBy(creature)) && selfHealingAllowed)
	) {
#ifdef DEBUG_FORCE_HEALS
		creature->sendSystemMessage("[doQueueComand] targeting self for healing");
		creature->sendSystemMessage("[doQueueComand] selfHealingAllowed = " + dbg_fh_bool2s(selfHealingAllowed));
#endif
		isRemoteHeal = false;
		targetCreature = creature;
	}

	if (targetCreature == NULL) {
		// we couldn't find a valid target
		return GENERALERROR;
	}

	CreatureObject* targetC = targetCreature.get();

	int retval = GENERALERROR;
	// fork off the execution in a path that does cross locking for player2player heals
	// and one for self-heals

	if (isRemoteHeal)
		retval = runCommandWithTarget(creature, targetC);
	else
		retval = runCommand(creature, targetC);

	return retval;
}

void ForceHealQueueCommand::applyForceCost(CreatureObject* creature, int calculatedForceCost) const {
	ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
	if (playerObject == NULL) return;

	int currentForce = playerObject->getForcePower();
	if (currentForce < calculatedForceCost) {
		// this sucks, we did all this healing and now he suddenly doesn't
		// have enough force? :(
		playerObject->setForcePower(0);
		creature->error("Does not have enough force to pay for the healing he did...");
	} else {
		playerObject->setForcePower(currentForce - calculatedForceCost);
	}
}

