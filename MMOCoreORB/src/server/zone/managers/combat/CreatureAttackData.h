/*
 * CreatureAttackData.h
 *
 *  Created on: Sep 27, 2010
 *      Author: dannuic
 */

#ifndef CREATUREATTACKDATA_H_
#define CREATUREATTACKDATA_H_

#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"

class CombatQueueCommand;

class CreatureAttackData {
protected:
	const CombatQueueCommand* baseCommand;

	float minDamage;
	float maxDamage;
	int damageType;
	int forceCost;
	float damageMultiplier;
	float healthDamageMultiplier;
	float actionDamageMultiplier;
	float mindDamageMultiplier;
	int accuracyBonus;
	float speedMultiplier;
	int poolsToDamage;

	float healthCostMultiplier;
	float actionCostMultiplier;
	float mindCostMultiplier;
	float forceCostMultiplier;
	float frsLightMinDamageModifier;
	float frsLightMaxDamageModifier;
	float frsDarkMinDamageModifier;
	float frsDarkMaxDamageModifier;

    int range;
    int coneRange;
    int coneAngle;
    int areaRange;

    bool splashDamage;
    bool hitIncapTarget;

    uint64 targetID;

    VectorMap<uint8, StateEffect>* stateEffects;
    Vector<DotEffect>* dotEffects;

	bool forceAttack;
	uint8 trails;

	String combatSpam;

	int stateAccuracyBonus;

public:
    CreatureAttackData(const UnicodeString & dataString, const CombatQueueCommand *base, uint64 target);
    CreatureAttackData(const CreatureAttackData& data);
    virtual ~CreatureAttackData() {}

    void fillFromBase();
    void setVariable(const String& var, const String& val);

    String getCommandName() const;
    uint32 getCommandCRC() const;

	float getActionDamageMultiplier() const {
		return actionDamageMultiplier;
	}

	void setActionDamageMultiplier(float actionDamageMultiplier) {
		this->actionDamageMultiplier = actionDamageMultiplier;
	}

	float getHealthDamageMultiplier() const {
		return healthDamageMultiplier;
	}

	void setHealthDamageMultiplier(float healthDamageMultiplier) {
		this->healthDamageMultiplier = healthDamageMultiplier;
	}

	float getMindDamageMultiplier() const {
		return mindDamageMultiplier;
	}

	void setMindDamageMultiplier(float mindDamageMultiplier) {
		this->mindDamageMultiplier = mindDamageMultiplier;
	}

    const CombatQueueCommand* getCommand() const {
    	return baseCommand;
    }

    float getMinDamage() const {
    	return minDamage;
    }

    float getMaxDamage() const {
    	return maxDamage;
    }

    int getDamageType() const {
    	return damageType;
    }

    int getAccuracyBonus() const {
    	return accuracyBonus;
    }

    float getActionCostMultiplier() const {
		return actionCostMultiplier;
	}


	void setSplashDamage(bool b) {
		splashDamage = b;
	}

	bool isSplashDamage() const {
		return splashDamage;
	}

	bool getHitIncapTarget() const {
		return hitIncapTarget;
	}

	int getAreaRange() const {
		return areaRange;
	}

	int getConeAngle() const {
		return coneAngle;
	}

	float getDamageMultiplier() const {
		return damageMultiplier;
	}

	float getForceCostMultiplier() const {
		return forceCostMultiplier;
	}

	float getHealthCostMultiplier() const {
		return healthCostMultiplier;
	}

	float getMindCostMultiplier() const {
		return mindCostMultiplier;
	}

	int getPoolsToDamage() const {
		return poolsToDamage;
	}

	int getConeRange() const {
		return coneRange;
	}

	int getRange() const {
		return range;
	}

	float getSpeedMultiplier() const {
		return speedMultiplier;
	}

	VectorMap<uint8, StateEffect>* getStateEffects() const {
		return stateEffects;
	}

	Vector<DotEffect>* getDotEffects() const {
		return dotEffects;
	}

	bool isForceAttack() const {
		return forceAttack;
	}

	int getForceCost() const {
		return forceCost;
	}

	float getFrsLightMinDamageModifier() const {
		return frsLightMinDamageModifier;
	}

	float getFrsLightMaxDamageModifier() const {
		return frsLightMaxDamageModifier;
	}

	float getFrsDarkMinDamageModifier() const {
		return frsDarkMinDamageModifier;
	}

	float getFrsDarkMaxDamageModifier() const {
		return frsDarkMaxDamageModifier;
	}

	void setForceAttack(bool forceAttack) {
		this->forceAttack = forceAttack;
	}

	uint8 getTrails() const {
		return trails;
	}

	uint64 getPrimaryTarget() const {
		return targetID;
	}

	void setTrails(uint8 trails) {
		this->trails = trails;
	}

	const String& getCombatSpam() const {
		return combatSpam;
	}

	void setCombatSpam(const String& spam) {
		this->combatSpam = spam;
	}

	bool isStateOnlyAttack() const {
		return poolsToDamage == 0;
	}

	int getStateAccuracyBonus() const {
		return stateAccuracyBonus;
	}

	void setStateAccuracyBonus(int stateAccuracyBonus) {
		this->stateAccuracyBonus = stateAccuracyBonus;
	}

	bool changesDefenderPosture() const;

	bool changesAttackerPosture() const;
};

#endif /* CREATUREATTACKDATA_H_ */
