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
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/combat/CombatManager.h"


void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) entry;

	// don't worry about this if no one's around, and do it for any creature
	if (scno == _this || numberOfPlayersInRange <= 0  || !scno->isCreatureObject() || isRetreating() || isFleeing() || isInCombat())
		return;

	if (followObject == NULL || followObject == scno) {
		CreatureObject* creo = (CreatureObject*)scno;

		// TODO: determine if creature can be seen by this (mask scent, et. al.)

		// determine if creature can be a threat
		if (creo->isAiAgent()) {
			AiAgent* aio = (AiAgent*)creo;
			if ((aio->getFerocity() <= 0 || getFerocity() <= 0) && aio->getLevel() >= getLevel())
				return;
		} else if (this->isAttackableBy(creo)) //no aigent<->aigent combat for now
			activateAwarenessEvent(creo);
	}

}

void CreatureImplementation::doAwarenessCheck(Coordinate& start, uint64 time, CreatureObject* target) {
	if (isDead() || zone == NULL || time == 0)
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
			AiAgent* aio = (AiAgent*)creo.get();
			if (getFerocity() > aio->getFerocity() && getLevel() >= aio->getLevel())
				addDefender(aio);
			else if (getLevel() < aio->getLevel()) {
				if (!tryRetreat())
					runAway(target);
			} else
				setOblivious();
		} else if (creo->isPlayerCreature()) {
			PlayerCreature* play = (PlayerCreature*)creo.get();
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

void CreatureImplementation::runAway(CreatureObject* target) {
	if (target == NULL)
		return;

	setOblivious();

	damageMap.removeAll();

	Vector3 runTrajectory(getPositionX() - target->getPositionX(), getPositionY() - target->getPositionY(), 0);
	runTrajectory = runTrajectory * (100 / runTrajectory.length());
	runTrajectory += target->getPosition();

	patrolPoints.removeAll();
	setNextPosition(runTrajectory.getX(), zone->getHeight(runTrajectory.getX(), runTrajectory.getY()), runTrajectory.getY(), getParent());

	showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);

	fleeing = true;

	CombatManager::instance()->forcePeace(_this);

	activateMovementEvent();
}

void CreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {

	/*menuResponse->addRadialMenuItem(205, 1, "@pet/pet_menu:menu_enter_exit");
	menuResponse->addRadialMenuItem(61, 3, "");

	if (checkInRangeGarage() && !isDestroyed())
		menuResponse->addRadialMenuItem(62, 3, "Repair");*/

	String skillBox = "outdoors_scout_novice";

	if (player->isInRange(_this, 10.0f)
			&& !player->isInCombat() && player->hasSkillBox(skillBox)
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

int CreatureImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {

	if(selectedID == 112 || selectedID == 234 || selectedID == 235 || selectedID == 236)
		harvest(player, selectedID);

	return 0;
}

void CreatureImplementation::harvest(PlayerCreature* player, byte selectedID) {
	if (zone == NULL)
		return;

	ManagedReference<ResourceManager*> resourceManager = zone->getZoneServer()->getResourceManager();
	String restype = "";
	int quantity = 0;

	if (selectedID == 112) {
		int type = System::random(2);

		switch (type) {
		case 0:
			restype = getMeatType();
			quantity = getMeatMax();
			break;
		case 1:
			restype = getHideType();
			quantity = getHideMax();
			break;
		case 2:
			restype = getBoneType();
			quantity = getBoneMax();
			break;
		default:
			restype = getHideType();
			quantity = getHideMax();
			break;
		}
	}

	if (selectedID == 234) {
		restype = getMeatType();
		quantity = getMeatMax();
	}

	if (selectedID == 235) {
		restype = getHideType();
		quantity = getHideMax();
	}

	if (selectedID == 236) {
		restype = getBoneType();
		quantity = getBoneMax();
	}

	int quantityExtracted = int(quantity * float(player->getSkillMod("creature_harvesting") / 100.0f));

	ManagedReference<ResourceSpawn*> resourceSpawn = resourceManager->getCurrentSpawn(restype, player->getZone()->getZoneID());

	if(resourceSpawn == NULL) {
		player->sendSystemMessage("Error: Server cannot locate a current spawn of " + restype);
		return;
	}

	float density = resourceSpawn->getDensityAt(player->getZone()->getZoneID(), player->getPositionX(), player->getPositionY());

	String creatureHealth = "";

	if(density > 0.80f) {
		quantityExtracted = int(quantityExtracted * 1.25f);
		creatureHealth = "creature_quality_fat";
	} else if(density > 0.60f) {
		quantityExtracted = int(quantityExtracted * 1.00f);
		creatureHealth = "creature_quality_medium";
	} else if(density > 0.40f) {
		quantityExtracted = int(quantityExtracted * 0.75f);
		creatureHealth = "creature_quality_skinny";
	} else {
		quantityExtracted = int(quantityExtracted * 0.50f);
		creatureHealth = "creature_quality_scrawny";
	}

	int baseAmount = quantityExtracted;

	float modifier = 1;

	if(player->isGrouped()) {

		modifier = player->getGroup()->getGroupHarvestModifier(player);

		quantityExtracted = (int)(quantityExtracted * modifier);
	}

	resourceManager->harvestResourceToPlayer(player, resourceSpawn, baseAmount);

	/// Send System Messages
	StringIdChatParameter harvestMessage("skl_use", creatureHealth);

	harvestMessage.setDI(quantityExtracted);
	harvestMessage.setTU(resourceSpawn->getFinalClass());

	ChatSystemMessage* sysMessage = new ChatSystemMessage(harvestMessage);
	player->sendMessage(sysMessage);

	/// Send bonus message
	if (modifier == 1.2f)
		player->sendSystemMessage("skl_use", "group_harvest_bonus");
	else if (modifier == 1.3f)
		player->sendSystemMessage("skl_use", "group_harvest_bonus_ranger");
	else if (modifier == 1.4f)
		player->sendSystemMessage("skl_use", "group_harvest_bonus_masterranger");

	/// Send group spam
	if(player->isGrouped()) {
		StringIdChatParameter bonusMessage("group", "notify_harvest_corpse");

		bonusMessage.setTU(player->getFirstName());
		bonusMessage.setDI(quantityExtracted);
		bonusMessage.setTO(resourceSpawn->getFinalClass());
		bonusMessage.setTT(getObjectNameStringIdFile(), getObjectNameStringIdName());

		sysMessage = new ChatSystemMessage(bonusMessage);
		player->getGroup()->broadcastMessage(player, sysMessage, false);
	}

	harvestList.removeElement(player);

	if(!hasLoot() && harvestList.size() == 0) {
		Reference<DespawnCreatureTask*> despawn = (DespawnCreatureTask*) getPendingTask("despawn");
		despawn->cancel();

		despawn->reschedule(1000);
	}
}

void CreatureImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* player) {
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

	createHarvestList();

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(_this);
	despawn->schedule(300000); /// 5 minutes
	addPendingTask("despawn", despawn);
}

void CreatureImplementation::createHarvestList() {
	PlayerCreature* tempPlayer;
	GroupObject* group;
	PlayerCreature* owner = (PlayerCreature*) getLootOwner();

	String skillBox = "outdoors_scout_novice";

	if (owner == NULL || !hasOrganics())
		return;

	if(owner->hasSkillBox(skillBox))
		harvestList.add(owner);

	if (owner->isGrouped()) {

		group = owner->getGroup();

		for (int i = 0; i < group->getGroupSize(); ++i) {

			SceneObject* groupMember = group->getGroupMember(i);

			if(groupMember != NULL && groupMember->isPlayerCreature()) {

				tempPlayer = (PlayerCreature*) groupMember;

				if (tempPlayer->hasSkillBox(skillBox))
					harvestList.add(tempPlayer);
			}
		}
	}
}


bool CreatureImplementation::hasOrganics() {
	return ((getHideMax() + getBoneMax() + getMeatMax()) > 0);
}

bool CreatureImplementation::canHarvestMe(CreatureObject* player) {
	if (!hasOrganics()){
		return false;
	}

	for (int i = 0; i < harvestList.size(); ++i){

		if (harvestList.get(i) == player){
			return true;
		}
	}

	return false;
}
