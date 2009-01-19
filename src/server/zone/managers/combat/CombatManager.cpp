/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "CombatManager.h"

#include "../../ZoneServer.h"
#include "../../Zone.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../packets.h"

#include "../../objects.h"

#include "../../objects/creature/skills/skills.h"
#include "events/SelfEnhanceEvent.h"

#include "CommandQueueAction.h"

#include "../loot/LootManager.h"

CombatManager::CombatManager(ZoneProcessServerImplementation* srv) {
	server = srv;
}

/*
 * handleAction() :
 *     Returns the time taken by the action.
 *     This is the entry point for combat queue actions
 */
float CombatManager::handleAction(CommandQueueAction* action) {
	CreatureObject* actor = action->getCreature();

	if (actor != NULL && actor->isPlayer()) {
		Player* playerActor = (Player*) actor;

		if (playerActor->isImmune()) {
			playerActor->sendSystemMessage("You cannot attack while Immune.");
			return 0.0f;
		}
	}

	// TODO: Check for armour if using Jedi skill and disallow

	Skill* skill = action->getSkill();

	if (skill->isTargetSkill())
		return doTargetSkill(action);
	else if (skill->isSelfSkill())
		return doSelfSkill(action);
	else if (skill->isCamoSkill())
		return doCamoSkill(action);
	else if(skill->isGroupSkill())
		return doGroupSkill(action);

	// Should not get here
	return 0.0f;
}

/*
 * doTargetSkill():
 *     Returns time taken by action
 */
float CombatManager::doTargetSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();
	SceneObject* target = action->getTarget();
	TargetSkill* tskill = (TargetSkill*)action->getSkill();
	String actionModifier = action->getActionModifier();

	if (target != NULL && target->isPlayer() && ((Player*)target)->isImmune() && !tskill->isHealSkill()) {
		if (creature->isPlayer())
			((Player*)creature)->sendSystemMessage("You cannot attack an immune player.");
		return 0.0f;
	}

	if (creature->isWatching() && !tskill->isHealSkill())
		creature->stopWatch(creature->getWatchID());

	if (creature->isListening() && !tskill->isHealSkill())
		creature->stopListen(creature->getListenID());

	if (tskill->isHealSkill()) {
		if (!tskill->calculateCost(creature))
			return 0.0f;

		try {
			if (creature != target)
				target->wlock(creature);

			tskill->doSkill(creature, target, actionModifier);

			if (creature != target)
				target->unlock();
		} catch (...) {
			if (creature != target)
				target->unlock();
		}

		return calculateHealSpeed(creature, tskill);
	}

	// Attack skills
	if (!checkSkill(creature, target, tskill))
		return 0.0f;

	uint32 animCRC = tskill->getAnimCRC();

	if (animCRC == 0)  // Default combat action
		animCRC = getDefaultAttackAnimation(creature);

	CombatAction* actionMessage;
	if (tskill->isThrowSkill()) {
		ThrowAttackTargetSkill* tarSkill = (ThrowAttackTargetSkill*) tskill;
		ThrowableWeapon* throwWeapon= tarSkill->getThrowableWeapon(creature,actionModifier);
		actionMessage = new CombatAction(creature, animCRC,throwWeapon->getObjectID());
	} else {
		actionMessage = new CombatAction(creature, animCRC);
	}
	if (!doAttackAction(creature, target, (AttackTargetSkill*)tskill, actionModifier, actionMessage)) {
		delete actionMessage;
		return 0.0f;
	}



	if (tskill->isArea())
		handleAreaAction(creature, target, action, actionMessage);

	creature->broadcastMessage(actionMessage);

	return tskill->calculateSpeed(creature);
}

float CombatManager::doSelfSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();

	SelfSkill* selfskill = (SelfSkill*) action->getSkill();

	if (!selfskill->isUseful(creature))
		return 0.0f;

	if (!selfskill->calculateCost(creature))
		return 0.0f;

	String actionModifier = action->getActionModifier();
	selfskill->doSkill(creature, actionModifier);

	if (selfskill->isEnhanceSkill()) {
		EnhanceSelfSkill* enhance = (EnhanceSelfSkill*) selfskill;

		if (enhance->getDuration() != 0) {
			SelfEnhanceEvent* event = new SelfEnhanceEvent(creature, enhance);
			server->addEvent(event);
		}
	}

	return selfskill->getSpeed();
}

float CombatManager::doCamoSkill(CommandQueueAction* action) {
	CamoSkill* skill = (CamoSkill*) action->getSkill();
	CreatureObject* creature = action->getCreature();
	SceneObject* target = action->getTarget();
	String actionModifier = action->getActionModifier();

	if (skill->getDuration() == 0)
		return skill->calculateSpeed(creature);

	if (skill->getCamoType() == 10) {
		skill->doSkill(creature,actionModifier);
	} else {
		skill->doSkill(creature,target,actionModifier);
	}

	return skill->calculateSpeed(creature);

}

float CombatManager::doGroupSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();
	SceneObject* target = action->getTarget();
	String actionModifier = action->getActionModifier();
	GroupSkill* groupskill = (GroupSkill*) action->getSkill();

	if(groupskill->canBePerformed(creature, target)) {
		groupskill->doSkill(creature, target, actionModifier);
		return groupskill->getSpeed();
	} else {
		return 0.0f;
	}
}

// TODO: Need support for grenades where the area is not centred around the attacker
void CombatManager::handleAreaAction(CreatureObject* creature, SceneObject* target, CommandQueueAction* action, CombatAction* actionMessage) {
	TargetSkill* skill = (TargetSkill*) action->getSkill();

	float CreatureVectorX = creature->getPositionX();
	float CreatureVectorY = creature->getPositionY();

	float DirectionVectorX = target->getPositionX() - CreatureVectorX;
	float DirectionVectorY = target->getPositionY() - CreatureVectorY;

	String actionModifier = action->getActionModifier();

	Zone* zone = creature->getZone();
	try {
		zone->lock();

		int weaponRange;
		if (creature->getWeapon() != NULL)
			weaponRange = creature->getWeapon()->getMaxRange();
		else
			weaponRange = 5;

		int coneRange = weaponRange;
		if (skill->getRange() != 0)
			coneRange = (int)skill->getRange();

		int areaRange = weaponRange;
		if (skill->getAreaRange() != 0)
			areaRange = (int)skill->getAreaRange();

		for (int i = 0; i < creature->inRangeObjectCount(); i++) {
			// Is this correct?
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) creature->getInRangeObject(i))->_this);

			if (!object->isPlayer() && !object->isNonPlayerCreature() && !object->isAttackableObject())
				continue;

			if (object == creature || object == target)
				continue;

			// TODO: Need to have ability for creatures to attack creatures.
			if (!object->isAttackableBy(creature))
				continue;
			if (!creature->isPlayer() && !object->isPlayer())
				continue;

			CreatureObject* creatureTarget = (CreatureObject*) object;

			if (creatureTarget->isIncapacitated() || creatureTarget->isDead())
				continue;

			if (creatureTarget->isPlayer())
				if (((Player*)creatureTarget)->isImmune())
					continue;

			// Check they are in the same cell
			if (creature->getParent() != object->getParent())
				continue;

			if (skill->isCone()) {
				if (!(creature->isInRange(object, coneRange)))
					continue;

				float angle = getConeAngle(object, CreatureVectorX, CreatureVectorY, DirectionVectorX, DirectionVectorY);
				float coneAngle = skill->getConeAngle() / 2;

				if (angle > coneAngle || angle < -coneAngle)
					continue;

			} else if (!skill->isThrowSkill() && !(creature->isInRange(object, areaRange)))
				continue;
			else if (skill->isThrowSkill() && !(target->isInRange(object, areaRange)))
				continue;

			zone->unlock();

			doAttackAction(creature, object, (AttackTargetSkill*)skill, actionModifier, NULL);

			zone->lock();
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();

		System::out << "Exception in CombatManager::handleAreaAction\n";
	}
}

bool CombatManager::doAttackAction(CreatureObject* attacker, SceneObject* target, AttackTargetSkill* skill,  String& modifier, CombatAction* actionMessage) {
	try {
		target->wlock(attacker);

		Creature* targetCreature = NULL;

		if (target->isPlayer() || target->isNonPlayerCreature()) {
			targetCreature = (Creature*) target;

			if (targetCreature->isIncapacitated() || targetCreature->isDead()) {
				targetCreature->unlock();
				return false;
			} else if (targetCreature->isPlayingMusic())
				targetCreature->stopPlayingMusic();
			else if (targetCreature->isDancing())
				targetCreature->stopDancing();

			if (targetCreature->isPlayer()) {
				Player* targetPlayer = (Player*) targetCreature;

				if (targetPlayer->isImmune()) {
					targetPlayer->unlock();
					return false;
				}

				if (attacker->isPlayer()) {
					if (!canAttack((Player*)attacker, targetPlayer)) {
						targetPlayer->unlock();
						return false;
					}
				}

				if (!targetPlayer->isOnline()) {
					targetPlayer->unlock();
					return false;
				}
			}
		}

		if (skill->isArea())
			attacker->addDefender(target);
		else
			attacker->setDefender(target);

		target->addDefender(attacker);
		attacker->clearState(CreatureState::PEACE);

		int damage = skill->doSkill(attacker, target, modifier, false);

		if (actionMessage != NULL && targetCreature != NULL)
			actionMessage->addDefender(targetCreature, damage >= 0);

		if (targetCreature != NULL) {
			/**
			 * TODO: REMOVE - handled with event handlers now
			 * if (targetCreature->isIncapacitated()) {
				attacker->sendSystemMessage("base_player", "prose_target_incap", targetCreature->getObjectID());

				if (!skill->isArea()) {
					attacker->clearCombatState(true);
				}

			} else if (targetCreature->isDead()) {
				attacker->sendSystemMessage("base_player", "prose_target_dead", targetCreature->getObjectID());

				if (!skill->isArea()) {
					attacker->clearCombatState(true);
				}
			}*/

			skill->calculateStates(attacker, targetCreature);

			if(targetCreature->isNonPlayerCreature())
				targetCreature->doAttack(attacker, damage);

			targetCreature->activateRecovery();
		} else {
			AttackableObject* targetObject = (AttackableObject*) target;
			if (targetObject->isDestroyed())
				if (!skill->isArea()) {
					attacker->clearCombatState(true);
					return false;
				}

			targetObject->doDamage(damage, attacker);
		}

		target->unlock();
	} catch (Exception& e) {
		System::out << "Exception in doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill)\n"
			 << e.getMessage() << "\n";
		e.printStackTrace();

		target->unlock();

		return false;
	} catch (...) {
		System::out << "exception in doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill)";

		target->unlock();

		return false;
	}

	return true;
}

bool CombatManager::canAttack(Player* player, Player* targetPlayer) {
	if (!player->isInDuelWith(targetPlayer, false)) {
		if (!player->isOvert() || !targetPlayer->isOvert()) {
			return false;
		} else if (!player->hatesFaction(targetPlayer->getFaction())) {
			return false;
		}
	}
	return true;
}

bool CombatManager::checkSkill(CreatureObject* creature, SceneObject* target, TargetSkill* skill) {
	if (target == NULL)
		return false;

	if (!skill->isUseful(creature, target))
		return false;

	if (!skill->calculateCost(creature))
		return false;

	return true;
}

float CombatManager::getConeAngle(SceneObject* target, float CreatureVectorX, float CreatureVectorY, float DirectionVectorX, float DirectionVectorY) {
	float Target1 = target->getPositionX() - CreatureVectorX;
	float Target2 = target->getPositionY() - CreatureVectorY;

	float angle = atan2(Target2, Target1) - atan2(DirectionVectorY, DirectionVectorX);
	float degrees = angle * 180 / M_PI;

	return degrees;
}

uint32 CombatManager::getDefaultAttackAnimation(CreatureObject* creature) {
	Weapon* weapon = creature->getWeapon();

	if ((weapon != NULL) && (weapon->getCategory() == WeaponImplementation::RANGED))
		return 0x506E9D4C;
	else {
		int choice = System::random(8);
		return defaultAttacks[choice];
	}
}

void CombatManager::doDodge(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "dodge", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);
}

void CombatManager::doCounterAttack(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "counterattack", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);
}

void CombatManager::doBlock(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "block", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);
}

// calc methods
void CombatManager::calculateDamageReduction(CreatureObject* creature, CreatureObject* targetCreature, float& damage) {

	if (targetCreature->isKnockedDown())
		damage *= 1.33f;

	if (creature->isIntimidated())
		damage *= 0.8f;
}

// TODO: Not used for force attacks
void CombatManager::checkMitigation(CreatureObject* creature, CreatureObject* targetCreature, float& minDamage, float& maxDamage) {
	Weapon* weapon = creature->getWeapon();
	uint32 mit = 0;

	if (weapon == NULL || MELEEWEAPON(weapon->getType())) {
		mit = targetCreature->getMitigation("melee_damage_mitigation_3");

		if (mit == 0) {
			mit = targetCreature->getMitigation("melee_damage_mitigation_2");
			if (mit == 0)
				mit = targetCreature->getMitigation("melee_damage_mitigation_1");
		}

	} else {
		mit = targetCreature->getMitigation("ranged_damage_mitigation_3");

		if (mit == 0) {
			mit = targetCreature->getMitigation("ranged_damage_mitigation_2");
			if (mit == 0)
				mit = targetCreature->getMitigation("ranged_damage_mitigation_1");
		}
	}

	if (mit != 0)
		maxDamage = minDamage + ((maxDamage - minDamage) * (1 - (float)mit / 100));
}

/*
 * checkSecondaryDefenses:
 *     returns 0 - hit, 1 - block, 2 - dodge, 3 - counter-attack
 */
int CombatManager::checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature) {
	if (targetCreature->isIntimidated())
		return 0;

	Weapon* targetWeapon = targetCreature->getWeapon();
	Weapon* playerWeapon = creature->getWeapon();

	if (targetWeapon == NULL)
		return 0;

	float playerAccuracy = creature->getAccuracy();
	float weaponAccuracy = getWeaponRangeMod(creature->getDistanceTo(targetCreature), playerWeapon);

	weaponAccuracy += calculatePostureMods(creature, targetCreature);

	int blindState = 0;

	if (creature->isBlinded())
		blindState = 1;

	float defTotal = 0;
	float accTotal = 0;

	int rand = System::random(100);

	if ((targetWeapon->getType() == WeaponImplementation::POLEARM) || (targetWeapon->getType() == WeaponImplementation::RIFLE)) {
		float block = targetCreature->getSkillMod("block");

		if (block == 0)
			return 0;

		if (block > 85)
			block = 85;

		defTotal = powf(float((block * 6.5) + (targetCreature->getCenteredBonus() * 1.5)), 4.9);
		defTotal -= (defTotal * targetCreature->calculateBFRatio());

		if ((playerAccuracy + weaponAccuracy + blindState) >= 0)
			accTotal = powf(float((playerAccuracy * 1.2) + weaponAccuracy - (blindState * 50)), 6);

		int chance = (int)round(((defTotal / (defTotal + accTotal))) * 100);

		/*cout << "accTotal:[" << accTotal << "] defTotal:[" << defTotal << "]\n";
		cout << "chance:[" << chance << "]\n";*/

		if (rand < chance) {
			doBlock(targetCreature, creature);
			return 1;
		}
	} else if ((targetWeapon->getType() == WeaponImplementation::ONEHANDED) || (targetWeapon->getType() == WeaponImplementation::PISTOL)) {
		float dodge = targetCreature->getSkillMod("dodge");

		if (dodge == 0)
			return 0;

		if (dodge > 85)
			dodge = 85;

		defTotal = powf(float((dodge * 6.5) + (targetCreature->getCenteredBonus() * 1.5)), 4.9);
		defTotal -= (defTotal * targetCreature->calculateBFRatio());

		if ((playerAccuracy + weaponAccuracy + blindState) >= 0)
			accTotal = powf(float((playerAccuracy * 1.2) + weaponAccuracy - (blindState * 50)), 6);

		int chance = (int)round(((defTotal / (defTotal + accTotal))) * 100);

		/*cout << "accTotal:[" << accTotal << "] defTotal:[" << defTotal << "]\n";
		cout << "chance:[" << chance << "]\n";*/

		if (rand < chance) {
			doDodge(targetCreature, creature);
			return 2;
		}
	} else if ((targetWeapon->getType() == WeaponImplementation::CARBINE) || (targetWeapon->getType() == WeaponImplementation::TWOHANDED)) {
		float counterAttack = targetCreature->getSkillMod("counterattack");

		if (counterAttack == 0)
			return 0;

		if (counterAttack > 85)
			counterAttack = 85;

		defTotal = powf(float((counterAttack * 6.5) + (targetCreature->getCenteredBonus() * 1.5)), 4.9);
		defTotal -= (defTotal * targetCreature->calculateBFRatio());

		if ((playerAccuracy + weaponAccuracy + blindState) >= 0)
			accTotal = powf(float((playerAccuracy * 1.2) + weaponAccuracy - (blindState * 50)), 6);

		int chance = (int)round(((defTotal / (defTotal + accTotal))) * 100);

		/*cout << "accTotal:[" << accTotal << "] defTotal:[" << defTotal << "]\n";
		cout << "chance:[" << chance << "]\n";*/

		if (rand < chance) {
			doCounterAttack(targetCreature, creature);
			return 3;
		}
	}

	// TODO: TKM secondary defenses also saberblock

	return 0;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, int accuracyBonus) {
	int hitChance = 0;
	Weapon* weapon = creature->getWeapon();

	// Get the weapon mods for range and add the mods for stance
	float weaponAccuracy = getWeaponRangeMod(creature->getDistanceTo(targetCreature), weapon);
	weaponAccuracy += calculatePostureMods(creature, targetCreature);

	// TODO: add Aim mod
	float aimMod = 0.0;

	float attackerAccuracy = creature->getAccuracy() + creature->getAccuracyBonus();

	int targetDefense = getTargetDefense(creature, targetCreature, weapon);

	// Calculation based on the DPS calculation spreadsheet
	float accTotal = 66.0; // Base chance

	float blindState = 0;
	if (creature->isBlinded())
		blindState = 50;
	float stunBonus = 0;
	if (targetCreature->isStunned())
		stunBonus = 50;

	accTotal += (attackerAccuracy + weaponAccuracy + aimMod + accuracyBonus + stunBonus
			- targetDefense - blindState) / 2.0;

	if (accTotal > 100)
		accTotal = 100.0;
	else if (accTotal < 0)
		accTotal = 0;

	hitChance = (int)accTotal;

	return hitChance;
}

float CombatManager::getWeaponRangeMod(float currentRange, Weapon* weapon) {
	float accuracy;

	float smallRange = 0;
	float idealRange = 2;
	float maxRange = 5;

	float smallMod = 7;
	float bigMod = 7;

	if (weapon != NULL) {
		smallRange = (float)weapon->getPointBlankRange();
		idealRange = (float)weapon->getIdealRange();
		maxRange = (float)weapon->getMaxRange();

		smallMod = (float)weapon->getPointBlankAccuracy();
		bigMod = (float)weapon->getIdealAccuracy();
	}

	if (currentRange > idealRange) {
		if (weapon != NULL) {
			smallMod = (float)weapon->getIdealAccuracy();
			bigMod = (float)weapon->getMaxRangeAccuracy();
		}

		idealRange = maxRange;
	}

	accuracy = smallMod + ((currentRange - smallRange)/(idealRange - smallRange) * (bigMod - smallMod));

	return accuracy;
}

int CombatManager::calculatePostureMods(CreatureObject* creature, CreatureObject* targetCreature) {
	int accuracy = 0;
	Weapon* weapon = creature->getWeapon();

	if (targetCreature->isKneeling()) {
		if (weapon == NULL || MELEEWEAPON(weapon->getType()))
			accuracy += 16;
		else
			accuracy -= 16;
	} else if (targetCreature->isProne()) {
		if (weapon == NULL || MELEEWEAPON(weapon->getType()))
			accuracy += 25;
		else
			accuracy -= 25;
	}

	if (creature->isKneeling()) {
		if (weapon == NULL || MELEEWEAPON(weapon->getType()))
			accuracy -= 16;
		else
			accuracy += 16;
	} else if (creature->isProne()) {
		if (weapon == NULL || MELEEWEAPON(weapon->getType()))
			accuracy -= 50;
		else
			accuracy += 50;
	}

	return accuracy;
}

uint32 CombatManager::getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon, bool forceAttack) {
	uint32 defense = 0;
	uint32 targetPosture = targetCreature->getPosture();

	if (forceAttack) {
		uint32 force = targetCreature->getSkillMod("force_defense");
		defense = force;
	} else {

		// TODO: Add defenses into creature luas.
		if (!targetCreature->isPlayer()) {
			defense = targetCreature->getLevel() / 2;

			if (defense > 250)
				defense = 250;
			return defense;

		} else if (weapon == NULL || MELEEWEAPON(weapon->getType())) {
			defense = targetCreature->getSkillMod("melee_defense");
		} else {
			defense = targetCreature->getSkillMod("ranged_defense");
		}
	}

	//defense += targetCreature->getDefenseBonus();

	return defense - (uint32)(defense * targetCreature->calculateBFRatio());
}

/**
 * applyDamage -
 * 		This routine applies damage to the target
 * 		Inputs are the attacker, defender, the amount of damage
 * 		and an integer specifying where the target has been hit
 * 		The values are:
 * 			0 - Chest
 * 			1 - Hands
 * 			2,3 - Left arm
 * 			4,5 - Right arm
 * 			6 -	Legs
 * 			7 - Feet
 * 			8 - Head
 * \param attacker The attacker.
 * \param target The target.
 * \param damage The damage.
 * \param part The area the damage is applied to.
 * \param askill The attack skill.
 * \param weapon The weapon used.
 * \return Returns the amount of damage absorbed by armour.
 */
int CombatManager::applyDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part, AttackTargetSkill* askill) {

	Weapon* weapon = attacker->getWeapon();

	int reduction = 0;

	reduction = getArmorReduction(weapon, target, damage, part);

	damage -= reduction;
	if (damage < 0)
		damage = 0;

	//target->addDamage(attacker, damage);
	target->addDamageDone(attacker, damage, askill->getSkillName());

	if (part < 6)
		attacker->inflictDamage(target, CreatureAttribute::HEALTH, damage);
	else if (part < 8)
		attacker->inflictDamage(target, CreatureAttribute::ACTION, damage);
	else
		attacker->inflictDamage(target, CreatureAttribute::MIND, damage);

	if (attacker->isPlayer()) {
		ShowFlyText* fly;
		switch(part) {
		case 8:
			fly = new ShowFlyText(target, "combat_effects", "hit_head", 0, 0, 0xFF);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 4:
		case 5:
			fly = new ShowFlyText(target, "combat_effects", "hit_rarm", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 1:
		case 2:
		case 3:
			fly = new ShowFlyText(target, "combat_effects", "hit_larm", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 0:
			fly = new ShowFlyText(target, "combat_effects", "hit_body", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 6:
		case 7:
			if (System::random(1) == 0)
				fly = new ShowFlyText(target, "combat_effects", "hit_lleg", 0, 0xFF, 0);
			else
				fly = new ShowFlyText(target, "combat_effects", "hit_rleg", 0, 0xFF, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		}
	}

	float woundsRatio = 5;

	if (weapon != NULL)
		woundsRatio = weapon->getWoundsRatio();

	if (woundsRatio + (woundsRatio * target->calculateBFRatio()) > System::random(100)) {
		if (part == 8)
			target->changeMindWoundsBar(1, true);
		else if (part < 6)
			target->changeHealthWoundsBar(1, true);
		else if (part < 8)
			target->changeActionWoundsBar(1, true);

		target->changeShockWounds(1);

		if (target->isPlayer()) {
			target->sendCombatSpam(attacker, NULL, 1, "wounded", false);
			target->sendCombatSpam(attacker, NULL, 1, "shock_wound", false);
		}

		Armor* armor = NULL;
		if (target->isPlayer())
			armor = ((Player*)target)->getPlayerArmor(part);
		if (armor != NULL) {
			armor->setConditionDamage(armor->getConditionDamage() + 1);
			armor->setUpdated(true);
		}

		if (weapon != NULL && System::random(10) == 1) {
			weapon->setConditionDamage(weapon->getConditionDamage() + 1);
			weapon->setUpdated(true);
		}
	}

	return reduction;
}

/*
 * This applies the damage afflicted by a trap. The damage will not kill the target.
 * \param attacker The attacker.
 * \param target The target.
 * \param damage The damage.
 * \param part The area the damage is applied to.
 *   		The values are:
 * 			0 - Chest
 * 			1 - Hands
 * 			2,3 - Left arm
 * 			4,5 - Right arm
 * 			6 -	Legs
 * 			7 - Feet
 * 			8 - Head
 * \param askill The attack skill.
 * \param weapon The weapon used.
 */
int CombatManager::applyTrapDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part, AttackTargetSkill* askill,Weapon* weapon) {

	int reduction = 0;

	reduction = getArmorReduction(weapon, target, damage, part);

	damage -= reduction;
	if (damage < 0)
		damage = 0;

	if (part < 6) {
		if (damage >= target->getHealth())
			damage = target->getHealth() - 1;
	} else if (part < 8) {
		if (damage >= target->getAction())
			damage = target->getAction() - 1;
	} else {
		if (damage >= target->getMind())
			damage = target->getMind() - 1;
	}

	target->addDamage(attacker, damage);
	target->addDamageDone(attacker, damage, askill->getSkillName());

	if (part < 6)
		attacker->inflictDamage(target, CreatureAttribute::HEALTH, damage);
	else if (part < 8)
		attacker->inflictDamage(target, CreatureAttribute::ACTION, damage);
	else
		attacker->inflictDamage(target, CreatureAttribute::MIND, damage);

	if (attacker->isPlayer()) {
		ShowFlyText* fly;
		switch(part) {
		case 8:
			fly = new ShowFlyText(target, "combat_effects", "hit_head", 0, 0, 0xFF);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 4:
		case 5:
			fly = new ShowFlyText(target, "combat_effects", "hit_rarm", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 1:
		case 2:
		case 3:
			fly = new ShowFlyText(target, "combat_effects", "hit_larm", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 0:
			fly = new ShowFlyText(target, "combat_effects", "hit_body", 0xFF, 0, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		case 6:
		case 7:
			if (System::random(1) == 0)
				fly = new ShowFlyText(target, "combat_effects", "hit_lleg", 0, 0xFF, 0);
			else
				fly = new ShowFlyText(target, "combat_effects", "hit_rleg", 0, 0xFF, 0);
			((Player*)attacker)->sendMessage(fly);
			break;
		}
	}

	float woundsRatio = 5;

	if (weapon != NULL)
		woundsRatio = weapon->getWoundsRatio();

	if (woundsRatio + (woundsRatio * target->calculateBFRatio()) > System::random(100)) {
		if (part == 9)
			target->changeMindWoundsBar(1, true);
		else if (part < 7)
			target->changeHealthWoundsBar(1, true);
		else if (part < 9)
			target->changeActionWoundsBar(1, true);

		target->changeShockWounds(1);

		Armor* armor = NULL;
		if (target->isPlayer())
			armor = ((Player*)target)->getPlayerArmor(part);
		if (armor != NULL) {
			armor->setConditionDamage(armor->getConditionDamage() + 1);
			armor->setUpdated(true);
		}

		if (weapon != NULL && System::random(10) == 1) {
			weapon->setConditionDamage(weapon->getConditionDamage() + 1);
			weapon->setUpdated(true);
		}
	}

	return reduction;
}

int CombatManager::getArmorReduction(Weapon* weapon, CreatureObject* target, int damage, int location) {
	float currentDamage = damage;
	int reduction;

	// Stage one : External full coverage.  PSG and Force Armour
	if (target->isPlayer() && ((Player*)target)->getPlayerArmor(13) != NULL) {
		// Do the reduction for PSG
	}

	// Stage two toughness
	if (target->isPlayer())
		if (weapon == NULL || MELEEWEAPON(weapon->getType())) { // Melee attack
			int toughness = 0;
			if (target->getWeapon() == NULL)
				toughness = target->getSkillMod("unarmed_toughness");
			else
				switch(target->getWeapon()->getType()) {
				case 0:
					toughness = target->getSkillMod("unarmed_toughness");
					break;
				case 1:
					toughness = target->getSkillMod("onehandmelee_toughness");
					break;
				case 2:
					toughness = target->getSkillMod("twohandmelee_toughness");
					break;
				case 3:
					toughness = target->getSkillMod("polearm_toughness");
					break;
				case 7:
				case 8:
				case 9:
					toughness = target->getSkillMod("lightsaber_toughness");
					break;
				}
				currentDamage -= currentDamage * toughness / 100.0f;
		}
	// TODO: Add Jedi toughness, all attacks except lightsaber


	// Stage three : Regular armour
	Armor* armor = NULL;

	if (target->isPlayer()) {
		armor = ((Player*)target)->getPlayerArmor(location);
		if (armor != NULL)
			if (!armor->isArmor()) {
				System::out << "Returned item is not armor, location " << location << endl;
				armor == NULL;
			}
		}

	int damageType = WeaponImplementation::KINETIC;

	float resist = 0;
	if (armor != NULL) {
		switch (damageType) {
		case WeaponImplementation::KINETIC:
			resist = armor->getKinetic();
			break;
		case WeaponImplementation::ENERGY:
			resist = armor->getEnergy();
			break;
		case WeaponImplementation::ELECTRICITY:
			resist = armor->getElectricity();
			break;
		case WeaponImplementation::STUN:
			resist = armor->getStun();
			break;
		case WeaponImplementation::BLAST:
			resist = armor->getBlast();
			break;
		case WeaponImplementation::HEAT:
			resist = armor->getHeat();
			break;
		case WeaponImplementation::COLD:
			resist = armor->getCold();
			break;
		case WeaponImplementation::ACID:
			resist = armor->getAcid();
			break;
		case WeaponImplementation::LIGHTSABER:
			resist = armor->getLightSaber();
			break;
		case WeaponImplementation::FORCE:
			resist = 0;
			break;
		}
	} else if (target->isNonPlayerCreature()) {
			resist = ((Creature*)target)->getArmorResist(damageType);
	}

	if (resist > 0 && resist < 100) {
		int armorPiercing = 1;
		if (weapon != NULL) {
			damageType = weapon->getDamageType();
			armorPiercing = weapon->getArmorPiercing();
		}

		int armorResistance = 0;
		if (armor != NULL)
			armorResistance = armor->getRating() / 16;
		else if (target->isNonPlayerCreature())
			armorResistance = ((Creature*)target)->getArmor();

		if (armorPiercing > armorResistance)
			for (int i = armorResistance; i < armorPiercing; i++)
				currentDamage *= 1.25f;
		else if (armorPiercing < armorResistance)
			for (int i = armorPiercing; i < armorResistance; i++)
				currentDamage *= 0.5;
	}

	if (target->isPlayer() && resist > 0 && armor != NULL)
		target->sendCombatSpam(target,(TangibleObject*)armor, (int)(currentDamage * resist / 100.0f), "armor_damaged", false);

	currentDamage -= currentDamage * resist / 100.0f;

	// Final outcome, may be negative
	reduction = damage - (int)currentDamage;

	return reduction;
}

bool CombatManager::calculateCost(CreatureObject* creature, float healthMultiplier, float actionMultiplier, float mindMultiplier, float forceMultiplier) {
	if (!creature->isPlayer())
		return true;

	Player* player = (Player*)creature;
	Weapon* weapon = creature->getWeapon();

	float wpnHealth = healthMultiplier;
	float wpnAction = actionMultiplier;
	float wpnMind = mindMultiplier;
	float forceCost = forceMultiplier;

	if (weapon != NULL) {
		wpnHealth *= weapon->getHealthAttackCost();
		wpnAction *= weapon->getActionAttackCost();
		wpnMind *= weapon->getMindAttackCost();
		forceCost *= weapon->getForceCost();

	} else {
		// TODO: Find the real TK unarmed HAM costs
		wpnHealth *= 10.0;
		wpnAction *= 25.0;
		wpnMind *= 10.0;
		forceCost *= 0;
	}

	int healthAttackCost = (int)(wpnHealth * (1 - (float)creature->getStrength() / 1500.0));
	int actionAttackCost = (int)(wpnAction * (1 - (float)creature->getQuickness() / 1500.0));
	int mindAttackCost = (int)(wpnMind * (1 - (float)creature->getFocus() / 1500.0));

	if (healthAttackCost < 0)
		healthAttackCost = 0;

	if (actionAttackCost < 0)
		actionAttackCost = 0;

	if (mindAttackCost < 0)
		mindAttackCost = 0;

	if (forceCost < 0)
		forceCost = 0;

	if (!player->changeHAMBars(-healthAttackCost, -actionAttackCost, -mindAttackCost))
		return false;

	if (forceCost > 0) {
		if (forceCost > player->getForcePower())
			return false;
		else
			player->changeForcePowerBar(-(int)forceCost);
	}

	return true;
}

float CombatManager::calculateWeaponAttackSpeed(CreatureObject* creature, TargetSkill* tskill) {
	Weapon* weapon = creature->getWeapon();
	float weaponSpeed;
	int speedMod = 0;

	if (creature->isPlayer()) {
		if (weapon == NULL)
			speedMod = ((Player*)creature)->getSkillMod("unarmed_speed");
		else switch (weapon->getObjectSubType()) {
			case TangibleObjectImplementation::MELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("unarmed_speed");
				break;
			case TangibleObjectImplementation::ONEHANDMELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("onehandmelee_speed");
				break;
			case TangibleObjectImplementation::TWOHANDMELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("twohandmelee_speed");
				break;
			case TangibleObjectImplementation::POLEARM:
				speedMod = ((Player*)creature)->getSkillMod("polearm_speed");
				break;
			case TangibleObjectImplementation::PISTOL:
				speedMod = ((Player*)creature)->getSkillMod("pistol_speed");
				break;
			case TangibleObjectImplementation::CARBINE:
				speedMod = ((Player*)creature)->getSkillMod("carbine_speed");
				break;
			case TangibleObjectImplementation::RIFLE:
				speedMod = ((Player*)creature)->getSkillMod("rifle_speed");
				break;
			case TangibleObjectImplementation::HEAVYWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("heavyweapon_speed");
				break;
			case TangibleObjectImplementation::SPECIALHEAVYWEAPON:
				if (weapon->getType() == WeaponImplementation::RIFLEFLAMETHROWER)
					speedMod = ((Player*)creature)->getSkillMod("heavy_flame_thrower_speed");
				else if (weapon->getType() == WeaponImplementation::RIFLELIGHTNING)
					speedMod = ((Player*)creature)->getSkillMod("heavy_rifle_lightning_speed");
					speedMod += ((Player*)creature)->getSkillMod("heavyweapon_speed");
					break;
			case TangibleObjectImplementation::ONEHANDSABER:
				speedMod = ((Player*)creature)->getSkillMod("onehandlightsaber_speed");
				break;
			case TangibleObjectImplementation::TWOHANDSABER:
				speedMod = ((Player*)creature)->getSkillMod("twohandlightsaber_speed");
				break;
			case TangibleObjectImplementation::POLEARMSABER:
				speedMod = ((Player*)creature)->getSkillMod("polearmlightsaber_speed");
				break;
		}
	}

	// Classic speed equation
	if (weapon != NULL)
		weaponSpeed = (1.0f - ((float)speedMod / 100.0f)) * tskill->getSpeedRatio() * weapon->getAttackSpeed();
	else
		weaponSpeed = (1.0f - ((float)speedMod / 100.0f)) * tskill->getSpeedRatio() * 2.0f;

	return MAX(weaponSpeed, 1.0f);
}

	float CombatManager::calculateHealSpeed(CreatureObject* creature, TargetSkill* tskill) {
		// Heals use an event for the timings.  However the combat queue needs timing for next action
		return tskill->calculateSpeed(creature);
	}

	void CombatManager::calculateStates(CreatureObject* creature, CreatureObject* targetCreature, AttackTargetSkill* tskill) {
		// TODO: None of these equations seem correct except intimidate
		int chance = 0;
		if ((chance = tskill->getKnockdownChance()) > 0)
			checkKnockDown(creature, targetCreature, chance);
		if ((chance = tskill->getPostureDownChance()) > 0)
			checkPostureDown(creature, targetCreature, chance);
		if ((chance = tskill->getPostureUpChance()) > 0)
			checkPostureUp(creature, targetCreature, chance);

		if (tskill->getDizzyChance() != 0) {
			int targetDefense = targetCreature->getSkillMod("dizzy_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());

			int rand = System::random(100);

			if ((5 > rand) || (rand > targetDefense))
				targetCreature->setDizziedState();
		}

		if (tskill->getBlindChance() != 0) {
			int targetDefense = targetCreature->getSkillMod("blind_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());

			int rand = System::random(100);

			if ((5 > rand) || (rand > targetDefense))
				targetCreature->setBlindedState();
		}

		if (tskill->getStunChance() != 0) {
			int targetDefense = targetCreature->getSkillMod("stun_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());

			int rand = System::random(100);

			if ((5 > rand) || (rand > targetDefense))
				targetCreature->setStunnedState();
		}

		if ((chance = tskill->getIntimidateChance()) > 0) {
			int rand = System::random(100);

			if (rand <= chance)
				targetCreature->setIntimidatedState();
		}

		targetCreature->updateStates();
	}

	/*
	 * Applies the states to the target.
	 * \param creature The skill user.
	 * \param targetCreature The target.
	 */
	void CombatManager::calculateTrapStates(CreatureObject* creature,
			CreatureObject* targetCreature, ThrowAttackTargetSkill* skill) {

		if (skill->isMissed())
			return;

		bool debuffHit = false;

		if (skill->isStateTap()) {

			if (skill->getDizzyChance() != 0)
				targetCreature->setDizziedState();

			if (skill->getBlindChance() != 0)
				targetCreature->setBlindedState();

			if (skill->getStunChance() != 0)
				targetCreature->setStunnedState();

			if (skill->getIntimidateChance() != 0)
				targetCreature->setIntimidatedState();

			if (skill->getSnareChance() != 0)
				targetCreature->setSnaredState();

			if (skill->getRootChance() != 0)
				targetCreature->setRootedState();

			targetCreature->updateStates();
		}

		if (skill->isDebuffTrap()) {
			if (targetCreature->hasBuff(skill->getNameCRC())) {
				return;
			}

			int duration = 30;
			Buff* deBuff = new Buff(skill->getNameCRC(), 0, duration);
			if (skill->getMeleeDefDebuff()!= 0) {
				deBuff->addSkillModBuff("melee_defense", skill->getMeleeDefDebuff());
				targetCreature->showFlyText("trap/trap", "melee_def_1_on", 255,
						255, 255);
				debuffHit = true;
			}
			if (skill->getRangedDefDebuff() != 0) {
				deBuff->addSkillModBuff("ranged_defense", skill->getRangedDefDebuff());
				targetCreature->showFlyText("trap/trap", "ranged_def_1_on",
						255, 255, 255);
				debuffHit = true;
			}
			if (skill->getIntimidateDefDebuff() != 0) {
				deBuff->addSkillModBuff("intimidate_defense",
						skill->getIntimidateDefDebuff());
				targetCreature->showFlyText("trap/trap",
						"melee_ranged_def_1_on", 255, 255, 255);
				debuffHit = true;
			}
			if (skill->getStunChance() != 0) {
				deBuff->addSkillModBuff("stun_defense", skill->getStunChance());
				targetCreature->showFlyText("trap/trap", "state_def_1_on", 255,
						255, 255);
				debuffHit = true;
			}

			if (debuffHit) {
				BuffObject* bo = new BuffObject(deBuff);
				targetCreature->applyBuff(bo);
			}
		}
	}


	void CombatManager::checkKnockDown(CreatureObject* creature, CreatureObject* targetCreature, int chance) {
		if (creature->isPlayer() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
			if (80 > System::random(100))
				targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
			return;
		}

		if (targetCreature->checkKnockdownRecovery()) {
			int targetDefense = targetCreature->getSkillMod("knockdown_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
			int rand = System::random(100);

			if ((5 > rand) || (rand > targetDefense)) {
				if (targetCreature->isMounted())
					targetCreature->dismount();
				targetCreature->setPosture(CreaturePosture::KNOCKEDDOWN);
				targetCreature->updateKnockdownRecovery();
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
			if (creature->isPlayer() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
				if (80 > System::random(100))
					targetCreature->setPosture(CreaturePosture::UPRIGHT, true);
				return;
			}

			if (targetCreature->checkPostureDownRecovery()) {
				int targetDefense = targetCreature->getSkillMod("posture_change_down_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());

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

					int combatEquil = targetCreature->getSkillMod("combat_equillibrium");

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
			int targetDefense = targetCreature->getSkillMod("posture_change_up_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());

			int rand = System::random(100);

			if ((5 > rand) || (rand > targetDefense)) {
				if (targetCreature->isMounted())
					targetCreature->dismount();

				if (targetCreature->getPosture() == CreaturePosture::PRONE) {
					targetCreature->setPosture(CreaturePosture::CROUCHED);
					targetCreature->updatePostureUpRecovery();
				} else if (targetCreature->getPosture() ==  CreaturePosture::CROUCHED) {
					targetCreature->setPosture(CreaturePosture::UPRIGHT);
					targetCreature->updatePostureUpRecovery();
				}
			}
		} else if (!targetCreature->checkPostureUpRecovery())
			creature->sendSystemMessage("cbt_spam", "posture_change_fail");
	}

	void CombatManager::doDotWeaponAttack(CreatureObject* creature, CreatureObject* targetCreature, bool areaHit) {
		Weapon* weapon = creature->getWeapon();

		int resist = 0;

		if (weapon != NULL) {
			if (weapon->getDot0Uses() != 0) {
				switch (weapon->getDot0Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");

					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");

					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");

					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");

					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;
				}

				if (areaHit == 0 && weapon->decreaseDot0Uses()) {
					weapon->setUpdated(true);
				}
			}

			if (weapon->getDot1Uses() != 0) {
				switch (weapon->getDot1Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");

					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");

					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");

					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");

					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;
				}

				if (areaHit == 0 && weapon->decreaseDot1Uses()) {
					weapon->setUpdated(true);
				}
			}

			if (weapon->getDot2Uses() != 0) {
				switch (weapon->getDot2Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");

					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");

					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");

					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");

					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;
				}

				if (areaHit == 0 && weapon->decreaseDot2Uses()) {
					weapon->setUpdated(true);
				}
			}
		}
	}

	/*
	 * Calculates and applies the damage of a skill.
	 * \param creature The creature, that throws the trap.
	 * \param target The traget.
	 * \param randompoolhit Is it random pool damage ?
	 * \param weapon The Trap.
	 */
	int CombatManager::calculateDamage(CreatureObject* creature, SceneObject* target, AttackTargetSkill* skill, bool randompoolhit) {
		Weapon* weapon = creature->getWeapon();

		float minDamage = 0;
		float maxDamage = 0;
		float healthDamage = 0;
		float actionDamage = 0;
		float mindDamage = 0;
		int reduction = 0;

		if (weapon != NULL) {
			minDamage = weapon->getMinDamage();
			maxDamage = weapon->getMaxDamage();
			if (weapon->getType() == 0) {  // Unarmed
				minDamage += (float)creature->getSkillMod("unarmed_damage");
				maxDamage += (float)creature->getSkillMod("unarmed_damage");
			}
			if (!weapon->isCertified()) {
				minDamage /= 5;
				maxDamage /= 5;
			}
		} else {
			minDamage = (float)creature->getSkillMod("unarmed_damage");
			maxDamage = minDamage + 15.0;
		}

		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature()) {
			targetCreature = (CreatureObject*) target;
			checkMitigation(creature, targetCreature, minDamage, maxDamage);
		}

		float damage = 0;
		int average = 0;

		int diff = (int)maxDamage - (int)minDamage;
		if (diff >= 0)
			average = System::random(diff) + (int)minDamage;

		float globalMultiplier = 1.0f;
		if (creature->isPlayer()) {
			globalMultiplier = GLOBAL_MULTIPLIER;  // All player damage has a multiplier
			if (!target->isPlayer())
				globalMultiplier *= PVE_MULTIPLIER;
			else
				globalMultiplier *= PVP_MULTIPLIER;
		}

		if (targetCreature != NULL) {

			int rand = System::random(100);

			if (getHitChance(creature, targetCreature, skill->getAccuracyBonus()) > rand) {
				int secondaryDefense = checkSecondaryDefenses(creature, targetCreature);

				if (secondaryDefense < 2) {
					if (secondaryDefense == 1)
						damage = damage / 2;

					//Work out the number of pools that may be affected
					int poolsAffected = 0;
					int totalPercentage = 0;  // Temporary fix until percentages in lua are corrected

					if (skill->healthPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->healthPoolAttackChance;
					}
					if (skill->actionPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->actionPoolAttackChance;
					}
					if (skill->mindPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->mindPoolAttackChance;
					}
					if (randompoolhit)
						poolsAffected = 1;  // Only one random pool hit

					damage = skill->damageRatio * average * globalMultiplier;
					float individualDamage = damage / poolsAffected;

					for (int i = 0; i < poolsAffected; i++) {
						int pool = System::random(totalPercentage);

						/* Body parts are
						 * 	0 - Chest
						 * 	1 - Hands
						 * 	2,3 - Left arm
						 * 	4,5 - Right arm
						 * 	6 -	Legs
						 * 	7 - Feet
						 * 	8 - Head
						 */
						int bodyPart = 0;
						if (pool < skill->healthPoolAttackChance) {
							healthDamage = individualDamage;
							if (System::random(1) == 0)  // 50% chance of chest hit
								bodyPart = 0;
							else
								bodyPart = System::random(4)+1;
							calculateDamageReduction(creature, targetCreature, healthDamage);
						}
						else if (pool < skill->healthPoolAttackChance + skill->actionPoolAttackChance) {
							actionDamage = individualDamage;
							if (System::random(2) == 0)
								bodyPart = 7;
							else
								bodyPart = 6;
							calculateDamageReduction(creature, targetCreature, actionDamage);
						}
						else {
							mindDamage = individualDamage;
							bodyPart = 8;
							calculateDamageReduction(creature, targetCreature, mindDamage);
						}

						if (skill->hasCbtSpamHit())
							creature->sendCombatSpam(targetCreature, NULL, (int32)individualDamage, skill->getCbtSpamHit());

						reduction += applyDamage(creature, targetCreature, (int32) individualDamage, bodyPart, skill);
					}
				}


				if (weapon != NULL) {
					doDotWeaponAttack(creature, targetCreature, 0);

					if (weapon->decreasePowerupUses())
						weapon->setUpdated(true);
					else if (weapon->hasPowerup())
						weapon->removePowerup((Player*)creature, true);
				}

			} else {
				skill->doMiss(creature, targetCreature, (int32) damage);
				return -1;
			}
		} else {
			return (int32)skill->damageRatio * average;
		}

		return (int32)damage - reduction;
	}

	/*
	 * Calculates and applies the damage of Traps.
	 * \param creature The creature, that throws the trap.
	 * \param target The traget.
	 * \param randompoolhit Is it random pool damage ?
	 * \param weapon The Trap.
	 * \return The damage done.
	 */
	int CombatManager::calculateTrapDamage(CreatureObject* creature, SceneObject* target, ThrowAttackTargetSkill* skill, bool randompoolhit, Weapon* weapon) {
		float minDamage = weapon->getMinDamage();
		float maxDamage = weapon->getMaxDamage();
		float healthDamage = 0;
		float actionDamage = 0;
		float mindDamage = 0;
		int reduction = 0;

		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature()) {
			targetCreature = (CreatureObject*) target;
			checkMitigation(creature, targetCreature, minDamage, maxDamage);
		}

		int average = 0;

		int diff = (int)maxDamage - (int)minDamage;
		if (diff >= 0)
			average = System::random(diff) + (int)minDamage;
		float damage = 0;

		float globalMultiplier = 1.0f;
		if (creature->isPlayer()) {
			globalMultiplier = GLOBAL_MULTIPLIER;  // All player damage has a multiplier
			if (!target->isPlayer())
				globalMultiplier *= PVE_MULTIPLIER;
			else
				globalMultiplier *= PVP_MULTIPLIER;
		}

		if (targetCreature != NULL) {
			int rand = System::random(100);

			int trappingSkill = creature->getSkillMod("trapping");

			int level = targetCreature->getLevel(); //336 ancient krayt

			if (level > 180)
				level = 180;

			if ((trappingSkill + rand > level) || (rand > 10 && rand < 20)) {
				int secondaryDefense = checkSecondaryDefenses(creature, targetCreature);

				if (secondaryDefense < 2) {
					if (secondaryDefense == 1)
						damage = damage / 2;

					//Work out the number of pools that may be affected
					int poolsAffected = 0;
					int totalPercentage = 0;  // Temporary fix until percentages in lua are corrected

					if (skill->healthPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->healthPoolAttackChance;
					}
					if (skill->actionPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->actionPoolAttackChance;
					}
					if (skill->mindPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += skill->mindPoolAttackChance;
					}
					if (randompoolhit)
						poolsAffected = 1;  // Only one random pool hit

					damage = average * globalMultiplier;
					float individualDamage = damage / poolsAffected;

					for (int i = 0; i < poolsAffected; i++) {
						int pool = System::random(totalPercentage);

						/* Body parts are
						 * 	0 - Chest
						 * 	1 - Hands
						 * 	2,3 - Left arm
						 * 	4,5 - Right arm
						 * 	6 -	Legs
						 * 	7 - Feet
						 * 	8 - Head
						 */
						int bodyPart = 0;
						if (pool < skill->healthPoolAttackChance) {
							healthDamage = individualDamage;
							if (System::random(1) == 0)  // 50% chance of chest hit
								bodyPart = 0;
							else
								bodyPart = System::random(4)+1;
							calculateDamageReduction(creature, targetCreature, healthDamage);
						}
						else if (pool < skill->healthPoolAttackChance + skill->actionPoolAttackChance) {
							actionDamage = individualDamage;
							if (System::random(2) == 0)  // 50% chance of chest hit
								bodyPart = 7;
							else
								bodyPart = 6;
							calculateDamageReduction(creature, targetCreature, actionDamage);
						}
						else {
							mindDamage = individualDamage;
							bodyPart = 8;
							calculateDamageReduction(creature, targetCreature, mindDamage);
						}

						reduction += applyTrapDamage(creature, targetCreature, (int32) individualDamage, bodyPart, skill,weapon);
						damage = individualDamage;
						if (skill->hasCbtSpamHit())
							creature->sendCombatSpam(targetCreature, NULL, (int32)individualDamage, skill->getCbtSpamHit());

					}
				}

			} else {
				skill->doMiss(creature, targetCreature, (int32) damage);
				return -1;
			}
		} else {
			return (int32)skill->damageRatio * average;
		}
		return (int32)damage - reduction;
	}

	void CombatManager::requestDuel(Player* player, uint64 targetID) {
		if (targetID != 0) {
			Zone* zone = player->getZone();

			SceneObject* targetObject = zone->lookupObject(targetID);

			if (targetObject != NULL && targetObject->isPlayer()) {
				Player* targetPlayer = (Player*) targetObject;
				if (targetPlayer != player && targetPlayer->isOnline())
					requestDuel(player, targetPlayer);
			}
		}
	}

	void CombatManager::requestDuel(Player* player, Player* targetPlayer) {
		/* Pre: player != targetPlayer and not NULL; player is locked
		 * Post: player requests duel to targetPlayer
		 */

		if (player->isListening())
			player->stopListen(player->getListenID());

		if (player->isWatching())
			player->stopWatch(player->getWatchID());

		try {
			targetPlayer->wlock(player);

			if (player->isOvert() && targetPlayer->isOvert()) {
				if (player->getFaction() != targetPlayer->getFaction()) {
					targetPlayer->unlock();
					return;
				}
			}

			if (player->requestedDuelTo(targetPlayer)) {
				ChatSystemMessage* csm = new ChatSystemMessage("duel", "already_challenged", targetPlayer->getObjectID());
				player->sendMessage(csm);

				targetPlayer->unlock();
				return;
			}

			player->info("requesting duel");

			player->addToDuelList(targetPlayer);

			if (targetPlayer->requestedDuelTo(player)) {
				BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE + CreatureFlag::AGGRESSIVE);
				player->sendMessage(pvpstat);

				ChatSystemMessage* csm = new ChatSystemMessage("duel", "accept_self", targetPlayer->getObjectID());
				player->sendMessage(csm);

				BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE + CreatureFlag::AGGRESSIVE);
				targetPlayer->sendMessage(pvpstat2);

				ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "accept_target", player->getObjectID());
				targetPlayer->sendMessage(csm2);
			} else {
				ChatSystemMessage* csm = new ChatSystemMessage("duel", "challenge_self", targetPlayer->getObjectID());
				player->sendMessage(csm);

				ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "challenge_target", player->getObjectID());
				targetPlayer->sendMessage(csm2);
			}

			targetPlayer->unlock();
		} catch (Exception& e) {
			System::out << "Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n" << e.getMessage() << "\n";
		} catch (...) {
			System::out << "Unreported Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n";
			targetPlayer->unlock();
		}
	}

	void CombatManager::requestEndDuel(Player* player, uint64 targetID) {
		if (targetID != 0) {
			Zone* zone = player->getZone();

			SceneObject* targetObject = zone->lookupObject(targetID);

			if (targetObject != NULL && targetObject->isPlayer()) {
				Player* targetPlayer = (Player*)targetObject;

				if (targetPlayer != player)
					requestEndDuel(player, targetPlayer);
			}
		} else {
			freeDuelList(player);
		}
	}

	void CombatManager::requestEndDuel(Player* player, Player* targetPlayer) {
		/* Pre: player != targetPlayer and not NULL; player is locked
		 * Post: player requested to end the duel with targetPlayer
		 */

		if (player->isListening())
			player->stopListen(player->getListenID());

		if (player->isWatching())
			player->stopWatch(player->getWatchID());

		try {
			targetPlayer->wlock(player);

			if (!player->requestedDuelTo(targetPlayer)) {
				ChatSystemMessage* csm = new ChatSystemMessage("duel", "not_dueling", targetPlayer->getObjectID());
				player->sendMessage(csm);

				targetPlayer->unlock();
				return;
			}

			player->info("ending duel");

			player->removeFromDuelList(targetPlayer);

			if (targetPlayer->requestedDuelTo(player)) {
				targetPlayer->removeFromDuelList(player);
				BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask());
				player->sendMessage(pvpstat);

				ChatSystemMessage* csm = new ChatSystemMessage("duel", "end_self", targetPlayer->getObjectID());
				player->sendMessage(csm);

				BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask());
				targetPlayer->sendMessage(pvpstat2);

				ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "end_target", player->getObjectID());
				targetPlayer->sendMessage(csm2);
			}

			targetPlayer->unlock();
		} catch (...) {
			targetPlayer->unlock();
		}
	}

	void CombatManager::freeDuelList(Player* player) {
		/* Pre: player not NULL and is locked
		 * Post: player removed and warned all of the objects from its duel list
		 */
		if (player->isDuelListEmpty())
			return;

		if (player->isListening())
			player->stopListen(player->getListenID());

		if (player->isWatching())
			player->stopWatch(player->getWatchID());

		player->info("freeing duel list");

		while (player->getDuelListSize() != 0) {
			ManagedReference<Player> targetPlayer = player->getDuelListObject(0);

			if (targetPlayer != NULL) {
				try {
					targetPlayer->wlock(player);

					if (targetPlayer->requestedDuelTo(player)) {
						targetPlayer->removeFromDuelList(player);

						BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask());
						player->sendMessage(pvpstat);

						ChatSystemMessage* csm = new ChatSystemMessage("duel", "end_self", targetPlayer->getObjectID());
						player->sendMessage(csm);

						BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask());
						targetPlayer->sendMessage(pvpstat2);

						ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "end_target", player->getObjectID());
						targetPlayer->sendMessage(csm2);
					}

					player->removeFromDuelList(targetPlayer);

					targetPlayer->unlock();
				} catch (ObjectNotDeployedException& e) {
					player->removeFromDuelList(targetPlayer);

					System::out << "Exception on CombatManager::freeDuelList()\n" << e.getMessage() << "\n";
				} catch (...) {
					targetPlayer->unlock();
				}
			}
		}
	}

	void CombatManager::declineDuel(Player* player, uint64 targetID) {
		if (targetID == 0)
			return;

		Zone* zone = player->getZone();

		SceneObject* targetObject = zone->lookupObject(targetID);

		if (targetObject != NULL && targetObject->isPlayer()) {
			Player* targetPlayer = (Player*)targetObject;

			if (targetPlayer != player)
				declineDuel(player, targetPlayer);
		}
	}

	void CombatManager::declineDuel(Player* player, Player* targetPlayer) {
		/* Pre: player != targetPlayer and not NULL; player is locked
		 * Post: player declined Duel to targetPlayer
		 */

		if (player->isListening())
			player->stopListen(player->getListenID());

		if (player->isWatching())
			player->stopWatch(player->getWatchID());

		try {
			targetPlayer->wlock(player);

			if (targetPlayer->requestedDuelTo(player)) {
				targetPlayer->removeFromDuelList(player);

				ChatSystemMessage* csm = new ChatSystemMessage("duel", "cancel_self", targetPlayer->getObjectID());
				player->sendMessage(csm);

				ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "cancel_target", player->getObjectID());
				targetPlayer->sendMessage(csm2);
			}

			targetPlayer->unlock();
		} catch (...) {
			targetPlayer->unlock();
		}
	}
