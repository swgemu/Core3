/*
 * CombatManager.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CombatManager.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/creature/UpdatePVPStatusMessage.h"
#include "server/zone/Zone.h"

const uint32 CombatManager::defaultAttacks[9] = {
		0x99476628, 0xF5547B91, 0x3CE273EC, 0x734C00C,
		0x43C4FFD0, 0x56D7CC78, 0x4B41CAFB, 0x2257D06B,
		0x306887EB
};


bool CombatManager::startCombat(CreatureObject* attacker, TangibleObject* defender, bool lockDefender) {
	if (attacker == defender)
		return false;

	bool success = true;

	if (!defender->isAttackableBy(attacker))
		return false;

	attacker->clearState(CreatureState::PEACE);

	if (lockDefender)
		defender->wlock(attacker);

	try {

		attacker->setDefender(defender);
		defender->addDefender(attacker);

	} catch (...) {
		success = false;
	}

	if (lockDefender)
		defender->unlock();

	return success;
}

bool CombatManager::attemptPeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* defender = (TangibleObject*) object.get();

		try {
			defender->wlock(attacker);

			if (defender->hasDefender(attacker)) {

				if (defender->isCreatureObject()) {
					CreatureObject* creature = (CreatureObject*) defender;

					if (creature->hasState(CreatureState::PEACE)) {
						attacker->removeDefender(defender);
						defender->removeDefender(attacker);

						--i;
					}
				} else {
					attacker->removeDefender(defender);
					defender->removeDefender(attacker);

					--i;
				}
			} else {
				attacker->removeDefender(defender);
				--i;
			}

			defender->unlock();

		} catch (...) {
			error("unknown exception in PlayerImplementation::doPeace()\n");
			defender->unlock();
		}

	}

	if (defenderList->size() != 0) {
		//info("defenderList not empty, trying to set Peace State");

		attacker->setState(CreatureState::PEACE);

		return false;
	} else {
		attacker->clearCombatState(false);

		return true;
	}
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* command) {
	if (!startCombat(attacker, defenderObject))
		return -1;

	if (!applySpecialAttackCost(attacker, command))
		return -2;

	if (attacker->hasAttackDelay())
		return -3;

	if (attacker->isBerserked() && command->getNameCRC() != 0xA8FEF90A) //berserk only works with attack
		return -3;

	int damage = 0;

	if (command->isAreaAction() || command->isConeAction())
		damage = doAreaCombatAction(attacker, defenderObject, command);
	else
		damage = doTargetCombatAction(attacker, defenderObject, command);

	CombatAction* combatAction = NULL;

	uint32 animationCRC = command->getAnimationCRC();

	if (animationCRC == 0)
		animationCRC = getDefaultAttackAnimation(attacker);

	uint8 hit = damage != 0 ? 1 : 0;

	if (defenderObject->isCreatureObject()) {
		combatAction = new CombatAction(attacker, (CreatureObject*)defenderObject, animationCRC, hit);
	} else {
		combatAction = new CombatAction(attacker, command->getAnimationCRC());
	}

	attacker->broadcastMessage(combatAction, true);

	String effect = command->getEffectString();

	if (!effect.isEmpty())
		attacker->playEffect(effect);

	return damage;
}

int CombatManager::doTargetCombatAction(CreatureObject* attacker, TangibleObject* tano, CombatQueueCommand* command) {
	int damage = 0;

	try {
		tano->wlock(attacker);

		if (tano->isCreatureObject()) {
			CreatureObject* defender = (CreatureObject*) tano;

			damage = doTargetCombatAction(attacker, defender, command);
		} else {
			int poolsToDamage = calculatePoolsToDamage(command->getPoolsToDamage());

			damage = applyDamage(attacker, tano, damage, poolsToDamage);

			broadcastCombatSpam(attacker, tano, attacker->getWeapon(), damage, command->getCombatSpam() + "_hit");
		}

		tano->unlock();
	} catch (...) {
		tano->unlock();
	}

	return damage;
}

int CombatManager::doTargetCombatAction(CreatureObject* attacker, CreatureObject* defender,  CombatQueueCommand* command) {
	int rand = System::random(100);

	int poolsToDamage = calculatePoolsToDamage(command->getPoolsToDamage());

	if (poolsToDamage != 0 && rand > getHitChance(attacker, defender, attacker->getWeapon(), 0)) {
		//better luck next time
		doMiss(attacker, defender, 0, command->getCombatSpam() + "_miss");
		return 0;
	}

	int damage = 0;

	String combatSpam = command->getCombatSpam();
	float damageMultiplier = (float) command->getDamageMultiplier();

	if (damageMultiplier != 0 && poolsToDamage != 0) {
		int secondaryDefense = checkSecondaryDefenses(attacker, defender, attacker->getWeapon());

		if (secondaryDefense != 0) {
			switch (secondaryDefense) {
			case BLOCK:
				damageMultiplier /= 2.f;
				doBlock(attacker, defender, damage, combatSpam + "_block");
				break;
			case DODGE:
				doDodge(attacker, defender, damage, combatSpam + "_evade");
				return 0;
				break;
			case COUNTER:
				doCounterAttack(attacker, defender, damage, combatSpam + "_counter");
				return 0;
				break;
			default:
				break;
			}
		}

		damage = applyDamage(attacker, defender, damageMultiplier, poolsToDamage);
	}

	applyStates(attacker, defender, command);

	broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, combatSpam + "_hit");

	return 0;
}

float CombatManager::getWeaponRangeModifier(float currentRange, WeaponObject* weapon) {
	float accuracy;

	float smallRange = 0;
	float idealRange = 2;
	float maxRange = 5;

	float smallMod = 7;
	float bigMod = 7;

	if (weapon != NULL) {
		smallRange = (float) weapon->getPointBlankRange();
		idealRange = (float) weapon->getIdealRange();
		maxRange = (float) weapon->getMaxRange();

		smallMod = (float) weapon->getPointBlankAccuracy();
		bigMod = (float) weapon->getIdealAccuracy();
	}

	if (currentRange > idealRange) {
		if (weapon != NULL) {
			smallMod = (float) weapon->getIdealAccuracy();
			bigMod = (float) weapon->getMaxRangeAccuracy();
		}

		idealRange = maxRange;
	}

	accuracy = smallMod + ((currentRange - smallRange) / (idealRange
			- smallRange) * (bigMod - smallMod));

	return accuracy;
}

int CombatManager::calculatePostureModifier(CreatureObject* creature, CreatureObject* targetCreature) {
	int accuracy = 0;
	WeaponObject* weapon = creature->getWeapon();

	if (targetCreature->isKneeling()) {
		if (weapon->hasMeleeAttack())
			accuracy += 16;
		else
			accuracy -= 16;
	} else if (targetCreature->isProne()) {
		if (weapon->hasMeleeAttack())
			accuracy += 25;
		else
			accuracy -= 25;
	}

	if (creature->isKneeling()) {
		if (weapon->hasMeleeAttack())
			accuracy -= 16;
		else
			accuracy += 16;
	} else if (creature->isProne()) {
		if (weapon->hasMeleeAttack())
			accuracy -= 50;
		else
			accuracy += 50;
	}

	return accuracy;
}

int CombatManager::getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int attackerAccuracy = 0;

	Vector<String>* creatureAccMods = weapon->getCreatureAccuracyModifiers();

	for (int i = 0; i < creatureAccMods->size(); ++i) {
		attackerAccuracy += attacker->getSkillMod(creatureAccMods->get(i));
	}

	return attackerAccuracy;
}

int CombatManager::getDefenderDefenseModifier(CreatureObject* defender, WeaponObject* weapon) {
	int targetDefense = 0;

	Vector<String>* defenseAccMods = weapon->getDefenderDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		targetDefense += defender->getSkillMod(defenseAccMods->get(i));
	}

	return targetDefense;
}

int CombatManager::getDefenderSecondaryDefenseModifier(CreatureObject* defender, WeaponObject* weapon) {
	int targetDefense = 0;

	Vector<String>* defenseAccMods = weapon->getDefenderSecondaryDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		targetDefense += defender->getSkillMod(defenseAccMods->get(i));
	}

	return targetDefense;
}

float CombatManager::hitChanceEquation(float attackerAccuracy,
		float accuracyBonus, float targetDefense, float defenseBonus) {

	float accTotal = 66.0 + (attackerAccuracy + accuracyBonus - targetDefense
			- defenseBonus) / 2.0;

	StringBuffer msg;
	msg << "HitChance\n";
	msg << "\tTarget Defense " << targetDefense << "\n";
	msg << "\tTarget Defense Bonus" << defenseBonus << "\n";

	info(msg.toString());

	return accTotal;
}

int CombatManager::getDamageModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int damageMods = 0;

	Vector<String>* weaponDamageMods = weapon->getDamageModifiers();

	for (int i = 0; i < weaponDamageMods->size(); ++i) {
		damageMods += attacker->getSkillMod(weaponDamageMods->get(i));
	}

	return damageMods;
}

int CombatManager::getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int speedMods = 0;

	Vector<String>* weaponSpeedMods = weapon->getSpeedModifiers();

	for (int i = 0; i < weaponSpeedMods->size(); ++i) {
		speedMods += attacker->getSkillMod(weaponSpeedMods->get(i));
	}

	return speedMods;
}

int CombatManager::getArmorObjectReduction(CreatureObject* attacker, ArmorObject* armor) {
	WeaponObject* weapon = attacker->getWeapon();

	int damageType = weapon->getDamageType();

	int resist = 0;

	switch (damageType) {
	case WeaponObject::KINETIC:
		resist = armor->getKinetic();
		break;
	case WeaponObject::ENERGY:
		resist = armor->getEnergy();
		break;
	case WeaponObject::ELECTRICITY:
		resist = armor->getElectricity();
		break;
	case WeaponObject::STUN:
		resist = armor->getStun();
		break;
	case WeaponObject::BLAST:
		resist = armor->getBlast();
		break;
	case WeaponObject::HEAT:
		resist = armor->getHeat();
		break;
	case WeaponObject::COLD:
		resist = armor->getCold();
		break;
	case WeaponObject::ACID:
		resist = armor->getAcid();
		break;
	case WeaponObject::LIGHTSABER:
		resist = armor->getLightSaber();
		break;
	case WeaponObject::FORCE:
		resist = 0;
		break;
	}

	return resist;

}

int CombatManager::getHealthArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	int reduction = 0;

	SceneObject* chest = defender->getSlottedObject("chest2");
	/*SceneObject* bicepr = defender->getSlottedObject("bicep_r");
	SceneObject* bicepl = defender->getSlottedObject("bicep_l");
	SceneObject* bracerr = defender->getSlottedObject("bracer_upper_r");
	SceneObject* bracerl = defender->getSlottedObject("bracer_upper_l");*/

	ArmorObject* armorToHit = NULL;

	if (chest != NULL && chest->isArmorObject())
		armorToHit = (ArmorObject*) chest;

	/*int rand = System::random(100);

	if (rand < 20) { // chest
		if (chest != NULL && chest->isArmorObject())
			armorToHit = (ArmorObject*) chest;
	} else if (rand < 40) { // bicepr
		if (bicepr != NULL && bicepr->isArmorObject())
			armorToHit = (ArmorObject*) bicepr;
	} else if (rand < 60) { // bicepl
		if (bicepl != NULL && bicepl->isArmorObject())
			armorToHit = (ArmorObject*) bicepl;
	} else if (rand < 80) { // bracerr
		if (bracerr != NULL && bracerr->isArmorObject())
			armorToHit = (ArmorObject*) bracerr;
	} else { //bracerl
		if (bracerl != NULL && bracerl->isArmorObject())
			armorToHit = (ArmorObject*) bracerl;
	}*/

	if (armorToHit == NULL)
		return 0;

	return getArmorObjectReduction(attacker, armorToHit);
}

int CombatManager::getActionArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* gloves = defender->getSlottedObject("gloves");
	SceneObject* boots = defender->getSlottedObject("shoes");

	ArmorObject* armorToHit = NULL;

	int rand = System::random(1);

	if (rand == 1) {
		if (gloves != NULL && gloves->isArmorObject())
			armorToHit = (ArmorObject*) gloves;
	} else {
		if (boots != NULL && boots->isArmorObject())
			armorToHit = (ArmorObject*) boots;
	}

	if (armorToHit == NULL)
		return 0;

	return getArmorObjectReduction(attacker, armorToHit);
}

int CombatManager::getMindArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* helmet = defender->getSlottedObject("hat");

	if (helmet != NULL && helmet->isArmorObject())
		return getArmorObjectReduction(attacker, (ArmorObject*) helmet);

	return 0;
}

int CombatManager::getArmorReduction(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon, float damage, int poolToDamage) {
	if (poolToDamage == 0)
		return 0;

	if (poolToDamage & CombatManager::HEALTH) {
		return getHealthArmorReduction(attacker, defender);
	} else if (poolToDamage & CombatManager::ACTION) {
		return getActionArmorReduction(attacker, defender);
	} else if (poolToDamage & CombatManager::MIND) {
		return getMindArmorReduction(attacker, defender);
	} else
		return 0;
}

float CombatManager::calculateDamage(CreatureObject* attacker, CreatureObject* defender, int poolToDamage) {
	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	int damageType = weapon->getDamageType();
	int attackType = weapon->getAttackType();
	int armorPiercing = weapon->getArmorPiercing(); // None

	int damageMod = getDamageModifier(attacker, weapon);

	minDamage += damageMod;
	maxDamage += damageMod;

	float damage = 0;

	int diff = (int) maxDamage - (int) minDamage;

	if (diff >= 0)
		damage = System::random(diff) + (int) minDamage;

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor((PlayerCreature*) attacker))
			damage /= 5;

		int FR = attacker->getSkillMod("force_run");

		if (FR > 1)
			damage /= 4;
	}

	if (attacker->isIntimidated())
		damage /= 2;

	if (attacker->isStunned())
		damage /= 2;

	if (defender->isKnockedDown())
		damage *= 1.333f;

	float armorReduction = getArmorReduction(attacker, defender, weapon, damage, poolToDamage);

	if (armorReduction > 0)
		damage *= (armorReduction /= 100.f);

	if (defender->isBerserked()) {
		damage += 50;
	}

	//damage = damage * ((float) getArmorReduction(attacker, defender, weapon, damage, poolToDamage) / 100.f);

	return damage;
}

int CombatManager::applyAccuracyPenalties(CreatureObject* creature, int attackType, int accuracy) {
	if (creature->isBerserked() && attackType == WeaponObject::MELEEATTACK)
		accuracy -= 10;

	if (creature->isBlinded())
		accuracy -= 50;

	return accuracy;
}

int CombatManager::applyDefensePenalties(CreatureObject* defender, int attackType, int defense) {
	if (defender->isInCover())
		defense += 10;

	if (defender->isStunned())
		defense -= 50;

	return defense;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int accuracyBonus) {
	int hitChance = 0;
	int attackType = weapon->getAttackType();

	info("Calculating hit chance");

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy));

	float aimMod = 0.0;
	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	if (creature->isBerserked() && attackType == WeaponObject::MELEEATTACK) {
		attackerAccuracy -= 10;
	}

	info("Base attacker accuracy is " + String::valueOf(attackerAccuracy));

	int targetDefense = getDefenderDefenseModifier(targetCreature, weapon);

	info("Base target defense is " + String::valueOf(targetDefense));

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	/*if (creature->isAiming() && creature->getAimMod() > 0) {
		aimMod = (float) creature->getAimMod();

		if (DEBUG)
			System::out << "\tAttacker aiming mod is " << aimMod << endl;

		creature->clearState(CreatureState::AIMING);
	}*/

	if (targetDefense > 125)
		targetDefense = 125;

	info("Target defense after state affects and cap is " +  String::valueOf(targetDefense));

	float defenseBonus = 0.0f; // TODO: Food/drink defense bonuses go here

	//Food dodge bonus.
	/*if (targetCreature->hasBuff(BuffCRC::FOOD_DODGE_ATTACK)) {
		Buff* buff = targetCreature->getBuff(BuffCRC::FOOD_DODGE_ATTACK);

		if (buff != NULL)
			defenseBonus += buff->getSkillModifierValue("dodge_attack");
	}*/

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy
			+ accuracyBonus + aimMod, targetDefense, defenseBonus);

	info("Final hit chance is " + String::valueOf(accTotal));

	if (accTotal > 100)
		accTotal = 100.0;
	else if (accTotal < 0)
		accTotal = 0;

	hitChance = (int) accTotal;

	return hitChance;
}

int CombatManager::checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon) {
	int hitChance = 0;
	int attackType = weapon->getAttackType();

	info("Calculating secondary hit chance");

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy));

	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	info("Base attacker accuracy is " + String::valueOf(attackerAccuracy));

	int targetDefense = getDefenderSecondaryDefenseModifier(targetCreature, weapon);

	if (targetCreature->isPlayerCreature())
		targetDefense += ((PlayerCreature*)targetCreature)->getCenteredBonus();

	info("Base target secondary defense is " + String::valueOf(targetDefense));

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	if (targetDefense > 125)
		targetDefense = 125;

	info("Target secondary defense after state affects and cap is " +  String::valueOf(targetDefense));

	if (targetDefense <= 0)
		return 0;

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy, targetDefense, 0);

	int rand = System::random(100);

	if (rand <= (int) accTotal) // Hit, not defended
		return 0;

	Vector<String>* defenseAccMods = weapon->getDefenderSecondaryDefenseModifiers();

	int selectOption = defenseAccMods->size();

	if (selectOption > 1)
		selectOption = System::random(selectOption - 1);
	else
		selectOption = 0;

	String def = defenseAccMods->get(selectOption);

	if (def == "block") {
		return BLOCK;
	} else if (def == "dodge") {
		return DODGE;
	} else if (def == "counterattack") {
		return COUNTER;
	} else
		return COUNTER;
}

float CombatManager::calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio) {
	int speedMod = getSpeedModifier(attacker, weapon);

	float attackSpeed = (1.0f - ((float) speedMod / 100.0f)) * skillSpeedRatio * weapon->getAttackSpeed();

	return MAX(attackSpeed, 1.0f);
}

void CombatManager::doMiss(CreatureObject* attacker, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "miss", 0xFF, 0xFF, 0xFF);

	broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, cbtSpam);
}

void CombatManager::doCounterAttack(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "counterattack", 0, 0xFF, 0);
	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doBlock(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "block", 0, 0xFF, 0);

	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doDodge(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "dodge", 0, 0xFF, 0);

	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

bool CombatManager::applySpecialAttackCost(CreatureObject* attacker, CombatQueueCommand* command) {

	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();

	int health = weapon->getHealthAttackCost() * command->getHealthCostMultiplier();
	int action = weapon->getActionAttackCost() * command->getActionCostMultiplier();
	int mind = weapon->getMindAttackCost() * command->getMindCostMultiplier();
	int force = weapon->getForceCost() * command->getForceCostMultiplier();

	if (health > 0) {
		if (attacker->getHAM(CreatureAttribute::HEALTH) <= health)
			return false;

		attacker->inflictDamage(CreatureAttribute::HEALTH, health, true);
	}

	if (action > 0) {
		if (attacker->getHAM(CreatureAttribute::ACTION) <= action)
			return false;

		attacker->inflictDamage(attacker, CreatureAttribute::ACTION, action, true);
	}

	if (mind > 0) {
		if (attacker->getHAM(CreatureAttribute::MIND) <= mind)
			return false;

		attacker->inflictDamage(attacker, CreatureAttribute::MIND, mind, true);
	}

	if (force > 0) {
		//TODO: add force withdrawal
	}

	return true;
}

void CombatManager::checkKnockDown(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (creature->isPlayerCreature() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
		if (80 > System::random(100))
			targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	if (targetCreature->checkKnockdownRecovery() && targetCreature->checkLastKnockdown()) {
		int targetDefense = targetCreature->getSkillMod("knockdown_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());
		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			targetCreature->setPosture(CreaturePosture::KNOCKEDDOWN);
			targetCreature->updateKnockdownRecovery();
			targetCreature->updateLastKnockdown();
			targetCreature->sendSystemMessage("cbt_spam", "posture_knocked_down");

			int combatEquil = targetCreature->getSkillMod("combat_equillibrium");

			if (combatEquil > 100)
				combatEquil = 100;

			if ((combatEquil >> 1) > (int) System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		}
	} else
		creature->sendSystemMessage("cbt_spam", "knockdown_fail");
}


void CombatManager::checkPostureDown(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (creature->isPlayerCreature() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
		if (80 > System::random(100))
			targetCreature->setPosture(CreaturePosture::UPRIGHT, true);

		return;
	}

	if (targetCreature->checkPostureDownRecovery()) {
		int targetDefense = targetCreature->getSkillMod(
				"posture_change_down_defense");
		targetDefense -= (int) (targetDefense
				* targetCreature->calculateBFRatio());

		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			if (targetCreature->getPosture() == CreaturePosture::UPRIGHT)
				targetCreature->setPosture(CreaturePosture::CROUCHED);
			else
				targetCreature->setPosture(CreaturePosture::PRONE);

			targetCreature->updatePostureDownRecovery();
			targetCreature->sendSystemMessage("cbt_spam", "posture_down");

			int combatEquil =
					targetCreature->getSkillMod("combat_equillibrium");

			if (combatEquil > 100)
				combatEquil = 100;

			if ((combatEquil >> 1) > (int) System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		}
	} else
		creature->sendSystemMessage("cbt_spam", "posture_change_fail");
}

void CombatManager::checkPostureUp(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (targetCreature->checkPostureUpRecovery()) {
		int targetDefense = targetCreature->getSkillMod(
				"posture_change_up_defense");
		targetDefense -= (int) (targetDefense
				* targetCreature->calculateBFRatio());

		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			if (targetCreature->getPosture() == CreaturePosture::PRONE) {
				targetCreature->setPosture(CreaturePosture::CROUCHED);
				targetCreature->updatePostureUpRecovery();
			} else if (targetCreature->getPosture()
					== CreaturePosture::CROUCHED) {
				targetCreature->setPosture(CreaturePosture::UPRIGHT);
				targetCreature->updatePostureUpRecovery();
			}
		}
	} else if (!targetCreature->checkPostureUpRecovery())
		creature->sendSystemMessage("cbt_spam", "posture_change_fail");
}

void CombatManager::applyStates(CreatureObject* creature, CreatureObject* targetCreature, CombatQueueCommand* tskill) {
	// TODO: None of these equations seem correct except intimidate
	int chance = 0;
	if ((chance = tskill->getKnockdownChance()) > 0)
		checkKnockDown(creature, targetCreature, chance);
	if ((chance = tskill->getPostureDownChance()) > 0)
		checkPostureDown(creature, targetCreature, chance);
	if ((chance = tskill->getPostureUpChance()) > 0)
		checkPostureUp(creature, targetCreature, chance);

	if (tskill->getDizzyChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("blind_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(0.0f, 0.0f, targetDefense, defenseBonus))
			targetCreature->setDizziedState(tskill->getDurationStateTime());
	}

	if (tskill->getBlindChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("blind_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(0.0f, 0.0f, targetDefense, defenseBonus))
			targetCreature->setBlindedState(tskill->getDurationStateTime());
	}

	if (tskill->getStunChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("blind_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(0.0f, 0.0f, targetDefense, defenseBonus))
			targetCreature->setStunnedState(tskill->getDurationStateTime());
	}

	if ((chance = tskill->getIntimidateChance()) > 0) {
		int targetDefense = targetCreature->getSkillMod("intimidate_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(chance, 0.0f, targetDefense, defenseBonus)) {
			targetCreature->setIntimidatedState(tskill->getDurationStateTime());
		} else
			targetCreature->showFlyText("combat_effects", "intimidated_miss", 0xFF, 0, 0);
	}

	if ((chance = tskill->getNextAttackDelayChance()) > 0) {
		int targetDefense = targetCreature->getSkillMod("warcry_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(chance, 0.0f, targetDefense, defenseBonus)) {
			targetCreature->setNextAttackDelay(tskill->getDurationStateTime());
		} else
			targetCreature->showFlyText("combat_effects", "warcry_miss", 0xFF, 0, 0);
	}
}

int CombatManager::calculatePoolsToDamage(int poolsToDamage) {
	if (poolsToDamage & RANDOM) {
		int rand = System::random(100);

		if (rand < 50) {
			poolsToDamage = HEALTH;
		} else if (rand < 85) {
			poolsToDamage = ACTION;
		} else {
			poolsToDamage = MIND;
		}
	}

	return poolsToDamage;
}

int CombatManager::applyDamage(CreatureObject* attacker, CreatureObject* defender, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0 || damageMultiplier == 0)
		return 0;

	float damage = 0;

	if (poolsToDamage & HEALTH) {
		damage += calculateDamage(attacker, defender, HEALTH) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::HEALTH, damage, true);
	}

	if (poolsToDamage & ACTION) {
		damage += calculateDamage(attacker, defender, ACTION) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::ACTION, damage, true);
	}

	if (poolsToDamage & MIND) {
		damage += calculateDamage(attacker, defender, MIND) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::MIND, damage, true);
	}

	return damage;
}

int CombatManager::applyDamage(CreatureObject* attacker, TangibleObject* defender, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0)
		return 0;

	int damage = System::random(1000);

	defender->inflictDamage(0, damage, true);

	return damage;
}

int CombatManager::doAreaCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* command) {
	float creatureVectorX = attacker->getPositionX();
	float creatureVectorY = attacker->getPositionY();

	float directionVectorX = defenderObject->getPositionX() - creatureVectorX;
	float directionVectorY = defenderObject->getPositionY() - creatureVectorY;

	Zone* zone = attacker->getZone();

	if (zone == NULL)
		return 0;

	int damage = 0;

	int range = command->getAreaRange();

	try {
		zone->rlock();

		for (int i = 0; i < attacker->inRangeObjectCount(); i++) {
			ManagedReference<SceneObject*> object = (SceneObject*) (((SceneObjectImplementation*) attacker->getInRangeObject(i))->_this);

			if (!object->isTangibleObject())
				continue;

			TangibleObject* tano = (TangibleObject*) object.get();

			if (object == attacker)
				continue;

			if (!attacker->isInRange(object, range))
				continue;

			if (!tano->isAttackableBy(attacker))
				continue;

			if (command->isConeAction() && !checkConeAngle(tano, command->getConeAngle(), creatureVectorX, creatureVectorY, directionVectorX,
					directionVectorY))
				continue;

			zone->runlock();

			try {
				damage += doTargetCombatAction(attacker, tano, command);
			} catch (...) {
				error("unreported exception caught in CombatManager::doAreaCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* commmand) executing doTargetCombatAction");
			}

			zone->rlock();
		}

		zone->runlock();
	} catch (...) {
		error("unreported exception caught in CombatManager::doAreaCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* commmand)");

		zone->runlock();
	}

	return damage;
}

void CombatManager::broadcastCombatSpam(CreatureObject* attacker, TangibleObject* defender, TangibleObject* weapon, uint32 damage, const String& stringid) {
	Zone* zone = attacker->getZone();

	Locker _locker(zone);

	for (int i = 0; i < attacker->inRangeObjectCount(); ++i) {
		SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) attacker->getInRangeObject(i))->_this);

		if (object->isPlayerCreature() && attacker->isInRange(object, 70)) {
			PlayerCreature* player = (PlayerCreature*) object;

			CombatSpam* msg = new CombatSpam(attacker, defender, weapon, damage, "cbt_spam", stringid, player);
			player->sendMessage(msg);
		}
	}
}


void CombatManager::requestDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requests duel to targetPlayer
	 */

	try {
		targetPlayer->wlock(player);

		if (player->requestedDuelTo(targetPlayer)) {
			ParameterizedStringId stringId("duel", "already_challenged");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->unlock();
			return;
		}

		player->info("requesting duel");

		player->addToDuelList(targetPlayer);

		if (targetPlayer->requestedDuelTo(player)) {
			BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer,
					targetPlayer->getPvpStatusBitmask()
							+ CreatureFlag::ATTACKABLE
							+ CreatureFlag::AGGRESSIVE);
			player->sendMessage(pvpstat);

			ParameterizedStringId stringId("duel", "accept_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player,
					player->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE
							+ CreatureFlag::AGGRESSIVE);
			targetPlayer->sendMessage(pvpstat2);

			ParameterizedStringId stringId2("duel", "accept_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		} else {
			ParameterizedStringId stringId3("duel", "challenge_self");
			stringId3.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId3);

			ParameterizedStringId stringId4("duel", "challenge_target");
			stringId4.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId3);
		}

		targetPlayer->unlock();
	} catch (Exception& e) {
		targetPlayer->unlock();

		StringBuffer msg;
		msg << "Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n"
				<< e.getMessage();

		error(msg.toString());
	} catch (...) {
		targetPlayer->unlock();

		StringBuffer msg;
		msg << "Unreported Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n";

		error(msg.toString());
	}
}

void CombatManager::requestEndDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requested to end the duel with targetPlayer
	 */

	try {
		targetPlayer->wlock(player);

		if (!player->requestedDuelTo(targetPlayer)) {
			ParameterizedStringId stringId("duel", "not_dueling");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->unlock();
			return;
		}

		player->info("ending duel");

		player->removeFromDuelList(targetPlayer);

		if (targetPlayer->requestedDuelTo(player)) {
			targetPlayer->removeFromDuelList(player);

			player->sendPvpStatusTo(targetPlayer);

			ParameterizedStringId stringId("duel", "end_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->sendPvpStatusTo(player);

			ParameterizedStringId stringId2("duel", "end_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		}

		targetPlayer->unlock();
	} catch (...) {
		targetPlayer->unlock();
	}
}

void CombatManager::freeDuelList(PlayerCreature* player, bool spam) {
	/* Pre: player not NULL and is locked
	 * Post: player removed and warned all of the objects from its duel list
	 */
	if (player->isDuelListEmpty())
		return;

	player->info("freeing duel list");

	while (player->getDuelListSize() != 0) {
		ManagedReference<PlayerCreature*> targetPlayer = player->getDuelListObject(0);

		if (targetPlayer != NULL && targetPlayer.get() != player) {
			try {
				targetPlayer->wlock(player);

				player->removeFromDuelList(targetPlayer);

				if (targetPlayer->requestedDuelTo(player)) {
					targetPlayer->removeFromDuelList(player);

					player->sendPvpStatusTo(targetPlayer);

					if (spam) {
						ParameterizedStringId stringId("duel", "end_self");
						stringId.setTT(targetPlayer->getObjectID());
						player->sendSystemMessage(stringId);
					}

					targetPlayer->sendPvpStatusTo(player);

					if (spam) {
						ParameterizedStringId stringId2("duel", "end_target");
						stringId2.setTT(player->getObjectID());
						targetPlayer->sendSystemMessage(stringId2);
					}
				}


				targetPlayer->unlock();
			} catch (ObjectNotDeployedException& e) {
				player->removeFromDuelList(targetPlayer);

				System::out << "Exception on CombatManager::freeDuelList()\n"
						<< e.getMessage() << "\n";
			} catch (...) {
				targetPlayer->unlock();
			}
		}
	}
}

void CombatManager::declineDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player declined Duel to targetPlayer
	 */

	try {
		targetPlayer->wlock(player);

		if (targetPlayer->requestedDuelTo(player)) {
			targetPlayer->removeFromDuelList(player);

			ParameterizedStringId stringId("duel", "cancel_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			ParameterizedStringId stringId2("duel", "cancel_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		}

		targetPlayer->unlock();
	} catch (...) {
		targetPlayer->unlock();
	}
}

bool CombatManager::checkConeAngle(SceneObject* target, float angle,
		float creatureVectorX, float creatureVectorY, float directionVectorX,
		float directionVectorY) {
	float Target1 = target->getPositionX() - creatureVectorX;
	float Target2 = target->getPositionY() - creatureVectorY;

	float resAngle = atan2(Target2, Target1) - atan2(directionVectorY, directionVectorX);
	float degrees = resAngle * 180 / M_PI;

	float coneAngle = angle / 2;

	if (angle > coneAngle || angle < -coneAngle)
		return false;

	return true;
}

uint32 CombatManager::getDefaultAttackAnimation(CreatureObject* creature) {
	WeaponObject* weapon = creature->getWeapon();

	if (weapon->isRangedWeapon())
		return 0x506E9D4C;
	else {
		int choice = System::random(8);
		return defaultAttacks[choice];
	}
}
