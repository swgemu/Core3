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

#include "../../ZoneClient.h"
#include "../../ZoneServer.h"

#include "../../objects.h"
#include "../../packets.h"

#include "../../managers/player/PlayerManager.h"
#include "../../managers/player/ProfessionManager.h"

#include "../../managers/item/ItemManager.h"

#include "../../managers/combat/CombatManager.h"

#include "../../managers/guild/GuildManager.h"
#include "../../managers/group/GroupManager.h"

#include "../../managers/planet/PlanetManager.h"

#include "../../managers/loot/LootManager.h"

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
#include "events/PlayerRecoveryEvent.h"
#include "events/CommandQueueActionEvent.h"
#include "events/ChangeFactionEvent.h"
#include "events/CenterOfBeingEvent.h"

#include "../creature/events/DizzyFallDownEvent.h"

#include "professions/Certification.h"

#include "../../managers/combat/CommandQueueAction.h"

PlayerImplementation::PlayerImplementation() : PlayerServant(0) {
	init();

	zoneID = 1;
	//zoneID = 8;
		
	setHeight(1.0f);
}

PlayerImplementation::PlayerImplementation(uint64 cid) : PlayerServant(baseID = cid << 32) {
	init();

	characterID = cid;
}

PlayerImplementation::~PlayerImplementation() {
	if (playerObject != NULL) {
		playerObject->undeploy();
		
		delete playerObject;
		playerObject = NULL;
	}
	
	if (inventory != NULL) {
		inventory->undeploy();
		
		delete inventory;
		inventory = NULL;
	}
}

void PlayerImplementation::init() {
	objectType = PLAYER;
	owner = NULL;
	zone = NULL;
	onlineStatus  = LOGGINGIN;

	// objects
	playerObject = NULL;
	
	disconnectEvent = NULL;
	logoutEvent = NULL;
	
	recoveryEvent = new PlayerRecoveryEvent(this);
	changeFactionEvent = NULL;
	
	datapad = NULL;

	// modifiers
	weaponSpeedModifier = 1;

	// constants
	itemShift = 100;
	
	// pvp stuff
	deathCount = 0;
	pvpRating = 0;
	duelList.setInsertPlan(SortedVector<Player*>::NO_DUPLICATE);
	
	// profession
	skillPoints = 0;
	skillBoxesToSave.setInsertPlan(SortedVector<SkillBox*>::NO_DUPLICATE);
	certificationList.setInsertPlan(SortedVector<Certification*>::NO_DUPLICATE);
	
	//temp
	factionRank = "Sexy Tester";
	rebelPoints = 0; 
 	imperialPoints = 0;
 	
 	regionId = 31; //Ancorhead I think lols.

 	conversatingCreature = NULL;
 	
 	chatRooms.setInsertPlan(SortedVector<ChatRoom*>::NO_DUPLICATE);
 	
 	centered = false;
 	centeredBonus = 0;
 	centerOfBeingEvent = new CenterOfBeingEvent(this);
 	
	lastTestPositionX = 0.f;
	lastTestPositionY = 0.f;
	
	tradeRequestedPlayer = 0;
	moneyToTrade = 0;
	acceptedTrade = false;
	verifiedTrade = false;

	setLogging(false);
	setGlobalLogging(true);
}

Player* PlayerImplementation::create(ZoneClient* client) {
	Player* player = (Player*) deploy();

	PlayerObjectImplementation* playerObjectImpl = new PlayerObjectImplementation(player);
	playerObject = (PlayerObject*) playerObjectImpl->deploy();

	setClient(client);
	client->setPlayer(player);

	string logName = "Player = " + firstName;

	setLockName(logName);
	//client->setLockName("ZoneClient = " + firstName);

	setLoggingName(logName);

	info("created player");
	
	return player;
}

void PlayerImplementation::load(ZoneClient* client) {
	try {
		wlock();
	
		setLoggingIn();
	
		owner = client;
		client->setPlayer(_this);

		stringstream logName;
		logName << "Player = " << firstName << " (0x" << hex << objectID << dec << ")";
	
		setLockName(logName.str());
		setLoggingName(logName.str());

		info("loading player");

		loadItems();

		setLoggingIn();
		
		Zone* zone = server->getZoneServer()->getZone(zoneID);
		insertToZone(zone);
		
		unlock();
	} catch (Exception& e) {
		unlock();

		error("logging in character");
		error(e.getMessage());

		client->disconnect();
	}
}

void PlayerImplementation::reload(ZoneClient* client) {
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
			
			owner->disconnect();
			
			wlock();
			
			info("loading player");
		} else if (isOnline()) {
			error("already loaded");
			
			unlock();

			client->disconnect();
			return;
		} else if (isOffline()) {
			info("reloading player from Cache");
		}
	
		owner = client;
		client->setPlayer(_this);

		setLoggingIn();
	
		Zone* zone = server->getZoneServer()->getZone(zoneID);
		
		if (isInQuadTree())
			reinsertToZone(zone);
		else
			insertToZone(zone);

		clearBuffs(true, true);

		if (!isOnFullHealth())
			doRecovery();	
		
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

	clearCombatState(); // remove the defenders
	
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

	if (zone != NULL && isInQuadTree()) {
		ZoneServer* zserver = zone->getZoneServer();
		
		ItemManager* itemManager = zserver->getItemManager();
		itemManager->unloadPlayerItems(_this);	

		PlayerManager* playerManager = zserver->getPlayerManager();
		playerManager->unload(_this);

		clearDuelList();

		if (isDancing())
			stopDancing();
		else if (isPlayingMusic())
			stopPlayingMusic();
			
		if (isWatching())
			stopWatch(watchID);
			
		if (isListening())
			stopListen(listenID);

		server->removeEvent(recoveryEvent);
		server->removeEvent((Event*) dizzyFallDownEvent);
		
		if (changeFactionEvent != NULL) {
			server->removeEvent(changeFactionEvent);
			delete changeFactionEvent;
			
			changeFactionEvent = NULL;
		}

		clearBuffs();
		
		removeFromZone(true);
		//zone = NULL;
	}
}

void PlayerImplementation::logout(bool doLock) {
	wlock(doLock);
	
	if (disconnectEvent == NULL) {
		info("creating disconnect event");		
		disconnectEvent = new PlayerDisconnectEvent(this);
		
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
			
			setLoggingOut();
			
			ClientLogout* packet = new ClientLogout();
			sendMessage(packet);
			break;
		}
	} else {
		if (logoutEvent != NULL){
			server->removeEvent(logoutEvent);
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
		
		// User is disconnecting in combat.  Will remain LD.
		if (isInCombat() && !isLinkDead()) {
			info("link dead");
			
			unload();
			
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
			logoutEvent = NULL;
		}
	
		if (closeClient && owner != NULL) {
			owner->closeConnection();
		}
		
		owner = NULL;
			
		unlock(doLock);
	} catch (...) {
		error("unreported exception on Player::disconnect()");
		unlock(doLock);
	}
}

void PlayerImplementation::createItems() {
	InventoryImplementation* invImpl = new InventoryImplementation(_this);
	inventory = (Inventory*) invImpl->deploy();
		
	DatapadImplementation* datapadImpl = new DatapadImplementation(_this);
	datapad = (Datapad*) datapadImpl->deploy();

	ItemManager* itemManager = zone->getZoneServer()->getItemManager();
	itemManager->loadDefaultPlayerItems(_this);

	if (!hairObject.empty()) {
		HairObjectImplementation* hairImpl = new HairObjectImplementation(_this, String::hashCode(hairObject), unicode("hair"), "hair");
		hairImpl->setCustomizationString(hairData);
		
		hairObj = (HairObject*) hairImpl->deploy();
	}
}

void PlayerImplementation::loadItems() {
	InventoryImplementation* invImpl = new InventoryImplementation(_this);
	inventory = (Inventory*) invImpl->deploy();
		
	DatapadImplementation* datapadImpl = new DatapadImplementation(_this);
	datapad = (Datapad*) datapadImpl->deploy();

	ItemManager* itemManager = zone->getZoneServer()->getItemManager();
	itemManager->loadPlayerItems(_this);

	if (!hairObject.empty()) {
		HairObjectImplementation* hairImpl = new HairObjectImplementation(_this, String::hashCode(hairObject), unicode("hair"), "hair");
		hairImpl->setCustomizationString(hairData);
		
		hairObj = (HairObject*) hairImpl->deploy();
	}
}

void PlayerImplementation::createBaseStats() {
	//TODO: bit hackish, find more clean solution
	
	int hamValues[9];
	
	if (startingProfession == "artisan")
		memcpy(hamValues, professionHams[0], sizeof(hamValues));
	else if (startingProfession == "brawler")
		memcpy(hamValues, professionHams[1], sizeof(hamValues));
	else if (startingProfession == "entertainer")
		memcpy(hamValues, professionHams[2], sizeof(hamValues));
	else if (startingProfession == "marksman")
		memcpy(hamValues, professionHams[3], sizeof(hamValues));
	else if (startingProfession == "medic")
		memcpy(hamValues, professionHams[4], sizeof(hamValues));
	else if (startingProfession == "scout")
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

void PlayerImplementation::sendToOwner() {
	if (faction != 0)
		pvpStatusBitmask |= OVERT_FLAG;

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
	
	if (/*objectID <= 0x15 ||*/ owner == NULL)
		return;
	
	try {
		zone->lock();

		info("inserting to zone");
		
		zone->registerObject(_this);

		owner->balancePacketCheckupTime();
		
		sendToOwner();
		
		zone->insert(this);
		zone->inRange(this, 128);

		owner->resetPacketCheckupTime();

		zone->unlock();
	} catch (...) {
		error("exception Player::insertToZone(Zone* zone)");

		zone->unlock();
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

void PlayerImplementation::updateZone() {
	if (zone == NULL || isIncapacitated() || isDead())
		return;
	
	if (isMounted())
		updateMountPosition();
	
	try {
		//info("updating player in Zone");
		
		zone->lock();

		zone->update(this);
		zone->inRange(this, 128);
		
		if (!isMounted())
			updatePlayerPosition();

		zone->unlock();
		
		//info("finished player update in Zone");
	} catch (...) {
		error("exception Player::updateZone()");

		zone->unlock();
	}
}

void PlayerImplementation::updateZoneWithParent(uint64 Parent) {
	/*if (zone == NULL)
		return;
	
	SceneObject* newParent = zone->lookupObject(Parent);
	
	if (newParent == NULL || parent == NULL)
		return;
	
	try {
		zone->lock();
		
		zone->update(this);		
		building->inRange(this, 128);

		updatePlayerPosition();

		zone->unlock();
	} catch (...) {
		error("Unreported exception in PlayerImplementation::updateZoneWithParent");
		zone->unlock();
	}*/
}

void PlayerImplementation::lightUpdateZone() {
	if (zone == NULL || isIncapacitated() || isDead())
		return;
	
	if (isMounted())
		updateMountPosition();
	
	try {
		//info("light updating player in Zone");

		zone->lock();

		zone->update(this);
		zone->inRange(this, 128);

		if (!isMounted())
			updatePlayerPosition(true);
	
		zone->unlock();

		//info("finsihed light update player in Zone");
	} catch (...) {
		error("exception Player::lightUpdateZone()");

		zone->unlock();
	}
}

void PlayerImplementation::lightUpdateZoneWithParent(uint64 Parent) {
	/*if (zone == NULL)
		return;

	SceneObject* newParent = zone->lookupObject(Parent);

	if (newParent == NULL || parent == NULL)
		return;

	try {
		zone->lock();

		zone->update(this);		
		building->inRange(this, 128);

		updatePlayerPosition(true);

		zone->unlock();
	} catch (...) {
		cout << "Unreported exception in PlayerImplementation::updateZoneWithParent\n";
		zone->unlock();
	}*/
}

void PlayerImplementation::updatePlayerPosition(bool doLightUpdate) {
	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
		
		if (obj != _this && obj->isPlayer()) {
			Player* player = (Player*) obj;
			
			if (doLightUpdate) {
				LightUpdateTransformMessage* umsg = new LightUpdateTransformMessage(_this);
				player->sendMessage(umsg);
			} else {
				UpdateTransformMessage* umsg = new UpdateTransformMessage(_this);
				player->sendMessage(umsg);
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

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->remove(this);
		
		zone->deleteObject(objectID);
		
		//TODO: SEND RETURN TO CHARSCREEN???
		
		zone->unlock(doLock);
	} catch (...) {
		error("exception Player::removeFromZone(bool doLock)");

		zone->unlock(doLock);
	}
}

void PlayerImplementation::notifyInsert(QuadTreeEntry* obj) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());
	
	Player* player;
	Creature* creature;
	TangibleObject* tangible;
	
	if (parent == scno)
		return;
	
	SceneObject* par = scno->getParent();

	if (par != NULL)
		par->sendTo(_this);
	
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

		if (creature->isRidingCreature())
			break;
		else
			creature->sendTo(_this);
		
		creature->sendItemsTo(_this);

		break;
	case SceneObjectImplementation::TANGIBLE:
		tangible = (TangibleObject*) scno;
		tangible->sendTo(_this);

		break;
	}
}

void PlayerImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());
	
	Player* player;
	Creature* creature;
	
	switch (scno->getObjectType()) {
	case SceneObjectImplementation::PLAYER:
		player = (Player*) scno;
		player->sendDestroyTo(_this);

		break;
	case SceneObjectImplementation::NONPLAYERCREATURE:
		creature = (Creature*) scno;
		creature->sendDestroyTo(_this);
		
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
	
	setIgnoreMovementTests(5);
	
	zoneID = planetid;
	ZoneServer* server = zone->getZoneServer();
	Zone* zone = server->getZone(zoneID);

	terrainName = Terrain::getTerrainName(zoneID);
	
	insertToZone(zone);
}	

void PlayerImplementation::doWarp(float x, float y, float z, bool doRandomize) {
	if (zone == NULL)
		return;

	removeFromZone();
	
	positionX = x;
	positionY = y;
	positionZ = z;
	
	setIgnoreMovementTests(10);
	
	if (doRandomize)
		randomizePosition(64);
	
	insertToZone(zone);
}	

void PlayerImplementation::bounceBack() {
	DataTransform* trans = new DataTransform(_this);
	sendMessage(trans);
}

void PlayerImplementation::notifySceneReady() {
	if (isLoggingIn()) {
		setOnline();
		
		unicode msg = unicode("Welcome to the Official Core3 Test Center!");
		sendSystemMessage(msg);

		unicode msg2 = unicode("please help us sorting some problems out by being as active as you can. we need to stress the server for these bugs to arise. thank you");
		sendSystemMessage(msg2);
		
		unicode msg3 = unicode("This server is owned, operated, and developed by Team SWGEmu at SWGEmu.com and is in no way affiliated with any other server communities.");
		sendSystemMessage(msg3);
		
		ChatManager* chatManager = server->getChatManager();
		chatManager->listMail(_this);
		
		info("scene ready");
	}	
}

void PlayerImplementation::sendSystemMessage(const string& message) {
	unicode msg(message);
	sendSystemMessage(msg);
}

void PlayerImplementation::sendSystemMessage(const string& file, const string& str, uint64 targetid) {
	ChatSystemMessage* msg = new ChatSystemMessage(file, str, targetid);
	sendMessage(msg);
}

void PlayerImplementation::sendSystemMessage(unicode& message) {
	ChatSystemMessage* smsg = new ChatSystemMessage(message);
	sendMessage(smsg);
}

void PlayerImplementation::queueAction(Player* player, uint64 target, uint32 actionCRC, uint32 actionCntr) {
	stringstream ident;
	ident << "0x" << hex << actionCRC << " (" << actionCntr << ")"; 
	
	//info("queing action " + ident.str());
	
	if (isDancing() || isPlayingMusic()) {
		player->sendSystemMessage("You cant use skills while dancing/playing music!");
		clearQueueAction(actionCntr);
	} else if (commandQueue.size() < 15) {
		CommandQueueAction* action = new CommandQueueAction(player, target, actionCRC, actionCntr);

		if (!doAction(action))
			delete action;
	} else
		clearQueueAction(actionCntr);

	//info("queing action " + ident.str() + " finished");

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

	action->setTarget((Player*) targetObject);
	action->setSkill(skill);
	
	if (!action->check())
		return false;

	if (commandQueue.size() != 0 || !nextAction.isPast()) {
		if (commandQueue.size() == 0) {
			CommandQueueActionEvent* e = new CommandQueueActionEvent(this);
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
		Event* e = new CommandQueueActionEvent(this);
		server->addEvent(e, nextAction);
		
		return;
	}

	if (action == NULL) {
		if (commandQueue.size() == 0)
			return;
			
		action = commandQueue.remove(0);
	}
	
	/*stringstream msg;
	msg << "activating action "<< hex << "0x" << action->getActionCRC() << " (" 
		<< action->getActionCounter() << ")";
	info(msg.str());*/
	
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
		Event* e = new CommandQueueActionEvent(this);

		if (!nextAction.isFuture()) {
			nextAction.update();
			nextAction.addMiliTime(100);
		}
		
		server->addEvent(e, nextAction);
	}
}

void PlayerImplementation::clearQueueAction(uint32 actioncntr, float timer, uint32 tab1, uint32 tab2) {
	Message* queuemsg = new CommandQueueRemove(_this, actioncntr, timer, tab1, tab2);
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
	
	if (++deathCount > 2) {
		server->removeEvent(recoveryEvent);

		clearStates();
		setPosture(DEAD_POSTURE);

		deathCount = 0;

		server->addEvent(recoveryEvent, 5000);
	} else {
		server->removeEvent(recoveryEvent);

		// send incapacitation timer
		CreatureObjectDeltaMessage3* incap = new CreatureObjectDeltaMessage3(_this);
		incap->updateIncapacitationRecoveryTime(8);
		incap->close();
	
		sendMessage(incap);

		clearStates();
		setPosture(INCAPACITATED_POSTURE);

		server->addEvent(recoveryEvent, 8000);
	}
}

void PlayerImplementation::changePosture(int post) {
	if (logoutEvent != NULL) {
		sendSystemMessage("Logout canceled.");
		server->removeEvent(logoutEvent);
		
		logoutEvent = NULL;
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
	}
	
	if (isInCombat() && post == SITTING_POSTURE) {
		clearQueueAction(actionCounter);
		return;
	}
	
	if (isDizzied() && post == CreatureObjectImplementation::UPRIGHT_POSTURE) {
		if ((getSkillMod("combat_equillibrium") >> 1) > System::random(100)) {
			if (!dizzyFallDownEvent->isQueued())
				server->addEvent(dizzyFallDownEvent, 100);
			setPosture(post, true);
		} else {
			setPosture(CreatureObjectImplementation::KNOCKEDDOWN_POSTURE, true);
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

void PlayerImplementation::doRecovery() {
	if (isLinkDead() && logoutTimeStamp.isPast()) {
		unload();
		setOffline();
		return;
	}
	
	if (isIncapacitated()) {
		speed = 5.376;
		
		setPosture(UPRIGHT_POSTURE);
	} else if (isDead()) { 		
		doClone();
		
		if (isLinkDead())
			server->addEvent(recoveryEvent, 3000);
	} else {
		if (hasStates()) {
			doStateRecovery();

			if (!isInCombat()) {
				if (isOnFullHealth() && !isDizzied() && !hasStates()) {
					if (isLinkDead())
						server->addEvent(recoveryEvent, 3000);
					return;
				}
					
			} else if (lastCombatAction.miliDifference() > 30000)
				clearCombatState();
		}
	}

	calculateHAMregen();

	if (isJedi() && !playerObject->isOnFullForce()) {
		if (getPosture() == SITTING_POSTURE)
			changeForceBar(playerObject->getForceRegen());
		else
			changeForceBar(playerObject->getForceRegen() / 3);
	}

	server->addEvent(recoveryEvent, 3000);
}

void PlayerImplementation::doStateRecovery() {
	if (isDizzied() && dizzyRecoveryTime.isPast())
		clearState(DIZZY_STATE);

	if (isBlinded() && blindRecoveryTime.isPast())
		clearState(BLINDED_STATE);

	if (isStunned() && stunRecoveryTime.isPast())
		clearState(STUNNED_STATE);
			
	if (isIntimidated() && intimidateRecoveryTime.isPast())
		clearState(INTIMIDATED_STATE);
			
	if (isPoisoned()) {
		if (poisonRecoveryTime.isPast())
			clearState(POISONED_STATE);
		else doPoisonTick();
	}
	
	if (isDiseased()) {
		if (diseasedRecoveryTime.isPast())
			clearState(DISEASED_STATE);			
		else doDiseaseTick();
	}
	
	if (isOnFire()) {
		if (fireRecoveryTime.isPast())
			clearState(ONFIRE_STATE);			
		else doFireTick();
	}
	
	if (isBleeding()) {
		if (bleedingRecoveryTime.isPast())
			clearState(BLEEDING_STATE);
		else doBleedingTick();
	}

	updateStates();
}

void PlayerImplementation::doClone() {
	info("cloning player");

	switch (zoneID) {
	case 0:	// corellia
		if (faction == String::hashCode("rebel"))
			doWarp(-326.0f, -4640.0f, 0, true);				// shuttle 1
		else
			doWarp(-28.0f, -4438.0f);						// shuttle 2
		
		break;
	case 2: // dathomir
		if (faction == String::hashCode("rebel"))			// science outpost
			doWarp(-76.0f, -1627.0f, 0, true);
		else
			doWarp(618.0f, 3054.0f);						// trade outpost
		
		break;
	default:
		if (faction == String::hashCode("rebel"))
			doWarp(-130.0f, -5300.0f, 0, true);
		else if (faction == String::hashCode("imperial"))
			doWarp(10.0f, -5480.0f, 0, true);
		else
			doWarp(96.0f, -5334.0f);
		
		break;
	}
		
	clearStates();
		
	//setNeutral();
	//setCovert();

	clearDuelList();		

	clearBuffs();
	
	changeForceBar(0);
	
	setPosture(UPRIGHT_POSTURE);
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
	
	defenseBonus += efficacy;
	centeredBonus = efficacy;
	
	showFlyText("combat_effects", "center_start_fly", 0, 255, 0);
	
	server->addEvent(centerOfBeingEvent, duration * 1000);
	
	centered = true;
}

void PlayerImplementation::removeCenterOfBeing() {
	if (!centered)
		return;
	
	server->removeEvent(centerOfBeingEvent);
	
	defenseBonus -= centeredBonus;
	centeredBonus = 0;
	
	showFlyText("combat_effects", "center_stop_fly", 255, 0, 0);
	centered = false;
}

void PlayerImplementation::kill() {
	server->removeEvent(recoveryEvent);

	clearStates();
	setPosture(DEAD_POSTURE);

	deathCount = 0;

	server->addEvent(recoveryEvent, 5000);
}

void PlayerImplementation::doPeace() {
	//info("trying Peace action");
	
	for (int i = 0; i < defenderList.size(); ++i) {
		CreatureObject* defender = defenderList.get(i);
		
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
		
		if (setState(PEACE_STATE))
			updateStates();
	}
	
	//info("finished doPeace");
}

void PlayerImplementation::lootCorpse() {
	if (targetObject == NULL || !targetObject->isNonPlayerCreature())
		return;
	
	Creature* target = (Creature*) targetObject;
	
	if (!isIncapacitated() && !isDead() && isInRange(target, 20)) {
		LootManager* lootManager = server->getLootManager();
		lootManager->lootCorpse(_this, target);
	}
}

bool PlayerImplementation::changeForceBar(int32 fp) {
	int32 newForce = playerObject->getForcePower() + fp;
	
	if (newForce <= 0)
		return false; 
	
	setForceBar(MIN(newForce, playerObject->getForcePowerMax()));

	return true;
}

void PlayerImplementation::addBuff(uint32 buffcrc, float time) {
	Buffs* bf = new Buffs(_this, buffcrc, time);
	sendMessage(bf);
}

//TODO: Fix the disconnect reconnect code so no need for reload variable
void PlayerImplementation::clearBuffs(bool doUpdatePlayer, bool reload) {
	// Clear buff icons
	if (doUpdatePlayer) {
		if (healthBuff || reload)
			addBuff(0x98321369, 0.0f);
	
		if (strengthBuff || reload)
			addBuff(0x815D85C5, 0.0f);
	
		if (constitutionBuff || reload)
			addBuff(0x7F86D2C6, 0.0f);
	
		if (actionBuff || reload)
			addBuff(0x4BF616E2, 0.0f);
	
		if (quicknessBuff || reload)
			addBuff(0x71B5C842, 0.0f);
	
		if (staminaBuff || reload)
			addBuff(0xED0040D9, 0.0f);
	
		if (mindBuff || reload)
			addBuff(0x11C1772E, 0.0f);
	
		if (focusBuff || reload)
			addBuff(0x2E77F586, 0.0f);
	
		if (willpowerBuff || reload)
			addBuff(0x3EC6FCB6, 0.0f);
		
		if(reload)
			return;
	}

	healthBuff = false;
	strengthBuff = false;
	constitutionBuff = false;
	actionBuff = false;
	quicknessBuff = false;
	staminaBuff = false;
	mindBuff = false;
	focusBuff = false;
	willpowerBuff = false;
	
	removeBuffs(doUpdatePlayer);
}

/*
 *	Item manipulation methods 
 */
 
void PlayerImplementation::changeCloth(uint64 itemid) {
	SceneObject* obj = inventory->getObject(itemid);
	if (obj == NULL || !obj->isTangible())
		return;
	
	TangibleObject* cloth = (TangibleObject*) obj;	
	
	if (cloth->isWeapon()) {
		changeWeapon(itemid);
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

	Weapon* weapon = (Weapon*) obj;
	
	if (weapon == NULL) 
		return;
	
	if (centered)
		removeCenterOfBeing();
	
	if (weapon->isEquipped()) {
		unequipItem(weapon);
		setWeapon(NULL);
		
		accuracy = getSkillMod("unarmed_accuracy");
	} else {
		if (weaponObject != NULL)
			unequipItem(weaponObject);

		setWeapon(weapon);
		equipItem(weapon);
		
		setWeaponSkillMods(weapon);		
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
}

void PlayerImplementation::setOvert() {
	if (!(pvpStatusBitmask & OVERT_FLAG))
		pvpStatusBitmask |= OVERT_FLAG;
	
	uint32 pvpBitmask = pvpStatusBitmask;
		
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
		error("exception Player::setOvert()");
		zone->unlock();
	}
}

void PlayerImplementation::setCovert() {
	if (pvpStatusBitmask & OVERT_FLAG)
		pvpStatusBitmask -= OVERT_FLAG;
	
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
		error("exception PlayerImplementation::setOvert()");
		zone->unlock();
	}
}

void PlayerImplementation::setLinkDead() {
	onlineStatus = LINKDEAD;
	
	if (playerObject != NULL)
		playerObject->setCharacterBit(PlayerObjectImplementation::LD, true);
	
	logoutTimeStamp.update();
	logoutTimeStamp.addMiliTime(30000);
	
	if (!recoveryEvent->isQueued())
		server->addEvent(recoveryEvent, 3000);
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
	if (duelList.put(targetPlayer) != -1) {
		info("player [" + targetPlayer->getLoggingName() + "] added to duel list");

		targetPlayer->acquire();
	} else
		error("player [" + targetPlayer->getLoggingName() + "] was already in duel list");
		
}

void PlayerImplementation::removeFromDuelList(Player* targetPlayer) {
	if (duelList.drop(targetPlayer)) {
		info("player [" + targetPlayer->getLoggingName() + "] removed from duel list");

		targetPlayer->release();
	} else
		error("player [" + targetPlayer->getLoggingName() + "] was not found in duel list for removal");
}

void PlayerImplementation::clearDuelList() {
	if (zone != NULL) {
		CombatManager* combatManager = server->getCombatManager();
		
		combatManager->freeDuelList(_this);
	}
}

void PlayerImplementation::sendMessage(Message* msg) {
	if (owner != NULL)
		owner->sendMessage(msg);
	else
		delete msg;
}

void PlayerImplementation::sendMessage(StandaloneMessage* msg) {
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

void PlayerImplementation::setAdminLevel(int level) {
	adminLevel = level;
	
	PlayerObjectDeltaMessage6* dplay6 = new PlayerObjectDeltaMessage6(playerObject);
	dplay6->setAdminLevel(level);
	dplay6->close();
	broadcastMessage(dplay6);
}

void PlayerImplementation::saveProfessions() {
	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->saveProfessions(this);
}

void PlayerImplementation::loadProfessions() {
	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->loadProfessions(this);
}

bool PlayerImplementation::trainSkillBox(const string& name) {
	ProfessionManager* professionManager = server->getProfessionManager();
	
	return professionManager->trainSkillBox(name, this);
}

void PlayerImplementation::surrenderSkillBox(const string& name) {
	ProfessionManager* professionManager = server->getProfessionManager();
	
	return professionManager->surrenderSkillBox(name, this);
}

void PlayerImplementation::newChangeFactionEvent(uint32 faction) {
	changeFactionEvent = new ChangeFactionEvent(this, faction);

	server->addEvent(changeFactionEvent);
}
