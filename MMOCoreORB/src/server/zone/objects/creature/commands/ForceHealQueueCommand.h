/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEHEALQUEUECOMMAND_H_
#define FORCEHEALQUEUECOMMAND_H_

#include "JediQueueCommand.h"

class ForceHealQueueCommand : public JediQueueCommand {
public:
	// Introducing our own enums since those will support being used in bitsets
	enum {
		HEALTH = 1,
		STRENGTH = 2,
		CONSTITUTION = 4,
		ACTION = 8,
		QUICKNESS = 16,
		STAMINA = 32,
		MIND = 64,
		FOCUS = 128,
		WILLPOWER = 256,
		BATTLE_FATIGUE = 512
	};

	enum {
		STUN = 1,
		DIZZY = 2,
		BLIND = 4,
		INTIMIDATE = 8,
	};

	enum {
		DISEASED = 1,
		POISONED = 2,
		BLEEDING = 4,
		ONFIRE   = 8
	};

	enum {
		HEAL_DAMAGE,
		HEAL_WOUNDS,
		HEAL_STATES,
		HEAL_BLEEDING,
		HEAL_POISON,
		HEAL_DISEASE,
		HEAL_FIRE,
		HEAL_FATIGUE
	};

	// these two enums are used for skills that allow healing on self and
	// others.
	enum {
		TARGET_AUTO = 0, // go by range !=0 for ranged / this is default
		TARGET_SELF = 1,
		TARGET_OTHER = 2
	};
protected:
	int speed;
	unsigned int allowedTarget;
	float forceCostMultiplier; // Value to be added to base force cost per point healed

	int statesToHeal; // bitmask of states to heal (STUN | DIZZY | BLINDED | INITIMDATED )
	int healStateCost; // Cost per state healed

	int healDiseaseCost; // > 0 heals given amount of dot damage
	int healPoisonCost; // > 0 heals given amount of poison
	int healBleedingCost; // > 0 heals given amount of bleeds
	int healFireCost; // > 0 heals given amount of fire dot

	int attributesToHeal; // bitmask of which attributes to heal, HEALTH etc..
	int woundAttributesToHeal; // bitmask of which attributes to heal, HEALTH etc..

	int healBattleFatigue; // amount of BF to heal
	int healAmount; // amount to heal (HAM pools)
	int healWoundAmount; // amount of wounds to heal

	int bleedHealIterations;
	int poisonHealIterations;
	int diseaseHealIterations;
	int fireHealIterations;

	int range; // range to heal up to, if <= 0 it heals the user

public:
	ForceHealQueueCommand(const String& name, ZoneProcessServer* server);

	void sendHealMessage(CreatureObject* creature, CreatureObject* target, int healType, int healSpec, int amount) const;

	int runCommandWithTarget(CreatureObject* creature, CreatureObject* targetCreature) const;

	int runCommand(CreatureObject* creature, CreatureObject* targetCreature) const;

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const;

	bool isForceHealCommand() {
		return true;
	}

	void setForceCostMultiplier(float fcm) {
		forceCostMultiplier = fcm;
	}

	void setHealStateCost(unsigned int cost) {
		healStateCost = cost;
	}

	void setStatesToHeal(unsigned int states) {
		statesToHeal = states;
	}

	void setHealDiseaseCost(unsigned int cost) {
		healDiseaseCost = cost;
	}

	void setHealPoisonCost(unsigned int cost) {
		healPoisonCost = cost;
	}

	void setHealBleedingCost(unsigned int cost) {
		healBleedingCost = cost;
	}

	void setHealFireCost(unsigned int cost) {
		healFireCost = cost;
	}

	void setAttributesToHeal(unsigned int attributes) {
		attributesToHeal = attributes;
	}

	void setWoundAttributesToHeal(unsigned int attributes) {
		woundAttributesToHeal = attributes;
	}

	void setHealBattleFatigue(unsigned int amount) {
		healBattleFatigue = amount;
	}

	void setHealAmount(unsigned int amount ) {
		healAmount = amount;
	}

	void setHealWoundAmount(unsigned int amount) {
		healWoundAmount = amount;
	}

	void setBleedHealIterations(unsigned int amount) {
		bleedHealIterations = amount;
	}

	void setPoisonHealIterations(unsigned int amount) {
		poisonHealIterations = amount;
	}

	void setDiseaseHealIterations(unsigned int amount) {
		diseaseHealIterations = amount;
	}

	void setFireHealIterations(unsigned int amount) {
		fireHealIterations = amount;
	}

	void setRange(int r) {
		range = r;
	}

	void setSpeed(int s) {
		speed = s;
	}

	void setAllowedTarget(unsigned int t) {
		allowedTarget = t;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}
};

#endif /* FORCEHEALQUEUECOMMAND_H_ */
