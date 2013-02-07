/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

#include "server/login/account/Account.h"
#include "server/zone/packets/charcreation/ClientCreateCharacter.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterSuccess.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterFailed.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/db/ServerDatabase.h"
#include "server/db/MantisDatabase.h"
#include "server/chat/ChatManager.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/login/packets/ErrorMessage.h"
#include "server/zone/packets/player/LogoutMessage.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/objects/tangible/OptionBitmask.h"

#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/tangible/CloningBuildingObjectTemplate.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

#include "server/zone/objects/player/events/PlayerIncapacitationRecoverTask.h"
#include "server/zone/objects/player/events/ForceMeditateTask.h"
#include "server/zone/objects/player/events/MeditateTask.h"
#include "server/zone/objects/player/events/LogoutTask.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

#include "server/zone/objects/building/cloning/CloneSpawnPoint.h"

#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/skill/SkillManager.h"

#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/packets/trade/AbortTradeMessage.h"
#include "server/zone/packets/trade/AcceptTransactionMessage.h"
#include "server/zone/packets/trade/UnAcceptTransactionMessage.h"
#include "server/zone/packets/trade/AddItemMessage.h"
#include "server/zone/packets/trade/BeginTradeMessage.h"
#include "server/zone/packets/trade/DenyTradeMessage.h"
#include "server/zone/packets/trade/TradeCompleteMessage.h"
#include "server/zone/packets/trade/GiveMoneyMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage6.h"
#include "server/zone/packets/object/StartingLocationListMessage.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/director/DirectorManager.h"

#include "server/zone/objects/player/sui/callbacks/CloningRequestSuiCallback.h"

#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"

#include "server/zone/Zone.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/ServerCore.h"

#include "server/login/account/Account.h"

#include "server/zone/objects/player/sui/callbacks/PlayerTeachSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PlayerTeachConfirmSuiCallback.h"

#include "server/zone/managers/stringid/StringIdManager.h"

#include "server/zone/objects/creature/buffs/PowerBoostBuff.h"

#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/gcw/GCWManager.h"

int PlayerManagerImplementation::MAX_CHAR_ONLINE_COUNT = 2;

PlayerManagerImplementation::PlayerManagerImplementation(ZoneServer* zoneServer, ZoneProcessServer* impl) :
		Logger("PlayerManager") {
	server = zoneServer;
	processor = impl;

	playerMap = new PlayerMap(3000);
	nameMap = new CharacterNameMap();

	globalExpMultiplier = 1.0f;

	DirectorManager::instance()->getLuaInstance()->runFile("scripts/screenplays/checklnum.lua");

	loadStartingItems();
	loadStartingLocations();
	loadBadgeMap();
	loadPermissionLevels();

	setGlobalLogging(true);
	setLogging(false);

	if (ServerCore::truncateDatabases()) {
		try {
			String query = "TRUNCATE TABLE characters";

			Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

			info("characters table truncated", true);
		} catch (Exception& e) {
			error(e.getMessage());
		}
	}

	loadNameMap();
}

bool PlayerManagerImplementation::createPlayer(MessageCallback* data) {
	PlayerCreationManager* pcm = PlayerCreationManager::instance();
	return pcm->createCharacter(data);
}

void PlayerManagerImplementation::loadStartingItems() {
	try {
		startingItemList = StartingItemList::instance();

		startingItemList->loadItems();
	} catch (Exception& e) {
		error("unknown error while loadStartingItems");
		error(e.getMessage());
	}
}

void PlayerManagerImplementation::loadStartingLocations() {
	info("Loading starting locations.");

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/creation/starting_locations.iff");

	if (iffStream == NULL) {
		info("Couldn't load starting locations.", true);
		return;
	}

	startingLocationList.parseFromIffStream(iffStream);

	info("Loaded " + String::valueOf(startingLocationList.getTotalLocations()) + " starting locations.", true);
}

void PlayerManagerImplementation::loadBadgeMap() {
	info("Loading badges.");

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/badge/badge_map.iff");

	if (iffStream == NULL) {
		info("Couldn't load badge map.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);


	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		int idx = 0;
		String key;

		DataTableRow* row = dtiff.getRow(i);
		row->getCell(0)->getValue(idx);
		row->getCell(1)->getValue(key);
		badgeMap.put(idx, key);

		if (idx > highestBadgeIndex)
			highestBadgeIndex = idx;
	}

	info("Loaded " + String::valueOf(badgeMap.size()) + " badges.", true);
}

void PlayerManagerImplementation::loadPermissionLevels() {
	try {
		permissionLevelList = PermissionLevelList::instance();
		permissionLevelList->loadLevels();
	}
	catch(Exception& e) {
		error("Couldn't load permission levels.");
		error(e.getMessage());
	}


}

void PlayerManagerImplementation::finalize() {
	delete playerMap;
	playerMap = NULL;

	delete nameMap;
	nameMap = NULL;
}

void PlayerManagerImplementation::loadNameMap() {
	info("loading character names");

	try {
		String query = "SELECT * FROM characters where character_oid > 16777216 and galaxy_id = " + String::valueOf(server->getGalaxyID()) + " order by character_oid asc";

		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			uint64 oid = res->getUnsignedLong(0);
			String firstName = res->getString(3);

			if (!nameMap->put(firstName.toLowerCase(), oid)) {
				error("error coliding name:" + firstName.toLowerCase());
			}
		}

	} catch (Exception& e) {
		error(e.getMessage());
	}

	StringBuffer msg;
	msg << "loaded " << nameMap->size() << " character names in memory";
	info(msg.toString(), true);
}

bool PlayerManagerImplementation::existsName(const String& name) {
	bool res = false;

	rlock();

	try {
		res = nameMap->containsKey(name.toLowerCase());
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	runlock();

	return res;
}


bool PlayerManagerImplementation::kickUser(const String& name, const String& admin, String& reason, bool doBan) {
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager == NULL)
		return false;

	ManagedReference<CreatureObject*> player = chatManager->getPlayer(name);

	if (player == NULL)
		return false;

	ManagedReference<CreatureObject*> adminplayer = chatManager->getPlayer(admin);

	if (adminplayer == NULL)
		return false;

	PlayerObject* ghost = cast<PlayerObject*>(player->getSlottedObject("ghost"));


	PlayerObject* adminghost = cast<PlayerObject*>(adminplayer->getSlottedObject("ghost"));

	if(adminghost == NULL)
		return false;

	StringBuffer kickMessage;
	kickMessage << "You have been kicked by " << admin << " for '" << reason << "'";
	player->sendSystemMessage(kickMessage.toString());

	if(ghost != NULL)
		ghost->setLoggingOut();

	ErrorMessage* errmsg = new ErrorMessage(admin, "You have been kicked", 0);
	player->sendMessage(errmsg);

	player->sendMessage(new LogoutMessage());

	ManagedReference<ZoneClientSession*> session = player->getClient();

	if(session != NULL)
		session->disconnect(true);

	/// 10 min ban
	if(doBan) {
		String banMessage = banAccount(adminghost, getAccount(ghost->getAccountID()), 60 * 10, reason);
		adminplayer->sendSystemMessage(banMessage);
	}

	return true;
}

CreatureObject* PlayerManagerImplementation::getPlayer(const String& name) {
	uint64 oid = 0;

	rlock();

	oid = nameMap->get(name.toLowerCase());

	runlock();

	if (oid == 0)
		return NULL;

	SceneObject* obj = server->getObject(oid);

	if (obj == NULL || !obj->isPlayerCreature())
		return NULL;

	return cast<CreatureObject*>( obj);
}

uint64 PlayerManagerImplementation::getObjectID(const String& name) {
	uint64 oid = 0;

	rlock();

	oid = nameMap->get(name.toLowerCase());

	runlock();

	return oid;
}

bool PlayerManagerImplementation::checkExistentNameInDatabase(const String& name) {
	if (name.isEmpty())
		return false;

	try {
		String fname = name.toLowerCase();
		Database::escapeString(fname);
		String query = "SELECT * FROM characters WHERE lower(firstname) = \""
				+ fname + "\"";

		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);
		bool nameExists = res->next();

		return !nameExists;
	} catch (DatabaseException& e) {
		return false;
	}

	return false;
}

bool PlayerManagerImplementation::checkPlayerName(MessageCallback* messageCallback) {
	ClientCreateCharacterCallback* callback = cast<ClientCreateCharacterCallback*>( messageCallback);
	ZoneClientSession* client = callback->getClient();

	NameManager* nm = processor->getNameManager();
	BaseMessage* msg = NULL;

	String firstName;

	UnicodeString unicodeName;
	callback->getCharacterName(unicodeName);

	String name = unicodeName.toString();

	//Get the firstname
	int idx = name.indexOf(" ");
	if (idx != -1)
		firstName = name.subString(0, idx);
	else
		firstName = name;

	//Does this name already exist?
	if (nameMap->containsKey(firstName.toLowerCase())) {
		msg = new ClientCreateCharacterFailed("name_declined_in_use");
		client->sendMessage(msg);

		return false;
	}

	//Check to see if name is valid
	int res = nm->validateName(name, callback->getSpecies());

	if (res != NameManagerResult::ACCEPTED) {
		switch (res) {
		case NameManagerResult::DECLINED_EMPTY:
			msg = new ClientCreateCharacterFailed("name_declined_empty");
			break;
		case NameManagerResult::DECLINED_DEVELOPER:
			msg = new ClientCreateCharacterFailed("name_declined_developer");
			break;
		case NameManagerResult::DECLINED_FICT_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_fictionally_reserved");
			break;
		case NameManagerResult::DECLINED_PROFANE:
			msg = new ClientCreateCharacterFailed("name_declined_profane");
			break;
		case NameManagerResult::DECLINED_RACE_INAPP:
			msg = new ClientCreateCharacterFailed("name_declined_racially_inappropriate");
			break;
		case NameManagerResult::DECLINED_SYNTAX:
			msg = new ClientCreateCharacterFailed("name_declined_syntax");
			break;
		case NameManagerResult::DECLINED_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_reserved");
			break;
		default:
			msg = new ClientCreateCharacterFailed("name_declined_retry");
			break;
		}

		client->sendMessage(msg); //Name failed filters
		return false;
	}

	return true;
}


TangibleObject* PlayerManagerImplementation::createHairObject(const String& hairObjectFile, const String& hairCustomization) {
	TangibleObject* hairObject = NULL;

	if (hairObjectFile.isEmpty()) {
		info("hairObjectFile empty");
		return NULL;
	}

	//String sharedHairObjectFile = hairObjectFile.replaceFirst("hair_", "shared_hair_");

	info("trying to create hair object " + hairObjectFile);
	SceneObject* hair = server->createObject(hairObjectFile.hashCode(), 1);

	if (hair == NULL) {
		info("objectManager returned NULL hair object");
		return NULL;
	}

	if (hair->getGameObjectType() != SceneObjectType::GENERICITEM || hair->getArrangementDescriptor(0) != "hair") {
		//info("wrong hair object type");
		//hair->finalize();

		ManagedReference<SceneObject*> clearRef = hair;

		return NULL;
	} else {
		hairObject = cast<TangibleObject*>( hair);

		hairObject->setCustomizationString(hairCustomization);

		info("hair object created successfully");
	}

	return hairObject;
}

bool PlayerManagerImplementation::createAllPlayerObjects(CreatureObject* player) {
	SceneObject* inventory = server->createObject(0x77ae7dbb, 1); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->transferObject(inventory, 4);

	SceneObject* datapad = server->createObject(0x95ae7939, 1); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	player->transferObject(datapad, 4);

	SceneObject* playerObject = server->createObject(String("object/player/player.iff").hashCode(), 1); //player object

	if (playerObject == NULL) {
		error("could not create player object");
		return false;
	}

	player->transferObject(playerObject, 4);

	SceneObject* bank = server->createObject(0xf5b8caa5, 1); //bank

	if (bank == NULL) {
		error("could not create bank");
		return false;
	}

	player->transferObject(bank, 4);

	SceneObject* missionBag = server->createObject(0xaa5efb52, 1); //mission bag

	if (missionBag == NULL) {
		error("could not create mission bag");
		return false;
	}

	player->transferObject(missionBag, 4);

	uint32 defaultWeaponCRC = String("object/weapon/melee/unarmed/unarmed_default_player.iff").hashCode();

	SceneObject* defaultWeapon = server->createObject(defaultWeaponCRC, 1);

	if (defaultWeapon == NULL) {
		error("could not create default_weapon");
		return false;
	}

	player->transferObject(defaultWeapon, 4);

	// temp

	/*SceneObject* vibro = server->createObject(0x652688CE, 1);
	player->transferObject(vibro, 4);
	player->setWeaponID(vibro->getObjectID());

	SceneObject* vibro2 = server->createObject(0x652688CE, 1);
	inventory->transferObject(vibro2, -1);

	String bharmor = "object/tangible/wearables/armor/bounty_hunter/shared_armor_bounty_hunter_chest_plate.iff";
	SceneObject* armor = server->createObject(bharmor.hashCode(), 1);
	inventory->transferObject(armor, -1);

	String backpack = "object/tangible/wearables/backpack/shared_backpack_s01.iff";
	SceneObject* backpackObject = server->createObject(backpack.hashCode(), 1);
	inventory->transferObject(backpackObject, -1);*/

	/// Add vehicle
	/*VehicleControlDevice* vehicleControlDevice = cast<VehicleControlDevice*>( server->createObject(String("object/intangible/vehicle/speederbike_swoop_pcd.iff").hashCode(), 1));
	VehicleObject* vehicle = cast<VehicleObject*>( server->createObject(String("object/mobile/vehicle/speederbike_swoop.iff").hashCode(), 1));
	vehicleControlDevice->setControlledObject(vehicle);
	datapad->transferObject(vehicleControlDevice, -1);*/

	String pole = "object/tangible/fishing/fishing_pole.iff";
	SceneObject* poleObject = server->createObject(pole.hashCode(), 1);
	inventory->transferObject(poleObject, -1);

	String bait = "object/tangible/fishing/bait/bait_worm.iff";
	SceneObject* baitObject = server->createObject(bait.hashCode(), 1);
	inventory->transferObject(baitObject, -1);

	/*SceneObject* mission = server->createObject(3741732474UL, 1); // empty mission
	datapad->transferObject(mission, -1);*/

	//Add a ship
	ShipControlDevice* shipControlDevice = cast<ShipControlDevice*>( server->createObject(String("object/intangible/ship/sorosuub_space_yacht_pcd.iff").hashCode(), 1));
	//ShipObject* ship = cast<ShipObject*>( server->createObject(String("object/ship/player/player_sorosuub_space_yacht.iff").hashCode(), 1));
	ShipObject* ship = cast<ShipObject*>( server->createObject(String("object/ship/player/player_basic_tiefighter.iff").hashCode(), 1));

	shipControlDevice->setControlledObject(ship);

	if (!shipControlDevice->transferObject(ship, 4))
		info("Adding of ship to device failed");
	datapad->transferObject(shipControlDevice, -1);

	return true;
}

void PlayerManagerImplementation::createTutorialBuilding(CreatureObject* player) {
	Zone* zone = server->getZone("tutorial");

	String tut = "object/building/general/newbie_hall.iff";
	String cell = "object/cell/cell.iff";

	BuildingObject* tutorial = cast<BuildingObject*>( server->createObject(tut.hashCode(), 1));
	tutorial->createCellObjects();
	tutorial->setPublicStructure(true);

	/*int totalCellNumber = tutorial->getTotalCellNumber();

	info("totalCellNumber " + String::valueOf(totalCellNumber), true);*/

	tutorial->initializePosition(System::random(5000), 0, System::random(5000));
	zone->transferObject(tutorial, -1, true);

	//SceneObject* travelTutorialTerminal = server->createObject((uint32)String("object/tangible/beta/beta_terminal_warp.iff").hashCode(), 1);

	/*	String blueFrogTemplateCRC = "object/tangible/terminal/terminal_character_builder.iff";
	SceneObject* blueFrogTemplate =  server->createObject(blueFrogTemplateCRC.hashCode(), 1);*/

	SceneObject* cellTut = tutorial->getCell(11);
	//cellTut->transferObject(travelTutorialTerminal, -1);

	SceneObject* cellTutPlayer = tutorial->getCell(1);
	//	cellTut->transferObject(blueFrogTemplate, -1);

	//tutorial->insertToZone(zone);

	//addPermission

	//tutorial->togglePermission("ADMIN", player->getFirstName());

	//travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);
	//travelTutorialTerminal->insertToZone(zone);
	//zone->transferObject(travelTutorialTerminal, -1, true);
	//	blueFrogTemplate->initializePosition(27.0f, -3.5f, -165.0f);
	//	blueFrogTemplate->insertToZone(zone);

	//player->initializePosition(27.0f, -3.5f, -165.0f);
	player->initializePosition(0, 0, -3);
	//player->setZone(zone);
	cellTutPlayer->transferObject(player, -1);
	PlayerObject* ghost = player->getPlayerObject();
	ghost->setSavedTerrainName(zone->getZoneName());
	ghost->setSavedParentID(cellTutPlayer->getObjectID());

	tutorial->updateToDatabase();
}

void PlayerManagerImplementation::createSkippedTutorialBuilding(CreatureObject* player) {
	Zone* zone = server->getZone("tutorial");

	String tut = "object/building/general/newbie_hall_skipped.iff";
	String cell = "object/cell/cell.iff";

	BuildingObject* tutorial = cast<BuildingObject*>( server->createObject(tut.hashCode(), 1));
	tutorial->createCellObjects();
	tutorial->initializePosition(System::random(5000), 0, System::random(5000));
	zone->transferObject(tutorial, -1, true);

	SceneObject* travelTutorialTerminal = server->createObject((uint32)String("object/tangible/beta/beta_terminal_warp.iff").hashCode(), 1);

	SceneObject* cellTut = tutorial->getCell(1);
	cellTut->transferObject(travelTutorialTerminal, -1);

	//tutorial->insertToZone(zone);

	travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);
	//travelTutorialTerminal->insertToZone(zone);
	//zone->transferObject(travelTutorialTerminal, -1, true);

	player->initializePosition(27.0f, -3.5f, -165.0f);
	//player->setZone(zone);
	cellTut->transferObject(player, -1);
	PlayerObject* ghost = player->getPlayerObject();
	ghost->setSavedTerrainName(zone->getZoneName());
	ghost->setSavedParentID(cellTut->getObjectID());

	tutorial->updateToDatabase();
}

void PlayerManagerImplementation::createDefaultPlayerItems(CreatureObject* player, const String& profession, const String& templateFile) {
	String prof;

	try {
		prof = profession.subString(profession.indexOf('_') + 1);
	} catch (ArrayIndexOutOfBoundsException& e) {
		prof = "artisan";
	}

	String race = templateFile;
	int ls = race.lastIndexOf('/');
	int fu = race.indexOf('_');
	int dot = race.lastIndexOf('.');

	String species = race.subString(ls + 1, fu);
	String sex = race.subString(fu + 1, dot);

	String gen = "general";
	String all = "all";

	Vector<StartingItem>* items;

	SceneObject* inventory = player->getSlottedObject("inventory");

	//Make profession items for species

	items = startingItemList->getSkillItems(prof, species, sex);

	if (items == NULL)
		return;

	for (int j = 0; j < items->size(); ++j) {
		StartingItem item = items->get(j);

		SceneObject* obj = server->createObject(item.getTemplateCRC(), 1);

		if (obj == NULL) {
			StringBuffer msg;
			msg << "trying to create unknown starting player object with template 0x" << item.getTemplateCRC();
			error(msg.toString());

			continue;
		}

		if (item.createEquipped()) {
			player->transferObject(obj, 4);
		} else {
			inventory->transferObject(obj, -1);
		}
	}

	//Make profession items for that apply to all species
	items = startingItemList->getSkillItems(prof, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		StartingItem item = items->get(j);

		SceneObject* obj = server->createObject(item.getTemplateCRC(), 1);

		if (obj == NULL) {
			StringBuffer msg;
			msg << "trying to create unknown starting player object with template 0x" << item.getTemplateCRC();
			error(msg.toString());

			continue;
		}

		if (item.createEquipped()) {
			player->transferObject(obj, 4);
		} else {
			inventory->transferObject(obj, -1);
		}
	}


	//Make general items for species
	items = startingItemList->getSkillItems(gen, species, sex);
	for (int j = 0; j < items->size(); ++j) {
		StartingItem item = items->get(j);

		SceneObject* obj = server->createObject(item.getTemplateCRC(), 1);

		if (obj == NULL) {
			StringBuffer msg;
			msg << "trying to create unknown starting player object with template 0x" << item.getTemplateCRC();
			error(msg.toString());

			continue;
		}

		if (item.createEquipped()) {
			player->transferObject(obj, 4);
		} else {
			inventory->transferObject(obj, -1);
		}
	}


	//Make general items that apple to all species
	items = startingItemList->getSkillItems(gen, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		StartingItem item = items->get(j);

		SceneObject* obj = server->createObject(item.getTemplateCRC(), 1);

		if (obj == NULL) {
			StringBuffer msg;
			msg << "trying to create unknown starting player object with template 0x" << item.getTemplateCRC();
			error(msg.toString());

			continue;
		}

		if (item.createEquipped()) {
			player->transferObject(obj, 4);
		} else {
			inventory->transferObject(obj, -1);
		}
	}

}

uint8 PlayerManagerImplementation::calculateIncapacitationTimer(CreatureObject* playerCreature, int condition) {
	//Switch the sign of the value
	int32 value = -condition;

	if (value < 0)
		return 0;

	uint32 recoveryTime = (value / 5); //In seconds - 3 seconds is recoveryEvent timer

	//Recovery time is gated between 10 and 60 seconds.
	recoveryTime = MIN(MAX(recoveryTime, 10), 60);

	//Check for incap recovery food buff - overrides recovery time gate.
	/*if (hasBuff(BuffCRC::FOOD_INCAP_RECOVERY)) {
		Buff* buff = getBuff(BuffCRC::FOOD_INCAP_RECOVERY);

		if (buff != NULL) {
			float percent = buff->getSkillModifierValue("incap_recovery");

			recoveryTime = round(recoveryTime * ((100.0f - percent) / 100.0f));

			StfParameter* params = new StfParameter();
			params->addDI(percent);

			sendSystemMessage("combat_effects", "incap_recovery", params); //Incapacitation recovery time reduced by %DI%.
			delete params;

			removeBuff(buff);
		}
	}*/

	return recoveryTime;
}

int PlayerManagerImplementation::notifyDestruction(TangibleObject* destructor, TangibleObject* destructedObject, int condition) {
	if (!destructedObject->isPlayerCreature())
		return 1;

	CreatureObject* playerCreature = cast<CreatureObject*>( destructedObject);

	if (playerCreature->isIncapacitated() || playerCreature->isDead())
		return 1;

	if (playerCreature->isRidingMount()) {
		playerCreature->executeObjectControllerAction(String("dismount").hashCode());
	}

	playerCreature->clearDots();

	PlayerObject* ghost = playerCreature->getPlayerObject();

	ghost->updateIncapacitationCounter();

	destructor->removeDefender(destructedObject);

	if (!destructor->isKiller() && ghost->getIncapacitationCounter() < 3) {
		playerCreature->setPosture(CreaturePosture::INCAPACITATED, true);

		uint32 incapTime = calculateIncapacitationTimer(playerCreature, condition);
		playerCreature->setCountdownTimer(incapTime, true);

		Reference<Task*> oldTask = playerCreature->getPendingTask("incapacitationRecovery");

		if (oldTask != NULL && oldTask->isScheduled()) {
			oldTask->cancel();
			playerCreature->removePendingTask("incapacitationRecovery");
		}

		Reference<Task*> task = new PlayerIncapacitationRecoverTask(playerCreature, false);
		playerCreature->addPendingTask("incapacitationRecovery", task, incapTime * 1000);

		StringIdChatParameter stringId;

		if (destructor != NULL) {
			stringId.setStringId("base_player", "prose_victim_incap");
			stringId.setTT(destructor->getObjectID());
		} else {
			stringId.setStringId("base_player", "victim_incapacitated");
		}

		playerCreature->sendSystemMessage(stringId);

	} else {
		if (destructor->isKiller() || !ghost->isFirstIncapacitationExpired()) {
			killPlayer(destructor, playerCreature, 0);
		}
	}

	return 0;
}

void PlayerManagerImplementation::killPlayer(TangibleObject* attacker, CreatureObject* player, int typeofdeath) {
	StringIdChatParameter stringId;

	if (attacker->isPlayerCreature()) {
		stringId.setStringId("base_player", "prose_target_dead");
		stringId.setTT(player->getObjectID());
		(cast<CreatureObject*>(attacker))->sendSystemMessage(stringId);
	}

	if (player->isRidingMount()) {
		player->executeObjectControllerAction(String("dismount").hashCode());
	}

	player->setPosture(CreaturePosture::DEAD, true);

	sendActivateCloneRequest(player, typeofdeath);

	stringId.setStringId("base_player", "prose_victim_dead");
	stringId.setTT(attacker->getObjectID());
	player->sendSystemMessage(stringId);

	player->updateTimeOfDeath();
	player->clearBuffs(true);

	if (attacker->getFaction() != 0) {
		if (attacker->isPlayerCreature()) {
			CreatureObject* attackerCreature = cast<CreatureObject*>(attacker);
			//FactionManager::instance()->awardPvpFactionPoints()
			PlayerObject* attackerGhost = attackerCreature->getPlayerObject();
			PlayerObject* ghost = player->getPlayerObject();

			bool areInDuel = (ghost->requestedDuelTo(attackerCreature) && attackerGhost->requestedDuelTo(player));

			if (!areInDuel) {
				FactionManager::instance()->awardPvpFactionPoints(attackerCreature, player);
			}
		} else {
			FactionManager::instance()->awardPvpFactionPoints(attacker, player);
		}
	}

	CombatManager::instance()->freeDuelList(player, false);

	player->notifyObjectKillObservers(attacker);

	/*Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(10 * 1000);*/
}

void PlayerManagerImplementation::sendActivateCloneRequest(CreatureObject* player, int typeofdeath) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST);
	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST_DECAY);

	ManagedReference<SuiListBox*> cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);
	cloneMenu->setCallback(new CloningRequestSuiCallback(player->getZoneServer(), typeofdeath));
	cloneMenu->setPromptTitle("@base_player:revive_title");

	/*
	if (typeofdeath == 1) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);//no decay - GM command, deathblow or factional death
	} else if (typeofdeath == 0) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_DECAY);
	} else if (ghost->getFactionStatus() == FactionStatus::OVERT) {//TODO: Do proper check if faction death
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_FACTIONAL);
	}*/

	ManagedReference<SceneObject*> closestCloning = zone->getNearestPlanetaryObject(player, "cloningfacility");

	uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
	ManagedReference<SceneObject*> preDesignatedFacility = server->getObject(preDesignatedFacilityOid);

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	String closestName = "None";
	String predesignatedName = "None";

	//Get the name of the closest
	if (closestCloning != NULL) {
		ManagedReference<CityRegion*> cr = closestCloning->getCityRegion();

		if (cr != NULL)
			closestName = cr->getRegionName();
		else
			closestName = closestCloning->getDisplayedName();
	}

	//Get the name of the predesignated
	if (preDesignatedFacility != NULL) {
		ManagedReference<CityRegion*> cr = preDesignatedFacility->getCityRegion();

		if (cr != NULL)
			predesignatedName = cr->getRegionName();
		else
			predesignatedName = preDesignatedFacility->getDisplayedName();
	}

	StringBuffer promptText;
	promptText << "@base_player:revive_closest : " << closestName << "\n"
			<< "@base_player:revive_bind : " << predesignatedName << "\n" //Space before tab character is needed for proper formatting in this case.
			<< "Cash Balance : " << player->getCashCredits() << "\n\n"
			<< "Select the desired option and click OK.";

	cloneMenu->setPromptText(promptText.toString());

	if (closestCloning != NULL)
		cloneMenu->addMenuItem("@base_player:revive_closest", closestCloning->getObjectID());

	if (preDesignatedFacility != NULL && preDesignatedFacility->getZone() == zone)
		cloneMenu->addMenuItem("@base_player:revive_bind", preDesignatedFacility->getObjectID());

	// Adding major ones
	SortedVector<ManagedReference<SceneObject*> > locations = zone->getPlanetaryObjectList("cloningfacility");

	for (int j = 0; j < locations.size(); j++) {
		ManagedReference<SceneObject*> location = locations.get(j);

		if (location == NULL || location == closestCloning || location == preDesignatedFacility)
			continue;

		ManagedReference<CityRegion*> cr = location->getCityRegion();

		if (cr != NULL)
			cloneMenu->addMenuItem(cr->getRegionName() + " (" + String::valueOf((int) player->getDistanceTo(location)) + "m)", location->getObjectID());
		else
			cloneMenu->addMenuItem(location->getDisplayedName() + " (" + String::valueOf((int) player->getDistanceTo(location)) + "m)", location->getObjectID());
	}

	ghost->addSuiBox(cloneMenu);
	player->sendMessage(cloneMenu->generateMessage());
}

void PlayerManagerImplementation::sendPlayerToCloner(CreatureObject* player, uint64 clonerID, int typeofdeath) {
	ManagedReference<SceneObject*> cloner = server->getObject(clonerID);

	info("entering sendPlayerToCloner");

	if (cloner == NULL) {
		error("Cloning structure is null");
		return;
	}

	PlayerObject* ghost = player->getPlayerObject();

	CloningBuildingObjectTemplate* cbot = cast<CloningBuildingObjectTemplate*>(cloner->getObjectTemplate());

	if (cbot == NULL) {
		error("Not a cloning building template.");
		return;
	}

	BuildingObject* cloningBuilding = cloner.castTo<BuildingObject*>();

	CloneSpawnPoint* clonePoint = cbot->getRandomSpawnPoint();

	if (clonePoint == NULL) {
		error("clone point null");
		return;
	}

	Coordinate* coordinate = clonePoint->getCoordinate();
	Quaternion* direction = clonePoint->getDirection();

	int cellID = clonePoint->getCellID();

	SceneObject* cell = cloningBuilding->getCell(cellID);

	if (cell == NULL) {
		StringBuffer msg;
		msg << "null cell for cellID " << cellID << " in building: " << cbot->getFullTemplateString();
		error(msg.toString());
		return;
	}

	Zone* zone = player->getZone();

	player->switchZone(zone->getZoneName(), coordinate->getPositionX(), coordinate->getPositionZ(), coordinate->getPositionY(), cell->getObjectID());

	uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
	ManagedReference<SceneObject*> preDesignatedFacility = server->getObject(preDesignatedFacilityOid);

	if (preDesignatedFacility != NULL && preDesignatedFacility == cloningBuilding) {
		// bind removed
		player->sendSystemMessage("@base_player:bind_removed");
		ghost->setCloningFacility(NULL);
	} else {
		// TODO: add wounds
		player->addWounds(CreatureAttribute::HEALTH, 100, true);
		player->addWounds(CreatureAttribute::ACTION, 100, true);
		player->addWounds(CreatureAttribute::MIND, 100, true);
	}

	player->addShockWounds(100, true);

	if (ghost->getFactionStatus() != FactionStatus::ONLEAVE)
		ghost->setFactionStatus(FactionStatus::ONLEAVE);

	// Decay
	if (typeofdeath == 0) {
		SortedVector<ManagedReference<SceneObject*> > insurableItems = getInsurableItems(player, false);

		for (int i = 0; i < insurableItems.size(); i++) {
			SceneObject* item = insurableItems.get(i);

			if (item != NULL && item->isTangibleObject()) {
				ManagedReference<TangibleObject*> obj = cast<TangibleObject*>(item);

				if (obj->getOptionsBitmask() & OptionBitmask::INSURED) {
					//1% Decay for insured items
					obj->inflictDamage(obj, 0, 0.01 * obj->getMaxCondition(), true, true);
					//Set uninsured
					uint32 bitmask = obj->getOptionsBitmask() - OptionBitmask::INSURED;
					obj->setOptionsBitmask(bitmask);
				} else {
					//5% Decay for uninsured items
					obj->inflictDamage(obj, 0, 0.05 * obj->getMaxCondition(), true, true);
				}
			}
		}
	}

	Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(3 * 1000);

	player->notifyObservers(ObserverEventType::PLAYERCLONED, player, 0);

	// Jedi experience loss.
	if (ghost->getJediState() > 1)
		awardExperience(player, "jedi_general", -200000, true);
}

void PlayerManagerImplementation::disseminateExperience(TangibleObject* destructedObject, ThreatMap* threatMap) {
	uint32 totalDamage = threatMap->getTotalDamage();

	VectorMap<ManagedReference<CreatureObject*>, int> slExperience;
	slExperience.setAllowOverwriteInsertPlan();
	slExperience.setNullValue(0);


	float gcwBonus = 1.0f;
	uint32 winningFaction = -1;

	Zone* zone = destructedObject->getZone();
	if(zone != NULL){
		GCWManager* gcwMan = zone->getGCWManager();
		gcwBonus += (gcwMan->getGCWXPBonus() / 100.0f);
		winningFaction = gcwMan->getWinningFaction();
	}


	if(zone != NULL)
	for (int i = 0; i < threatMap->size(); ++i) {

		CreatureObject* player = threatMap->elementAt(i).getKey();


		if (!player->isPlayerCreature())
			continue;

		ManagedReference<GroupObject*> group = player->getGroup();

		ThreatMapEntry* entry = &threatMap->elementAt(i).getValue();

		Locker crossLocker(player, destructedObject);

		uint32 combatXp = 0;

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();
			String xpType = entry->elementAt(j).getKey();

			float xpAmount =  40.f * destructedObject->getLevel(); //TODO: need better formula for tano exp

			ManagedReference<AiAgent*> ai = cast<AiAgent*>(destructedObject);

			if (ai != NULL)
				xpAmount = ai->getBaseXp();

			xpAmount *= (float) damage / totalDamage;

			//Cap xp based on player level
			xpAmount = MIN(xpAmount, calculatePlayerLevel(player) * 300.f);

			//Apply group bonus if in group
			if (group != NULL)
				xpAmount *= 1.20; //TODO: Add groupExperienceModifier to lua player_manager.lua - requires refactor of startingitems (move to player creation manager).

			//Jedi experience doesn't count towards combat experience supposedly.
			if (xpType != "jedi_general")
				combatXp += xpAmount;

			if( winningFaction == player->getFaction()){
				xpAmount *= gcwBonus;
				combatXp *= gcwBonus;
			}
			//Award individual weapon exp.
			awardExperience(player, xpType, xpAmount);
		}

		combatXp /= 10.f;

		awardExperience(player, "combat_general", combatXp);

		//Check if the group leader is a squad leader
		if (group == NULL)
			continue;

		Vector3 pos(player->getWorldPositionX(), player->getWorldPositionY(), 0);

		crossLocker.release();

		ManagedReference<SceneObject*> groupLeader = group->getLeader();

		if (groupLeader == NULL || !groupLeader->isPlayerCreature())
			continue;

		CreatureObject* squadLeader = groupLeader.castTo<CreatureObject*>();

		Locker squadLock(squadLeader, destructedObject);

		//If he is a squad leader, and is in range of this player, then add the combat exp for him to use.
		if (squadLeader->hasSkill("outdoors_squadleader_novice") && pos.distanceTo(player->getWorldPosition()) <= 192.f) {
			int v = slExperience.get(squadLeader) + combatXp;
			slExperience.put(squadLeader, v);
		}
	}

	//Send out squad leader experience.
	for (int i = 0; i < slExperience.size(); ++i) {
		VectorMapEntry<ManagedReference<CreatureObject*>, int>* entry = &slExperience.elementAt(i);

		Locker clock(entry->getKey(), destructedObject);

		awardExperience(entry->getKey(), "squadleader", entry->getValue() * 2.f);
	}

	threatMap->removeAll();
}

bool PlayerManagerImplementation::checkEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int strength = player->getHAM(CreatureAttribute::STRENGTH);
	int constitution = player->getHAM(CreatureAttribute::CONSTITUTION);
	int quickness = player->getHAM(CreatureAttribute::QUICKNESS);
	int stamina = player->getHAM(CreatureAttribute::STAMINA);
	int focus = player->getHAM(CreatureAttribute::FOCUS);
	int willpower = player->getHAM(CreatureAttribute::WILLPOWER);

	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

	if (healthEncumb >= strength || healthEncumb >= constitution ||
			actionEncumb >= quickness || actionEncumb >= stamina ||
			mindEncumb >= focus || mindEncumb >= willpower)
		return false;
	else
		return true;
}


void PlayerManagerImplementation::applyEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int healthEncumb = MAX(0, armor->getHealthEncumbrance());
	int actionEncumb = MAX(0, armor->getActionEncumbrance());
	int mindEncumb = MAX(0, armor->getMindEncumbrance());

	player->addEncumbrance(CreatureEncumbrance::HEALTH, healthEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::ACTION, actionEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::MIND, mindEncumb, true);

	player->inflictDamage(player, CreatureAttribute::STRENGTH, healthEncumb, true);
	player->addMaxHAM(CreatureAttribute::STRENGTH, -healthEncumb, true);

	player->inflictDamage(player, CreatureAttribute::CONSTITUTION, healthEncumb, true);
	player->addMaxHAM(CreatureAttribute::CONSTITUTION, -healthEncumb, true);

	player->inflictDamage(player, CreatureAttribute::QUICKNESS, actionEncumb, true);
	player->addMaxHAM(CreatureAttribute::QUICKNESS, -actionEncumb, true);

	player->inflictDamage(player, CreatureAttribute::STAMINA, actionEncumb, true);
	player->addMaxHAM(CreatureAttribute::STAMINA, -actionEncumb, true);

	player->inflictDamage(player, CreatureAttribute::FOCUS, mindEncumb, true);
	player->addMaxHAM(CreatureAttribute::FOCUS, -mindEncumb, true);

	player->inflictDamage(player, CreatureAttribute::WILLPOWER, mindEncumb, true);
	player->addMaxHAM(CreatureAttribute::WILLPOWER, -mindEncumb, true);
}

void PlayerManagerImplementation::removeEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int healthEncumb = MAX(0, armor->getHealthEncumbrance());
	int actionEncumb = MAX(0, armor->getActionEncumbrance());
	int mindEncumb = MAX(0, armor->getMindEncumbrance());

	player->addEncumbrance(CreatureEncumbrance::HEALTH, -healthEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::ACTION, -actionEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::MIND, -mindEncumb, true);

	player->addMaxHAM(CreatureAttribute::STRENGTH, healthEncumb, true);
	player->healDamage(player, CreatureAttribute::STRENGTH, healthEncumb, true);

	player->addMaxHAM(CreatureAttribute::CONSTITUTION, healthEncumb, true);
	player->healDamage(player, CreatureAttribute::CONSTITUTION, healthEncumb, true);

	player->addMaxHAM(CreatureAttribute::QUICKNESS, actionEncumb, true);
	player->healDamage(player, CreatureAttribute::QUICKNESS, actionEncumb, true);

	player->addMaxHAM(CreatureAttribute::STAMINA, actionEncumb, true);
	player->healDamage(player, CreatureAttribute::STAMINA, actionEncumb, true);

	player->addMaxHAM(CreatureAttribute::FOCUS, mindEncumb, true);
	player->healDamage(player, CreatureAttribute::FOCUS, mindEncumb, true);

	player->addMaxHAM(CreatureAttribute::WILLPOWER, mindEncumb, true);
	player->healDamage(player, CreatureAttribute::WILLPOWER, mindEncumb, true);
}


void PlayerManagerImplementation::awardBadge(PlayerObject* ghost, uint32 badge) {
	if (!Badge::exists(badge))
		return;

	StringIdChatParameter stringId("badge_n", "");
	stringId.setTO("badge_n", Badge::getName(badge));

	ManagedReference<CreatureObject*> player = dynamic_cast<CreatureObject*>(ghost->getParent().get().get());

	if (ghost->hasBadge(badge)) {
		stringId.setStringId("badge_n", "prose_hasbadge");
		player->sendSystemMessage(stringId);
		return;
	}

	ghost->setBadge(badge);
	stringId.setStringId("badge_n", "prose_grant");
	player->sendSystemMessage(stringId);

	switch (ghost->getNumBadges()) {
	case 5:
		awardBadge(ghost, Badge::COUNT_5);
		break;
	case 10:
		awardBadge(ghost, Badge::COUNT_10);
		break;
	case 25:
		awardBadge(ghost, Badge::COUNT_25);
		break;
	case 50:
		awardBadge(ghost, Badge::COUNT_50);
		break;
	case 75:
		awardBadge(ghost, Badge::COUNT_75);
		break;
	case 100:
		awardBadge(ghost, Badge::COUNT_100);
		break;
	case 125:
		awardBadge(ghost, Badge::COUNT_125);
		break;
	default:
		break;
	}

	if (Badge::getType(badge) == Badge::EXPLORATION) {
		switch (ghost->getBadgeTypeCount(Badge::EXPLORATION)) {
		case 10:
			awardBadge(ghost, Badge::BDG_EXP_10_BADGES);
			break;
		case 20:
			awardBadge(ghost, Badge::BDG_EXP_20_BADGES);
			break;
		case 30:
			awardBadge(ghost, Badge::BDG_EXP_30_BADGES);
			break;
		case 40:
			awardBadge(ghost, Badge::BDG_EXP_40_BADGES);
			break;
		case 45:
			awardBadge(ghost, Badge::BDG_EXP_45_BADGES);
			break;
		default:
			break;
		}
	}

	// For the Hologrind - Please uncomment to re-enable when ready.

	/*
	Vector<byte>* profs = ghost->getHologrindProfessions();

	int profsDone = 0;

	for (int i = 0; i < profs->size(); ++i) { // So that it only sends 1 popup...
		byte prof = profs->get(i);

		int badgeIdx = 42 + prof;

		if (!ghost->hasBadge(badgeIdx))
			continue;

		profsDone++;
	}

	if (profsDone > 5) // Corresponds to the total professions needed in Generate holo.
		finishHologrind(player); // Method to send popup and grant Force Sensitive box.

	 */

}

void PlayerManagerImplementation::setExperienceMultiplier(float globalMultiplier) {
	globalExpMultiplier = globalMultiplier;
}

/*
 * Award experience to a player.
 * Ex.
	PlayerManager* playerManager = server->getPlayerManager();
	playerManager->awardExperience(playerCreature, "resource_harvesting_inorganic", 500);
 *
 */
void PlayerManagerImplementation::awardExperience(CreatureObject* player, const String& xpType,
		int amount, bool sendSystemMessage, float localMultiplier) {

	PlayerObject* playerObject = player->getPlayerObject();
	int xp = playerObject->addExperience(xpType, (int) (amount * localMultiplier * globalExpMultiplier));

	player->notifyObservers(ObserverEventType::XPAWARDED, player, xp);

	if (sendSystemMessage) {
		if (xp > 0) {
			StringIdChatParameter message("base_player","prose_grant_xp");
			message.setDI(xp);
			message.setTO("exp_n", xpType);
			player->sendSystemMessage(message);
		}
		if (xp > 0 && playerObject->hasCappedExperience(xpType)) {
			StringIdChatParameter message("base_player", "prose_hit_xp_cap"); //You have achieved your current limit for %TO experience.
			message.setTO("exp_n", xpType);
			player->sendSystemMessage(message);
		}
	}


}

void PlayerManagerImplementation::sendLoginMessage(CreatureObject* creature) {
	String motd = server->getLoginMessage();

	ChatSystemMessage* csm = new ChatSystemMessage(UnicodeString(motd), ChatSystemMessage::DISPLAY_CHATONLY);
	creature->sendMessage(csm);
}

void PlayerManagerImplementation::resendLoginMessageToAll() {
	ChatManager* chatManager = server->getChatManager();

	if (chatManager != NULL) {
		String motd = server->getLoginMessage();

		ChatSystemMessage* csm = new ChatSystemMessage(UnicodeString(motd), ChatSystemMessage::DISPLAY_CHATONLY);
		chatManager->broadcastMessage(csm);
	}
}

void PlayerManagerImplementation::handleAbortTradeMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL) {
		AbortTradeMessage* msg = new AbortTradeMessage();
		player->sendMessage(msg);

		return;
	}

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	AbortTradeMessage* msg = new AbortTradeMessage();

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>( obj.get());

		Locker locker(receiver, player);

		ManagedReference<TradeSession*> receiverContainer = dynamic_cast<TradeSession*>(receiver->getActiveSession(SessionFacadeType::TRADE));

		if (receiverContainer != NULL && receiverContainer->getTradeTargetPlayer() == player->getObjectID()) {
			receiver->dropActiveSession(SessionFacadeType::TRADE);
			receiver->sendMessage(msg->clone());
		}

		locker.release();
	}

	player->sendMessage(msg->clone());

	delete msg;

	player->dropActiveSession(SessionFacadeType::TRADE);
}

void PlayerManagerImplementation::handleAddItemToTradeWindow(CreatureObject* player, uint64 itemID) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL)
		return;

	// First Verify Target is Player
	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* receiver = cast<CreatureObject*>( obj.get());

	ManagedReference<SceneObject*> objectToTrade = server->getObject(itemID);

	if (objectToTrade == NULL || !objectToTrade->isASubChildOf(player) ||
			!objectToTrade->checkContainerPermission(player, ContainerPermissions::MOVECONTAINER)) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player);
		return;
	}

	if (objectToTrade->isNoTrade()) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player);
		return;
	}

	if(objectToTrade->isControlDevice()) {
		cast<ControlDevice*>(objectToTrade.get())->storeObject(player);
	}

	tradeContainer->addTradeItem(objectToTrade);

	SceneObject* inventory = player->getSlottedObject("inventory");
	inventory->sendWithoutContainerObjectsTo(receiver);
	objectToTrade->sendTo(receiver, true);

	AddItemMessage* msg = new AddItemMessage(itemID);
	receiver->sendMessage(msg);
}

void PlayerManagerImplementation::handleGiveMoneyMessage(CreatureObject* player, uint32 value) {
	Locker _locker(player);

	int currentMoney = player->getCashCredits();

	if (value > currentMoney)
		value = currentMoney;

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL)
		return;

	tradeContainer->setMoneyToTrade(value);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>( obj.get());

		GiveMoneyMessage* msg = new GiveMoneyMessage(value);
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleAcceptTransactionMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL)
		return;

	tradeContainer->setAcceptedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		AcceptTransactionMessage* msg = new AcceptTransactionMessage();
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleUnAcceptTransactionMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL)
		return;

	tradeContainer->setAcceptedTrade(false);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		UnAcceptTransactionMessage* msg = new UnAcceptTransactionMessage();
		receiver->sendMessage(msg);
	}

}

bool PlayerManagerImplementation::checkTradeItems(CreatureObject* player, CreatureObject* receiver) {
	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = receiver->getPlayerObject();

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));
	ManagedReference<TradeSession*> receiverContainer = dynamic_cast<TradeSession*>(receiver->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL || receiverContainer == NULL)
		return false;

	if (tradeContainer->getTradeTargetPlayer() != receiver->getObjectID())
		return false;

	if (receiverContainer->getTradeTargetPlayer() != player->getObjectID())
		return false;

	SceneObject* playerInventory = player->getSlottedObject("inventory");
	SceneObject* receiverInventory = receiver->getSlottedObject("inventory");

	SceneObject* playerDatapad = player->getSlottedObject("datapad");
	SceneObject* receiverDatapad = receiver->getSlottedObject("datapad");

	int playerTanos = 0;
	int playerItnos = 0;
	int recieverTanos = 0;
	int recieverItnos = 0;

	for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = tradeContainer->getTradeItem(i);

		if(scene->isNoTrade())
			return false;

		if(scene->isTangibleObject()) {

			String err;
			if (receiverInventory->canAddObject(scene, -1, err) != 0)
				return false;

			if (!playerInventory->hasObjectInContainer(scene->getObjectID()))
				return false;

			recieverTanos++;

		} else if(scene->isIntangibleObject()) {

			String err;
			if (receiverDatapad->canAddObject(scene, -1, err) != 0)
				return false;

			if (!playerDatapad->hasObjectInContainer(scene->getObjectID()))
				return false;

			recieverItnos++;

		} else {
			return false;
		}
	}

	for (int i = 0; i < receiverContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = receiverContainer->getTradeItem(i);

		if(scene->isNoTrade())
			return false;

		if(scene->isTangibleObject()) {

			String err;
			if (playerInventory->canAddObject(scene, -1, err) != 0)
				return false;

			if (!receiverInventory->hasObjectInContainer(scene->getObjectID()))
				return false;

			playerTanos++;

		} else if(scene->isIntangibleObject()) {

			String err;
			if (playerDatapad->canAddObject(scene, -1, err) != 0)
				return false;

			if (!receiverDatapad->hasObjectInContainer(scene->getObjectID()))
				return false;

			playerItnos++;

		} else {
			return false;
		}
	}

	if (receiverInventory->getContainerObjectsSize() + recieverTanos >= receiverInventory->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (playerInventory->getContainerObjectsSize() + playerTanos >= playerInventory->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (receiverDatapad->getContainerObjectsSize() + recieverItnos >= receiverDatapad->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (playerDatapad->getContainerObjectsSize() + playerItnos >= playerDatapad->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	int playerMoneyToTrade = tradeContainer->getMoneyToTrade();

	if (playerMoneyToTrade < 0)
		return false;

	if (playerMoneyToTrade > player->getCashCredits())
		return false;

	int receiverMoneyToTrade = receiverContainer->getMoneyToTrade();

	if (receiverMoneyToTrade < 0)
		return false;

	if (receiverMoneyToTrade > receiver->getCashCredits())
		return false;

	if (player->getDistanceTo(receiver) >= 15.f) {
		player->sendSystemMessage("You are too far to trade");
		receiver->sendSystemMessage("You are too far to trade");
		return false;
	}


	return true;
}

void PlayerManagerImplementation::handleVerifyTradeMessage(CreatureObject* player) {
	ManagedReference<ObjectController*> objectController = server->getObjectController();

	Locker locker(player);

	ManagedReference<TradeSession*> tradeContainer = dynamic_cast<TradeSession*>(player->getActiveSession(SessionFacadeType::TRADE));

	if (tradeContainer == NULL) {
		return;
	}

	tradeContainer->setVerifiedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		Locker clocker(receiver, player);

		ManagedReference<TradeSession*> receiverTradeContainer = dynamic_cast<TradeSession*>(receiver->getActiveSession(SessionFacadeType::TRADE));

		if (receiverTradeContainer == NULL) {
			tradeContainer->setVerifiedTrade(false);
			return;
		}

		if (!checkTradeItems(player, receiver)) {
			clocker.release();
			handleAbortTradeMessage(player);

			locker.release();
			return;
		}

		if (receiverTradeContainer->hasVerifiedTrade()) {
			SceneObject* receiverInventory = receiver->getSlottedObject("inventory");
			SceneObject* receiverDatapad = receiver->getSlottedObject("datapad");

			for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = tradeContainer->getTradeItem(i);

				if(item->isTangibleObject()) {
					if (objectController->transferObject(item, receiverInventory, -1, true))
						item->sendDestroyTo(player);
				} else {
					if (objectController->transferObject(item, receiverDatapad, -1, true))
						item->sendDestroyTo(player);
				}
			}

			SceneObject* playerInventory = player->getSlottedObject("inventory");
			SceneObject* playerDatapad = player->getSlottedObject("datapad");

			for (int i = 0; i < receiverTradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = receiverTradeContainer->getTradeItem(i);

				if(item->isTangibleObject()) {
					if (objectController->transferObject(item, playerInventory, -1, true))
						item->sendDestroyTo(receiver);
				} else {
					if (objectController->transferObject(item, playerDatapad, -1, true))
						item->sendDestroyTo(receiver);
				}
			}

			uint32 giveMoney = tradeContainer->getMoneyToTrade();

			if (giveMoney > 0) {
				player->subtractCashCredits(giveMoney);
				receiver->addCashCredits(giveMoney);
			}

			giveMoney = receiverTradeContainer->getMoneyToTrade();

			if (giveMoney > 0) {
				receiver->subtractCashCredits(giveMoney);
				player->addCashCredits(giveMoney);
			}

			receiver->dropActiveSession(SessionFacadeType::TRADE);
			player->dropActiveSession(SessionFacadeType::TRADE);

			TradeCompleteMessage* msg = new TradeCompleteMessage();
			receiver->sendMessage(msg->clone());
			player->sendMessage(msg->clone());

			delete msg;
		}
	}
}

int PlayerManagerImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if (eventType == ObserverEventType::POSTURECHANGED) {
		CreatureObject* creature = cast<CreatureObject*>( observable);


		if (creature->hasState(CreatureState::ALERT)) { // This can apply to TKA AND Jedi meditate since they share the same sysmsgs / moods.
			creature->sendSystemMessage("@teraskasi:med_end");
			creature->setMood(creature->getMoodID(), true);
			creature->clearState(CreatureState::ALERT, true);

			// Check POSTERCHANGE on Meditate...
			Reference<MeditateTask*> meditateTask = cast<MeditateTask*>( creature->getPendingTask("meditate"));
			if (meditateTask != NULL) {
				creature->removePendingTask("meditate");

				if (meditateTask->isScheduled())
					meditateTask->cancel();
			}

			// Check POSTERCHANGE on Force Meditate...
			Reference<ForceMeditateTask*> fmeditateTask = cast<ForceMeditateTask*>( creature->getPendingTask("forcemeditate"));

			if (fmeditateTask != NULL) {
				creature->removePendingTask("forcemeditate");

				if (fmeditateTask->isScheduled())
					fmeditateTask->cancel();
			}
		}

		// Check POSTURECHANGED disrupting Logout...
		Reference<LogoutTask*> logoutTask = cast<LogoutTask*>(creature->getPendingTask("logout"));
		if(logoutTask != NULL) {
			logoutTask->cancelLogout();
		}
	}

	return 1;
}

void PlayerManagerImplementation::sendBattleFatigueMessage(CreatureObject* player, CreatureObject* target) {
	uint32 targetBattleFatigue = target->getShockWounds();

	uint32 playerBattleFatigue = player->getShockWounds();

	String targetName = target->getFirstName();

	if (targetBattleFatigue >= 250 && targetBattleFatigue < 500) {
		target->sendSystemMessage("@healing:shock_effect_low_target");
	} else if (targetBattleFatigue >= 500 && targetBattleFatigue < 750) {
		target->sendSystemMessage("@healing:shock_effect_medium_target");
	} else if (targetBattleFatigue >= 750) {
		target->sendSystemMessage("@healing:shock_effec_high_target");
	}

	if (playerBattleFatigue >= 250 && playerBattleFatigue < 500) {
		player->sendSystemMessage("@healing:shock_effect_low");
	} else if (playerBattleFatigue >= 500 && playerBattleFatigue < 750) {
		player->sendSystemMessage("@healing:shock_effect_medium");
	} else if (playerBattleFatigue >= 750) {
		player->sendSystemMessage("@healing:shock_effect_high");
	}
}

int PlayerManagerImplementation::healEnhance(CreatureObject* enhancer, CreatureObject* patient, byte attribute, int buffvalue, float duration) {
	String buffname = "medical_enhance_" + BuffAttribute::getName(attribute);
	uint32 buffcrc = buffname.hashCode();
	uint32 buffdiff = buffvalue;

	//If a stronger buff already exists, then we don't buff the patient.
	if (patient->hasBuff(buffcrc)) {
		Buff* buff = patient->getBuff(buffcrc);

		if (buff != NULL) {
			int value = buff->getAttributeModifierValue(attribute);

			if (value > buffvalue)
				return 0;

			buffdiff -= value;
		}
	}

	Reference<Buff*> buff = new Buff(patient, buffname.hashCode(), duration, BuffType::MEDICAL);

	if(BuffAttribute::isProtection(attribute))
			buff->setSkillModifier(BuffAttribute::getProtectionString(attribute), buffvalue);
	else{
			buff->setAttributeModifier(attribute, buffvalue);
			buff->setFillAttributesOnBuff(true);
	}

	patient->addBuff(buff);

	enhancer->notifyObservers(ObserverEventType::ENHANCINGPERFORMED, patient, buffdiff);

	return buffdiff;
}

void PlayerManagerImplementation::stopListen(CreatureObject* creature, uint64 entid, bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 listenID = creature->getListenID();

	if (object == NULL)
		return;

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot stop listening an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (entertainer == creature)
		return;

	String entName;
	ManagedReference<EntertainingSession*> esession;

	if (entertainer != NULL) {
		Locker clocker(entertainer, creature);

		entName = entertainer->getFirstName();

		ManagedReference<Facade*> session = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

		if (session != NULL) {
			esession = dynamic_cast<EntertainingSession*>(session.get());

			if (esession != NULL) {
				esession->activateEntertainerBuff(creature, PerformanceType::MUSIC);

				esession->removeListener(creature);
			}
		}

		clocker.release();
	}

	if (entid != listenID && entertainer != NULL) {
		creature->sendSystemMessage("You are not currently listening to " + entName + ".");

		return;
	}

	creature->setMood(creature->getMoodID());

	if (doSendPackets && esession != NULL)
		esession->sendEntertainmentUpdate(creature, 0, creature->getMoodString());

	if (creature->isPlayerCreature() && entertainer != NULL) {
		CreatureObject* player = cast<CreatureObject*>( creature);

		StringIdChatParameter stringID;

		if (forced) {
			stringID.setTU(entid);
			stringID.setStringId("performance", "music_stop_other");

			player->sendSystemMessage(stringID);
			//player->sendSystemMessage("performance", "dance_stop_other", params); //"%TU stops dancing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop watching " << entertainer->getFirstName() << " because they are too far away.";
			player->sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(entid);
			//player->sendSystemMessage("performance", "dance_watch_out_of_range", params); //"You stop watching %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("@performance:music_listen_stop_self"); //"You stop watching."
		}
	}

	//esession->setEntertainerBuffDuration(creature, PerformanceType::MUSIC, 0.0f); // reset
	//esession->setEntertainerBuffStrength(creature, PerformanceType::MUSIC, 0.0f);
	creature->info("stopped watching [" + entName + "]");

	//creature->setListenToID(0, true);
}


void PlayerManagerImplementation::stopWatch(CreatureObject* creature, uint64 entid, bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 watchID = creature->getWatchToID();

	if (object == NULL)
		return;

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot stop watching an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (entertainer == creature)
		return;

	ManagedReference<EntertainingSession*> esession = NULL;

	String entName;
	if (entertainer != NULL) {
		Locker clocker(entertainer, creature);

		entName = entertainer->getFirstName();

		ManagedReference<Facade*> session = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

		if (session != NULL) {
			esession = dynamic_cast<EntertainingSession*>(session.get());

			if (esession != NULL) {
				esession->activateEntertainerBuff(creature, PerformanceType::DANCE);

				esession->removeWatcher(creature);
			}
		}

		clocker.release();
	}

	if (entid != watchID) {
		creature->sendSystemMessage("You are not currently watching " + entName + ".");

		return;
	}

	creature->setMood(creature->getMoodID());

	if (doSendPackets && esession != NULL)
		esession->sendEntertainmentUpdate(creature, 0, creature->getMoodString());

	//System Message.
	if (creature->isPlayerCreature() && entertainer != NULL) {
		CreatureObject* player = cast<CreatureObject*>( creature);

		StringIdChatParameter stringID;
		//StfParameter* params = new StfParameter;

		if (forced) {
			stringID.setTU(entid);
			stringID.setStringId("performance", "dance_stop_other");

			player->sendSystemMessage(stringID);
			//player->sendSystemMessage("performance", "dance_stop_other", params); //"%TU stops dancing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop watching " << entertainer->getFirstName() << " because they are too far away.";
			player->sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(entid);
			//player->sendSystemMessage("performance", "dance_watch_out_of_range", params); //"You stop watching %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("@performance:dance_watch_stop_self"); //"You stop watching."
		}
	}


	//esession->setEntertainerBuffDuration(creature, PerformanceType::DANCE, 0.0f); // reset
	//esession->setEntertainerBuffStrength(creature, PerformanceType::DANCE, 0.0f);
	creature->info("stopped watching [" + entName + "]");

	creature->setWatchToID(0);
	/*doWatching = false;
	watchID = 0;*/
}

void PlayerManagerImplementation::startWatch(CreatureObject* creature, uint64 entid) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 watchID = creature->getWatchToID();

	if (object == NULL)
		return;

	/*if (object->isNonPlayerCreature()) {
		creature->sendSystemMessage("@performance:dance_watch_npc");
		return;
	}*/

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot start watching an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (creature == entertainer)
		return;

	Locker clocker(entertainer, creature);

	if (creature->isDancing() || creature->isPlayingMusic()) {
		creature->sendSystemMessage("You cannot /watch while skill animating.");

		return;
	} else if (!entertainer->isDancing()) {
		creature->sendSystemMessage(entertainer->getCustomObjectName().toString() + " is not currently dancing.");

		return;
	} else if (entid == watchID) {
		creature->sendSystemMessage("You are already watching " + entertainer->getCustomObjectName().toString() + ".");

		return;
	}

	ManagedReference<Facade*> facade = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return;

	EntertainingSession* entertainingSession = dynamic_cast<EntertainingSession*>(facade.get());

	if (entertainingSession == NULL)
		return;

	if (creature->isWatching()) {
		stopWatch(creature, watchID, false);
	}

	//sendEntertainmentUpdate(entid, "entertained");

	entertainingSession->sendEntertainmentUpdate(creature, entid, "entertained");
	entertainingSession->addWatcher(creature);

	//creature->addWatcher(_this);

	//if (isPlayer())
	creature->sendSystemMessage("You begin watching " + entertainer->getCustomObjectName().toString() + ".");

	//setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	//setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	creature->info("started watching [" + entertainer->getCustomObjectName().toString() + "]");

	creature->setWatchToID(entertainer->getObjectID());
	//watchID =  entid;
}

void PlayerManagerImplementation::startListen(CreatureObject* creature, uint64 entid) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 listenID = creature->getListenID();

	if (object == NULL)
		return;

	/*if (object->isNonPlayerCreature()) {
		creature->sendSystemMessage("@performance:dance_watch_npc");
		return;
	}*/

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot start listening an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (creature == entertainer)
		return;

	Locker clocker(entertainer, creature);

	if (creature->isDancing() || creature->isPlayingMusic()) {
		creature->sendSystemMessage("You cannot /watch while skill animating.");

		return;
	} else if (!entertainer->isPlayingMusic()) {
		creature->sendSystemMessage(entertainer->getCustomObjectName().toString() + " is not currently playing music.");

		return;
	} else if (entid == listenID) {
		creature->sendSystemMessage("You are already listening " + entertainer->getCustomObjectName().toString() + ".");

		return;
	}

	ManagedReference<Facade*> facade = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return;

	EntertainingSession* entertainingSession = dynamic_cast<EntertainingSession*>(facade.get());

	if (entertainingSession == NULL)
		return;

	if (creature->isListening()) {
		stopListen(creature, listenID, false);
	}

	//sendEntertainmentUpdate(entid, "entertained");

	entertainingSession->sendEntertainmentUpdate(creature, entid, "entertained");
	entertainingSession->addListener(creature);

	//creature->addWatcher(_this);

	//if (isPlayer())
	creature->sendSystemMessage("You begin to listen " + entertainer->getCustomObjectName().toString() + ".");

	//setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	//setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	creature->info("started watching [" + entertainer->getCustomObjectName().toString() + "]");

	creature->setListenToID(entertainer->getObjectID());
	//watchID =  entid;
}


SceneObject* PlayerManagerImplementation::getInRangeStructureWithAdminRights(CreatureObject* creature, uint64 targetID) {
	ZoneServer* zoneServer = server;

	//First we need to check if the target. if it's not right...
	//Check the building they are standing in, if it's not right...
	//Find the nearest installation.

	ManagedReference<SceneObject*> obj = NULL;

	if (targetID != 0) {
		obj = zoneServer->getObject(targetID);

		if (obj != NULL && obj->isStructureObject() && (cast<StructureObject*>(obj.get()))->isOnAdminList(creature))
			return obj.get();
	}


	ManagedReference<SceneObject*> rootParent = creature->getRootParent();

	if (rootParent != NULL && rootParent->isStructureObject() && (cast<StructureObject*>(rootParent.get()))->isOnAdminList(creature)) {
		return rootParent;
	}

	StructureObject* structure = NULL;
	float distance = 16000;

	Zone* zone = creature->getZone();

	if (zone == NULL) {
		return NULL;
	}

	//We need to search nearby for an installation that belongs to the player.
	Locker _locker(zone);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = creature->getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		ManagedReference<SceneObject*> tObj = cast<SceneObject*>( closeObjects->get(i).get());

		if (tObj != NULL) {
			if (tObj->isStructureObject()) {
				float dist = tObj->getDistanceTo(creature);

				StructureObject* structureObject = cast<StructureObject*>( tObj.get());

				if (structureObject->isOnAdminList(creature) && dist < distance) {
					structure = structureObject;
					distance = dist;
				}
			}
		}
	}

	if (distance < 25)
		return structure;

	return NULL;
}

StructureObject* PlayerManagerImplementation::getInRangeOwnedStructure(CreatureObject* creature, float range) {
	Locker _lock(creature);

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return NULL;

	ManagedReference<StructureObject*> closestStructure = NULL;
	float closestDistance = 16000.f;

	for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
		uint64 oid = ghost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = cast<StructureObject*>(ghost->getZoneServer()->getObject(oid));

		Locker _slock(structure, creature);

		if (creature->getZone() != structure->getZone())
			continue;

		float distance = structure->getDistanceTo(creature);

		if (distance <= range && distance < closestDistance) {
			closestStructure = structure;
			closestDistance = distance;
		}
	}

	return closestStructure;
}

void PlayerManagerImplementation::updatePermissionLevel(CreatureObject* targetPlayer, int permissionLevel) {

	if (targetPlayer == NULL) {
		return;
	}

	//Locker clocker(targetPlayer, player);
	Locker locker(targetPlayer);
	ManagedReference<PlayerObject*> ghost = targetPlayer->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	SkillManager* skillManager = server->getSkillManager();

	int currentPermissionLevel = ghost->getAdminLevel();

	/*Temporarily removed so that we can update admin levels immediately
	if(currentPermissionLevel == permissionLevel)
		return;*/

	if (currentPermissionLevel != 0) {
		Vector<String>* skillsToBeRemoved = permissionLevelList->getPermissionSkills(currentPermissionLevel);
		if(skillsToBeRemoved != NULL) {
			for(int i = 0; i < skillsToBeRemoved->size(); i++) {
				String skill = skillsToBeRemoved->get(i);
				targetPlayer->sendSystemMessage("Staff skill revoked: " + skill);
				skillManager->surrenderSkill(skill, targetPlayer, true);
			}
		}
	}

	if(permissionLevel != 0) {
		Vector<String>* skillsToBeAdded = permissionLevelList->getPermissionSkills(permissionLevel);
		if(skillsToBeAdded != NULL) {
			for(int i = 0; i < skillsToBeAdded->size(); ++i) {
				String skill = skillsToBeAdded->get(i);
				targetPlayer->sendSystemMessage("Staff skill granted: " + skill);
				skillManager->awardSkill(skill, targetPlayer, false, true, true);
			}
		}
	}

	ghost->setAdminLevel(permissionLevel);
	updatePermissionName(targetPlayer, permissionLevel);
}

void PlayerManagerImplementation::updatePermissionName(CreatureObject* player, int permissionLevel) {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	//Send deltas
	if (player->isOnline()) {
		UnicodeString tag = permissionLevelList->getPermissionTag(permissionLevel);

		TangibleObjectDeltaMessage3* tanod3 = new TangibleObjectDeltaMessage3(player);
		tanod3->updateName(player->getDisplayedName(), tag);
		tanod3->close();
		player->broadcastMessage(tanod3, true);

		/*PlayerObjectDeltaMessage6* playd6 = new PlayerObjectDeltaMessage6(ghost);
			playd6->setAdminLevel(adminLevel);
			playd6->close();
			player->broadcastMessage(playd6, true);*/
	}
}

void PlayerManagerImplementation::updateSwimmingState(CreatureObject* player, float newZ) {
	player->notifySelfPositionUpdate();
	if (player->getParent() != NULL) {
		return;
	}

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == NULL) {
		player->info("No zone.", true);
		return;
	}

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	if (planetManager == NULL) {
		player->info("No planet manager.", true);
		return;
	}

	ManagedReference<TerrainManager*> terrainManager = planetManager->getTerrainManager();

	if (terrainManager == NULL) {
		player->info("No terrain manager.", true);
		return;
	}

	float landHeight = zone->getHeight(player->getPositionX(), player->getPositionY());
	float waterHeight;
	terrainManager->getWaterHeight(player->getPositionX(), player->getPositionY(), waterHeight);

	if ((waterHeight > landHeight) && (landHeight + player->getSwimHeight() - waterHeight < 0.2)) {
		//Water level is higher than the terrain level and is deep enough for the player to be swimming.
		//Check if the player is on a bridge or other terrain above the water level.
		SortedVector<IntersectionResult> intersections;

		CollisionManager::getWorldFloorCollisions(player->getPositionX(), player->getPositionY(), zone, true, &intersections);

		for (int i = 0; i < intersections.size(); i++) {
			if (fabs(16384 - intersections.get(i).getIntersectionDistance() - newZ) < 0.2) {
				//Player is on terrain above the water.
				player->clearState(CreatureState::SWIMMING, true);
				return;
			}
		}

		//Player is in the water.
		player->setState(CreatureState::SWIMMING, true);
		return;
	}

	//Terrain is above water level.
	player->clearState(CreatureState::SWIMMING, true);
}

int PlayerManagerImplementation::checkSpeedHackFirstTest(CreatureObject* player, float parsedSpeed, ValidatedPosition& teleportPosition, float errorMultiplier) {
	float allowedSpeedMod = player->getSpeedMultiplierMod();
	float allowedSpeedBase = player->getRunSpeed();
	ManagedReference<SceneObject*> parent = player->getParent();
	SpeedMultiplierModChanges* changeBuffer = player->getSpeedMultiplierModChanges();
	Vector3 teleportPoint = teleportPosition.getPosition();
	uint64 teleportParentID = teleportPosition.getParent();

	if (parent != NULL && parent->isVehicleObject()) {
		VehicleObject* vehicle = cast<VehicleObject*>( parent.get());

		allowedSpeedMod = vehicle->getSpeedMultiplierMod();
		allowedSpeedBase = vehicle->getRunSpeed();
	}

	float maxAllowedSpeed = allowedSpeedMod * allowedSpeedBase;

	if (parsedSpeed > maxAllowedSpeed * errorMultiplier) {
		//float delta = abs(parsedSpeed - maxAllowedSpeed);

		if (changeBuffer->size() == 0) { // no speed changes
			StringBuffer msg;
			msg << "max allowed speed should be " << maxAllowedSpeed * errorMultiplier;
			msg << " parsed " << parsedSpeed;
			player->info(msg.toString());

			player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return 1;
		}

		SpeedModChange* firstChange = &changeBuffer->get(changeBuffer->size() - 1);
		Time* timeStamp = &firstChange->getTimeStamp();

		if (timeStamp->miliDifference() > 2000) { // we already should have lowered the speed, 2 seconds lag
			StringBuffer msg;
			msg << "max allowed speed should be " << maxAllowedSpeed * errorMultiplier;
			msg << " parsed " << parsedSpeed;
			player->info(msg.toString());

			player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return 1;
		}

		for (int i = 0; i < changeBuffer->size() - 1; ++i) {
			SpeedModChange* change = &changeBuffer->get(i);
			//Time timeStamp = change->getTimeStamp();

			float oldSpeedMod = change->getNewSpeed();
			float allowed = allowedSpeedBase * oldSpeedMod * errorMultiplier;

			if (allowed >= parsedSpeed) {
				return 0; // no hack detected
			}

			if (allowed > maxAllowedSpeed)
				maxAllowedSpeed = allowed;
		}

		StringBuffer msg;
		msg << "max allowed speed should be " << maxAllowedSpeed;
		msg << " parsed " << parsedSpeed;
		msg << " changeBufferSize: " << changeBuffer->size();

		player->info(msg.toString());

		player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

		return 1;
	}

	return 0;
}

int PlayerManagerImplementation::checkSpeedHackSecondTest(CreatureObject* player, float newX, float newZ, float newY, uint32 newStamp, SceneObject* newParent) {
	PlayerObject* ghost = player->getPlayerObject();

	uint32 deltaTime = ghost->getServerMovementTimeDelta();//newStamp - stamp;

	if (deltaTime < 1000) {
		//info("time hasnt passed yet", true);
		return 0;
	}

	uint32 stamp = ghost->getClientLastMovementStamp();

	if (stamp > newStamp) {
		//info("older stamp received", true);
		return 1;
	}

	Vector3 newWorldPosition(newX, newY, newZ);

	/*StringBuffer newWorldPosMsg;
	newWorldPosMsg << "x:" << newWorldPosition.getX() << " z:" << newWorldPosition.getZ() << " y:" << newWorldPosition.getY();
	player->info(newWorldPosMsg.toString(), true);*/

	if (newParent != NULL) {
		ManagedReference<SceneObject*> root = newParent->getRootParent();

		if (!root->isBuildingObject())
			return 1;

		float length = Math::sqrt(newX * newX + newY * newY);
		float angle = root->getDirection()->getRadians() + atan2(newX, newY);

		newWorldPosition.set(root->getPositionX() + (sin(angle) * length), root->getPositionZ() + newZ, root->getPositionY() + (cos(angle) * length));
	}

	/*newWorldPosMsg.deleteAll();
	newWorldPosMsg << "x:" << newWorldPosition.getX() << " z:" << newWorldPosition.getZ() << " y:" << newWorldPosition.getY();
	player->info(newWorldPosMsg.toString(), true);*/

	ValidatedPosition* lastValidatedPosition = ghost->getLastValidatedPosition();

	Vector3 lastValidatedWorldPosition = lastValidatedPosition->getWorldPosition(server);

	//ignoring Z untill we have all heightmaps
	float oldValidZ = lastValidatedWorldPosition.getZ();
	float oldNewPosZ = newWorldPosition.getZ();

	lastValidatedWorldPosition.setZ(0);
	newWorldPosition.setZ(0);

	float dist = newWorldPosition.distanceTo(lastValidatedWorldPosition);

	if (dist < 1) {
		//info("distance too small", true);
		return 0;
	}

	float speed = dist / (float) deltaTime * 1000;

	/*if (oldNewPosZ > oldValidZ) {
		float heightDist = oldNewPosZ - oldValidZ;

		//if (heightDist > speed) {
			StringBuffer msg;
			msg << " heightDist:" << heightDist << " speed:" << speed << " terrain neg:" << player->getSlopeModPercent();
			player->info(msg.toString(), true);
		//}
	}*/

	//lastValidatedPosition->set(newWorldPosition.getX(), oldNewPosZ, newWorldPosition.getY());

	/*StringBuffer msg;
	msg << "distancia recorreguda " << dist << " a una velocitat " << speed;
	info(msg, true);*/

	int ret = checkSpeedHackFirstTest(player, speed, *lastValidatedPosition, 1.5f);

	if (ret == 0) {
		lastValidatedPosition->setPosition(newX, newZ, newY);

		if (newParent != NULL)
			lastValidatedPosition->setParent(newParent->getObjectID());
		else
			lastValidatedPosition->setParent(0);

		ghost->updateServerLastMovementStamp();
	}

	return ret;

	//return 0;
}

void PlayerManagerImplementation::lootAll(CreatureObject* player, CreatureObject* ai) {
	Locker locker(ai, player);

	if (!ai->isDead() || player->isDead())
		return;

	if (ai->getDistanceTo(player) > 6) {
		player->sendSystemMessage("@pet/droid_modules:corpse_too_far");
		return;
	}

	SceneObject* creatureInventory = ai->getSlottedObject("inventory");

	if (creatureInventory == NULL)
		return;

	if (creatureInventory->getContainerPermissions()->getOwnerID() != player->getObjectID() && creatureInventory->getContainerPermissions()->getOwnerID() != player->getGroupID()) {
		player->sendSystemMessage("@group:no_loot_permission");

		return;
	}

	int cashCredits = ai->getCashCredits();

	if (cashCredits > 0) {
		player->addCashCredits(cashCredits, true);
		ai->setCashCredits(0);

		StringIdChatParameter param("base_player", "prose_coin_loot"); //You loot %DI credits from %TT.
		param.setDI(cashCredits);
		param.setTT(ai);

		player->sendSystemMessage(param);
	}

	SceneObject* playerInventory = player->getSlottedObject("inventory");

	if (playerInventory == NULL)
		return;

	int totalItems = creatureInventory->getContainerObjectsSize();

	if (totalItems < 1) {
		rescheduleCorpseDestruction(player, ai);
		return;
	}

	StringBuffer args;
	args << playerInventory->getObjectID() << " -1 0 0 0";

	String stringArgs = args.toString();

	for (int i = totalItems - 1; i >= 0; --i) {
		SceneObject* object = creatureInventory->getContainerObject(i);

		player->executeObjectControllerAction(String("transferitemmisc").hashCode(), object->getObjectID(), stringArgs);
	}

	if (creatureInventory->getContainerObjectsSize() <= 0)
		player->sendSystemMessage("@base_player:corpse_looted"); //You have completely looted the corpse of all items.

	rescheduleCorpseDestruction(player, ai);
}

void PlayerManagerImplementation::generateHologrindSkills(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint8> profs;
	//Fill the total profs array.
	for (int i = 0; i < 32; ++i)
		profs.put(i + 1);

	// TODO: Remove ungrindable professions (temporary.)
	// Commando.
	profs.drop(5);
	// Droid Engineer.
	profs.drop(16);
	// Bio-Engineer.
	profs.drop(20);
	// Creature Handler.
	profs.drop(21);
	// Politician.
	profs.drop(32);

	uint8 totalProfsNeeded = 6; // Six for the time being (static amount), if number is altered, please also change method in awardBadge that calls finishHologrind.

	for (int i = 0; i < totalProfsNeeded; ++i) {
		uint8 prof = profs.remove(System::random(profs.size() - 1));
		ghost->addHologrindProfession(prof);
	}

}

void PlayerManagerImplementation::sendStartingLocationsTo(CreatureObject* player) {
	StartingLocationListMessage* slm = new StartingLocationListMessage(player);
	startingLocationList.insertToMessage(slm);

	player->sendMessage(slm);
}

StartingLocation* PlayerManagerImplementation::getStartingLocation(const String& city) {
	for (int i = 0; i < startingLocationList.size(); ++i) {
		StartingLocation* loc = &startingLocationList.get(i);

		if (loc == NULL)
			continue;

		if (loc->getLocation() == city)
			return loc;
	}

	return NULL;
}

void PlayerManagerImplementation::addInsurableItemsRecursive(SceneObject* obj, SortedVector<ManagedReference<SceneObject*> >* items, bool onlyInsurable) {
	for (int j = 0; j < obj->getContainerObjectsSize(); j++) {
		SceneObject* object = obj->getContainerObject(j);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* item = cast<TangibleObject*>( object);

		if (item != NULL && !(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject())) {
			items->put(item);
		} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
			items->put(item);
		}

		if (object->isContainerObject())
			addInsurableItemsRecursive(object, items, onlyInsurable);
	}
}

SortedVector<ManagedReference<SceneObject*> > PlayerManagerImplementation::getInsurableItems(CreatureObject* player, bool onlyInsurable) {
	SortedVector<ManagedReference<SceneObject*> > insurableItems;
	insurableItems.setNoDuplicateInsertPlan();

	if (player == NULL)
		return insurableItems;

	SceneObject* datapad = player->getSlottedObject("datapad");
	SceneObject* defweapon = player->getSlottedObject("default_weapon");
	SceneObject* bank = player->getSlottedObject("bank");

	for (int i = 0; i < player->getSlottedObjectsSize(); ++i) {
		SceneObject* container = player->getSlottedObject(i);

		if (container == datapad || container == NULL || container == bank || container == defweapon)
			continue;

		if (container->isTangibleObject()) {
			TangibleObject* item = cast<TangibleObject*>( container);

			if (item != NULL && !(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject())) {
				insurableItems.put(item);
			} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
				insurableItems.put(item);
			}
		}

		addInsurableItemsRecursive(container, &insurableItems, onlyInsurable);
	}

	return insurableItems;
}

int PlayerManagerImplementation::calculatePlayerLevel(CreatureObject* player) {
	ManagedReference<WeaponObject*> weapon = player->getWeapon();

	if (weapon == NULL) {
		player->error("player with NULL weapon");

		return 0;
	}

	String weaponType = weapon->getWeaponType();

	int level = MIN(25, player->getSkillMod("private_" + weaponType + "_combat_difficulty") / 100 + 1);

	return level;
}

String PlayerManagerImplementation::getBadgeKey(int idx) {
	VectorMapEntry<int, String> entry = badgeMap.elementAt(idx);

	return entry.getValue();
}

CraftingStation* PlayerManagerImplementation::getNearbyCraftingStation(CreatureObject* player, int type) {

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == NULL)
		return NULL;

	ManagedReference<ZoneServer*> server = zone->getZoneServer();

	if (server == NULL)
		return NULL;

	ManagedReference<CraftingStation*> station = NULL;

	//Locker locker(zone);

	SortedVector < QuadTreeEntry* > *closeObjects = new SortedVector<QuadTreeEntry*>(100, 50);
	CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();
	vec->safeCopyTo(*closeObjects);

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* scno = cast<SceneObject*> (closeObjects->get(i));

		if (scno->isCraftingStation() && (abs(scno->getPositionZ() - player->getPositionZ()) < 7.0f) && player->isInRange(scno, 7.0f)) {

			station = cast<CraftingStation*> (server->getObject(scno->getObjectID()));

			if (station == NULL)
				continue;

			if (type == station->getStationType() || (type
					== CraftingTool::JEDI && station->getStationType()
					== CraftingTool::WEAPON)) {

				return station;
			}
		}
	}

	return NULL;
}

void PlayerManagerImplementation::finishHologrind(CreatureObject* player) {

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HOLOGRIND_UNLOCK))
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::NONE);
	box->setPromptTitle("@quest/force_sensitive/intro:force_sensitive"); // You feel a tingle in the Force.
	box->setPromptText("Perhaps you should meditate somewhere alone...");

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	SkillManager::instance()->awardSkill("force_title_jedi_novice", player, true, false, true);

	ghost->setJediState(1);

}

Account* PlayerManagerImplementation::getAccount(const String& username) {

	String name = username;

	Database::escapeString(name);

	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.username = '" << name << "' LIMIT 1;";

	return queryForAccount(query.toString());
}

Account* PlayerManagerImplementation::getAccount(uint32 accountID) {

	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	return queryForAccount(query.toString());
}

Account* PlayerManagerImplementation::queryForAccount(const String& query) {
	Account* account = NULL;

	Reference<ResultSet*> result;

	try {
		result = ServerDatabase::instance()->executeQuery(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	if (result != NULL && result->next()) {

		account = new Account();

		account->setActive(result->getBoolean(0));
		account->setUsername(result->getString(1));

		account->setAccountID(result->getUnsignedInt(4));
		account->setStationID(result->getUnsignedInt(5));

		account->setTimeCreated(result->getUnsignedInt(6));
		account->setAdminLevel(result->getInt(7));

		account->updateFromDatabase();
	}

	result = NULL;

	return account;
}

String PlayerManagerImplementation::banAccount(PlayerObject* admin, Account* account, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "INSERT INTO account_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << ", now(), " << (uint64)time(0) + seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning account: " + e.getMessage();
	}

	try {

		CharacterList* characters = account->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == server->getGalaxyID()) {

				ManagedReference<CreatureObject*> player = getPlayer(entry->getFirstName());
				if(player != NULL && player->isOnline()) {

					player->sendMessage(new LogoutMessage());

					Reference<ZoneClientSession*> session = player->getClient();

					if(session != NULL)
						session->disconnect(true);
				}
			}
		}
	} catch(Exception& e) {
		return "Account Successfully Banned, but error kicking characters. " + e.getMessage();
	}

	return "Account Successfully Banned";
}

String PlayerManagerImplementation::unbanAccount(PlayerObject* admin, Account* account, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "UPDATE account_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "'  WHERE account_id = " << account->getAccountID() << " and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception unbanning account: " + e.getMessage();
	}

	return "Account Successfully Unbanned";
}

String PlayerManagerImplementation::banFromGalaxy(PlayerObject* admin, Account* account, const uint32 galaxy, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "INSERT INTO galaxy_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << "," << galaxy << ", now()," << (uint64)time(0) + seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning from galaxy: " + e.getMessage();
	}

	try {

		CharacterList* characters = account->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == server->getGalaxyID()) {

				ManagedReference<CreatureObject*> player = getPlayer(entry->getFirstName());
				if(player != NULL && player->isOnline()) {

					player->sendMessage(new LogoutMessage());

					ManagedReference<ZoneClientSession*> session = player->getClient();

					if(session != NULL)
						session->disconnect(true);
				}
			}
		}
	} catch(Exception& e) {
		return "Successfully Banned from Galaxy, but error kicking characters. " + e.getMessage();
	}

	return "Successfully Banned from Galaxy";
}

String PlayerManagerImplementation::unbanFromGalaxy(PlayerObject* admin, Account* account, const uint32 galaxy, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;

		query << "UPDATE galaxy_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "' WHERE account_id = " <<  account->getAccountID() << " and galaxy_id = " << galaxy << " and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception unbanning from galaxy: " + e.getMessage();
	}

	return "Successfully Unbanned from Galaxy";
}

String PlayerManagerImplementation::banCharacter(PlayerObject* admin, Account* account, const String& name, const uint32 galaxyID, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	String escapedName = name;
	Database::escapeString(escapedName);

	try {
		StringBuffer query;
		query << "INSERT INTO character_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << ", " << galaxyID << ", '" << escapedName << "', " <<  "now(), UNIX_TIMESTAMP() + " << seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning character: " + e.getMessage();
	}

	try {
		ManagedReference<CreatureObject*> player = getPlayer(name);
		if(player != NULL && player->isOnline()) {

			player->sendMessage(new LogoutMessage());

			ManagedReference<ZoneClientSession*> session = player->getClient();

			if(session != NULL)
				session->disconnect(true);
		}
	} catch(Exception& e) {
		return "Character Successfully Banned, but error kicking Character. " + e.getMessage();
	}

	return "Character Successfully Banned";
}

String PlayerManagerImplementation::unbanCharacter(PlayerObject* admin, Account* account, const String& name, const uint32 galaxyID, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	String escapedName = name;
	Database::escapeString(escapedName);

	try {
		StringBuffer query;
		query << "UPDATE character_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "' WHERE account_id = " <<  account->getAccountID() << " AND galaxy_id = " << galaxyID << " and name =  '" << escapedName << "' and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning character: " + e.getMessage();
	}

	return "Character Successfully Unbanned";
}

void PlayerManagerImplementation::fixHAM(CreatureObject* player) {
	Locker locker(player);

	try {
		BuffList* buffs = player->getBuffList();

		VectorMap<byte, int> attributeValues;
		attributeValues.setNullValue(0);
		attributeValues.setAllowOverwriteInsertPlan();

		ManagedReference<Buff*> powerBoost;

		//check buffs
		for (int i = 0; i < buffs->getBuffListSize(); ++i) {
			ManagedReference<Buff*> buff = buffs->getBuffByIndex(i);

			PowerBoostBuff* power = dynamic_cast<PowerBoostBuff*>(buff.get());

			if (power != NULL) {
				powerBoost = power;
				continue;
			}

			VectorMap<byte, int>* attributeModifiers = buff->getAttributeModifiers();

			for (int j = 0; j < attributeModifiers->size(); ++j) {
				byte modifier = attributeModifiers->elementAt(j).getKey();
				int val = attributeModifiers->elementAt(j).getValue();

				attributeValues.put(modifier, attributeValues.get(modifier) + val);
			}
		}

		if (powerBoost != NULL)
			player->removeBuff(powerBoost);

		int encumbranceType = -1;

		for (int i = 0; i < 9; ++i) {
			int maxModifier = attributeValues.get((byte)i);
			int baseHam = player->getBaseHAM(i);
			int max = player->getMaxHAM(i);

			int calculated = baseHam + maxModifier;

			if (i % 3 == 0) {
				++encumbranceType;
			} else {
				calculated -= player->getEncumbrance(encumbranceType);
			}

			//info("attribute: " + CreatureAttribute::getName(i, true) + " max = " + String::valueOf(max) + " calculatedMax = " + String::valueOf(calculated), true);

			if (calculated != max && calculated > 1) {
				if (player->getHAM(i) > calculated)
					player->setHAM(i, calculated, false);

				player->setMaxHAM(i, calculated, false);
			}
		}
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

bool PlayerManagerImplementation::promptTeachableSkills(CreatureObject* teacher, SceneObject* target) {
	if (target == NULL || !target->isPlayerCreature()) {
		teacher->sendSystemMessage("@teaching:no_target"); //Whom do you want to teach?
		return false;
	}

	if (target == teacher) {
		teacher->sendSystemMessage("@teaching:no_teach_self"); //You cannot teach yourself.
		return false;
	}

	Locker _lock(teacher, target);

	//We checked if they had the player object in slot with isPlayerCreature
	CreatureObject* student = cast<CreatureObject*>(target);

	if (teacher->getGroup() == NULL || student->getGroup() != teacher->getGroup()) {
		StringIdChatParameter params("teaching", "not_in_same_group"); //You must be within the same group as %TT in order to teach.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	if (student->isDead()) {
		StringIdChatParameter params("teaching", "student_dead"); //%TT does not feel like being taught right now.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	if (!student->isInRange(teacher, 32.f)) {
		teacher->sendSystemMessage("@teaching:student_too_far"); // Your student must be nearby in order to teach.
		return false;
	}

	ManagedReference<PlayerObject*> studentGhost = student->getPlayerObject();

	//Do they have an outstanding teaching offer?
	if (studentGhost->hasSuiBoxWindowType(SuiWindowType::TEACH_OFFER)) {
		StringIdChatParameter params("teaching", "student_has_offer_to_learn"); //%TT already has an offer to learn.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	SortedVector<String> skills = getTeachableSkills(teacher, student);

	if (skills.size() <= 0) {
		StringIdChatParameter params("teaching", "no_skills_for_student"); //You have no skills that  %TT can currently learn."
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(teacher, SuiWindowType::TEACH_SKILL);
	listbox->setUsingObject(student);
	listbox->setForceCloseDistance(32.f);
	listbox->setPromptTitle("SELECT SKILL");
	listbox->setPromptText("Select a skill to teach.");
	listbox->setCancelButton(true, "@cancel");

	for (int i = 0; i < skills.size(); ++i) {
		String skill = skills.get(i);
		listbox->addMenuItem("@skl_n:" + skill, skill.hashCode());
	}

	listbox->setCallback(new PlayerTeachSuiCallback(server));

	if (teacher->isPlayerCreature()) {
		ManagedReference<PlayerObject*> teacherGhost = teacher->getPlayerObject();

		teacherGhost->addSuiBox(listbox);
	}

	teacher->sendMessage(listbox->generateMessage());

	return true;
}

bool PlayerManagerImplementation::offerTeaching(CreatureObject* teacher, CreatureObject* student, Skill* skill) {
	ManagedReference<PlayerObject*> studentGhost = student->getPlayerObject();

	//Do they have an outstanding teaching offer?
	if (studentGhost->hasSuiBoxWindowType(SuiWindowType::TEACH_OFFER)) {
		StringIdChatParameter params("teaching", "student_has_offer_to_learn"); //%TT already has an offer to learn.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	ManagedReference<SuiMessageBox*> suibox = new SuiMessageBox(teacher, SuiWindowType::TEACH_OFFER);
	suibox->setUsingObject(teacher);
	suibox->setForceCloseDistance(32.f);
	suibox->setPromptTitle("@sui:swg"); //Star Wars Galaxies

	StringIdManager* sidman = StringIdManager::instance();

	String sklname = sidman->getStringId(String("@skl_n:" + skill->getSkillName()).hashCode()).toString();
	String expname = sidman->getStringId(String("@exp_n:" + skill->getXpType()).hashCode()).toString();

	StringBuffer prompt;
	prompt << teacher->getDisplayedName()
							<< " has offered to teach you " << sklname << " (" << skill->getXpCost()
							<< " " << expname  << " experience cost).";

	suibox->setPromptText(prompt.toString());
	suibox->setCallback(new PlayerTeachConfirmSuiCallback(server, skill));

	suibox->setOkButton(true, "@yes");
	suibox->setCancelButton(true, "@no");

	studentGhost->addSuiBox(suibox);
	student->sendMessage(suibox->generateMessage());

	StringIdChatParameter params("teaching", "offer_given"); //You offer to teach %TT %TO.
	params.setTT(student->getDisplayedName());
	params.setTO("@skl_n:" + skill->getSkillName());
	teacher->sendSystemMessage(params);

	return true;
}

bool PlayerManagerImplementation::acceptTeachingOffer(CreatureObject* teacher, CreatureObject* student, Skill* skill) {
	if (teacher->getGroup() == NULL || student->getGroup() != teacher->getGroup()) {
		StringIdChatParameter params("teaching", "not_in_same_group"); //You must be within the same group as %TT in order to teach.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	//Check to see if the teacher still has the skill and the student can still learn the skill.
	SkillManager* skillManager = SkillManager::instance();

	if (!student->isInRange(teacher, 32.f)) {
		StringIdChatParameter params("teaching", "teacher_too_far_target"); //You are too far away from %TT to learn.
		params.setTT(teacher->getDisplayedName());
		student->sendSystemMessage(params);

		params.setStringId("teaching", "student_too_far_target");
		params.setTT(student->getDisplayedName()); //You are too far away from %TT to teach.
		teacher->sendSystemMessage(params);
		return false;
	}

	if (teacher->hasSkill(skill->getSkillName()) && skillManager->awardSkill(skill->getSkillName(), student, true, false, false)) {
		StringIdChatParameter params("teaching", "student_skill_learned"); //You learn %TO from %TT.
		params.setTO("@skl_n:" + skill->getSkillName());
		params.setTT(teacher->getDisplayedName());
		student->sendSystemMessage(params);

		params.setStringId("teaching", "teacher_skill_learned"); //%TT learns %TO from you.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);

		if (skillManager->isApprenticeshipEnabled() && !skill->getSkillName().endsWith("novice")) {
			int exp = 10 + (skill->getTotalChildren() * 10);

			StringIdChatParameter params("teaching", "experience_received"); //You have received %DI Apprenticeship experience.
			params.setDI(exp);
			teacher->sendSystemMessage(params);

			awardExperience(teacher, "apprenticeship", exp, false);
		}
	} else {
		student->sendSystemMessage("@teaching:learning_failed"); //Learning failed.
		teacher->sendSystemMessage("@teaching:teaching_failed"); //Teaching failed.
		return false;
	}

	return true;
}

SortedVector<String> PlayerManagerImplementation::getTeachableSkills(CreatureObject* teacher, CreatureObject* student) {
	SortedVector<String> skills;
	skills.setNoDuplicateInsertPlan();

	SkillList* skillList = teacher->getSkillList();

	SkillManager* skillManager = SkillManager::instance();

	for (int i = 0; i < skillList->size(); ++i) {
		Skill* skill = skillList->get(i);

		String skillName = skill->getSkillName();

		if (!skillName.contains("novice") && skillManager->canLearnSkill(skillName, student, false))
			skills.put(skillName);
	}

	return skills;
}

void PlayerManagerImplementation::decreaseOnlineCharCount(ZoneClientSession* client) {
	Locker locker(&onlineMapMutex);

	uint32 accountId = client->getAccountID();

	if (!onlineZoneClientMap.containsKey(accountId))
		return;

	BaseClientProxy* session = client->getSession();



	Vector<Reference<ZoneClientSession*> > clients = onlineZoneClientMap.get(accountId);

	for (int i = 0; i < clients.size(); ++i)
		if (clients.get(i) == client) {
			clients.remove(i);

			break;
		}

	if (clients.size() == 0)
		onlineZoneClientMap.remove(accountId);
	else
		onlineZoneClientMap.put(accountId, clients);

	locker.release();

	if (session != NULL) {
		onlineZoneClientMap.accountLoggedOut(session->getIPAddress(), accountId);
	}
}

bool PlayerManagerImplementation::increaseOnlineCharCountIfPossible(ZoneClientSession* client) {
	Locker locker(&onlineMapMutex);

	uint32 accountId = client->getAccountID();

	BaseClientProxy* session = client->getSession();

	if (!onlineZoneClientMap.containsKey(accountId)) {
		Vector<Reference<ZoneClientSession*> > clients;
		clients.add(client);

		onlineZoneClientMap.put(accountId, clients);

		locker.release();

		if (session != NULL) {
			String ip = session->getIPAddress();

			onlineZoneClientMap.addAccount(ip, accountId);
		}

		return true;
	}

	Vector<Reference<ZoneClientSession*> > clients = onlineZoneClientMap.get(accountId);

	int onlineCount = 0;

	for (int i = 0; i < clients.size(); ++i) {
		ZoneClientSession* session = clients.get(i);

		ManagedReference<SceneObject*> player = session->getPlayer();

		if (player != NULL) {
			ManagedReference<PlayerObject*> ghost = cast<PlayerObject*>(player->getSlottedObject("ghost"));

			if (ghost != NULL && ghost->getAdminLevel() > 0)
				continue;
			else if (player->getClient() == session)
				++onlineCount;
		}
	}

	if (onlineCount >= MAX_CHAR_ONLINE_COUNT)
		return false;

	clients.add(client);

	onlineZoneClientMap.put(accountId, clients);

	locker.release();

	if (session != NULL) {
		String ip = session->getIPAddress();

		onlineZoneClientMap.addAccount(ip, accountId);
	}

	return true;
}

/*
int PlayerManagerImplementation::getOnlineCharCount(unsigned int accountId) {
	//onlineMapMutex.rlock()
	return 0;
}
 */

bool PlayerManagerImplementation::shouldRescheduleCorpseDestruction(CreatureObject* player, CreatureObject* ai) {

	if (ai->isNonPlayerCreatureObject()) {
		NonPlayerCreatureObject *npc = dynamic_cast<NonPlayerCreatureObject*>(ai);

		if (!npc->hasLoot() && npc->getCashCredits() < 1 && npc->getBankCredits() < 1) {
			return true;
		}
	} else if (ai->isCreature()) {
		Creature * creature = dynamic_cast<Creature*>(ai);

		if(creature->hasLoot() || creature->getCashCredits() > 0 || creature->getBankCredits() > 0)
			return false;

		return !(creature->hasSkillToHarvestMe(player) || canGroupMemberHarvestCorpse(player, creature));

	}

	return false;
}

bool PlayerManagerImplementation::canGroupMemberHarvestCorpse(CreatureObject* player, Creature* creature) {

	if (!player->isGrouped())
		return false;

	ManagedReference<GroupObject*> group = player->getGroup();
	int groupSize = group->getGroupSize();

	for (int i = 0; i < groupSize; i++) {
		ManagedReference<SceneObject*> groupMember = group->getGroupMember(i);

		if (player->getObjectID() == groupMember->getObjectID())
			continue;

		if (groupMember->isInRange(player, 256.0f)) {
			CreatureObject *groupMemberCreature = dynamic_cast<CreatureObject*>(groupMember.get());

			if (creature->hasSkillToHarvestMe(groupMemberCreature)) {
				return true;
			}
		}
	}

	return false;
}

void PlayerManagerImplementation::rescheduleCorpseDestruction(CreatureObject* player, CreatureObject* ai) {

	//If the looting player or no group members in the area can harvest then despawn immediately
	if (shouldRescheduleCorpseDestruction(player, ai)) {
		Reference<DespawnCreatureTask*> despawn = dynamic_cast<DespawnCreatureTask*>(ai->getPendingTask("despawn"));
		if (despawn != NULL) {
			despawn->cancel();
			despawn->reschedule(1000);
		}

	}
}
