/*
 * CombatManager.h
 *
 *  Created on: 21/01/2010
 *      Author: victor
 */

#ifndef COMBATMANAGER_H_
#define COMBATMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

class CombatManager : public Singleton<CombatManager>, public Logger {

public:
	const static int BLOCK = 1;
	const static int DODGE = 2;
	const static int COUNTER = 3;

public:
	CombatManager() {
		setLoggingName("CombatManager");
		setGlobalLogging(true);
		setLogging(true);
	}

	/**
	 * Attempts combat between 2 creature objects
	 * @pre { attacker locked, defender unlocked }
	 * @post { attacker locked, defender unlocked }
	 * @param attacker attacking object
	 * @param defender defender object
	 * @return true on success
	 */
	bool startCombat(CreatureObject* attacker, TangibleObject* defender);

	/**
	 * Attempts to stop combat
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker CreatureObject that attempts peace state
	 * @return true on succes
	 */
	bool attemptPeace(CreatureObject* attacker);

	/**
	 * Attempt
	 */

	//all the combat math will go here

	float getWeaponRangeModifier(float currentRange, WeaponObject* weapon);

	int applyDefensePenalties(CreatureObject* defender, int attackType, int defense);
	int applyAccuracyPenalties(CreatureObject* creature, int attackType, int accuracy);

	/**
	 * @returns % to hit
	 */
	int getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int accuracyBonus);

	/**
	 * returns 0 - hit, 1 - block, 2 - dodge, 3 - counter-attack
	 */
	int checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon);

	float hitChanceEquation(float attackerAccuracy, float accuracyBonus, float targetDefense, float defenseBonus);
	int calculatePostureModifier(CreatureObject* creature, CreatureObject* targetCreature);

	int getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getDefenderDefenseModifier(CreatureObject* defender, WeaponObject* weapon);
	int getDefenderSecondaryDefenseModifier(CreatureObject* defender, WeaponObject* weapon);
	int getDamageModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon);
	int calculateDamage(CreatureObject* attacker, CreatureObject* defender);
	float calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio);

	void broadcastCombatSpam(CreatureObject* attacker, TangibleObject* defender, TangibleObject* weapon, uint32 damage, const String& stringid);

	//TODO
	int calculateDamage(CreatureObject* attacker, TangibleObject* defender) {
		return 0;
	}

	/**
	 * Damage random pool target
	 * @pre { defender locked }
	 * @post { defender locked}
	 */
	//void damageRandomPool(CreatureObject* defender, int damage, int healthPoolAttackChance = 50, int actionPoolAttackChance = 35, int mindPoolAttackChance = 15);


};


#endif /* COMBATMANAGER_H_ */
