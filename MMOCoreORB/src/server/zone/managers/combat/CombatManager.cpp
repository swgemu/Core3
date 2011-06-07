/*
 * CombatManager.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CombatManager.h"
#include "CreatureAttackData.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/collision/CollisionManager.h"

const uint32 CombatManager::defaultAttacks[9] = {
		0x99476628, 0xF5547B91, 0x3CE273EC, 0x734C00C,
		0x43C4FFD0, 0x56D7CC78, 0x4B41CAFB, 0x2257D06B,
		0x306887EB
};


bool CombatManager::startCombat(CreatureObject* attacker, TangibleObject* defender, bool lockDefender) {
	if (attacker == defender)
		return false;

	if (attacker->getZone() == NULL || defender->getZone() == NULL)
		return false;

	bool success = true;

	if (attacker->isRidingMount())
		return false;

	if (!defender->isAttackableBy(attacker))
		return false;

	if (defender->isCreatureObject() && ((CreatureObject*)defender)->isIncapacitated())
		return false;

	attacker->clearState(CreatureState::PEACE);

	if (attacker->isEntertaining())
		attacker->stopEntertaining();

	Locker clocker(defender, attacker);

	attacker->setDefender(defender);
	defender->addDefender(attacker);

	return success;
}

bool CombatManager::attemptPeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* defender = (TangibleObject*) object.get();

		try {
			Locker clocker(defender, attacker);

			if (defender->hasDefender(attacker)) {

				if (defender->isCreatureObject()) {
					CreatureObject* creature = (CreatureObject*) defender;

					if (creature->getMainDefender() != attacker) {
						attacker->removeDefender(defender);
						defender->removeDefender(attacker);

						--i;
					} else if (creature->hasState(CreatureState::PEACE) || creature->isDead() || attacker->isDead()) {
						attacker->removeDefender(defender);
						defender->removeDefender(attacker);

						--i;
					}
				} else {
					attacker->removeDefender(defender);
					defender->removeDefender(attacker);

					--i;
				}
			} else {
				attacker->removeDefender(defender);
				--i;
			}

			clocker.release();

		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}
	}

	if (defenderList->size() != 0) {
		//info("defenderList not empty, trying to set Peace State");

		attacker->setState(CreatureState::PEACE);

		return false;
	} else {
		attacker->clearCombatState(false);

		return true;
	}
}

void CombatManager::forcePeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* defender = (TangibleObject*) object.get();

		Locker clocker(defender, attacker);

		if (defender->hasDefender(attacker)) {
			attacker->removeDefender(defender);
			defender->removeDefender(attacker);
		} else {
			attacker->removeDefender(defender);
		}

		--i;

		clocker.release();
	}

	attacker->clearCombatState(false);
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* command) {
	return doCombatAction(attacker, defenderObject, CreatureAttackData("",command));
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data) {
	//info("entering doCombat action", true);

	if (!startCombat(attacker, defenderObject))
		return -1;

	//info("past start combat", true);

	if (!applySpecialAttackCost(attacker, data))
		return -2;

	//info("past special attack cost", true);

	if (attacker->hasAttackDelay())
		return -3;

	//info("past delay", true);

	if (attacker->isBerserked() && data.getCommandCRC() != 0xA8FEF90A) //berserk only works with attack
		return -3;

	//info("past berserk", true);

	int damage = 0;

	if (data.getCommand()->isAreaAction() || data.getCommand()->isConeAction())
		damage = doAreaCombatAction(attacker, defenderObject, data);
	else
		damage = doTargetCombatAction(attacker, defenderObject, data);

	CombatAction* combatAction = NULL;

	uint32 animationCRC = data.getAnimationCRC();

	if (animationCRC == 0)
		animationCRC = getDefaultAttackAnimation(attacker);

	if (attacker->isCreature())
		animationCRC = String("creature_attack_light").hashCode();

	uint8 hit = damage != 0 ? 1 : 0;

	if (defenderObject->isCreatureObject()) {
		combatAction = new CombatAction(attacker, (CreatureObject*)defenderObject, animationCRC, hit);
	} else {
		combatAction = new CombatAction(attacker, defenderObject, data.getAnimationCRC(), hit);
	}

	attacker->broadcastMessage(combatAction, true);

	String effect = data.getCommand()->getEffectString();

	if (!effect.isEmpty())
		attacker->playEffect(effect);

	if (hit == 1) {
		attacker->updateLastSuccessfulCombatAction();

		Locker clocker(defenderObject, attacker);

		defenderObject->notifyObservers(ObserverEventType::DAMAGERECEIVED, attacker, damage);
	}

	return damage;
}

int CombatManager::doTargetCombatAction(CreatureObject* attacker, TangibleObject* tano, const CreatureAttackData& data) {
	int damage = 0;

	Locker clocker(tano, attacker);

	attacker->addDefender(tano);
	tano->addDefender(attacker);

	if (tano->isCreatureObject()) {
		CreatureObject* defender = (CreatureObject*) tano;

		damage = doTargetCombatAction(attacker, defender, data);
	} else {
		int poolsToDamage = calculatePoolsToDamage(data.getPoolsToDamage());

		damage = applyDamage(attacker, tano, damage, poolsToDamage);

		broadcastCombatSpam(attacker, tano, attacker->getWeapon(), damage, data.getCommand()->getCombatSpam() + "_hit");
	}

	return damage;
}

int CombatManager::doTargetCombatAction(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data) {
	if (defender->isEntertaining())
		defender->stopEntertaining();

	int rand = System::random(100);

	int poolsToDamage = calculatePoolsToDamage(data.getPoolsToDamage());

	if (poolsToDamage != 0 && rand > getHitChance(attacker, defender, attacker->getWeapon(), 0)) {
		//better luck next time
		doMiss(attacker, defender, 0, data.getCommand()->getCombatSpam() + "_miss");
		return 0;
	}

	int damage = 0;

	String combatSpam = data.getCommand()->getCombatSpam();
	float damageMultiplier = data.getDamageMultiplier();

	if (damageMultiplier != 0 && poolsToDamage != 0) {
		int secondaryDefense = checkSecondaryDefenses(attacker, defender, attacker->getWeapon());

		if (secondaryDefense != 0) {
			switch (secondaryDefense) {
			case BLOCK:
				damageMultiplier /= 2.f;
				doBlock(attacker, defender, damage, combatSpam + "_block");
				break;
			case DODGE:
				doDodge(attacker, defender, damage, combatSpam + "_evade");
				return 0;
				break;
			case COUNTER:
				doCounterAttack(attacker, defender, damage, combatSpam + "_counter");
				return 0;
				break;
			default:
				break;
			}
		}

		damage = applyDamage(attacker, defender, damageMultiplier, poolsToDamage);
	}

	applyStates(attacker, defender, data);
	attemptApplyDot(attacker, defender, data, damage);

	broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, combatSpam + "_hit");

	if (damage != 0 && defender->hasAttackDelay())
		defender->removeAttackDelay();

	return damage;
}

bool CombatManager::attemptApplyDot(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data, int appliedDamage) {
	uint32 duration = data.getDotDuration();

	if (duration == 0) {
		//info("dot duration 0", true);
		return false;
	}

	uint64 type = data.getDotType();
	uint8 dotPool = data.getDotPool();
	uint32 strength = data.getDotStrength();
	float potency = data.getDotPotency();
	bool dotDamageOfHit = data.getCommand()->isDotDamageOfHit();

	if (dotDamageOfHit) {
		if (appliedDamage < 1) {
			//info("applieddamage < 1", true);
			return false;
		}

		strength = appliedDamage;
	}

	int resist = 0;

	switch (type) {
	case CreatureState::BLEEDING:
		resist = defender->getSkillMod("resistance_bleeding");
		break;
	case CreatureState::POISONED:
		resist = defender->getSkillMod("resistance_poison");
		break;
	case CreatureState::DISEASED:
		resist = defender->getSkillMod("resistance_disease");
		break;
	case CreatureState::ONFIRE:
		resist = defender->getSkillMod("resistance_fire");
		break;
	}

	//info("entering addDotState", true);

	int applied = defender->addDotState(type, strength, dotPool, duration, potency, resist);

	return applied != 0;
}

float CombatManager::getWeaponRangeModifier(float currentRange, WeaponObject* weapon) {
	float accuracy;

	float smallRange = 0;
	float idealRange = 2;
	float maxRange = 5;

	float smallMod = 7;
	float bigMod = 7;

	if (weapon != NULL) {
		smallRange = (float) weapon->getPointBlankRange();
		idealRange = (float) weapon->getIdealRange();
		maxRange = (float) weapon->getMaxRange();

		smallMod = (float) weapon->getPointBlankAccuracy();
		bigMod = (float) weapon->getIdealAccuracy();
	}

	if (currentRange > idealRange) {
		if (weapon != NULL) {
			smallMod = (float) weapon->getIdealAccuracy();
			bigMod = (float) weapon->getMaxRangeAccuracy();
		}

		idealRange = maxRange;
	}

	accuracy = smallMod + ((currentRange - smallRange) / (idealRange != smallRange ? idealRange - smallRange : 1) * (bigMod - smallMod));

	return accuracy;
}

int CombatManager::calculatePostureModifier(CreatureObject* creature, CreatureObject* targetCreature) {
	int accuracy = 0;
	WeaponObject* weapon = creature->getWeapon();

	if (targetCreature->isKneeling()) {
		if (weapon->isMeleeWeapon())
			accuracy += 16;
		else
			accuracy -= 16;
	} else if (targetCreature->isProne()) {
		if (weapon->isMeleeWeapon())
			accuracy += 25;
		else
			accuracy -= 25;
	}

	if (creature->isKneeling()) {
		if (weapon->isMeleeWeapon())
			accuracy -= 16;
		else
			accuracy += 16;
	} else if (creature->isProne()) {
		if (weapon->isMeleeWeapon())
			accuracy -= 50;
		else
			accuracy += 50;
	}

	return accuracy;
}

int CombatManager::getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int attackerAccuracy = 0;

	Vector<String>* creatureAccMods = weapon->getCreatureAccuracyModifiers();

	for (int i = 0; i < creatureAccMods->size(); ++i) {
		attackerAccuracy += attacker->getSkillMod(creatureAccMods->get(i));
	}

	if (attacker->isAiAgent()) {
		ManagedReference<AiAgent*> creoAttacker = dynamic_cast<AiAgent*>(attacker);
		attackerAccuracy += creoAttacker->getChanceHit() * 100;
	}

	return attackerAccuracy;
}

int CombatManager::getDefenderDefenseModifier(CreatureObject* defender, WeaponObject* weapon) {
	int targetDefense = 0;

	Vector<String>* defenseAccMods = weapon->getDefenderDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		targetDefense += defender->getSkillMod(defenseAccMods->get(i));
	}

	return targetDefense;
}

int CombatManager::getDefenderSecondaryDefenseModifier(CreatureObject* defender, WeaponObject* weapon) {
	int targetDefense = 0;

	Vector<String>* defenseAccMods = weapon->getDefenderSecondaryDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		targetDefense += defender->getSkillMod(defenseAccMods->get(i));
	}

	return targetDefense;
}

float CombatManager::hitChanceEquation(float attackerAccuracy, float accuracyBonus, float targetDefense, float defenseBonus) {

	float accTotal = 66.0 + (attackerAccuracy + accuracyBonus - targetDefense - defenseBonus) / 2.0;

	/*StringBuffer msg;
	msg << "HitChance\n";
	msg << "\tTarget Defense " << targetDefense << "\n";
	msg << "\tTarget Defense Bonus" << defenseBonus << "\n";

	info(msg.toString());*/

	return accTotal;
}

int CombatManager::getDamageModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int damageMods = 0;

	Vector<String>* weaponDamageMods = weapon->getDamageModifiers();

	for (int i = 0; i < weaponDamageMods->size(); ++i) {
		damageMods += attacker->getSkillMod(weaponDamageMods->get(i));
	}

	return damageMods;
}

int CombatManager::getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int speedMods = 0;

	Vector<String>* weaponSpeedMods = weapon->getSpeedModifiers();

	for (int i = 0; i < weaponSpeedMods->size(); ++i) {
		speedMods += attacker->getSkillMod(weaponSpeedMods->get(i));
	}

	return speedMods;
}

int CombatManager::getArmorObjectReduction(CreatureObject* attacker, ArmorObject* armor) {
	WeaponObject* weapon = attacker->getWeapon();

	int damageType = weapon->getDamageType();

	float resist = 0;

	switch (damageType) {
	case WeaponObject::KINETIC:
		resist = armor->getKinetic();
		break;
	case WeaponObject::ENERGY:
		resist = armor->getEnergy();
		break;
	case WeaponObject::ELECTRICITY:
		resist = armor->getElectricity();
		break;
	case WeaponObject::STUN:
		resist = armor->getStun();
		break;
	case WeaponObject::BLAST:
		resist = armor->getBlast();
		break;
	case WeaponObject::HEAT:
		resist = armor->getHeat();
		break;
	case WeaponObject::COLD:
		resist = armor->getCold();
		break;
	case WeaponObject::ACID:
		resist = armor->getAcid();
		break;
	case WeaponObject::LIGHTSABER:
		resist = armor->getLightSaber();
		break;
	case WeaponObject::FORCE:
		resist = 0;
		break;
	}

	return (int)resist;

}

int CombatManager::getHealthArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	int reduction = 0;

	SceneObject* chest = defender->getSlottedObject("chest2");
	/*SceneObject* bicepr = defender->getSlottedObject("bicep_r");
	SceneObject* bicepl = defender->getSlottedObject("bicep_l");
	SceneObject* bracerr = defender->getSlottedObject("bracer_upper_r");
	SceneObject* bracerl = defender->getSlottedObject("bracer_upper_l");*/

	ArmorObject* armorToHit = NULL;

	if (chest != NULL && chest->isArmorObject())
		armorToHit = (ArmorObject*) chest;

	/*int rand = System::random(100);

	if (rand < 20) { // chest
		if (chest != NULL && chest->isArmorObject())
			armorToHit = (ArmorObject*) chest;
	} else if (rand < 40) { // bicepr
		if (bicepr != NULL && bicepr->isArmorObject())
			armorToHit = (ArmorObject*) bicepr;
	} else if (rand < 60) { // bicepl
		if (bicepl != NULL && bicepl->isArmorObject())
			armorToHit = (ArmorObject*) bicepl;
	} else if (rand < 80) { // bracerr
		if (bracerr != NULL && bracerr->isArmorObject())
			armorToHit = (ArmorObject*) bracerr;
	} else { //bracerl
		if (bracerl != NULL && bracerl->isArmorObject())
			armorToHit = (ArmorObject*) bracerl;
	}*/

	if (armorToHit == NULL)
		return 0;

	return getArmorObjectReduction(attacker, armorToHit);
}

int CombatManager::getActionArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* gloves = defender->getSlottedObject("gloves");
	SceneObject* boots = defender->getSlottedObject("shoes");

	ArmorObject* armorToHit = NULL;

	int rand = System::random(1);

	if (rand == 1) {
		if (gloves != NULL && gloves->isArmorObject())
			armorToHit = (ArmorObject*) gloves;
	} else {
		if (boots != NULL && boots->isArmorObject())
			armorToHit = (ArmorObject*) boots;
	}

	if (armorToHit == NULL)
		return 0;

	return getArmorObjectReduction(attacker, armorToHit);
}

int CombatManager::getMindArmorReduction(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* helmet = defender->getSlottedObject("hat");

	if (helmet != NULL && helmet->isArmorObject())
		return getArmorObjectReduction(attacker, (ArmorObject*) helmet);

	return 0;
}

int CombatManager::getArmorNpcReduction(CreatureObject* attacker, AiAgent* defender, WeaponObject* weapon) {
	int damageType = weapon->getDamageType();

	float resist = 0;

	switch (damageType) {
	case WeaponObject::KINETIC:
		resist = defender->getKinetic();
		break;
	case WeaponObject::ENERGY:
		resist = defender->getEnergy();
		break;
	case WeaponObject::ELECTRICITY:
		resist = defender->getElectricity();
		break;
	case WeaponObject::STUN:
		resist = defender->getStun();
		break;
	case WeaponObject::BLAST:
		resist = defender->getBlast();
		break;
	case WeaponObject::HEAT:
		resist = defender->getHeat();
		break;
	case WeaponObject::COLD:
		resist = defender->getCold();
		break;
	case WeaponObject::ACID:
		resist = defender->getAcid();
		break;
	case WeaponObject::LIGHTSABER:
		resist = defender->getLightSaber();
		break;
	case WeaponObject::FORCE:
		resist = 0;
		break;
	}

	return (int)resist;
}

int CombatManager::getArmorReduction(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon, float damage, int poolToDamage) {
	if (poolToDamage == 0)
		return 0;

	if (defender->isAiAgent()) {
		return getArmorNpcReduction(attacker, (AiAgent*)defender, weapon);
	}

	if (poolToDamage & CombatManager::HEALTH) {
		return getHealthArmorReduction(attacker, defender);
	} else if (poolToDamage & CombatManager::ACTION) {
		return getActionArmorReduction(attacker, defender);
	} else if (poolToDamage & CombatManager::MIND) {
		return getMindArmorReduction(attacker, defender);
	} else
		return 0;
}

float CombatManager::calculateDamage(CreatureObject* attacker, CreatureObject* defender, int poolToDamage) {
	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	//info("attacker base damage is " + String::valueOf(minDamage) + "-"+ String::valueOf(maxDamage), true);

	int damageType = weapon->getDamageType();
	int attackType = weapon->getAttackType();
	int armorPiercing = weapon->getArmorPiercing(); // None

	int damageMod = getDamageModifier(attacker, weapon);

	//info("attacker weapon damage mod is " + String::valueOf(damageMod), true);

	minDamage += damageMod;
	maxDamage += damageMod;

	float damage = 0;

	int diff = (int) maxDamage - (int) minDamage;

	if (diff >= 0)
		damage = System::random(diff) + (int) minDamage;

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor((PlayerCreature*) attacker))
			damage /= 5;

		int FR = attacker->getSkillMod("force_run");

		if (FR > 1)
			damage /= 4;
	}

	if (attacker->isIntimidated())
		damage *= 0.66f;// damage /= 2;

	if (attacker->isStunned())
		damage *= 0.9f;// damage /= 2;

	if (defender->isKnockedDown())
		damage *= 1.333f;

	float armorReduction = getArmorReduction(attacker, defender, weapon, damage, poolToDamage);

	//info("defender armor reduction is " + String::valueOf(armorReduction), true);

	if (armorReduction > 0)
		damage *= (1.f - (armorReduction /= 100.f));

	if (defender->isBerserked()) {
		damage += 50;
	}

	//Toughness
	ManagedReference<WeaponObject*> weaponDefender = defender->getWeapon();

	if (weaponDefender != NULL) {
		// Weapon related toughness.
		int toughness = 0;
		int jediToughness = 0;

		if (weaponDefender->isUnarmedWeapon())
			toughness = defender->getSkillMod("unarmed_toughness");
		else if (weaponDefender->isOneHandMeleeWeapon())
			toughness = defender->getSkillMod("onehandmelee_toughness");
		else if (weaponDefender->isTwoHandMeleeWeapon())
			toughness = defender->getSkillMod("twohandmelee_toughness");
		else if (weaponDefender->isPolearmWeaponObject())
			toughness = defender->getSkillMod("polearm_toughness");
		/*else if (weaponDefender->isOneHandLightsaber()){
		toughness = defender->getSkillMod("lightsaber_toughness");

		if (weapon->getDamageType() == WeaponObject::LIGHTSABER)
			jediToughness = defender->getSkillMod("jedi_toughness");
	} else if	(weaponDefender->isTwoHandLightsaber()){
		toughness = defender->getSkillMod("lightsaber_toughness");

		if (weapon->getDamageType() == WeaponObject::LIGHTSABER)
			jediToughness = defender->getSkillMod("jedi_toughness");
	} else if	(weaponDefender->isPolearmLightsaber()){
		toughness = defender->getSkillMod("lightsaber_toughness");

		if (weapon->getDamageType() == WeaponObject::LIGHTSABER)
			jediToughness = defender->getSkillMod("jedi_toughness");
	}*/

		if (!defender->isAiAgent()) { // NPCs/Creatures do not have toughness.
			damage -= damage * (toughness + jediToughness / 1.02f) / 100.0f;
		}
	}

	//info("damage to be dealt is " + String::valueOf(damage), true);

	return damage;
}

int CombatManager::applyAccuracyPenalties(CreatureObject* creature, int attackType, int accuracy) {
	if (creature->isBerserked() && attackType == WeaponObject::MELEEATTACK)
		accuracy -= 10;

	if (creature->isBlinded())
		accuracy -= 50;

	return accuracy;
}

int CombatManager::applyDefensePenalties(CreatureObject* defender, int attackType, int defense) {
	if (defender->isInCover())
		defense += 10;

	if (defender->isStunned())
		defense -= 50;

	return defense;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int accuracyBonus) {
	int hitChance = 0;
	int attackType = weapon->getAttackType();

	//info("Calculating hit chance", true);

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	//info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy), true);

	float aimMod = 0.0;
	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	if (creature->isBerserked() && attackType == WeaponObject::MELEEATTACK) {
		attackerAccuracy -= 10;
	}

	//info("Base attacker accuracy is " + String::valueOf(attackerAccuracy), true);

	int targetDefense = getDefenderDefenseModifier(targetCreature, weapon);

	//info("Base target defense is " + String::valueOf(targetDefense), true);

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	uint32 steadyAim = String("steadyaim").hashCode();

	if ((creature->isAiming()) || (creature->hasBuff(steadyAim))) {
		if (attackType == WeaponObject::RANGEDATTACK)
			aimMod = (float) creature->getSkillMod("aim");

		if (creature->isAiming())
			creature->clearState(CreatureState::AIMING);

		if (creature->hasBuff(steadyAim))
			creature->removeBuff(steadyAim);
	}

	if (targetDefense > 125)
		targetDefense = 125;

	//info("Target defense after state affects and cap is " +  String::valueOf(targetDefense), true);

	float defenseBonus = 0.0f; // TODO: Food/drink defense bonuses go here

	//Food dodge bonus.
	if (targetCreature->hasBuff(BuffCRC::FOOD_DODGE_ATTACK)) {
		Buff* buff = targetCreature->getBuff(BuffCRC::FOOD_DODGE_ATTACK);

		if (buff != NULL)
			defenseBonus += buff->getSkillModifierValue("dodge_attack");
	}

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy + accuracyBonus + aimMod, targetDefense, defenseBonus);

	//info("Final hit chance is " + String::valueOf(accTotal), true);

	if (accTotal > 100)
		accTotal = 100.0;
	else if (accTotal < 0)
		accTotal = 0;

	hitChance = (int) accTotal;

	return hitChance;
}

int CombatManager::checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon) {
	int hitChance = 0;
	int attackType = weapon->getAttackType();

	//info("Calculating secondary hit chance");

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	//info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy));

	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	//info("Base attacker accuracy is " + String::valueOf(attackerAccuracy));

	int targetDefense = getDefenderSecondaryDefenseModifier(targetCreature, weapon);

	if (targetCreature->isPlayerCreature())
		targetDefense += ((PlayerCreature*)targetCreature)->getCenteredBonus();

	//info("Base target secondary defense is " + String::valueOf(targetDefense));

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	if (targetDefense > 125)
		targetDefense = 125;

	//info("Target secondary defense after state affects and cap is " +  String::valueOf(targetDefense));

	if (targetDefense <= 0)
		return 0;

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy, targetDefense, 0);

	int rand = System::random(100);

	if (rand <= (int) accTotal) // Hit, not defended
		return 0;

	ManagedReference<WeaponObject*> targetWeapon = targetCreature->getWeapon();

	if (targetWeapon == NULL)
		return 0;

	Vector<String>* defenseAccMods = targetWeapon->getDefenderSecondaryDefenseModifiers();

	int selectOption = defenseAccMods->size();

	if (selectOption > 1)
		selectOption = System::random(selectOption - 1);
	else
		selectOption = 0;

	String def = defenseAccMods->get(selectOption);

	if (def == "block") {
		return BLOCK;
	} else if (def == "dodge") {
		return DODGE;
	} else if (def == "counterattack") {
		return COUNTER;
	} else
		return COUNTER;
}

float CombatManager::calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio) {
	int speedMod = getSpeedModifier(attacker, weapon);

	float attackSpeed = (1.0f - ((float) speedMod / 100.0f)) * skillSpeedRatio * weapon->getAttackSpeed();

	return MAX(attackSpeed, 1.0f);
}

void CombatManager::doMiss(CreatureObject* attacker, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "miss", 0xFF, 0xFF, 0xFF);

	broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, cbtSpam);
}

void CombatManager::doCounterAttack(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "counterattack", 0, 0xFF, 0);
	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doBlock(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "block", 0, 0xFF, 0);

	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doDodge(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	defender->showFlyText("combat_effects", "dodge", 0, 0xFF, 0);

	defender->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

bool CombatManager::applySpecialAttackCost(CreatureObject* attacker, const CreatureAttackData& data) {
	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();

	int health = (int) (weapon->getHealthAttackCost() * data.getHealthCostMultiplier());
	int action = (int) (weapon->getActionAttackCost() * data.getActionCostMultiplier());
	int mind = (int) (weapon->getMindAttackCost() * data.getMindCostMultiplier());
	int force = (int) (weapon->getForceCost() * data.getForceCostMultiplier());

	health = MAX(0, health - (float(attacker->getHAM(CreatureAttribute::STRENGTH)) / 10.f));
	action = MAX(0, action - (float(attacker->getHAM(CreatureAttribute::QUICKNESS)) / 10.f));
	mind = MAX(0, mind - (float(attacker->getHAM(CreatureAttribute::FOCUS)) / 10.f));

	if (attacker->getHAM(CreatureAttribute::HEALTH) <= health)
		return false;

	if (attacker->getHAM(CreatureAttribute::ACTION) <= action)
		return false;

	if (attacker->getHAM(CreatureAttribute::MIND) <= mind)
		return false;

	if (health > 0) {
		attacker->inflictDamage(attacker, CreatureAttribute::HEALTH, health, true);
	}

	if (action > 0) {
		attacker->inflictDamage(attacker, CreatureAttribute::ACTION, action, true);
	}

	if (mind > 0) {
		attacker->inflictDamage(attacker, CreatureAttribute::MIND, mind, true);
	}

	if (force > 0) {
		//TODO: add force withdrawal
	}

	return true;
}

void CombatManager::checkKnockDown(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (creature->isPlayerCreature() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
		if (80 > System::random(100))
			targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	if (targetCreature->checkKnockdownRecovery() && targetCreature->checkLastKnockdown()) {
		int targetDefense = targetCreature->getSkillMod("knockdown_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());
		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			targetCreature->setPosture(CreaturePosture::KNOCKEDDOWN);
			targetCreature->updateKnockdownRecovery();
			targetCreature->updateLastKnockdown();
			targetCreature->sendSystemMessage("cbt_spam", "posture_knocked_down");

			int combatEquil = targetCreature->getSkillMod("combat_equillibrium");

			if (combatEquil > 100)
				combatEquil = 100;

			if ((combatEquil >> 1) > (int) System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		}
	} else
		creature->sendSystemMessage("cbt_spam", "knockdown_fail");
}


void CombatManager::checkPostureDown(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (creature->isPlayerCreature() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
		if (80 > System::random(100))
			targetCreature->setPosture(CreaturePosture::UPRIGHT, true);

		return;
	}

	if (targetCreature->checkPostureDownRecovery()) {
		int targetDefense = targetCreature->getSkillMod(
				"posture_change_down_defense");
		targetDefense -= (int) (targetDefense
				* targetCreature->calculateBFRatio());

		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			if (targetCreature->getPosture() == CreaturePosture::UPRIGHT)
				targetCreature->setPosture(CreaturePosture::CROUCHED);
			else
				targetCreature->setPosture(CreaturePosture::PRONE);

			targetCreature->updatePostureDownRecovery();
			targetCreature->sendSystemMessage("cbt_spam", "posture_down");

			int combatEquil =
					targetCreature->getSkillMod("combat_equillibrium");

			if (combatEquil > 100)
				combatEquil = 100;

			if ((combatEquil >> 1) > (int) System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		}
	} else
		creature->sendSystemMessage("cbt_spam", "posture_change_fail");
}

void CombatManager::checkPostureUp(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
	if (targetCreature->checkPostureUpRecovery()) {
		int targetDefense = targetCreature->getSkillMod(
				"posture_change_up_defense");
		targetDefense -= (int) (targetDefense
				* targetCreature->calculateBFRatio());

		int rand = System::random(100);

		if ((5 > rand) || (rand > targetDefense)) {
			if (targetCreature->isMounted())
				targetCreature->dismount();

			if (targetCreature->getPosture() == CreaturePosture::PRONE) {
				targetCreature->setPosture(CreaturePosture::CROUCHED);
				targetCreature->updatePostureUpRecovery();
			} else if (targetCreature->getPosture()
					== CreaturePosture::CROUCHED) {
				targetCreature->setPosture(CreaturePosture::UPRIGHT);
				targetCreature->updatePostureUpRecovery();
			}
		}
	} else if (!targetCreature->checkPostureUpRecovery())
		creature->sendSystemMessage("cbt_spam", "posture_change_fail");
}

void CombatManager::applyStates(CreatureObject* creature, CreatureObject* targetCreature, const CreatureAttackData& data) {
	// TODO: None of these equations seem correct except intimidate
	int chance = 0;
	if ((chance = data.getKnockdownStateChance()) > 0)
		checkKnockDown(creature, targetCreature, chance);
	if ((chance = data.getPostureDownStateChance()) > 0)
		checkPostureDown(creature, targetCreature, chance);
	if ((chance = data.getPostureUpStateChance()) > 0)
		checkPostureUp(creature, targetCreature, chance);

	if (data.getDizzyStateChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("dizzy_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(data.getDizzyStateChance(), 0.0f, targetDefense, defenseBonus))
			targetCreature->setDizziedState(data.getDurationStateTime());
	}

	if (data.getBlindStateChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("blind_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(data.getBlindStateChance(), 0.0f, targetDefense, defenseBonus))
			targetCreature->setBlindedState(data.getDurationStateTime());
	}

	if (data.getStunStateChance() != 0) {
		float targetDefense = targetCreature->getSkillMod("stun_defense");
		// Force Enhancement "Force Resist States" skill.
		float stateResist = targetCreature->getSkillMod("resistance_states");
		// Force Defense Jedi State Defense skill mod.
		float stateDefense = targetCreature->getSkillMod("jedi_state_defense");
		targetDefense = (targetDefense + stateResist + stateDefense);
		targetDefense -= (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(data.getStunStateChance(), 0.0f, targetDefense, defenseBonus))
			targetCreature->setStunnedState(data.getDurationStateTime());
	}

	if ((chance = data.getIntimidateStateChance()) > 0) {
		int targetDefense = targetCreature->getSkillMod("intimidate_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(chance, 0.0f, targetDefense, defenseBonus)) {
			targetCreature->setIntimidatedState(data.getDurationStateTime());
		} else
			targetCreature->showFlyText("combat_effects", "intimidated_miss", 0xFF, 0, 0);
	}

	if ((chance = data.getNextAttackDelayChance()) > 0) {
		int targetDefense = targetCreature->getSkillMod("warcry_defense");
		targetDefense -= (int) (targetDefense * targetCreature->calculateBFRatio());

		if (targetDefense > 125)
			targetDefense = 125;

		float defenseBonus = 0.0f; // TODO: Food/drink bonuses go here

		if (System::random(100) <= hitChanceEquation(chance, 0.0f, targetDefense, defenseBonus)) {
			targetCreature->setNextAttackDelay(data.getDurationStateTime());
		} else
			targetCreature->showFlyText("combat_effects", "warcry_miss", 0xFF, 0, 0);
	}
}

int CombatManager::calculatePoolsToDamage(int poolsToDamage) {
	if (poolsToDamage & RANDOM) {
		int rand = System::random(100);

		if (rand < 50) {
			poolsToDamage = HEALTH;
		} else if (rand < 85) {
			poolsToDamage = ACTION;
		} else {
			poolsToDamage = MIND;
		}
	}

	return poolsToDamage;
}

int CombatManager::applyDamage(CreatureObject* attacker, CreatureObject* defender, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0 || damageMultiplier == 0)
		return 0;

	float damage = 0;

	if (poolsToDamage & HEALTH) {
		damage += calculateDamage(attacker, defender, HEALTH) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::HEALTH, (int)damage, true);
	}

	if (poolsToDamage & ACTION) {
		damage += calculateDamage(attacker, defender, ACTION) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::ACTION, (int)damage, true);
	}

	if (poolsToDamage & MIND) {
		damage += calculateDamage(attacker, defender, MIND) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::MIND, (int)damage, true);
	}

	return (int) damage;
}

int CombatManager::applyDamage(CreatureObject* attacker, TangibleObject* defender, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0)
		return 0;

	int damage = System::random(1000);

	defender->inflictDamage(attacker, 0, damage, true);

	return damage;
}

int CombatManager::doAreaCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data) {
	float creatureVectorX = attacker->getPositionX();
	float creatureVectorY = attacker->getPositionY();

	float directionVectorX = defenderObject->getPositionX() - creatureVectorX;
	float directionVectorY = defenderObject->getPositionY() - creatureVectorY;

	Zone* zone = attacker->getZone();

	if (zone == NULL)
		return 0;

	PlayerManager* playerManager = zone->getZoneServer()->getPlayerManager();

	int damage = 0;

	int range = data.getAreaRange();

	if (data.getCommand()->isConeAction()) {
		range = data.getRange();

		if (range == -1) {
			WeaponObject* weapon = attacker->getWeapon();
			range = weapon->getMaxRange();
		}
	}

	try {
		zone->rlock();

		for (int i = 0; i < attacker->inRangeObjectCount(); ++i) {
			ManagedReference<SceneObject*> object = (SceneObject*) attacker->getInRangeObject(i);

			if (!object->isTangibleObject()) {
				//error("object is not tangible");
				continue;
			}

			TangibleObject* tano = (TangibleObject*) object.get();

			if (object == attacker) {
				//error("object is attacker");
				continue;
			}

			if (!attacker->isInRange(object, range)) {
				//error("not in range " + String::valueOf(range));
				continue;
			}

			if (!tano->isAttackableBy(attacker)) {
				//error("object is not attackeble");
				continue;
			}

			if (tano->isCreatureObject() && ((CreatureObject*)tano)->isIncapacitated()) {
				//error("object is incapacitated");
				continue;
			}

			if (data.getCommand()->isConeAction() && !checkConeAngle(tano, data.getConeAngle(), creatureVectorX, creatureVectorY, directionVectorX,
					directionVectorY)) {
				//error("object is not in cone angle");
				continue;
			}

			zone->runlock();

			if (CollisionManager::checkLineOfSight(object, attacker)) {
				damage += doTargetCombatAction(attacker, tano, data);
			}

			zone->rlock();
		}

		zone->runlock();
	} catch (...) {
		zone->runlock();

		throw;
	}

	return damage;
}

void CombatManager::broadcastCombatSpam(CreatureObject* attacker, TangibleObject* defender, TangibleObject* weapon, uint32 damage, const String& stringid) {
	Zone* zone = attacker->getZone();

	Locker _locker(zone);

	for (int i = 0; i < attacker->inRangeObjectCount(); ++i) {
		SceneObject* object = (SceneObject*) attacker->getInRangeObject(i);

		if (object->isPlayerCreature() && attacker->isInRange(object, 70)) {
			PlayerCreature* player = (PlayerCreature*) object;

			CombatSpam* msg = new CombatSpam(attacker, defender, weapon, damage, "cbt_spam", stringid, player);
			player->sendMessage(msg);
		}
	}
}


void CombatManager::requestDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requests duel to targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	if (player->requestedDuelTo(targetPlayer)) {
		StringIdChatParameter stringId("duel", "already_challenged");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		return;
	}

	player->info("requesting duel");

	player->addToDuelList(targetPlayer);

	if (targetPlayer->requestedDuelTo(player)) {
		BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer,
				targetPlayer->getPvpStatusBitmask()
						+ CreatureFlag::ATTACKABLE
						+ CreatureFlag::AGGRESSIVE);
		player->sendMessage(pvpstat);

		StringIdChatParameter stringId("duel", "accept_self");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player,
				player->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE
						+ CreatureFlag::AGGRESSIVE);
		targetPlayer->sendMessage(pvpstat2);

		StringIdChatParameter stringId2("duel", "accept_target");
		stringId2.setTT(player->getObjectID());
		targetPlayer->sendSystemMessage(stringId2);
	} else {
		StringIdChatParameter stringId3("duel", "challenge_self");
		stringId3.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId3);

		StringIdChatParameter stringId4("duel", "challenge_target");
		stringId4.setTT(player->getObjectID());
		targetPlayer->sendSystemMessage(stringId4);
	}
}

void CombatManager::requestEndDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requested to end the duel with targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	if (!player->requestedDuelTo(targetPlayer)) {
		StringIdChatParameter stringId("duel", "not_dueling");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		return;
	}

	player->info("ending duel");

	player->removeFromDuelList(targetPlayer);
	player->removeDefender(targetPlayer);

	if (targetPlayer->requestedDuelTo(player)) {
		targetPlayer->removeFromDuelList(player);
		targetPlayer->removeDefender(player);

		player->sendPvpStatusTo(targetPlayer);

		StringIdChatParameter stringId("duel", "end_self");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		targetPlayer->sendPvpStatusTo(player);

		StringIdChatParameter stringId2("duel", "end_target");
		stringId2.setTT(player->getObjectID());
		targetPlayer->sendSystemMessage(stringId2);
	}
}

void CombatManager::freeDuelList(PlayerCreature* player, bool spam) {
	/* Pre: player not NULL and is locked
	 * Post: player removed and warned all of the objects from its duel list
	 */
	if (player->isDuelListEmpty())
		return;

	player->info("freeing duel list");

	while (player->getDuelListSize() != 0) {
		ManagedReference<PlayerCreature*> targetPlayer = player->getDuelListObject(0);

		if (targetPlayer != NULL && targetPlayer.get() != player) {
			try {
				Locker clocker(targetPlayer, player);

				player->removeFromDuelList(targetPlayer);
				player->removeDefender(targetPlayer);

				if (targetPlayer->requestedDuelTo(player)) {
					targetPlayer->removeFromDuelList(player);
					targetPlayer->removeDefender(player);

					player->sendPvpStatusTo(targetPlayer);

					if (spam) {
						StringIdChatParameter stringId("duel", "end_self");
						stringId.setTT(targetPlayer->getObjectID());
						player->sendSystemMessage(stringId);
					}

					targetPlayer->sendPvpStatusTo(player);

					if (spam) {
						StringIdChatParameter stringId2("duel", "end_target");
						stringId2.setTT(player->getObjectID());
						targetPlayer->sendSystemMessage(stringId2);
					}
				}


			} catch (ObjectNotDeployedException& e) {
				player->removeFromDuelList(targetPlayer);

				System::out << "Exception on CombatManager::freeDuelList()\n"
						<< e.getMessage() << "\n";
			}
		}
	}
}

void CombatManager::declineDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player declined Duel to targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	if (targetPlayer->requestedDuelTo(player)) {
		targetPlayer->removeFromDuelList(player);

		StringIdChatParameter stringId("duel", "cancel_self");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		StringIdChatParameter stringId2("duel", "cancel_target");
		stringId2.setTT(player->getObjectID());
		targetPlayer->sendSystemMessage(stringId2);
	}
}

bool CombatManager::checkConeAngle(SceneObject* target, float angle,
		float creatureVectorX, float creatureVectorY, float directionVectorX,
		float directionVectorY) {
	float Target1 = target->getPositionX() - creatureVectorX;
	float Target2 = target->getPositionY() - creatureVectorY;

	float resAngle = atan2(Target2, Target1) - atan2(directionVectorY, directionVectorX);
	float degrees = resAngle * 180 / M_PI;

	float coneAngle = angle / 2;

	if (degrees > coneAngle || degrees < -coneAngle) {
		return false;
	}

	return true;
}

uint32 CombatManager::getDefaultAttackAnimation(CreatureObject* creature) {
	WeaponObject* weapon = creature->getWeapon();

	if (weapon->isRangedWeapon())
		return 0x506E9D4C;
	else {
		int choice = System::random(8);
		return defaultAttacks[choice];
	}
}
