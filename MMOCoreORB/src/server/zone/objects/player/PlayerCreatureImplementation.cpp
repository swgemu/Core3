/*
 * PlayerCreatureImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerCreature.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/weather/WeatherManager.h"
#include "server/zone/packets/zone/unkByteFlag.h"
#include "server/zone/packets/zone/CmdStartScene.h"
#include "server/zone/packets/zone/CmdSceneReady.h"
#include "server/zone/packets/zone/ParametersMessage.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/player/BadgesResponseMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/ui/ExecuteConsoleCommand.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/creature/CreatureManager.h"

#include "server/chat/room/ChatRoom.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"

#include "events/PlayerDisconnectEvent.h"
#include "events/PlayerRecoveryEvent.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/professions/SkillBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/listbox/teachplayerlistbox/TeachPlayerListBox.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/professions/ProfessionManager.h"

#include "server/chat/StringIdChatParameter.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"

#include "badges/Badge.h"
#include "badges/Badges.h"

#include "PlayerObject.h"

void PlayerCreatureImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	disconnectEvent = NULL;
	recoveryEvent = NULL;
	owner = NULL;

	spawnedBlueFrog = false;

	persistentMessages.setNoDuplicateInsertPlan();
	duelList.setNoDuplicateInsertPlan();

	setLoggingName("PlayerCreature");

	/**
	 * Here we are loading the schematics based on the skills that the
	 * player has, we do this incase we change the items
	 * in the schematic group.
	 */
	ZoneServer* zoneServer = server->getZoneServer();
	ProfessionManager* professionManager = zoneServer->getProfessionManager();

	SkillBoxList* playerSkillBoxList = getSkillBoxList();

	if (getPlayerObject() != NULL) {
		for(int i = 0; i < playerSkillBoxList->size(); ++i) {
			SkillBox* skillBox = playerSkillBoxList->get(i);
			professionManager->awardDraftSchematics(skillBox, getPlayerObject(), false);
		}
	}

}

void PlayerCreatureImplementation::finalize() {
	if (server != NULL) {
		ManagedReference<ZoneServer*> zoneServer = server->getZoneServer();

		if (zoneServer != NULL)
			zoneServer->increaseTotalDeletedPlayers();
	}
}



void PlayerCreatureImplementation::notifyLoadFromDatabase() {
	CreatureObjectImplementation::notifyLoadFromDatabase();

	/*StackTrace::printStackTrace();

	if (parent != NULL) {
		info("loading from database with parent not null", true);
	}*/

	surveyTool = NULL;
	group = NULL;
	centeredBonus = 0;
	listenToID = 0;
	watchToID = 0;
	tradeContainer.clear();
	chatRooms.removeAll();
	setMood(getMoodID());

	if (getZone() != NULL && !isInQuadTree())
		setZone(NULL);

	if (owner == NULL)
		setLinkDead();

	clearCombatState(true);
	clearState(CreatureState::ALERT);

	if (posture == CreaturePosture::SKILLANIMATING)
		setPosture(CreaturePosture::UPRIGHT, true);

	if (performanceCounter != 0)
		setPerformanceCounter(0);

	if (instrumentID != 0)
		setInstrumentID(0);

	if (hasState(CreatureState::RIDINGMOUNT) && parent == NULL)
		clearState(CreatureState::RIDINGMOUNT);

	speedMultiplierModChanges.removeAll();
	serverLastMovementStamp.updateToCurrentTime();

	lastValidatedPosition.update(_this);
	movementCounter = 0;
	clientLastMovementStamp = 0;

	activateRecovery();
}

void PlayerCreatureImplementation::sendToOwner(bool doClose) {
	if (owner == NULL)
		return;

	owner->balancePacketCheckupTime();

	BaseMessage* byteFlag = new unkByteFlag();
	owner->sendMessage(byteFlag);

	BaseMessage* startScene = new CmdStartScene(_this);
	owner->sendMessage(startScene);

	BaseMessage* parameters = new ParametersMessage();
	owner->sendMessage(parameters);

	if (parent != NULL) {
		SceneObject* grandParent = getRootParent();

		grandParent->sendTo(_this, true);

		addNotifiedSentObject(grandParent);
		//notifiedSentObjects.put(grandParent);

		//info("parent not null", true);

		/*if (grandParent->isBuildingObject())
			((BuildingObject*)grandParent)->addNotifiedSentObject(_this);*/
	}

	ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();
	guildManager->sendBaselinesTo(_this);

	sendTo(_this, doClose);

	if (group != NULL)
		group->sendTo(_this, true);

	owner->resetPacketCheckupTime();
}


bool PlayerCreatureImplementation::isAttackableBy(CreatureObject* object) {
	if (object == _this)
		return false;

	if (isDead())
		return false;

	if (object->isPlayerCreature()) {
		PlayerCreature* playerCreature = (PlayerCreature*) object;

		if (duelList.contains(playerCreature) && playerCreature->requestedDuelTo(_this))
			return true;
	} else if (object->isAiAgent())
		return true;

	return false;
}



void PlayerCreatureImplementation::logout(bool doLock) {
	Locker _locker(_this);

	try {
		if (disconnectEvent == NULL) {
			info("creating disconnect event");

			disconnectEvent = new PlayerDisconnectEvent(_this);

			if (isLoggingOut()) {
				disconnectEvent->schedule(10);
			} else {
				disconnectEvent->schedule(1000);
				setLoggingOut();
			}
		}
	} catch (Exception& e) {
		error("unreported exception caught in PlayerCreatureImplementation::logout(boolean doLock)");
	}

}

void PlayerCreatureImplementation::doRecovery() {
	if (!isInQuadTree() && parent != NULL && parent->isCellObject() && owner == NULL) {
		SceneObject* building = parent->getParent();

		if (building != NULL && building->getZone() != NULL)
			insertToZone(building->getZone());
	}

	if (isLinkDead()) {
		if (logoutTimeStamp.isPast()) {
			info("unloading dead link player");

			unload();

			setOffline();

			if (owner != NULL)
				owner->closeConnection(false, true);

			return;
		} else {
			info("keeping dead linked player in game");
		}
	}

	activateHAMRegeneration();
	activateStateRecovery();

	PlayerObject* playerObject = getPlayerObject();

	if (playerObject != NULL && cooldownTimerMap->isPast("digestEvent")) {
		playerObject->doDigest();
		cooldownTimerMap->updateToCurrentAndAddMili("digestEvent", 18000);
	}

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	if (isInCombat() && getTargetID() != 0 && !isPeaced()
			&& (commandQueue.size() == 0) && nextAction.isPast()) {
		sendExecuteConsoleCommand("/attack");
		//enqueueCommand(0xA8FEF90A, 0, getTargetID(), ""); // Do default attack
	}

	activateRecovery();
}

void PlayerCreatureImplementation::activateRecovery() {
	if (recoveryEvent == NULL) {
		recoveryEvent = new PlayerRecoveryEvent(_this);

		recoveryEvent->schedule(3000);
	}
}

void PlayerCreatureImplementation::unloadSpawnedChildren() {
	SceneObject* datapad = getSlottedObject("datapad");

	if (datapad == NULL)
		return;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = (ControlDevice*) object.get();

			device->storeObject(_this);
		}
	}
}

void PlayerCreatureImplementation::updateToDatabase() {
	/*if (zone != NULL) {
		savedZoneID = zone->getZoneID();
	}

	if (parent != NULL) {
		savedParentID = parent->getObjectID();
	} *//*else
		savedParentID = 0;*/

	CreatureObjectImplementation::updateToDatabase();
}


void PlayerCreatureImplementation::unload() {
	info("unloading player");

	SceneObject* savedParent = NULL;

	PlayerObject* ghost = getPlayerObject();

	if (ghost != NULL) {
		ghost->setParent(_this);
		ghost->notifyOffline();
	}

	if (isRidingMount()) {
		executeObjectControllerAction(String("dismount").hashCode());
	}

	unloadSpawnedChildren();

	if (getZone() != NULL) {
		savedTerrainName = getZone()->getZoneName();

		if (isInQuadTree()) {
			if (parent != NULL) {
				savedParentID = parent->getObjectID();

				savedParent = parent;
			} else
				savedParentID = 0;

			removeFromZone();
		}
	}

	if (parent != NULL)
		parent->removeObject(_this);

	clearUpdateToDatabaseTask();
	//updateToDatabaseAllObjects(false);

	if (savedParent != NULL) {
		//savedParent->updateToDatabaseWithoutChildren();
	}

	clearCombatState(true);

	stopEntertaining();

	tradeContainer.clear();

	damageOverTimeList.removeAll();

	ManagedReference<ChatManager*> chatManager = getZoneServer()->getChatManager();

	if (chatManager != NULL)
		chatManager->removePlayer(getFirstName().toLowerCase());

	while (!chatRooms.isEmpty()) {
		ChatRoom* room = chatRooms.get(0);
		room->removePlayer(_this);
	}

	CombatManager::instance()->freeDuelList(_this);

	if (group != NULL)
		GroupManager::instance()->leaveGroup(group, _this);

	updateToDatabase();
	/*StringBuffer msg;
	msg << "remaining ref count: " << _this->getReferenceCount();
	info(msg.toString(), true);

	_this->printReferenceHolders();*/
}

void PlayerCreatureImplementation::reload(ZoneClientSession* client) {
	if (disconnectEvent != NULL) {
		disconnectEvent->cancel();
		disconnectEvent = NULL;
	}

	if (isLoggingIn()) {
		unlock();

		if (owner != NULL && owner != client)
			owner->disconnect();

		wlock();
	}

	setOnline();

	movementCounter = 0;

	//notifiedSentObjects.removeAll();

	if (isRidingMount() && parent == NULL) {
		clearState(CreatureState::RIDINGMOUNT);
	}

	insertToZone(getZone());
}

void PlayerCreatureImplementation::disconnect(bool closeClient, bool doLock) {
	Locker locker(_this);

	if (!isOnline()) {
		return;
	}

	if (/*isInCombat() && */!isLinkDead()) {
		info("link dead");

		setLinkDead();
	} else {
		info ("disconnecting player");

		unload();

		setOffline();
	}

	if (disconnectEvent != NULL)
		disconnectEvent = NULL;

	/*if (logoutEvent != NULL) {
			server->removeEvent(logoutEvent);
			delete logoutEvent;

			logoutEvent = NULL;
		}*/

	if (closeClient && owner != NULL)
		owner->closeConnection(false, true);

	owner = NULL;


}

void PlayerCreatureImplementation::setCombatState() {
	CreatureObjectImplementation::setCombatState();

	if (tradeContainer.isTryingToTrade()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();
		playerManager->handleAbortTradeMessage(_this, false);
	}
}

String PlayerCreatureImplementation::getFirstName() {
	UnicodeString fullName = objectName.getCustomString();

    int idx = fullName.indexOf(' ');

    if (idx != -1) {
    	return fullName.subString(0, idx).toString();
    } else {
    	return fullName.toString();
    }
}

String PlayerCreatureImplementation::getLastName() {
	UnicodeString lastName;

	UnicodeString fullName = objectName.getCustomString();
	UnicodeTokenizer tokenizer(fullName);

	if (tokenizer.hasMoreTokens())
		tokenizer.shiftTokens(1);

	if (tokenizer.hasMoreTokens())
		tokenizer.getUnicodeToken(lastName);

	return lastName.toString();
}

void PlayerCreatureImplementation::setLinkDead() {
	onlineStatus = LINKDEAD;

	logoutTimeStamp.updateToCurrentTime();
	logoutTimeStamp.addMiliTime(30000);

	PlayerObject* playerObject = (PlayerObject*) getSlottedObject("ghost");

	if (playerObject != NULL)
		playerObject->setCharacterBit(PlayerObjectImplementation::LD, true);

	activateRecovery();
}

void PlayerCreatureImplementation::setOnline() {
	onlineStatus = ONLINE;

	PlayerObject* playerObject = (PlayerObject*) getSlottedObject("ghost");

	if (playerObject != NULL)
		playerObject->clearCharacterBit(PlayerObjectImplementation::LD, true);

	doRecovery();
}

void PlayerCreatureImplementation::sendMessage(BasePacket* msg) {
	if (owner == NULL) {
		delete msg;
		return;
	} else {
		owner->sendMessage(msg);
	}
}

uint32 PlayerCreatureImplementation::getNewSuiBoxID(uint32 type) {
	return (++suiBoxNextID << 16) + (uint16)type;
}

void PlayerCreatureImplementation::sendBadgesResponseTo(PlayerCreature* player) {
	BaseMessage* msg = new BadgesResponseMessage(_this, &badges);
	player->sendMessage(msg);
}

void PlayerCreatureImplementation::notifySceneReady() {
	teleporting = false;

	BaseMessage* msg = new CmdSceneReady();
	sendMessage(msg);

	PlayerObject* playerObject = (PlayerObject*) getSlottedObject("ghost");

	if (playerObject == NULL)
		return;

	creatureBuffs.sendTo(_this);

	if (guild != NULL) {
		ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

		if (guildChat == NULL)
			return;

		guildChat->sendTo(_this);
		guildChat->addPlayer(_this);
	}

	playerObject->sendFriendLists();

	ManagedReference<WeatherManager*> weatherManager = getZone()->getPlanetManager()->getWeatherManager();
	weatherManager->sendWeatherPacket(_this);

	if (isDead()) {
		//If the player is dead, see if they already have a clone box. If so, resend it.
		ManagedReference<SuiBox*> cloneBox = getSuiBoxFromWindowType(SuiWindowType::CLONE_REQUEST);

		if (cloneBox != NULL) {
			cloneBox->clearOptions();
			sendMessage(cloneBox->generateMessage());
		} else {
			//Otherwise, send them a new one.
			server->getPlayerManager()->sendActivateCloneRequest(_this);
		}
	}
}

void PlayerCreatureImplementation::removeSuiBox(unsigned int boxID, bool closeWindowToClient) {
	if (closeWindowToClient == true) {
		SuiBox* sui = suiBoxes.get(boxID);

		if (sui != NULL) {
			sendMessage(sui->generateCloseMessage());
		}
	}

	suiBoxes.drop(boxID);
}

void PlayerCreatureImplementation::removeSuiBoxType(unsigned int windowType) {
	SuiBox* sui = NULL;

	if ((sui = getSuiBoxFromWindowType(windowType)) != NULL) {
		removeSuiBox(sui->getBoxID(), true);
	}
}


void PlayerCreatureImplementation::resetFirstIncapacitationTime() {
	if (!isFirstIncapacitation())
		resetIncapacitationCounter();

	cooldownTimerMap->updateToCurrentAndAddMili("firstIncapacitationTime", 900000);
}

bool PlayerCreatureImplementation::isFirstIncapacitationExpired() {
	return cooldownTimerMap->isPast("firstIncapacitationTime");
}

int PlayerCreatureImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();

	playerManager->notifyDestruction(attacker, _this, condition);

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int PlayerCreatureImplementation::notifyObjectInserted(SceneObject* object) {
	if (object->isArmorObject()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();

		playerManager->applyEncumbrancies(_this, (ArmorObject*)object);

		WearableObject* armor = (WearableObject*) object;
		armor->setAttachmentMods(_this);

	} else if (object->isWearableObject()) {
		WearableObject* clothing = (WearableObject*) object;
		clothing->setAttachmentMods(_this);

	}

	if (object->isInstrument() && isEntertaining())
		stopEntertaining();

	return CreatureObjectImplementation::notifyObjectInserted(object);
}


/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int PlayerCreatureImplementation::notifyObjectRemoved(SceneObject* object) {
	if (object->isArmorObject()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();

		playerManager->removeEncumbrancies(_this, (ArmorObject*)object);

		WearableObject* armor = (WearableObject*) object;
		armor->setAttachmentMods(_this, true);

	} else if (object->isWearableObject()) {
		WearableObject* clothing = (WearableObject*) object;
		clothing->setAttachmentMods(_this, true);
	}

	if (object->isInstrument()) {
		if (isPlayingMusic())
			stopEntertaining();
	}

	return CreatureObjectImplementation::notifyObjectRemoved(object);
}

void PlayerCreatureImplementation::awardBadge(uint32 badge) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();
	playerManager->awardBadge(_this, badge);
}

void PlayerCreatureImplementation::sendExecuteConsoleCommand(const String& command) {
	BaseMessage* msg = new ExecuteConsoleCommand(command);
	sendMessage(msg);
}

WaypointObject* PlayerCreatureImplementation::getSurveyWaypoint() {
	PlayerObject* ghost = getPlayerObject();

	WaypointList* list = ghost->getWaypointList();

	uint64 wpid = list->getWaypointBySpecialType(WaypointObject::SPECIALTYPE_RESOURCE);

	if (wpid != 0) {
		return list->get(wpid);
	}

	return NULL;
}

void PlayerCreatureImplementation::notifySelfPositionUpdate() {
	CreatureObjectImplementation::notifySelfPositionUpdate();

	if (getZone() == NULL)
		return;

	/*if (activeAreas.size() != 0) {
		info(String::valueOf(activeAreas.size()) + " areas", true);
	}*/

	if (getActiveAreas()->size() == 0 && inRangeObjectCount() < 20) {
		if ((parent != NULL && !parent->isCellObject()) || parent == NULL) {
			getZone()->getCreatureManager()->spawnRandomCreaturesAround(_this);
		}
	}
}
