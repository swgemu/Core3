 /*
 * CombatManager.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CombatManager.h"
#include "CreatureAttackData.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/events/LogoutTask.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/buffs/StateBuff.h"

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

	if (attacker->isRidingMount())
		return false;

	if (!defender->isAttackableBy(attacker))
		return false;

	if (defender->isCreatureObject() && (cast<CreatureObject*>(defender))->isIncapacitated())
		return false;

	// this is redundant (happens again in set/addDefender)
	//attacker->clearState(CreatureState::PEACE);

	Locker clocker(defender, attacker);

	attacker->setDefender(defender);
	defender->addDefender(attacker);

	return true;
}

bool CombatManager::attemptPeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* defender = cast<TangibleObject*>( object.get());

		try {
			Locker clocker(defender, attacker);

			if (defender->hasDefender(attacker)) {

				if (defender->isCreatureObject()) {
					CreatureObject* creature = cast<CreatureObject*>(defender);

					if (creature->getMainDefender() != attacker || creature->hasState(CreatureState::PEACE) || creature->isDead() || attacker->isDead()) {
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

		// clearCombatState() (rightfully) does not automatically set peace, so set it
		attacker->setState(CreatureState::PEACE);

		return true;
	}
}

void CombatManager::forcePeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* defender = cast<TangibleObject*>( object.get());

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
	attacker->setState(CreatureState::PEACE);
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, CombatQueueCommand* command) {
	return doCombatAction(attacker, defenderObject, CreatureAttackData("",command));
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, const CreatureAttackData& data) {
	//info("entering doCombat action", true);

	if (!startCombat(attacker, defenderObject))
		return -1;

	//info("past start combat", true);

	if (attacker->hasAttackDelay())
		return -3;

	//info("past delay", true);

	if (attacker->isBerserked() && data.getCommandCRC() != 0xA8FEF90A) //berserk only works with attack
		return -3;

	//info("past berserk", true);

	if (!applySpecialAttackCost(attacker, data))
		return -2;

	//info("past special attack cost", true);

	int damage = 0;

	if (data.getCommand()->isAreaAction() || data.getCommand()->isConeAction())
		damage = doAreaCombatAction(attacker, defenderObject, data);
	else
		damage = doTargetCombatAction(attacker, defenderObject, data);

	CombatAction* combatAction = NULL;

	uint32 animationCRC = data.getAnimationCRC();

	if (!attacker->isCreature() && animationCRC == 0)
		animationCRC = getDefaultAttackAnimation(attacker);

	// TODO: this might need a randomize like player CRCs
	if (attacker->isCreature() && animationCRC == 0) {
		if (attacker->getGameObjectType() == SceneObjectType::DROIDCREATURE || attacker->getGameObjectType() == SceneObjectType::PROBOTCREATURE) {
			animationCRC = String("fire_3_single_light").hashCode();
		} else {
			animationCRC = String("creature_attack_light").hashCode();
		}

	}

	uint8 hit = damage != 0 ? 1 : 0;

	if (defenderObject->isCreatureObject()) {
		combatAction = new CombatAction(attacker, cast<CreatureObject*>(defenderObject), animationCRC, hit);
	} else {
		combatAction = new CombatAction(attacker, defenderObject, animationCRC, hit);
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
		CreatureObject* defender = cast<CreatureObject*>( tano);

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

	int hitVal = 0;
	float damageMultiplier = data.getDamageMultiplier();
	int damageMax = data.getDamageMax();

	// need to calculate damage here to get proper client spam
	int damage = 0;

	if (damageMultiplier != 0)
		damage = calculateDamage(attacker, defender, data) * damageMultiplier;

	if (damageMax != 0)
		damage = calculateDamage(attacker, defender, data); // For Powers.

	damageMultiplier = 1.0f;
	hitVal = getHitChance(attacker, defender, attacker->getWeapon(), damage, data.getAccuracyBonus() + attacker->getSkillMod(data.getCommand()->getAccuracySkillMod()));
	String combatSpam = data.getCommand()->getCombatSpam();
	// FIXME: probably need to add getCombatSpamBlock(), etc in data and store it in commands explicitly to avoid malformed text

	switch (hitVal) {
	case HIT:
		broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, combatSpam + "_hit");
		break;
	case BLOCK:
		doBlock(attacker, defender, damage, combatSpam + "_block");
		damageMultiplier = 0.5f;
		break;
	case LSBLOCK:
		doLightsaberBlock(attacker, defender, damage, combatSpam + "_block");
		damageMultiplier = 0.0f;
		break;
	case DODGE:
		doDodge(attacker, defender, damage, combatSpam + "_evade");
		damageMultiplier = 0.0f;
		break;
	case COUNTER:
		doCounterAttack(attacker, defender, damage, combatSpam + "_counter");
		damageMultiplier = 0.0f;
		break;
	case MISS:
		doMiss(attacker, defender, damage, combatSpam + "_miss");
		return 0;
		break;
	default:
		break;
	}

	int poolsToDamage = calculatePoolsToDamage(data.getPoolsToDamage());
	if (damage != 0 && damageMultiplier != 0 && poolsToDamage != 0)
		damage = applyDamage(attacker, defender, damage, damageMultiplier, poolsToDamage);

	if (defender->hasAttackDelay())
		defender->removeAttackDelay();

	applyStates(attacker, defender, data);
	applyDots(attacker, defender, data, damage);

	return damage;
}

void CombatManager::applyDots(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data, int appliedDamage) {
	VectorMap<uint64, DotEffect>* dotEffects = data.getDotEffects();

	for (int i = 0; i < dotEffects->size(); i++) {
		DotEffect effect = dotEffects->get(i);

		if (effect.getDotDuration() == 0 || System::random(100) > effect.getDotChance()) continue;

		Vector<String> defenseMods = effect.getDefenderStateDefenseModifers();
		int resist = 0;

		for (int j = 0; j < defenseMods.size(); j++)
			resist += defender->getSkillMod(defenseMods.get(j));

		//info("entering addDotState", true);

		defender->addDotState(effect.getDotType(), data.getCommand()->getNameCRC(), effect.isDotDamageofHit() ? appliedDamage : effect.getDotStrength(), effect.getDotPool(), effect.getDotDuration(), effect.getDotPotency(), resist);
	}
}

float CombatManager::getWeaponRangeModifier(float currentRange, WeaponObject* weapon) {
	float minRange = 0;
	float idealRange = 2;
	float maxRange = 5;

	float smallMod = 7;
	float bigMod = 7;

	if (weapon != NULL) {
		minRange = (float) weapon->getPointBlankRange();
		idealRange = (float) weapon->getIdealRange();
		maxRange = (float) weapon->getMaxRange();

		smallMod = (float) weapon->getPointBlankAccuracy();
		bigMod = (float) weapon->getIdealAccuracy();
	}

	// this assumes that we are attacking somewhere between point blank and ideal range
	float smallRange = minRange;
	float bigRange = idealRange;

	// check that assumption and correct if it's not true
	if (currentRange > idealRange) {
		if (weapon != NULL) {
			smallMod = (float) weapon->getIdealAccuracy();
			bigMod = (float) weapon->getMaxRangeAccuracy();
		} // else retain mod values = 7

		smallRange = idealRange;
		bigRange = maxRange;
	} else if (currentRange <= minRange)
		return smallMod;

	return smallMod + ((currentRange - smallRange) / (bigRange - smallRange) * (bigMod - smallMod));
}

int CombatManager::calculatePostureModifier(CreatureObject* creature) {
	int accuracy = 0;

	if (creature->isKneeling())
		accuracy += 16;
	else if (creature->isProne())
		accuracy += 50;
	else if (creature->isRunning())
		accuracy -= 50;

	return accuracy;
}

int CombatManager::calculateTargetPostureModifier(CreatureObject* creature, CreatureObject* targetCreature) {
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

	return accuracy;
}

int CombatManager::getAttackerAccuracyModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int attackerAccuracy = 0;

	Vector<String>* creatureAccMods = weapon->getCreatureAccuracyModifiers();

	for (int i = 0; i < creatureAccMods->size(); ++i) {
		String mod = creatureAccMods->get(i);
		attackerAccuracy += attacker->getSkillMod(mod);
		attackerAccuracy += attacker->getSkillMod("private_" + mod);
	}

	return attackerAccuracy;
}

int CombatManager::getAttackerAccuracyBonus(CreatureObject* attacker, WeaponObject* weapon) {
	int bonus = 0;

	bonus += attacker->getSkillMod("attack_accuracy");

	bonus += attacker->getSkillMod("private_accuracy_bonus");

	if (weapon->getAttackType() == WeaponObject::MELEEATTACK)
		bonus += attacker->getSkillMod("private_melee_accuracy_bonus");
	if (weapon->getAttackType() == WeaponObject::RANGEDATTACK)
		bonus += attacker->getSkillMod("private_ranged_accuracy_bonus");

	bonus += calculatePostureModifier(attacker);

	if (attacker->isAiAgent()) {
		ManagedReference<AiAgent*> agent = dynamic_cast<AiAgent*>(attacker);
		bonus += agent->getChanceHit() * 100;
	}

	return bonus;
}

int CombatManager::getDefenderDefenseModifier(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon) {
	int targetDefense = 0;
	int buffDefense = 0;

	Vector<String>* defenseAccMods = weapon->getDefenderDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		String mod = defenseAccMods->get(i);
		targetDefense += defender->getSkillMod(mod);
		targetDefense += defender->getSkillMod("private_" + mod);
	}

	//info("Base target defense is " + String::valueOf(targetDefense), true);

	targetDefense += defender->getSkillMod("private_defense");
	targetDefense += calculateTargetPostureModifier(attacker, defender);

	// defense hardcap
	if (targetDefense > 125)
		targetDefense = 125;

	//info("Target defense after state affects and cap is " +  String::valueOf(targetDefense), true);

	return targetDefense;
}

int CombatManager::getDefenderSecondaryDefenseModifier(CreatureObject* defender) {
	if (defender->isIntimidated()) return 0;

	int targetDefense = 0;
	ManagedReference<WeaponObject*> weapon = defender->getWeapon();

	Vector<String>* defenseAccMods = weapon->getDefenderSecondaryDefenseModifiers();

	for (int i = 0; i < defenseAccMods->size(); ++i) {
		String mod = defenseAccMods->get(i);
		targetDefense += defender->getSkillMod(mod);
		targetDefense += defender->getSkillMod("private_" + mod);
	}

	if (targetDefense > 125)
		targetDefense = 125;

	return targetDefense;
}

int CombatManager::getDefenderToughnessModifier(CreatureObject* defender) {
	int toughness = 0;
	ManagedReference<WeaponObject*> weapon = defender->getWeapon();

	Vector<String>* defenseToughMods = weapon->getDefenderToughnessModifiers();

	for (int i = 0; i < defenseToughMods->size(); ++i) {
		toughness += defender->getSkillMod(defenseToughMods->get(i));
	}

	return toughness;
}


float CombatManager::hitChanceEquation(float attackerAccuracy, float accuracyBonus, float targetDefense) {
	float accTotal = 66.0 + accuracyBonus + (attackerAccuracy - targetDefense) / 2.0;

	/*StringBuffer msg;
	msg << "HitChance\n";
	msg << "\tTarget Defense " << targetDefense << "\n";
	msg << "\tTarget Defense Bonus" << defenseBonus << "\n";

	info(msg.toString());*/

	return accTotal;
}

int CombatManager::calculateDamageRange(CreatureObject* attacker, CreatureObject* defender, WeaponObject* weapon) {
	int attackType = weapon->getAttackType();
	int damageMitigation = 0;
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	//info("attacker base damage is " + String::valueOf(minDamage) + "-"+ String::valueOf(maxDamage), true);

	PlayerObject* defenderGhost = defender->getPlayerObject();

	// this is for damage mitigation
	if (defenderGhost != NULL) {
		StringBuffer mitString;
		switch (attackType){
		case WeaponObject::MELEEATTACK:
			mitString << "melee_damage_mitigation_";
			break;
		case WeaponObject::RANGEDATTACK:
			mitString << "ranged_damage_mitigation_";
			break;
		default:
			break;
		}

		for (int i = 3; i > 0; i--) {
			mitString << i;
			if (defenderGhost->hasAbility(mitString.toString())) {
				damageMitigation = i;
				break;
			}
		}

		if (damageMitigation > 0) {
			maxDamage = minDamage + (maxDamage - minDamage) * (1 - (0.2 * damageMitigation));
		}
	}

	int maxDamageMuliplier = attacker->getSkillMod("private_max_damage_multiplier");
	int maxDamageDivisor = attacker->getSkillMod("private_max_damage_divisor");

	float range = maxDamage - minDamage;

	if (maxDamageMuliplier != 0)
		range *= maxDamageMuliplier;

	if (maxDamageDivisor != 0)
		range /= maxDamageDivisor;

	//info("attacker weapon damage mod is " + String::valueOf(maxDamage), true);

	return (int)range;
}

int CombatManager::getDamageModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int damageMods = 0;

	Vector<String>* weaponDamageMods = weapon->getDamageModifiers();

	for (int i = 0; i < weaponDamageMods->size(); ++i) {
		damageMods += attacker->getSkillMod(weaponDamageMods->get(i));
	}

	damageMods += attacker->getSkillMod("private_damage_bonus");

	if (weapon->getAttackType() == WeaponObject::MELEEATTACK)
		damageMods += attacker->getSkillMod("private_melee_damage_bonus");
	if (weapon->getAttackType() == WeaponObject::RANGEDATTACK)
		damageMods += attacker->getSkillMod("private_ranged_damage_bonus");

	int damageMultiplier = attacker->getSkillMod("private_damage_multiplier");

	if (damageMultiplier != 0)
		damageMods *= damageMultiplier;

	int damageDivisor = attacker->getSkillMod("private_damage_divisor");

	if (damageDivisor != 0)
		damageMods /= damageDivisor;

	return damageMods;
}

int CombatManager::getSpeedModifier(CreatureObject* attacker, WeaponObject* weapon) {
	int speedMods = 0;

	Vector<String>* weaponSpeedMods = weapon->getSpeedModifiers();

	for (int i = 0; i < weaponSpeedMods->size(); ++i) {
		speedMods += attacker->getSkillMod(weaponSpeedMods->get(i));
	}

	speedMods += attacker->getSkillMod("private_speed_bonus");

	if (weapon->getAttackType() == WeaponObject::MELEEATTACK)
		speedMods += attacker->getSkillMod("private_melee_speed_bonus");
	if (weapon->getAttackType() == WeaponObject::RANGEDATTACK)
		speedMods += attacker->getSkillMod("private_ranged_speed_bonus");

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

ArmorObject* CombatManager::getHealthArmor(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* chest = defender->getSlottedObject("chest2");
	SceneObject* bicepr = defender->getSlottedObject("bicep_r");
	SceneObject* bicepl = defender->getSlottedObject("bicep_l");
	SceneObject* bracerr = defender->getSlottedObject("bracer_upper_r");
	SceneObject* bracerl = defender->getSlottedObject("bracer_upper_l");
	SceneObject* gloves = defender->getSlottedObject("gloves");

	ManagedReference<ArmorObject*> armorToHit = NULL;

	int rand = System::random(11);
	switch (rand) {
	case 0:
	case 1: // hit right bicep
		if (bicepr != NULL && bicepr->isArmorObject())
			armorToHit = cast<ArmorObject*>(bicepr);
		break;
	case 2:
	case 3: // hit left bicep
		if (bicepl != NULL && bicepl->isArmorObject())
			armorToHit = cast<ArmorObject*>(bicepl);
		break;
	case 4: // hit right bracer
		if (bracerr != NULL && bracerr->isArmorObject())
			armorToHit = cast<ArmorObject*>(bracerr);
		break;
	case 5: // hit left bracer
		if (bracerl != NULL && bracerl->isArmorObject())
			armorToHit = cast<ArmorObject*>(bracerl);
		break;
	case 6: // hit gloves
		if (gloves != NULL && gloves->isArmorObject())
			armorToHit = cast<ArmorObject*>(gloves);
		break;
	default: // hit chest
		if (chest != NULL && chest->isArmorObject())
			armorToHit = cast<ArmorObject*>(chest);
		break;
	}

	return armorToHit;
}

ArmorObject* CombatManager::getActionArmor(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* boots = defender->getSlottedObject("shoes");
	SceneObject* pants = defender->getSlottedObject("pants1");

	ManagedReference<ArmorObject*> armorToHit = NULL;

	int rand = System::random(2);
	switch (rand) {
	case 0: // hit shoes
		if (boots != NULL && boots->isArmorObject())
			armorToHit = cast<ArmorObject*>(boots);
		break;
	default: // hit pants
		if (pants != NULL && pants->isArmorObject())
			armorToHit = cast<ArmorObject*>(pants);
		break;
	}

	return armorToHit;
}

ArmorObject* CombatManager::getMindArmor(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* helmet = defender->getSlottedObject("hat");

	if (helmet != NULL && helmet->isArmorObject())
		return cast<ArmorObject*>(helmet);

	return NULL;
}

ArmorObject* CombatManager::getPSGArmor(CreatureObject* attacker, CreatureObject* defender) {
	SceneObject* psg = defender->getSlottedObject("utility_belt");

	if (psg != NULL && psg->isArmorObject())
		return cast<ArmorObject*>(psg);

	return NULL;
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

int CombatManager::getArmorReduction(CreatureObject* attacker, CreatureObject* defender, float damage, int poolToDamage) {
	if (poolToDamage == 0)
		return 0;

	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();

	// the easy calculation
	if (defender->isAiAgent()) {
		damage *= getArmorPiercing(cast<AiAgent*>(defender), weapon);

		float armorReduction = getArmorNpcReduction(attacker, cast<AiAgent*>(defender), weapon);
		if (armorReduction > 0) damage *= (1.f - (armorReduction / 100.f));

		return damage;
	}

	// start with PSG reduction
	ManagedReference<ArmorObject*> psg = getPSGArmor(attacker, defender);

	if (psg != NULL && !psg->isVulnerable(weapon->getDamageType())) {
		float originalDamage = damage;
		float armorPiercing = getArmorPiercing(psg, weapon);
		float armorReduction =  getArmorObjectReduction(attacker, psg);

		damage *= armorPiercing;
		if (armorReduction > 0) damage *= (1.f - (armorReduction / 100.f));

		// inflict condition damage
		// TODO: this formula makes PSG's take more damage than regular armor, but that's how it was on live
		// it can be fixed by doing condition damage after all damage reductions
		float conditionDamage = (originalDamage * armorPiercing - damage) * 0.1;
		psg->inflictDamage(psg, 0, conditionDamage, false, true);
	}

	// Next is Jedi Force Armor reduction.
	int forceArmor = defender->getSkillMod("force_armor");
	if (!defender->isAiAgent() && (forceArmor > 0) && (weapon->getAttackType() != WeaponObject::FORCEATTACK)) {
		float originalDamage = damage;
		float armorReduction = forceArmor;
		float frsModsL = defender->getSkillMod("force_control_light");
		float frsModsD = defender->getSkillMod("force_control_dark");

		ManagedReference<PlayerObject*> playerObject = defender->getPlayerObject();

		// Client Effect upon hit.
		// TODO: does this really need to be here? animations need to be fixed
		defender->playEffect("clienteffect/pl_force_armor_hit.cef", "");

		// TODO: why is this done twice? these calculations don't seem correct, or are at least obfuscated
		if (frsModsL > 0) // If they are in the Light FRS.
			armorReduction += frsModsL / 3;
		else if (frsModsD > 0) // If they are in the Dark FRS.
			armorReduction += frsModsD / 3;

		damage *= (1.f - (armorReduction / 100.f));

		if (forceArmor == 25) { // Force Armor 1
			float frsMods = 0; // Storage for the Force Rank Manipulation, which "Increases the efficiency of any Force ability."
			// FIXME: these ifchecks don't need to be here, do they? implement a global FRS skillmod getter, this is messy
			if (defender->hasSkill("force_rank_light_novice"))
				frsMods = defender->getSkillMod("force_manipulation_light");
			else if(defender->hasSkill("force_rank_dark_novice"))
				frsMods = defender->getSkillMod("force_manipulation_dark");

			int forceCost = ((originalDamage - damage) * 0.5 - (frsMods / 2));
			int fP = playerObject->getForcePower();
			if (fP <= forceCost) {
				Buff* buff = cast<Buff*>( defender->getBuff(BuffCRC::JEDI_FORCE_ARMOR_1));

				if (buff != NULL)
					defender->removeBuff(buff);
			} else
				playerObject->setForcePower(playerObject->getForcePower() - forceCost);
		} else if (forceArmor == 45) { // Force Armor 2
			float frsMods = 0; // Storage for the Force Rank Manipulation, which "Increases the efficiency of any Force ability."
			if (defender->hasSkill("force_rank_light_novice"))
				frsMods = defender->getSkillMod("force_manipulation_light");
			else if(defender->hasSkill("force_rank_dark_novice"))
				frsMods = defender->getSkillMod("force_manipulation_dark");

			int forceCost = ((originalDamage - damage) * 0.3 - (frsMods / 2));
			int fP = playerObject->getForcePower();
			if (fP <= forceCost) {
				Buff* buff = cast<Buff*>( defender->getBuff(BuffCRC::JEDI_FORCE_ARMOR_2));

				if (buff != NULL)
					defender->removeBuff(buff);
			} else
				playerObject->setForcePower(playerObject->getForcePower() - forceCost);
		}
	}

	// now apply the rest of the damage to the regular armor
	ManagedReference<ArmorObject*> armor = NULL;

	if (poolToDamage & CombatManager::HEALTH)
		armor = getHealthArmor(attacker, defender);
	else if (poolToDamage & CombatManager::ACTION)
		armor = getActionArmor(attacker, defender);
	else if (poolToDamage & CombatManager::MIND)
		armor = getMindArmor(attacker, defender);

	if (armor != NULL && !armor->isVulnerable(weapon->getDamageType())) {
		// use only the damage applied to the armor for piercing (after the PSG takes some off)
		float originalDamage = damage;
		float armorPiercing = getArmorPiercing(armor, weapon);
		float armorReduction = getArmorObjectReduction(attacker, armor);

		damage *= armorPiercing;
		if (armorReduction > 0) damage *= (1.f - (armorReduction / 100.f));

		// inflict condition damage
		float conditionDamage = (originalDamage * armorPiercing - damage) * 0.1;
		armor->inflictDamage(armor, 0, conditionDamage, false, true);
	}

	return damage;
}

float CombatManager::getArmorPiercing(ArmorObject* armor, WeaponObject* weapon) {
	int armorPiercing = weapon->getArmorPiercing();
	int armorReduction = 0;

	if (armor != NULL)
		armorReduction = armor->getRating();

	if (armorPiercing > armorReduction)
		return pow(1.25, armorPiercing - armorReduction);
	else
		return pow(0.50, armorReduction - armorPiercing);
}

float CombatManager::getArmorPiercing(AiAgent* defender, WeaponObject* weapon) {
	int armorPiercing = weapon->getArmorPiercing();
	int armorReduction = defender->getArmor();

	if (armorPiercing > armorReduction)
		return pow(1.25, armorPiercing - armorReduction);
	else
		return pow(0.50, armorReduction - armorPiercing);
}

float CombatManager::calculateDamage(CreatureObject* attacker, TangibleObject* defender) {
	float damage = 0;

	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	int maxDamageMuliplier = attacker->getSkillMod("private_max_damage_multiplier");
	int maxDamageDivisor = attacker->getSkillMod("private_max_damage_divisor");

	float diff = maxDamage - minDamage;

	if (maxDamageMuliplier != 0)
		diff *= maxDamageMuliplier;

	if (maxDamageDivisor != 0)
		diff /= maxDamageDivisor;

	if (diff >= 0)
		damage = System::random(diff) + (int)minDamage;

	damage += getDamageModifier(attacker, weapon);

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor(attacker))
			damage /= 5;
	}

	//info("damage to be dealt is " + String::valueOf(damage), true);

	return damage * 10;
}

float CombatManager::calculateDamage(CreatureObject* attacker, CreatureObject* defender, const CreatureAttackData& data) {
	float damage = 0;
	int damageMax = data.getDamageMax();
	int damageMaxDif = damageMax - System::random(500);

	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();


	int diff = calculateDamageRange(attacker, defender, weapon);
	float minDamage = weapon->getMinDamage();

	if (diff >= 0)
		damage = System::random(diff) + (int)minDamage;

	if (weapon != attacker->getSlottedObject("default_weapon")) {
		float conditionDamage = damage / 10000.f;
		if (weapon->isSliced()) conditionDamage *= 1.1;
		if (weapon->hasPowerup()) conditionDamage *= 1.1;
		weapon->inflictDamage(weapon, 0, conditionDamage, false, true);

		if (((float)weapon->getConditionDamage() - conditionDamage / (float)weapon->getMaxCondition() < 0.75) && ((float)weapon->getConditionDamage() / (float)weapon->getMaxCondition() > 0.75))
			attacker->sendSystemMessage("@combat_effects:weapon_quarter");
		if (((float)weapon->getConditionDamage() - conditionDamage / (float)weapon->getMaxCondition() < 0.50) && ((float)weapon->getConditionDamage() / (float)weapon->getMaxCondition() > 0.50))
			attacker->sendSystemMessage("@combat_effects:weapon_half");

	}

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor(attacker))
			damage /= 5;
	}

	if (damageMax > 0)
		damage = damageMaxDif;

	damage += getDamageModifier(attacker, weapon);
	damage += defender->getSkillMod("private_damage_susceptibility");

	/*if (defender->isKneeling())
		damage *= 1.5f;*/

	if (defender->isKnockedDown() || defender->isProne())
		damage *= 1.33f;

	//Toughness
	int toughness = getDefenderToughnessModifier(defender);

	damage *= (1.f - (toughness /= 100.f));

	if (weapon->getDamageType() != WeaponObject::LIGHTSABER) damage *= (1.f - (defender->getSkillMod("jedi_toughness") / 100.f));

	if (damageMax > 0) {
		damage *= (1.f - (defender->getSkillMod("force_toughness") / 100.f));

		int forceShield = defender->getSkillMod("force_shield");

		if (defender->isPlayerCreature() && (forceShield > 0)) {
			float originalDamage = damage;
			float armorReduction = forceShield;

			ManagedReference<PlayerObject*> playerObject = defender->getPlayerObject();

			// Client Effect upon hit.
			// TODO: does this really need to be here? animations need to be fixed
			defender->playEffect("clienteffect/pl_force_shield_hit.cef", "");

			damage *= (1.f - (armorReduction / 100.f));

			if (forceShield == 25) { // Force Shield 1

				int forceCost = ((originalDamage - damage) * 0.5);
				int fP = playerObject->getForcePower();
				if (fP <= forceCost) {
					Buff* buff = cast<Buff*>( defender->getBuff(BuffCRC::JEDI_FORCE_SHIELD_1));

					if (buff != NULL)
						defender->removeBuff(buff);
				} else
					playerObject->setForcePower(playerObject->getForcePower() - forceCost);
			} else if (forceShield == 45) { // Force Shield 2

				int forceCost = ((originalDamage - damage) * 0.3);
				int fP = playerObject->getForcePower();
				if (fP <= forceCost) {
					Buff* buff = cast<Buff*>( defender->getBuff(BuffCRC::JEDI_FORCE_SHIELD_2));

					if (buff != NULL)
						defender->removeBuff(buff);
				} else
					playerObject->setForcePower(playerObject->getForcePower() - forceCost);
			}
		}
	}


	if (attacker->isPlayerCreature() && defender->isPlayerCreature())
		damage *= 0.25;

	//info("damage to be dealt is " + String::valueOf(damage), true);

	return damage;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, WeaponObject* weapon, int damage, int accuracyBonus) {
	int hitChance = 0;
	int attackType = weapon->getAttackType();

	//info("Calculating hit chance", true);

	float weaponAccuracy = 0.0f;
	// Get the weapon mods for range and add the mods for stance
	weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
	// accounts for steadyaim, general aim, and specific weapon aim, these buffs will clear after a completed combat action
	if (weapon->getAttackType() == WeaponObject::RANGEDATTACK) weaponAccuracy += creature->getSkillMod("private_aim");

	//info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy), true);

	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	//info("Base attacker accuracy is " + String::valueOf(attackerAccuracy), true);

	// need to also add in general attack accuracy (mostly gotten from foods and states)
	accuracyBonus += getAttackerAccuracyBonus(creature, weapon);

	//info("Attacker accuracy bonus is " + String::valueOf(accuracyBonus), true);

	int targetDefense = getDefenderDefenseModifier(creature, targetCreature, weapon);

	// first (and third) argument is divided by 2, second isn't
	float accTotal = hitChanceEquation(attackerAccuracy + weaponAccuracy, accuracyBonus, targetDefense);

	// this is the scout/ranger creature hit bonus that only works against creatures (not NPCS)
	if (targetCreature->isCreature())
		accTotal += creature->getSkillMod("creature_hit_bonus");

	//info("Final hit chance is " + String::valueOf(accTotal), true);

	if (accTotal > 100)
		accTotal = 100.0;
	else if (accTotal < 0)
		accTotal = 0;

	if (System::random(100) > accTotal) // miss, just return MISS
		return MISS;

	// now we have a successful hit, so calculate secondary defenses if there is a damage component
	if (damage > 0) {
		targetDefense = getDefenderSecondaryDefenseModifier(targetCreature);

		if (targetDefense <= 0)
			return HIT; // no secondary defenses

		ManagedReference<WeaponObject*> targetWeapon = targetCreature->getWeapon();
		Vector<String>* defenseAccMods = targetWeapon->getDefenderSecondaryDefenseModifiers();
		String def = defenseAccMods->get(0);

		if (def == "saber_block"){
			if ((weapon->getAttackType() == WeaponObject::RANGEDATTACK) && ((System::random(100)) < targetCreature->getSkillMod(def)))
				return LSBLOCK;
		else return HIT;
		}

		accTotal = hitChanceEquation(attackerAccuracy + weaponAccuracy, accuracyBonus, targetDefense);

		if (accTotal > 100)
			accTotal = 100.0;
		else if (accTotal < 0)
			accTotal = 0;

		if (System::random(100) > accTotal) { // successful secondary defense, return type of defense

			// this means use defensive acuity, which mean random 1, 2, or 3
			if (targetWeapon == NULL)
				return System::random(2) + 1;

			if (def == "block")
				return BLOCK;
			else if (def == "dodge")
				return DODGE;
			else if (def == "counterattack")
				return COUNTER;
			else if (def == "unarmed_passive_defense")
				return System::random(2) + 1;
			else // shouldn't get here
				return HIT; // no secondary defenses available on this weapon
		}
	}

	return HIT;
}

float CombatManager::calculateWeaponAttackSpeed(CreatureObject* attacker, WeaponObject* weapon, float skillSpeedRatio) {
	int speedMod = getSpeedModifier(attacker, weapon);
	float jediSpeed = attacker->getSkillMod("combat_haste") / 100.0f;

	float attackSpeed = (1.0f - ((float) speedMod / 100.0f)) * skillSpeedRatio * weapon->getAttackSpeed();
	
	if (jediSpeed > 0)
		attackSpeed = attackSpeed * jediSpeed;

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

void CombatManager::doLightsaberBlock(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	// No Fly Text.

	creature->doCombatAnimation(defender, String("test_sword_ricochet").hashCode(), 0);

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
	int force = (int) ((weapon->getForceCost() / 4) * data.getForceCostMultiplier()); // Divide by 4 until sabers are correctly implemented.

	health = MAX(0, health - (float(attacker->getHAM(CreatureAttribute::STRENGTH)) / 10.f));
	action = MAX(0, action - (float(attacker->getHAM(CreatureAttribute::QUICKNESS)) / 10.f));
	mind = MAX(0, mind - (float(attacker->getHAM(CreatureAttribute::FOCUS)) / 10.f));

	if (force > 0) { // Need Force check first otherwise it can be spammed.
		ManagedReference<PlayerObject*> playerObject = attacker->getPlayerObject();
		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= force) {
				attacker->sendSystemMessage("@jedi_spam:no_force_power");
				return false;
			} else
				playerObject->setForcePower(playerObject->getForcePower() - force);
		}
	}

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

	if (weapon != attacker->getSlottedObject("default_weapon")) {
		float conditionDamage = (health + action + mind) / 10000.f;
		weapon->inflictDamage(weapon, 0, conditionDamage, false, true);

		if (((float)weapon->getConditionDamage() - conditionDamage / (float)weapon->getMaxCondition() < 0.75) && ((float)weapon->getConditionDamage() / (float)weapon->getMaxCondition() > 0.75))
			attacker->sendSystemMessage("@combat_effects:weapon_quarter");
		if (((float)weapon->getConditionDamage() - conditionDamage / (float)weapon->getMaxCondition() < 0.50) && ((float)weapon->getConditionDamage() / (float)weapon->getMaxCondition() > 0.50))
			attacker->sendSystemMessage("@combat_effects:weapon_half");
	}

	return true;
}

void CombatManager::applyStates(CreatureObject* creature, CreatureObject* targetCreature, const CreatureAttackData& data) {
	VectorMap<uint64, StateEffect>* stateEffects = data.getStateEffects();

	// loop through all the states in the command
	for (int i = 0; i < stateEffects->size(); i++) {
		StateEffect effect = stateEffects->get(i);
		bool failed = false;
		uint8 effectType = effect.getEffectType();

		if (System::random(100) > effect.getStateChance()) continue; // effect didn't trigger this attack and don't send a message

		Vector<String> exclusionTimers = effect.getDefenderExclusionTimers();
		// loop through any exclusion timers
		for (int j = 0; j < exclusionTimers.size(); j++)
			if (!targetCreature->checkCooldownRecovery(exclusionTimers.get(j))) failed = true;

		float targetDefense = 0.f;

		// if recovery timer conditions aren't satisfied, it won't matter
		if (!failed) {
			Vector<String> defenseMods = effect.getDefenderStateDefenseModifiers();
			// add up all defenses against the state the target has
			for (int j = 0; j < defenseMods.size(); j++)
				targetDefense += targetCreature->getSkillMod(defenseMods.get(j));

			targetDefense -= targetCreature->calculateBFRatio();

			if (targetDefense > 125)
				targetDefense = 125;

			// now roll to see if it gets applied
			uint32 strength = effect.getStateStrength();
			if (strength == 0) strength = getAttackerAccuracyModifier(creature, creature->getWeapon());
			if (targetDefense > 0 && strength != 0 && System::random(100) > hitChanceEquation(strength, 0.0f, targetDefense))
				failed = true;

			// no reason to apply jedi defenses if primary defense was successful
			if (!failed) {
				targetDefense = 0.f;
				Vector<String> jediMods = effect.getDefenderJediStateDefenseModifiers();
				// second chance for jedi, roll against their special defense "jedi_state_defense"
				for (int j = 0; j < jediMods.size(); j++)
					targetDefense += targetCreature->getSkillMod(jediMods.get(j));

				if (targetDefense > 125)
					targetDefense = 125;

				// now roll again to see if it gets applied
				if (targetDefense > 0 && strength != 0 && System::random(100) > hitChanceEquation(strength, 0.0f, targetDefense))
					failed = true;
			}
		}

		if (!failed)
			data.getCommand()->applyEffect(targetCreature, effectType, creature->getSkillMod(data.getCommand()->getAccuracySkillMod()));

		// can move this to scripts, but only these three states have fail messages
		if (failed) {
			switch (effectType) {
			case CommandEffect::KNOCKDOWN:
				creature->sendSystemMessage("@cbt_spam:knockdown_fail");
				break;
			case CommandEffect::POSTUREDOWN:
			case CommandEffect::POSTUREUP:
				creature->sendSystemMessage("@cbt_spam:posture_change_fail");
				break;
			case CommandEffect::NEXTATTACKDELAY:
				creature->sendSystemMessage("@combat_effects:warcry_miss");
				break;
			case CommandEffect::INTIMIDATE:
				creature->sendSystemMessage("@combat_effects:intimidated_miss");
				break;
			default:
				break;
			}
		}

		// now check combat equilibrium
		if (!failed && (effectType == CommandEffect::KNOCKDOWN || effectType == CommandEffect::POSTUREDOWN || effectType == CommandEffect::POSTUREUP)) {
			int combatEquil = targetCreature->getSkillMod("combat_equillibrium");

			if (combatEquil > 100)
				combatEquil = 100;

			if ((combatEquil >> 1) > (int) System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
		}
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

int CombatManager::applyDamage(CreatureObject* attacker, CreatureObject* defender, int damage, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0 || damageMultiplier == 0)
		return 0;

	float ratio = attacker->getWeapon()->getWoundsRatio();
	float healthDamage = 0.f, actionDamage = 0.f, mindDamage = 0.f;
	bool wounded = false;

	if (defender->isPlayerCreature() && defender->getPvpStatusBitmask() == CreatureFlag::NONE) {
		return 0;
	}

	WeaponObject* weapon = attacker->getWeapon();

	if (poolsToDamage & HEALTH) {
		healthDamage = getArmorReduction(attacker, defender, damage, HEALTH) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::HEALTH, (int)healthDamage, true);
		if (!wounded && System::random(100) < ratio) {
			defender->addWounds(CreatureAttribute::HEALTH + System::random(2), 1, true);
			wounded = true;
		}
	}

	if (poolsToDamage & ACTION) {
		actionDamage = getArmorReduction(attacker, defender, damage, ACTION) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::ACTION, (int)actionDamage, true);
		if (!wounded && System::random(100) < ratio) {
			defender->addWounds(CreatureAttribute::ACTION + System::random(2), 1, true);
			wounded = true;
		}
	}

	if (poolsToDamage & MIND) {
		mindDamage = getArmorReduction(attacker, defender, damage, MIND) * damageMultiplier;
		defender->inflictDamage(attacker, CreatureAttribute::MIND, (int)mindDamage, true);
		if (!wounded && System::random(100) < ratio) {
			defender->addWounds(CreatureAttribute::MIND + System::random(2), 1, true);
			wounded = true;
		}
	}

	if (wounded)
		defender->addShockWounds(1, true);

	weapon->decreasePowerupUses(attacker);

	return (int) (healthDamage + actionDamage + mindDamage);
}

int CombatManager::applyDamage(CreatureObject* attacker, TangibleObject* defender, float damageMultiplier, int poolsToDamage) {
	if (poolsToDamage == 0)
		return 0;

	if (defender->isPlayerCreature() && defender->getPvpStatusBitmask() == CreatureFlag::NONE) {
		return 0;
	}

	int damage = calculateDamage(attacker, defender);

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
	}

	if (range < 0) {
		WeaponObject* weapon = attacker->getWeapon();
		range = weapon->getMaxRange();
	}

	try {
		zone->rlock();

		SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = attacker->getCloseObjects();

		for (int i = 0; i < closeObjects->size(); ++i) {
			ManagedReference<SceneObject*> object = cast<SceneObject*>(closeObjects->get(i).get());

			if (!object->isTangibleObject()) {
				//error("object is not tangible");
				continue;
			}

			TangibleObject* tano = cast<TangibleObject*>(object.get());

			if (object == attacker) {
				//error("object is attacker");
				continue;
			}

			if (!attacker->isInRange(object, range)) {
				//error("not in range " + String::valueOf(range));
				continue;
			}

			if (!tano->isAttackableBy(attacker)) {
				//error("object is not attackable");
				continue;
			}

			if (tano->isCreatureObject() && (cast<CreatureObject*>(tano))->isIncapacitated()) {
				//error("object is incapacitated");
				continue;
			}

			if (data.getCommand()->isConeAction() && !checkConeAngle(tano, data.getConeAngle(), creatureVectorX, creatureVectorY, directionVectorX, directionVectorY)) {
				//error("object is not in cone angle");
				continue;
			}

			zone->runlock();

			try {
				if (CollisionManager::checkLineOfSight(object, attacker)) {
					damage += doTargetCombatAction(attacker, tano, data);
				}
			} catch (Exception& e) {
				error(e.getMessage());
			} catch (...) {
				zone->rlock();

				throw;
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

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = attacker->getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* object = cast<SceneObject*>( closeObjects->get(i).get());

		if (object->isPlayerCreature() && attacker->isInRange(object, 70)) {
			CreatureObject* player = cast<CreatureObject*>( object);

			CombatSpam* msg = new CombatSpam(attacker, defender, weapon, damage, "cbt_spam", stringid, player);
			player->sendMessage(msg);
		}
	}
}


void CombatManager::requestDuel(CreatureObject* player, CreatureObject* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requests duel to targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = targetPlayer->getPlayerObject();

	if (ghost->requestedDuelTo(targetPlayer)) {
		StringIdChatParameter stringId("duel", "already_challenged");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		return;
	}

	player->info("requesting duel");

	ghost->addToDuelList(targetPlayer);

	if (targetGhost->requestedDuelTo(player)) {
		BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer,
				targetPlayer->getPvpStatusBitmask()
				| CreatureFlag::ATTACKABLE
				| CreatureFlag::AGGRESSIVE);
		player->sendMessage(pvpstat);

		StringIdChatParameter stringId("duel", "accept_self");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player,
				player->getPvpStatusBitmask() | CreatureFlag::ATTACKABLE
				| CreatureFlag::AGGRESSIVE);
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

void CombatManager::requestEndDuel(CreatureObject* player, CreatureObject* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requested to end the duel with targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = targetPlayer->getPlayerObject();

	if (!ghost->requestedDuelTo(targetPlayer)) {
		StringIdChatParameter stringId("duel", "not_dueling");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		return;
	}

	player->info("ending duel");

	ghost->removeFromDuelList(targetPlayer);
	player->removeDefender(targetPlayer);

	if (targetGhost->requestedDuelTo(player)) {
		targetGhost->removeFromDuelList(player);
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

void CombatManager::freeDuelList(CreatureObject* player, bool spam) {
	/* Pre: player not NULL and is locked
	 * Post: player removed and warned all of the objects from its duel list
	 */
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost->isDuelListEmpty())
		return;

	player->info("freeing duel list");

	while (ghost->getDuelListSize() != 0) {
		ManagedReference<CreatureObject*> targetPlayer = ghost->getDuelListObject(0);
		PlayerObject* targetGhost = targetPlayer->getPlayerObject();

		if (targetPlayer != NULL && targetPlayer.get() != player) {
			try {
				Locker clocker(targetPlayer, player);

				ghost->removeFromDuelList(targetPlayer);
				player->removeDefender(targetPlayer);

				if (targetGhost->requestedDuelTo(player)) {
					targetGhost->removeFromDuelList(player);
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
				ghost->removeFromDuelList(targetPlayer);

				System::out << "Exception on CombatManager::freeDuelList()\n"
						<< e.getMessage() << "\n";
			}
		}
	}
}

void CombatManager::declineDuel(CreatureObject* player, CreatureObject* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player declined Duel to targetPlayer
	 */

	Locker clocker(targetPlayer, player);

	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = targetPlayer->getPlayerObject();

	if (targetGhost->requestedDuelTo(player)) {
		targetGhost->removeFromDuelList(player);

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
	else
		return defaultAttacks[System::random(8)];
}
