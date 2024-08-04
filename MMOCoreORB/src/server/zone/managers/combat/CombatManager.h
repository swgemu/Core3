/*
 * CombatManager.h
 *
 *  Created on: 21/01/2010
 *      Author: victor
 */

#ifndef COMBATMANAGER_H_
#define COMBATMANAGER_H_

//#define TOHIT_DEBUG

#include "DefenderHitList.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"

class CreatureAttackData;
class CombatQueueCommand;

class CombatManager : public Singleton<CombatManager>, public Logger, public Object {
public:
	enum HitStatus : int {
		 MISS = 0,
		 HIT = 1,
		 BLOCK = 2,
		 DODGE = 3,
		 REDIRECT = 4,
		 COUNTER = 5,
		 FUMBLE = 6,
		 RICOCHET = 7,
		 REFLECT = 8,
		 REFLECT_TO_TARGET = 9,
	};

	// trails bitmask
	const static int NOTRAIL = 0x00;
	const static int LEFTFOOTTRAIL = 0x01;
	const static int RIGHTFOOTTRAIL = 0x02;
	const static int LEFTHANDTRAIL = 0x04;
	const static int RIGHTHANDTRAIL = 0x08;
	const static int WEAPONTRAIL = 0x10;
	const static int DEFAULTTRAIL = 0xFF;

	// poolsToDamage
	const static int NONE = 0;
	const static int HEALTH = 1;
	const static int ACTION = 2;
	const static int MIND = 4;
	const static int RANDOM = 8;

	enum hitLocation : int {
		HIT_BODY = 0,
		HIT_HEAD = 1,
		HIT_RARM = 2,
		HIT_LARM = 3,
		HIT_RLEG = 4,
		HIT_LLEG = 5,
		HIT_NUM = 6,
	};

	//Mitigation types
	const static int PSG = 0x1;
	const static int FORCESHIELD = 0x02;
	const static int FORCEFEEDBACK = 0x03;
	const static int FORCEABSORB = 0x04;
	const static int FORCEARMOR = 0x5;
	const static int ARMOR = 0x6;
	const static int FOOD = 0x7;

	// toHitChance
	const static constexpr float toHitScale = 50.f;
	const static constexpr float toHitBase = 75.f;
	const static constexpr float toHitStep = 25.f;
	const static constexpr float toHitStepMax = toHitBase / toHitStep;
	const static constexpr float toHitMax = 100.f;
	const static constexpr float toHitMin = 0.f;

	// weaponType
	enum WeaponType {
		THROWNWEAPON = 0x1,
		HEAVYWEAPON = 0x2,
		MINEWEAPON = 0x4,
		SPECIALHEAVYWEAPON = 0x8,
		UNARMEDWEAPON = 0x10,
		ONEHANDMELEEWEAPON = 0x20,
		TWOHANDMELEEWEAPON = 0x40,
		POLEARMWEAPON = 0x80,
		PISTOLWEAPON = 0x100,
		CARBINEWEAPON = 0x200,
		RIFLEWEAPON = 0x400,
		GRENADEWEAPON = 0x800,
		LIGHTNINGRIFLEWEAPON = 0x1000,
		ONEHANDJEDIWEAPON = 0x2000,
		TWOHANDJEDIWEAPON = 0x4000,
		POLEARMJEDIWEAPON = 0x8000
	};

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

	/**
	 * Checks if there is an active challenge
	 * @param challenger player that is being checked if they have an open challenge for target
	 * @param targetPlayer target
	 * @pre { challenger != targetPlayer, challenger is locked }
	 * @post { challenger is locked }
	 */
	bool hasActiveDuelChallenge(CreatureObject* challenger, CreatureObject* targetPlayer) const;

	float calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio) const;

	void broadcastCombatAction(CreatureObject * attacker, WeaponObject* weapon, SortedVector<DefenderHitList*> targetDefenders, const CreatureAttackData & data) const;

	void finalCombatSpam(TangibleObject* attacker, WeaponObject* item, SortedVector<DefenderHitList*> targetDefenders, const CreatureAttackData & data) const;
	void broadcastCombatSpam(TangibleObject* attacker, TangibleObject* defender, TangibleObject* item, int damage, const String& file, const String& stringName, byte color) const;
	void sendMitigationCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, int type) const;

	float hitChanceEquation(float attackerAccuracy, float targetDefense) const;
	float doObjectDetonation(TangibleObject* droid, CreatureObject* defender, float damage, WeaponObject* weapon = nullptr) const;

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

	int getWeaponDefendResult(uint32 defendWeaponMask) const {
		switch (defendWeaponMask) {
			case WeaponType::ONEHANDMELEEWEAPON: return HitStatus::DODGE;
			case WeaponType::TWOHANDMELEEWEAPON: return HitStatus::COUNTER;
			case WeaponType::POLEARMWEAPON: return HitStatus::BLOCK;
			case WeaponType::PISTOLWEAPON: return HitStatus::DODGE;
			case WeaponType::CARBINEWEAPON: return HitStatus::COUNTER;
			case WeaponType::RIFLEWEAPON: return HitStatus::BLOCK;
			case WeaponType::ONEHANDJEDIWEAPON: return HitStatus::RICOCHET;
			case WeaponType::TWOHANDJEDIWEAPON: return HitStatus::RICOCHET;
			case WeaponType::POLEARMJEDIWEAPON: return HitStatus::RICOCHET;
			default: {
				const int defenseAcuity[] = { BLOCK, DODGE, COUNTER };
				return defenseAcuity[System::random(2)];
			}
		}
	}

	float getWeaponPostureModifier(uint32 attackWeaponMask) const {
		switch(attackWeaponMask) {
			case WeaponType::RIFLEWEAPON: return 2.5f;
			case WeaponType::CARBINEWEAPON: return 2.f;
			case WeaponType::PISTOLWEAPON: return 1.5f;
			case WeaponType::SPECIALHEAVYWEAPON: return 3.f;
			case WeaponType::ONEHANDMELEEWEAPON: return 1.f;
			case WeaponType::TWOHANDMELEEWEAPON: return 1.f;
			case WeaponType::UNARMEDWEAPON: return 1.f;
			case WeaponType::POLEARMWEAPON: return 1.f;
			case WeaponType::THROWNWEAPON: return 1.f;
			case WeaponType::ONEHANDJEDIWEAPON: return 1.f;
			case WeaponType::TWOHANDJEDIWEAPON: return 1.f;
			case WeaponType::POLEARMJEDIWEAPON: return 1.f;
			default: return 1.f;
		}
	}
};

#endif /* COMBATMANAGER_H_ */
