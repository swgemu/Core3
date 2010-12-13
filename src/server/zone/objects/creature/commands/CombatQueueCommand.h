/*
 * CombatQueueCommand.h
 *
 *  Created on: 24/05/2010
 *      Author: victor
 */

#ifndef COMBATQUEUECOMMAND_H_
#define COMBATQUEUECOMMAND_H_

#include"server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "QueueCommand.h"

class CombatQueueCommand: public QueueCommand {
protected:
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
	bool dotDamageOfHit;

	int range;

	bool areaAction;
	bool coneAction;
	int coneAngle;
	int areaRange;

	String combatSpam;
	uint32 animationCRC;
	String effectString;
public:

	CombatQueueCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		dotDuration = 0;
		dotType = 0;
		dotPool = 0;
		dotStrength = 0;
		dotPotency = 80;

		coneAngle = 30;
		dotDamageOfHit = false;

		//for weapon set -1
		range = -1;

		areaRange = 0;
		areaAction = false;
		coneAction = false;

		combatSpam = "";
		animationCRC = 0;
	}

	int doCombatAction(CreatureObject* creature, const uint64& target, const UnicodeString& arguments = "") {
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		PlayerManager* playerManager = server->getPlayerManager();

		if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
			return INVALIDTARGET;

		float checkRange = range;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (checkRange == -1) {
			checkRange = weapon->getMaxRange();
		}

		if (creature->isKneeling() && weapon->isMeleeWeapon())
			return NOKNEELING;

		if (creature->isProne() && !weapon->isRangedWeapon())
			return NOPRONE;

		if (!targetObject->isInRange(creature, checkRange))
			return TOOFAR;

		if (!playerManager->checkLineOfSight(creature, targetObject)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return GENERALERROR;
		}

		CombatManager* combatManager = CombatManager::instance();

		try {
			int res = combatManager->doCombatAction(creature, (TangibleObject*) ((targetObject.get())), CreatureAttackData(arguments, this));

			switch (res) {
			case -1:
				return INVALIDTARGET;
			case -2:
				return INSUFFICIENTHAM;
			case -3:
				return GENERALERROR;
			}

		} catch (...) {
			error("unreported exception caught in CombatQueueCommand::doCombatAction");
		}

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject *object) {
		return CombatManager::instance()->calculateWeaponAttackSpeed(object, object->getWeapon(), speedMultiplier);
	}

	inline uint32 getDotDuration() const {
		return dotDuration;
	}

	inline uint64 getDotType() const {
		return dotType;
	}

	inline uint8 getDotPool() const {
		return dotPool;
	}

	inline uint32 getDotStrength() const {
		return dotStrength;
	}

	inline float getDotPotency() const {
		return dotPotency;
	}

	inline float getHealthCostMultiplier() const {
		return healthCostMultiplier;
	}

	inline float getActionCostMultiplier() const {
		return actionCostMultiplier;
	}

	inline float getMindCostMultiplier() const {
		return mindCostMultiplier;
	}

	inline int getRange() const {
		return range;
	}

	inline int getBlindChance() const {
		return blindStateChance;
	}

	inline float getDamageMultiplier() const {
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

	inline float getSpeedMultiplier() const {
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

	inline bool isDotDamageOfHit() const {
		return dotDamageOfHit;
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

	inline float getForceCostMultiplier() const {
		return forceCostMultiplier;
	}

	inline int getNextAttackDelayChance() const {
		return nextAttackDelayChance;
	}

	void setBlindStateChance(int blindStateChance) {
		this->blindStateChance = blindStateChance;
	}

	void setDamageMultiplier(float damageMultiplier) {
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

	void setSpeedMultiplier(float speedMultiplier) {
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
