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
#include "server/zone/objects/creature/NonPlayerCreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"

class CreatureAttackData;
class CombatQueueCommand;

class CombatManager : public Singleton<CombatManager>, public Logger, public Object {

public:
	const static int HIT = 0;
	const static int BLOCK = 1;
	const static int DODGE = 2;
	const static int COUNTER = 3;
	const static int MISS = 4;

	const static int HEALTH = 1;
	const static int ACTION = 2;
	const static int MIND = 4;
	const static int RANDOM = 8;

	const static int MELEEWEAPON = 0x1;
	const static int RANGEDWEAPON = 0x2;
	const static int THROWNWEAPON = 0x4;
	const static int HEAVYWEAPON = 0x8;;
	const static int MINE = 0x10;
	const static int SPECIALHEAVYWEAPON = 0x20;
	const static int ONEHANDMELEEWEAPON = 0x40;
	const static int TWOHANDMELEEWEAPON = 0x80;
	const static int POLEARM = 0x100;
	const static int PISTOL = 0x200;
	const static int CARBINE = 0x400;
	const static int RIFLE = 0x800;
	const static int GRENADE = 0x1000;
	const static int LIGHTNINGRIFLE = 0x2000;

public:
	CombatManager() {
		setLoggingName("CombatManager");
		setGlobalLogging(false);
		setLogging(false);
	}

	/**
	 * Attempts combat between 2 creature objects
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker attacking object
	 * @param defender defender object
	 * @param lockDefender will crosslock with attacker if true
	 * @return true on success
	 */
	bool startCombat(CreatureObject* attacker, TangibleObject* defender, bool lockDefender = true);

	/**
	 * Attempts to stop combat
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker CreatureObject that attempts peace state
	 * @return true on succes
	 */
	bool attemptPeace(CreatureObject* attacker);

	/**
	 * Forces clear combat
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker CreatureObject clears combat
	 */
	void forcePeace(CreatureObject* attacker);

	/**
	 * Attempts combat action
	 * @pre { attacker locked, defender unlocked }
	 * @post { attacker locked, defender unlocked }
	 * @param attacker Attacker trying the action
	 * @param defender Defender of the action
	 * @param poolsToDamage bitmask of what pool to damage (bit 1 health, 2 action, 4 mind, 8 random)
	 * @return returns -1 on failure to start combat or damage on succesfull combat
	 */
	int doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* command);
	int doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data);

	/**
	 * Requests duel
	 * @param player player that is trying to duel target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void requestDuel(CreatureObject* player, CreatureObject* targetPlayer);

	/**
	 * Requests end duel
	 * @param player player that is trying to end duel to target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void requestEndDuel(CreatureObject* player, CreatureObject* targetPlayer);

	/**
	 * Clears duel list
	 * @param player player to clear duel list
	 * @pre { player is locked }
	 * @post { player is locked }
	 */
	void freeDuelList(CreatureObject* player, bool spam = false);

	/**
	 * Declines duel
	 * @param player player that is trying to end duel to target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void declineDuel(CreatureObject* player, CreatureObject* targetPlayer);

	float calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio);

	//all the combat math will go here
protected:

	const static uint32 defaultAttacks[9];

	int doTargetCombatAction(CreatureObject* attacker, CreatureObject* defenderObject, const CreatureAttackData& data);
	int doAreaCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data);
	int doTargetCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data);
	void applyDots(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data, int appliedDamage);

	float getWeaponRangeModifier(float currentRange, WeaponObject* weapon);

	int applyDefensePenalties(CreatureObject* defender, int attackType, int defense);
	int applyAccuracyPenalties(CreatureObject* creature, int attackType, int accuracy);

	uint32 getDefaultAttackAnimation(CreatureObject* creature);

	/**
	 * @returns 0 - hit, 1 - block, 2 - dodge, 3 - counter-attack, 4 - miss
	 */
	int getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int accuracyBonus);

	float hitChanceEquation(float attackerAccuracy, float accuracyBonus, float targetDefense);
	int calculatePostureModifier(CreatureObject* creature);
	int calculateTargetPostureModifier(CreatureObject* creature, CreatureObject* targetCreature);

	int getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getDefenderDefenseModifier(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon);
	int getDefenderSecondaryDefenseModifier(CreatureObject* defender);
	int getDefenderToughnessModifier(CreatureObject* defender);
	int calculateDamageRange(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon);
	int getDamageModifier(CreatureObject* attacker, WeaponObject* weapon);
	int getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon);
	float calculateDamage(CreatureObject* attacker, CreatureObject* defender, int poolToDamage);
	float calculateDamage(CreatureObject* attacker, TangibleObject* defender);
	bool checkConeAngle(SceneObject* targetCreature, float angle, float creatureVectorX, float creatureVectorY, float directionVectorX, float directionVectorY);

	void doMiss(CreatureObject* attacker, CreatureObject* defender, int damage, const String& cbtSpam);
	void doCounterAttack(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam);
	void doBlock(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam);
	void doDodge(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam);

	int applyDamage(CreatureObject* attacker, TangibleObject* defender, float damageMultiplier, int poolsToDamage);
	int applyDamage(CreatureObject* attacker, CreatureObject* defender, float damageMultiplier, int poolsToDamage);
	void applyStates(CreatureObject* creature, CreatureObject* targetCreature, const CreatureAttackData& data);

	int getArmorObjectReduction(CreatureObject* attacker, ArmorObject* armor);
	int getArmorReduction(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon, float damage, int poolsToDamage);
	float getArmorPiercing(ArmorObject* armor, WeaponObject* weapon);
	float getArmorPiercing(AiAgent* defender, WeaponObject* weapon);
	int getArmorNpcReduction(CreatureObject* attacker, AiAgent* defender, WeaponObject* weapon);
	ArmorObject* getHealthArmor(CreatureObject* attacker, CreatureObject* defender);
	ArmorObject* getActionArmor(CreatureObject* attacker, CreatureObject* defender);
	ArmorObject* getMindArmor(CreatureObject* attacker, CreatureObject* defender);
	ArmorObject* getPSGArmor(CreatureObject* attacker, CreatureObject* defender);

	/**
	 * returns bitmask with what pools to damage
	 */
	int calculatePoolsToDamage(int poolsToDamage);

	/**
	 * returns false on insufficient
	 */
	bool applySpecialAttackCost(CreatureObject* attacker, const CreatureAttackData& data);

	void broadcastCombatSpam(CreatureObject* attacker, TangibleObject* defender, TangibleObject* weapon, uint32 damage, const String& stringid);

};


#endif /* COMBATMANAGER_H_ */
