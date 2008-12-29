/*
 * ThrowDirectPoolAttackTargetSkill.h
 *
 *  Created on: Oct 28, 2008
 *      Author: swgdev
 */

#ifndef THROWDIRECTPOOLATTACKTARGETSKILL_H_
#define THROWDIRECTPOOLATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"
#include "../../../../tangible/weapons/ThrowableWeapon.h"
#include "../../../../tangible/weapons/throwable/TrapThrowableWeapon.h"

class ThrowDirectPoolAttackTargetSkill: public AttackTargetSkill {
protected:
	bool missed;
public:
	ThrowDirectPoolAttackTargetSkill(const String& name, const String& anim,
			ZoneProcessServerImplementation* serv) :
		AttackTargetSkill(name, anim, DIRECT, serv) {
		healthPoolAttackChance = 0;
		strengthPoolAttackChance = 0;
		constitutionPoolAttackChance = 0;

		actionPoolAttackChance = 0;
		quicknessPoolAttackChance = 0;
		staminaPoolAttackChance = 0;

		mindPoolAttackChance = 0;
		focusPoolAttackChance = 0;
		willpowerPoolAttackChance = 0;

		type = THROW;
		damageRatio = 1.0;

		requiredWeaponType = 0xFF;

		range = 32.0f;

		missed = false;
	}

	int doSkill(CreatureObject* creature, SceneObject* target,
			const String& modifier, bool doAnimation) {

		TrapThrowableWeapon* trap = (TrapThrowableWeapon*) getThrowableWeapon(
				creature, modifier);

		if (trap == NULL)
			return 0;

		CreatureObject* targetCreature = (CreatureObject*) target;
		Player* player = (Player*) creature;

		if (!targetCreature->isCreature()) {
			player->sendSystemMessage("traps/traps", "sys_creatures_only");
			return 0;
		}

		trap->useCharge(player);

		int damage = calculateTrapDamage(creature, target, ((Weapon*) trap));

		if (damage && targetCreature->hasAttackDelay())
			targetCreature->clearAttackDelay();

		StfParameter* params = new StfParameter();
		StringBuffer creatureName;
		creatureName << "@" << targetCreature->getStfName() << ":"
				<< targetCreature->getSpeciesName();
		params->addTT(creatureName.toString());

		if (damage != 0) {

			String type = "trapping";

			int xp = int(targetCreature->getLevel() * 10);

			player->addXp(type, xp, true);

			player->sendSystemMessage(getDeBuffStrFile(), getDeBuffMessage(), params);

			missed = false;

		} else {

			player->sendSystemMessage(getDeBuffStrFile(), getDeBuffEndMessage(), params);

			missed = true;

		}
		return damage;
	}

	void doMiss(CreatureObject* creature, CreatureObject* target, int32 damage) {

		target->showFlyText("trap/trap", "sys_miss", 0xFF, 0xFF, 0xFF);
	}

	virtual int calculateTrapDamage(CreatureObject* creature,
			SceneObject* target, Weapon* weapon) {

		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature())
			targetCreature = (CreatureObject*) target;

		float minDamage = 0;
		float maxDamage = 0;
		float healthDamage = 0;
		float actionDamage = 0;
		float mindDamage = 0;
		int reduction = 0;

		minDamage = weapon->getMinDamage();
		maxDamage = weapon->getMaxDamage();

		if (targetCreature != NULL)
			checkMitigation(creature, targetCreature, minDamage, maxDamage);

		float damage = 0;
		int average = 0;

		int diff = (int) maxDamage - (int) minDamage;
		if (diff >= 0)
			average = System::random(diff) + (int) minDamage;

		if (targetCreature != NULL) {

			int rand = System::random(100);

			int trappingSkill = creature->getSkillMod("trapping");

			int level = targetCreature->getLevel(); //336 ancient krayt

			if(level > 180)
				level = 180;

			if ((trappingSkill + rand > level) || (rand > 10 && rand < 20)) {

				int secondaryDefense = checkSecondaryDefenses(creature,
						targetCreature);

				if (secondaryDefense < 2) {
					if (secondaryDefense == 1)
						damage = damage / 2;

					if (healthPoolAttackChance != 0) {
						healthDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								healthDamage);

						damage += healthDamage;
					}

					if (strengthPoolAttackChance != 0) {

						float strengthDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								strengthDamage);

						applyStrengthPoolDamage(targetCreature,
								(int32) strengthDamage);

						damage += strengthDamage;
					}

					if (constitutionPoolAttackChance != 0) {

						float constitutionDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								constitutionDamage);

						applyConstitutionPoolDamage(targetCreature,
								(int32) constitutionDamage);

						damage += constitutionDamage;
					}

					if (actionPoolAttackChance != 0) {
						actionDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								actionDamage);

						damage += actionDamage;
					}

					if (quicknessPoolAttackChance != 0) {

						float quicknessDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								quicknessDamage);

						applyQuicknessPoolDamage(targetCreature,
								(int32) quicknessDamage);

						damage += quicknessDamage;
					}

					if (staminaPoolAttackChance != 0) {

						float staminaDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								staminaDamage);

						applyStaminaPoolDamage(targetCreature,
								(int32) staminaDamage);

						damage += staminaDamage;
					}

					if (mindPoolAttackChance != 0) {
						mindDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								mindDamage);

						damage += mindDamage;
					}

					if (focusPoolAttackChance != 0) {

						float focusDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								focusDamage);

						applyFocusPoolDamage(targetCreature,
								(int32) focusDamage);

						damage += focusDamage;
					}

					if (willpowerPoolAttackChance != 0) {

						float willpowerDamage = damageRatio * average;
						calculateDamageReduction(creature, targetCreature,
								willpowerDamage);

						applyWillpowerPoolDamage(targetCreature,
								(int32) willpowerDamage);

						damage += willpowerDamage;
					}
				} else
					return 0;

				if (damage == 0) {
					doMiss(creature, targetCreature, (int32) damage);
					return 0;
				}

				if (hasCbtSpamHit() && healthDamage < targetCreature->getHealth() &&
						actionDamage < targetCreature->getAction() &&
						mindDamage < targetCreature->getMind())
					creature->sendCombatSpam(targetCreature, NULL,
							(int32) damage, getCbtSpamHit());

				if (healthDamage > 0 && healthDamage < targetCreature->getHealth())
					reduction = applyHealthPoolDamage(creature, targetCreature,
							(int32) healthDamage, System::random(5) + 1);
				if (actionDamage > 0 && actionDamage < targetCreature->getAction())
					reduction = applyActionPoolDamage(creature, targetCreature,
							(int32) actionDamage, System::random(1) + 7);
				if (mindDamage > 0 && mindDamage < targetCreature->getMind())
					reduction = applyMindPoolDamage(creature, targetCreature,
							(int32) mindDamage);

				if (weapon != NULL) {
					doDotWeaponAttack(creature, targetCreature, 0);

					if (weapon->decreasePowerupUses())
						weapon->setUpdated(true);
					else if (weapon->hasPowerup())
						weapon->removePowerup((Player*) creature, true);
				}

			} else {
				doMiss(creature, targetCreature, (int32) damage);
				return 0;
			}
		} else {
			return (int32) damageRatio * average;
		}

		return (int32) damage - reduction;
	}

	virtual int calculateDamage(CreatureObject* creature, SceneObject* target) {
		return 0;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*) creature;

		int wpnHealth = 20;
		int wpnAction = 80;
		int wpnMind = 10;

		int healthAttackCost = wpnHealth - (wpnHealth * creature->getStrength()
				/ 1500);
		int actionAttackCost = wpnAction - (wpnAction
				* creature->getQuickness() / 1500);
		int mindAttackCost = wpnMind - (wpnMind * creature->getFocus() / 1500);

		if (healthAttackCost < 0)
			healthAttackCost = 0;

		if (actionAttackCost < 0)
			actionAttackCost = 0;

		if (mindAttackCost < 0)
			mindAttackCost = 0;

		if (!player->changeHAMBars(-healthAttackCost, -actionAttackCost,
				-mindAttackCost))
			return false;

		return true;
	}

	void calculateStates(CreatureObject* creature,
			CreatureObject* targetCreature) {

		if (missed)
			return;

		bool debuffHit = false;

		if (hasStateChance) {

			if (dizzyStateChance != 0)
				targetCreature->setDizziedState();

			if (blindStateChance != 0)
				targetCreature->setBlindedState();

			if (stunStateChance != 0)
				targetCreature->setStunnedState();

			if (intimidateStateChance != 0)
				targetCreature->setIntimidatedState();

			if (snareStateChance != 0)
				targetCreature->setSnaredState();

			if (rootStateChance != 0)
				targetCreature->setRootedState();

			targetCreature->updateStates();
		}

		if (isDebuff()) {
			if (targetCreature->hasBuff(getNameCRC())) {
				return;
			}

			int duration = 30;
			Buff* deBuff = new Buff(getNameCRC(), 0, duration);
			if (meleeDefDebuff != 0) {
				deBuff->addSkillModBuff("melee_defense", meleeDefDebuff);
				targetCreature->showFlyText("trap/trap", "melee_def_1_on", 255, 255, 255);
				debuffHit = true;
			}
			if (rangedDefDebuff != 0) {
				deBuff->addSkillModBuff("ranged_defense", rangedDefDebuff);
				targetCreature->showFlyText("trap/trap", "ranged_def_1_on", 255, 255, 255);
				debuffHit = true;
			}
			if (intimidateDefDebuff != 0) {
				deBuff->addSkillModBuff("intimidate_defense",
						intimidateDefDebuff);
				targetCreature->showFlyText("trap/trap", "melee_ranged_def_1_on", 255, 255, 255);
				debuffHit = true;
			}
			if (stunDefDebuff != 0) {
				deBuff->addSkillModBuff("stun_defense", stunDefDebuff);
				targetCreature->showFlyText("trap/trap", "state_def_1_on", 255, 255, 255);
				debuffHit = true;
			}

			if (debuffHit) {
				BuffObject* bo = new BuffObject(deBuff);
				targetCreature->applyBuff(bo);
			}
		}
	}

};

#endif /* THROWDIRECTPOOLATTACKTARGETSKILL_H_ */
