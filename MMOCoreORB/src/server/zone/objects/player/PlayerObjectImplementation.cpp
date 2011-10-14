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

#include "PlayerObject.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/combat/CombatManager.h"
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
#include "server/chat/room/ChatRoom.h"
#include "server/chat/ChatManager.h"
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
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "badges/Badge.h"
#include "badges/Badges.h"
#include "server/zone/packets/player/BadgesResponseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/weather/WeatherManager.h"
#include "events/PlayerDisconnectEvent.h"
#include "events/PlayerRecoveryEvent.h"
#include "server/zone/objects/player/variables/Ability.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void PlayerObjectImplementation::initializeTransientMembers() {
	IntangibleObjectImplementation::initializeTransientMembers();

	foodFillingMax = 100;
	drinkFillingMax = 100;

	duelList.setNoDuplicateInsertPlan();

	setLoggingName("PlayerObject");

	/**
	 * Here we are loading the schematics based on the skills that the
	 * player has, we do this incase we change the items
	 * in the schematic group.
	 */
	ZoneServer* zoneServer = server->getZoneServer();
	SkillManager* skillManager = SkillManager::instance();

	if (parent == NULL || !parent->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>( parent.get());

	SkillList* playerSkillList = creature->getSkillList();

	for(int i = 0; i < playerSkillList->size(); ++i) {
		Skill* skill = playerSkillList->get(i);
		skillManager->awardDraftSchematics(skill, _this, false);
	}

	skillManager->updateXpLimits(_this);
}

void PlayerObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	IntangibleObjectImplementation::loadTemplateData(templateData);

	characterBitmask = ANONYMOUS;

	adminLevel = 0;

	forcePower = 0;
	forcePowerMax = 0;

	foodFilling = 0;
	foodFillingMax = 100;

	drinkFilling = 0;
	drinkFillingMax = 100;

	jediState = 4;

	languageID = 0;

	experienceList.setNullValue(0);
}

void PlayerObjectImplementation::notifyLoadFromDatabase() {
	IntangibleObjectImplementation::notifyLoadFromDatabase();

	chatRooms.removeAll();
	tradeContainer.clear();

	surveyTool = NULL;

	centeredBonus = 0;

	serverLastMovementStamp.updateToCurrentTime();

	lastValidatedPosition.update(parent.get());

	clientLastMovementStamp = 0;

	setLinkDead();

	activateRecovery();
}

void PlayerObjectImplementation::unloadSpawnedChildren() {
	SceneObject* datapad = parent->getSlottedObject("datapad");
	CreatureObject* creo = dynamic_cast<CreatureObject*>(parent.get());

	if (datapad == NULL)
		return;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = cast<ControlDevice*>( object.get());

			device->storeObject(creo);
		}
	}
}


void PlayerObjectImplementation::unload() {
	info("unloading player");

	SceneObject* savedParent = NULL;

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get());

	notifyOffline();

	if (creature->isRidingMount()) {
		creature->executeObjectControllerAction(String("dismount").hashCode());
	}

	unloadSpawnedChildren();

	SceneObject* creoParent = creature->getParent();

	if (creature->getZone() != NULL) {
		savedTerrainName = creature->getZone()->getZoneName();

		//if (creature->isInQuadTree()) {
			if (creoParent != NULL) {
				savedParentID = creoParent->getObjectID();

				savedParent = creoParent;
			} else
				savedParentID = 0;

			creature->removeFromZone();
		//}
	}

	if (creoParent != NULL)
		creoParent->removeObject(creature);

	creature->clearUpdateToDatabaseTask();
	//updateToDatabaseAllObjects(false);

	if (savedParent != NULL) {
		//savedParent->updateToDatabaseWithoutChildren();
	}

	creature->clearCombatState(true);

	creature->stopEntertaining();

	tradeContainer.clear();

	creature->removeDotsFromVector();

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
	msg << "remaining ref count: " << _this->getReferenceCount();
	info(msg.toString(), true);

	_this->printReferenceHolders();*/
}


void PlayerObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending player object baselines");

	BaseMessage* play3 = new PlayerObjectMessage3(_this);
	player->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6(_this);
	player->sendMessage(play6);

	if (player == parent) {
		BaseMessage* play8 = new PlayerObjectMessage8(this);
		player->sendMessage(play8);

		BaseMessage* play9 = new PlayerObjectMessage9(this);
		player->sendMessage(play9);
	}
}

void PlayerObjectImplementation::notifySceneReady() {
	teleporting = false;

	BaseMessage* msg = new CmdSceneReady();
	sendMessage(msg);

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get());

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

	ManagedReference<WeatherManager*> weatherManager = creature->getZone()->getPlanetManager()->getWeatherManager();
	weatherManager->sendWeatherPacket(creature);

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
}

void PlayerObjectImplementation::sendFriendLists() {
	info("sending friendslist message  size " + String::valueOf(friendList.size()));

	ChatManager* chatManager = server->getChatManager();

	friendList.resetUpdateCounter();
	ignoreList.resetUpdateCounter();

	FriendsListMessage* flist = new FriendsListMessage(_this);
	parent->sendMessage(flist);

	IgnoreListMessage* ilist = new IgnoreListMessage(_this);
	parent->sendMessage(ilist);

	DeltaMessage* delta = new PlayerObjectDeltaMessage9(_this);
	friendList.insertToDeltaMessage(delta);
	ignoreList.insertToDeltaMessage(delta);
	delta->close();

	parent->sendMessage(delta);
}

void PlayerObjectImplementation::sendMessage(BasePacket* msg) {
	if (parent == NULL)
		delete msg;
	else {
		parent->sendMessage(msg);
	}
}

bool PlayerObjectImplementation::setCharacterBit(uint32 bit, bool notifyClient) {
	if (!(characterBitmask & bit)) {
		characterBitmask |= bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3(_this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}
		return true;
	} else
		return false;
}

bool PlayerObjectImplementation::clearCharacterBit(uint32 bit, bool notifyClient) {
	if (characterBitmask & bit) {
		characterBitmask &= ~bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3( _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}

		return true;
	} else
		return false;
}

void PlayerObjectImplementation::sendBadgesResponseTo(CreatureObject* player) {
	BaseMessage* msg = new BadgesResponseMessage(parent.get(), &badges);
	player->sendMessage(msg);
}

void PlayerObjectImplementation::awardBadge(uint32 badge) {
	PlayerManager* playerManager = getZoneServer()->getPlayerManager();
	playerManager->awardBadge(_this, badge);
}

int PlayerObjectImplementation::addExperience(const String& xpType, int xp, bool notifyClient) {
	if (xp == 0)
		return 0;

	int valueToAdd = xp;

	Locker locker(_this);

	if (experienceList.contains(xpType)) {
		xp += experienceList.get(xpType);

		if (xp <= 0) {
			removeExperience(xpType, notifyClient);
			return 0;
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

	waypoint->updateToDatabase();
}

void PlayerObjectImplementation::addWaypoint(WaypointObject* waypoint, bool checkName, bool notifyClient) {
	uint64 waypointID = waypoint->getObjectID();
	int specialTypeID = waypoint->getSpecialTypeID();
	bool doRemove = false;

	if (waypointList.contains(waypointID))
		doRemove = true;

	if (!doRemove && checkName) {
		String name = waypoint->getCustomName().toString();
		waypointID = waypointList.find(name);

		if(waypointID != 0)
			doRemove = true;
	}

	if (!doRemove && specialTypeID != 0) {
		waypointID = waypointList.getWaypointBySpecialType(specialTypeID);

		if(waypointID != 0)
			doRemove = true;
	}

	if(doRemove)
		removeWaypoint(waypointID, notifyClient);

	setWaypoint(waypoint, notifyClient);
}

void PlayerObjectImplementation::removeWaypoint(uint64 waypointID, bool notifyClient) {
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

}


void PlayerObjectImplementation::addWaypoint(const String& planet, float positionX, float positionY, bool notifyClient) {
	ManagedReference<WaypointObject*> obj = cast<WaypointObject*>( getZoneServer()->createObject(0xc456e788, 1));
	obj->setPlanetCRC(planet.hashCode());
	obj->setPosition(positionX, 0, positionY);
	obj->setActive(true);

	addWaypoint(obj, false, notifyClient);
}

void PlayerObjectImplementation::addAbility(Ability* ability, bool notifyClient) {
	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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
	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(0);
		abilityList.remove(abilityList.find(ability), msg, 1);
		msg->close();
		sendMessage(msg);
	} else {
		abilityList.remove(abilityList.find(ability));
	}
}

void PlayerObjectImplementation::removeAbilities(Vector<Ability*>& abilities, bool notifyClient) {
	if (abilities.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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

void PlayerObjectImplementation::addSchematics(Vector<ManagedReference<DraftSchematic* > >& schematics, bool notifyClient) {
	if (schematics.size() == 0)
		return;

	Vector<ManagedReference<DraftSchematic* > > schematicsToSend;
	for (int i = 0; i < schematics.size(); ++i) {

		/// If schematic is not already in the schematic list, we want to send it
		/// if not, we don't want to send it to the datapad
		if(!schematicList.contains(schematics.get(i)))
			schematicsToSend.add(schematics.get(i));
	}

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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
}

void PlayerObjectImplementation::addSchematic(DraftSchematic* schematic, bool notifyClient) {
	if (schematic == NULL)
		return;

	if(schematicList.updateUseCount(schematic)) {
		return;
	}

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(4);

		schematicList.add(schematic, msg, 1);

		msg->close();

		sendMessage(msg);
	} else {
		schematicList.add(schematic);
	}
}

void PlayerObjectImplementation::removeSchematics(Vector<ManagedReference<DraftSchematic* > >& schematics, bool notifyClient) {

	if (schematics.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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
	CreatureObject* player = cast<CreatureObject*>( getParentRecursively(SceneObject::PLAYERCREATURE));

	if(player == NULL)
		return;

	SkillList* playerSkillBoxList = player->getSkillList();

	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		Skill* skillBox = playerSkillBoxList->get(i);
		skillManager->awardDraftSchematics(skillBox, _this, true);
	}

	schematicList.awardLimitedUseSchematics();
}

void PlayerObjectImplementation::removeSchematic(DraftSchematic* schematic, bool notifyClient) {
	if (schematic == NULL)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
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
	CreatureObject* player = cast<CreatureObject*>( getParentRecursively(SceneObject::PLAYERCREATURE));

	if(player == NULL)
		return;

	SkillList* playerSkillBoxList = player->getSkillList();

	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		Skill* skillBox = playerSkillBoxList->get(i);
		skillManager->awardDraftSchematics(skillBox, _this, true);
	}

	schematicList.awardLimitedUseSchematics();
}
void PlayerObjectImplementation::doDigest() {
	if (!isDigesting())
		return;

	if (foodFilling > 0)
		setFoodFilling(foodFilling - 1);

	if (drinkFilling > 0)
		setDrinkFilling(drinkFilling - 1);
}

Vector<ManagedReference<DraftSchematic* > > PlayerObjectImplementation::filterSchematicList(
		CreatureObject* player, Vector<uint32>* enabledTabs, int complexityLevel) {

	Locker _locker(_this);

	return schematicList.filterSchematicList(player, enabledTabs, complexityLevel);
}

void PlayerObjectImplementation::addFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	PlayerManager* playerManager = server->getPlayerManager();

	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<CreatureObject*> playerToAdd;
	playerToAdd = dynamic_cast<CreatureObject*>(zoneServer->getObject(objID));

	if (playerToAdd == NULL || playerToAdd == parent) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			(cast<CreatureObject*>( parent.get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToAddGhost = playerToAdd->getPlayerObject();
	playerToAddGhost->addReverseFriend(cast<CreatureObject*>(parent.get())->getFirstName());
	playerToAddGhost->updateToDatabase();

	if (notifyClient) {
		AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
		parent->sendMessage(init);

		AddFriendMessage* add = new AddFriendMessage(parent->getObjectID(),	nameLower, "Core3", true);
		parent->sendMessage(add);

		if (playerToAdd->isOnline()) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(nameLower, "Core3", true);
			parent->sendMessage(notifyStatus);
		}

		friendList.add(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this);
		friendList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "friend_added");
		param.setTT(nameLower);
		(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		friendList.add(nameLower);
	}
}

void PlayerObjectImplementation::removeFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	if (!friendList.contains(nameLower)) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerManager* playerManager = server->getPlayerManager();
	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<CreatureObject*> playerToRemove;
	playerToRemove = dynamic_cast<CreatureObject*>(zoneServer->getObject(objID));

	if (playerToRemove == NULL) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToRemoveGhost = playerToRemove->getPlayerObject();
	playerToRemoveGhost->removeReverseFriend(cast<CreatureObject*>(parent.get())->getFirstName());
	playerToRemoveGhost->updateToDatabase();

	if (notifyClient) {
		AddFriendMessage* add = new AddFriendMessage(parent->getObjectID(),	nameLower, "Core3", false);
		parent->sendMessage(add);

		friendList.removePlayer(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this);
		friendList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "friend_removed");
		param.setTT(nameLower);
		(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		friendList.removePlayer(nameLower);
	}
}


void PlayerObjectImplementation::addIgnore(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	if (notifyClient) {
		AddIgnoreMessage* add = new AddIgnoreMessage(parent->getObjectID(),	nameLower, "Core3", true);
		parent->sendMessage(add);

		ignoreList.add(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this);
		ignoreList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "ignore_added");
		param.setTT(nameLower);
		(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		ignoreList.add(nameLower);
	}
}


void PlayerObjectImplementation::removeIgnore(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	if (!ignoreList.contains(nameLower)) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "ignore_not_found");
			param.setTT(nameLower);
			(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);
		}

		return;
	}

	if (notifyClient) {
		AddIgnoreMessage* add = new AddIgnoreMessage(parent->getObjectID(),	nameLower, "Core3", false);
		parent->sendMessage(add);

		ignoreList.removePlayer(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this);
		ignoreList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "ignore_removed");
		param.setTT(nameLower);
		cast<CreatureObject*>(parent.get())->sendSystemMessage(param);

	} else {
		ignoreList.removePlayer(nameLower);
	}
}

void PlayerObjectImplementation::setTitle(const String& characterTitle, bool notifyClient) {
	if (title == characterTitle)
		return;

	title = characterTitle;

	if (notifyClient) {
		PlayerObjectDeltaMessage3* dplay3 = new PlayerObjectDeltaMessage3(_this);
		dplay3->setCurrentTitle(title);
		dplay3->close();
		broadcastMessage(dplay3, true); //update the zone.
	}
}

void PlayerObjectImplementation::notifyOnline() {
	CreatureObject* playerCreature = cast<CreatureObject*>( parent.get());
	ChatManager* chatManager = server->getChatManager();

	Vector<String>* reverseTable = friendList.getReverseTable();

	String firstName = playerCreature->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < reverseTable->size(); ++i) {
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(reverseTable->get(i));

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
		} else {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(name, "Core3", false);
			parent->sendMessage(notifyStatus);
		}
	}
}

void PlayerObjectImplementation::notifyOffline() {
	//info("notifyOffline", true);
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	if (chatManager == NULL)
		return;

	Vector<String>* reverseTable = friendList.getReverseTable();

	String firstName = (cast<CreatureObject*>(parent.get()))->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < reverseTable->size(); ++i) {
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(reverseTable->get(i));

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(firstName, "Core3", false);
			player->sendMessage(notifyStatus);
		}
	}
}

void PlayerObjectImplementation::setLanguageID(byte language, bool notifyClient) {
	if (languageID == language)
		return;

	languageID = language;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this);
		dplay9->setLanguageID(languageID);
		dplay9->close();
		parent->sendMessage(dplay9);
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
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this);
		dplay9->updateFoodFilling(newValue);
		dplay9->close();
		parent->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::setDrinkFilling(int newValue, bool notifyClient) {
	if (drinkFilling == newValue)
		return;

	drinkFilling = newValue;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this);
		dplay9->updateDrinkFilling(drinkFilling);
		dplay9->close();
		parent->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::increaseFactionStanding(const String& factionName, float amount) {
	if (amount < 0)
		return; //Don't allow negative values to be sent to this method.

	//Get the current amount of faction standing
	float currentAmount = factionStandingList.get(factionName);

	//Ensure that the new amount is not greater than 5000.
	float newAmount = MIN(5000.f, currentAmount + amount);

	if (factionStandingList.contains(factionName))
		factionStandingList.get(factionName) = newAmount;
	else
		factionStandingList.put(factionName, newAmount);

	int change = floor(newAmount - currentAmount);

	//Send the proper system message.
	StringIdChatParameter msg("@base_player:prose_award_faction");
	msg.setTO("@faction/faction_names:" + factionName);
	msg.setDI(change);

	if (newAmount == 0)
		msg.setStringId("@base_player:prose_max_faction");

	CreatureObject* player = cast<CreatureObject*>( parent.get());
	player->sendSystemMessage(msg);
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

	if ((sui = getSuiBoxFromWindowType(windowType)) != NULL) {
		removeSuiBox(sui->getBoxID(), true);
	}
}

void PlayerObjectImplementation::decreaseFactionStanding(const String& factionName, float amount) {
	if (amount < 0)
		return; //Don't allow negative values to be sent to this method.

	//Get the current amount of faction standing
	float currentAmount = factionStandingList.get(factionName);

	//Ensure that the new amount is not less than -5000.
	float newAmount = MAX(-5000.f, currentAmount - amount);

	if (factionStandingList.contains(factionName))
		factionStandingList.get(factionName) = newAmount;
	else
		factionStandingList.put(factionName, newAmount);

	int change = floor(currentAmount - newAmount);

	//Send the proper system message.
	StringIdChatParameter msg("@base_player:prose_lose_faction");
	msg.setTO("@faction/faction_names:" + factionName);
	msg.setDI(change);

	if (newAmount == 0)
		msg.setStringId("@base_player:prose_min_faction");

	CreatureObject* player = cast<CreatureObject*>( parent.get());
	player->sendSystemMessage(msg);
}

float PlayerObjectImplementation::getFactionStanding(const String& factionName) {
	return factionStandingList.get(factionName);
}

bool PlayerObjectImplementation::isFirstIncapacitationExpired() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get());

	return creature->checkCooldownRecovery("firstIncapacitationTime");
}


void PlayerObjectImplementation::resetFirstIncapacitationTime() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get());

	if (!isFirstIncapacitation())
		resetIncapacitationCounter();

	creature->addCooldown("firstIncapacitationTime", 900000);
}

void PlayerObjectImplementation::logout(bool doLock) {
	Locker _locker(parent.get());

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


void PlayerObjectImplementation::doRecovery() {
	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get());

	if (!creature->isInQuadTree() && creature->getParent() != NULL && creature->getParent()->isCellObject() && creature->getClient() == NULL) {
		SceneObject* building = creature->getParent()->getParent();

		if (building != NULL && building->getZone() != NULL)
			//creature->insertToZone(building->getZone());
			building->getZone()->addObject(creature, -1, true);
	}

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
		doDigest();
		cooldownTimerMap->updateToCurrentAndAddMili("digestEvent", 18000);
	}

	DamageOverTimeList* damageOverTimeList = creature->getDamageOverTimeList();

	if (damageOverTimeList->hasDot() && damageOverTimeList->isNextTickPast()) {
		damageOverTimeList->activateDots(creature);
	}

	CommandQueueActionVector* commandQueue = creature->getCommandQueue();

	if (creature->isInCombat() && creature->getTargetID() != 0 && !creature->isPeaced()
			&& (commandQueue->size() == 0) && creature->isNextActionPast()) {
		creature->sendExecuteConsoleCommand("/attack");
		//enqueueCommand(0xA8FEF90A, 0, getTargetID(), ""); // Do default attack
	}

	activateRecovery();
}

void PlayerObjectImplementation::activateRecovery() {
	if (recoveryEvent == NULL) {
		recoveryEvent = new PlayerRecoveryEvent(_this);

		recoveryEvent->schedule(3000);
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
}

void PlayerObjectImplementation::reload(ZoneClientSession* client) {
	if (disconnectEvent != NULL) {
		disconnectEvent->cancel();
		disconnectEvent = NULL;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get());

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
	creature->getZone()->addObject(creature, -1, true);
}

void PlayerObjectImplementation::disconnect(bool closeClient, bool doLock) {
	Locker locker(parent.get());

	if (!isOnline()) {
		return;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get());

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


WaypointObject* PlayerObjectImplementation::getSurveyWaypoint() {
	WaypointList* list = getWaypointList();

	uint64 wpid = list->getWaypointBySpecialType(WaypointObject::SPECIALTYPE_RESOURCE);

	if (wpid != 0) {
		return list->get(wpid);
	}

	return NULL;
}


