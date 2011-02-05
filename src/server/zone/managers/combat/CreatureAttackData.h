/*
 * CreatureAttackData.h
 *
 *  Created on: Sep 27, 2010
 *      Author: dannuic
 */

#ifndef CREATUREATTACKDATA_H_
#define CREATUREATTACKDATA_H_

#include "engine/engine.h"

class CombatQueueCommand;

class CreatureAttackData {
protected:
	CombatQueueCommand* baseCommand;

	float damageMultiplier;
	float speedMultiplier;
	int poolsToDamage;

	float healthCostMultiplier;
	float actionCostMultiplier;
	float mindCostMultiplier;
	float forceCostMultiplier;

	int knockdownStateChance;
	int postureDownStateChance;
	int postureUpStateChance;

	int dizzyStateChance;
	int blindStateChance;
	int stunStateChance;
	int intimidateStateChance;
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

    float getActionCostMultiplier() const {
		return actionCostMultiplier;
	}

	uint32 getAnimationCRC() const {
		return animationCRC;
	}

	int getAreaRange() const {
		return areaRange;
	}

	int getBlindStateChance() const {
		return blindStateChance;
	}

	int getConeAngle() const {
		return coneAngle;
	}

	float getDamageMultiplier() const {
		return damageMultiplier;
	}

	int getDizzyStateChance() const {
		return dizzyStateChance;
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

	int getIntimidateStateChance() const {
		return intimidateStateChance;
	}

	int getKnockdownStateChance() const {
		return knockdownStateChance;
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

	int getPostureDownStateChance() const {
		return postureDownStateChance;
	}

	int getPostureUpStateChance() const {
		return postureUpStateChance;
	}

	int getRange() const {
		return range;
	}

	float getSpeedMultiplier() const {
		return speedMultiplier;
	}

	int getStunStateChance() const {
		return stunStateChance;
	}

	void setAnimationCRC(uint32 animationCRC) {
		this->animationCRC = animationCRC;
	}
};

#endif /* CREATUREATTACKDATA_H_ */
