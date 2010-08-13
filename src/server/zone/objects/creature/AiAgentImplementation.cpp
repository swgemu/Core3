/*
 * AiAgentImplementation.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "AiAgent.h"

#include "events/AiThinkEvent.h"
#include "events/AiMoveEvent.h"
#include "events/RespawnCreatureTask.h"
#include "events/DespawnCreatureOnPlayerDissappear.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/Zone.h"
#include "PatrolPoint.h"


void AiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);

	pvpStatusBitmask = CreatureFlag::ATTACKABLE;

	if (templateData->isNonPlayerCreatureObjectTemplate())
		npcTemplate = (NonPlayerCreatureObjectTemplate*) templateData;
	/*else {
		StringBuffer msg;
		msg << "creating " << TemplateManager::instance()->getTemplateFile(serverObjectCRC);
		msg << " with wrong template type object";
		error(msg.toString());
	}*/
}

void AiAgentImplementation::initializeTransientMembers() {
	SharedObjectTemplate* templ = TemplateManager::instance()->getTemplate(serverObjectCRC);

	if (templ != NULL && templ->isNonPlayerCreatureObjectTemplate()) {
		npcTemplate = (NonPlayerCreatureObjectTemplate*) templ;
	}
}

void AiAgentImplementation::doRecovery() {
	if (isDead() || zone == NULL)
		return;

	activateHAMRegeneration();
	activateStateRecovery();
	activatePostureRecovery();

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	if (isInCombat() && defenderList.size() > 0) {
		SceneObject* targetToAttack = defenderList.get(0);

		if (!tryRetreat() && targetToAttack->isCreatureObject()) {
			CreatureObject* creo = (CreatureObject*) targetToAttack;

			if (creo->isPeaced() || !creo->isInRange(_this, 128) || !creo->isAttackableBy(_this)) {
				removeDefender(creo);
				setFollowObject(NULL);
				//CombatManager::instance()->attemptPeace(_this);
			} else {
				setTargetID(creo->getObjectID(), true);

				setFollowObject(creo);

				checkNewAngle();

				if (commandQueue.size() == 0 && weapon != NULL)
					enqueueCommand(0xA8FEF90A, 0, creo->getObjectID(), ""); // Do default attack
			}
		}
	}

	activateRecovery();
}

void AiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == NULL) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this);
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

bool AiAgentImplementation::tryRetreat() {
	try {
		if (homeLocation.getPositionX() == 0 && homeLocation.getPositionY() == 0 && homeLocation.getPositionZ() == 0)
			return false;

		if (lastSuccessfulCombatAction.miliDifference() <= 30000) {
			return false;
		} else if (homeLocation.isInRange(_this, 100))
			return false;

		setFollowObject(NULL);

		homeLocation.setReached(false);

		damageMap.removeAll();

		patrolPoints.removeAll();
		patrolPoints.add(homeLocation);

		CombatManager::instance()->forcePeace(_this);

		activateMovementEvent();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in AiAgentImplementation::tryRetreat()");
	}

	return true;
}

void AiAgentImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {

}

void AiAgentImplementation::setDefender(SceneObject* defender) {
	CreatureObjectImplementation::setDefender(defender);

	//followObject = defender;

	activateRecovery();
}

void AiAgentImplementation::addDefender(SceneObject* defender) {
	if (defenderList.size() == 0)
		showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0, 0);

	CreatureObjectImplementation::addDefender(defender);

	activateRecovery();
}

void AiAgentImplementation::removeDefender(SceneObject* defender) {
	CreatureObjectImplementation::removeDefender(defender);

	if (followObject == defender)
		setFollowObject(NULL);
}

/**
 * Cleares the combat state
 * @pre { this object is locked }
 * @post { this object is locked, this object is not in a combat state }
 * @param clearDefenders if true the defender vector willl be emptied
 */
void AiAgentImplementation::clearCombatState(bool clearDefenders) {
	CreatureObjectImplementation::clearCombatState(clearDefenders);

	damageMap.removeAll();

	setFollowObject(NULL);
}

void AiAgentImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) entry)->_getStub());

	if (scno == _this)
		return;

	if (scno->isPlayerCreature())
		++numberOfPlayersInRange;
}

void AiAgentImplementation::clearDespawnEvent() {
	despawnEvent = NULL;
}

void AiAgentImplementation::respawn(Zone* zone, int level) {
	if (this->zone != NULL)
		return;

	setLevel(level);

	initializePosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());

	SceneObject* cell = homeLocation.getCell();

	Locker zoneLocker(zone);

	if (cell != NULL)
		cell->addObject(_this, -1);

	insertToZone(zone);
}

void AiAgentImplementation::notifyDespawn(Zone* zone) {
	if (respawnTimer == 0)
		return;

	if (npcTemplate == NULL)
		return;

	Reference<Task*> task = new RespawnCreatureTask(_this, zone, level);

	loadTemplateData(npcTemplate);
	stateBitmask = 0;
	posture = CreaturePosture::UPRIGHT;
	shockWounds = 0;
	damageMap.removeAll();

	task->schedule(respawnTimer * 1000);
}

void AiAgentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) entry)->_getStub());

	if (scno == _this)
		return;

	if (scno->isPlayerCreature()) {
		if ((--numberOfPlayersInRange <= 0)  && (despawnEvent == NULL)) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this);
			despawnEvent->schedule(30000);
		}
	}
}

void AiAgentImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new AiThinkEvent(_this);

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void AiAgentImplementation::activatePostureRecovery() {
	if (isProne() || isKnockedDown() || isKneeling())
		executeObjectControllerAction(0xA8A25C79); // stand
}

void AiAgentImplementation::updateCurrentPosition(PatrolPoint* pos) {
	PatrolPoint* nextPosition = pos;

	setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(),
		nextPosition->getPositionY());

	SceneObject* cell = nextPosition->getCell();

	/*StringBuffer reachedPosition;
	reachedPosition << "(" << positionX << ", " << positionY << ")";
	info("reached " + reachedPosition.toString(), true);*/

	if (cell != NULL)
		updateZoneWithParent(cell, false, false);
	else
		updateZone(false, false);
}


void AiAgentImplementation::checkNewAngle() {
	if (followObject == NULL)
		return;

	Vector3 thisWorldPos = getWorldPosition();
	Vector3 targetWorldPos = followObject->getWorldPosition();

	float directionangle = atan2(targetWorldPos.getX() - thisWorldPos.getX(), targetWorldPos.getY() - thisWorldPos.getY());

	/*StringBuffer msg;
	msg << "direction angle " << String::valueOf(directionangle) << " getRadians " << direction.getRadians();

	info(msg.toString(), true);*/

	if (directionangle < 0) {
		float a = M_PI + directionangle;
		directionangle = M_PI + a;
	}

	float err = fabs(directionangle - direction.getRadians());

	if (err < 0.05) {
		//info("not updating " + String::valueOf(directionangle), true);
		return;
	}

	direction.setHeadingDirection(directionangle);

	if (!nextStepPosition.isReached()) {
		broadcastNextPositionUpdate(&nextStepPosition);
	} else {
		++movementCounter;

		if (parent != NULL && parent->isCellObject())
			updateZoneWithParent(parent, true, true);
		else
			updateZone(true, true);
	}
}

void AiAgentImplementation::doMovement() {
	//info("doMovement", true);
	if (isDead() || zone == NULL)
		return;

	if (currentSpeed != 0) {
		updateCurrentPosition(&nextStepPosition);
		nextStepPosition.setReached(true);

		if (isRetreating()) {
			if (nextStepPosition.isInRange(&homeLocation, 0.5))
				homeLocation.setReached(true);
		}

	}

	if (patrolPoints.size() == 0) {
		if (followObject != NULL) {
			setNextPosition(followObject->getPositionX(), followObject->getPositionZ(), followObject->getPositionY(), followObject->getParent());
		} else {
			currentSpeed = 0;
			return;
		}
	}

	float maxDistance = getWeapon()->getMaxRange();

	if (isRetreating())
		maxDistance = 0;

	float dist = 0;

	float dx, dy;
	ManagedReference<SceneObject*> cellObject;

	bool found = false;

	Vector3 thisWorldPos = getWorldPosition();
	PatrolPoint* nextPosition = NULL;

	while (!found && patrolPoints.size() != 0) {
		nextPosition = &patrolPoints.elementAt(0);

		cellObject = nextPosition->getCell();

		Vector3 nextPosWorldPos = nextPosition->getWorldPosition();

		dx = nextPosWorldPos.getX() - thisWorldPos.getX();
		dy = nextPosWorldPos.getY() - thisWorldPos.getY();

		dist = sqrt(dx * dx + dy * dy);

		if (dist < maxDistance && cellObject == parent) {
			patrolPoints.remove(0);

			nextPosition = NULL;
		} else
			found = true;
	}

	if (!found) {
		currentSpeed = 0;
		//info("not found in doMovement", true);

		if (followObject != NULL)
			activateMovementEvent();

		return;
	}

	if (!isStanding()) {
		activateMovementEvent();
		return;
	}

	float newPositionX, newPositionZ, newPositionY;

	float updateTicks = float(UPDATEMOVEMENTINTERVAL) / 1000.f;

	//info("runSpeed: " + String::valueOf(runSpeed), true);

	float newSpeed = runSpeed * updateTicks;

	newPositionX = thisWorldPos.getX() + (newSpeed * (dx / dist));
	newPositionY = thisWorldPos.getY() + (newSpeed * (dy / dist));
	newPositionZ = zone->getHeight(newPositionX, newPositionY);

	float directionangle = atan2(newPositionX - thisWorldPos.getX(), newPositionY - thisWorldPos.getY());

	direction.setHeadingDirection(directionangle);

	currentSpeed = runSpeed;

	if ((parent != NULL && parent != cellObject) || (cellObject != NULL && dist <= currentSpeed)) {
		nextStepPosition = *nextPosition;
	} else {
		nextStepPosition.setPosition(newPositionX, newPositionZ, newPositionY);
		nextStepPosition.setCell(NULL);
	}

	nextStepPosition.setReached(false);

	broadcastNextPositionUpdate(&nextStepPosition);

	activateMovementEvent();
}

void AiAgentImplementation::activateMovementEvent() {
	if (moveEvent == NULL) {
		moveEvent = new AiMoveEvent(_this);

		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
	}

	if (!moveEvent->isScheduled())
		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
}

void AiAgentImplementation::setNextPosition(float x, float z, float y, SceneObject* cell) {
	PatrolPoint point(x, z, y, cell);

	if (patrolPoints.size() == 0)
		patrolPoints.add(point);
	else
		patrolPoints.setElementAt(0, point);
}

void AiAgentImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BasePacket* msg = NULL;
	++movementCounter;

	if (point == NULL) {
		if (parent != NULL)
			msg = new UpdateTransformWithParentMessage(_this);
		else
			msg = new UpdateTransformMessage(_this);
	} else {
		if (point->getCell() != NULL)
			msg = new LightUpdateTransformWithParentMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		else
			msg = new LightUpdateTransformMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	broadcastMessage(msg, false);
}

int AiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	if (zone != NULL) {
		CreatureManager* creatureManager = zone->getCreatureManager();

		creatureManager->notifyDestruction(attacker, _this, condition);
	}

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

bool AiAgentImplementation::hasOrganics() {
	return ((getHideMax() + getBoneMax() + getMeatMax()) > 0);
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	activateRecovery();

	if (attacker->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) attacker;

		if (damage > 0) {
			damageMap.addDamage(player, damage);

			if (System::random(5) == 1) {
				setFollowObject(player);
				setDefender(player);
			}
		}
	}

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}


void AiAgentImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* player) {
	int creaKnowledge = player->getSkillMod("creature_knowledge");

	if (isDead()) {
		return;
	}

	if (getArmor() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmor() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmor() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmor() == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (getKinetic() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				"100%");

	if (getEnergy() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				"100%");

	if (getElectricity() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				"100%");

	if (getStun() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				"100%");

	if (getBlast() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				"100%");

	if (getHeat() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat", "100%");

	if (getCold() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold", "100%");

	if (getAcid() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid", "100%");

	if (getLightSaber() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint", "100%");

	if (getKinetic() > 0 && getKinetic() < 100) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() < 100) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() < 100) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}

	if (getStun() > 0 && getStun() < 100) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}

	if (getBlast() > 0 && getBlast() < 100) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}

	if (getHeat() > 0 && getHeat() < 100) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}

	if (getCold() > 0 && getCold() < 100) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}

	if (getAcid() > 0 && getAcid() < 100) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() < 100) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	if (getKinetic() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	if (getHideType().isEmpty() && getBoneType().isEmpty()
			&& getMeatType().isEmpty()) {
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
		if (!getHideType().isEmpty())
			alm->insertAttribute("res_hide", getHideType());//.subString(4).replaceAll("_"," "));
		else
			alm->insertAttribute("res_hide", "---");
		if (!getBoneType().isEmpty())
			alm->insertAttribute("res_bone", getBoneType());//.subString(5).replaceAll("_"," "));
		else
			alm->insertAttribute("res_bone", "---");
		if (!getMeatType().isEmpty())
			alm->insertAttribute("res_meat", getMeatType());//.subString(4).replaceAll("_"," "));
		else
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
		alm->insertAttribute("challenge_level", (int) getLevel());

	int skillNum = skillCommands.size();

	if (creaKnowledge >= 70) {
		if (skillNum >= 1)
			alm->insertAttribute("pet_command_18", skillCommands.get(0));
		else
			alm->insertAttribute("pet_command_18", "---");
	}

	if (creaKnowledge >= 80) {
		if (skillNum >= 2)
			alm->insertAttribute("pet_command_19", skillCommands.get(1));
		else
			alm->insertAttribute("pet_command_19", "---");
	}

	if (creaKnowledge >= 90)
		alm->insertAttribute("basetohit", 0.89f);

	if (creaKnowledge >= 100) {
		StringBuffer damageMsg;
		//damageMsg << creatureWeaponMinDamage << "-" << creatureWeaponMaxDamage;
		alm->insertAttribute("cat_wpn_damage", damageMsg.toString());
	}

}


void AiAgentImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature())
		return;

	PlayerCreature* playerCreature = (PlayerCreature*) player;

	//player->setLastNpcConvStr(("npc_" + getFu().toString()));
	playerCreature->setLastNpcConvMessStr("0,init");

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	String responseFile, responseAttitude;

	if (responseFile == "") {
		if (isImperial()) {
			responseFile = "npc_reaction/stormtrooper";
		} else if (isRebel()) {
			responseFile = "npc_reaction/military";
		} else {
			short file = System::random(2);
			if (file == 0)
				responseFile = "npc_reaction/fancy";
			else if (file == 1)
				responseFile = "npc_reaction/slang";
			else
				responseFile = "npc_reaction/townperson";
		}
	}

	if (responseAttitude == "") {
		short type = System::random(2);
		if (type == 0)
			responseAttitude = "mean";
		else if (type == 1)
			responseAttitude = "mid";
		else
			responseAttitude = "nice";
	}

	StringBuffer convoChoice;
	convoChoice << "hi_" <<  responseAttitude << "_" << (System::random(15) + 1);

	NpcConversationMessage* initial = new NpcConversationMessage(
			playerCreature, responseFile, convoChoice.toString());
	player->sendMessage(initial);

	// Parse and send the options:
	StringList* slist = new StringList(playerCreature);

	String test = "I'm looking for work";
	slist->insertOption(test);

	player->sendMessage(slist);

	playerCreature->setLastNpcConvMessStr("chitchat");
}

void AiAgentImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return;

	PlayerCreature* player = (PlayerCreature*) obj;

	String chk = player->getLastNpcConvMessStr();

	if (chk != "chitchat") {
		return;
	}

	UnicodeString saying = "";
	switch(System::random(5)) {
	case 0:
		saying = "Why the heck would you want to work when welfare is free.";
		break;
	case 1:
		saying = "Pfft, work in this economy?  I'm waiting for the government to bail me out.";
		break;
	case 2:
		saying = "Check the missions terminals, they are overflowing with work.";
		break;
	case 3:
		saying = "Huh, work?  Whats that?";
		break;
	case 4:
		saying = "Did you check the mission terminals?";
		break;
	case 5:
		saying = "Me too.";
		break;
	}

	NpcConversationMessage* response = new NpcConversationMessage(
			player, saying);
	player->sendMessage(response);

	// Parse and send the options:
	StringList* slist = new StringList(player);
	player->sendMessage(slist);
}
