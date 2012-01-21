/*
 * CreatureImplementation.cpp
 *
 *  Created on: 10/23/2010
 *      Author: Kyle
 */

#include "CreatureObject.h"
#include "Creature.h"
#include "AiAgent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/tangible/DamageMap.h"


void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	AiAgentImplementation::notifyPositionUpdate(entry);

	SceneObject* scno = cast<SceneObject*>( entry);

	// don't worry about this if no one's around, and do it for any creature
	if (scno == _this || numberOfPlayersInRange <= 0  || !scno->isCreatureObject() || isRetreating() || isFleeing() || isInCombat())
		return;

	if (followObject == NULL || followObject == scno) {
		CreatureObject* creo = cast<CreatureObject*>( scno);

		// TODO: determine if creature can be seen by this (mask scent, et. al.)

		// determine if creature can be a threat
		if (creo->isAiAgent()) {
			AiAgent* aio = cast<AiAgent*>(creo);
			if ((aio->getFerocity() <= 0 || getFerocity() <= 0) && aio->getLevel() >= getLevel())
				return;
		} else if (this->isAttackableBy(creo) && isInRange(scno, 15) && !creo->isDead()) { //no aigent<->aigent combat for now
			activateAwarenessEvent(creo);
		}
	}
}

void CreatureImplementation::doAwarenessCheck(Coordinate& start, uint64 time, CreatureObject* target) {
	if (isDead() || getZone() == NULL || time == 0 || target->isDead())
		return;

	int awarenessRadius = getFerocity() + 32;

	if( getDistanceTo(target) > awarenessRadius || isCamouflaged(target))
		return;

	// calculate average speed
	Vector3 deltaV(target->getPositionX() - start.getPositionX(), target->getPositionY() - start.getPositionY(), 0);
	float avgSpeed = deltaV.squaredLength() / (time) * 1000000;

	// set frightened or threatened
	// TODO: weight this by ferocity/level difference
	if (isStalker() && isAggressiveTo(target)) {
		if (followObject == NULL)
			setStalkObject(target);
		else if (avgSpeed <= (target->getWalkSpeed() * target->getWalkSpeed()))
			addDefender(target);
	} else if (isAggressiveTo(target))
		addDefender(target);
	else if (avgSpeed <= (target->getWalkSpeed() * target->getWalkSpeed())) {
		setOblivious();
	} else if (followObject == NULL) {
		setWatchObject(target);
		showFlyText("npc_reaction/flytext", "alert", 0xFF, 0, 0);
	} else if (followObject->isCreatureObject() && target == followObject) {
		ManagedReference<CreatureObject*> creo = dynamic_cast<CreatureObject*>(followObject.get());
		// determine if frightened or threatened
		if (creo->isAiAgent()) {
			AiAgent* aio = cast<AiAgent*>(creo.get());
			if (getFerocity() > aio->getFerocity() && getLevel() >= aio->getLevel())
				addDefender(aio);
			else if (getLevel() < aio->getLevel()) {
				if (!tryRetreat())
					runAway(target);
			} else
				setOblivious();
		} else if (creo->isPlayerCreature()) {
			CreatureObject* play = cast<CreatureObject*>(creo.get());
			// TODO: tweak this formula based on feedback
			if ((getFerocity() * getLevel() / 4) < play->getLevel()) {
				if (!tryRetreat())
					runAway(target);
			} else
				addDefender(play);
		}
	}

	activateRecovery();
	activateMovementEvent();
}

bool CreatureImplementation::isCamouflaged(CreatureObject* target) {
	/// check invisible
	if (target->isPlayerCreature()) {
		PlayerObject* ghost = cast<PlayerObject*> (target->getSlottedObject(
				"ghost"));
		if (ghost != NULL) {
			if (ghost->isInvisible())
				return true;
		}
	}

	/// Check masked scent
	if (!target->hasState(CreatureState::MASKSCENT)) {
		if(camouflagedObjects.contains(target)) {
			camouflagedObjects.removeElement(target);
		}
		return false;
	}

	/// Don't do anything if object is ignored (Camo / Masked Scent)
	if (camouflagedObjects.contains(target))
		return true;

	int camoSkill = target->getSkillMod("mask_scent");
	int creatureLevel = getLevel();
	int chance = (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + 100;
	int roll = System::random(100);

	if (roll > chance) {
		uint32 crc = String("skill_buff_mask_scent").hashCode();
		target->sendSystemMessage("skl_use", "sys_scentmask_break");
		target->removeBuff(crc);
	} else {
		StringIdChatParameter success("skl_use", "sys_scentmask_success");
		success.setTT(getObjectName()->getDisplayedName());

		target->sendSystemMessage(success);

		camouflagedObjects.add(target);

		PlayerObject* ghost = cast<PlayerObject*> (target->getSlottedObject(
				"ghost"));
		if (ghost != NULL)
			ghost->addExperience("scout", (creatureLevel * 2), true);
		return true;
	}

	return false;
}

void CreatureImplementation::runAway(CreatureObject* target) {
	if (target == NULL)
		return;

	setOblivious();

	damageMap->removeAll();

	Vector3 runTrajectory(getPositionX() - target->getPositionX(), getPositionY() - target->getPositionY(), 0);
	runTrajectory = runTrajectory * (100 / runTrajectory.length());
	runTrajectory += target->getPosition();

	patrolPoints.removeAll();
	setNextPosition(runTrajectory.getX(), getZone()->getHeight(runTrajectory.getX(), runTrajectory.getY()), runTrajectory.getY(), getParent());

	showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);


	fleeing = true;

	CombatManager::instance()->forcePeace(_this);

	activateMovementEvent();
}

void CreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {

	/*menuResponse->addRadialMenuItem(205, 1, "@pet/pet_menu:menu_enter_exit");
	menuResponse->addRadialMenuItem(61, 3, "");

	if (checkInRangeGarage() && !isDestroyed())
		menuResponse->addRadialMenuItem(62, 3, "Repair");*/

	if (player->isInRange(_this, 10.0f)
			&& !player->isInCombat() && player->hasSkill("outdoors_scout_novice")
			&& isDead() && canHarvestMe(player)) {

		menuResponse->addRadialMenuItem(112, 3, "@sui:harvest_corpse");

		if (getMeatType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 234, 3, "@sui:harvest_meat");

		if (getHideType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 235, 3, "@sui:harvest_hide");

		if (getBoneType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 236, 3, "@sui:harvest_bone");
	}

	/*if (player->isInRange(getPositionX(), getPositionY(), 10.0f) && player->hasBiologicalSignature()
			&& getObjectCRC() == 0x78E5C3B5 && getCreatureLinkID() == player->getObjectID()){
		omr->addRadialParent(137, 3, "Transfer Bio-Signature");
	}*/
}

int CreatureImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (getZone() == NULL)
		return 0;

	if (selectedID == 112 || selectedID == 234 || selectedID == 235 || selectedID == 236) {
		getZone()->getCreatureManager()->harvest(_this, player, selectedID);

		return 0;
	}

	return AiAgentImplementation::handleObjectMenuSelect(player, selectedID);
}

void CreatureImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	AiAgentImplementation::fillAttributeList(alm, player);

	int creaKnowledge = player->getSkillMod("creature_knowledge");

	if (getHideType().isEmpty() && getBoneType().isEmpty() && getMeatType().isEmpty()) {
		return;
	}

	if (creaKnowledge >= 5) {
		if (isAggressiveTo(player))
			alm->insertAttribute("aggro", "yes");
		else
			alm->insertAttribute("aggro", "no");
		if (isStalker())
			alm->insertAttribute("stalking", "yes");
		else
			alm->insertAttribute("stalking", "no");
	}

	if (creaKnowledge >= 10) {
		if (getTame() >= 0.0f && isBaby())
			alm->insertAttribute("tamable", "yes");
		else
			alm->insertAttribute("tamable", "no");
	}

	if (creaKnowledge >= 20) {
		if (!getHideType().isEmpty()) {
			StringBuffer hideName;
			hideName << "@obj_attr_n:" << getHideType();
			alm->insertAttribute("res_hide", hideName.toString());
		} else
			alm->insertAttribute("res_hide", "---");
		if (!getBoneType().isEmpty()) {
			StringBuffer boneName;
			boneName << "@obj_attr_n:" << getBoneType();
			alm->insertAttribute("res_bone", boneName.toString());
		} else
			alm->insertAttribute("res_bone", "---");
		if (!getMeatType().isEmpty()) {
			StringBuffer meatName;
			meatName << "@obj_attr_n:" << getMeatType();
			alm->insertAttribute("res_meat", meatName.toString());
		} else
			alm->insertAttribute("res_meat", "---");
	}

	if (creaKnowledge >= 30) {
		if (isKiller())
			alm->insertAttribute("killer", "yes");
		else
			alm->insertAttribute("killer", "no");
	}

	if (creaKnowledge >= 40) {
		alm->insertAttribute("ferocity", (int) getFerocity());
	}

	if (creaKnowledge >= 50)
		alm->insertAttribute("challenge_level", getLevel());

	//int skillNum = skillCommands.size();
	CreatureAttackMap* attackMap = getAttackMap();
	int skillNum = 0;
	if (attackMap != NULL)
		skillNum = attackMap->size();

	if (creaKnowledge >= 70) {
		String skillname = "none";
		if (skillNum >= 1)
			skillname = attackMap->getCommand(0);

		StringBuffer skillMsg;
		skillMsg << "@combat_effects:" << skillname;

		alm->insertAttribute("pet_command_18", skillMsg.toString());
	}

	if (creaKnowledge >= 80) {
		String skillname = "none";
		if (skillNum >= 2)
			skillname = attackMap->getCommand(1);

		StringBuffer skillMsg;
		skillMsg << "@combat_effects:" << skillname;

		alm->insertAttribute("pet_command_19", skillMsg.toString());
	}

	if (creaKnowledge >= 90)
		alm->insertAttribute("basetohit", getChanceHit());

	if (creaKnowledge >= 100) {
		StringBuffer damageMsg;
		damageMsg << getDamageMin() << "-" << getDamageMax();
		alm->insertAttribute("cat_wpn_damage", damageMsg.toString());
	}
}

void CreatureImplementation::scheduleDespawn() {
	if (getPendingTask("despawn") != NULL)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(_this);
	//despawn->schedule(300000); /// 5 minutes
	addPendingTask("despawn", despawn, 45000); /// 45 seconds
}

bool CreatureImplementation::hasOrganics() {
	return ((getHideMax() + getBoneMax() + getMeatMax()) > 0);
}

bool CreatureImplementation::canHarvestMe(CreatureObject* player) {
	if (!hasOrganics())
		return false;

	if (player != lootOwner && lootOwner != NULL) {
		ManagedReference<GroupObject*> group = lootOwner->getGroup();

		if (group == NULL)
			return false;

		if (!group->hasMember(player))
			return false;
	}

	if (player->hasSkill("outdoors_scout_novice"))
		return true;
	else
		return false;
}
