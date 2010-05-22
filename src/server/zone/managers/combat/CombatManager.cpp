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
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/Zone.h"

bool CombatManager::startCombat(CreatureObject* attacker, TangibleObject* defender) {
	if (attacker == defender)
		return false;

	bool success = true;

	if (!defender->isAttackableBy(attacker))
		return false;

	defender->wlock(attacker);

	try {

		attacker->setDefender(defender);
		defender->addDefender(attacker);

	} catch (...) {
		success = false;
	}

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

int CombatManager::calculateDamage(CreatureObject* attacker, CreatureObject* defender) {
	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	int damageType = weapon->getDamageType();
	int attackType = weapon->getAttackType();
	int armorPiercing = weapon->getArmorPiercing(); // None

	int damageMod = getDamageModifier(attacker, weapon);

	minDamage += damageMod;
	maxDamage += damageMod;

	int damage = 0;

	int diff = (int) maxDamage - (int) minDamage;

	if (diff >= 0)
		damage = System::random(diff) + (int) minDamage;

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor((PlayerCreature*) attacker))
			damage /= 5;
	}

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

int CombatManager::attemptCombatAction(CreatureObject* attacker, CreatureObject* defender) {
	int rand = System::random(100);

	if (rand > getHitChance(attacker, defender, attacker->getWeapon(), 0)) {
		//doMiss(attacker, defender, creature->getWeapon(), 0);
		return MISS;
	}

	return 0;
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
/*
void CombatManager::damageRandomPool(CreatureObject* defender, int damage, int healthPoolAttackChance = 50, int actionPoolAttackChance = 35, int mindPoolAttackChance = 15) {

}
*/
