/*
 * CombatQueueCommand.h
 *
 *  Created on: 24/05/2010
 *      Author: victor
 */

#ifndef COMBATQUEUECOMMAND_H_
#define COMBATQUEUECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "QueueCommand.h"

class CombatQueueCommand: public QueueCommand {
protected:
	int damageMultiplier;
	int speedMultiplier;
	int poolsToDamage;

	int healthCostMultiplier;
	int actionCostMultiplier;
	int mindCostMultiplier;
	int forceCostMultiplier;

	int knockdownStateChance;
	int postureDownStateChance;
	int postureUpStateChance;

	int dizzyStateChance;
	int blindStateChance;
	int stunStateChance;
	int intimidateStateChance;
	int nextAttackDelayChance;
	int durationStateTime;

	int range;

	bool areaAction;
	bool coneAction;
	int coneAngle;
	int areaRange;

	String combatSpam;
	uint32 animationCRC;
	String effectString;
public:

	CombatQueueCommand(const String& name,
			ZoneProcessServerImplementation* server) :
		QueueCommand(name, server) {

		damageMultiplier = 1;
		speedMultiplier = 1;
		healthCostMultiplier = 1;
		actionCostMultiplier = 1;
		mindCostMultiplier = 1;
		forceCostMultiplier = 1;

		poolsToDamage = CombatManager::RANDOM;

		knockdownStateChance = 0;
		postureDownStateChance = 0;
		postureUpStateChance = 0;
		dizzyStateChance = 0;
		blindStateChance = 0;
		stunStateChance = 0;
		intimidateStateChance = 0;
		nextAttackDelayChance = 0;

		durationStateTime = 10;

		coneAngle = 30;

		//for weapon set -1
		range = -1;

		areaRange = 0;
		areaAction = false;
		coneAction = false;

		combatSpam = "";
		animationCRC = 0;
	}

	int doCombatAction(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
			return INVALIDTARGET;

		float checkRange = range;

		if (checkRange == -1) {
			ManagedReference<WeaponObject*> weapon = creature->getWeapon();

			checkRange = weapon->getMaxRange();
		}

		if (!targetObject->isInRange(creature, checkRange))
			return TOOFAR;

		CombatManager* combatManager = CombatManager::instance();

		try {
			int res = combatManager->doCombatAction(creature, (TangibleObject*) ((targetObject.get())), this);

			switch (res) {
			case -1:
				return INVALIDTARGET;
			case -2:
				return INSUFFICIENTHAM;
			default:
				return GENERALERROR;
			}

		} catch (...) {
			error("unreported exception caught in Melee1hLunge1Command::doQueueCommand");
		}

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject *object) {
		float duration = CombatManager::instance()->calculateWeaponAttackSpeed(
				object, object->getWeapon(), speedMultiplier);
		return duration;
	}

	inline int getHealthCostMultiplier() const {
		return healthCostMultiplier;
	}

	inline int getActionCostMultiplier() const {
		return actionCostMultiplier;
	}

	inline int getMindCostMultiplier() const {
		return mindCostMultiplier;
	}

	inline int getRange() const {
		return range;
	}

	inline int getBlindChance() const {
		return blindStateChance;
	}

	inline int getDamageMultiplier() const {
		return damageMultiplier;
	}

	inline int getDizzyChance() const {
		return dizzyStateChance;
	}

	inline int getIntimidateChance() const {
		return intimidateStateChance;
	}

	inline int getKnockdownChance() const {
		return knockdownStateChance;
	}

	inline int getPostureDownChance() const {
		return postureDownStateChance;
	}

	inline int getPostureUpChance() const {
		return postureUpStateChance;
	}

	inline int getSpeedMultiplier() const {
		return speedMultiplier;
	}

	inline int getStunChance() const {
		return stunStateChance;
	}

	inline bool isAreaAction() const {
		return areaAction;
	}

	inline bool isConeAction() const {
		return coneAction;
	}

	inline int getConeAngle() const {
		return coneAngle;
	}

	inline int getAreaRange() const {
		return areaRange;
	}

	inline int getDurationStateTime() const {
		return durationStateTime;
	}

	inline int getForceCostMultiplier() const {
		return forceCostMultiplier;
	}

	inline int getNextAttackDelayChance() const {
		return nextAttackDelayChance;
	}

	void setBlindStateChance(int blindStateChance) {
		this->blindStateChance = blindStateChance;
	}

	void setDamageMultiplier(int damageMultiplier) {
		this->damageMultiplier = damageMultiplier;
	}

	void setDizzyStateChance(int dizzyStateChance) {
		this->dizzyStateChance = dizzyStateChance;
	}

	void setIntimidateStateChance(int intimidateStateChance) {
		this->intimidateStateChance = intimidateStateChance;
	}

	void setKnockdownStateChance(int knockdownStateChance) {
		this->knockdownStateChance = knockdownStateChance;
	}

	void setPostureDownStateChance(int postureDownStateChance) {
		this->postureDownStateChance = postureDownStateChance;
	}

	void setPostureUpStateChance(int postureUpStateChance) {
		this->postureUpStateChance = postureUpStateChance;
	}

	void setSpeedMultiplier(int speedMultiplier) {
		this->speedMultiplier = speedMultiplier;
	}

	void setStunStateChance(int stunStateChance) {
		this->stunStateChance = stunStateChance;
	}

	inline uint32 getAnimationCRC() const {
		return animationCRC;
	}

	inline String getEffectString() const {
		return effectString;
	}

	inline String getCombatSpam() const {
		return combatSpam;
	}

	inline int getPoolsToDamage() const {
		return poolsToDamage;
	}

	void setAnimationCRC(uint32 animationCRC) {
		this->animationCRC = animationCRC;
	}

	void setCombatSpam(String combatSpam) {
		this->combatSpam = combatSpam;
	}

	void setPoolsToDamage(int poolsToDamage) {
		this->poolsToDamage = poolsToDamage;
	}

};

#endif /* COMBATQUEUECOMMAND_H_ */
