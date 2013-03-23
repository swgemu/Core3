/*
 * CreatureAttackData.h
 *
 *  Created on: Sep 27, 2010
 *      Author: dannuic
 */

#ifndef CREATUREATTACKDATA_H_
#define CREATUREATTACKDATA_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"

class CombatQueueCommand;

class CreatureAttackData {
protected:
	CombatQueueCommand* baseCommand;

	float damage;
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

	int nextAttackDelayChance;
	int durationStateTime;

	uint32 dotDuration;
	uint64 dotType;
	uint8 dotPool;
	uint32 dotStrength;
	float dotPotency;

    int range;
    int coneAngle;
    int areaRange;

    uint32 animationCRC;

    VectorMap<uint64, StateEffect>* stateEffects;
    VectorMap<uint64, DotEffect>* dotEffects;

	uint8 attackType;
	uint8 trails;

	String combatSpam;

public:
    CreatureAttackData(const UnicodeString & dataString, CombatQueueCommand *base);
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

    CombatQueueCommand* getCommand() const {
    	return baseCommand;
    }

    float getDamage() const {
    	return damage;
    }

    int getAccuracyBonus() const {
    	return accuracyBonus;
    }

    float getActionCostMultiplier() const {
		return actionCostMultiplier;
	}

	uint32 getAnimationCRC() const {
		return animationCRC;
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

	uint32 getDotDuration() const {
		return dotDuration;
	}

	uint8 getDotPool() const {
		return dotPool;
	}

	float getDotPotency() const {
		return dotPotency;
	}

	uint32 getDotStrength() const {
		return dotStrength;
	}

	uint64 getDotType() const {
		return dotType;
	}

	int getDurationStateTime() const {
		return durationStateTime;
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

	int getNextAttackDelayChance() const {
		return nextAttackDelayChance;
	}

	int getPoolsToDamage() const {
		return poolsToDamage;
	}

	int getRange() const {
		return range;
	}

	float getSpeedMultiplier() const {
		return speedMultiplier;
	}

	VectorMap<uint64, StateEffect>* getStateEffects() const {
		return stateEffects;
	}

	VectorMap<uint64, DotEffect>* getDotEffects() const {
		return dotEffects;
	}

	void setAnimationCRC(uint32 animationCRC) {
		this->animationCRC = animationCRC;
	}

	uint8 getAttackType() const {
		return attackType;
	}

	void setAttackType(uint8 attackType) {
		this->attackType = attackType;
	}

	uint8 getTrails() const {
		return trails;
	}

	void setTrails(uint8 trails) {
		this->trails = trails;
	}

	String getCombatSpam() const {
		return combatSpam;
	}

	void setCombatSpam(String spam) {
		this->combatSpam = spam;
	}
};

#endif /* CREATUREATTACKDATA_H_ */
