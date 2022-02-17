/*
 * CombatManager.h
 *
 *  Created on: 21/01/2010
 *      Author: victor
 */

#ifndef COMBATMANAGER_H_
#define COMBATMANAGER_H_

#include "DefenderHitList.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"

class CreatureAttackData;
class CombatQueueCommand;

class CombatManager : public Singleton<CombatManager>, public Logger, public Object {

public:
	// hitstatus: 0x0-MISS 0x1-HIT 0x2-BLOCK 0x3-DODGE 0x5-COUNTER 0x7-RICOCHET 0x8-REFLECT 0x9-REFLECT_TO_TARGET
	const static int MISS = 0x00;
	const static int HIT = 0x01;
	const static int BLOCK = 0x02;
	const static int DODGE = 0x03;
	const static int COUNTER = 0x05;
	const static int RICOCHET = 0x07;
	const static int REFLECT = 0x08;
	const static int REFLECT_TO_TARGET = 0x09;

	// trails bitmask
	const static int NOTRAIL = 0x00;
	const static int LEFTFOOTTRAIL = 0x01;
	const static int RIGHTFOOTTRAIL = 0x02;
	const static int LEFTHANDTRAIL = 0x04;
	const static int RIGHTHANDTRAIL = 0x08;
	const static int WEAPONTRAIL = 0x10;
	const static int DEFAULTTRAIL = 0xFF;

	const static int NONE = 0;
	const static int HEALTH = 1;
	const static int ACTION = 2;
	const static int MIND = 4;
	const static int RANDOM = 8;

	// hitLocations
	enum HitLocations { HIT_NONE, HIT_BODY, HIT_LARM, HIT_RARM, HIT_LLEG, HIT_RLEG, HIT_HEAD };

	//Mitigation types
	const static int PSG = 0x1;
	const static int FORCESHIELD = 0x02;
	const static int FORCEFEEDBACK = 0x03;
	const static int FORCEABSORB = 0x04;
	const static int FORCEARMOR = 0x5;
	const static int ARMOR = 0x6;
	const static int FOOD = 0x7;

	Vector<uint32> defaultMeleeAttacks;
	Vector<uint32> defaultRangedAttacks;

private:
	void initializeDefaultAttacks();

public:
	CombatManager() {
		setLoggingName("CombatManager");
		setGlobalLogging(false);
		setLogging(false);
		initializeDefaultAttacks();
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
	bool startCombat(CreatureObject* attacker, TangibleObject* defender, bool lockDefender = true, bool allowIncapTarget = false) const;

	/**
	 * Attempts to stop combat
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker CreatureObject that attempts peace state
	 * @return true on succes
	 */
	bool attemptPeace(CreatureObject* attacker) const;

	/**
	 * Forces clear combat
	 * @param attacker CreatureObject clears combat
	 */
	void forcePeace(CreatureObject* attacker) const;

	/**
	 * Attempts combat action
	 * @pre { attacker locked, defender unlocked }
	 * @post { attacker locked, defender unlocked }
	 * @param attacker Attacker trying the action
	 * @param defender Defender of the action
	 * @param poolsToDamage bitmask of what pool to damage (bit 1 health, 2 action, 4 mind, 8 random)
	 * @return returns -1 on failure to start combat or damage on succesfull combat
	 */
	int doCombatAction(TangibleObject* attacker, WeaponObject* weapon, TangibleObject* defenderObject, const CombatQueueCommand* command) const;
	int doCombatAction(CreatureObject* attacker, WeaponObject* weapon, TangibleObject* defenderObject, const CreatureAttackData& data) const;

	Reference<SortedVector<ManagedReference<TangibleObject*> >* > getAreaTargets(TangibleObject* attacker, WeaponObject* weapon, TangibleObject* defenderObject, const CreatureAttackData& data) const;

	/**
	 * Requests duel
	 * @param player player that is trying to duel target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void requestDuel(CreatureObject* player, CreatureObject* targetPlayer) const;

	/**
	 * Requests end duel
	 * @param player player that is trying to end duel to target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void requestEndDuel(CreatureObject* player, CreatureObject* targetPlayer) const;

	/**
	 * Clears duel list
	 * @param player player to clear duel list
	 * @pre { player is locked }
	 * @post { player is locked }
	 */
	void freeDuelList(CreatureObject* player, bool spam = false) const;

	/**
	 * Declines duel
	 * @param player player that is trying to end duel to target
	 * @param targetPlayer target
	 * @pre { player != targetPlayer, player is locked }
	 * @post { player is locked }
	 */
	void declineDuel(CreatureObject* player, CreatureObject* targetPlayer) const;

	bool areInDuel(CreatureObject* player1, CreatureObject* player2) const;

	float calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio) const;

	void broadcastCombatAction(CreatureObject * attacker, WeaponObject* weapon, SortedVector<DefenderHitList*> targetDefenders, const CreatureAttackData & data) const;

	void finalCombatSpam(TangibleObject* attacker, WeaponObject* item, SortedVector<DefenderHitList*> targetDefenders, const CreatureAttackData & data) const;
	void broadcastCombatSpam(TangibleObject* attacker, TangibleObject* defender, TangibleObject* item, int damage, const String& file, const String& stringName, byte color) const;
	void sendMitigationCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, int type) const;

	float hitChanceEquation(float attackerAccuracy, float attackerRoll, float targetDefense, float defenderRoll) const;
	float doDroidDetonation(CreatureObject* droid, CreatureObject* defender, float damage) const;

	void checkForTefs(CreatureObject* attacker, CreatureObject* defender, bool* shouldGcwCrackdownTef, bool* shouldGcwTef, bool* shouldBhTef) const;
	void getFrsModifiedForceAttackDamage(CreatureObject* attacker, float& minDmg, float& maxDmg, const CreatureAttackData& data) const;

	int getArmorObjectReduction(ArmorObject* armor, int damageType) const;
	ArmorObject* getPSGArmor(CreatureObject* defender) const;

	//all the combat math will go here
protected:
	int doTargetCombatAction(CreatureObject* attacker, WeaponObject* weapon, TangibleObject* defenderObject, SortedVector<DefenderHitList*>* targetDefenders, const CreatureAttackData& data, bool* shouldGcwCrackdownTef, bool* shouldGcwTef, bool* shouldBhTef) const;
	int creoTargetCombatAction(CreatureObject* attacker, WeaponObject* weapon, CreatureObject* defenderObject, DefenderHitList* defenderHitList, const CreatureAttackData& data, bool* shouldGcwCrackdownTef, bool* shouldGcwTef, bool* shouldBhTef) const;

	int doTargetCombatAction(TangibleObject* attacker, WeaponObject* weapon, TangibleObject* tano, SortedVector<DefenderHitList*>* targetDefenders, const CreatureAttackData& data) const;
	int tanoTargetCombatAction(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defenderObject, DefenderHitList* hitList, const CreatureAttackData& data) const;

	float calculateDamage(CreatureObject* attacker, WeaponObject* weapon, CreatureObject* defender, const CreatureAttackData& data) const;
	float calculateDamage(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, const CreatureAttackData& data) const;
	float calculateDamage(CreatureObject* attacker, WeaponObject* weapon, TangibleObject* defender, const CreatureAttackData& data) const;
	int calculateDamageRange(TangibleObject* attacker, CreatureObject* defender, WeaponObject* weapon) const;
	float applyDamageModifiers(CreatureObject* attacker, WeaponObject* weapon, float damage, const CreatureAttackData& data) const;

	/**
	 * returns bitmask with what pools to damage
	 */
	int calculatePoolsToDamage(int poolsToDamage) const;
	int applyDamage(CreatureObject* attacker, WeaponObject* weapon, TangibleObject* defender, DefenderHitList* defenderHitList, int poolsToDamage, const CreatureAttackData& data) const;
	int applyDamage(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, DefenderHitList* defenderHitList, int damage, float damageMultiplier, int poolsToDamage, uint8& hitLocation, const CreatureAttackData& data) const;
	void woundCreatureTarget(CreatureObject* defender, WeaponObject* weapon, Vector<int> poolsToWound) const;

	void applyDots(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data, int appliedDamage, int unmitDamage, int poolsToDamage) const;
	void applyWeaponDots(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon) const;
	uint8 getPoolForDot(uint64 dotType, int poolsToDamage) const;

	int getAttackerAccuracyModifier(TangibleObject* attacker, CreatureObject* defender, WeaponObject* weapon) const;
	int getAttackerAccuracyBonus(CreatureObject* attacker, WeaponObject* weapon) const;
	int calculatePostureModifier(CreatureObject* creature, WeaponObject* weapon) const;
	int calculateTargetPostureModifier(WeaponObject* weapon, CreatureObject* targetCreature) const;
	float getWeaponRangeModifier(float currentRange, WeaponObject* weapon) const;

	int getDefenderDefenseModifier(CreatureObject* defender, WeaponObject* weapon, TangibleObject* attacker) const;
	int getDefenderSecondaryDefenseModifier(CreatureObject* defender) const;
	float getDefenderToughnessModifier(CreatureObject* defender, int attackType, int damType, float damage) const;

	/**
	* @returns 0 - hit, 1 - block, 2 - dodge, 3 - counter-attack, 4 - miss
	*/
	int getHitChance(TangibleObject* attacker, CreatureObject* targetCreature, WeaponObject* weapon, const CreatureAttackData& data, int damage, int accuracyBonus) const;

	int getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon) const;

	bool checkConeAngle(SceneObject* targetCreature, float angle, float creatureVectorX, float creatureVectorY, float directionVectorX, float directionVectorY) const;

	int getArmorReduction(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, DefenderHitList* hitList, float damage, int hitLocation, const CreatureAttackData& data) const;
	float getArmorPiercing(TangibleObject* defender, int armorPiercing) const;
	int getArmorNpcReduction(AiAgent* defender, int damageType) const;
	int getArmorVehicleReduction(VehicleObject* defender, int damageType) const;
	int getArmorTurretReduction(CreatureObject* attacker, TangibleObject* defender, int damageType) const;
	ArmorObject* getArmorObject(CreatureObject* defender, uint8 hitLocation) const;

	void showHitLocationFlyText(CreatureObject *attacker, CreatureObject *defender, uint8 location) const;
	void doMiss(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, const CreatureAttackData& data, int damage) const;
	void doCounterAttack(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, int damage) const;
	void doBlock(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, int damage) const;
	void doDodge(TangibleObject* attacker, WeaponObject* weapon, CreatureObject* defender, int damage) const;

	/**
	 * returns false on insufficient
	 */
	bool applySpecialAttackCost(CreatureObject* attacker, WeaponObject* weapon, const CreatureAttackData& data) const;

	void applyStates(CreatureObject* creature, CreatureObject* targetCreature, DefenderHitList* hitList, const CreatureAttackData& data) const;
};

#endif /* COMBATMANAGER_H_ */
