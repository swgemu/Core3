/*
 * CombatManager.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CombatManager.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/creature/UpdatePVPStatusMessage.h"
#include "server/zone/Zone.h"

bool CombatManager::startCombat(CreatureObject* attacker, TangibleObject* defender, bool lockDefender) {
	if (attacker == defender)
		return false;

	bool success = true;

	if (!defender->isAttackableBy(attacker))
		return false;

	if (lockDefender)
		defender->wlock(attacker);

	try {

		attacker->setDefender(defender);
		defender->addDefender(attacker);

	} catch (...) {
		success = false;
	}

	if (lockDefender)
		defender->unlock();

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
			defender->wlock(attacker);

			if (defender->hasDefender(attacker)) {

				if (defender->isCreatureObject()) {
					CreatureObject* creature = (CreatureObject*) defender;

					if (creature->hasState(CreatureState::PEACE)) {
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

			defender->unlock();

		} catch (...) {
			error("unknown exception in PlayerImplementation::doPeace()\n");
			defender->unlock();
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

	accuracy = smallMod + ((currentRange - smallRange) / (idealRange
			- smallRange) * (bigMod - smallMod));

	return accuracy;
}

int CombatManager::calculatePostureModifier(CreatureObject* creature, CreatureObject* targetCreature) {
	int accuracy = 0;
	WeaponObject* weapon = creature->getWeapon();

	if (targetCreature->isKneeling()) {
		if (weapon->hasMeleeAttack())
			accuracy += 16;
		else
			accuracy -= 16;
	} else if (targetCreature->isProne()) {
		if (weapon->hasMeleeAttack())
			accuracy += 25;
		else
			accuracy -= 25;
	}

	if (creature->isKneeling()) {
		if (weapon->hasMeleeAttack())
			accuracy -= 16;
		else
			accuracy += 16;
	} else if (creature->isProne()) {
		if (weapon->hasMeleeAttack())
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

float CombatManager::hitChanceEquation(float attackerAccuracy,
		float accuracyBonus, float targetDefense, float defenseBonus) {

	float accTotal = 66.0 + (attackerAccuracy + accuracyBonus - targetDefense
			- defenseBonus) / 2.0;

	StringBuffer msg;
	msg << "HitChance\n";
	msg << "\tTarget Defense " << targetDefense << "\n";
	msg << "\tTarget Defense Bonus" << defenseBonus << "\n";

	info(msg.toString());

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

int CombatManager::calculateDamage(CreatureObject* attacker, TangibleObject* defender) {
	return System::random(1000);
}

int CombatManager::calculateDamage(CreatureObject* attacker, CreatureObject* defender) {
	ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
	float minDamage = weapon->getMinDamage(), maxDamage = weapon->getMaxDamage();

	int damageType = weapon->getDamageType();
	int attackType = weapon->getAttackType();
	int armorPiercing = weapon->getArmorPiercing(); // None

	int damageMod = getDamageModifier(attacker, weapon);

	minDamage += damageMod;
	maxDamage += damageMod;

	int damage = 0;

	int diff = (int) maxDamage - (int) minDamage;

	if (diff >= 0)
		damage = System::random(diff) + (int) minDamage;

	if (attacker->isPlayerCreature()) {
		if (!weapon->isCertifiedFor((PlayerCreature*) attacker))
			damage /= 5;
	}

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

	info("Calculating hit chance");

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy));

	float aimMod = 0.0;
	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	info("Base attacker accuracy is " + String::valueOf(attackerAccuracy));

	int targetDefense = getDefenderDefenseModifier(targetCreature, weapon);

	info("Base target defense is " + String::valueOf(targetDefense));

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	/*if (creature->isAiming() && creature->getAimMod() > 0) {
		aimMod = (float) creature->getAimMod();

		if (DEBUG)
			System::out << "\tAttacker aiming mod is " << aimMod << endl;

		creature->clearState(CreatureState::AIMING);
	}*/

	if (targetDefense > 125)
		targetDefense = 125;

	info("Target defense after state affects and cap is " +  String::valueOf(targetDefense));

	float defenseBonus = 0.0f; // TODO: Food/drink defense bonuses go here

	//Food dodge bonus.
	/*if (targetCreature->hasBuff(BuffCRC::FOOD_DODGE_ATTACK)) {
		Buff* buff = targetCreature->getBuff(BuffCRC::FOOD_DODGE_ATTACK);

		if (buff != NULL)
			defenseBonus += buff->getSkillModifierValue("dodge_attack");
	}*/

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy
			+ accuracyBonus + aimMod, targetDefense, defenseBonus);

	info("Final hit chance is " + String::valueOf(accTotal));

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

	info("Calculating secondary hit chance");

	float weaponAccuracy = 0;
	if (attackType == WeaponObject::MELEEATTACK || attackType == WeaponObject::RANGEDATTACK) {
		// Get the weapon mods for range and add the mods for stance
		weaponAccuracy = getWeaponRangeModifier(creature->getDistanceTo(targetCreature), weapon);
		weaponAccuracy += calculatePostureModifier(creature, targetCreature);
	}

	info("Attacker weapon accuracy is " + String::valueOf(weaponAccuracy));

	int attackerAccuracy = getAttackerAccuracyModifier(creature, weapon);

	info("Base attacker accuracy is " + String::valueOf(attackerAccuracy));

	int targetDefense = getDefenderSecondaryDefenseModifier(targetCreature, weapon);

	info("Base target secondary defense is " + String::valueOf(targetDefense));

	targetDefense = applyDefensePenalties(targetCreature, attackType, targetDefense);

	attackerAccuracy = applyAccuracyPenalties(creature, attackType, attackerAccuracy);

	if (targetDefense > 125)
		targetDefense = 125;

	info("Target secondary defense after state affects and cap is " +  String::valueOf(targetDefense));

	if (targetDefense <= 0)
		return 0;

	float accTotal = hitChanceEquation(attackerAccuracy, weaponAccuracy, targetDefense, 0);

	int rand = System::random(100);

	if (rand <= (int) accTotal) // Hit, not defended
		return 0;

	Vector<String>* defenseAccMods = weapon->getDefenderSecondaryDefenseModifiers();

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
	creature->showFlyText("combat_effects", "counterattack", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doBlock(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	creature->showFlyText("combat_effects", "block", 0, 0xFF, 0);

	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::doDodge(CreatureObject* creature, CreatureObject* defender, int damage, const String& cbtSpam) {
	creature->showFlyText("combat_effects", "dodge", 0, 0xFF, 0);

	creature->doCombatAnimation(defender, String("dodge").hashCode(), 0);

	broadcastCombatSpam(creature, defender, creature->getWeapon(), damage, cbtSpam);
}

void CombatManager::applyDamage(TangibleObject* defender, int damage, int poolsToDamage) {
	if (poolsToDamage == 0)
		return;

	if (poolsToDamage & RANDOM) {
		poolsToDamage = 0;

		int rand = System::random(100);

		if (rand < 50) {
			poolsToDamage = HEALTH;
		} else if (rand < 85) {
			poolsToDamage = ACTION;
		} else {
			poolsToDamage = MIND;
		}
	}

	if (poolsToDamage & HEALTH) {
		defender->inflictDamage(CreatureAttribute::HEALTH, damage, true);
	}

	if (poolsToDamage & ACTION) {
		defender->inflictDamage(CreatureAttribute::ACTION, damage, true);
	}

	if (poolsToDamage & MIND) {
		defender->inflictDamage(CreatureAttribute::MIND, damage, true);
	}
}

int CombatManager::doCombatAction(CreatureObject* attacker, TangibleObject* defenderObject, int damageMultiplier, int speedMultiplier, int poolsToDamage, uint32 animationCRC, const String& combatSpam) {
	int damage = 0;
	if (defenderObject->isCreatureObject()) {
		CreatureObject* defender = (CreatureObject*) defenderObject;

		return doCombatAction(attacker, defender, damageMultiplier, speedMultiplier, poolsToDamage, animationCRC, combatSpam);
	} else {
		damage = calculateDamage(attacker, defenderObject);

		if (damage > 0) {
			applyDamage(defenderObject, damage, poolsToDamage);
		}

		CombatAction* combatAction = new CombatAction(attacker, animationCRC);
		attacker->broadcastMessage(combatAction, true);

		broadcastCombatSpam(attacker, defenderObject, attacker->getWeapon(), damage, combatSpam + "_hit");
	}

	return damage;
}

int CombatManager::doCombatAction(CreatureObject* attacker, CreatureObject* defender, int damageMultiplier, int speedMultiplier, int poolsToDamage, uint32 animationCRC, const String& combatSpam) {
	int damage = 0;

	damage = calculateDamage(attacker, defender);

	damage *= damageMultiplier;

	int rand = System::random(100);

	if (rand > getHitChance(attacker, defender, attacker->getWeapon(), 0)) {
		//better luck next time
		doMiss(attacker, defender, damage, combatSpam + "_miss");
		return 0;
	}

	int secondaryDefense = checkSecondaryDefenses(attacker, defender, attacker->getWeapon());

	if (secondaryDefense != 0) {
		switch (secondaryDefense) {
		case BLOCK:
			damage /= 2;
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

	if (damage > 0)
		applyDamage(defender, damage, poolsToDamage);

	CombatAction* combatAction = new CombatAction(attacker, defender, animationCRC, 1);
	attacker->broadcastMessage(combatAction, true);

	broadcastCombatSpam(attacker, defender, attacker->getWeapon(), damage, combatSpam + "_hit");

	return 0;
}

void CombatManager::broadcastCombatSpam(CreatureObject* attacker, TangibleObject* defender, TangibleObject* weapon, uint32 damage, const String& stringid) {
	Zone* zone = attacker->getZone();

	Locker _locker(zone);

	for (int i = 0; i < attacker->inRangeObjectCount(); ++i) {
		SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) attacker->getInRangeObject(i))->_this);

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

	try {
		targetPlayer->wlock(player);

		if (player->requestedDuelTo(targetPlayer)) {
			ParameterizedStringId stringId("duel", "already_challenged");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->unlock();
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

			ParameterizedStringId stringId("duel", "accept_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player,
					player->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE
							+ CreatureFlag::AGGRESSIVE);
			targetPlayer->sendMessage(pvpstat2);

			ParameterizedStringId stringId2("duel", "accept_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		} else {
			ParameterizedStringId stringId3("duel", "challenge_self");
			stringId3.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId3);

			ParameterizedStringId stringId4("duel", "challenge_target");
			stringId4.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId3);
		}

		targetPlayer->unlock();
	} catch (Exception& e) {
		targetPlayer->unlock();

		StringBuffer msg;
		msg << "Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n"
				<< e.getMessage();

		error(msg.toString());
	} catch (...) {
		targetPlayer->unlock();

		StringBuffer msg;
		msg << "Unreported Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n";

		error(msg.toString());
	}
}

void CombatManager::requestEndDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player requested to end the duel with targetPlayer
	 */

	try {
		targetPlayer->wlock(player);

		if (!player->requestedDuelTo(targetPlayer)) {
			ParameterizedStringId stringId("duel", "not_dueling");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->unlock();
			return;
		}

		player->info("ending duel");

		player->removeFromDuelList(targetPlayer);

		if (targetPlayer->requestedDuelTo(player)) {
			targetPlayer->removeFromDuelList(player);

			player->sendPvpStatusTo(targetPlayer);

			ParameterizedStringId stringId("duel", "end_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			targetPlayer->sendPvpStatusTo(player);

			ParameterizedStringId stringId2("duel", "end_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		}

		targetPlayer->unlock();
	} catch (...) {
		targetPlayer->unlock();
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
				targetPlayer->wlock(player);

				player->removeFromDuelList(targetPlayer);

				if (targetPlayer->requestedDuelTo(player)) {
					targetPlayer->removeFromDuelList(player);

					player->sendPvpStatusTo(targetPlayer);

					if (spam) {
						ParameterizedStringId stringId("duel", "end_self");
						stringId.setTT(targetPlayer->getObjectID());
						player->sendSystemMessage(stringId);
					}

					targetPlayer->sendPvpStatusTo(player);

					if (spam) {
						ParameterizedStringId stringId2("duel", "end_target");
						stringId2.setTT(player->getObjectID());
						targetPlayer->sendSystemMessage(stringId2);
					}
				}


				targetPlayer->unlock();
			} catch (ObjectNotDeployedException& e) {
				player->removeFromDuelList(targetPlayer);

				System::out << "Exception on CombatManager::freeDuelList()\n"
						<< e.getMessage() << "\n";
			} catch (...) {
				targetPlayer->unlock();
			}
		}
	}
}

void CombatManager::declineDuel(PlayerCreature* player, PlayerCreature* targetPlayer) {
	/* Pre: player != targetPlayer and not NULL; player is locked
	 * Post: player declined Duel to targetPlayer
	 */

	try {
		targetPlayer->wlock(player);

		if (targetPlayer->requestedDuelTo(player)) {
			targetPlayer->removeFromDuelList(player);

			ParameterizedStringId stringId("duel", "cancel_self");
			stringId.setTT(targetPlayer->getObjectID());
			player->sendSystemMessage(stringId);

			ParameterizedStringId stringId2("duel", "cancel_target");
			stringId2.setTT(player->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		}

		targetPlayer->unlock();
	} catch (...) {
		targetPlayer->unlock();
	}
}

