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

	float damageMultiplier;
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

public:
    CreatureAttackData(const UnicodeString & dataString, CombatQueueCommand *base);
    CreatureAttackData(const CreatureAttackData& data);
    virtual ~CreatureAttackData() {}

    void fillFromBase();
    void setVariable(const String& var, const String& val);

    String getCommandName() const;
    uint32 getCommandCRC() const;

    CombatQueueCommand* getCommand() const {
    	return baseCommand;
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
};

#endif /* CREATUREATTACKDATA_H_ */
