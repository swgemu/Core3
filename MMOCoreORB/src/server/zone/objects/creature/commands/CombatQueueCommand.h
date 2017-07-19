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
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "templates/params/creature/CreatureState.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "QueueCommand.h"
#include "server/zone/objects/player/FactionStatus.h"

class CombatQueueCommand : public QueueCommand {
protected:
	float minDamage;
	float maxDamage;
	int damageType;
	float damageMultiplier;
	int accuracyBonus;
	float speedMultiplier;
	float speed;
	int poolsToDamage;

	float healthCostMultiplier;
	float actionCostMultiplier;
	float mindCostMultiplier;
	float forceCostMultiplier;
	float forceCost;
	int visMod;

	int coneRange;
	int range;

	String accuracySkillMod;

	bool splashDamage;
	bool areaAction;
	bool coneAction;
	int coneAngle;
	int areaRange;

	String combatSpam;
	String stateSpam;
	String animation;
	String effectString;

	VectorMap<uint8, StateEffect> stateEffects;
	Vector<DotEffect> dotEffects;

	bool forceAttack;
	uint8 trails;
	uint8 animType;

	uint32 weaponType;

public:
	enum AnimGenTypes {
		GENERATE_NONE, // Uses animation as given - Default
		GENERATE_RANGED, // Generates _light|_medium as well as appends _face with headshots
		GENERATE_INTENSITY // generates _light|_medium only
	};

	CombatQueueCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

		minDamage = 0;
		maxDamage = 0;
		damageType = 0;
		damageMultiplier = 1;
		accuracyBonus = 0;
		speedMultiplier = 1;
		speed = 0;
		healthCostMultiplier = 1;
		actionCostMultiplier = 1;
		mindCostMultiplier = 1;

		// Force Power is only set in Jedi-skills.
		forceCostMultiplier = 0;
		forceCost = 0;
		visMod = 0;

		poolsToDamage = CombatManager::RANDOM;

		coneAngle = 30;

		coneRange = -1;

		//for weapon set -1
		range = -1;

		accuracySkillMod = "";

		areaRange = 0;
		splashDamage = false;
		areaAction = false;
		coneAction = false;

		combatSpam = "";
		animation = "";
		animType = GENERATE_NONE;


		forceAttack = false;
		trails = CombatManager::DEFAULTTRAIL;

		weaponType = SharedWeaponObjectTemplate::ANYWEAPON;
	}

	void onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) const {
		// evidence shows that this has a custom OOR message.
		if (errorNumber == TOOFAR) {
			creature->sendSystemMessage("@error_message:target_out_of_range"); //Your target is out of range for this action.
			CombatSpam* spam = new CombatSpam(creature, NULL, creature, NULL, 0, "cbt_spam", "out_of_range", 10); // That target is out of range. (red)
			creature->sendMessage(spam);
			QueueCommand::onFail(actioncntr, creature, GENERALERROR);
		} else {
			QueueCommand::onFail(actioncntr, creature, errorNumber);
		}
	}

	int doCombatAction(CreatureObject* creature, const uint64& target, const UnicodeString& arguments = "", ManagedReference<WeaponObject*> weapon = NULL) const {
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
			return INVALIDTARGET;

		float rangeToCheck = range;

		if (weapon == NULL) {
			if(creature->getWeapon() == NULL) {
				return GENERALERROR;
			}
			else {
				weapon = creature->getWeapon();
			}
		}

		if (!(getWeaponType() & weapon->getWeaponBitmask()))
			return INVALIDWEAPON;

		if (rangeToCheck == -1)
			rangeToCheck = (float) Math::max(10, weapon->getMaxRange());

		if (creature->isDead() || (creature->isPet() && creature->isIncapacitated()))
			return INVALIDLOCOMOTION;

		if (creature->isPlayerCreature()) {
			PlayerObject* ghost = creature->getPlayerObject();

			if (ghost != NULL) {
				if (ghost->isOnLoadScreen())
					ghost->setOnLoadScreen(false);

				if (ghost->isAFK())
					return GENERALERROR;

				ManagedReference<TangibleObject*> targetTano = targetObject.castTo<TangibleObject*>();

				if (targetTano != NULL && creature->getFaction() != 0 && targetTano->getFaction() != 0 && targetTano->getFaction() != creature->getFaction() && creature->getFactionStatus() != FactionStatus::OVERT) {
					if (targetTano->isCreatureObject()) {
						ManagedReference<CreatureObject*> targetCreature = targetObject.castTo<CreatureObject*>();

						if (targetCreature != NULL) {
							if (targetCreature->isPlayerCreature()) {
								if (!CombatManager::instance()->areInDuel(creature, targetCreature) && !targetCreature->hasBountyMissionFor(creature) && !creature->hasBountyMissionFor(targetCreature) && targetCreature->getFactionStatus() == FactionStatus::OVERT)
									ghost->doFieldFactionChange(FactionStatus::OVERT);
							} else if (targetCreature->isPet()) {
								ManagedReference<CreatureObject*> targetOwner = targetCreature->getLinkedCreature().get();

								if (targetOwner != NULL && !creature->hasBountyMissionFor(targetOwner) && !targetOwner->hasBountyMissionFor(creature) && !CombatManager::instance()->areInDuel(creature, targetOwner) && targetOwner->getFactionStatus() == FactionStatus::OVERT) {
										ghost->doFieldFactionChange(FactionStatus::OVERT);
								}
							} else {
								if (creature->getFactionStatus() == FactionStatus::ONLEAVE)
									ghost->doFieldFactionChange(FactionStatus::COVERT);
							}
						}
					} else {
						if (creature->getFactionStatus() == FactionStatus::ONLEAVE && !(targetTano->getPvpStatusBitmask() & CreatureFlag::OVERT))
							ghost->doFieldFactionChange(FactionStatus::COVERT);
						else if ((targetTano->getPvpStatusBitmask() & CreatureFlag::OVERT))
							ghost->doFieldFactionChange(FactionStatus::OVERT);
					}
				}
			}
		}

		if (creature->isKneeling() && weapon->isMeleeWeapon() && !(poolsToDamage == 0) && !weapon->isJediWeapon())
			return NOKNEELING;

		if (creature->isProne() && (weapon->isMeleeWeapon() || poolsToDamage == 0))
			return NOPRONE;

		if (!checkDistance(creature, targetObject, rangeToCheck))
			return TOOFAR;

		if (weapon->isRangedWeapon() && creature->isProne() && checkDistance(targetObject, creature, 7))
			return TOOCLOSE;

		if (!CollisionManager::checkLineOfSight(creature, targetObject)) {
			creature->sendSystemMessage("@cbt_spam:los_fail"); // "You lost sight of your target."
			return GENERALERROR;
		}

		if (creature->isPlayerCreature() && !targetObject->isPlayerCreature() && targetObject->getParentID() != 0 && creature->getParentID() != targetObject->getParentID()) {
			Reference<CellObject*> targetCell = targetObject->getParent().get().castTo<CellObject*>();

			if (targetCell != NULL) {
				ContainerPermissions* perms = targetCell->getContainerPermissions();

				if (!perms->hasInheritPermissionsFromParent()) {
					if (!targetCell->checkContainerPermission(creature, ContainerPermissions::WALKIN)) {
						creature->sendSystemMessage("@combat_effects:cansee_fail"); // You cannot see your target.
						return GENERALERROR;
					}
				}
			}
		}

		CombatManager* combatManager = CombatManager::instance();

		try {
			int res = combatManager->doCombatAction(creature, weapon, cast<TangibleObject*>(targetObject.get()), CreatureAttackData(arguments, this, target));

			switch (res) {
			case -1:
				return INVALIDTARGET;
			case -2:
				return INSUFFICIENTHAM;
			case -3:
				return GENERALERROR;
			}

		} catch (Exception& e) {
			creature->error("unreported exception caught in CombatQueueCommand::doCombatAction");
			creature->error(e.getMessage());
			e.printStackTrace();
		}

		// only clear aiming states if command was successful
		creature->removeStateBuff(CreatureState::AIMING);
		creature->removeBuff(STRING_HASHCODE("steadyaim"));

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) const {
		return CombatManager::instance()->calculateWeaponAttackSpeed(object, object->getWeapon(), speedMultiplier);
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

	inline int getConeRange() const {
		return coneRange;
	}

	inline int getRange() const {
		return range;
	}

	inline const String& getAccuracySkillMod() const {
		return accuracySkillMod;
	}

	inline float getDamageMultiplier() const {
		return damageMultiplier;
	}

	inline int getAccuracyBonus() const {
		return accuracyBonus;
	}

	inline float getSpeedMultiplier() const {
		return speedMultiplier;
	}

	inline float getSpeed() const {
		return speed;
	}

	inline bool isSplashDamage() const {
		return splashDamage;
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

	inline float getForceCostMultiplier() const {
		return forceCostMultiplier;
	}

	inline float getForceCost() const {
		return forceCost;
	}

	void setDamageMultiplier(float damageMultiplier) {
		this->damageMultiplier = damageMultiplier;
	}

	void setAccuracyBonus(int accuracyBonus) {
		this->accuracyBonus = accuracyBonus;
	}

	void setHealthCostMultiplier(float f) {
		this->healthCostMultiplier = f;
	}

	void setActionCostMultiplier(float f) {
		this->actionCostMultiplier = f;
	}

	void setMindCostMultiplier(float f) {
		this->mindCostMultiplier = f;
	}

	void setForceCostMultiplier(float f) {
		this->forceCostMultiplier = f;
	}

	void setForceCost(float f) {
		this->forceCost = f;
	}

	void setConeAngle(int i) {
		this->coneAngle = i;
	}

	void setSplashDamage(bool b) {
		this->splashDamage = b;
	}

	void setAreaAction(bool b) {
		this->areaAction = b;
	}

	void setConeAction(bool b) {
		this->coneAction = b;
	}

	void setAreaRange(int i) {
		this->areaRange = i;
	}

	void setEffectString(const String& s) {
		this->effectString = s;
	}

	void setSpeedMultiplier(float speedMultiplier) {
		this->speedMultiplier = speedMultiplier;
	}

	void setSpeed(float speedd) {
		this->speed = speedd;
	}

	void setAnimType(uint8 type) {
		animType = type;
	}

	uint8 getAnimType() const {
		return animType;
	}

	const String& getAnimationString() const {
		return animation;
	}

	static inline String getIntensity(int threshold, int damage) {
		if(damage > threshold)
			return "_medium";
		else
			return "_light";
	}

	String getDefaultAttackAnimation(TangibleObject* attacker, WeaponObject* weapon, uint8 hitLocation, int damage) const {
		enum lateralLocations {LEFT, CENTER, RIGHT};
		static const char* headLocations[] =  {"attack_high_left", "attack_high_center", "attack_high_right"};
		static const char* chestLocations[] = {"attack_mid_left", "attack_mid_center", "attack_mid_right"};
		static const char* legLocations[] = {"attack_low_left", "attack_low_center", "attack_low_right"};

		static const char* rangedAttacks[] = {"fire_1_single", "fire_3_single", "fire_5_single"};

		String intensity = getIntensity(((uint32)weapon->getMaxDamage()) >> 2, damage);
		StringBuffer buffer;

		if (attacker->isDroidObject()) {
			return "droid_attack" + intensity;
		} else if (!attacker->isCreature()) {
			if (weapon->isRangedWeapon()) {

				buffer << rangedAttacks[System::random(2)];

				buffer << intensity;

				if (hitLocation == CombatManager::HIT_HEAD)
					buffer << "_face";

			} else {
				if (hitLocation == 0)
					hitLocation = System::random(5) + 1;

				switch(hitLocation) {
				case CombatManager::HIT_BODY:
					buffer << chestLocations[CENTER];
					break;
				case CombatManager::HIT_LARM:
					buffer << chestLocations[RIGHT];
					break;
				case CombatManager::HIT_RARM:
					buffer << chestLocations[LEFT]; // these are purposely backwards - It's mirrored
					break;
				case CombatManager::HIT_LLEG:
					buffer << legLocations[System::random(1) + 1];
					break;
				case CombatManager::HIT_RLEG:
					buffer << legLocations[System::random(1)];
					break;
				case CombatManager::HIT_HEAD:
					buffer << headLocations[System::random(2)];
					break;
				}

				buffer << intensity;

				// TODO: Actually sequence these
				buffer << "_" << String::valueOf(System::random(3));
			}
		} else {
			if (attacker->getGameObjectType() == SceneObjectType::DROIDCREATURE || attacker->getGameObjectType() == SceneObjectType::PROBOTCREATURE)
				return "droid_attack" + intensity;
			else if (weapon->isRangedWeapon())
				return "creature_attack_ranged" + intensity;
			else
				return "creature_attack" + intensity;
		}

		//info("Generated Attack Animation- " + buffer.toString(), true);
		return buffer.toString();
	}

	inline String generateAnimation(uint8 hitLocation, int weaponThreshold, int damage) const {
		String anim = animation;

		switch(animType) {
		case GENERATE_NONE:
			break;
		case GENERATE_RANGED:
		case GENERATE_INTENSITY:
			anim += getIntensity(weaponThreshold, damage);

			if (animType == GENERATE_INTENSITY)
				return anim;

			if (hitLocation == CombatManager::HIT_HEAD)
				anim += "_face";

			return anim;
		}
		//info("Generated Attack Animation- " + anim, true);
		return anim;
	}

	virtual String getAnimation(TangibleObject* attacker, TangibleObject* defender, WeaponObject* weapon, uint8 hitLocation, int damage) const {

		if (animation.isEmpty())
			return getDefaultAttackAnimation(attacker, weapon, hitLocation, damage);

		return generateAnimation(hitLocation, ((uint32)weapon->getMaxDamage()) >> 2, damage);
	}

	inline const String& getEffectString() const {
		return effectString;
	}

	inline const String& getCombatSpam() const {
		return combatSpam;
	}

	inline int getPoolsToDamage() const {
		return poolsToDamage;
	}

	inline VectorMap<uint8, StateEffect>* getStateEffects() const {
		return &(const_cast<CombatQueueCommand*>(this)->stateEffects);
	}

	inline Vector<DotEffect>* getDotEffects() const {
		return &(const_cast<CombatQueueCommand*>(this)->dotEffects);
	}

	void setAnimationString(const String& anim) {
		this->animation = anim;
	}

	void setCombatSpam(const String& combatSpam) {
		this->combatSpam = combatSpam;
	}

	void setPoolsToDamage(int poolsToDamage) {
		this->poolsToDamage = poolsToDamage;
	}

	void setStateEffects(VectorMap<uint8, StateEffect> stateEffects) {
		this->stateEffects = stateEffects;
	}

	void addStateEffect(const StateEffect& stateEffect) {
		stateEffects.put(stateEffect.getEffectType(), stateEffect);
	}

	const StateEffect& getStateEffect(uint8 type) const {
		return const_cast<CombatQueueCommand*>(this)->stateEffects.get(type);
	}

	void setDotEffects(const Vector<DotEffect>& dotEffects) {
		this->dotEffects = dotEffects;
	}

	inline float getMinDamage() const {
		return minDamage;
	}

	void setMinDamage(float dm) {
		this->minDamage = dm;
	}

	inline float getMaxDamage() const {
		return maxDamage;
	}

	void setMaxDamage(float dm) {
		this->maxDamage = dm;
	}

	inline int getDamageType() const {
		return damageType;
	}

	void setDamageType(float dm) {
		this->damageType = dm;
	}

	void addDotEffect(const DotEffect& dotEffect) {
		dotEffects.add(dotEffect);
	}

	void setConeRange(int i) {
		this->coneRange = i;
	}

	void setRange(int i) {
		this->range = i;
	}

	void setAccuracySkillMod(const String& acc) {
		this->accuracySkillMod = acc;
	}

	bool hasCombatSpam() {
		return !combatSpam.isEmpty();
	}

	bool isCombatCommand() {
		return true;
	}

	virtual bool isSquadLeaderCommand() {
		return false;
	}

	// this goes in command in order to allow for overriding for special commands
	virtual void applyEffect(CreatureObject* attacker, CreatureObject* defender, uint8 effectType, uint32 mod) const {
		CombatManager* combatManager = CombatManager::instance();
		StateEffect effect = getStateEffect(effectType);
		Reference<Buff*> buff = NULL;

		Vector<String> defenseMods = effect.getDefenderStateDefenseModifiers();
		float targetDefense = 0.f;
		for (int j = 0; j < defenseMods.size(); j++)
			targetDefense += defender->getSkillMod(defenseMods.get(j));

		targetDefense -= mod;

		uint32 duration = (uint32) Math::max(5.f, effect.getStateLength()*(1.f-targetDefense/120.f));

		switch (effectType) {
		case CommandEffect::BLIND:
			defender->setBlindedState(duration);
			break;
		case CommandEffect::DIZZY:
			defender->setDizziedState(duration);
			break;
		case CommandEffect::INTIMIDATE:
			defender->setIntimidatedState(duration);
			break;
		case CommandEffect::STUN:
			defender->setStunnedState(duration);
			break;
		case CommandEffect::KNOCKDOWN:
			if (!defender->checkKnockdownRecovery()) {
				if (defender->getPosture() != CreaturePosture::UPRIGHT)
					defender->setPosture(CreaturePosture::UPRIGHT, false, false);
				break;
			}

			if (defender->isRidingMount()) {
				defender->updateCooldownTimer("mount_dismount", 0);
				defender->dismount();
			}

			if (!defender->isDead() && !defender->isIncapacitated())
				defender->setPosture(CreaturePosture::KNOCKEDDOWN, false, false);

			defender->updateKnockdownRecovery();
			defender->updatePostureChangeDelay(5000);
			defender->removeBuff(STRING_HASHCODE("burstrun"));
			defender->removeBuff(STRING_HASHCODE("retreat"));
			defender->sendSystemMessage("@cbt_spam:posture_knocked_down");
			defender->sendStateCombatSpam("cbt_spam", "posture_knocked_down", 0, 0, false);
			break;
		case CommandEffect::POSTUREUP:
			if (!defender->checkPostureUpRecovery()) {
				if (defender->getPosture() != CreaturePosture::UPRIGHT)
					defender->setPosture(CreaturePosture::UPRIGHT, false, false);
				break;
			}

			if (defender->isRidingMount()) {
				defender->updateCooldownTimer("mount_dismount", 0);
				defender->dismount();
			}

			if (defender->getPosture() == CreaturePosture::PRONE) {
				defender->setPosture(CreaturePosture::CROUCHED, false, false);
				defender->sendSystemMessage("@cbt_spam:force_posture_change_1");
				defender->sendStateCombatSpam("cbt_spam", "force_posture_change_1", 0, 0, false);
			} else if (defender->getPosture() == CreaturePosture::CROUCHED) {
				defender->setPosture(CreaturePosture::UPRIGHT, false, false);
				defender->sendSystemMessage("@cbt_spam:force_posture_change_0");
				defender->sendStateCombatSpam("cbt_spam", "force_posture_change_0", 0, 0, false);
			}

			defender->updatePostureUpRecovery();
			defender->updatePostureChangeDelay(2500);
			defender->removeBuff(STRING_HASHCODE("burstrun"));
			defender->removeBuff(STRING_HASHCODE("retreat"));
			break;
		case CommandEffect::POSTUREDOWN:
			if (!defender->checkPostureDownRecovery()) {
				if (defender->getPosture() != CreaturePosture::UPRIGHT)
					defender->setPosture(CreaturePosture::UPRIGHT, false, false);
				break;
			}

			if (defender->isRidingMount()) {
				defender->updateCooldownTimer("mount_dismount", 0);
				defender->dismount();
			}

			if (defender->getPosture() == CreaturePosture::UPRIGHT) {
				defender->setPosture(CreaturePosture::CROUCHED, false, false);
				defender->sendSystemMessage("@cbt_spam:force_posture_change_1");
				defender->sendStateCombatSpam("cbt_spam", "force_posture_change_1", 0, 0, false);
			} else if (defender->getPosture() == CreaturePosture::CROUCHED) {
				defender->setPosture(CreaturePosture::PRONE, false, false);
				defender->sendSystemMessage("@cbt_spam:force_posture_change_2");
				defender->sendStateCombatSpam("cbt_spam", "force_posture_change_2", 0, 0, false);
			}

			defender->updatePostureDownRecovery();
			defender->updatePostureChangeDelay(2500);
			defender->removeBuff(STRING_HASHCODE("burstrun"));
			defender->removeBuff(STRING_HASHCODE("retreat"));
			break;
		case CommandEffect::NEXTATTACKDELAY:
			defender->setNextAttackDelay(mod, duration);
			break;
		case CommandEffect::HEALTHDEGRADE:
			buff = new Buff(defender, STRING_HASHCODE("healthdegrade"), duration, BuffType::STATE);
			buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, -1*effect.getStateStrength());
			buff->setAttributeModifier(CreatureAttribute::STRENGTH, -1*effect.getStateStrength());
			defender->addBuff(buff);
			break;
		case CommandEffect::ACTIONDEGRADE:
			buff = new Buff(defender, STRING_HASHCODE("actiondegrade"), duration, BuffType::STATE);
			buff->setAttributeModifier(CreatureAttribute::QUICKNESS, -1*effect.getStateStrength());
			buff->setAttributeModifier(CreatureAttribute::STAMINA, -1*effect.getStateStrength());
			defender->addBuff(buff);
			break;
		case CommandEffect::MINDDEGRADE:
			buff = new Buff(defender, STRING_HASHCODE("minddegrade"), duration, BuffType::STATE);
			buff->setAttributeModifier(CreatureAttribute::FOCUS, -1*effect.getStateStrength());
			buff->setAttributeModifier(CreatureAttribute::WILLPOWER, -1*effect.getStateStrength());
			defender->addBuff(buff);
			break;
		case CommandEffect::REMOVECOVER:
			if (defender->hasState(CreatureState::COVER)) {
				defender->clearState(CreatureState::COVER);
				defender->sendSystemMessage("@combat_effects:strafe_system");
				defender->setNextAttackDelay(mod, duration);
			}
			break;
		case CommandEffect::ATTACKER_FORCE_STAND:
			attacker->setPosture(CreaturePosture::UPRIGHT, false, false);
			break;
		case CommandEffect::ATTACKER_FORCE_CROUCH:
			attacker->setPosture(CreaturePosture::CROUCHED, false, false);
			break;
		case CommandEffect::ATTACKER_FORCE_PRONE:
			attacker->setPosture(CreaturePosture::PRONE, false, false);
			break;
		default:
			break;
		}
		return;
	}

	//Override for special cases (skills like Taunt that don't have 5 result strings)
	virtual void sendAttackCombatSpam(TangibleObject* attacker, TangibleObject* defender, int attackResult, int damage, const CreatureAttackData& data) const {
		if (attacker == NULL || defender == NULL)
			return;

		String stringName = data.getCombatSpam();
		byte color = 0;

		switch (attackResult) {
		case CombatManager::HIT:
			stringName += "_hit";
			color = 1;
			break;
		case CombatManager::MISS:
			stringName += "_miss";
			break;
		case CombatManager::DODGE:
			stringName += "_evade";
			break;
		case CombatManager::COUNTER:
			stringName += "_counter";
			break;
		case CombatManager::BLOCK:
		case CombatManager::RICOCHET:
			stringName += "_block";
			break;
		default:
			break;
		}

		CombatManager::instance()->broadcastCombatSpam(attacker, defender, NULL, damage, "cbt_spam", stringName, color);

	}

	bool isForceAttack() const {
		return forceAttack;
	}

	void setForceAttack(bool forceAttack) {
		this->forceAttack = forceAttack;
	}

	uint8 getTrails() const {
		return trails;
	}

	void setTrails(uint8 trails) {
		this->trails = trails;
	}

	uint32 getWeaponType() const {
		return weaponType;
	}

	void setWeaponType(uint32 weaponType) {
		this->weaponType = weaponType;
	}

	bool validateWeapon(WeaponObject* weapon) {
		return true;
	}

	void setVisMod(int vm) {
		visMod = vm;
	}

	int getVisMod() const {
		return visMod;
	}

};

#endif /* COMBATQUEUECOMMAND_H_ */
