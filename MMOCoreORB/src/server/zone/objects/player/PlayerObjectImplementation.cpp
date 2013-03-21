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
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/structure/StructureManager.h"
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
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "FactionStatus.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/templates/intangible/SharedPlayerObjectTemplate.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/objects/player/events/BountyHunterTefRemovalTask.h"
#include "server/zone/managers/visibility/VisibilityManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
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

	characterBitmask = ANONYMOUS;

	adminLevel = 0;

	forcePower = getForcePower();
	forcePowerMax = getForcePowerMax();
	forcePowerRegen = getForcePowerRegen();

	trainerZoneName = getTrainerZoneName();

	foodFilling = 0;
	foodFillingMax = 100;

	drinkFilling = 0;
	drinkFillingMax = 100;

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

	setLinkDead();

	activateRecovery();
}

void PlayerObjectImplementation::unloadSpawnedChildren() {
	ManagedReference<SceneObject*> datapad = getParent().get()->getSlottedObject("datapad");
	ManagedReference<CreatureObject*> creo = dynamic_cast<CreatureObject*>(parent.get().get());

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

	ManagedReference<CreatureObject*> creature = dynamic_cast<CreatureObject*>(parent.get().get());

	MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
	missionManager->deactivateMissions(creature);

	notifyOffline();

	if (creature->isRidingMount()) {
		creature->executeObjectControllerAction(String("dismount").hashCode());
	}

	unloadSpawnedChildren();

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

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(creature->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer != NULL)
		creature->dropActiveSession(SessionFacadeType::TRADE);

	creature->clearDots();

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
	msg << "remaining ref count: " << _this.get()->getReferenceCount();
	info(msg.toString(), true);

	_this.get()->printReferenceHolders();*/
}


void PlayerObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending player object baselines");

	BaseMessage* play3 = new PlayerObjectMessage3(_this.get());
	player->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6(_this.get());
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

	BaseMessage* msg = new CmdSceneReady();
	sendMessage(msg);

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(parent.get().get());

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

	if (zoneServer != NULL && zoneServer->isServerLoading())
		return;

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

	FriendsListMessage* flist = new FriendsListMessage(_this.get());
	getParent().get()->sendMessage(flist);

	IgnoreListMessage* ilist = new IgnoreListMessage(_this.get());
	getParent().get()->sendMessage(ilist);

	DeltaMessage* delta = new PlayerObjectDeltaMessage9(_this.get());
	friendList.insertToDeltaMessage(delta);
	ignoreList.insertToDeltaMessage(delta);
	delta->close();

	getParent().get()->sendMessage(delta);
}

void PlayerObjectImplementation::sendMessage(BasePacket* msg) {
	if (parent == NULL)
		delete msg;
	else {
		getParent().get()->sendMessage(msg);
	}
}

bool PlayerObjectImplementation::setCharacterBit(uint32 bit, bool notifyClient) {
	if (!(characterBitmask & bit)) {
		characterBitmask |= bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3(_this.get());
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
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3(_this.get());
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
	playerManager->awardBadge(_this.get(), badge);
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
	} else if (factionStatus == FactionStatus::CHANGINGSTATUS) {
		creature->setPvpStatusBitmask(pvpStatusBitmask | CreatureFlag::CHANGEFACTIONSTATUS);
	} else if (factionStatus == FactionStatus::OVERT) {

		if(!(pvpStatusBitmask & CreatureFlag::OVERT))
			creature->addCooldown("declare_overt_cooldown",GCWManagerImplementation::overtCooldown*1000);

		if (!(pvpStatusBitmask & CreatureFlag::OVERT))
			pvpStatusBitmask |= CreatureFlag::OVERT;

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

	ManagedReference<SceneObject*> parent = getParent();

	Zone* zone = parent->getZone();

	if (zone == NULL)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) parent->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = closeObjects.get(i).castTo<BuildingObject*>();

		if (building != NULL) {
			building->updateCellPermissionsTo(creature);
		}
	}

}

int PlayerObjectImplementation::addExperience(const String& xpType, int xp, bool notifyClient) {
	if (xp == 0)
		return 0;

	int valueToAdd = xp;

	Locker locker(_this.get());

	if (experienceList.contains(xpType)) {
		xp += experienceList.get(xpType);

		if (xp <= 0 && xpType != "jedi_general") {
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
	int specialTypeID = waypoint->getSpecialTypeID();
	bool doRemove = false;

	if (waypointList.contains(waypointID))
		doRemove = true;

	if (!doRemove && checkName) {
		String name = waypoint->getCustomObjectName().toString();
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


WaypointObject* PlayerObjectImplementation::addWaypoint(const String& planet, float positionX, float positionY, bool notifyClient) {
	ManagedReference<WaypointObject*> obj = cast<WaypointObject*>( getZoneServer()->createObject(0xc456e788, 1));
	obj->setPlanetCRC(planet.hashCode());
	obj->setPosition(positionX, 0, positionY);
	obj->setActive(true);

	addWaypoint(obj, false, notifyClient);

	return obj;
}

void PlayerObjectImplementation::addAbility(Ability* ability, bool notifyClient) {
	if (notifyClient) {
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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

bool PlayerObjectImplementation::addRewardedSchematic(DraftSchematic* schematic, int quantity, bool notifyClient) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	schematics.add(schematic);
	if(!schematicList.addRewardedSchematic(schematic, quantity))
		return true;

	if(addSchematics(schematics, notifyClient)) {
		CreatureObject* parent = cast<CreatureObject*>(_this.get()->getParent().get().get());

		if(notifyClient && parent != NULL) {
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
		PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(_this.get());
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
		skillManager->awardDraftSchematics(skillBox, _this.get(), true);
	}

	schematicList.addRewardedSchematics(_this.get());
}

void PlayerObjectImplementation::doDigest(int fillingReduction) {
	if (!isDigesting())
		return;

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

	Locker _locker(_this.get());

	return schematicList.filterSchematicList(player, enabledTabs, complexityLevel);
}

void PlayerObjectImplementation::addFriend(const String& name, bool notifyClient) {
	String nameLower = name.toLowerCase();

	PlayerManager* playerManager = server->getPlayerManager();

	uint64 objID = playerManager->getObjectID(nameLower);

	ZoneServer* zoneServer = server->getZoneServer();
	ManagedReference<CreatureObject*> playerToAdd;
	playerToAdd = dynamic_cast<CreatureObject*>(zoneServer->getObject(objID));

	if (playerToAdd == NULL || playerToAdd == parent.get().get()) {
		if (notifyClient) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			(cast<CreatureObject*>(parent.get().get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToAddGhost = playerToAdd->getPlayerObject();

	if (playerToAddGhost == NULL)
		return;

	playerToAddGhost->addReverseFriend(cast<CreatureObject*>(parent.get().get())->getFirstName());
	playerToAddGhost->updateToDatabase();

	ManagedReference<SceneObject*> parent = getParent();

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

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.get());
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
			(cast<CreatureObject*>(parent.get().get()))->sendSystemMessage(param);
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
			(cast<CreatureObject*>(parent.get().get()))->sendSystemMessage(param);
		}

		return;
	}

	PlayerObject* playerToRemoveGhost = playerToRemove->getPlayerObject();

	if (playerToRemoveGhost == NULL)
		return;

	playerToRemoveGhost->removeReverseFriend((cast<CreatureObject*>(parent.get().get()))->getFirstName());
	playerToRemoveGhost->updateToDatabase();

	ManagedReference<SceneObject*> parent = getParent();

	if (notifyClient) {
		AddFriendMessage* add = new AddFriendMessage(parent->getObjectID(),	nameLower, "Core3", false);
		parent->sendMessage(add);

		friendList.removePlayer(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.get());
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
	ManagedReference<SceneObject*> parent = getParent();

	if (notifyClient) {
		AddIgnoreMessage* add = new AddIgnoreMessage(parent->getObjectID(),	nameLower, "Core3", true);
		parent->sendMessage(add);

		ignoreList.add(nameLower);

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.get());
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
	ManagedReference<SceneObject*> parent = getParent();

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

		PlayerObjectDeltaMessage9* delta = new PlayerObjectDeltaMessage9(_this.get());
		ignoreList.insertToDeltaMessage(delta);
		delta->close();

		parent->sendMessage(delta);

		StringIdChatParameter param("cmnty", "ignore_removed");
		param.setTT(nameLower);
		(cast<CreatureObject*>(parent.get()))->sendSystemMessage(param);

	} else {
		ignoreList.removePlayer(nameLower);
	}
}

void PlayerObjectImplementation::setTitle(const String& characterTitle, bool notifyClient) {
	if (title == characterTitle)
		return;

	title = characterTitle;

	if (notifyClient) {
		PlayerObjectDeltaMessage3* dplay3 = new PlayerObjectDeltaMessage3(_this.get());
		dplay3->setCurrentTitle(title);
		dplay3->close();
		broadcastMessage(dplay3, true); //update the zone.
	}
}

void PlayerObjectImplementation::notifyOnline() {
	CreatureObject* playerCreature = cast<CreatureObject*>( parent.get().get());
	ChatManager* chatManager = server->getChatManager();
	ManagedReference<SceneObject*> parent = getParent();
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

	//Resend all suis.
	for (int i = 0; i < suiBoxes.size(); ++i) {
		ManagedReference<SuiBox*> sui = suiBoxes.get(i);

		parent->sendMessage(sui->generateMessage());
	}

	//Login to visibility manager
	VisibilityManager::instance()->login(playerCreature);
}

void PlayerObjectImplementation::notifyOffline() {
	//info("notifyOffline", true);
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	if (chatManager == NULL)
		return;

	Vector<String>* reverseTable = friendList.getReverseTable();

	ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(parent.get().get());

	String firstName = playerCreature->getFirstName();
	firstName = firstName.toLowerCase();

	for (int i = 0; i < reverseTable->size(); ++i) {
		ManagedReference<CreatureObject*> player = chatManager->getPlayer(reverseTable->get(i));

		if (player != NULL) {
			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(firstName, "Core3", false);
			player->sendMessage(notifyStatus);
		}
	}

	//Logout from visibility manager
	VisibilityManager::instance()->logout(playerCreature);
}

void PlayerObjectImplementation::setLanguageID(byte language, bool notifyClient) {
	if (languageID == language)
		return;

	languageID = language;

	if (notifyClient) {
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.get());
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
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(_this.get());
		dplay9->updateDrinkFilling(drinkFilling);
		dplay9->close();
		getParent().get()->sendMessage(dplay9);
	}
}

void PlayerObjectImplementation::increaseFactionStanding(const String& factionName, float amount) {
	if (amount < 0)
		return; //Don't allow negative values to be sent to this method.

	CreatureObject* player = cast<CreatureObject*>( parent.get().get());

	//Get the current amount of faction standing
	float currentAmount = factionStandingList.getFactionStanding(factionName);

	//Ensure that the new amount is not greater than 5000.
	float newAmount = currentAmount + amount;

	if (!factionStandingList.isPvpFaction(factionName))
		newAmount = MIN(5000, newAmount);
	else
		newAmount = MIN(FactionManager::instance()->getFactionPointsCap(player->getFactionRank()), newAmount);

	factionStandingList.put(factionName, newAmount);

	int change = floor(newAmount - currentAmount);

	//Send the proper system message.
	StringIdChatParameter msg("@base_player:prose_award_faction");
	msg.setTO("@faction/faction_names:" + factionName);
	msg.setDI(change);

	if (change == 0)
		msg.setStringId("@base_player:prose_max_faction");


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

	//Ensure that the new amount is not less than -5000.
	float newAmount = MAX(-5000, currentAmount - amount);

	factionStandingList.put(factionName, newAmount);

	int change = floor(currentAmount - newAmount);

	//Send the proper system message.
	StringIdChatParameter msg("@base_player:prose_lose_faction");
	msg.setTO("@faction/faction_names:" + factionName);
	msg.setDI(change);

	if (change == 0)
		msg.setStringId("@base_player:prose_min_faction");

	player->sendSystemMessage(msg);
}

float PlayerObjectImplementation::getFactionStanding(const String& factionName) {
	return factionStandingList.getFactionStanding(factionName);
}

bool PlayerObjectImplementation::isFirstIncapacitationExpired() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get().get());

	return creature->checkCooldownRecovery("firstIncapacitationTime");
}


void PlayerObjectImplementation::resetFirstIncapacitationTime() {
	CreatureObject* creature = cast<CreatureObject*>( parent.get().get());

	if (!isFirstIncapacitation())
		resetIncapacitationCounter();

	creature->addCooldown("firstIncapacitationTime", 900000);
}

void PlayerObjectImplementation::logout(bool doLock) {
	Locker _locker(parent.get());

	try {
		if (disconnectEvent == NULL) {
			info("creating disconnect event");

			disconnectEvent = new PlayerDisconnectEvent(_this.get());

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

	if (getForcePowerMax() > 0  && (getForcePowerMax() - getForcePower() > 0))
	activateForceRegen();

	CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();

	if (cooldownTimerMap->isPast("digestEvent")) {
		Time* currentTime = new Time();

		int timeDelta = currentTime->getMiliTime() - lastDigestion.getMiliTime();
		int fillingReduction = timeDelta / 18000;

		doDigest(fillingReduction);

		lastDigestion.updateToCurrentTime();
		cooldownTimerMap->updateToCurrentAndAddMili("digestEvent", 18000);
	}

	DamageOverTimeList* damageOverTimeList = creature->getDamageOverTimeList();

	if (damageOverTimeList->hasDot() && damageOverTimeList->isNextTickPast()) {
		damageOverTimeList->activateDots(creature);
	}

	CommandQueueActionVector* commandQueue = creature->getCommandQueue();

	if (creature->isInCombat() && creature->getTargetID() != 0 && !creature->isPeaced()
			&& (commandQueue->size() == 0) && creature->isNextActionPast() && !creature->isDead() && !creature->isIncapacitated()) {
		creature->sendExecuteConsoleCommand("/attack");
		//enqueueCommand(0xA8FEF90A, 0, getTargetID(), ""); // Do default attack
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
		recoveryEvent = new PlayerRecoveryEvent(_this.get());

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

	activateMissions();
}

void PlayerObjectImplementation::reload(ZoneClientSession* client) {
	if (disconnectEvent != NULL) {
		disconnectEvent->cancel();
		disconnectEvent = NULL;
	}

	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

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


WaypointObject* PlayerObjectImplementation::getSurveyWaypoint() {
	WaypointList* list = getWaypointList();

	uint64 wpid = list->getWaypointBySpecialType(WaypointObject::SPECIALTYPE_RESOURCE);

	if (wpid != 0) {
		return list->get(wpid);
	}

	return NULL;
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
			MissionObject* mission = cast<MissionObject*>(datapad->getContainerObject(i));

			if (mission != NULL) {
				//Check if it is target or destination NPC
				MissionObjective* objective = mission->getMissionObjective();
				if (objective != NULL) {
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

	forcePower = fp;

	if (notifyClient == true){
		// Update the force power bar.
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePower();
		dplay8->close();

		sendMessage(dplay8);
	}

}

void PlayerObjectImplementation::activateForceRegen() {
	CreatureObject* creature = dynamic_cast<CreatureObject*>(parent.get().get());

	if (creature->isIncapacitated() || creature->isDead())
		return;

	if (getForcePower() < 0)
		setForcePower(0);

	float modifier = 1.f;
	
	if (creature->isMeditating())
		modifier = 3.f;

	uint32 forceTick = getForcePowerRegen() / 5 * modifier;

	if (forceTick < 1)
		forceTick = 1;

	if (forceTick > getForcePowerMax() - getForcePower()){   // If the player's Force Power is going to regen again and it's close to max,
		setForcePower(getForcePowerMax());             // Set it to max, so it doesn't go over max.
	} else setForcePower(getForcePower() + forceTick); // Otherwise regen normally.
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
		bountyLockList.put(playerId, new BountyHunterTefRemovalTask(_this.get(), playerId));
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

	ManagedReference<CreatureObject*> target = cast<CreatureObject*>(zoneServer->getObject(playerId));

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

Vector3 PlayerObjectImplementation::getTrainerCoordinates() {
	return trainerCoordinates;
}

void PlayerObjectImplementation::setTrainerCoordinates(const Vector3& trainer) {
	trainerCoordinates = trainer;
}

void PlayerObjectImplementation::addPermissionGroup(const String& group, bool updateInRangeBuildingPermissions) {
	permissionGroups.put(group);

	if (!updateInRangeBuildingPermissions)
		return;

	ManagedReference<SceneObject*> parent = getParent();

	Zone* zone = parent->getZone();

	if (zone == NULL)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) parent->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = closeObjects.get(i).castTo<BuildingObject*>();

		if (building != NULL) {
			building->broadcastCellPermissions();
		}
	}
}

void PlayerObjectImplementation::removePermissionGroup(const String& group, bool updateInRangeBuildingPermissions) {
	permissionGroups.drop(group);

	if (!updateInRangeBuildingPermissions)
		return;

	ManagedReference<SceneObject*> parent = getParent();

	Zone* zone = parent->getZone();

	if (zone == NULL)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) parent->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = closeObjects.get(i).castTo<BuildingObject*>();

		if (building != NULL) {
			building->broadcastCellPermissions();
		}
	}
}

bool PlayerObjectImplementation::hasPermissionGroup(const String& group) {
	return permissionGroups.contains(group);
}

void PlayerObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	for (int i = 0; i < ownedStructures.size(); ++i) {
		//ManagedReference<StructureObject*> structure = ownedStructures.get(i);

		uint64 oid = ownedStructures.get(i);

		ManagedReference<StructureObject*> structure = cast<StructureObject*>(getZoneServer()->getObject(oid));

		if (structure != NULL) {
			Zone* zone = structure->getZone();

			if (zone != NULL)
				StructureManager::instance()->destroyStructure(structure);

			structure->destroyObjectFromDatabase(true);
		}
	}
}
