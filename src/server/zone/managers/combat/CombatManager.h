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
	CombatManager() {
		setLoggingName("CombatManager");
		setGlobalLogging(true);
		setLogging(false);
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

	float getWeaponRangeModifier(float currentRange, WeaponObject* weapon);

	int getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int accuracyBonus);
	float hitChanceEquation(float attackerAccuracy, float accuracyBonus, float targetDefense, float defenseBonus);
	int calculatePostureModifier(CreatureObject* creature, CreatureObject* targetCreature);

	int getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getDefenderDefenseModifier(CreatureObject* defender, WeaponObject* weapon);
	int getDamageModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon);
	int calculateDamage(CreatureObject* attacker, CreatureObject* defender);

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

	//all the combat math will go here
};


#endif /* COMBATMANAGER_H_ */
