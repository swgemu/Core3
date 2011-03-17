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
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/chat/ChatManager.h"

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

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/professions/Certification.h"
#include "server/zone/objects/player/variables/PlayerList.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/chat/StringIdChatParameter.h"


void PlayerObjectImplementation::initializeTransientMembers() {
	IntangibleObjectImplementation::initializeTransientMembers();

	foodFillingMax = 100;
	drinkFillingMax = 100;

	setLoggingName("PlayerObject");
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
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
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
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}

		return true;
	} else
		return false;
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

	if (waypointList.contains(waypointID)) {
		error("this contains this waypoint ID");
		return;
	}

	if (checkName) {
		String name = waypoint->getCustomName().toString();
		uint64 index = waypointList.find(name);

		if (index != 0)
			removeWaypoint(index, notifyClient);

	}

	if (specialTypeID != 0) {
		uint64 idx = waypointList.getWaypointBySpecialType(specialTypeID);

		if (idx != 0)
			removeWaypoint(idx, notifyClient);
	}

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
	ManagedReference<WaypointObject*> obj = (WaypointObject*) getZoneServer()->createObject(0xc456e788, 1);
	obj->setPlanetCRC(planet.hashCode());
	obj->setPosition(positionX, 0, positionY);
	obj->setActive(true);

	addWaypoint(obj, false, notifyClient);
}

void PlayerObjectImplementation::addSkills(Vector<String>& skills, bool notifyClient) {
	if (skills.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(0);

		skillList.add(skills.get(0), msg, skills.size());

		for (int i = 1; i < skills.size(); ++i)
			skillList.add(skills.get(i), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < skills.size(); ++i)
			skillList.add(skills.get(i));
	}
}

void PlayerObjectImplementation::addSkills(Vector<Certification*>& skills, bool notifyClient) {
	if (skills.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(0);

		skillList.add(skills.get(0)->getName(), msg, skills.size());

		for (int i = 1; i < skills.size(); ++i)
			skillList.add(skills.get(i)->getName(), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < skills.size(); ++i)
			skillList.add(skills.get(i)->getName());
	}
}

void PlayerObjectImplementation::removeSkills(Vector<String>& skills, bool notifyClient) {
	if (skills.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(0);

		skillList.remove(skillList.find(skills.get(0)), msg, skills.size());

		for (int i = 1; i < skills.size(); ++i)
			skillList.remove(skillList.find(skills.get(i)), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < skills.size(); ++i)
			skillList.remove(skillList.find(skills.get(i)));
	}
}

void PlayerObjectImplementation::removeSkills(Vector<Certification*>& skills, bool notifyClient) {
	if (skills.size() == 0)
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this);
		msg->startUpdate(0);

		skillList.remove(skillList.find(skills.get(0)->getName()), msg, skills.size());

		for (int i = 1; i < skills.size(); ++i)
			skillList.remove(skillList.find(skills.get(i)->getName()), msg, 0);

		msg->close();

		sendMessage(msg);
	} else {
		for (int i = 0; i < skills.size(); ++i)
			skillList.remove(skillList.find(skills.get(i)->getName()));
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
	ProfessionManager* professionManager = zoneServer->getProfessionManager();
	PlayerCreature* player = (PlayerCreature*) getParentRecursively(SceneObject::PLAYERCREATURE);

	if(player == NULL)
		return;

	SkillBoxList* playerSkillBoxList = player->getSkillBoxList();
	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		SkillBox* skillBox = playerSkillBoxList->get(i);
		professionManager->awardDraftSchematics(skillBox, _this, true);
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
	ProfessionManager* professionManager = zoneServer->getProfessionManager();
	PlayerCreature* player = (PlayerCreature*) getParentRecursively(SceneObject::PLAYERCREATURE);

	if(player == NULL)
		return;

	SkillBoxList* playerSkillBoxList = player->getSkillBoxList();
	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		SkillBox* skillBox = playerSkillBoxList->get(i);
		professionManager->awardDraftSchematics(skillBox, _this, true);
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
		PlayerCreature* player, Vector<uint32>* enabledTabs, int complexityLevel) {

	Locker _locker(_this);

	return schematicList.filterSchematicList(player, enabledTabs, complexityLevel);
}

void PlayerObjectImplementation::addFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	PlayerManager* playerManager = server->getPlayerManager();

	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<PlayerCreature*> playerToAdd;
	playerToAdd = dynamic_cast<PlayerCreature*>(zoneServer->getObject(objID));

	if (playerToAdd == NULL || playerToAdd == parent) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			((CreatureObject*) parent.get())->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToAddGhost = playerToAdd->getPlayerObject();
	playerToAddGhost->addReverseFriend(((PlayerCreature*) parent.get())->getFirstName());
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
		((CreatureObject*) parent.get())->sendSystemMessage(param);

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
			((CreatureObject*) parent.get())->sendSystemMessage(param);
		}

		return;
	}

	PlayerManager* playerManager = server->getPlayerManager();
	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<PlayerCreature*> playerToRemove;
	playerToRemove = dynamic_cast<PlayerCreature*>(zoneServer->getObject(objID));

	if (playerToRemove == NULL) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			((CreatureObject*) parent.get())->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToRemoveGhost = playerToRemove->getPlayerObject();
	playerToRemoveGhost->removeReverseFriend(((PlayerCreature*) parent.get())->getFirstName());
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
		((CreatureObject*) parent.get())->sendSystemMessage(param);

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
		((CreatureObject*) parent.get())->sendSystemMessage(param);

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
			((CreatureObject*) parent.get())->sendSystemMessage(param);
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
		((CreatureObject*) parent.get())->sendSystemMessage(param);

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
	PlayerCreature* playerCreature = (PlayerCreature*) parent.get();
	ChatManager* chatManager = server->getChatManager();

	Vector<String>* reverseTable = friendList.getReverseTable();

	String firstName = playerCreature->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < reverseTable->size(); ++i) {
		ManagedReference<PlayerCreature*> player = chatManager->getPlayer(reverseTable->get(i));

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(firstName, "Core3", true);
			player->sendMessage(notifyStatus);
		}
	}

	for (int i = 0; i < friendList.size(); ++i) {
		String name = friendList.get(i);
		ManagedReference<PlayerCreature*> player = chatManager->getPlayer(name);

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

	String firstName = ((PlayerCreature*) parent.get())->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < reverseTable->size(); ++i) {
		ManagedReference<PlayerCreature*> player = chatManager->getPlayer(reverseTable->get(i));

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

void PlayerObjectImplementation::addFactionPoints(const String& faction, int amount) {

}

void PlayerObjectImplementation::subtractFactionPoints(const String& faction, int amount) {

}

int PlayerObjectImplementation::getFactionPoints(const String& faction) {

}
