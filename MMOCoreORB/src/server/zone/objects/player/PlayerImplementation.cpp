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

#include "../../ZoneClientSession.h"
#include "../../ZoneServer.h"

#include "../../objects.h"
#include "../../packets.h"

#include "../../managers/player/PlayerManager.h"
#include "../../managers/player/ProfessionManager.h"
#include "../../managers/crafting/CraftingManager.h"
#include "../../managers/item/ItemManager.h"
#include "../../managers/combat/CombatManager.h"
#include "../../managers/guild/GuildManager.h"
#include "../../managers/group/GroupManager.h"
#include "../../managers/planet/PlanetManager.h"
#include "../../managers/resource/ResourceManager.h"
#include "../../managers/loot/LootManager.h"
#include "../../managers/sui/SuiManager.h"

#include "../../../chat/ChatManager.h"
#include "../../../ServerCore.h"

#include "Races.h"

#include "../terrain/Terrain.h"
#include "../terrain/RegionNames.h"

#include "../tangible/weapons/WeaponImplementation.h"

#include "Player.h"
#include "PlayerImplementation.h"

#include "PlayerHAM.h"

#include "events/PlayerLogoutEvent.h"
#include "events/PlayerDisconnectEvent.h"
#include "events/PlayerSaveStateEvent.h"
#include "events/PlayerRecoveryEvent.h"
#include "events/PlayerDigestEvent.h"
#include "events/CommandQueueActionEvent.h"
#include "events/ChangeFactionStatusEvent.h"
#include "events/CenterOfBeingEvent.h"
#include "events/PowerboostEventWane.h"
#include "events/PowerboostEventEnd.h"
#include "events/SurveyEvent.h"
#include "events/EntertainerEvent.h"
#include "events/SampleEvent.h"
#include "events/ReviveCountdownEvent.h"

#include "../creature/events/DizzyFallDownEvent.h"

#include "professions/Certification.h"

#include "../../managers/combat/CommandQueueAction.h"
#include "../../managers/skills/SkillManager.h"

PlayerImplementation::PlayerImplementation() : PlayerServant(0) {
	zoneID = 1;
	//zoneID = 8;

	setHeight(1.0f);
}

PlayerImplementation::PlayerImplementation(uint64 cid) : PlayerServant(baseID = cid << 32) {
	characterID = cid;
}

PlayerImplementation::~PlayerImplementation() {
	clearBuffs(false);

	for (int i = 0; i < suiBoxes.size(); ++i) {
		SuiBox* box =  suiBoxes.get(i);
		box->finalize();
	}

	if (playerObject != NULL) {
		playerObject->finalize();
		playerObject = NULL;
	}

	if (datapad != NULL) {
		info("undeploying player datapad");

		datapad->finalize();
		datapad = NULL;
	}

	if (hairObj != NULL) {
		hairObj->finalize();
		hairObj = NULL;
	}

	if (playerSaveStateEvent != NULL) {
		if (playerSaveStateEvent->isQueued())
			server->removeEvent(playerSaveStateEvent);

		delete playerSaveStateEvent;
		playerSaveStateEvent = NULL;
	}

	if (centerOfBeingEvent != NULL) {
		server->removeEvent(centerOfBeingEvent);

		delete centerOfBeingEvent;
		centerOfBeingEvent = NULL;
	}

	if (powerboostEventEnd != NULL) {
		server->removeEvent(powerboostEventEnd);

		delete powerboostEventEnd;
		powerboostEventEnd = NULL;
	}

	if (powerboostEventWane != NULL) {
		server->removeEvent(powerboostEventWane);

		delete powerboostEventWane;
		powerboostEventWane = NULL;
	}

	if (recoveryEvent != NULL) {
		if (recoveryEvent->isQueued())
			server->removeEvent(recoveryEvent);

		delete recoveryEvent;
		recoveryEvent = NULL;
	}

	if (digestEvent != NULL) {
		if (digestEvent->isQueued())
			server->removeEvent(digestEvent);

		delete digestEvent;
		digestEvent = NULL;
	}

	server->getZoneServer()->increaseTotalDeletedPlayers();

	info("undeploying player");
}

void PlayerImplementation::initialize() {
	objectType = PLAYER;

	owner = NULL;
	zone = NULL;

	onlineStatus  = LOGGINGIN;

	// objects
	playerObject = NULL;

	disconnectEvent = NULL;
	logoutEvent = NULL;

	playerSaveStateEvent = NULL;

	recoveryEvent = NULL;
	digestEvent = NULL;

	changeFactionEvent = NULL;

	datapad = NULL;

	stfName = "species";

	// modifiers
	weaponSpeedModifier = 1;

	// constants
	itemShift = 100;

	// pvp stuff
	deathCount = 0;
	pvpRating = PVPRATING_DEFAULT; //New players start with pvpRating of 1200
	duelList.setInsertPlan(SortedVector<Player*>::NO_DUPLICATE);
	factionStatus = 0;

	// profession
	skillPoints = 0;
	skillBoxesToSave.setInsertPlan(SortedVector<SkillBox*>::NO_DUPLICATE);
	certificationList.setInsertPlan(SortedVector<Certification*>::NO_DUPLICATE);

	// Draft Schematics
	draftSchematicList.setInsertPlan(SortedVector<DraftSchematic*>::NO_DUPLICATE);
	draftSchematicList.setNullValue(NULL);
	draftSchematicUpdateCount = 0;

	//Crafting
	currentCraftingTool = NULL;

	resourceDeedID = 0;

	//GM Flags
	chatMuted = false;
	immune = false;

	//Mission Vars
	misoRFC = 0x01;
	misoBSB = 0;
	curMisoKeys = "";
	finMisoKeys = "";

 	regionId = 31; //Ancorhead I think lols.

 	conversatingCreature = NULL;

 	chatRooms.setInsertPlan(SortedVector<ChatRoom*>::NO_DUPLICATE);

 	centered = false;
	powerboosted = false;

	centerOfBeingEvent = new CenterOfBeingEvent(this);
	powerboostEventEnd = new PowerboostEventEnd(this);
	powerboostEventWane = new PowerboostEventWane(this);


	lastTestPositionX = 0.f;
	lastTestPositionY = 0.f;

	tradeRequestedPlayer = 0;
	moneyToTrade = 0;
	acceptedTrade = false;
	verifiedTrade = false;

	surveyEvent = NULL;
	entertainerEvent = NULL;
	sampleEvent = NULL;
	firstSampleEvent = NULL;
	surveyWaypoint = NULL;
	surveyTool = NULL;
	cancelSample = false;
	surveyErrorMessage = false;
	sampleErrorMessage = false;

	// Stat Migration
	setTargetHealth(0);
	setTargetStrength(0);
	setTargetConstitution(0);
	setTargetAction(0);
	setTargetQuickness(0);
	setTargetStamina(0);
	setTargetMind(0);
	setTargetFocus(0);
	setTargetWillpower(0);

	reviveTimeout;
 	reviveCountdownEvent = NULL;

	suiBoxes.setInsertPlan(SortedVector<SuiBox*>::NO_DUPLICATE);
	suiBoxes.setNullValue(NULL);

	suiChoicesList = new SuiListBoxVector();

	suiBoxNextID = 0;

	guildLeader = false;

	setLogging(false);
	setGlobalLogging(true);
}

void PlayerImplementation::create(ZoneClientSession* client) {
	playerObject = new PlayerObject(_this);

	setClient(client);
	client->setPlayer(_this);

	string logName = "Player = " + firstName;

	setLockName(logName);
	//client->setLockName("ZoneClient = " + firstName);

	setLoggingName(logName);

	info("created player");
}

void PlayerImplementation::makeCharacterMask() {
	characterMask = 0;

	if (this->isRebel())
		characterMask |= REBEL;
	else if (this->isImperial())
		characterMask |= IMPERIAL;
	else
		characterMask |= NEUTRAL;

	if(this->isOnLeave())
		characterMask |= COVERT;

	switch (raceID) {
	case 0:
		characterMask |= MALE | HUMAN;
		break;
	case 1:
		characterMask |= MALE | TRANDOSHAN;
		break;
	case 2:
		characterMask |= MALE | TWILEK;
		break;
	case 3:
		characterMask |= MALE | BOTHAN;
		break;
	case 4:
		characterMask |= MALE | ZABRAK;
		break;
	case 5:
		characterMask |= MALE | RODIAN;
		break;
	case 6:
		characterMask |= MALE | MONCALAMARI;
		break;
	case 7:
		characterMask |= MALE | WOOKIEE;
		break;
	case 8:
		characterMask |= MALE | SULLUSTAN;
		break;
	case 9:
		characterMask |= MALE | ITHORIAN;
		break;
	case 10:
		characterMask |= FEMALE | HUMAN;
		break;
	case 11:
		characterMask |= FEMALE | TRANDOSHAN;
		break;
	case 12:
		characterMask |= FEMALE | TWILEK;
		break;
	case 13:
		characterMask |= FEMALE | BOTHAN;
		break;
	case 14:
		characterMask |= FEMALE | ZABRAK;
		break;
	case 15:
		characterMask |= FEMALE | RODIAN;
		break;
	case 16:
		characterMask |= FEMALE | MONCALAMARI;
		break;
	case 17:
		characterMask |= FEMALE | WOOKIEE;
		break;
	case 18:
		characterMask |= FEMALE | SULLUSTAN;
		break;
	case 19:
		characterMask |= FEMALE | ITHORIAN;
		break;
	}
}

void PlayerImplementation::refuseCreate(ZoneClientSession* client) {
	info("name refused for character creation");

	BaseMessage* msg = new ClientCreateCharacterFailed("name_declined_in_use");
	client->sendMessage(msg);

	client->disconnect();
}

void PlayerImplementation::load(ZoneClientSession* client) {
	try {
		//wlock();

		setLoggingIn();

		owner = client;
		client->setPlayer(_this);

		stringstream logName;
		logName << "Player = " << firstName << " (0x" << hex << objectID << dec << ")";

		setLockName(logName.str());
		setLoggingName(logName.str());

		info("loading player");

		makeCharacterMask();

		loadItems();
		//resetArmorEncumbrance();

		setLoggingIn(); //Anyone notice this is in here twice?

		Zone* zone = server->getZoneServer()->getZone(zoneID);
		insertToZone(zone);

		initializeEvents();

		server->addEvent(playerSaveStateEvent, 300000);

		resetArmorEncumbrance();

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->updateOtherFriendlists(_this, true);

		//unlock();
	} catch (Exception& e) {
		//unlock();

		error("logging in character");
		error(e.getMessage());

		client->disconnect();
	}
}

void PlayerImplementation::reload(ZoneClientSession* client) {
	try {
		wlock();

		if (isLoggingOut()) {
			if (disconnectEvent != NULL) {
				server->removeEvent(disconnectEvent);

				delete disconnectEvent;
				disconnectEvent = NULL;
			}

			info("reloading player");
		} else if (logoutEvent != NULL) {
			server->removeEvent(logoutEvent);

			delete logoutEvent;
			logoutEvent = NULL;
		} else if (isLoggingIn()) {
			info("kicking player over network failure");

			unlock();

			if (owner != NULL && owner != client)
				owner->disconnect();

			wlock();

			info("loading player");
		} else if (isOnline()) {
			info("already loaded");

			unlock();

			client->disconnect();
			return;
		} else if (isOffline()) {
			info("reloading player from Cache");
		}

		owner = client;
		client->setPlayer(_this);

		setLoggingIn();

		initializeEvents();

		server->addEvent(playerSaveStateEvent, 300000);

		Zone* zone = server->getZoneServer()->getZone(zoneID);

		if (isInQuadTree())
			reinsertToZone(zone);
		else
			insertToZone(zone);

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerObject->updateAllFriends(playerObject);
		playerManager->updateGuildStatus(_this);

		if (isMounted())
			dismount(true, true);

		//resetArmorEncumbrance();

		activateRecovery();

		//reset mission vars:
		misoRFC = 0x01;
		misoBSB = 0;

		playerManager->updateOtherFriendlists(_this, true);

		unlock();
	} catch (Exception& e) {
		error("reconnecting in character");
		error(e.getMessage());

		unlock();

		client->disconnect();
	}
}

void PlayerImplementation::unload() {
	info("unloading player");

	tradeItems.removeAll();

	for (int i = 0; i < commandQueue.size(); ++i) {
		CommandQueueAction* action = commandQueue.get(i);

		delete action;
	}

	commandQueue.removeAll();

	clearCombatState(); // remove the defenders

	removeEvents();

	PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
	playerManager->updateOtherFriendlists(_this, false);

	// remove from group
	if (group != NULL && zone != NULL) {
		GroupManager* groupManager = server->getGroupManager();
		groupManager->leaveGroup(group, _this);
	}

	// remove from chat rooms
	while (!chatRooms.isEmpty()) {
		ChatRoom* room = chatRooms.get(0);
		room->removePlayer(_this, false);
	}

	// unload mount from world
	if (mount != NULL) {
		MountCreature* mnt = mount;
		mnt->wlock();

		mnt->store(false);

		mnt->unlock();
	}

	savePlayerState();

	if (zone != NULL) {
		ZoneServer* zserver = zone->getZoneServer();

		PlayerManager* playerManager = zserver->getPlayerManager();
		playerManager->unload(_this);

		if (isInQuadTree()) {
			clearDuelList();

			if (isDancing())
				stopDancing();
			else if (isPlayingMusic())
				stopPlayingMusic();

			if (isWatching())
				stopWatch(watchID);

			if (isListening())
				stopListen(listenID);

			clearTarget();

			removeFromZone(true);
			//zone = NULL;
		}
	}
}

void PlayerImplementation::savePlayerState(bool doSchedule) {
	info("saving player state");

	saveWaypoints(_this);

	saveDatapad(_this);

	playerObject->saveFriends();
	playerObject->saveIgnore();

	if (zone != NULL) {
		ZoneServer* zserver = zone->getZoneServer();

		PlayerManager* playerManager = zserver->getPlayerManager();
		playerManager->save(_this);

		ItemManager* itemManager = zserver->getItemManager();
		itemManager->unloadPlayerItems(_this);
	}

	if (playerSaveStateEvent == NULL)
		return;

	if (doSchedule) {
		playerSaveStateEvent->setPlayer(_this);
		server->addEvent(playerSaveStateEvent, 300000);
	} else {
		if (playerSaveStateEvent->isQueued())
			server->removeEvent(playerSaveStateEvent);
		playerSaveStateEvent->setPlayer(NULL);
	}
}

void PlayerImplementation::logout(bool doLock) {
	wlock(doLock);

	if (disconnectEvent == NULL) {
		info("creating disconnect event");

		disconnectEvent = new PlayerDisconnectEvent(_this);

		if (isLoggingOut()) {
			server->addEvent(disconnectEvent, 10);
		} else {
			server->addEvent(disconnectEvent, 1000);
			setLoggingOut();
		}
	}

	unlock(doLock);
}

void PlayerImplementation::userLogout(int msgCounter) {
	if (msgCounter < 0 || msgCounter > 3)
		msgCounter = 3;

	if (!isSitting()) {
		changePosture(CreaturePosture::SITTING);
	}

	if (!isInCombat() && isSitting()) {
		logoutEvent = new PlayerLogoutEvent(_this, msgCounter);

		switch (msgCounter) {
		case 3:
			sendSystemMessage("You can safely log out in 30 seconds...");
			server->addEvent(logoutEvent, 15000);
			break;
		case 2:
			sendSystemMessage("You can safely log out in 15 seconds...");
			server->addEvent(logoutEvent, 10000);
			break;
		case 1:
			sendSystemMessage("You can safely log out in 5 seconds...");
			server->addEvent(logoutEvent, 5000);
			break;
		case 0:  // Disconnect!!!
			info("Safe Logout");

			ClientLogout* packet = new ClientLogout();
			sendMessage(packet);

			delete logoutEvent;
			logoutEvent = NULL;
			break;
		}
	} else {
		if (logoutEvent != NULL) { // we better dont delete the event from where
									//we are running this so we make sure we make it null in event::activate() before calling this
			if (logoutEvent->isQueued())
				server->removeEvent(logoutEvent);

			delete logoutEvent;
			logoutEvent = NULL;
		}

		if (isInCombat())
			sendSystemMessage("Can not log out while in combat.");
		else if (!isSitting())
			sendSystemMessage("You must be sitting to log out.");
	}
}

void PlayerImplementation::disconnect(bool closeClient, bool doLock) {
	try {
		wlock(doLock);

		if (!isOnline()) {
			unlock(doLock);
			return;
		}

		// User is disconnecting in combat.  Will remain LD.
		if (isInCombat() && !isLinkDead()) {
			info("link dead");

			setLinkDead();
		} else {
			info("disconnecting player");

			unload();

			setOffline();
		}

		if (disconnectEvent != NULL)
			disconnectEvent = NULL;

		if (logoutEvent != NULL) {
			server->removeEvent(logoutEvent);
			delete logoutEvent;

			logoutEvent = NULL;
		}

		if (closeClient && owner != NULL) {
			owner->closeConnection();
		}

		owner = NULL;

		unlock(doLock);
	} catch (Exception& e) {
		error("Exception on Player::disconnect()");
		e.printStackTrace();

		clearDisconnectEvent();
		unlock(doLock);
	} catch (...) {
		error("unreported exception on Player::disconnect()");

		clearDisconnectEvent();
		unlock(doLock);
	}
}

void PlayerImplementation::initializeEvents() {
	if (playerSaveStateEvent == NULL)
		playerSaveStateEvent = new PlayerSaveStateEvent(_this);
	else
		playerSaveStateEvent->setPlayer(_this);

	if (recoveryEvent == NULL)
		recoveryEvent = new PlayerRecoveryEvent(_this);
	else
		recoveryEvent->setPlayer(_this);

	if (digestEvent == NULL)
		digestEvent = new PlayerDigestEvent(_this);
	else
		digestEvent->setPlayer(_this);

	if (dizzyFallDownEvent == NULL)
		dizzyFallDownEvent = new DizzyFallDownEvent(this);
}

void PlayerImplementation::removeEvents() {
	/*
	if (reviveCountdownEvent != NULL) {
		if (reviveCountdownEvent->isQueued())
			server->removeEvent(reviveCountdownEvent);

		delete reviveCountdownEvent;
		reviveCountdownEvent = NULL;
	}*/

	if (firstSampleEvent != NULL) {
		if (firstSampleEvent->isQueued())
			server->removeEvent(firstSampleEvent);

		delete firstSampleEvent;
		firstSampleEvent = NULL;
	}

	if (sampleEvent != NULL) {
		if (sampleEvent->isQueued())
			server->removeEvent(sampleEvent);

		delete sampleEvent;
		sampleEvent = NULL;
	}

	if (entertainerEvent != NULL) {
		if (entertainerEvent->isQueued())
			server->removeEvent(entertainerEvent);

		delete entertainerEvent;
		entertainerEvent = NULL;
	}

	if (isInQuadTree()) {
		if (dizzyFallDownEvent != NULL ) {
			if (dizzyFallDownEvent->isQueued())
				server->removeEvent(dizzyFallDownEvent);

			delete dizzyFallDownEvent;
			dizzyFallDownEvent = NULL;
		}

		/*if (reviveCountdownEvent != NULL && reviveCountdownEvent->isQueued()) {
			server->removeEvent(reviveCountdownEvent);

			delete reviveCountdownEvent;
			reviveCountdownEvent = NULL;
		}*/

		if (changeFactionEvent != NULL) {
			server->removeEvent(changeFactionEvent);

			delete changeFactionEvent;
			changeFactionEvent = NULL;
		}
	}
}

void PlayerImplementation::createItems() {
	inventory = new Inventory(_this);

	datapad = new Datapad(_this);

	ItemManager* itemManager = zone->getZoneServer()->getItemManager();
	itemManager->loadDefaultPlayerItems(_this);
	itemManager->loadPlayerDatapadItems(_this);

	if (!hairObject.empty()) {
		hairObj = new HairObject(_this, String::hashCode(hairObject), unicode("hair"), "hair");
		string hairAppearance;
		getHairAppearance(hairAppearance);
		hairObj->setCustomizationString(hairAppearance);
	}
}

void PlayerImplementation::loadItems() {
	inventory = new Inventory(_this);

	datapad = new Datapad(_this);

	ItemManager* itemManager = zone->getZoneServer()->getItemManager();
	itemManager->loadPlayerItems(_this);

	if (!hairObject.empty()) {
		hairObj = new HairObject(_this, String::hashCode(hairObject), unicode("hair"), "hair");
		string hairAppearance;
		getHairAppearance(hairAppearance);
		hairObj->setCustomizationString(hairAppearance);
	}
}

void PlayerImplementation::updateHair() {
	if (hairObj != NULL) {
		if (zone != NULL) {
			//unequipItem(hairObj);
			ZoneServer* zserver = zone->getZoneServer();

			ItemManager* itemManager = zserver->getItemManager();
			removeInventoryItem(hairObj);

			BaseMessage* msg = new SceneObjectDestroyMessage(hairObj);
			broadcastMessage(msg);

			hairObj->finalize();
			hairObj = NULL;
		}
	}

	if (!hairObject.empty()) {
		hairObj = new HairObject(_this, String::hashCode(hairObject), unicode("hair"), "hair");
		string hairAppearance;
		getHairAppearance(hairAppearance);
		hairObj->setCustomizationString(hairAppearance);
		hairObj->sendTo(_this);
		unequipItem(hairObj);
		equipItem(hairObj);
	}
}

void PlayerImplementation::createBaseStats() {
	//TODO: bit hackish, find more clean solution

	int hamValues[9];

	if (startingProfession == "crafting_artisan")
		memcpy(hamValues, professionHams[0], sizeof(hamValues));
	else if (startingProfession == "combat_brawler")
		memcpy(hamValues, professionHams[1], sizeof(hamValues));
	else if (startingProfession == "social_entertainer")
		memcpy(hamValues, professionHams[2], sizeof(hamValues));
	else if (startingProfession == "combat_marksman")
		memcpy(hamValues, professionHams[3], sizeof(hamValues));
	else if (startingProfession == "science_medic")
		memcpy(hamValues, professionHams[4], sizeof(hamValues));
	else if (startingProfession == "outdoors_scout")
		memcpy(hamValues, professionHams[5], sizeof(hamValues));
	else
		memcpy(hamValues, professionHams[6], sizeof(hamValues));

	int race = Races::getRaceID(raceFile);

	// Add the race mods
	int hamMods[9];
	memcpy(hamMods, raceHamMods[race % 10], sizeof(hamMods));

	for (int i = 0; i < 9; i++)
		hamValues[i] += hamMods[i];

	baseHealth = hamValues[0];
	baseStrength = hamValues[1];
	baseConstitution = hamValues[2];
	baseAction = hamValues[3];
	baseQuickness = hamValues[4];
	baseStamina = hamValues[5];
	baseMind = hamValues[6];
	baseFocus = hamValues[7];
	baseWillpower = hamValues[8];
}

void PlayerImplementation::trainStartingProfession() {
	trainSkillBox(startingProfession + "_novice");

	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->loadDefaultSkills(this);
}

void PlayerImplementation::decayInventory() {
	if (inventory != NULL)
		for (int i = 0; i < inventory->objectsSize(); i++) {
			TangibleObject* item = ((TangibleObject*) inventory->getObject(i));

			if (item->isWeapon() && item->isEquipped())
				((Weapon*)item)->decayWeapon(5);
			else if (item->isArmor() && item->isEquipped())
				((Armor*)item)->decayArmor(5);

			item->sendTo(_this);
		}
}

void PlayerImplementation::resetArmorEncumbrance() {
	healthEncumbrance = 0;
	actionEncumbrance = 0;
	mindEncumbrance = 0;

	for (int i=0; i < inventory->objectsSize(); i++) {
		TangibleObject* item = ((TangibleObject*) inventory->getObject(i));

		if (item->isEquipped() && item->isArmor()) {
			item->setEquipped(false);
			unsetArmorSkillMods((Armor*)item);
			changeArmor(item->getObjectID(), true);

		}
	}
}

void PlayerImplementation::sendToOwner() {
	if (faction != 0)
		pvpStatusBitmask |= CreatureFlag::OVERT;

	CreatureObjectImplementation::sendToOwner(_this, false);

	playerObject->sendToOwner();

	sendItemsTo(_this);
	sendPersonalContainers();
	sendGuildList();

	CreatureObjectImplementation::close(owner);

	if (parent != NULL)
		parent->sendTo(_this);
}

void PlayerImplementation::sendTo(Player* player, bool doClose) {
	CreatureObjectImplementation::sendTo(player, false);

	playerObject->sendTo(player);

	if (doClose)
		CreatureObjectImplementation::close(player->getClient());
}

void PlayerImplementation::sendPersonalContainers() {
	//datapad
	datapad->sendTo(_this, false);

	for (int i = 0; i < datapad->objectsSize(); ++i) {
		SceneObject* item = datapad->getObject(i);
		item->sendTo(_this);
	}

	datapad->close(_this);
}

void PlayerImplementation::insertToZone(Zone* zone) {
	PlayerImplementation::zone = zone;

	if (owner == NULL)
		return;

	try {
		zone->lock();

		info("inserting to zone");

		if (parent == NULL) {
			//cout << "Debug Position Cout: Player inserted with cords: " <<  positionX << " " << zone->getHeight(positionX, positionY) << " " << positionY << endl;
			setPosition(positionX, zone->getHeight(positionX, positionY), positionY);
		}

		zone->registerObject(_this);

		owner->balancePacketCheckupTime();

		sendToOwner();

		if (parent != NULL && parent->isCell()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();
			insertToBuilding(building);
			building->notifyInsertToZone(_this);
		} else {
			zone->insert(this);
			zone->inRange(this, 128);
		}

		owner->resetPacketCheckupTime();

		zone->unlock();
	} catch (...) {
		error("exception Player::insertToZone(Zone* zone)");

		zone->unlock();
	}
}

void PlayerImplementation::insertToBuilding(BuildingObject* building, bool doLock) {
	if (owner == NULL || isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("inserting to building");

		((CellObject*)parent)->addChild(_this);

		building->insert(this);
		building->inRange(this, 128);

		//building->unlock(doLock);

		linkType = 0xFFFFFFFF;
		broadcastMessage(link(parent), 128, false);

	} catch (...) {
		error("exception PlayerImplementation::insertToBuilding(BuildingObject* building)");

		//building->unlock(doLock);
	}
}

void PlayerImplementation::reinsertToZone(Zone* zone) {
	try {
		zone->lock();

		info("reinserting to zone");

		owner->balancePacketCheckupTime();

		sendToOwner();

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			notifyInsert(obj);
		}

		owner->resetPacketCheckupTime();

		zone->unlock();
	} catch (...) {
		error("exception Player::reinsertToZone(Zone* zone)");

		zone->unlock();
	}

}

void PlayerImplementation::updateZone(bool lightUpdate) {
	if (zone == NULL || isIncapacitated() || isDead())
		return;

	bool insert = false;

	/*if (zone->getZoneID() == 8) {
		float height = zone->getHeight(positionX, positionY);
		cout << "(" << positionX << "," << height << "," << positionY << "\n";
	}*/

	if (isMounted())
		updateMountPosition();

	try {
		//info("updating player in Zone");

		zone->lock();

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*)parent;

			removeFromBuilding((BuildingObject*)cell->getParent());

			parent = NULL;
			insert = true;
		}

		if (insert)
			zone->insert(this);
		else
			zone->update(this);

		zone->inRange(this, 128);

		if (!isMounted())
			updatePlayerPosition(lightUpdate);

		zone->unlock();

		//info("finished player update in Zone");
	} catch (...) {
		error("exception Player::updateZone()");

		zone->unlock();
	}
}

void PlayerImplementation::updateZoneWithParent(uint64 Parent, bool lightUpdate) {
	if (isMounted())
		dismount(true, true);

	if (zone == NULL)
		return;

	SceneObject* newParent = parent;

	if (parent == NULL || (parent != NULL && parent->getObjectID() != Parent))
		newParent = zone->lookupObject(Parent);

	if (newParent == NULL)
		return;

	bool insert = false;

	try {
		zone->lock();

		if (newParent != parent) {
			if (parent == NULL) {
				zone->remove(this);
				insert = true;
			} else {
				BuildingObject* building = (BuildingObject*) parent->getParent();
				SceneObject* newObj = newParent->getParent();

				if (newObj->isBuilding()) {
					BuildingObject* newBuilding = (BuildingObject*) newObj;

					if (building != newBuilding) {
						removeFromBuilding(building);

						insert = true;
					}
				}

				((CellObject*) parent)->removeChild(_this);
			}
			parent = newParent;
			((CellObject*) parent)->addChild(_this);
		}

		BuildingObject* building = (BuildingObject*) parent->getParent();

		if (insert) {
			insertToBuilding(building, false);
		} else {
			building->update(this);
			building->inRange(this, 128);
		}

		updatePlayerPosition(lightUpdate);

		zone->unlock();
	} catch (...) {
		zone->unlock();
		error("Exception in PlayerImplementation::updateZoneWithParent");
	}
}

void PlayerImplementation::updatePlayerPosition(bool doLightUpdate) {
	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

		if (obj != _this && obj->isPlayer()) {
			Player* player = (Player*) obj;

			if (doLightUpdate) {
				if (parent != NULL && parent->isCell()) {
					LightUpdateTransformWithParentMessage* umsg = new LightUpdateTransformWithParentMessage(_this);
					player->sendMessage(umsg);
				} else {
					LightUpdateTransformMessage* umsg = new LightUpdateTransformMessage(_this);
					player->sendMessage(umsg);
				}
			} else {
				if (parent != NULL && parent->isCell()) {
					UpdateTransformWithParentMessage* umsg = new UpdateTransformWithParentMessage(_this);
					player->sendMessage(umsg);
				} else {
					UpdateTransformMessage* umsg = new UpdateTransformMessage(_this);
					player->sendMessage(umsg);
				}
			}
		}
	}
}

void PlayerImplementation::updateMountPosition() {
	if (parent == NULL || parent != mount)
		return;

	try {
		mount->wlock();

		mount->setDirection(directionX, directionZ, directionY, directionW);
		mount->setPosition(positionX, positionZ, positionY);

		mount->updateZone();

		mount->unlock();
	} catch (...) {
		cout << "Unreported exception in PlayerImplementation::updateMount()\n";
		mount->unlock();
	}
}

void PlayerImplementation::removeFromZone(bool doLock) {
	if (zone == NULL)
		return;

	try {
		zone->lock(doLock);

		info("removing from zone");

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;
			BuildingObject* building = (BuildingObject*)parent->getParent();

			removeFromBuilding(building);
		} else
			zone->remove(this);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->deleteObject(objectID);

		zone->unlock(doLock);
	} catch (...) {
		error("exception Player::removeFromZone(bool doLock)");

		zone->unlock(doLock);
	}
}

void PlayerImplementation::deaggro() {
	// TODO: FIX: this will deadlock if its called with a player from this defender list locked: eg: command handler @summon
	// Temporarly moved to ::load and ::reload till we figure a better solution
	// pre this wlocked
	// post this wlocked
	try {
		if (isInCombat()) {

			SceneObject* scno = NULL;
			Creature* defender = NULL;

			CreatureObject* aggroedCreature = NULL;
			Player* aggroedPlayer = NULL;

			for (int i = 0; i < getDefenderListSize(); ++i) {
				scno = getDefender(i);

				if (scno->isNonPlayerCreature()) {

					defender = (Creature*) scno;
					aggroedCreature = defender->getAggroedCreature();

					if (aggroedCreature != NULL && aggroedCreature->isPlayer()) {

						aggroedPlayer = (Player*) aggroedCreature;

						if (aggroedPlayer->getFirstName() == getFirstName()) {

							try {
								if ((SceneObject*) defender
										!= (SceneObject*) _this)

								defender->wlock(_this);
								defender->deagro();
								defender->removeFromDamageMap(aggroedCreature);
								removeDefender(scno);

								if ((SceneObject*) defender
										!= (SceneObject*) _this)
									defender->unlock();
							} catch (...) {
								if ((SceneObject*) defender
										!= (SceneObject*) _this)
									defender->unlock();
							}
						}
					}
				}

				if (scno->isPlayer()) {
					aggroedPlayer = (Player*) scno;

					try {
						if ((SceneObject*) aggroedPlayer != (SceneObject*) _this)
							aggroedPlayer->wlock(_this);

						aggroedPlayer->removeDefender(_this);
						removeDefender(scno);

						if ((SceneObject*) aggroedPlayer != (SceneObject*) _this)
							aggroedPlayer->unlock();
					} catch (...) {
						if ((SceneObject*) aggroedPlayer != (SceneObject*) _this)
							aggroedPlayer->unlock();
					}

				}

			}

			postureState = CreaturePosture::UPRIGHT;
			updateStates();

		}

	} catch (...) {
		error("unreported exception caught in PlayerImplementation::deaggro()");
	}
}

void PlayerImplementation::removeFromBuilding(BuildingObject* building, bool doLock) {
	if (building == NULL || !isInQuadTree() || !parent->isCell())
		return;

	try {
		//building->lock(doLock);

		info("removing from building");

		broadcastMessage(link(0, 0xFFFFFFFF), 128, false);

		((CellObject*)parent)->removeChild(_this);

		building->remove(this);

		//building->unlock(doLock);
	} catch (...) {
		error("exception PlayerImplementation::removeFromBuilding(BuildingObject* building, bool doLock)");

		//building->unlock(doLock);
	}
}

void PlayerImplementation::notifyInsert(QuadTreeEntry* obj) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	Player* player;
	Creature* creature;
	TangibleObject* tangible;
	StaticObject* statico;
	BuildingObject* buio;

	AttackableObject* attacko;

	if (parent == scno)
		return;

	SceneObject* scnoParent = scno->getParent();

	if (scnoParent != NULL && scnoParent->isNonPlayerCreature())
		return;

	switch (scno->getObjectType()) {
	case SceneObjectImplementation::PLAYER:
		if (objectID == obj->getObjectID())
			break;

		player = (Player*) scno;

		player->sendTo(_this);
		player->sendItemsTo(_this);

		break;
	case SceneObjectImplementation::NONPLAYERCREATURE:
		creature = (Creature*) scno;

		creature->sendTo(_this);
		creature->sendItemsTo(_this);

		break;
	case SceneObjectImplementation::TANGIBLE:
		tangible = (TangibleObject*) scno;
		tangible->sendTo(_this);
		break;

	case SceneObjectImplementation::STATIC:
		statico = (StaticObject*) scno;
		statico->sendTo(_this);
		break;

	case SceneObjectImplementation::BUILDING:
		buio = (BuildingObject*) scno;
		buio->sendTo(_this);
		break;

	case SceneObjectImplementation::ATTACKABLE:
		attacko = (AttackableObject*) scno;
		attacko->sendTo(_this);
		break;
	}
}

void PlayerImplementation::notifyDissapear(QuadTreeEntry* obj) {
	//cout << "PlayerImplementation::notifyDissapear" << endl;

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	Player* player;
	Creature* creature;

	TangibleObject* tano;
	BuildingObject* buio;

	switch (scno->getObjectType()) {
	case SceneObjectImplementation::PLAYER:
		player = (Player*) scno;
		player->sendDestroyTo(_this);

		break;
	case SceneObjectImplementation::NONPLAYERCREATURE:
		creature = (Creature*) scno;
		creature->sendDestroyTo(_this);

		break;

	case SceneObjectImplementation::BUILDING:
		buio = (BuildingObject*) scno;
		buio->sendDestroyTo(_this);
		break;

	case SceneObjectImplementation::TANGIBLE:
		tano = (TangibleObject*) scno;
		tano->sendDestroyTo(_this);

		break;
	}
}

void PlayerImplementation::switchMap(int planetid) {
	if (zone == NULL)
		return;

	if (mount != NULL) {
		MountCreature* mnt = mount;
		mnt->wlock();

		mnt->store(false);

		mnt->unlock();
	}

	removeFromZone();

	parent = NULL;

	setIgnoreMovementTests(5);

	zoneID = planetid;
	ZoneServer* server = zone->getZoneServer();
	Zone* zone = server->getZone(zoneID);

	terrainName = Terrain::getTerrainName(zoneID);

	//reset mission vars:
	misoRFC = 0x01;
	misoBSB = 0;

	insertToZone(zone);
}

void PlayerImplementation::doWarp(float x, float y, float z, float randomizeDistance, uint64 parentID) {
	if (zone == NULL)
		return;

	if (isMounted())
		dismount(true, true);

	removeFromZone();

	parent = NULL;

	setPosition(x, 0, y);

	if (parentID != 0) {
		SceneObject* newParent = zone->lookupObject(parentID);

		if (newParent != NULL && newParent->isCell())
			parent = newParent;
	}

	setIgnoreMovementTests(10);

	if (randomizeDistance != 0)
		randomizePosition(randomizeDistance);

	insertToZone(zone);
}

void PlayerImplementation::bounceBack() {
	if (parent != NULL && parent->isCell()) {
		DataTransformWithParent* trans = new DataTransformWithParent(_this);
		sendMessage(trans);
	} else {
		DataTransform* trans = new DataTransform(_this);
		sendMessage(trans);
	}
}

void PlayerImplementation::notifySceneReady() {
	PlayerObject* playerObject = getPlayerObject();

	if (onlineStatus  == LOGGINGIN) {
		unicode msg = unicode("Welcome to the Official Core3 Test Center!");
		sendSystemMessage(msg);
		unicode msg2 = unicode("Please help us sorting some problems out by being as active as you can. we need to stress the server for these bugs to arise. thank you");
		sendSystemMessage(msg2);

		unicode msg3 = unicode("This server is owned, operated, and developed by Team SWGEmu at SWGEmu.com and is in no way affiliated with any other server communities.");
		sendSystemMessage(msg3);

		unicode msg4 = unicode("Please Report All Spammer, Harassment, Exploits Or Bugs To HTTP://WWW.SWGEMU.COM/SUPPORT.");
		sendSystemMessage(msg4);

		playerObject->loadFriends();
		playerObject->loadIgnore();

		loadGuildChat();


	} else {
		//we need to reset the "magicnumber" for the internal friendlist due to clientbehaviour (Diff. Zoningservers SoE)
		playerObject->friendsMagicNumberReset();
	}

	updateBuffWindow();
	//updateHAMBars();

	ChatManager* chatManager = server->getChatManager();
	chatManager->listMail(_this);

	info("scene ready");
	setOnline();
}

void PlayerImplementation::loadGuildChat() {
	ChatManager* chatManager = server->getChatManager();

	if (chatManager)
		chatManager->sendGuildChat(_this);
	else
		error("Error: PlayerManagerImplementation::loadGuildChat() chatManager is null ");
}

void PlayerImplementation::sendSystemMessage(const string& message) {
	unicode msg(message);
	sendSystemMessage(msg);
}

void PlayerImplementation::sendSystemMessage(const string& file, const string& str, uint64 targetid) {
	ChatSystemMessage* msg = new ChatSystemMessage(file, str, targetid);
	sendMessage(msg);
}

void PlayerImplementation::sendSystemMessage(const string& file, const string& str,StfParameter * param) {
	ChatSystemMessage* msg = new ChatSystemMessage(file, str, param);
	sendMessage(msg);
}

void PlayerImplementation::sendMail(string& mailSender, unicode& subjectSender,
		unicode& bodySender, string& charNameSender) {

	ChatManager * chat=  zone->getChatManager();

	chat->sendMail(mailSender, subjectSender, bodySender, charNameSender);
}

void PlayerImplementation::sendSystemMessage(unicode& message) {
	ChatSystemMessage* smsg = new ChatSystemMessage(message);
	sendMessage(smsg);
}

void PlayerImplementation::sendBattleFatigueMessage(CreatureObject* target) {
	uint32 battleFatigue = target->getShockWounds();

	string targetName = target->getCharacterName().c_str();

	stringstream msgPlayer, msgTarget;

	if (battleFatigue < 250) {
		return;
	} else if (battleFatigue < 500) {
		msgPlayer << targetName << "'s battle fatigue is reducing the effectiveness of the medicine.";
		msgTarget << "Your battle fatigue is reducing the effectiveness of the medicine.";
	} else if (battleFatigue < 750) {
		msgPlayer << targetName << "'s battle fatigue is significantly reducing the effectiveness of the medicine.";
		msgTarget << "Your battle fatigue is significantly reducing the effectiveness of the medicine.";
	} else if (battleFatigue < 1000) {
		msgPlayer << targetName << "'s battle fatigue is greatly reducing the effectiveness of the medicine.";
		msgTarget << "Your battle fatigue is greatly reducing the effectiveness of the medicine. You should seek an entertainer.";
	} else {
		msgPlayer << targetName << "'s battle fatigue is too high for the medicine to do any good.";
		msgTarget << "Your battle fatigue is too high for the medicine to do any good. You should seek an entertainer.";
	}

	target->sendSystemMessage(msgTarget.str());
	if (_this != target)
		sendSystemMessage(msgPlayer.str());
}

void PlayerImplementation::sendHealMessage(CreatureObject* target, int h, int a, int m) {
	//TODO: Revisit this once Stf Concatenation is figured out.

	/*
	StfParameter* stfp = new StfParameter();
	string msgPlayer, msgTarget;

	if (h > 0 && a > 0 && m > 0 ) {
		msgPlayer = "";
		msgTarget = "";
	} else if (h > 0 && a > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else if (h > 0 && m > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else if (a > 0 && m > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else if (h > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else if (a > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else if (m > 0) {
		msgPlayer = "";
		msgTarget = "";
	} else {
		return;
	}

	target->sendSystemMessage("healing_response", msgTarget.str());
	if (_this != target)
		sendSystemMessage("healing_response", msgPlayer.str(), stfp);
	*/

	return;
}

void PlayerImplementation::queueFlourish(const string& modifier, uint64 target, uint32 actionCntr) {
	//TODO: Refactor this part later somehow?
	if (!isPlayer())
		return;

	//PlayerImplementation* player = (PlayerImplementation*) this;

	string skillBox = "social_entertainer_novice";

	if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
		// TODO: sendSystemMessage("cmd_err", "ability_prose", creature);
		sendSystemMessage("You do not have sufficient abilities to Flourish");
		return;
	}

	int fid = atoi(modifier.c_str());

    if (modifier == "") {
    	sendSystemMessage("performance", "flourish_format");
    	return;
    }

    if (fid < 1 || fid > 8) {
    	sendSystemMessage("performance", "flourish_not_valid");
    	sendSystemMessage("performance", "flourish_format");
    	return;
    }

    uint32 actionCRC = String::hashCode("flourish+" + modifier); // get the CRC for flourish+1, etc

    PlayerObject* po = getPlayerObject();
    queueAction(po->getPlayer(), target, actionCRC, actionCntr, modifier);
}


void PlayerImplementation::queueAction(Player* player, uint64 target, uint32 actionCRC, uint32 actionCntr, const string& amod) {
	/*stringstream ident;
	ident << "0x" << hex << actionCRC << " (" << actionCntr << ")";

	sendSystemMessage("queing action " + ident.str());*/

	// Try to queue some music skills
	Skill* skill = creatureSkills.get(actionCRC);

	if ((isDancing() || isPlayingMusic())
		&& (skill != NULL) && !(skill->isEntertainSkill() || skill->isDanceSkill() || skill->isMusicSkill())) {

		player->sendSystemMessage("You cant use skills while dancing/playing music!");
		clearQueueAction(actionCntr);
	} else if (commandQueue.size() < 15) {
		CommandQueueAction* action = new CommandQueueAction(player, target, actionCRC, actionCntr, amod);

		if (!doAction(action))
			delete action;
	} else
		clearQueueAction(actionCntr);

	/*sendSystemMessage("queing action " + ident.str() + " finished");*/

	return;
}

bool PlayerImplementation::doAction(CommandQueueAction* action) {
	CombatManager* combatManager = server->getCombatManager();

	uint32 actionCRC = action->getActionCRC();
	Skill* skill = creatureSkills.get(actionCRC);

	if (skill == NULL) {
		action->clearError(2);
		return false;
	}

	updateTarget(action->getTargetID());

	action->setTarget(targetObject.get());
	action->setSkill(skill);

	if (!action->check())
		return false;

	if (commandQueue.size() != 0 || !nextAction.isPast()) {
		if (commandQueue.size() == 0) {
			CommandQueueActionEvent* e = new CommandQueueActionEvent(_this);
			server->addEvent(e, nextAction);
		}

		commandQueue.add(action);
	} else {
		nextAction.update();

		activateQueueAction(action);

	}

	return true;
}

void PlayerImplementation::activateQueueAction(CommandQueueAction* action) {
	if (!isOnline()) {
		return;
	}

	if (nextAction.isFuture()) {
		Event* e = new CommandQueueActionEvent(_this);
		server->addEvent(e, nextAction);

		return;
	}

	if (action == NULL) {
		if (commandQueue.size() == 0)
			return;

		action = commandQueue.remove(0);
	}

	stringstream msg;
	msg << "activating action " << action->getSkill()->getSkillName() << " " << hex << "0x" << action->getActionCRC() << " ("
		<< action->getActionCounter() << ")";
	info(msg);

	//sendSystemMessage(msg.str());

	CombatManager* combatManager = server->getCombatManager();

	if (!isIncapacitated() && !isDead()) {
		if (action->validate()) {
			float time = combatManager->handleAction(action);
			action->clear(time);
			uint64 ctime = nextAction.getMiliTime();

			nextAction.update();
			nextAction.addMiliTime((uint32) (time * 1000));
		} else {
			action->clearError(1, 19);
		}
	} else {
		action->clearError(1, 19);
	}

	delete action;

	activateRecovery();

	if (commandQueue.size() != 0) {
		Event* e = new CommandQueueActionEvent(_this);

		if (!nextAction.isFuture()) {
			nextAction.update();
			nextAction.addMiliTime(100);
		}

		server->addEvent(e, nextAction);
	}
}

void PlayerImplementation::clearQueueAction(uint32 actioncntr, float timer, uint32 tab1, uint32 tab2) {
	BaseMessage* queuemsg = new CommandQueueRemove(_this, actioncntr, timer, tab1, tab2);
	sendMessage(queuemsg);
}

void PlayerImplementation::deleteQueueAction(uint32 actioncntr) {
	for (int i = 0; i < commandQueue.size(); ++i) {
		CommandQueueAction* action = commandQueue.get(i);

		if (action->getActionCounter() == actioncntr) {
			commandQueue.remove(i);
			delete action;
			break;
		}
	}
}

void PlayerImplementation::doIncapacitate() {
	clearCombatState();

	if (isMounted())
		dismount(true, true);

	if (deathCount == 0) {
		firstIncapacitationTime.update();
		firstIncapacitationTime.addMiliTime(900000);
	} else if (deathCount != 0 && firstIncapacitationTime.isPast()) {
		deathCount = 0;
		firstIncapacitationTime.update();
		firstIncapacitationTime.addMiliTime(900000);
	}

	if (++deathCount < 3) {
		// send incapacitation timer
		CreatureObjectDeltaMessage3* incap = new CreatureObjectDeltaMessage3(_this);
		incap->updateIncapacitationRecoveryTime(8);
		incap->close();

		sendMessage(incap);

		clearStates();
		setPosture(CreaturePosture::INCAPACITATED);

		rescheduleRecovery(8000);
	} else
		kill();
}

void PlayerImplementation::kill() {
	sendSystemMessage("base_player", "victim_dead"); //You have died. Requesting clone activation...
	handleDeath();
}

void PlayerImplementation::deathblow(Player* killer) {
	float currentRating = (float)getPvpRating();
	float opponentRating = (float)killer->getPvpRating();

	string mfaction = (faction == String::hashCode("imperial")) ? "imperial" : "rebel";
	string kfaction = (killer->getFaction() == String::hashCode("imperial")) ? "imperial" : "rebel";


	if (!isInDuelWith(killer) && hatesFaction(killer->getFaction())) {
		subtractFactionPoints(mfaction, 30);
		killer->subtractFactionPoints(mfaction, 45);
		killer->addFactionPoints(kfaction, 45);
	}

	//Using the formula: N = P1 - ( (1/5) * (P1 - P2 + 100) ), where P1 - P2 + 100 >= 0
	int pointsLost = (int)round((1.0f/5.0f) * (currentRating - opponentRating + 100.0f));

	pointsLost = (pointsLost >= 0) ? pointsLost : 0;
	pointsLost = ((currentRating - pointsLost) >= PVPRATING_MIN) ? pointsLost : 0; //Check to be sure that they don't go below the minimum points allowed.

	decreasePvpRating(pointsLost);

	int newRating = getPvpRating();

	stringstream defeatedMsg;

	string killerName = "";
	unicode uniName = unicode("");
	uniName = killer->getCharacterName();
	killerName = uniName.c_str();

	if (pointsLost > 0) {
		switch (System::random(2)) {
		case 0:
			defeatedMsg << "You have been killed by " << killerName.c_str() << ". Your new player combat rating is " << newRating << ".";
			break;
		case 1:
			defeatedMsg << "You have fallen prey to " << killerName.c_str() << ". Your new player combat rating is " << newRating << ".";
			break;
		case 2:
		default:
			defeatedMsg << "You have perished at the hand of " << killerName.c_str() << ". Your new player combat rating is " << newRating << ".";
			break;
		}
	} else {
		defeatedMsg << "Although you have fallen at the hands of " << killerName.c_str() << ",  your cannot lose any more rating points at this time.  Your player combat rating remains at " << newRating << ".";
	}

	//TODO: awardFactionPoints(); Only if both players are overt.

	sendSystemMessage("base_player", "prose_victim_dead", killer->getObjectID()); //You were slain by %TT. Requesting clone activation...

	sendSystemMessage(defeatedMsg.str());

	clearDuelList();
	handleDeath();
}

/*
void PlayerImplementation::throttlePvpRating(Player* player) {
	 *
	 * TODO: When a player is killed, they should be added to that players recently killed list so that no points are awarded.
	 *
}*/

void PlayerImplementation::handleDeath() {
	setPosture(CreaturePosture::DEAD);
	deathCount = 0;
	rescheduleRecovery(3000);
}

void PlayerImplementation::changePosture(int post) {
	if (logoutEvent != NULL) {
		if (post == CreaturePosture::SITTING) {
			clearQueueAction(actionCounter);
			return;
		}

		sendSystemMessage("Logout canceled.");
		server->removeEvent(logoutEvent);
		delete logoutEvent;

		logoutEvent = NULL;
	}

	if (!getCanSample() && !getCancelSample()) {
		sendSystemMessage("You stop taking resource samples.");

		if (firstSampleEvent != NULL && firstSampleEvent->isQueued()) {
			server->removeEvent(firstSampleEvent);

			delete firstSampleEvent;
			firstSampleEvent = NULL;
		}

		if (sampleEvent != NULL) {
			uint64 time = -(sampleEvent->getTimeStamp().miliDifference());
			if (sampleEvent->isQueued())
				server->removeEvent(sampleEvent);

			delete sampleEvent;
			sampleEvent = NULL;

			string str = "";
			sampleEvent = new SampleEvent(_this, str, true);
			server->addEvent(sampleEvent, time);
			setCancelSample(true);
		}
	}

	if (isMounted())
		return;

	if (hasAttackDelay()) {
		clearQueueAction(actionCounter);
		return;
	}

	if (meditating) {
		updateMood(Races::getMood(moodid));
		meditating = false;
		sendSystemMessage("teraskasi", "med_end");
	}

	if (isInCombat() && post == CreaturePosture::SITTING) {
		clearQueueAction(actionCounter);
		return;
	}

	if (isDizzied() && post == CreaturePosture::UPRIGHT) {
		if ((getSkillMod("combat_equillibrium") >> 1) > System::random(100)) {
			if (!dizzyFallDownEvent->isQueued())
				server->addEvent(dizzyFallDownEvent, 100);
			setPosture(post, true);
		} else {
			setPosture(CreaturePosture::KNOCKEDDOWN, true);
			sendSystemMessage("cbt_spam", "dizzy_fall_down_single");
		}
	} else
		setPosture(post);

	clearQueueAction(actionCounter);
}

void PlayerImplementation::activateRecovery() {
	if (!recoveryEvent->isQueued())
		server->addEvent(recoveryEvent, 3000);
}

void PlayerImplementation::rescheduleRecovery(int time) {
	if (recoveryEvent->isQueued())
		server->removeEvent(recoveryEvent);

	server->addEvent(recoveryEvent, time);
}

void PlayerImplementation::doRecovery() {
	if (isLinkDead()) {
		if (logoutTimeStamp.isPast()) {
			info("unloading dead linked player");

			unload();

			setOffline();

			return;
		} else {
			info("keeping dead linked player in game");

			activateRecovery();
		}
	}

	if (isIncapacitated()) {
		speed = 5.376;

		setPosture(CreaturePosture::UPRIGHT);
	} else if (isDead()) {
		activateClone();
		//activateReviveCountdown(); TODO: Fix the revive countdown timer issue.
		return;
	}


	if (!isInCombat() && isOnFullHealth() && ((playerObject != NULL && isJedi() && playerObject->isOnFullForce()) || !isJedi()) && !hasStates() && !hasWounds() && !hasShockWounds()) {
		return;
	} else if (lastCombatAction.miliDifference() > 15000) {
		clearCombatState();
	} else if (isInCombat() && targetObject != NULL && !hasState(CreatureState::PEACE)
			&& (commandQueue.size() == 0)) {
		queueAction(_this, getTargetID(), 0xA8FEF90A, ++actionCounter, "");
	}

	if (!isOnFullHealth() || hasWounds() || hasShockWounds())
		calculateHAMregen();

	if (hasStates())
		doStateRecovery();

	if (isJedi())
		calculateForceRegen();

	activateRecovery();
}


void PlayerImplementation::resurrect() {
	uint32 boxID = getSuiBoxFromType(0xC103); //Activate Clone SuiBox

	if (hasSuiBox(boxID)) {
		SuiBox* sui = getSuiBox(boxID);
		sendMessage(sui->generateCloseMessage());
		removeSuiBox(boxID);
		sui->finalize();
	}
	changePosture(CreaturePosture::UPRIGHT);
}

void PlayerImplementation::clearReviveCountdown() {
	reviveTimeout.update();

	if (reviveCountdownEvent != NULL && reviveCountdownEvent->isQueued()) {
		server->removeEvent(reviveCountdownEvent);

		delete reviveCountdownEvent;
		reviveCountdownEvent = NULL;
	}
}

void PlayerImplementation::activateReviveCountdown() {
	int minutes = 5;

	reviveTimeout.update();
	reviveTimeout.addMiliTime(minutes * 60 * 1000);

	countdownRevive(minutes);
}

void PlayerImplementation::countdownRevive(int counter) {
	stringstream message;
	int seconds = 60; //How long in between message delays.

	if (!isRevivable() && counter >= 0) {
		counter = 0;
	}

	switch (counter) {
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
		message << "You have " << counter << " minutes remaining to be revived.";
		break;
	case 0:
		message << "Your chance for resuscitation has expired. You have one minute to select a cloning facility, or one will be automatically chosen.";
		break;
	default:
		break;
	}

	sendSystemMessage(message.str());

	if (counter >= 0) {

		--counter;

		if (reviveCountdownEvent != NULL && reviveCountdownEvent->isQueued()) {
			server->removeEvent(reviveCountdownEvent);

			delete reviveCountdownEvent;
			reviveCountdownEvent = NULL;
		}

		reviveCountdownEvent = new ReviveCountdownEvent(this, counter, seconds);
		server->addEvent(reviveCountdownEvent);
	} else {
		if (!hasSuiBox(0xC103))
			doClone();
	}
}

void PlayerImplementation::doStateRecovery() {
	if (isDizzied() && dizzyRecoveryTime.isPast())
		clearState(CreatureState::DIZZY);

	if (isBlinded() && blindRecoveryTime.isPast())
		clearState(CreatureState::BLINDED);

	if (isStunned() && stunRecoveryTime.isPast())
		clearState(CreatureState::STUNNED);

	if (isIntimidated() && intimidateRecoveryTime.isPast())
		clearState(CreatureState::INTIMIDATED);

	if (isPoisoned()) {
		if (poisonRecoveryTime.isPast())
			clearState(CreatureState::POISONED);
		else doPoisonTick();
	}

	if (isDiseased()) {
		if (diseasedRecoveryTime.isPast())
			clearState(CreatureState::DISEASED);
		else doDiseaseTick();
	}

	if (isOnFire()) {
		if (fireRecoveryTime.isPast())
			clearState(CreatureState::ONFIRE);
		else doFireTick();
	}

	if (isBleeding()) {
		if (bleedingRecoveryTime.isPast())
			clearState(CreatureState::BLEEDING);
		else doBleedingTick();
	}

	updateStates();
}

void PlayerImplementation::activateDigest() {
	if (!digestEvent->isQueued())
		server->addEvent(digestEvent, 18000);
}

void PlayerImplementation::doDigest() {
	if(playerObject == NULL)
		return;

	if (!playerObject->isDigesting())
		return;

	if(playerObject->getFoodFilling() > 0)
		playerObject->changeFoodFilling(-1, true);

	if(playerObject->getDrinkFilling() > 0)
		playerObject->changeDrinkFilling(-1, true);

	activateDigest();
}

void PlayerImplementation::activateClone() {
	if (hasSuiBoxType(0xC103)) {
		int boxID = getSuiBoxFromType(0xC103);
		SuiListBox* sui = (SuiListBox*) getSuiBox(boxID);

		if (sui != NULL) {
			sendMessage(sui->generateCloseMessage());
			removeSuiBox(boxID);
			sui->finalize();
		}
	}

	SuiListBox* cloneMenu = new SuiListBox(_this, 0xC103);

	cloneMenu->setPromptTitle("@base_player:revive_title");

	string clonerName = "Mos Eisley";

	//TODO: Integrate this menu with cloning system.

	stringstream promptText;
	promptText << "Closest:\t\t\t" << clonerName << "\n"
			   << "Pre-Designated: \t" << clonerName << "\n" //Space before tab character is needed for proper formatting in this case.
			   << "Cash Balance:\t\t" << getCashCredits() << "\n\n"
			   << "Select the desired option and click OK.";

	cloneMenu->setPromptText(promptText.str());

	cloneMenu->addMenuItem("@base_player:revive_closest");
	cloneMenu->addMenuItem("@base_player:revive_bind");

	addSuiBox(cloneMenu);
	sendMessage(cloneMenu->generateMessage());
}

void PlayerImplementation::doClone() {
	info("cloning player");

	//clearReviveCountdown();

	clearStates();
	clearBuffs(true);
	resetArmorEncumbrance();

	//TODO: This should check to see if the data is stored at the cloning facility or not, these numbers are much less if so.

	changeHealthWoundsBar(100);
	changeActionWoundsBar(100);
	changeMindWoundsBar(100);
	//TODO: Add in secondary wounds?
	changeShockWounds(100);

	switch (zoneID) {
	case 0:	// Corellia
		if (faction == String::hashCode("rebel"))
			doWarp(-326.0f, -4640.0f);				// shuttle 1
		else
			doWarp(-28.0f, -4438.0f);				// shuttle 2

		break;
	case 1:	// Dantooine
		if (faction == String::hashCode("rebel"))			// Mining Outpost
			doWarp(4.3f, 0.1, 3.8f, 0, 1365997);
		else
 			doWarp(4.3f, 0.1, 3.8f, 0, 1365997);

 		break;
	case 2: // Dathomir
		if (faction == String::hashCode("rebel"))			// science outpost
			doWarp(-76.0f, -1627.0f);
		else
			doWarp(618.0f, 3054.0f);						// trade outpost

		break;
	case 3: // Endor
		if (faction == String::hashCode("rebel"))
			doWarp(3.9f, 0.1f, 3.7f, 0, 6705359);
		else
 			doWarp(3.9f, 0.1f, 3.6f, 0, 6705359);

 		break;
	case 4: // Lok
		if (faction == String::hashCode("rebel"))			// Nyms Stronghold
			doWarp(0.3f, 0.3f, 1.2f, 0, 2745624);
		else
 			doWarp(0.3f, 0.3f, 1.2f, 0, 2745624);

 		break;
	case 5: // Naboo
		if (faction == String::hashCode("rebel"))			// Theed
			doWarp(1.7f, -4.8f, 0.1f, 0, 1697354);
		else
 			doWarp(1.7f, -4.8f, 0.1f, 0, 1697354);

 		break;
	case 6: // Rori
		if (faction == String::hashCode("rebel"))			// Restuss
			doWarp(1.7f, -4.8f, 0.7f, 0, 4695371);
		else
 			doWarp(1.7f, -4.8f, 0.7f, 0, 4695371);

 		break;
	case 7: // Talus
		if (faction == String::hashCode("rebel"))			//  Daeric
			doWarp(1.8f, -4.8f, 0.6f, 0, 3175408);
		else
 			doWarp(1.8f, -4.8f, 0.6f, 0, 3175408);

 		break;
	case 9: // Yavin4
		if (faction == String::hashCode("rebel"))			//  Labor Camp
			doWarp(4.3f, 0.1f, -3.7f, 0, 3035395);
		else
 			doWarp(4.3f, 0.1f, -3.7f, 0, 3035395);

 		break;
	default:
		if (faction == String::hashCode("rebel"))
			doWarp(-130.0f, -5300.0f);
		else if (faction == String::hashCode("imperial"))
     		//doWarp(10.0f, -5480.0f, 0, true);
			doWarp(-2.8f, 0.1f, -4.8f, 0, 3565798);
		else
			doWarp(0.5f, 1.5f, 0.3f, 0, 1590892); // ah cloning facility

		break;
	}

	//food persists cloning
	//setFoodFilling(0, true);
	//setDrinkFilling(0, true);

	decayInventory();

	changeForcePowerBar(0);

	if (isOvert())
		setCovert();

	setPosture(CreaturePosture::UPRIGHT);

	rescheduleRecovery();
}


void PlayerImplementation::sendConsentBox() {
	if (consentList.size() <= 0) {
		sendSystemMessage("You have yet to give anyone your consent.");
		return;
	}

	if (hasSuiBoxType(0xC057)) {
		int boxID = getSuiBoxFromType(0xC057);
		SuiListBox* sui = (SuiListBox*) getSuiBox(boxID);

		if (sui != NULL) {
			sendMessage(sui->generateCloseMessage());
			removeSuiBox(boxID);
			sui->finalize();
		}
	}

	SuiListBox* consentBox = new SuiListBox(_this, 0xC057);

	consentBox->setPromptTitle("Consent List");
	consentBox->setPromptText("Below is listed all players whom you have given consent.");

	for (int i=0; i < consentList.size(); i++) {
		string entryName = consentList.get(i);
		if (!entryName.empty())
			consentBox->addMenuItem(entryName);
	}

	addSuiBox(consentBox);
	sendMessage(consentBox->generateMessage());
}

void PlayerImplementation::doPowerboost() {
	if (powerboosted) {
		sendSystemMessage("teraskasi", "powerboost_active");
		return;
	}

	int duration = 0;

	if (!meditating) {
		sendSystemMessage("teraskasi", "powerboost_fail");
		return;
	}

	string txt0 = "combat_unarmed_accuracy_02";
	string txt1 = "combat_unarmed_master";

	if (hasSkillBox(txt1))
		// ToDo: Master duration modifier is missing in the packet?
		// TKM should have 10 Minutes powerboost but the client sends only 5 minute powerboost at master as well
		//duration = 600000;

		duration = 300000;

	else if (hasSkillBox(txt0))
		duration = 300000;

	//Fire the "begin"-event
	sendSystemMessage("teraskasi", "powerboost_begin");

	//Queue the "wane"-event
	server->addEvent(powerboostEventWane, duration-60000);

	//Queue the "...come to an end"-event
	server->addEvent(powerboostEventEnd, duration);

	powerboosted = true;
}



void PlayerImplementation::doCenterOfBeing() {
	if (centered) {
		sendSystemMessage("combat_effects", "already_centered");
		return;
	}

	int duration = 0;
	int efficacy = 0;

	if (weaponObject == NULL) {
		duration = getSkillMod("center_of_being_duration_unarmed");
		efficacy = getSkillMod("unarmed_center_of_being_efficacy");
	} else {
		switch (weaponObject->getType()) {
		case WeaponImplementation::UNARMED:
			duration = getSkillMod("center_of_being_duration_unarmed");
			efficacy = getSkillMod("unarmed_center_of_being_efficacy");
			break;

		case WeaponImplementation::ONEHANDED:
			duration = getSkillMod("center_of_being_duration_onehandmelee");
			efficacy = getSkillMod("onehandmelee_center_of_being_efficacy");
			break;

		case WeaponImplementation::TWOHANDED:
			duration = getSkillMod("center_of_being_duration_twohandmelee");
			efficacy = getSkillMod("twohandmelee_center_of_being_efficacy");
			break;

		case WeaponImplementation::POLEARM:
			duration = getSkillMod("center_of_being_duration_polearm");
			efficacy = getSkillMod("polearm_center_of_being_efficacy");
			break;
		default:
			break;
		}
	}

	if (duration == 0 || efficacy == 0)
		return;

	//defenseBonus += efficacy;
	centeredBonus = efficacy;

	showFlyText("combat_effects", "center_start_fly", 0, 255, 0);

	server->addEvent(centerOfBeingEvent, duration * 1000);

	centered = true;
}

void PlayerImplementation::removeCenterOfBeing() {
	if (!centered)
		return;

	server->removeEvent(centerOfBeingEvent);

	//defenseBonus -= centeredBonus;
	centeredBonus = 0;

	showFlyText("combat_effects", "center_stop_fly", 255, 0, 0);
	centered = false;
}

void PlayerImplementation::doPeace() {
	//info("trying Peace action");

	for (int i = 0; i < defenderList.size(); ++i) {
		ManagedReference<SceneObject> defender = defenderList.get(i);

		try {
			defender->wlock(_this);

			if (defender->hasDefender(_this)) {
				if (defender->isPeaced()) {
					removeDefender(defender);
					defender->removeDefender(_this);

					i--;
				}
			} else {
				removeDefender(defender);
				i--;
			}

			defender->unlock();

		} catch (...) {
			error("unknown exception in PlayerImplementation::doPeace()\n");
			defender->unlock();
		}

	}

	if (defenderList.size() != 0) {
		//info("defenderList not empty, trying to set Peace State");

		if (setState(CreatureState::PEACE))
			updateStates();
	}

	//info("finished doPeace");
}

void PlayerImplementation::lootCorpse(bool lootAll) {
	if (targetObject == NULL || !targetObject->isNonPlayerCreature())
		return;

	Creature* target = (Creature*) targetObject.get();

	if (target->isMount())
		return;

	if (!isIncapacitated() && !isDead() && isInRange(target, 20)) {
		LootManager* lootManager = server->getLootManager();

		if (lootAll)
			lootManager->lootCorpse(_this, target);
		else
			lootManager->showLoot(_this, target);
	}
}

void PlayerImplementation::lootObject(Creature* creature, SceneObject* object) {
	if (creature->isMount())
		return;

	LootManager* lootManager = server->getLootManager();

	lootManager->lootObject(_this, creature, object->getObjectID());
}

void PlayerImplementation::calculateForceRegen() {
	if (isJedi() && !playerObject->isOnFullForce()) {
		if (getPosture() == CreaturePosture::SITTING)
			changeForcePowerBar(playerObject->getForceRegen()); // probably shouldn't be here *shrug*
		else // 3 second tick do a full regen every 10 secs ish
			changeForcePowerBar( (int)((playerObject->getForceRegen() / 3.0) + .5));
	}
}

bool PlayerImplementation::changeForcePowerBar(int32 fp) {
	int32 newForce = playerObject->getForcePower() + fp;

	if (newForce <= 0)
		return false;

	setForcePowerBar(MIN(newForce, playerObject->getForcePowerMax()));

	if(fp < 0)
		activateRecovery();

	return true;
}

void PlayerImplementation::addBuff(uint32 buffcrc, float time) {
	Buffs* bf = new Buffs(_this, buffcrc, time);
	sendMessage(bf);
}

// TODO: clearBuffs
void PlayerImplementation::clearBuffs(bool doUpdatePlayer) {
	// Clear buff icons
	/*
	if (doUpdatePlayer) {
		if (healthBuff)
			addBuff(0x98321369, 0.0f);

		if (strengthBuff)
			addBuff(0x815D85C5, 0.0f);

		if (constitutionBuff)
			addBuff(0x7F86D2C6, 0.0f);

		if (actionBuff)
			addBuff(0x4BF616E2, 0.0f);

		if (quicknessBuff)
			addBuff(0x71B5C842, 0.0f);

		if (staminaBuff)
			addBuff(0xED0040D9, 0.0f);

		if (mindBuff)
			addBuff(0x11C1772E, 0.0f);

		if (focusBuff)
			addBuff(0x2E77F586, 0.0f);

		if (willpowerBuff)
			addBuff(0x3EC6FCB6, 0.0f);

	}

	healthBuff = false;
	strengthBuff = false;
	constitutionBuff = false;
	actionBuff = false;
	quicknessBuff = false;
	staminaBuff = false;
	mindBuff = false;
	focusBuff = false;
	willpowerBuff = false; */

	removeBuffs(doUpdatePlayer);
}

/*
*
*		GM METHODS
*
*/
void PlayerImplementation::mutePlayer() {
	chatMuted = !chatMuted;
}

void PlayerImplementation::toggleImmune() {
	if (!immune) {
		clearDuelList();
		clearCombatState();
		setPvpStatusBitmask(0);
		sendSystemMessage("You are now immune to attacks.");
	} else {
		setPvpStatusBitmask(CreatureFlag::PLAYER);
		sendSystemMessage("You are no longer immune to attacks.");
	}

	immune = !immune;

	UpdatePVPStatusMessage * mess = new UpdatePVPStatusMessage(this, pvpStatusBitmask);
	broadcastMessage(mess);
}


/*
 *	Item manipulation methods
 */

void PlayerImplementation::addInventoryItem(TangibleObject* item) {

	CreatureObjectImplementation::addInventoryItem(item);

	if(item->isEquipped())
		equipPlayerItem(item);

}

void PlayerImplementation::addInventoryResource(ResourceContainer* item) {

	CreatureObjectImplementation::addInventoryResource(item);
}


void PlayerImplementation::equipPlayerItem(TangibleObject* item) {
	if (item->isEquipped())
		item->setEquipped(false);

	if (item->isWeapon()) {
		changeWeapon(item->getObjectID());
	} else if (item->isArmor()) {
		changeArmor(item->getObjectID(), true);
	} else if (item->isClothing()) {
		changeCloth(item->getObjectID());
	} else if (item->isInstrument()) {
		changeWeapon(item->getObjectID());
	}
}

bool PlayerImplementation::hasItemPermission(TangibleObject * item) {
	uint16 maskRes = ~(item->getPlayerUseMask()) & characterMask;

	if (maskRes == 0)
		return true;
	else if (maskRes == COVERT) {
		this->sendSystemMessage("You can not use this item while on leave.");
		return false;
	} else if (maskRes & (COVERT | REBEL | IMPERIAL | NEUTRAL)) {
		this->sendSystemMessage("You are not the proper faction to use this item.");
		return false;
	} else if (maskRes & 0x0FFC) {
		this->sendSystemMessage("Your species can not use this item.");
		return false;
	} else if (maskRes & (MALE | FEMALE)) {
		this->sendSystemMessage("This item is not appropriate for your gender.");
		return false;
	}

	//should never get here
	this->sendSystemMessage("There was an error, while trying to equip this item.");
	return false;
}
void PlayerImplementation::changeCloth(uint64 itemid) {
	SceneObject* obj = inventory->getObject(itemid);

	if (obj == NULL || !obj->isTangible())
		return;

	TangibleObject* cloth = (TangibleObject*) obj;

	if(!hasItemPermission(cloth) && !cloth->isEquipped())
		return;

	if (cloth->isWeapon()) {
		if (cloth->isEquipped())
			changeWeapon(itemid);
		return;
	}

	if (cloth->isArmor()) {
		if (cloth->isEquipped())
			changeArmor(itemid, false);
		return;
	}

	if (cloth->isEquipped()) {
		unequipItem(cloth);
	} else {
		equipItem(cloth);
	}
}

void PlayerImplementation::changeWeapon(uint64 itemid) {
	SceneObject* obj = inventory->getObject(itemid);

	if (obj == NULL || !obj->isTangible())
		return;



	if (isPlayingMusic())
		stopPlayingMusic();

	if (((TangibleObject*)obj)->isWeapon()) {

		Weapon* weapon = (Weapon*) obj;

		if (weapon == NULL)
			return;

		if (!this->hasItemPermission(weapon) && !weapon->isEquipped())
			return;

		if (centered)
			removeCenterOfBeing();

		if (weapon->isEquipped()) {
			unequipItem(weapon);
			unsetWeaponSkillMods(weapon);
			setWeapon(NULL);

			accuracy = getSkillMod("unarmed_accuracy");
		} else {
			if (weaponObject != NULL) {
				unequipItem(weaponObject);
				unsetWeaponSkillMods(weaponObject);
			}

			setWeapon(weapon);
			equipItem(weapon);

			setWeaponSkillMods(weapon);
		}
	} else if (((TangibleObject*)obj)->isInstrument()){

		Instrument* device = (Instrument*) obj;
		int instrument = device->getInstrumentType();

		string skillBox;
		// Needs to be refactored
		switch(instrument)
		{
		case InstrumentImplementation::SLITHERHORN: //SLITHERHORN
			skillBox = "social_entertainer_novice";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::FIZZ: // FIZZ
			skillBox = "social_entertainer_music_01";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::FANFAR: // FANFAR
			skillBox = "social_entertainer_music_03";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::KLOOHORN: // KLOOHORN
			skillBox = "social_entertainer_music_04";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::MANDOVIOL: // MANDOVIOL
			skillBox = "social_entertainer_master";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::TRAZ: // TRAZ
			skillBox = "social_musician_novice";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::BANDFILL: // BANDFILL
			skillBox = "social_musician_knowledge_02";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::FLUTEDROOPY: // FLUTEDROOPY
			skillBox = "social_musician_knowledge_03";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::OMNIBOX: // OMNIBOX
			skillBox = "social_musician_knowledge_04";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		case InstrumentImplementation::NALARGON: // NALARGON
			skillBox = "social_musician_master";
			if (!getSkillBoxesSize() || !hasSkillBox(skillBox)) {
				sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
				return;
			}
			break;
		default :
			sendSystemMessage("You do not have sufficient abilities to equip " + device->getName().c_str() + ".");
			return;
		}

		TangibleObject* item = (TangibleObject*) obj;

		if (isPlayingMusic())
			stopPlayingMusic();

		if (item->isEquipped()) {
			unequipItem(item);
		}
		else
			equipItem(item);
	} else {
		TangibleObject* item = (TangibleObject*) obj;

		sendSystemMessage("triggered here.");
		if (item->isEquipped())
			unequipItem(item);
		else
			equipItem(item);
	}
}

void PlayerImplementation::changeArmor(uint64 itemid, bool forced) {
	SceneObject* obj = inventory->getObject(itemid);

	if (obj == NULL || !obj->isTangible())
		return;

	if (((TangibleObject*)obj)->isArmor()) {
		Armor* armoritem = (Armor*) obj;

		if (armoritem == NULL)
			return;

		if(!hasItemPermission(armoritem) && !armoritem->isEquipped())
			return;

		if (armoritem->isEquipped()) {
			unequipItem((TangibleObject*) obj);
			unsetArmorSkillMods(armoritem);
			unsetArmorEncumbrance(armoritem);
		} else {
			Armor* olditem = getArmor(armoritem->getType());

			if (olditem != NULL) {
				unsetArmorSkillMods(olditem);
				unsetArmorEncumbrance(olditem);
				unequipItem((TangibleObject*) olditem);
			}

			if (setArmorEncumbrance(armoritem, forced)) {
				equipItem((TangibleObject*) obj);
				setArmorSkillMods(armoritem);
			} else
				sendSystemMessage("You don't have enough pool points to do that!");
		}
	} else {
		TangibleObject* item = (TangibleObject*) obj;

		if (item->isEquipped())
			unequipItem(item);
		else
			equipItem(item);
	}

	BaseMessage* creo6 = new CreatureObjectMessage6(_this);
	BaseMessage* creo4 = new CreatureObjectMessage4(this);

	sendMessage(creo6);
	sendMessage(creo4);
}

void PlayerImplementation::setItemSkillMod(int type, int value) {
	switch (type) {
	case 1:
		addSkillModBonus("melee_defense", value, true);
		break;
	case 2:
		addSkillModBonus("ranged_defense", value, true);
		break;
	case 3:
		addSkillModBonus("stun_defense", value, true);
		break;
	case 4:
		addSkillModBonus("dizzy_defense", value, true);
		break;
	case 5:
		addSkillModBonus("blind_defense", value, true);
		break;
	case 6:
		addSkillModBonus("knockdown_defense", value, true);
		break;
	case 7:
		addSkillModBonus("intimidate_defense", value, true);
		break;
	case 8:
		addSkillModBonus("pistol_speed", value, true);
		break;
	case 9:
		addSkillModBonus("carbine_speed", value, true);
		break;
	case 10:
		addSkillModBonus("rifle_speed", value, true);
		break;
	case 11:
		addSkillModBonus("unarmed_speed", value, true);
		break;
	case 12:
		addSkillModBonus("onehandmelee_speed", value, true);
		break;
	case 13:
		addSkillModBonus("twohandmelee_speed", value, true);
		break;
	case 14:
		addSkillModBonus("polearm_speed", value, true);
		break;
	case 15:
		addSkillModBonus("pistol_accuracy", value, true);
		break;
	case 16:
		addSkillModBonus("carbine_accuracy", value, true);
		break;
	case 17:
		addSkillModBonus("rifle_accuracy", value, true);
		break;
	case 18:
		addSkillModBonus("unarmed_accuracy", value, true);
		break;
	case 19:
		addSkillModBonus("onehandmelee_accuracy", value, true);
		break;
	case 20:
		addSkillModBonus("twohandmelee_accuracy", value, true);
		break;
	case 21:
		addSkillModBonus("polearm_accuracy", value, true);
		break;
	case 22:
		addSkillModBonus("dodge", value, true);
		break;
	case 23:
		addSkillModBonus("block", value, true);
		break;
	case 24:
		addSkillModBonus("counterattack", value, true);
		break;
	case 25:
		addSkillModBonus("resistance_bleeding", value, true);
		break;
	case 26:
		addSkillModBonus("resistance_disease", value, true);
		break;
	case 27:
		addSkillModBonus("resistance_fire", value, true);
		break;
	case 28:
		addSkillModBonus("resistance_poison", value, true);
		break;
	case 29:
		addSkillModBonus("slope_move", value, true);
		break;
	case 30:
		addSkillModBonus("heavyweapon_speed", value, true);
		break;
	case 31:
		addSkillModBonus("heavyweapon_accuracy", value, true);
		break;
	}
}

void PlayerImplementation::setWeaponSkillMods(Weapon* weapon) {
	switch (weapon->getType()) {
		case WeaponImplementation::UNARMED:
			accuracy = getSkillMod("unarmed_accuracy");
			break;

		case WeaponImplementation::ONEHANDED:
			accuracy = getSkillMod("onehandmelee_accuracy");
			break;

		case WeaponImplementation::TWOHANDED:
			accuracy = getSkillMod("twohandmelee_accuracy");
			break;

		case WeaponImplementation::POLEARM:
			accuracy = getSkillMod("polearm_accuracy");
			break;

		case WeaponImplementation::PISTOL:
			accuracy = getSkillMod("pistol_accuracy");
			break;

		case WeaponImplementation::CARBINE:
			accuracy = getSkillMod("carbine_accuracy");
			break;

		case WeaponImplementation::RIFLE:
			accuracy = getSkillMod("rifle_accuracy");
			break;

		case WeaponImplementation::HEAVYWEAPON:
			accuracy = getSkillMod("heavyweapon_accuracy");
			break;

		case WeaponImplementation::SPECIALHEAVYWEAPON:
			if (weapon->getType() == WeaponImplementation::RIFLEFLAMETHROWER)
				accuracy = getSkillMod("heavy_flame_thrower_accuracy");

			else if (weapon->getType() == WeaponImplementation::RIFLELIGHTNING)
				accuracy = getSkillMod("heavy_rifle_lightning_accuracy");

			accuracy += getSkillMod("heavyweapon_accuracy");
			break;

		/*case Weapon::ONEHANDSABER:
			accuracy = SkillMods.get("");
			break;

		case Weapon::TWOHANDSABER:
			accuracy = SkillMods.get("");
			break;

		case Weapon::POLEARMSABER:
			accuracy = SkillMods.get("");
			break;*/
	}
	setItemSkillMod(weapon->getSkillMod0Type(), weapon->getSkillMod0Value());
	setItemSkillMod(weapon->getSkillMod1Type(), weapon->getSkillMod1Value());
	setItemSkillMod(weapon->getSkillMod2Type(), weapon->getSkillMod2Value());

	if (checkCertification(weapon->getCert())) {
		weapon->setCertified(true);
	} else {
		sendSystemMessage("You are not certified to use this weapon. Damage will be reduced.");
		weapon->setCertified(false);
	}
}

void PlayerImplementation::setArmorSkillMods(Armor* armoritem) {
	setItemSkillMod(armoritem->getSkillMod0Type(), armoritem->getSkillMod0Value());
	setItemSkillMod(armoritem->getSkillMod1Type(), armoritem->getSkillMod1Value());
	setItemSkillMod(armoritem->getSkillMod2Type(), armoritem->getSkillMod2Value());

	setItemSkillMod(armoritem->getSocket0Type(), armoritem->getSocket0Value());
	setItemSkillMod(armoritem->getSocket1Type(), armoritem->getSocket1Value());
	setItemSkillMod(armoritem->getSocket2Type(), armoritem->getSocket2Value());
	setItemSkillMod(armoritem->getSocket3Type(), armoritem->getSocket3Value());

}

void PlayerImplementation::unsetArmorSkillMods(Armor* armoritem) {
	setItemSkillMod(armoritem->getSkillMod0Type(), -armoritem->getSkillMod0Value());
	setItemSkillMod(armoritem->getSkillMod1Type(), -armoritem->getSkillMod1Value());
	setItemSkillMod(armoritem->getSkillMod2Type(), -armoritem->getSkillMod2Value());

	setItemSkillMod(armoritem->getSocket0Type(), -armoritem->getSocket0Value());
	setItemSkillMod(armoritem->getSocket1Type(), -armoritem->getSocket1Value());
	setItemSkillMod(armoritem->getSocket2Type(), -armoritem->getSocket2Value());
	setItemSkillMod(armoritem->getSocket3Type(), -armoritem->getSocket3Value());

}

void PlayerImplementation::unsetWeaponSkillMods(Weapon* weapon) {
	setItemSkillMod(weapon->getSkillMod0Type(), -weapon->getSkillMod0Value());
	setItemSkillMod(weapon->getSkillMod1Type(), -weapon->getSkillMod1Value());
	setItemSkillMod(weapon->getSkillMod2Type(), -weapon->getSkillMod2Value());

	accuracy = getSkillMod("unarmed_accuracy");
}

bool PlayerImplementation::setArmorEncumbrance(Armor* armor, bool forced) {
	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

	if ((healthEncumb >= strength || healthEncumb >= constitution ||
		actionEncumb >= quickness || actionEncumb >= stamina ||
		mindEncumb >= focus || mindEncumb >= willpower) && !forced)
		return false;

	if ((strength > 100000 || constitution > 100000 ||
		quickness > 100000 || stamina > 100000 ||
		focus > 100000 || willpower > 100000) && !forced)
		return false;

	healthEncumbrance += healthEncumb;
	actionEncumbrance += actionEncumb;
	mindEncumbrance += mindEncumb;

	strengthMax -= healthEncumb;
	constitutionMax -= healthEncumb;
	quicknessMax -= actionEncumb;
	staminaMax -= actionEncumb;
	focusMax -= mindEncumb;
	willpowerMax -= mindEncumb;

	strength -= healthEncumb;
	constitution -= healthEncumb;
	quickness -= actionEncumb;
	stamina -= actionEncumb;
	focus -= mindEncumb;
	willpower -= mindEncumb;

	return true;

}

void PlayerImplementation::unsetArmorEncumbrance(Armor* armor) {
	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

	healthEncumbrance -= healthEncumb;
	actionEncumbrance -= actionEncumb;
	mindEncumbrance -= mindEncumb;

	strengthMax += healthEncumb;
	constitutionMax += healthEncumb;
	quicknessMax += actionEncumb;
	staminaMax += actionEncumb;
	focusMax += mindEncumb;
	willpowerMax += mindEncumb;

	strength += healthEncumb;
	constitution += healthEncumb;
	quickness += actionEncumb;
	stamina += actionEncumb;
	focus += mindEncumb;
	willpower += mindEncumb;

}

void PlayerImplementation::applyPowerup(uint64 powerupID, uint64 targetID) {
	SceneObject* invObj = getInventoryItem(powerupID);

	if (invObj == NULL || !invObj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) invObj;

	if (!tano->isWeaponPowerup())
		return;

	Powerup* powerup = (Powerup*) tano;

	invObj = getInventoryItem(targetID);

	if (invObj == NULL || !invObj->isTangible())
		return;

	tano = (TangibleObject*) invObj;

	if (!tano->isWeapon())
		return;

	Weapon* weapon = (Weapon*) tano;

	weapon->wlock();
	powerup->wlock();

	if (weapon->getPowerupUses() == 0) {
		stringstream msg;
		msg << "You powerup your " << weapon->getName().c_str() << " with " << powerup->getName().c_str();
		sendSystemMessage(msg.str());
		powerup->apply(weapon);
		powerup->remove(_this);

		weapon->unlock();
		powerup->unlock();
		powerup->finalize();

		return;
	}
	else
		sendSystemMessage("This weapon is already powered up!");

	weapon->unlock();
	powerup->unlock();
}


void PlayerImplementation::applyAttachment(uint64 attachmentID, uint64 targetID) {
	SceneObject* invObj = getInventoryItem(attachmentID);

	if (invObj == NULL || !invObj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) invObj;

	if (!tano->isAttachment())
		return;

	Attachment* attachment = (Attachment*) tano;

	invObj = getInventoryItem(targetID);

	if (invObj == NULL || !invObj->isTangible())
		return;

	tano = (TangibleObject*) invObj;

	if (!tano->isArmor())
		return;

	Armor* armor = (Armor*) tano;

	armor->wlock();
	attachment->wlock();

	int skillModType;
	int skillModValue;

	int armorIndex;
	int attachmentIndex;

	bool done = false;
	bool setMods = false;

	while (!done) {
		done = true;
		attachmentIndex = attachment->getBestSkillMod();
		skillModType = attachment->getSkillModType(attachmentIndex);
		skillModValue = attachment->getSkillModValue(attachmentIndex);

		if (armor->isEquipped()) {
			unsetArmorSkillMods(armor);
			setMods = true;
		}

		int armorIndex = armor->addSkillMod(skillModType, skillModValue);

		if (setMods) {
			setArmorSkillMods(armor);
			setMods = false;
		}

		switch (armorIndex) {
		case (-1): // add failed
			break;
		case (-2): // equal or lesser value, remove skill mod from attachment and try again
			attachment->setSkillModValue(attachmentIndex, 0);
			attachment->setUpdated(true);
			done = false;
			break;
		case (-3): // we overwrote the skill mod with a higher one.  delete the attachment.
			armor->unlock();
			attachment->unlock();
			attachment->remove(_this);

			attachment->finalize();
			return;
		default: // skill mod was added successfully
			armor->unlock();
			attachment->unlock();
			attachment->remove(_this);

			attachment->finalize();
			return;
		}
	}
	// this is for the case when we pulled off the skill mod but the attachment only had one mod)
	if (attachment->isUpdated()) {
		attachment->remove(_this);
		attachment->setUpdated(false);

		armor->unlock();
		attachment->unlock();

		attachment->finalize();
		return;
	}

	armor->unlock();
	attachment->unlock();
}

void PlayerImplementation::setOvert() {
	if (!(pvpStatusBitmask & CreatureFlag::OVERT))
		pvpStatusBitmask |= CreatureFlag::OVERT;

	if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
		pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

	characterMask &= ~COVERT;

	factionStatus = 2;

	uint32 pvpBitmask = pvpStatusBitmask;

	sendSystemMessage("faction_recruiter", "overt_complete");

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;
				sendFactionStatusTo(player, true);
			} else if (object->isNonPlayerCreature()) {
				CreatureObjectImplementation * npc = (CreatureObjectImplementation *) object->_getImplementation();
				npc->sendFactionStatusTo(_this);
			}
		}

		zone->unlock();
	} catch (...) {
		error("exception Player::setOvert()");
		zone->unlock();
	}
}

void PlayerImplementation::setCovert() {
	if (pvpStatusBitmask & CreatureFlag::OVERT)
		pvpStatusBitmask -= CreatureFlag::OVERT;

	if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
		pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

	characterMask |= COVERT;

	factionStatus = 1;

	sendSystemMessage("faction_recruiter", "covert_complete");

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;
				sendFactionStatusTo(player, true);
			} else if (object->isNonPlayerCreature()) {
				CreatureObjectImplementation * npc = (CreatureObjectImplementation *) object->_getImplementation();
				npc->sendFactionStatusTo(_this);
			}
		}

		zone->unlock();
	} catch (...) {
		error("exception PlayerImplementation::setCovert()");
		zone->unlock();
	}
}

void PlayerImplementation::setOnLeave() {
	if (pvpStatusBitmask & CreatureFlag::OVERT)
		pvpStatusBitmask -= CreatureFlag::OVERT;

	if (pvpStatusBitmask & CreatureFlag::CHANGEFACTIONSTATUS)
		pvpStatusBitmask -= CreatureFlag::CHANGEFACTIONSTATUS;

	if (faction != 0)
		characterMask |= COVERT;

	factionStatus = 0;

	if (faction != 0)
		sendSystemMessage("faction_recruiter", "on_leave_complete");

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;
				sendFactionStatusTo(player, true);
			} else if (object->isNonPlayerCreature()) {
				CreatureObjectImplementation * npc = (CreatureObjectImplementation *) object->_getImplementation();
				npc->sendFactionStatusTo(_this);
			}
		}

		zone->unlock();
	} catch (...) {
		error("exception PlayerImplementation::setOnLeave()");
		zone->unlock();
	}
}

void PlayerImplementation::setLinkDead() {
	onlineStatus = LINKDEAD;

	if (playerObject != NULL)
		playerObject->setCharacterBit(PlayerObjectImplementation::LD, true);

	logoutTimeStamp.update();
	logoutTimeStamp.addMiliTime(30000);

	activateRecovery();
}

void PlayerImplementation::setOnline() {
	if (isLinkDead()) {
		if (playerObject != NULL)
			playerObject->clearCharacterBit(PlayerObjectImplementation::LD, true);
	}

	onlineStatus = ONLINE;
}

bool PlayerImplementation::isInDuelWith(Player* targetPlayer, bool doLock) {
	if (_this == targetPlayer)
		return false;

	try {
		if (doLock)
			targetPlayer->wlock(_this);

		bool res;
		if (requestedDuelTo(targetPlayer) && targetPlayer->requestedDuelTo(_this))
			res = true;
		else
			res = false;

		if (doLock)
			targetPlayer->unlock();

		return res;
	} catch (...) {
		if (doLock)
			targetPlayer->unlock();

		return false;
	}
}

void PlayerImplementation::addToDuelList(Player* targetPlayer) {
	if (duelList.put(targetPlayer) != -1)
		info("player [" + targetPlayer->getLoggingName() + "] added to duel list");
	else
		error("player [" + targetPlayer->getLoggingName() + "] was already in duel list");

}

void PlayerImplementation::removeFromDuelList(Player* targetPlayer) {
	if (duelList.drop(targetPlayer))
		info("player [" + targetPlayer->getLoggingName() + "] removed from duel list");
	else
		error("player [" + targetPlayer->getLoggingName() + "] was not found in duel list for removal");
}

void PlayerImplementation::clearDuelList() {
	if (zone != NULL) {
		CombatManager* combatManager = server->getCombatManager();
		combatManager->freeDuelList(_this);
	}
}

// Mission Functions

bool PlayerImplementation::isOnCurMisoKey(string& tmk) {
	tmk += ",";

	size_t pos;
	pos = curMisoKeys.find(tmk);

	if (pos == string::npos) {
		//printf("PlayerImplementation::isOnCurMisoKey() : player does not have mission.");
		return false;
	} else {
		//printf("PlayerImplementation::isOnCurMisoKey() : player has mission.");
		return true;
	}
}

void PlayerImplementation::removeFromCurMisoKeys(string tck) {
	tck += ",";

	size_t pos;
	pos = curMisoKeys.find(tck);

	if (pos == string::npos) {
		printf("PlayerImplementation::removeFromCurMisoKeys() : player does not have mission.");
		return;
	}

	//printf("Debug: erasing tck = %s. curMisoKeys = %s\n", tck.c_str(), curMisoKeys.c_str());
	curMisoKeys.erase(pos, tck.size());
	//printf("Debug: Tck erased = %s. curMisoKeys = %s\n", tck.c_str(), curMisoKeys.c_str());
}

bool PlayerImplementation::hasCompletedMisoKey(string& tmk) {
	tmk += ",";

	size_t pos;
	pos = finMisoKeys.find(tmk);

	if (pos == string::npos) {
		//printf("PlayerImplementation::hasCompletedMisoKey() : player hasnt completed the mission.");
		return false;
	} else {
		//printf("PlayerImplementation::hasCompletedMisoKey() : player has completed mission.");
		return true;
	}
}

// Crafting
CraftingTool* PlayerImplementation::getCurrentCraftingTool() {
	return currentCraftingTool;
}

CraftingTool* PlayerImplementation::getCraftingTool(const int type, bool doLock) {

	wlock(doLock);

	TangibleObject* item= NULL;

	// The For loop is looking for something in inventory with the same name as what is passed in
	for (int i = 0; i < inventory->objectsSize(); i++) {

		item = (TangibleObject*) inventory->getObject(i);

		if (item != NULL && item->isCraftingTool()) {

			CraftingTool* possibleTool = (CraftingTool*)item;

			if ((possibleTool->getToolType() == type)
					&& (possibleTool->isReady())) {

				unlock(doLock);
				return possibleTool;

			}
		}
	}
	unlock(doLock);
	return NULL;

}

void PlayerImplementation::setCurrentCraftingTool(CraftingTool* ct) {
	currentCraftingTool = ct;
}

void PlayerImplementation::clearCurrentCraftingTool() {
	currentCraftingTool = NULL;
}

void PlayerImplementation::prepareCraftingSession(CraftingTool* ct, DraftSchematic* ds) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->prepareCraftingSession(_this, ct, ds);
}

void PlayerImplementation::addIngredientToSlot(TangibleObject* tano, int slot, int counter) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->addIngredientToSlot(_this, tano, slot, counter);
}

void PlayerImplementation::removeResourceFromCraft(uint64 resID, int slot, int counter) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->removeIngredientFromSlot(_this, slot, counter);
}

void PlayerImplementation::nextCraftingStage(string test) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->nextCraftingStage(_this, test);
}

void PlayerImplementation::craftingCustomization(string name, int condition) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->craftingCustomization(_this, name, condition);
}

void PlayerImplementation::createPrototype(string count) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->createPrototype(_this, count);
}

void PlayerImplementation::createSchematic(string count) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->createSchematic(_this, count);
}

void PlayerImplementation::handleExperimenting(int count, int numRowsAttempted, string expstring) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->handleExperimenting(_this, count, numRowsAttempted, expstring);
}
// Draft Schematics

void PlayerImplementation::addDraftSchematicsFromGroupName(const string& schematicGroupName) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->addDraftSchematicsFromGroupName(_this, schematicGroupName);
}

void PlayerImplementation::subtractDraftSchematicsFromGroupName(const string& schematicGroupName) {
	CraftingManager* craftingManager = server->getCraftingManager();
	craftingManager->subtractDraftSchematicsFromGroupName(_this, schematicGroupName);
}

void PlayerImplementation::addDraftSchematic(DraftSchematic* ds) {
	draftSchematicList.put(ds->getSchematicID(), ds);
}

void PlayerImplementation::subtractDraftSchematic(DraftSchematic* ds) {
	draftSchematicList.drop(ds->getSchematicID());
}

void PlayerImplementation::sendDraftSchematics() {
	PlayerObjectDeltaMessage9* dplay9;

	dplay9 = new PlayerObjectDeltaMessage9(playerObject);

	dplay9->updateDraftSchematics();

	dplay9->close();
	sendMessage(dplay9);

	// Sending all the ingredients and experimental properties when draft schematics are sent
	// is the only way I can think of at the moment to prevent the bug if the client
	// leaves their datapad open and they surrender a skill that has draft schematics.
	// The draft schematics that are suppose to be deleted when surrendering only disappear
	// when the datapad is refreshed (close datapad, open datapad to refresh), if the client
	// clicks on a draft schematic he doesn't have, it screws up their retreiveing the information
	// of the draft schematic because they don't really have that schematic
	for (int i = 0; i < draftSchematicList.size(); i++) {
		DraftSchematic* schematic = draftSchematicList.get(i);
		schematic->sendIngredientsToPlayer(_this);
		schematic->sendExperimentalPropertiesToPlayer(_this);
	}
}

// Get by key
DraftSchematic* PlayerImplementation::getDraftSchematic(uint32 schematicID) {
	if(draftSchematicList.contains(schematicID)) {
		return draftSchematicList.get(schematicID);
	} else {
		return NULL;
	}
}

// Get by index
DraftSchematic* PlayerImplementation::getDraftSchematic(int index) {
	if(index >= 0 && index < draftSchematicList.size()) {
		return draftSchematicList.get(index);
	} else {
		return NULL;
	}
}

void PlayerImplementation::sendMessage(BaseMessage* msg) {
	if (owner != NULL)
		owner->sendMessage(msg);
	else
		delete msg;
}

void PlayerImplementation::sendMessage(StandaloneBaseMessage* msg) {
	if (owner != NULL)
		owner->sendMessage(msg);
	else
		delete msg;
}

void PlayerImplementation::addSkillBox(SkillBox* skillBox, bool updateClient) {
	skillBoxes.put(skillBox->getName(), skillBox);

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1;

		dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->startSkillBoxListUpdate(1);
		dcreo1->addSkillBox(skillBox->getName());

		dcreo1->close();
		sendMessage(dcreo1);
	}
}

void PlayerImplementation::removeSkillBox(SkillBox* skillBox, bool updateClient) {
	skillBoxes.remove(skillBox->getName());

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1;

		dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->startSkillBoxListUpdate(1);
		dcreo1->removeSkillBox(skillBox->getName());

		dcreo1->close();
		sendMessage(dcreo1);
	}
}

void PlayerImplementation::addCertifications(Vector<Certification*>& certs, bool updateClient) {
	PlayerObjectDeltaMessage9* dplay9;

	if (updateClient) {
		dplay9 = new PlayerObjectDeltaMessage9(playerObject);
		dplay9->startSkillListUpdate(certs.size());
	}

	for (int i = 0; i < certs.size(); i++) {
		Certification* cert = certs.get(i);
		certificationList.put(cert->getName(), cert);

		if (updateClient)
			dplay9->addSkill(cert->getName());
	}

	if (updateClient) {
		dplay9->close();
		sendMessage(dplay9);
	}
}

void PlayerImplementation::removeCertifications(Vector<Certification*>& certs, bool updateClient) {
	for (int i = 0; i < certs.size(); i++) {
		Certification* cert = certs.get(i);
		certificationList.drop(cert->getName());
	}

	if (updateClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
		dplay9->updateSkilsAndCertifications();
		dplay9->close();
		sendMessage(dplay9);
	}
}

void PlayerImplementation::increasePvpRating(int value) {
	pvpRating = pvpRating + value;
}

void PlayerImplementation::decreasePvpRating(int value) {
	pvpRating = pvpRating - value;
}

void PlayerImplementation::toggleCharacterBit(uint32 bit) {
	if (playerObject != NULL) {
		if (!playerObject->setCharacterBit(bit, true))
			playerObject->clearCharacterBit(bit, true);
	}
}


bool PlayerImplementation::setGuildPermissionsBit(uint32 bit, bool updateClient) {
	if (!(guildPermissionsBitmask & bit)) {
		guildPermissionsBitmask |= bit;

		return true;

	} else
		return false;
}

bool PlayerImplementation::clearGuildPermissionsBit(uint32 bit, bool updateClient) {
	if (guildPermissionsBitmask & bit) {
		guildPermissionsBitmask &= ~bit;

		return true;

	} else
		return false;
}

void PlayerImplementation::toggleGuildPermissionsBit(uint32 bit) {
	if (!setGuildPermissionsBit(bit, true))
		clearGuildPermissionsBit(bit, true);
}

bool PlayerImplementation::awardBadge(uint32 badgeindex) {
  	if (badgeindex > 139)
  		return false;

	badges.setBadge(badgeindex);

	return true;
}

void PlayerImplementation::getPlayersNearYou() {
	if (zone == NULL || objectID <= 0x15 || isIncapacitated() || isDead())
		return;

	try {
		zone->lock();

		PlayersNearYouMessage* pny = new PlayersNearYouMessage(_this);

		uint32 counter = 0;

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				++counter;
				Player* player = (Player*) obj;
				pny->addFoundPlayer(player);
			}
		}

		pny->insertPlayerCounter(counter);
		sendMessage(pny);

		zone->unlock();
	} catch (...) {
		error("exception PlayerImplementation::getPlayersNearYou()");
		zone->unlock();
	}
}

void PlayerImplementation::addDatapadItem(SceneObject* item) {
	datapad->addObject(item);
}

SceneObject* PlayerImplementation::getDatapadItem(uint64 oid) {
	return datapad->getObject(oid);
}

void PlayerImplementation::removeDatapadItem(uint64 oid) {
	datapad->removeObject(oid);
}

SceneObject* PlayerImplementation::getPlayerItem(uint64 oid) {
	SceneObject* object = NULL;

	object = getInventoryItem(oid);

	if (object == NULL) {
		object = getDatapadItem(oid);

		if (object == NULL)
			object = getWaypoint(oid);
	}

	return object;
}

bool PlayerImplementation::setGuild(uint32 gid) {
	PlayerManager* playerManager = zone->getZoneServer()->getPlayerManager();
	GuildManager* guildManager = playerManager->getGuildManager();

	guild = guildManager->getGuild(gid);

	return guild != NULL;
}

bool PlayerImplementation::updateGuild(uint32 gid) {
	PlayerManager* playerManager = zone->getZoneServer()->getPlayerManager();
	GuildManager* guildManager = playerManager->getGuildManager();

	Guild* gld = guildManager->getGuild(gid);
	if (gld == NULL)
		return false;

	guild = gld;

	sendGuildTo();

	return true;
}

void PlayerImplementation::updateGuild(Guild* gld) {
	guild = gld;

	sendGuildTo();
}

void PlayerImplementation::sendGuildList() {
	if (guild != NULL)
		guild->sendGuildListTo(_this);
}

void PlayerImplementation::saveProfessions() {
	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->saveProfessions(this);
}

void PlayerImplementation::loadProfessions() {
	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->loadProfessions(this);

	accuracy = getSkillMod("unarmed_accuracy");
}

bool PlayerImplementation::trainSkillBox(const string& name, bool updateClient) {
	ProfessionManager* professionManager = server->getProfessionManager();

	return professionManager->trainSkillBox(name, this, updateClient);
}

void PlayerImplementation::surrenderSkillBox(const string& name) {
	ProfessionManager* professionManager = server->getProfessionManager();

	return professionManager->surrenderSkillBox(name, this);
}

void PlayerImplementation::newChangeFactionStatusEvent(uint8 stat, uint32 timer) {
	pvpStatusBitmask |= CreatureFlag::CHANGEFACTIONSTATUS;

	changeFactionEvent = new ChangeFactionStatusEvent(this, stat, timer);
	server->addEvent(changeFactionEvent);

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;
				sendFactionStatusTo(player, true);
			}
		}

		zone->unlock();
	} catch (...) {
		error("exception PlayerImplementation::newChangeFactionStatusEvent()");
		zone->unlock();
	}
}

void PlayerImplementation::setEntertainerEvent() {
	if (entertainerEvent != NULL) {
		server->removeEvent(entertainerEvent);
	}

	entertainerEvent = new EntertainerEvent(_this);

	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;

	if (isDancing())
		performance = skillManager->getDance(getPerformanceName());
	else if(isPlayingMusic() && getInstrument() != NULL)
		performance = skillManager->getSong(getPerformanceName(), getInstrument()->getInstrumentType());
	else
		return;

	if(!performance) { // shouldn't happen
		stringstream msg;
		msg << "Performance was null in setEntertainerEvent.  Please report to McMahon! Name: " << getPerformanceName() << " and Type: " << dec << getInstrument()->getInstrumentType();

		sendSystemMessage(msg.str());
		return;
	}
	// I think the getLoopDuration is wrong now...thinking it should just be flat 10 seconds
	//server->addEvent(entertainerEvent, (uint64) performance->getLoopDuration() * 1000);
	server->addEvent(entertainerEvent, 10000);
}

void PlayerImplementation::setSurveyEvent(string& resourceName) {
	surveyEvent = new SurveyEvent(_this, resourceName);
	server->addEvent(surveyEvent, 5000);
}

void PlayerImplementation::setSampleEvent(string& resourceName, bool firstTime) {
	if (surveyTool == NULL) {
		sendSystemMessage("Please contact Ritter ASAP and log the exact actions you just took for a bug report. Thank you.");
		return;
	}

	if (getParent() != NULL && getParent()->isCell()) {
		ChatSystemMessage* sysMessage = new ChatSystemMessage("error_message","survey_in_structure");
		sendMessage(sysMessage);
		return;
	} else if (isInCombat()) {
		ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","sample_cancel_attack");
		sendMessage(sysMessage);
		return;
	} else if (isMounted()) {
		sendSystemMessage("You can not sample while riding a mount.");
		return;
	} else if (getInventoryItem(surveyTool->getObjectID()) == NULL) {
		ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","sample_gone");
		sendMessage(sysMessage);
		return;
	} else if (getPosture() != CreaturePosture::CROUCHED) {
		return;
	}

	if (firstTime) {

		sampleTool = surveyTool;

		firstSampleEvent = new SampleEvent(_this, resourceName);
		server->addEvent(firstSampleEvent, 2000);

		sampleEvent = new SampleEvent(_this, resourceName, false, true);
		server->addEvent(sampleEvent, 22000);
	} else {
		firstSampleEvent = NULL;

		if (changeActionBar(-200, false) ) {
			activateRecovery();

			sampleEvent = new SampleEvent(_this, resourceName);

			getZone()->getZoneServer()->getResourceManager()->sendSampleMessage(_this, resourceName);

			server->addEvent(sampleEvent, 20000);
		} else {
			sendSystemMessage("You do not have enough action to do that.");
			changePosture(CreaturePosture::UPRIGHT);
		}
	}
}

void PlayerImplementation::sendSampleTimeRemaining() {
	// Precondition: sampleEvent != NULL
	int time = -(sampleEvent->getTimeStamp().miliDifference()) / 1000;

	unicode ustr = "";
	ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","tool_recharge_time",ustr,time,false);
	sendMessage(sysMessage);
}

void PlayerImplementation::launchFirework(int animationType) {
	//Create the firework in the world.
	FireworkWorld* firework = new FireworkWorld(_this);

	switch (animationType) {
		case 1:
			firework->setFireworkObject(0xEF5A1CF7);
			break;
		case 2:
			firework->setFireworkObject(0x344DB460);
			break;
		case 3:
			firework->setFireworkObject(0x7D40D3ED);
			break;
		case 4:
			firework->setFireworkObject(0x86A3F8F9);
			break;
		case 5:
			firework->setFireworkObject(0xCFAE9F74);
			break;
		case 6:
			firework->setFireworkObject(0xF472118F);
			break;
		case 7:
			firework->setFireworkObject(0xFC967104);
			break;
		case 8:
			firework->setFireworkObject(0xBD7F7602);
			break;
		default:
			firework->setFireworkObject(0xBD7F7602);
			break;
	}

	firework->setZoneProcessServer(server);
	firework->setDirection(0, 0, -0.64, 0.76);

	setPosture(CreaturePosture::CROUCHED);

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* player = (Player*) obj;

				firework->sendTo(player);

				Animation* anim = new Animation(_this, "manipulate_low");
				player->sendMessage(anim);
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();

		cout << "unreported Exception on Player::launchFirework()\n";
	}

	firework->finalize();
}


int PlayerImplementation::getSlicingAbility() {
	string txt0 = "combat_smuggler_novice";
	string txt1 = "combat_smuggler_slicing_01";
	string txt2 = "combat_smuggler_slicing_02";
	string txt3 = "combat_smuggler_slicing_03";
	string txt4 = "combat_smuggler_slicing_04";
	string txt5 = "combat_smuggler_master";

	if (hasSkillBox(txt5))
		return 5;
	else if (hasSkillBox(txt4))
		return 4;
	else if (hasSkillBox(txt3))
		return 3;
	else if (hasSkillBox(txt2))
		return 2;
	else if (hasSkillBox(txt1))
		return 1;
	else if (hasSkillBox(txt0))
		return 0;

	return -1;
}

void PlayerImplementation::updateBuffWindow() {
	for (int i=0; i < creatureBuffs.size(); i++) {
		Buff* buff = creatureBuffs.get(i);

		if (buff->isActive())
			addBuff(buff->getBuffCRC(), buff->getTimeRemaining());
	}
}

void PlayerImplementation::queueHeal(TangibleObject* medPack, uint32 actionCRC, const string& attribute) {
	if (medPack == NULL || !medPack->isPharmaceutical()) {
		sendSystemMessage("healing_response", "healing_resonse_60"); //No valid medicine found.
		return;
	}

	uint64 objectID = medPack->getObjectID();

	stringstream actionModifier;
	if (!attribute.empty())
		actionModifier << attribute << "|";

	actionModifier << objectID;

	queueAction(_this, getTargetID(), actionCRC, ++actionCounter, actionModifier.str());
}

void PlayerImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	//player = the player requesting the radial
	//_this = the object who's radial was activated (can only be a playerobject)

	if (_this->isPlayingMusic()) {
		if (!player->isListening())
			omr->addRadialItem(0, 50, 3, "Listen");
		else
			omr->addRadialItem(0, 50, 3, "Stop Listen");
	}

	if (_this->isDancing()) {
		if (!player->isWatching())
			omr->addRadialItem(0, 50, 3, "Watch");
		else
			omr->addRadialItem(0, 50, 3, "Stop Watch");
	}

	omr->finish();

	player->sendMessage(omr);
}

void PlayerImplementation::saveDatapad(Player* player) {
	try {
		Datapad* datapad = player->getDatapad();
		if (datapad == NULL)
			return;

		string name, detailName, appearance, mountApp;
		stringstream query;
		uint32 objCRC, itnoCRC;
		uint64 objID;

		query.str("");
		query << "DELETE FROM datapad where character_id = " << player->getCharacterID() << ";";
		ServerDatabase::instance()->executeStatement(query);

		for (int i = 0; i < datapad->objectsSize(); ++i) {
			name = "";
			detailName = "";
			appearance = "";
			mountApp = "";
			objCRC = 0;
			objID = 0;
			itnoCRC = 0;

			SceneObject* item = datapad->getObject(i);

			if (item != NULL && item->isIntangible()) {
				IntangibleObject* itno = (IntangibleObject*) item;

				if (itno != NULL) {
					if (item->getObjectType() == 7 ) { //Vehicle (MountCreature)
						name = itno->getName();
						detailName = itno->getDetailName();
						objCRC = item->getObjectCRC();

						MountCreature* mountCreature = (MountCreature*) itno->getWorldObject();

						if (mountCreature != NULL) {
							Creature* creaMount = (Creature*) mountCreature;

							itnoCRC = mountCreature->getObjectCRC();
							objID = mountCreature->getObjectID();

							mountCreature->getCharacterAppearance(mountApp);

							if (mountApp != "") {
								BinaryData cust(mountApp);
								cust.encode(appearance);
							}
						}
					}

					//TODO: Datapad Load/save Schematics
					//TODO: Datapad Load/save Droids
					//TODO: Datapad Load/save Pets

					if (itnoCRC != 0 ) {
						query.str("");

						query << "Insert into datapad set character_id = " << player->getCharacterID()
						<< ",name = '" << name << "', itnocrc = " << objCRC << ",item_crc = " << itnoCRC
						<< ",itemMask = 65535, appearance = '" << appearance.substr(0, appearance.size() - 1)
						<< "',obj_id = " << objID << ";";

						ServerDatabase::instance()->executeStatement(query);
					}
				}
			}
		}
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		player->info("DB Exception in PlayerImplementation::saveDatapad(Player* player)");
	} catch (...) {
		player->info("Unreported Exception in PlayerImplementation::saveDatapad(Player* player)");

	}
}

void PlayerImplementation::addFactionPoints(string faction, uint32 points) {
	int currentPoints = factionPointsMap.getFactionPoints(faction);
	uint32 maxPoints = getMaxFactionPoints(faction);
	uint32 pointsToAdd;

	if (currentPoints + (int) points > maxPoints)
		pointsToAdd = (int) maxPoints - currentPoints;
	else
		pointsToAdd = points;

	if (pointsToAdd > 0) {
		factionPointsMap.addFactionPoints(faction, pointsToAdd);

		StfParameter * param = new StfParameter();
		param->addTO(faction);
		param->addDI(pointsToAdd);
		sendSystemMessage("base_player", "prose_award_faction", param);
		delete param;
	}

	if (pointsToAdd != points) {
		StfParameter * param = new StfParameter();
		param->addTO(faction);
		sendSystemMessage("base_player", "prose_max_faction", param);
		delete param;
	}
}

void PlayerImplementation::subtractFactionPoints(string faction, uint32 points) {
	int currentPoints = factionPointsMap.getFactionPoints(faction);
	uint32 pointsToAdd;

	if ((currentPoints - (int) points) < -5000)
		pointsToAdd = currentPoints - -5000;
	else
		pointsToAdd = points;

	if (pointsToAdd > 0) {
		factionPointsMap.subtractFactionPoints(faction, pointsToAdd);

		StfParameter * param = new StfParameter();
		param->addTO(faction);
		param->addDI(pointsToAdd);
		sendSystemMessage("base_player", "prose_lose_faction", param);
		delete param;
	}

	if (pointsToAdd != points) {
		StfParameter * param = new StfParameter();
		param->addTO(faction);
		sendSystemMessage("base_player", "prose_min_faction", param);
		delete param;
	}
}

void PlayerImplementation::delFactionPoints(Player * player, uint32 amount) {
	if (player == NULL)
		return;

	uint32 charge = (uint32) ceil(amount * FactionRankTable::getDelegateRatio(getFactionRank()));
	string faction;
	if (getFaction() == String::hashCode("imperial"))
		faction = "imperial";
	else if (getFaction() == String::hashCode("rebel"))
		faction = "rebel";
	else
		return;

	if (getFactionPoints(faction) < charge + 200)
		return;

	subtractFactionPoints(faction, charge);

	try {
		player->wlock(_this);

		player->addFactionPoints(faction, amount);

		player->unlock();
	} catch (...) {
		error("unreported exception caught in PlayerImplementation::delFactionPoints(Player * player, uint32 amount)");
		player->unlock();
	}
}

void PlayerImplementation::addSuiBoxChoice(string& choice){
	suiChoicesList->add(choice);
}

void PlayerImplementation::removeLastSuiBoxChoice(){
	suiChoicesList->removeLastElement();
}

void PlayerImplementation::setSuiBoxChoices(SuiListBoxVector* choicesList){
	suiChoicesList->removeAll();
	suiChoicesList = choicesList;
}

SuiListBoxVector* PlayerImplementation::getSuiBoxChoices(){
	return suiChoicesList;
}

void PlayerImplementation::clearSuiBoxChoices(){
	suiChoicesList->removeAll();
}

void PlayerImplementation::setResourceDeedID(uint64 objectID){
	resourceDeedID = objectID;
}

uint64 PlayerImplementation::getResourceDeedID(){
	return resourceDeedID;
}
