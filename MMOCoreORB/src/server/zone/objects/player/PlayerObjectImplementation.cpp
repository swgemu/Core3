/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/chat/ChatManager.h"
#include "server/chat/room/ChatRoom.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/packets/player/PlayerObjectMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage8.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"
#include "server/zone/packets/player/FriendListMessage.h"
#include "server/zone/packets/player/IgnoreListMessage.h"
#include "server/zone/packets/player/AddFriendInitiateMessage.h"
#include "server/zone/packets/player/AddFriendMessage.h"
#include "server/zone/packets/player/AddIgnoreMessage.h"
#include "server/zone/packets/player/FriendStatusChangeMessage.h"
#include "server/zone/packets/player/PlayerObjectMessage6.h"
#include "server/zone/packets/player/PlayerObjectMessage8.h"
#include "server/zone/packets/player/PlayerObjectMessage9.h"
#include "server/zone/packets/zone/CmdSceneReady.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/player/variables/PlayerList.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "events/PlayerDisconnectEvent.h"
#include "events/PlayerRecoveryEvent.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/structure/events/StructureSetOwnerTask.h"
#include "badges/Badge.h"
#include "badges/Badges.h"
#include "server/zone/packets/player/BadgesResponseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/weather/WeatherManager.h"
#include "server/zone/objects/player/variables/Ability.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "FactionStatus.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/templates/intangible/SharedPlayerObjectTemplate.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/objects/player/events/StoreSpawnedChildrenTask.h"
#include "server/zone/objects/player/events/BountyHunterTefRemovalTask.h"
#include "server/zone/objects/player/events/RemoveSpouseTask.h"
#include "server/zone/objects/player/events/PvpTefRemovalTask.h"
#include "server/zone/managers/visibility/VisibilityManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "events/ForceRegenerationEvent.h"
#include "server/login/account/Account.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/managers/player/QuestInfo.h"
#include "server/zone/objects/player/events/ForceMeditateTask.h"

void PlayerObjectImplementation::initializeTransientMembers() {
	IntangibleObjectImplementation::initializeTransientMembers();

	foodFillingMax = 100;
	drinkFillingMax = 100;

	duelList.setNoDuplicateInsertPlan();

	setLoggingName("PlayerObject");
}

void PlayerObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	IntangibleObjectImplementation::loadTemplateData(templateData);

	SharedPlayerObjectTemplate* sply = dynamic_cast<SharedPlayerObjectTemplate*>(templateData);

	characterBitmask = 0;

	adminLevel = 0;

	forcePower = getForcePower();
	forcePowerMax = getForcePowerMax();
	forcePowerRegen = getForcePowerRegen();

	trainerZoneName = getTrainerZoneName();

	foodFilling = 0;
	foodFillingMax = 100;

	drinkFilling = 0;
	drinkFillingMax = 100;

	reactionFines = 0;

	jediState = getJediState();

	languageID = 0;

	experienceList.setNullValue(0);

	permissionGroups = *(sply->getPlayerDefaultGroupPermissions());
}

void PlayerObjectImplementation::notifyLoadFromDatabase() {
	IntangibleObjectImplementation::notifyLoadFromDatabase();

	chatRooms.removeAll();

	serverLastMovementStamp.updateToCurrentTime();

	lastValidatedPosition.update(getParent().get());

	clientLastMovementStamp = 0;
}

void PlayerObjectImplementation::unloadSpawnedChildren() {
	ManagedReference<SceneObject*> datapad = getParent().get()->getSlottedObject("datapad");
	ManagedReference<CreatureObject*> creo = dynamic_cast<CreatureObject*>(parent.get().get());

	if (datapad == NULL)
		return;

	Vector<ManagedReference<CreatureObject*> > childrenToStore;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = cast<ControlDevice*>( object.get());

			ManagedReference<CreatureObject*> child = cast<CreatureObject*>(device->getControlledObject());
			if (child != NULL)
				childrenToStore.add(child);
		}
	}

	StoreSpawnedChildrenTask* task = new StoreSpawnedChildrenTask(creo, childrenToStore);
	task->execute();
}


void PlayerObjectImplementation::unload() {
	info("unloading player");

	SceneObject* savedParent = NULL;

	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
	missionManager->deactivateMissions(creature);

	notifyOffline();

	if (creature->isRidingMount()) {
		creature->executeObjectControllerAction(STRING_HASHCODE("dismount"));
	}

	unloadSpawnedChildren();

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();
	playerManager->ejectPlayerFromBuilding(creature);

	ManagedReference<SceneObject*> creoParent = creature->getParent();

	if (creature->getZone() != NULL) {
		savedTerrainName = creature->getZone()->getZoneName();

		//if (creature->isInQuadTree()) {
		if (creoParent != NULL) {
			savedParentID = creoParent->getObjectID();

			savedParent = creoParent;
		} else
			savedParentID = 0;

		creature->destroyObjectFromWorld(true);
		//}
	}

	/*if (creoParent != NULL)
		creoParent->removeObject(creature);*/

	creature->clearUpdateToDatabaseTask();
	//updateToDatabaseAllObjects(false);

	if (savedParent != NULL) {
		//savedParent->updateToDatabaseWithoutChildren();
	}

	creature->clearCombatState(true);

	creature->stopEntertaining();

	ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer != NULL)
		creature->dropActiveSession(SessionFacadeType::TRADE);

	//creature->clearDots();

	ManagedReference<ChatManager*> chatManager = getZoneServer()->getChatManager();

	if (chatManager != NULL)
		chatManager->removePlayer(creature->getFirstName().toLowerCase());

	while (!chatRooms.isEmpty()) {
		ChatRoom* room = chatRooms.get(0);
		room->removePlayer(creature);
	}

	CombatManager::instance()->freeDuelList(creature);

	GroupObject* group = creature->getGroup();

	if (group != NULL)
		GroupManager::instance()->leaveGroup(group, creature);

	updateToDatabase();
	/*StringBuffer msg;
	msg << "remaining ref count: " << _this.getReferenceUnsafeStaticCast()->getReferenceCount();
	info(msg.toString(), true);

	_this.getReferenceUnsafeStaticCast()->printReferenceHolders();*/
}

void PlayerObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending player object baselines");

	BaseMessage* play3 = new PlayerObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(play6);

	if (player == parent.get().get()) {
		BaseMessage* play8 = new PlayerObjectMessage8(this);
		player->sendMessage(play8);

		BaseMessage* play9 = new PlayerObjectMessage9(this);
		player->sendMessage(play9);
	}
}

void PlayerObjectImplementation::notifySceneReady() {
	teleporting = false;
	onLoadScreen = false;

	BaseMessage* msg = new CmdSceneReady();
	sendMessage(msg);

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	creature->broadcastPvpStatusBitmask();

	creature->sendBuffsTo(creature);

	GuildObject* guild = creature->getGuildObject();

	if (guild != NULL) {
		ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

		if (guildChat == NULL)
			return;

		guildChat->sendTo(creature);
		guildChat->addPlayer(creature);
	}

	sendFriendLists();

	if (creature->isDead()) {
		//If the player is dead, see if they already have a clone box. If so, resend it.
		ManagedReference<SuiBox*> cloneBox = getSuiBoxFromWindowType(SuiWindowType::CLONE_REQUEST);

		if (cloneBox != NULL) {
			cloneBox->clearOptions();
			sendMessage(cloneBox->generateMessage());
		} else {
			//Otherwise, send them a new one.
			server->getPlayerManager()->sendActivateCloneRequest(creature);
		}
	}

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == NULL || zoneServer->isServerLoading())
		return;

	// Leave all planet chat rooms
	for (int i = 0; i < zoneServer->getZoneCount(); ++i) {
		ManagedReference<Zone*> zone = zoneServer->getZone(i);

		if (zone == NULL)
			continue;

		ManagedReference<ChatRoom*> room = zone->getChatRoom();
		if( room == NULL )
			continue;

		room->removePlayer(creature);

	}

	// Join current planet chat room
	if(creature->getZone() != NULL ){
		ManagedReference<ChatRoom*> planetChat = creature->getZone()->getChatRoom();

		if (planetChat == NULL)
			return;

		planetChat->sendTo(creature);
		planetChat->addPlayer(creature);
	}

	if(creature->getZone() != NULL && creature->getZone()->getPlanetManager() != NULL) {
		ManagedReference<WeatherManager*> weatherManager = creature->getZone()->getPlanetManager()->getWeatherManager();
		if(weatherManager != NULL) {
			creature->setCurrentWind((byte)System::random(200));
			creature->setCurrentWeather(0xFF);
			weatherManager->sendWeatherTo(creature);
		}
	}

}

void PlayerObjectImplementation::sendFriendLists() {
	info("sending friendslist message  size " + String::valueOf(friendList.size()));

	ChatManager* chatManager = server->getChatManager();

	friendList.resetUpdateCounter();
	ignoreList.resetUpdateCounter();

	FriendsListMessage* flist = new FriendsListMessage(_this.getReferenceUnsafeStaticCast());
	getParent().get()->sendMessage(flist);

	IgnoreListMessage* ilist = new IgnoreListMessage(_this.getReferenceUnsafeStaticCast());
	getParent().get()->sendMessage(ilist);

	DeltaMessage* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
	friendList.insertToDeltaMessage(delta);
	ignoreList.insertToDeltaMessage(delta);
	delta->close();

	getParent().get()->sendMessage(delta);
}

void PlayerObjectImplementation::sendMessage(BasePacket* msg) {
	ManagedReference<SceneObject*> strongParent = getParent().get();
	if (strongParent == NULL)
		delete msg;
	else {
		strongParent->sendMessage(msg);
	}
}

bool PlayerObjectImplementation::setCharacterBit(uint32 bit, bool notifyClient) {
	if (!(characterBitmask & bit)) {
		characterBitmask |= bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}
		return true;
	} else
		return false;
}

bool PlayerObjectImplementation::isAnonymous()  {
	return (characterBitmask & ((uint32)ANONYMOUS)) != 0;
}

bool PlayerObjectImplementation::isAFK()  {
	return (characterBitmask & ((uint32)AFK)) != 0;
}

bool PlayerObjectImplementation::isRoleplayer()  {
	return (characterBitmask & ((uint32)ROLEPLAYER)) != 0;
}

bool PlayerObjectImplementation::isNewbieHelper()  {
	return (characterBitmask & ((uint32)NEWBIEHELPER)) != 0;
}

bool PlayerObjectImplementation::isLFG()  {
	return (characterBitmask & ((uint32)LFG)) != 0;
}

bool PlayerObjectImplementation::clearCharacterBit(uint32 bit, bool notifyClient) {
	if (characterBitmask & bit) {
		characterBitmask &= ~bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}

		return true;
	} else
		return false;
}

void PlayerObjectImplementation::sendBadgesResponseTo(CreatureObject* player) {
	BaseMessage* msg = new BadgesResponseMessage(getParent().get(), &badges);
	player->sendMessage(msg);
}

void PlayerObjectImplementation::awardBadge(uint32 badge) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();
	playerManager->awardBadge(_this.getReferenceUnsafeStaticCast(), badge);
}

void PlayerObjectImplementation::setFactionStatus(int status) {
	factionStatus = status;

	CreatureObject* creature = cast<CreatureObject*>(getParent().get().get());
	uint32 pvpStatusBitmask = creature->getPvpStatusBitmask();

	if (factionStatus == FactionStatus::COVERT) {
		creature->sendSystemMessage("@faction_recruiter:covert_complete");

		if (pvpStatusBitmask & CreatureFlag::OVERT)
			pvpStatusBitmask -= CreatureFlag::OVERT;

		if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
			pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

		/*if (pvpStatusBitmask & CreatureFlag::BLINK_GREEN)
			pvpStatusBitmask -= CreatureFlag::BLINK_GREEN;*/

		creature->setPvpStatusBitmask(pvpStatusBitmask);
	} else if (factionStatus == FactionStatus::OVERT) {

		if(!(pvpStatusBitmask & CreatureFlag::OVERT)) {
			creature->addCooldown("declare_overt_cooldown",GCWManagerImplementation::overtCooldown*1000);
			pvpStatusBitmask |= CreatureFlag::OVERT;
		}

		if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
			pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

		/*if (pvpStatusBitmask & CreatureFlag::BLINK_GREEN)
			pvpStatusBitmask -= CreatureFlag::BLINK_GREEN;*/

		creature->sendSystemMessage("@faction_recruiter:overt_complete");

		creature->setPvpStatusBitmask(pvpStatusBitmask);
	} else if (factionStatus == FactionStatus::ONLEAVE) {
		if (pvpStatusBitmask & CreatureFlag::OVERT)
			pvpStatusBitmask -= CreatureFlag::OVERT;

		if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
			pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

		/*if (pvpStatusBitmask & CreatureFlag::BLINK_GREEN)
			pvpStatusBitmask -= CreatureFlag::BLINK_GREEN;*/

		if (creature->getFaction() != 0)
			creature->sendSystemMessage("@faction_recruiter:on_leave_complete");

		creature->setPvpStatusBitmask(pvpStatusBitmask);
	}

	Vector<ManagedReference<CreatureObject*> > petsToStore;

	for (int i = 0; i < getActivePetsSize(); i++) {
		Reference<AiAgent*> pet = getActivePet(i);

		if (pet == NULL)
			continue;

		CreatureTemplate* creatureTemplate = pet->getCreatureTemplate();

		if (creatureTemplate != NULL) {
			String templateFaction = creatureTemplate->getFaction();

			if (!templateFaction.isEmpty() && factionStatus == FactionStatus::ONLEAVE) {
				petsToStore.add(pet.castTo<CreatureObject*>());
				creature->sendSystemMessage("You're no longer the right faction status for one of your pets, storing...");
				continue;
			}
		}

		if (pvpStatusBitmask & CreatureFlag::PLAYER)
			pvpStatusBitmask &= ~CreatureFlag::PLAYER;

		pet->setPvpStatusBitmask(pvpStatusBitmask);
	}

	StoreSpawnedChildrenTask* task = new StoreSpawnedChildrenTask(creature, petsToStore);
	task->execute();

	updateInRangeBuildingPermissions();
}

int PlayerObjectImplementation::addExperience(const String& xpType, int xp, bool notifyClient) {
	if (xp == 0)
		return 0;

	int valueToAdd = xp;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (experienceList.contains(xpType)) {
		xp += experienceList.get(xpType);



		if (xp <= 0 && xpType != "jedi_general") {
			removeExperience(xpType, notifyClient);
			return 0;
		// -10 million experience cap for Jedi experience loss
		} else if(xp < -10000000 && xpType == "jedi_general") {
			xp = -10000000;
		}
	}

	int xpCap = -1;

	if (xpTypeCapList.contains(xpType))
		xpCap = xpTypeCapList.get(xpType);

	if (xpCap < 0)
		xpCap = 2000;

	if (xp > xpCap) {
		valueToAdd = xpCap - (xp - valueToAdd);
		xp = xpCap;
	}

	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(0);
		experienceList.set(xpType, xp, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		experienceList.set(xpType, xp);
	}

	return valueToAdd;
}

void PlayerObjectImplementation::removeExperience(const String& xpType, bool notifyClient) {
	if (!experienceList.contains(xpType))
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(0);
		experienceList.drop(xpType, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		experienceList.drop(xpType);
	}
}

bool PlayerObjectImplementation::hasCappedExperience(const String& xpType) {
	if (experienceList.contains(xpType) && xpTypeCapList.contains(xpType)) {
		return experienceList.get(xpType) == xpTypeCapList.get(xpType);
	}

	return false;
}

void PlayerObjectImplementation::setWaypoint(WaypointObject* waypoint, bool notifyClient) {
	uint64 waypointID = waypoint->getObjectID();

	if (notifyClient) {
		PlayerObjectDeltaMessage8* msg = new PlayerObjectDeltaMessage8(this);
		msg->startUpdate(1);
		waypointList.set(waypointID, waypoint, msg, 1);
		msg->close();

		sendMessage(msg);
	} else {
		waypointList.set(waypointID, waypoint);
	}
}

void PlayerObjectImplementation::addWaypoint(WaypointObject* waypoint, bool checkName, bool notifyClient) {
	uint64 waypointID = waypoint->getObjectID();

	if (waypointList.contains(waypointID)) {
		updateWaypoint(waypointID);
		return;
	}

	int specialTypeID = waypoint->getSpecialTypeID();
	bool doRemove = false;
	bool destroy = false;

	if (checkName) {
		String name = waypoint->getCustomObjectName().toString();
		waypointID = waypointList.find(name);

		if(waypointID != 0) {
			doRemove = true;
			destroy = true;
		}
	}

	if (!doRemove && specialTypeID != 0) {
		waypointID = waypointList.getWaypointBySpecialType(specialTypeID);

		if(waypointID != 0) {
			doRemove = true;
			destroy = true;
		}
	}

	if(doRemove)
		removeWaypoint(waypointID, notifyClient, destroy);

	setWaypoint(waypoint, notifyClient);
}

void PlayerObjectImplementation::removeWaypoint(uint64 waypointID, bool notifyClient, bool destroy) {
	ManagedReference<WaypointObject*> waypoint = waypointList.get(waypointID);

	if (waypoint == NULL)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage8* msg = new PlayerObjectDeltaMessage8(this);
		msg->startUpdate(1);
		waypointList.drop(waypointID, msg, 1);
		msg->close();

		sendMessage(msg);
	} else {
		waypointList.drop(waypointID);
	}

	if (destroy && waypoint->isPersistent()) {
		waypoint->destroyObjectFromDatabase(true);
	}
}

void PlayerObjectImplementation::updateWaypoint(uint64 waypointID) {
	ManagedReference<WaypointObject*> waypoint = waypointList.get(waypointID);

	if (waypoint == NULL)
		return;

	PlayerObjectDeltaMessage8* msg = new PlayerObjectDeltaMessage8(this);
	msg->startUpdate(1);
	waypointList.update(waypointID, msg, 1);
	msg->close();

	sendMessage(msg);

}

void PlayerObjectImplementation::removeWaypointBySpecialType(int specialTypeID, bool notifyClient) {
	uint64 waypointID = waypointList.getWaypointBySpecialType(specialTypeID);

	while (waypointID != 0) {
		removeWaypoint(waypointID, notifyClient);

		waypointID = waypointList.getWaypointBySpecialType(specialTypeID);
	}

}

WaypointObject* PlayerObjectImplementation::getWaypointBySpecialType(int specialTypeID) {
	uint64 waypointID = waypointList.getWaypointBySpecialType(specialTypeID);
	if (waypointID != 0) {
		return waypointList.get(waypointID);
	}
	return NULL;
}

WaypointObject* PlayerObjectImplementation::getSurveyWaypoint() {
	return getWaypointBySpecialType(WaypointObject::SPECIALTYPE_RESOURCE);
}

WaypointObject* PlayerObjectImplementation::addWaypoint(const String& planet, float positionX, float positionY, bool notifyClient) {
	ManagedReference<WaypointObject*> obj = getZoneServer()->createObject(0xc456e788, 1).castTo<WaypointObject*>();
	obj->setPlanetCRC(planet.hashCode());
	obj->setPosition(positionX, 0, positionY);
	obj->setActive(true);

	addWaypoint(obj, false, notifyClient);

	return obj;
}

void PlayerObjectImplementation::addAbility(Ability* ability, bool notifyClient) {
	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(0);
		abilityList.add(ability, msg, 1);
		msg->close();
		sendMessage(msg);
	} else {
		abilityList.add(ability);
	}
}

void PlayerObjectImplementation::addAbilities(Vector<Ability*>& abilities, bool notifyClient) {
	if (abilities.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(0);

		abilityList.add(abilities.get(0), msg, abilities.size());

		for (int i = 1; i < abilities.size(); ++i)
			abilityList.add(abilities.get(i), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < abilities.size(); ++i)
			abilityList.add(abilities.get(i));
	}
}

void PlayerObjectImplementation::removeAbility(Ability* ability, bool notifyClient) {
	int index = abilityList.find(ability);

	if (index == -1)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(0);
		abilityList.remove(index, msg, 1);
		msg->close();
		sendMessage(msg);
	} else {
		abilityList.remove(index);
	}
}

void PlayerObjectImplementation::removeAbilities(Vector<Ability*>& abilities, bool notifyClient) {
	if (abilities.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(0);

		abilityList.remove(abilityList.find(abilities.get(0)), msg, abilities.size());

		for (int i = 1; i < abilities.size(); ++i)
			abilityList.remove(abilityList.find(abilities.get(i)), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < abilities.size(); ++i)
			abilityList.remove(abilityList.find(abilities.get(i)));
	}
}

bool PlayerObjectImplementation::addSchematics(Vector<ManagedReference<DraftSchematic* > >& schematics, bool notifyClient) {
	if (schematics.size() == 0)
		return false;

	Vector<ManagedReference<DraftSchematic* > > schematicsToSend;
	for (int i = 0; i < schematics.size(); ++i) {

		/// If schematic is not already in the schematic list, we want to send it
		/// if not, we don't want to send it to the datapad
		if(!schematicList.contains(schematics.get(i)))
			schematicsToSend.add(schematics.get(i));
	}

	if(schematicsToSend.size() == 0)
		return false;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(4);

		schematicList.add(schematicsToSend.get(0), msg, schematicsToSend.size());

		for (int i = 1; i < schematicsToSend.size(); ++i)
			schematicList.add(schematicsToSend.get(i),  msg, 0);

		msg->close();

		sendMessage(msg);
	} else {

		for (int i = 0; i < schematicsToSend.size(); ++i)
			schematicList.add(schematicsToSend.get(i));

	}

	return true;
}

bool PlayerObjectImplementation::addRewardedSchematic(DraftSchematic* schematic, short type, int quantity, bool notifyClient) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	schematics.add(schematic);

	CreatureObject* parent = cast<CreatureObject*>(_this.getReferenceUnsafeStaticCast()->getParent().get().get());

	if (parent == NULL)
		return false;

	if (type == SchematicList::LOOT && schematicList.contains(schematic)) {
		parent->sendSystemMessage("@loot_schematic:already_have_schematic"); // You already have this schematic.
		return false;
	}

	if(!schematicList.addRewardedSchematic(schematic, type, quantity))
		return true;

	if(addSchematics(schematics, notifyClient)) {
		if(notifyClient) {
			schematic->sendDraftSlotsTo(parent);
			schematic->sendResourceWeightsTo(parent);
		}
		return true;
	}
	return false;
}

/**
 * For use when manually removing a schematic, like if a quest termination removed a schematic
 * from a player, not needed when schematics are automatically removed by usecount decreasing
 */
void PlayerObjectImplementation::removeRewardedSchematic(DraftSchematic* schematic, bool notifyClient) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	schematics.add(schematic);
	schematicList.removeRewardedSchematic(schematic);

	return removeSchematics(schematics, true);
}

void PlayerObjectImplementation::decreaseSchematicUseCount(DraftSchematic* schematic) {

	if(schematicList.decreaseSchematicUseCount(schematic)) {
		Vector<ManagedReference<DraftSchematic*> > schematics;

		schematics.add(schematic);
		return removeSchematics(schematics, true);
	}
}

void PlayerObjectImplementation::removeSchematics(Vector<ManagedReference<DraftSchematic* > >& schematics, bool notifyClient) {

	if (schematics.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		msg->startUpdate(4);

		schematicList.removeAll(msg);

		msg->close();

		sendMessage(msg);

	} else {

		schematicList.removeAll();
	}

	/**
	 * Here we are loading the schematics based on the skills that the
	 * player has, we do this incase we change the items
	 * in the schematic group.
	 */
	ZoneServer* zoneServer = server->getZoneServer();
	SkillManager* skillManager = zoneServer->getSkillManager();
	ManagedReference<CreatureObject*> player = cast<CreatureObject*>( getParentRecursively(SceneObjectType::PLAYERCREATURE).get().get());

	if(player == NULL)
		return;

	SkillList* playerSkillBoxList = player->getSkillList();

	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		Skill* skillBox = playerSkillBoxList->get(i);
		skillManager->awardDraftSchematics(skillBox, _this.getReferenceUnsafeStaticCast(), true);
	}

	schematicList.addRewardedSchematics(_this.getReferenceUnsafeStaticCast());
}

void PlayerObjectImplementation::doDigest(int fillingReduction) {
	if (!isDigesting())
		return;

	// Make sure filling isn't over max before we reduce
	if (foodFilling > foodFillingMax)
		foodFilling = foodFillingMax;

	if (drinkFilling > drinkFillingMax)
		drinkFilling = drinkFillingMax;

	if (foodFilling > 0) {
		setFoodFilling(foodFilling - fillingReduction);
		if (foodFilling < 0)
			foodFilling = 0;
	}

	if (drinkFilling > 0) {
		setDrinkFilling(drinkFilling - fillingReduction);
		if (drinkFilling < 0)
			drinkFilling = 0;
	}
}

Vector<ManagedReference<DraftSchematic* > > PlayerObjectImplementation::filterSchematicList(
		CreatureObject* player, Vector<uint32>* enabledTabs, int complexityLevel) {

	Locker _locker(_this.getReferenceUnsafeStaticCast());

	return schematicList.filterSchematicList(player, enabledTabs, complexityLevel);
}

void PlayerObjectImplementation::addFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	PlayerManager* playerManager = server->getPlayerManager();

	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<CreatureObject*> playerToAdd;
	playerToAdd = zoneServer->getObject(objID).castTo<CreatureObject*>();

	ManagedReference<SceneObject*> strongParent = getParent().get();
	if (playerToAdd == NULL || playerToAdd == strongParent) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			if (strongParent != NULL && strongParent->isCreatureObject())
				(cast<CreatureObject*>(strongParent.get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToAddGhost = playerToAdd->getPlayerObject();

	if (playerToAddGhost == NULL)
		return;

	if (strongParent != NULL && strongParent->isCreatureObject())
		playerToAddGhost->addReverseFriend(cast<CreatureObject*>(strongParent.get())->getFirstName());
	playerToAddGhost->updateToDatabase();

	if (notifyClient && strongParent != NULL) {
		AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
		strongParent->sendMessage(init);

		AddFriendMessage* add = new AddFriendMessage(strongParent->getObjectID(),	nameLower, "Core3", true);
		strongParent->sendMessage(add);

		if (playerToAdd->isOnline()) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(nameLower, "Core3", true);
			strongParent->sendMessage(notifyStatus);
		}

		friendList.add(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		friendList.insertToDeltaMessage(delta);
		delta->close();

		strongParent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "friend_added");
		param.setTT(nameLower);
		if (strongParent->isCreatureObject())
			(cast<CreatureObject*>(strongParent.get()))->sendSystemMessage(param);

	} else {
		friendList.add(nameLower);
	}
}

void PlayerObjectImplementation::removeFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	ManagedReference<CreatureObject*> strongParent = getParent().get().castTo<CreatureObject*>();

	if (!friendList.contains(nameLower)) {
		if (notifyClient && strongParent != NULL) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			strongParent->sendSystemMessage(param);
		}

		return;
	}

	PlayerManager* playerManager = server->getPlayerManager();
	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<CreatureObject*> playerToRemove;
	playerToRemove = zoneServer->getObject(objID).castTo<CreatureObject*>();

	if (playerToRemove == NULL) {
		if (notifyClient && strongParent != NULL) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			strongParent->sendSystemMessage(param);
		}

	} else {
		PlayerObject* playerToRemoveGhost = playerToRemove->getPlayerObject();

		if (playerToRemoveGhost != NULL) {
			if (strongParent != NULL)
				playerToRemoveGhost->removeReverseFriend(strongParent->getFirstName());
			playerToRemoveGhost->updateToDatabase();
		}
	}

	ManagedReference<SceneObject*> parent = getParent().get();

	if (notifyClient && parent != NULL) {
		AddFriendMessage* add = new AddFriendMessage(parent->getObjectID(),	nameLower, "Core3", false);
		parent->sendMessage(add);

		friendList.removePlayer(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		friendList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "friend_removed");
		param.setTT(nameLower);
		if (strongParent != NULL)
			strongParent->sendSystemMessage(param);

	} else {
		friendList.removePlayer(nameLower);
	}
}

void PlayerObjectImplementation::removeAllFriends() {
	ManagedReference<CreatureObject*> strongParent = getParent().get().castTo<CreatureObject*>();

	if (strongParent == NULL) {
		return;
	}

	String playerName = strongParent->getFirstName();
	PlayerManager* playerManager = server->getPlayerManager();
	ZoneServer* zoneServer = server->getZoneServer();

	while (friendList.size() > 0) {
		String name = friendList.get(0).toLowerCase();
		uint64 objID = playerManager->getObjectID(name);

		ManagedReference<CreatureObject*> playerToRemove = zoneServer->getObject(objID).castTo<CreatureObject*>();

		if (playerToRemove != NULL) {
			PlayerObject* playerToRemoveGhost = playerToRemove->getPlayerObject();

			if (playerToRemoveGhost != NULL) {
				playerToRemoveGhost->removeReverseFriend(playerName);
				playerToRemoveGhost->updateToDatabase();
			}
		}

		friendList.removePlayer(name);
	}

	while (friendList.reversePlayerCount() > 0) {
		String name = friendList.getReversePlayer(0).toLowerCase();
		uint64 objID = playerManager->getObjectID(name);

		ManagedReference<CreatureObject*> playerToRemove = zoneServer->getObject(objID).castTo<CreatureObject*>();

		if (playerToRemove != NULL && playerToRemove->isPlayerCreature()) {
			EXECUTE_TASK_2(playerToRemove, playerName, {
					Locker locker(playerToRemove_p);

					PlayerObject* ghost = playerToRemove_p->getPlayerObject();
					if (ghost != NULL) {
						ghost->removeFriend(playerName_p, false);
					}
			});
		}

		removeReverseFriend(name);
	}
}

void PlayerObjectImplementation::removeAllReverseFriends(const String& oldName) {
	PlayerManager* playerManager = server->getPlayerManager();
	ZoneServer* zoneServer = server->getZoneServer();

	while (friendList.reversePlayerCount() > 0) {
		String name = friendList.getReversePlayer(0).toLowerCase();
		uint64 objID = playerManager->getObjectID(name);

		ManagedReference<CreatureObject*> reverseFriend = zoneServer->getObject(objID).castTo<CreatureObject*>();

		if (reverseFriend != NULL && reverseFriend->isPlayerCreature()) {
			EXECUTE_TASK_2(reverseFriend, oldName, {
					Locker locker(reverseFriend_p);

					PlayerObject* ghost = reverseFriend_p->getPlayerObject();
					if (ghost != NULL) {
						ghost->removeFriend(oldName_p, false);
					}
			});
		}

		removeReverseFriend(name);
	}
}

void PlayerObjectImplementation::addIgnore(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();
	ManagedReference<SceneObject*> parent = getParent().get();

	if (notifyClient && parent != NULL) {
		AddIgnoreMessage* add = new AddIgnoreMessage(parent->getObjectID(),	nameLower, "Core3", true);
		parent->sendMessage(add);

		ignoreList.add(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		ignoreList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "ignore_added");
		param.setTT(nameLower);
		if (parent->isCreatureObject())
			(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		ignoreList.add(nameLower);
	}
}


void PlayerObjectImplementation::removeIgnore(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();
	ManagedReference<SceneObject*> parent = getParent();

	if (!ignoreList.contains(nameLower)) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "ignore_not_found");
			param.setTT(nameLower);
			if (parent != NULL && parent->isCreatureObject())
				(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);
		}

		return;
	}

	if (notifyClient && parent != NULL) {
		AddIgnoreMessage* add = new AddIgnoreMessage(parent->getObjectID(),	nameLower, "Core3", false);
		parent->sendMessage(add);

		ignoreList.removePlayer(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		ignoreList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "ignore_removed");
		param.setTT(nameLower);
		if (parent->isCreatureObject())
			(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		ignoreList.removePlayer(nameLower);
	}
}

void PlayerObjectImplementation::setTitle(const String& characterTitle, bool notifyClient) {
	if (title == characterTitle)
		return;

	if(!characterTitle.isEmpty()){
		Skill* targetSkill = SkillManager::instance()->getSkill(characterTitle);

		if(targetSkill == NULL || !targetSkill->isTitle()) {
			return;
		}
	}

	title = characterTitle;

	if (notifyClient) {
		PlayerObjectDeltaMessage3* dplay3 = new PlayerObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		dplay3->setCurrentTitle(title);
		dplay3->close();
		broadcastMessage(dplay3, true); //update the zone.
	}
}

void PlayerObjectImplementation::notifyOnline() {
	ManagedReference<SceneObject*> parent = getParent().get();
	CreatureObject* playerCreature = cast<CreatureObject*>( parent.get());
	if (playerCreature == NULL || parent == NULL)
		return;

	ChatManager* chatManager = server->getChatManager();

	String firstName = playerCreature->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < friendList.reversePlayerCount(); ++i) {
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(friendList.getReversePlayer(i));

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(firstName, "Core3", true);
			player->sendMessage(notifyStatus);
		}
	}

	for (int i = 0; i < friendList.size(); ++i) {
		String name = friendList.get(i);
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(name);

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(name, "Core3", true);
			parent->sendMessage(notifyStatus);
		}
	}

	//Resend all suis.
	for (int i = 0; i < suiBoxes.size(); ++i) {
		ManagedReference<SuiBox*> sui = suiBoxes.get(i);

		parent->sendMessage(sui->generateMessage());
	}

	//Login to visibility manager
	VisibilityManager::instance()->login(playerCreature);

	//Login to jedi manager
	JediManager::instance()->onPlayerLoggedIn(playerCreature);

	if (getForcePowerMax() > 0 && getForcePower() < getForcePowerMax())
		activateForcePowerRegen();

	schedulePvpTefRemovalTask();
}

void PlayerObjectImplementation::notifyOffline() {
	//info("notifyOffline", true);
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	if (chatManager == NULL)
		return;

	ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(parent.get().get());
	if (playerCreature == NULL)
		return;

	String firstName = playerCreature->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < friendList.reversePlayerCount(); ++i) {
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(friendList.getReversePlayer(i));

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(firstName, "Core3", false);
			player->sendMessage(notifyStatus);
		}
	}

	//Logout from visibility manager
	VisibilityManager::instance()->logout(playerCreature);

	//Logout from jedi manager
	JediManager::instance()->onPlayerLoggedOut(playerCreature);
}

void PlayerObjectImplementation::setLanguageID(byte language, bool notifyClient) {
	if (languageID == language)
		return;

	languageID = language;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		dplay9->setLanguageID(languageID);
		dplay9->close();
		getParent().get()->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::toggleCharacterBit(uint32 bit) {
	if (characterBitmask & bit) {
		clearCharacterBit(bit, true);
	} else {
		setCharacterBit(bit, true);
	}
}

void PlayerObjectImplementation::setFoodFilling(int newValue, bool notifyClient) {
	if (foodFilling == newValue)
		return;

	foodFilling = newValue;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		dplay9->updateFoodFilling(newValue);
		dplay9->close();
		getParent().get()->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::setDrinkFilling(int newValue, bool notifyClient) {
	if (drinkFilling == newValue)
		return;

	drinkFilling = newValue;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
		dplay9->updateDrinkFilling(drinkFilling);
		dplay9->close();
		getParent().get()->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::increaseFactionStanding(const String& factionName, float amount) {
	if (amount < 0)
		return; //Don't allow negative values to be sent to this method.

	CreatureObject* player = cast<CreatureObject*>( parent.get().get());
	if (player == NULL)
		return;

	//Get the current amount of faction standing
	float currentAmount = factionStandingList.getFactionStanding(factionName);

	//Ensure that the new amount is not greater than 5000.
	float newAmount = currentAmount + amount;

	if (!factionStandingList.isPvpFaction(factionName))
		newAmount = MIN(5000, newAmount);
	else if (player->getFaction() == factionName.hashCode())
		newAmount = MIN(FactionManager::instance()->getFactionPointsCap(player->getFactionRank()), newAmount);
	else
		newAmount = MIN(1000, newAmount);

	factionStandingList.put(factionName, newAmount);

	if (amount != 0) {
		int change = floor(newAmount - currentAmount);

		//Send the proper system message.
		StringIdChatParameter msg("@base_player:prose_award_faction");
		msg.setTO("@faction/faction_names:" + factionName);
		msg.setDI(change);

		if (change == 0)
			msg.setStringId("@base_player:prose_max_faction");


		player->sendSystemMessage(msg);
	}
}

uint32 PlayerObjectImplementation::getNewSuiBoxID(uint32 type) {
	return (++suiBoxNextID << 16) + (uint16)type;
}

void PlayerObjectImplementation::removeSuiBox(unsigned int boxID, bool closeWindowToClient) {
	if (closeWindowToClient == true) {
		SuiBox* sui = suiBoxes.get(boxID);

		if (sui != NULL) {
			sendMessage(sui->generateCloseMessage());
		}
	}

	suiBoxes.drop(boxID);
}

void PlayerObjectImplementation::removeSuiBoxType(unsigned int windowType) {
	SuiBox* sui = NULL;

	while ((sui = getSuiBoxFromWindowType(windowType)) != NULL) {
		removeSuiBox(sui->getBoxID(), true);
	}
}

void PlayerObjectImplementation::decreaseFactionStanding(const String& factionName, float amount) {
	if (amount < 0)
		return; //Don't allow negative values to be sent to this method.

	//Get the current amount of faction standing
	float currentAmount = factionStandingList.get(factionName);

	CreatureObject* player = cast<CreatureObject*>( parent.get().get());
	if (player == NULL)
		return;

	//Ensure that the new amount is not less than -5000.
	float newAmount = MAX(-5000, currentAmount - amount);

	if (factionStandingList.isPvpFaction(factionName)) {
		if (player->getFaction() == factionName.hashCode())
			newAmount = MIN(FactionManager::instance()->getFactionPointsCap(player->getFactionRank()), newAmount);
		else
			newAmount = MIN(1000, newAmount);
	}

	factionStandingList.put(factionName, newAmount);

	if (amount != 0) {
		int change = floor(currentAmount - newAmount);

		//Send the proper system message.
		StringIdChatParameter msg("@base_player:prose_lose_faction");
		msg.setTO("@faction/faction_names:" + factionName);
		msg.setDI(change);

		if (change == 0)
			msg.setStringId("@base_player:prose_min_faction");

		player->sendSystemMessage(msg);
	}
}

float PlayerObjectImplementation::getFactionStanding(const String& factionName) {
	return factionStandingList.getFactionStanding(factionName);
}

bool PlayerObjectImplementation::isFirstIncapacitationExpired() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get().get());
	if (creature == NULL)
		return false;

	return creature->checkCooldownRecovery("firstIncapacitationTime");
}


void PlayerObjectImplementation::resetFirstIncapacitationTime() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get().get());
	if (creature == NULL)
		return;

	if (!isFirstIncapacitation())
		resetIncapacitationCounter();

	creature->addCooldown("firstIncapacitationTime", 900000);
}

void PlayerObjectImplementation::logout(bool doLock) {
	Locker _locker(parent.get());

	try {
		if (disconnectEvent == NULL) {
			info("creating disconnect event");

			disconnectEvent = new PlayerDisconnectEvent(_this.getReferenceUnsafeStaticCast());

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


void PlayerObjectImplementation::doRecovery() {
	if (getZoneServer()->isServerLoading()) {
		activateRecovery();

		return;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	/*if (!creature->isInQuadTree() && creature->getParent() != NULL && creature->getParent()->isCellObject() && creature->getClient() == NULL) {
		SceneObject* building = creature->getParent()->getParent();

		if (building != NULL && building->getZone() != NULL)
			//creature->insertToZone(building->getZone());
			building->getZone()->transferObject(creature, -1, true);
	}*/

	if (isLinkDead()) {
		if (logoutTimeStamp.isPast()) {
			info("unloading dead link player");

			unload();

			setOffline();

			if (creature->getClient() != NULL)
				creature->getClient()->closeConnection(false, true);

			return;
		} else {
			info("keeping dead linked player in game");
		}
	}

	creature->activateHAMRegeneration();
	creature->activateStateRecovery();

	CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();

	if (cooldownTimerMap->isPast("digestEvent")) {
		Time currentTime;

		int timeDelta = currentTime.getMiliTime() - lastDigestion.getMiliTime();
		int fillingReduction = timeDelta / 18000;

		doDigest(fillingReduction);

		lastDigestion.updateToCurrentTime();
		cooldownTimerMap->updateToCurrentAndAddMili("digestEvent", 18000);
	}

	DamageOverTimeList* damageOverTimeList = creature->getDamageOverTimeList();

	if (damageOverTimeList->hasDot() && damageOverTimeList->isNextTickPast()) {
		damageOverTimeList->activateDots(creature);
	}

	if (creature->isBleeding() && !damageOverTimeList->hasDot(CreatureState::BLEEDING))
		creature->clearState(CreatureState::BLEEDING);
	if (creature->isPoisoned() && !damageOverTimeList->hasDot(CreatureState::POISONED))
		creature->clearState(CreatureState::POISONED);
	if (creature->isDiseased() && !damageOverTimeList->hasDot(CreatureState::DISEASED))
		creature->clearState(CreatureState::DISEASED);
	if (creature->isOnFire() && !damageOverTimeList->hasDot(CreatureState::ONFIRE))
		creature->clearState(CreatureState::ONFIRE);

	CommandQueueActionVector* commandQueue = creature->getCommandQueue();

	if (creature->isInCombat() && creature->getTargetID() != 0 && !creature->isPeaced()
			&& (commandQueue->size() == 0) && creature->isNextActionPast() && !creature->isDead() && !creature->isIncapacitated()) {
		creature->executeObjectControllerAction(STRING_HASHCODE("attack"), creature->getTargetID(), "");
	}

	if (!getZoneServer()->isServerLoading()) {
		if(creature->getZone() != NULL && creature->getZone()->getPlanetManager() != NULL) {
			ManagedReference<WeatherManager*> weatherManager = creature->getZone()->getPlanetManager()->getWeatherManager();

			if (weatherManager != NULL)
				weatherManager->sendWeatherTo(creature);
		}
	}

	activateRecovery();
}

void PlayerObjectImplementation::activateRecovery() {
	if (recoveryEvent == NULL) {
		recoveryEvent = new PlayerRecoveryEvent(_this.getReferenceUnsafeStaticCast());

		recoveryEvent->schedule(3000);
	}
}

void PlayerObjectImplementation::activateForcePowerRegen() {
	if (forceRegenerationEvent == NULL) {
		forceRegenerationEvent = new ForceRegenerationEvent(_this.getReferenceUnsafeStaticCast());

		float timer = ((float) getForcePowerRegen()) / 5.f;
		float scheduledTime = 10 / timer;
		uint64 miliTime = static_cast<uint64>(scheduledTime * 1000.f);
		forceRegenerationEvent->schedule(miliTime);
	}
}

void PlayerObjectImplementation::setLinkDead() {
	onlineStatus = LINKDEAD;

	logoutTimeStamp.updateToCurrentTime();
	logoutTimeStamp.addMiliTime(30000);

	setCharacterBit(PlayerObjectImplementation::LD, true);

	activateRecovery();
}

void PlayerObjectImplementation::setOnline() {
	onlineStatus = ONLINE;

	clearCharacterBit(PlayerObjectImplementation::LD, true);

	doRecovery();

	activateMissions();
}

void PlayerObjectImplementation::reload(ZoneClientSession* client) {
	if (disconnectEvent != NULL) {
		disconnectEvent->cancel();
		disconnectEvent = NULL;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	if (isLoggingIn()) {
		creature->unlock();

		ZoneClientSession* owner = creature->getClient();

		if (owner != NULL && owner != client)
			owner->disconnect();

		creature->wlock();
	}

	setOnline();

	creature->setMovementCounter(0);

	//notifiedSentObjects.removeAll();

	if (creature->isRidingMount() && creature->getParent() == NULL) {
		creature->clearState(CreatureState::RIDINGMOUNT);
	}

	//creature->insertToZone(creature->getZone());
	creature->getZone()->transferObject(creature, -1, true);
}

void PlayerObjectImplementation::disconnect(bool closeClient, bool doLock) {
	Locker locker(parent.get());

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return;

	if (!isOnline()) {
		ZoneClientSession* owner = creature->getClient();

		if (closeClient && owner != NULL)
			owner->closeConnection(false, true);

		creature->setClient(NULL);

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

	ZoneClientSession* owner = creature->getClient();

	if (closeClient && owner != NULL)
		owner->closeConnection(false, true);

	creature->setClient(NULL);
}

void PlayerObjectImplementation::clearDisconnectEvent() {
	disconnectEvent = NULL;
}

void PlayerObjectImplementation::clearRecoveryEvent() {
	recoveryEvent = NULL;
}

void PlayerObjectImplementation::clearForceRegenerationEvent() {
	forceRegenerationEvent = NULL;
}

void PlayerObjectImplementation::maximizeExperience() {
	VectorMap<String, int>* xpCapList = getXpTypeCapList();

	for (int i = 0; i < xpCapList->size(); ++i) {
		addExperience(xpCapList->elementAt(i).getKey(), xpCapList->elementAt(i).getValue(), true);
	}
}

void PlayerObjectImplementation::activateMissions() {
	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL) {
		return;
	}

	SceneObject* datapad = creature->getSlottedObject("datapad");

	if (datapad == NULL) {
		return;
	}

	int datapadSize = datapad->getContainerObjectsSize();

	for (int i = datapadSize - 1; i >= 0; --i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			Reference<MissionObject*> mission = datapad->getContainerObject(i).castTo<MissionObject*>();

			if (mission != NULL) {
				//Check if it is target or destination NPC
				MissionObjective* objective = mission->getMissionObjective();
				if (objective != NULL) {
					Locker locker(objective);
					objective->activate();
				}
			}
		}
	}
}

void PlayerObjectImplementation::setForcePowerMax(int newValue, bool notifyClient) {
	if(newValue == getForcePowerMax())
		return;

	forcePowerMax = newValue;

	if(forcePower > forcePowerMax)
		setForcePower(forcePowerMax, true);

	if (forcePower < forcePowerMax) {
		activateForcePowerRegen();
	}

	if (notifyClient == true){
		// Update the force power bar max.
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePowerMax();
		dplay8->close();

		sendMessage(dplay8);
	}
}

void PlayerObjectImplementation::setForcePower(int fp, bool notifyClient) {

	if(fp == getForcePower())
		return;

	// Set forcepower back to 0 incase player goes below	
	if (fp < 0)
		fp = 0;	

	// Set force back to max incase player goes over
	if (fp > getForcePowerMax())
		fp = getForcePowerMax();


	// Activate regeneration.
	if (fp < getForcePowerMax()) {
		activateForcePowerRegen();
	}

	forcePower = fp;			

	if (notifyClient == true){
		// Update the force power bar.
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePower();
		dplay8->close();

		sendMessage(dplay8);
	}

}

void PlayerObjectImplementation::doForceRegen() {
	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL || creature->isIncapacitated() || creature->isDead())
		return;

	const static uint32 tick = 5;

	uint32 modifier = 1;

	if (creature->isMeditating()) {
		Reference<ForceMeditateTask*> medTask = creature->getPendingTask("forcemeditate").castTo<ForceMeditateTask*>();

		if (medTask != NULL)
			modifier = 3;
	}

	uint32 forceTick = tick * modifier;

	if (forceTick > getForcePowerMax() - getForcePower()){   // If the player's Force Power is going to regen again and it's close to max,
		setForcePower(getForcePowerMax());             // Set it to max, so it doesn't go over max.
	} else {
		setForcePower(getForcePower() + forceTick); // Otherwise regen normally.
	}
}

void PlayerObjectImplementation::clearScreenPlayData(const String& screenPlay) {
	for (int i = screenPlayData.size() - 1; i >= 0; --i) {
		if (screenPlayData.elementAt(i).getKey().contains(screenPlay + "_"))
			screenPlayData.drop(screenPlayData.elementAt(i).getKey());
	}
}

void PlayerObjectImplementation::addToBountyLockList(uint64 playerId) {
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			bountyLockList.get(playerId)->cancel();
		}
	} else {
		bountyLockList.put(playerId, new BountyHunterTefRemovalTask(_this.getReferenceUnsafeStaticCast(), playerId));
		updateBountyPvpStatus(playerId);
	}
}

void PlayerObjectImplementation::removeFromBountyLockList(uint64 playerId, bool immediately) {
	int tefTime = 15 * 60 * 1000;
	if (immediately) {
		//Schedule tef removal to happen soon but delay it enough for any bh mission to be dropped correctly.
		tefTime = 100;
	}
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			//Reschedule for another 15 minutes tef.
			bountyLockList.get(playerId)->reschedule(tefTime);
		} else {
			bountyLockList.get(playerId)->schedule(tefTime);
		}
	}
}

void PlayerObjectImplementation::removeFromBountyLockListDirectly(uint64 playerId) {
	if (bountyLockList.contains(playerId)) {
		if (bountyLockList.get(playerId)->isScheduled()) {
			bountyLockList.get(playerId)->cancel();
		}
	}
	bountyLockList.drop(playerId);
	updateBountyPvpStatus(playerId);
}

void PlayerObjectImplementation::updateBountyPvpStatus(uint64 playerId) {
	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(getParent().get().get());

	if (creature == NULL) {
		return;
	}

	ZoneServer* zoneServer = creature->getZoneServer();
	if (zoneServer == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> target = zoneServer->getObject(playerId).castTo<CreatureObject*>();

	if (target == NULL) {
		return;
	}

	creature->sendPvpStatusTo(target);
	target->sendPvpStatusTo(creature);
}

bool PlayerObjectImplementation::isBountyLocked() {
	return bountyLockList.size() > 0;
}

bool PlayerObjectImplementation::isInBountyLockList(uint64 playerId) {
	return bountyLockList.contains(playerId);
}

Time PlayerObjectImplementation::getLastVisibilityUpdateTimestamp() {
	return lastVisibilityUpdateTimestamp;
}

Time PlayerObjectImplementation::getLastPvpCombatActionTimestamp() {
	return lastPvpCombatActionTimestamp;
}

void PlayerObjectImplementation::updateLastPvpCombatActionTimestamp() {
	ManagedReference<CreatureObject*> parent = getParent().get().castTo<CreatureObject*>();

	if (parent == NULL)
		return;

	bool alreadyHasTef = hasPvpTef();

	lastPvpCombatActionTimestamp.updateToCurrentTime();
	lastPvpCombatActionTimestamp.addMiliTime(300000); // 5 minutes

	schedulePvpTefRemovalTask();

	if (!alreadyHasTef) {
		updateInRangeBuildingPermissions();
		parent->setPvpStatusBit(CreatureFlag::TEF);
	}
}

bool PlayerObjectImplementation::hasPvpTef() {
	return !lastPvpCombatActionTimestamp.isPast();
}

void PlayerObjectImplementation::schedulePvpTefRemovalTask(bool removeNow) {
	ManagedReference<CreatureObject*> parent = getParent().get().castTo<CreatureObject*>();

	if (parent == NULL)
		return;

	if (pvpTefTask == NULL) {
		pvpTefTask = new PvpTefRemovalTask(parent);
	}

	if (removeNow) {
		lastPvpCombatActionTimestamp.updateToCurrentTime();

		if (pvpTefTask->isScheduled()) {
			pvpTefTask->cancel();
		}

		pvpTefTask->execute();

	} else if (!pvpTefTask->isScheduled()) {
		if (hasPvpTef()) {
			pvpTefTask->schedule(llabs(getLastPvpCombatActionTimestamp().miliDifference()));
		} else {
			pvpTefTask->execute();
		}
	}

}

Vector3 PlayerObjectImplementation::getTrainerCoordinates() {
	return trainerCoordinates;
}

void PlayerObjectImplementation::setTrainerCoordinates(const Vector3& trainer) {
	trainerCoordinates = trainer;
}

void PlayerObjectImplementation::addPermissionGroup(const String& group, bool updatePermissions) {
	permissionGroups.put(group);

	if (updatePermissions)
		updateInRangeBuildingPermissions();
}

void PlayerObjectImplementation::removePermissionGroup(const String& group, bool updatePermissions) {
	permissionGroups.drop(group);

	if (updatePermissions)
		updateInRangeBuildingPermissions();
}

void PlayerObjectImplementation::updateInRangeBuildingPermissions() {
	ManagedReference<CreatureObject*> parent = getParent().get().castTo<CreatureObject*>();

	if (parent == NULL)
		return;

	Zone* zone = parent->getZone();

	if (zone == NULL)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) parent->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = closeObjects.get(i).castTo<BuildingObject*>();

		if (building != NULL) {
			building->updateCellPermissionsTo(parent);
		}
	}
}

bool PlayerObjectImplementation::hasPermissionGroup(const String& group) {
	return permissionGroups.contains(group);
}

void PlayerObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	removeAllFriends();

	for (int i = 0; i < currentEventPerks.size(); ++i) {
		uint64 oid = currentEventPerks.get(i);

		ManagedReference<EventPerkDeed*> perk = getZoneServer()->getObject(oid).castTo<EventPerkDeed*>();

		if (perk != NULL) {
			perk->activateRemoveEvent(true);
		}
	}

	for (int i = 0; i < ownedVendors.size(); ++i) {
		uint64 oid = ownedVendors.get(i);

		ManagedReference<TangibleObject*> vendor = getZoneServer()->getObject(oid).castTo<TangibleObject*>();

		if (vendor != NULL) {
			VendorManager::instance()->destroyVendor(vendor);
		}
	}

	for (int i = 0; i < ownedStructures.size(); ++i) {
		uint64 oid = ownedStructures.get(i);

		ManagedReference<StructureObject*> structure = getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure != NULL) {
			Zone* zone = structure->getZone();

			if (zone != NULL) {
				if (structure->isCivicStructure()) {
					StructureSetOwnerTask* task = new StructureSetOwnerTask(structure, 0);
					task->execute();

					if (structure->isCityHall()) {
						ManagedReference<CityRegion*> city = structure->getCityRegion().get();

						if (city != NULL) {
							EXECUTE_TASK_1(city, {
									Locker locker(city_p);

									city_p->setMayorID(0);
							});
						}
					}

					continue;
				}

				StructureManager::instance()->destroyStructure(structure);
			} else {
				structure->destroyObjectFromDatabase(true);
			}
		}
	}

	if (isMarried()) {
		PlayerManager* playerManager = server->getPlayerManager();
		ManagedReference<CreatureObject*> spouse = playerManager->getPlayer(spouseName);

		if (spouse != NULL) {
			PlayerObject* spouseGhost = spouse->getPlayerObject();

			if (spouseGhost != NULL) {
				RemoveSpouseTask* task = new RemoveSpouseTask(spouse);
				task->execute();
			}
		}
	}
}

int PlayerObjectImplementation::getLotsRemaining() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	int lotsRemaining = maximumLots;

	for (int i = 0; i < ownedStructures.size(); ++i) {
		unsigned long oid = ownedStructures.get(i);

		Reference<StructureObject*> structure = getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure != NULL) {
			lotsRemaining = lotsRemaining - structure->getLotSize();
		}
	}

	return lotsRemaining;
}

void PlayerObjectImplementation::setJediState(int state, bool notifyClient) {
	if (jediState == state)
		return;

	jediState = state;

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.getReferenceUnsafeStaticCast());
	delta->setJediState(state);
	delta->close();

	sendMessage(delta);
}

int PlayerObjectImplementation::getSpentJediSkillPoints() {
	if (jediState < 2)
		return 0;

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>( getParentRecursively(SceneObjectType::PLAYERCREATURE).get().get());

	if(player == NULL)
		return 0;

	int jediSkillPoints = 0;

	SkillList* skillList = player->getSkillList();

	for(int i = 0; i < skillList->size(); ++i) {
		Skill* jediSkill = skillList->get(i);

		if (jediSkill->getSkillName().indexOf("force_discipline") != -1)
			jediSkillPoints += jediSkill->getSkillPointsRequired();
	}

	return jediSkillPoints;
}

bool PlayerObjectImplementation::canActivateQuest(int questID) {
	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature == NULL)
		return false;

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

	if (playerManager == NULL)
		return false;

	// Invalid quest id
	if (questID < 0 || questID > playerManager->getTotalPlayerQuests())
		return false;

	// Quest is active or already completed
	if (hasActiveQuestBitSet(questID) || hasCompletedQuestsBitSet(questID))
		return false;

	String parentQuest = playerManager->getPlayerQuestParent(questID);

	// Quest has a parent quest that has not been completed
	if (parentQuest != "") {
		int parentQuestID = playerManager->getPlayerQuestID(parentQuest);

		if (parentQuestID < 0 || !hasCompletedQuestsBitSet(parentQuestID))
			return false;
	}

	return true;
}

void PlayerObjectImplementation::activateQuest(int questID) {
	if (!canActivateQuest(questID))
		return;

	CreatureObject* creature = cast<CreatureObject*>(getParent().get().get());

	if (creature == NULL)
		return;

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

	if (playerManager == NULL)
		return;

	ManagedReference<QuestInfo*> questInfo = playerManager->getQuestInfo(questID);

	if (questInfo == NULL)
		return;

	setActiveQuestsBit(questID, 1);

	if (questInfo->shouldSendSystemMessage())
		creature->sendSystemMessage("@quest/quests:quest_journal_updated");
}


void PlayerObjectImplementation::setActiveQuestsBit(int bitIndex, byte value, bool notifyClient) {
	activeQuests.setBit(bitIndex, value);

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage8* delta = new PlayerObjectDeltaMessage8(this);
	delta->startUpdate(5);
	activeQuests.insertToMessage(delta);
	delta->close();

	sendMessage(delta);
}

void PlayerObjectImplementation::setCompletedQuestsBit(int bitIndex, byte value, bool notifyClient) {
	completedQuests.setBit(bitIndex, value);

	if (!notifyClient)
		return;

	PlayerObjectDeltaMessage8* delta = new PlayerObjectDeltaMessage8(this);
	delta->startUpdate(4);
	completedQuests.insertToMessage(delta);
	delta->close();

	sendMessage(delta);
}

void PlayerObjectImplementation::setPlayerQuestData(uint32 questHashCode, PlayerQuestData& data, bool notifyClient) {
	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(6);
		playerQuestsData.set(questHashCode, data, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		playerQuestsData.set(questHashCode, data);
	}
}

PlayerQuestData PlayerObjectImplementation::getQuestData(uint32 questHashCode) {
	return playerQuestsData.get(questHashCode);
}

int PlayerObjectImplementation::getVendorCount() {
	// Cleanup vendor list before returning the count
	for (int i = ownedVendors.size() - 1; i >= 0; --i) {
		ManagedReference<SceneObject*> vendor = server->getZoneServer()->getObject(ownedVendors.get(i)).get();

		if (vendor == NULL) {
			ownedVendors.remove(i);
			continue;
		}

		if (vendor->getParent().get() == NULL)
			vendor->destroyObjectFromDatabase(true);
	}

	return ownedVendors.size();
}

bool PlayerObjectImplementation::hasChosenVeteranReward( const String& rewardTemplate ){

	for( int i = 0; i < chosenVeteranRewards.size(); i++){
		if( rewardTemplate == chosenVeteranRewards.get(i) ){
			return true;
		}
	}

	return false;

}

int PlayerObjectImplementation::getCharacterAgeInDays() {
	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

	ManagedReference<Account*> account = playerManager->getAccount(getAccountID());
	if(account == NULL) {
		return 0;
	}

	CharacterList* list = account->getCharacterList();
	if (list == NULL) {
		return 0;
	}

	Time currentTime;
	Time age;

	for (int i = 0; i < list->size(); i++) {
		CharacterListEntry entry = list->get(i);
		if (entry.getObjectID() == creature->getObjectID() && entry.getGalaxyID() == creature->getZoneServer()->getGalaxyID()) {
			age = entry.getCreationDate();
			break;
		}
	}

	uint32 timeDelta = currentTime.getTime() - age.getTime();

	int days = timeDelta / 60 / 60 / 24;

	return days;
}
