/*
 * PlayerCreatureImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerCreature.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/packets/zone/unkByteFlag.h"
#include "server/zone/packets/zone/CmdStartScene.h"
#include "server/zone/packets/zone/CmdSceneReady.h"
#include "server/zone/packets/zone/ParametersMessage.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/player/BadgesResponseMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

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
#include "server/zone/objects/player/Races.h"

#include "server/zone/objects/scene/variables/ParameterizedStringId.h"

#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/ZoneServer.h"

#include "badges/Badge.h"
#include "badges/Badges.h"

#include "PlayerObject.h"

void PlayerCreatureImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	disconnectEvent = NULL;
	recoveryEvent = NULL;
	owner = NULL;

	persistentMessages.setNoDuplicateInsertPlan();
	duelList.setNoDuplicateInsertPlan();

	setLoggingName("PlayerCreature");
}

void PlayerCreatureImplementation::finalize() {

}

void PlayerCreatureImplementation::notifyLoadFromDatabase() {
	CreatureObjectImplementation::notifyLoadFromDatabase();

	surveyTool = NULL;
	centeredBonus = 0;
	tradeContainer.clear();

	if (zone != NULL && !isInQuadTree())
		zone = NULL;

	if (owner == NULL)
		setLinkDead();

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

		info("parent not null", true);

		/*if (grandParent->isBuildingObject())
			((BuildingObject*)grandParent)->addNotifiedSentObject(_this);*/
	} else {
		info("parent null", true);
		sendTo(_this, doClose);
	}

	if (group != NULL)
		group->sendTo(_this, true);

	creatureBuffs.sendTo(_this);

	owner->resetPacketCheckupTime();
}

void PlayerCreatureImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) entry)->_getStub());

	if (scno == _this)
		return;

	//TODO: fix cell movement for this to not happen
	/*SceneObject* grandParent = getRootParent();

	if (parent != NULL) {
		if (grandParent == scno) { // we already should have sent our grandParent to owner

			if (grandParent->isBuildingObject())
				((BuildingObject*)grandParent)->addNotifiedSentObject(_this);

			return;
		}
	}

	if (scno->getParent() != NULL) {
		//check the parent if its building
		//check if the building has me as notified
		//if it has me than send the object without the buio
		//if it hasnt me than dont send me and wait for the building to be sent
		//TODO: check if we need this for every object or only for buildings
		SceneObject* scnoGrandParent = scno->getRootParent();

		if (scnoGrandParent->isBuildingObject()) {
			BuildingObject* building = (BuildingObject*)scnoGrandParent;

			if (!building->hasNotifiedSentObject(_this))
				return;
		} else // we wait for the Objects parent to get sent
			return;
	}

	if (scno->isBuildingObject())
		((BuildingObject*)scno)->addNotifiedSentObject(_this);*/

	scno->sendTo(_this, true);
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

void PlayerCreatureImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) entry)->_getStub());

	if (scno == _this)
		return;

	scno->sendDestroyTo(_this);
}

void PlayerCreatureImplementation::logout(bool doLock) {
	wlock(doLock);

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
	} catch (...) {
		error("unreported exception caught in PlayerCreatureImplementation::logout(boolean doLock)");
	}

	unlock(doLock);
}

void PlayerCreatureImplementation::doRecovery() {
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

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	if (isInCombat() && getTargetID() != 0 && !isPeaced()
			&& (commandQueue.size() == 0)) {
		enqueueCommand(0xA8FEF90A, 0, getTargetID(), ""); // Do default attack
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
		SceneObject* object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = (ControlDevice*) object;

			device->storeObject(_this);
		}
	}
}

void PlayerCreatureImplementation::unload() {
	info("unloading player", true);

	SceneObject* savedParent = NULL;

	PlayerObject* ghost = getPlayerObject();

	if (ghost != NULL)
		ghost->notifyOffline();

	if (isRidingMount()) {
		executeObjectControllerAction(String("dismount").hashCode());
	}

	unloadSpawnedChildren();

	if (parent != NULL) {
		savedParentID = parent->getObjectID();

		savedParent = parent;
	} else
		savedParentID = 0;

	if (zone != NULL) {
		savedZoneID = zone->getZoneID();

		if (isInQuadTree()) {
			removeFromZone();
		}
	}

	clearUpdateToDatabaseTask();
	updateToDatabaseAllObjects(false);

	if (savedParent != NULL) {
		//savedParent->updateToDatabaseWithoutChildren();
	}

	clearCombatState(true);

	tradeContainer.clear();

	getZoneServer()->getChatManager()->removePlayer(getFirstName().toLowerCase());

	CombatManager::instance()->freeDuelList(_this);

	if (group != NULL)
		GroupManager::instance()->leaveGroup(group, _this);

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

	insertToZone(zone);
}

void PlayerCreatureImplementation::disconnect(bool closeClient, bool doLock) {
	try {
		wlock(doLock);

		if (!isOnline()) {
			unlock(doLock);
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

		unlock();
	} catch (...) {
		unlock();
	}
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

void PlayerCreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {

	if (group != NULL) {
		if (group->hasMember(player))
			menuResponse->addRadialMenuItem(51, 51, "@sui:teach"); //TODO:find the stf
	}

}

int PlayerCreatureImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {

	switch(selectedID) {
	case 51:

			if(isTeachingOrLearning() || player->isTeachingOrLearning()) {
				player->sendSystemMessage("teaching", "teaching_failed");
				return 1;
			}

			player->setTeachingOrLearning(true);

			TeachPlayerListBox* teachPlayerListBox = new TeachPlayerListBox(player);
			teachPlayerListBox->setCancelButton(true, "");

			bool completed = teachPlayerListBox->generateSkillList(player, _this);

			if(!completed)
				player->setTeachingOrLearning(false);

		break;
	}

	return 0;
}

void PlayerCreatureImplementation::insertToBuilding(BuildingObject * building) {
	SceneObjectImplementation::insertToBuilding(building);
	building->onEnter(_this);
}

void PlayerCreatureImplementation::removeFromBuilding(BuildingObject * building) {
	SceneObjectImplementation::removeFromBuilding(building);
	building->onExit(_this);
}

uint32 PlayerCreatureImplementation::getNewSuiBoxID(uint32 type) {
	return (++suiBoxNextID << 16) + (uint16)type;
}

void PlayerCreatureImplementation::sendBadgesResponseTo(PlayerCreature* player) {
	BaseMessage* msg = new BadgesResponseMessage(_this, &badges);
	player->sendMessage(msg);
}

void PlayerCreatureImplementation::notifySceneReady() {
	BaseMessage* msg = new CmdSceneReady();
	sendMessage(msg);

	PlayerObject* playerObject = (PlayerObject*) getSlottedObject("ghost");
	if (playerObject == NULL)
		return;

	playerObject->sendFriendLists();
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

	cooldownTimerMap.updateToCurrentAndAddMili("firstIncapacitationTime", 900000);
}

bool PlayerCreatureImplementation::isFirstIncapacitationExpired() {
	return cooldownTimerMap.isPast("firstIncapacitationTime");
}

int PlayerCreatureImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();

	playerManager->notifyDestruction(attacker, _this, condition);

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

int PlayerCreatureImplementation::canAddObject(SceneObject* object, String& errorDescription) {
	if (object->isArmorObject()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();

		if (!playerManager->checkEncumbrancies(_this, (ArmorObject*)object))
			return TransferErrorCode::NOTENOUGHENCUMBRANCE;
	}

	return CreatureObjectImplementation::canAddObject(object, errorDescription);
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int PlayerCreatureImplementation::notifyObjectInserted(SceneObject* object) {
	if (object->isArmorObject()) {
		PlayerManager* playerManager = getZoneServer()->getPlayerManager();

		playerManager->applyEncumbrancies(_this, (ArmorObject*)object);
	}

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
	}

	return CreatureObjectImplementation::notifyObjectRemoved(object);
}

void PlayerCreatureImplementation::awardBadge(uint32 badge) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();
	playerManager->awardBadge(_this, badge);
}

WaypointObject* PlayerCreatureImplementation::getSurveyWaypoint() {
	PlayerObject* ghost = getPlayerObject();

	WaypointList* list = ghost->getWaypointList();

	for(int i = 0; i < list->size(); ++i) {
		ManagedReference<WaypointObject* > waypoint = (WaypointObject*) list->getValueAt(i);

		if(waypoint == NULL)
			continue;

		String name = waypoint->getCustomName().toString();
		if(name == "Resource Survey")
			return waypoint;
	}
	return NULL;
}
