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

float CombatManager::handleAction(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();

	if (creature != NULL && creature->isPlayer() && ((Player*)creature)->isImmune()) {
		((Player*)creature)->sendSystemMessage("You cannot attack while Immune.");
		return 0.0f;
	}

	Skill* skill = action->getSkill();

	if (skill->isTargetSkill())
		return doTargetSkill(action);
	else if (skill->isSelfSkill())
		return doSelfSkill(action);

	return 0.0f;
}

float CombatManager::doTargetSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();
	SceneObject* target = action->getTarget();

	if (target != NULL && target->isPlayer() && ((Player*)target)->isImmune()) {
		if (creature->isPlayer())
			((Player*)creature)->sendSystemMessage("You cannot attack an immune player.");
		return 0.0f;
	}

	string actionModifier = action->getActionModifier();

	TargetSkill* tskill = (TargetSkill*)action->getSkill();

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

		return tskill->calculateSpeed(creature);
	}

	if (!checkSkill(creature, target, tskill))
		return 0.0f;

	uint32 animCRC = tskill->getAnimCRC();

	if (animCRC == 0)
		animCRC = getDefaultAttackAnimation(creature);

	CombatAction* actionMessage = new CombatAction(creature, animCRC);

	if (!doAction(creature, target, tskill, actionModifier, actionMessage)) {
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

	string actionModifier = action->getActionModifier();

	if (!selfskill->isUseful(creature))
		return 0.0f;

	if (!selfskill->calculateCost(creature))
		return 0.0f;

	selfskill->doSkill(creature, actionModifier);

	if (selfskill->isEnhanceSkill()) {
		EnhanceSelfSkill* enhance = (EnhanceSelfSkill*) selfskill;

		if (enhance->getDuration() != 0) {
			SelfEnhanceEvent* event = new SelfEnhanceEvent(creature, enhance);
			server->addEvent(event);
		}
	}

	return selfskill->calculateSpeed(creature);
}


void CombatManager::handleAreaAction(CreatureObject* creature, SceneObject* target, CommandQueueAction* action, CombatAction* actionMessage) {
	TargetSkill* skill = (TargetSkill*) action->getSkill();

	float CreatureVectorX = creature->getPositionX();
	float CreatureVectorY = creature->getPositionY();

	float DirectionVectorX = target->getPositionX() - CreatureVectorX;
	float DirectionVectorY = target->getPositionY() - CreatureVectorY;

	string actionModifier = action->getActionModifier();

	Zone* zone = creature->getZone();
	try {
		zone->lock();

		for (int i = 0; i < creature->inRangeObjectCount(); i++) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) creature->getInRangeObject(i))->_this);

			if (!object->isPlayer() && !object->isNonPlayerCreature() && !object->isAttackableObject())
				continue;

			SceneObject* targetObject = (SceneObject*) object;

			if (targetObject == creature || targetObject == target)
				continue;

			if (!targetObject->isAttackableBy(creature))
				continue;

			if (!creature->isPlayer() && !targetObject->isPlayer())
				continue;

			Player* playerTarget = (Player*) targetObject;

			if (targetObject->isPlayer() && (playerTarget->isIncapacitated() || playerTarget->isDead() || playerTarget->isImmune()))
				continue;


			if (creature->getParent() != targetObject->getParent())
				continue;

			if (skill->isCone()) {
				if (!(creature->isInRange(targetObject, skill->getRange())))
					continue;

				float angle = getConeAngle(targetObject, CreatureVectorX, CreatureVectorY, DirectionVectorX, DirectionVectorY);
				float coneAngle = skill->getConeAngle() / 2;

				if (angle > coneAngle || angle < -coneAngle)
					continue;

			} else if (!(creature->isInRange(targetObject, skill->getAreaRange())))
				continue;

			zone->unlock();

			doAction(creature, targetObject, skill, actionModifier, NULL);

			zone->lock();
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();

		cout << "Exception in CombatManager::handleAreaAction\n";
	}
}

bool CombatManager::doAction(CreatureObject* attacker, SceneObject* target, TargetSkill* skill,  string& modifier, CombatAction* actionMessage) {
	try {
		target->wlock(attacker);

		Creature* targetCreature = NULL;

		if (target->isPlayer()) {
			targetCreature = (Creature*) target;
			Player* targetPlayer = (Player*) target;

			if (attacker->isPlayer()) {
				Player* player = (Player*) attacker;
				if (!canAttack(player, targetPlayer)) {
					targetCreature->unlock();
					return false;
				}
			}

			if (!targetPlayer->isOnline()) {
				targetCreature->unlock();
				return false;
			}
		}

		if (target->isNonPlayerCreature()) {
			targetCreature = (Creature*) target;

			if (targetCreature->isIncapacitated() || targetCreature->isDead()) {
				target->unlock();
				return false;
			}

			Creature* creature = (Creature*)targetCreature;
			if (creature->isMount()) {
				if (!skill->isAttackSkill()) {
					targetCreature->unlock();
					return false;
				}

				return handleMountDamage(attacker, (MountCreature*)creature);
			}
		} else if (target->isAttackableObject()) {
			AttackableObject* targetObject = (AttackableObject*) target;
			if (targetObject->isDestroyed()) {
				target->unlock();
				return false;
			}
		}

		if (skill->isAttackSkill()) {
			if (targetCreature != NULL) {
				if (targetCreature->isPlayingMusic())
					targetCreature->stopPlayingMusic();
				else if (targetCreature->isDancing())
					targetCreature->stopDancing();
			}

			if (skill->isArea())
				attacker->addDefender(target);
			else
				attacker->setDefender(target);

			target->addDefender(attacker);
			attacker->clearState(CreatureObjectImplementation::PEACE_STATE);
		}

		int damage = skill->doSkill(attacker, target, modifier, false);

		if (actionMessage != NULL && targetCreature != NULL) //disabled untill we figure out how to make it work for more defenders
			actionMessage->addDefender(targetCreature, damage > 0);

		if (targetCreature != NULL) {
			if (targetCreature->isIncapacitated()) {
				attacker->sendSystemMessage("base_player", "prose_target_incap", targetCreature->getObjectID());

				if (!skill->isArea())
					attacker->clearCombatState(true);
			} else if (targetCreature->isDead()) {
				attacker->sendSystemMessage("base_player", "prose_target_dead", targetCreature->getObjectID());

				if (!skill->isArea())
					attacker->clearCombatState(true);
			}

			if (!targetCreature->isIncapacitated() && skill->isAttackSkill()) {
				AttackTargetSkill* askill = (AttackTargetSkill*) skill;
				askill->calculateStates(attacker, targetCreature);

				if(targetCreature->isNonPlayerCreature()) {
					Creature* creature = (Creature*) targetCreature;
					if (!creature->isMount())
						creature->doAttack(attacker, damage);
				}

				targetCreature->activateRecovery();
			}
		}
		else {
			AttackableObject* targetObject = (AttackableObject*) target;
			targetObject->doDamage(damage, attacker);
		}

		target->unlock();
	} catch (Exception& e) {
		cout << "Exception in doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill)\n"
			 << e.getMessage() << "\n";
		e.printStackTrace();

		target->unlock();

		return false;
	} catch (...) {
		cout << "exception in doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill)";

		target->unlock();

		return false;
	}

	return true;
}

bool CombatManager::handleMountDamage(CreatureObject* attacker, MountCreature* mount) {
	// Pre: targetCraeture && mount locked
	// Post: mount unlocked
	if (attacker->getMount() == mount) {
		mount->unlock();
		return false;
	}

	CreatureObject* owner = mount->getLinkedCreature();

	if (mount->isDisabled()) {
		mount->unlock();
		return false;
	}

	if (!mount->isInWorld()) {
		mount->unlock();
		return false;
	}

	if (owner == attacker) {
		mount->unlock();
		return false;
	}

	if (owner->isPlayer() && attacker->isPlayer()) {
		Player* player = (Player*) owner;

		mount->unlock();

		if (player == attacker)
			return false;

		player->wlock(attacker);

		if (!canAttack((Player*)attacker, player)) {
			player->unlock();
			return false;
		}

		player->unlock();

		mount->wlock(attacker);
	}

	mount->changeConditionDamage(System::random(20000));

	if (mount->isDisabled()) {
		CreatureObject* creature = mount->getLinkedCreature();
		if (creature != NULL && creature->isMounted()) {
			mount->unlock();

			creature->wlock(attacker);
			creature->dismount();
			creature->unlock();

			return true;
		}
	}

	mount->unlock();
	return true;

}

bool CombatManager::canAttack(Player* player, Player* targetPlayer) {
	/* Pre: player && targetPlayer not NULL; targetPlayer is cross locked to player
	 * Post: player is in duel with target or is overt and has the oposite faction
	 */
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
	//Pre: creature wlocked

	Weapon* weapon = creature->getWeapon();

	if (weapon == NULL)
		return 0x99476628;

	switch (weapon->getCategory()) {
		case (WeaponImplementation::MELEE):
			return 0x43C4FFD0;
		case (WeaponImplementation::RANGED):
			return 0x506E9D4C;
	}

	return 0;
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
			BaseMessage* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask() + CreatureObjectImplementation::ATTACKABLE_FLAG + CreatureObjectImplementation::AGGRESSIVE_FLAG);
			player->sendMessage(pvpstat);

			ChatSystemMessage* csm = new ChatSystemMessage("duel", "accept_self", targetPlayer->getObjectID());
			player->sendMessage(csm);

			BaseMessage* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask() + CreatureObjectImplementation::ATTACKABLE_FLAG + CreatureObjectImplementation::AGGRESSIVE_FLAG);
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
		cout << "Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n" << e.getMessage() << "\n";
	} catch (...) {
		cout << "Unreported Exception caught in CombatManager::requestDuel(Player* player, Player* targetPlayer)\n";
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

				cout << "Exception on CombatManager::freeDuelList()\n" << e.getMessage() << "\n";
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

void CombatManager::doDodge(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "dodge", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String::hashCode("dodge"), 0);
}

void CombatManager::doCounterAttack(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "counterattack", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String::hashCode("dodge"), 0);
}

void CombatManager::doBlock(CreatureObject* creature, CreatureObject* defender) {
	creature->showFlyText("combat_effects", "block", 0, 0xFF, 0);
	creature->doCombatAnimation(defender, String::hashCode("dodge"), 0);
}

// calc methods
void CombatManager::calculateDamageReduction(CreatureObject* creature, CreatureObject* targetCreature, float& damage) {
	//Armor piercing: figure difference in AP to AR, apply 25% increases or 50% decreases accordingly
	// Source: http://www.nofuture.org.uk/swg/rifleman.php (and others)

	// AP/AR calculations have been removed form this section. - Avengre


	//Other factors
	if (targetCreature->isPlayer())
		damage = damage / 4;

	if (targetCreature->isKnockedDown())
		damage *= 1.33f;

	if (creature->isIntimidated())
		damage *= 0.8f;
}

void CombatManager::checkMitigation(CreatureObject* creature, CreatureObject* targetCreature, float& minDamage, float& maxDamage) {
	Weapon* weapon = creature->getWeapon();
	Weapon* tarWeapon = targetCreature->getWeapon();

	int creatureWeaponCategory = WeaponImplementation::MELEE;
	int targetWeaponCategory = WeaponImplementation::MELEE;

	if (weapon != NULL)
		creatureWeaponCategory = weapon->getCategory();

	if (tarWeapon != NULL)
		targetWeaponCategory = tarWeapon->getCategory();

	if (creatureWeaponCategory == WeaponImplementation::MELEE) {
		uint32 mit = targetCreature->getMitigation("melee_damage_mitigation_3");

		if (mit == 0) {
			mit = targetCreature->getMitigation("melee_damage_mitigation_2");
			if (mit == 0)
				mit = targetCreature->getMitigation("melee_damage_mitigation_1");
		}

		if (mit != 0)
			maxDamage = minDamage + ((maxDamage - minDamage) * (1 - (float)mit / 100));

	} else if (creatureWeaponCategory == WeaponImplementation::RANGED) {
		uint32 mit = targetCreature->getMitigation("ranged_damage_mitigation_3");

		if (mit == 0) {
			mit = targetCreature->getMitigation("ranged_damage_mitigation_2");
			if (mit == 0)
				mit = targetCreature->getMitigation("ranged_damage_mitigation_1");
		}

		if (mit != 0)
			maxDamage = minDamage + ((maxDamage - minDamage) * (1 - (float)mit / 100));
	}
}

int CombatManager::checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature) {
	if (targetCreature->isIntimidated())
		return 0;

	Weapon* targetWeapon = targetCreature->getWeapon();
	Weapon* playerWeapon = creature->getWeapon();

	if (targetWeapon == NULL)
		return 0;

	float playerAccuracy = creature->getAccuracy();
	float weaponAccuracy = getWeaponAccuracy(creature->getDistanceTo(targetCreature), playerWeapon);

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

	return 0;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, int accuracyBonus) {
	int hitChance = 0;
	Weapon* weapon = creature->getWeapon();

	float weaponAccuracy = getWeaponAccuracy(creature->getDistanceTo(targetCreature), weapon);
	weaponAccuracy += calculatePostureMods(creature, targetCreature);

	// TODO: add Aim mod

	float playerAccuracy = creature->getAccuracy();

	if (playerAccuracy > 250.f)
		playerAccuracy = 250.f;

	uint32 targetDefense = getTargetDefense(creature, targetCreature, weapon);

	float defTotal = powf((float)(targetDefense << 1), 2);
	float accTotal = 0;

	int blindState = 0;

	if (creature->isBlinded())
		blindState = 50;

	if ((playerAccuracy + weaponAccuracy - blindState) < 0)
		accTotal = 0;
	else
		accTotal = powf((playerAccuracy * 1.5 + weaponAccuracy - blindState), 2);

	defTotal -= (defTotal * targetCreature->calculateBFRatio());

	float primaryDef = defTotal / (defTotal + accTotal);

	if (creature->isStunned())
		primaryDef *= 0.33;

	//cout << "primaryDef:[" << primaryDef << "] accTotal:[" << accTotal << "] defTotal:[" << defTotal << "]\n";

	hitChance = (int)round(((1 - primaryDef) * 100));

	//cout << "hitChance:[" << (int)hitChance << "]\n";

	return hitChance;
}

float CombatManager::getWeaponAccuracy(float currentRange, Weapon* weapon) {
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

	//cout << "Weapon accuracy:[" << accuracy << "]\n";

	return accuracy;
}

int CombatManager::calculatePostureMods(CreatureObject* creature, CreatureObject* targetCreature) {
	int accuracy = 0;
	Weapon* weapon = creature->getWeapon();

	if (targetCreature->isKneeled()) {
		if (weapon == NULL || weapon->isMelee())
			accuracy += 16;
		else
			accuracy -= 16;
	} else if (targetCreature->isProne()) {
		if (weapon == NULL || weapon->isMelee())
			accuracy += 25;
		else
			accuracy -= 25;
	}

	if (creature->isKneeled()) {
		if (weapon == NULL || weapon->isMelee())
			accuracy -= 16;
		else
			accuracy += 16;
	} else if (creature->isProne()) {
		if (weapon == NULL || weapon->isMelee())
			accuracy -= 50;
		else
			accuracy += 50;
	}

	return accuracy;
}

uint32 CombatManager::getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon) {
	uint32 defense = 0;
	uint32 targetPosture = targetCreature->getPosture();

	if (weapon != NULL) {
		if (weapon->isMelee()) {
			uint32 melee = targetCreature->getSkillMod("melee_defense");
			defense += melee;
		} else if (weapon->isRanged()) {
			uint32 ranged = targetCreature->getSkillMod("ranged_defense");
			defense += ranged;
		}
	} else {
		uint32 melee = targetCreature->getSkillMod("melee_defense");
		defense += melee;
	}

	//defense += targetCreature->getDefenseBonus();

	if (defense > 125)
		defense = 125;

	return defense - (uint32)(defense * targetCreature->calculateBFRatio());
}
