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

CombatManager::CombatManager(ZoneProcessServerImplementation* srv) {
	server = srv;
}

float CombatManager::handleAction(CommandQueueAction* action) {
	Skill* skill = action->getSkill();

	if (skill->isTargetSkill())
		return doTargetSkill(action);
	else if (skill->isSelfSkill())
		return doSelfSkill(action);
}

float CombatManager::doTargetSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();
	CreatureObject* targetCreature = action->getTarget();

	if (creature->isWatching())
		creature->stopWatch(creature->getWatchID());
		
	if (creature->isListening())
		creature->stopListen(creature->getListenID());

	TargetSkill* tskill = (TargetSkill*)action->getSkill();
	
	if (tskill->isHealSkill()) {
		if (!tskill->calculateCost(creature))
			return 0.0f;

		try {
			if (creature != targetCreature)
				targetCreature->wlock(creature);
			
				tskill->doSkill(creature, targetCreature);
			
			if (creature != targetCreature)
				targetCreature->unlock();
		} catch (...) {
			if (creature != targetCreature)
				targetCreature->unlock();
		}

		return tskill->calculateSpeed(creature);
	}

	if (!checkSkill(creature, targetCreature, tskill))
		return 0.0f;
	
	CombatAction* actionMessage = new CombatAction(creature, tskill->getAnimCRC());
	
	if (!doAction(creature, targetCreature, tskill, actionMessage)) {
		delete actionMessage;
		return 0.0f;
	}

	if (tskill->isArea())
		handleAreaAction(creature, targetCreature, action, actionMessage);
	
	creature->broadcastMessage(actionMessage);

	return tskill->calculateSpeed(creature);
}

float CombatManager::doSelfSkill(CommandQueueAction* action) {
	CreatureObject* creature = action->getCreature();

	SelfSkill* selfskill = (SelfSkill*) action->getSkill();
		
	if (!selfskill->isUsefull(creature))
		return 0.0f;
		
	if (!selfskill->calculateCost(creature))
		return 0.0f;
	
	selfskill->doSkill(creature);
	
	if (selfskill->isEnhanceSkill()) {
		EnhanceSelfSkill* enhance = (EnhanceSelfSkill*) selfskill;
		
		if (enhance->getDuration() != 0) {
			SelfEnhanceEvent* event = new SelfEnhanceEvent(creature, enhance);
			server->addEvent(event);
		}
	}
			
	return selfskill->calculateSpeed(creature);
}


void CombatManager::handleAreaAction(CreatureObject* creature, CreatureObject* target, CommandQueueAction* action, CombatAction* actionMessage) {
	TargetSkill* skill = (TargetSkill*) action->getSkill();
	
	float CreatureVectorX = creature->getPositionX();
	float CreatureVectorY = creature->getPositionY();
	
	float DirectionVectorX = target->getPositionX() - CreatureVectorX;
	float DirectionVectorY = target->getPositionY() - CreatureVectorY;

	Zone* zone = creature->getZone();
	try {
		zone->lock();
		
		for (int i = 0; i < creature->inRangeObjectCount(); i++) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) creature->getInRangeObject(i))->_this);
						
			if (!object->isPlayer() && !object->isNonPlayerCreature())
				continue;
			
			CreatureObject* targetCreature = (CreatureObject*) object;
		
			if (targetCreature == creature || targetCreature == target)
				continue;
			
			if (!targetCreature->isAttackable())
				continue;
			
			if (!creature->isPlayer() && !targetCreature->isPlayer())
				continue;
			
			if (skill->isCone()) {
				if (!(creature->isInRange(targetCreature, skill->getRange())))
					continue;
				
				float angle = getConeAngle(targetCreature, CreatureVectorX, CreatureVectorY, DirectionVectorX, DirectionVectorY);
				float coneAngle = skill->getConeAngle() / 2;
			
				if (angle > coneAngle || angle < -coneAngle)
					continue;
				
			} else if (!(creature->isInRange(targetCreature, skill->getAreaRange())))
				continue;
			
			zone->unlock();

			if (doAction(creature, targetCreature, skill, NULL)) {
				if (skill->isAttackSkill())
					targetCreature->addDefender(creature);
			}

			zone->lock();
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
		
		cout << "Exception in CombatManager::handleAreaAction\n";
	}
}

bool CombatManager::doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill, CombatAction* actionMessage) {
	try {
		targetCreature->wlock(attacker);
		
		if (targetCreature->isPlayer()) {
			Player* targetPlayer = (Player*) targetCreature;
	
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
		
		if (targetCreature->isIncapacitated() || targetCreature->isDead()) {
			targetCreature->unlock();
			return false;
		}
		
		if (targetCreature->isNonPlayerCreature()) {
			Creature* creature = (Creature*)targetCreature;
			if (creature->isMount()) {
				if (!skill->isAttackSkill()) {
					targetCreature->unlock();
					return false;
				}
						
				return handleMountDamage(attacker, (MountCreature*)creature);
			}
		}
			
		if (skill->isAttackSkill()) {
			if (targetCreature->isPlayingMusic())
				targetCreature->stopPlayingMusic();
			else if (targetCreature->isDancing())
				targetCreature->stopDancing();
			
			attacker->setDefender(targetCreature);
			targetCreature->addDefender(attacker);
		}
		
		int damage = skill->doSkill(attacker, targetCreature, false);
		if (actionMessage != NULL) //disabled untill we figure out how to make it work for more defenders
			actionMessage->addDefender(targetCreature, damage > 0); 
		
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
			
		targetCreature->unlock();
	} catch (...) {
		cout << "exception in doAction(CreatureObject* attacker, CreatureObject* targetCreature, TargetSkill* skill)";
		targetCreature->unlock();
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
		} else if (player->getFaction() == targetPlayer->getFaction()) {
			return false;
		}
	}
	return true;
}

bool CombatManager::checkSkill(CreatureObject* creature, CreatureObject* targetCreature, TargetSkill* skill) {
	if (targetCreature == NULL)
		return false;
		
	if (!skill->isUsefull(creature, targetCreature))
		return false;
			
	if (!skill->calculateCost(creature))
		return false;
	
	return true;	
}

float CombatManager::getConeAngle(CreatureObject* targetCreature, float CreatureVectorX, float CreatureVectorY, float DirectionVectorX, float DirectionVectorY) {
	float Target1 = targetCreature->getPositionX() - CreatureVectorX;
	float Target2 = targetCreature->getPositionY() - CreatureVectorY;
		
	float angle = atan2(Target2, Target1) - atan2(DirectionVectorY, DirectionVectorX);
	float degrees = angle * 180 / M_PI;
	
	return degrees;
}

void CombatManager::requestDuel(Player* player, uint64 targetID) {
	if (targetID != 0) {
		Zone* zone = player->getZone();
		
		SceneObject* targetObject = zone->lookupObject(targetID);

		if (targetObject != NULL && targetObject->isPlayer()) {
			Player* targetPlayer = (Player*)targetObject;
			if (targetPlayer != player)
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
	
		player->addToDuelList(targetPlayer);
		
		if (targetPlayer->requestedDuelTo(player)) {
			Message* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask() + CreatureObjectImplementation::ATTACKABLE_FLAG + CreatureObjectImplementation::AGGRESSIVE_FLAG);	
			player->sendMessage(pvpstat);
		
			ChatSystemMessage* csm = new ChatSystemMessage("duel", "accept_self", targetPlayer->getObjectID());
			player->sendMessage(csm);
			
			Message* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask() + CreatureObjectImplementation::ATTACKABLE_FLAG + CreatureObjectImplementation::AGGRESSIVE_FLAG);	
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
		
		player->removeFromDuelList(targetPlayer);
		
		if (targetPlayer->requestedDuelTo(player)) {
			targetPlayer->removeFromDuelList(player);
			Message* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask());	
			player->sendMessage(pvpstat);
		
			ChatSystemMessage* csm = new ChatSystemMessage("duel", "end_self", targetPlayer->getObjectID());
			player->sendMessage(csm);
			
			Message* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask());	
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
		
	for (int i = 0; i < player->getDuelListSize(); i++) {
		Player* targetPlayer = player->getDuelListObject(i);
		
		if (targetPlayer != NULL) {
			try {
				targetPlayer->wlock(player);

				if (targetPlayer->requestedDuelTo(player)) {
					targetPlayer->removeFromDuelList(player);
					
					Message* pvpstat = new UpdatePVPStatusMessage(targetPlayer, targetPlayer->getPvpStatusBitmask());	
					player->sendMessage(pvpstat);
			
					ChatSystemMessage* csm = new ChatSystemMessage("duel", "end_self", targetPlayer->getObjectID());
					player->sendMessage(csm);
			
					Message* pvpstat2 = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask());	
					targetPlayer->sendMessage(pvpstat2);
				
					ChatSystemMessage* csm2 = new ChatSystemMessage("duel", "end_target", player->getObjectID());
					targetPlayer->sendMessage(csm2);
				}
	
				player->removeFromDuelList(targetPlayer);

				targetPlayer->unlock();
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
	if (targetCreature->isPlayer())
		damage = damage / 3;

	if (targetCreature->isKnockeddowned())
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

	Weapon* weao = targetCreature->getWeapon();

	if (weao == NULL)
		return 0;

	float playerAccuracy = creature->getAccuracy();

	if (playerAccuracy > 250)
		playerAccuracy = 250;

	if (creature->isBlinded())
		playerAccuracy *= 0.80;

	int rand = System::random(100);

	if ((weao->getType() == WeaponImplementation::POLEARM) || (weao->getType() == WeaponImplementation::RIFLE)) {
		float block = targetCreature->getSkillMod("block");

		if (block > 120)
			block = 120;

		int chance = (int)(playerAccuracy - block);

		if ((5 > rand) || (rand > chance)) {
			doBlock(targetCreature, creature);
			return 1;
		}
	} else if ((weao->getType() == WeaponImplementation::ONEHANDED) || (weao->getType() == WeaponImplementation::PISTOL)) {
		float dodge = targetCreature->getSkillMod("dodge");

		if (dodge > 120)
			dodge = 120;

		int chance = (int)(playerAccuracy - dodge);

		if ((5 > rand) || (rand > chance)) {
			doDodge(targetCreature, creature);
			return 2;
		}
	} else if ((weao->getType() == WeaponImplementation::CARBINE) || (weao->getType() == WeaponImplementation::TWOHANDED)) {
		float counterAttack = targetCreature->getSkillMod("counterattack");

		if (counterAttack > 120)
			counterAttack = 120;

		int chance = (int)(playerAccuracy - counterAttack);

		if ((5 > rand) || (rand > chance)) {
			doCounterAttack(targetCreature, creature);
			return 3;
		}
	}

	return 0;
}

int CombatManager::getHitChance(CreatureObject* creature, CreatureObject* targetCreature, int accuracyBonus) {
	float hitChance = 0;
	Weapon* weapon = creature->getWeapon();
	uint32 playerPosture = creature->getPosture();

	float playerAccuracy = creature->getAccuracy();

	if (playerAccuracy > 250)
		playerAccuracy = 250;

	if (creature->isBlinded())
		playerAccuracy *= 0.80;

	hitChance += playerAccuracy;

	float WeaponAccuracy = 30.f;

	if (weapon != NULL)
		WeaponAccuracy = getWeaponAccuracy(creature->getDistanceTo(targetCreature), weapon);

	hitChance += WeaponAccuracy;

	float defense = getTargetDefense(creature, targetCreature, weapon);

	if (targetCreature->isStunned())
		defense *= 0.80;

	hitChance -= defense;		

	hitChance = 66 + (hitChance / 2) + accuracyBonus;

	if (playerPosture == CreatureObjectImplementation::CROUCHED_POSTURE)
		hitChance += 16;
	else if (playerPosture == CreatureObjectImplementation::PRONE_POSTURE)
		hitChance += 50;

	//hitChance += aiming;

	//cout << "hitChance:" << (int)hitChance << "\n";

	return (int)hitChance;
}

float CombatManager::getWeaponAccuracy(float currentRange, Weapon* weapon) {
	float accuracy;

	float smallRange = 0;
	float bigRange = 2;
	float maxRange = 5;

	if (weapon != NULL) {
		smallRange = (float)weapon->getPointBlankRange();
		bigRange = (float)weapon->getIdealRange();
		maxRange = (float)weapon->getMaxRange();
	}

	float smallMod = (float)weapon->getPointBlankAccuracy();
	float bigMod = (float)weapon->getIdealAccuracy();

	if (currentRange > bigRange) {
		smallMod = (float)weapon->getIdealAccuracy();
		bigRange = maxRange;
		bigMod = (float)weapon->getMaxRangeAccuracy();				
	}

	accuracy = smallMod + ((currentRange - smallRange)/(bigRange - smallRange) * (bigMod - smallMod));

	return accuracy;
}

float CombatManager::getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon) {
	float defense = 0;
	uint32 targetPosture = targetCreature->getPosture();

	if (weapon != NULL) {
		if (weapon->isMelee()) {
			int melee = targetCreature->getSkillMod("melee_defense");
			defense += melee;

			if (targetPosture == CreatureObjectImplementation::CROUCHED_POSTURE)
				defense -= 16;
			else if (targetPosture == CreatureObjectImplementation::PRONE_POSTURE)
				defense -=25;

		} else if (weapon->isRanged()) {
			int ranged = targetCreature->getSkillMod("ranged_defense");
			defense += ranged;

			if (targetPosture == CreatureObjectImplementation::CROUCHED_POSTURE)
				defense += 16;
			else if (targetPosture == CreatureObjectImplementation::PRONE_POSTURE)
				defense +=25;
		}
	} else {		

		int bonus = creature->getSkillMod("unarmed_accuracy");
		defense -= bonus;

		int melee = targetCreature->getSkillMod("melee_defense");
		defense += melee;

		if (targetPosture == CreatureObjectImplementation::CROUCHED_POSTURE)
			defense -= 16;
		else if (targetPosture == CreatureObjectImplementation::PRONE_POSTURE)
			defense -=25;
	}

	defense += targetCreature->getDefenseBonus();

	if (defense > 200)
		defense = 200;

	return defense;
}
