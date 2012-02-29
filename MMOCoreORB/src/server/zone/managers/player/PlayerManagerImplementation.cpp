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

#include "server/zone/objects/tangible/OptionBitmask.h"

#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/cloning/CloningBuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"

#include "server/zone/objects/player/events/PlayerIncapacitationRecoverTask.h"
#include "server/zone/objects/player/events/MeditateTask.h"
#include "server/zone/objects/player/events/LogoutTask.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

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

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage6.h"
#include "server/zone/packets/object/StartingLocationListMessage.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/director/DirectorManager.h"

#include "server/zone/objects/player/sui/callbacks/CloningRequestSuiCallback.h"

#include "server/zone/Zone.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/ServerCore.h"

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

void PlayerManagerImplementation::finalize() {
	delete playerMap;
	playerMap = NULL;

	delete nameMap;
	nameMap = NULL;
}

void PlayerManagerImplementation::loadNameMap() {
	info("loading character names");

	try {
		String query = "SELECT * FROM characters where character_oid > 16777216 order by character_oid asc";

		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			uint64 oid = res->getUnsignedLong(0);
			String firstName = res->getString(3);

			nameMap->put(firstName.toLowerCase(), oid);
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


bool PlayerManagerImplementation::kickUser(const String& name, const String& admin) {
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager == NULL)
		return false;

	ManagedReference<CreatureObject*> player = chatManager->getPlayer(name);

	if (player == NULL)
		return false;

	PlayerObject* ghost = cast<PlayerObject*>(player->getSlottedObject("ghost"));

	if(ghost != NULL)
		ghost->setLoggingOut();

	ErrorMessage* errmsg = new ErrorMessage(admin, "You have been kicked", 0);
	player->sendMessage(errmsg);

	player->sendMessage(new LogoutMessage());

	ZoneClientSession* session = player->getClient();

	if(session != NULL)
		session->disconnect(true);

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

	int AI = playerCreature->getSkillMod("avoid_incapacitation");

	if (AI > 0)
		return 0;

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
		playerCreature->setUseCount(incapTime);

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

	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST);
	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST_DECAY);

	ManagedReference<SuiListBox*> cloneMenu;

	if (typeofdeath == 1) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);//no decay - GM command, deathblow or factional death
	} else if (typeofdeath == 0) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_DECAY);
	} else if (ghost->getFactionStatus() == FactionStatus::OVERT) {//TODO: Do proper check if faction death
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_FACTIONAL);
	}

	cloneMenu->setPromptTitle("@base_player:revive_title");

	CloningBuildingObject* closestCloning = zone->getNearestCloningBuilding(player);
	CloningBuildingObject* preDesignatedFacility = (CloningBuildingObject*)ghost->getCloningFacility();

	if (closestCloning == NULL)//TODO: Add default location so people don't get stuck
		return;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	String closestName;

	int x = closestCloning->getPositionX();
	int y = closestCloning->getPositionY();

	CityRegion* cr = planetManager->getRegionAt(x, y);

	if (cr != NULL) {
		closestName = cr->getRegionName();
	} else {
		if (zone->getZoneName() == "tutorial") {
			closestName = "Aboard a Space Station";
		} else {
			closestName = closestCloning->getObjectName()->getDisplayedName();
		}
	}

	String predesignatedName;

	if (preDesignatedFacility == NULL) {
		predesignatedName == "None";
	} else {
		cr = planetManager->getRegionAt(preDesignatedFacility->getPositionX(), preDesignatedFacility->getPositionY());
		if (cr != NULL)
			predesignatedName = cr->getRegionName();
		else
			predesignatedName = preDesignatedFacility->getObjectName()->getDisplayedName();
	}

	if (predesignatedName == "")
		predesignatedName = "None";

	//TODO: Integrate this menu with cloning system.
	StringBuffer promptText;
	promptText << "@base_player:revive_closest : " << closestName << "\n"
			<< "@base_player:revive_bind : " << predesignatedName << "\n" //Space before tab character is needed for proper formatting in this case.
			<< "Cash Balance : " << player->getCashCredits() << "\n\n"
			<< "Select the desired option and click OK.";

	cloneMenu->setPromptText(promptText.toString());
	cloneMenu->setCallback(new CloningRequestSuiCallback(player->getZoneServer()));
	cloneMenu->addMenuItem("@base_player:revive_closest", closestCloning->getObjectID());

	//TODO: Add force shrine locations for force sensitives

	//Check if predesignated is on this planet or not.
	Zone* facilityZone = preDesignatedFacility->getZone();
	if (preDesignatedFacility != NULL && facilityZone != NULL && facilityZone->getZoneName() == zone->getZoneName())
		cloneMenu->addMenuItem("@base_player:revive_bind", preDesignatedFacility->getObjectID());

	// Adding major ones
	SortedVector<ManagedReference<SceneObject*> > locations = zone->getPlanetaryObjectList("cloningfacility");

	if (locations.size() != 0) {
		for (int j = 0; j < locations.size(); j++) {
			ManagedReference<SceneObject*> location = locations.get(j);

			if (location != NULL && location->isCloningBuildingObject() && location != preDesignatedFacility && location != closestCloning) {
				//CloningBuildingObject* cbo = dynamic_cast<CloningBuildingObject*>location;
				CityRegion* cr = planetManager->getRegionAt(location->getPositionX(), location->getPositionY());
				if (cr != NULL)
					cloneMenu->addMenuItem(cr->getRegionName() + " (" + String::valueOf((int)player->getDistanceTo(location)) + "m)", location->getObjectID());
				else
					cloneMenu->addMenuItem(location->getObjectName()->getDisplayedName() + " (" + String::valueOf((int)player->getDistanceTo(location)) + "m)", location->getObjectID());
			}
		}
	}

	ghost->addSuiBox(cloneMenu);
	player->sendMessage(cloneMenu->generateMessage());
}

void PlayerManagerImplementation::sendPlayerToCloner(CreatureObject* player, uint64 clonerID, int typeofdeath) {
	ManagedReference<SceneObject*> cloner = server->getObject(clonerID);

	info("entering sendPlayerToCloner");

	if (cloner == NULL) {
		error("cloner is null");
		return;
	}

	if (!cloner->isCloningBuildingObject()) {
		error("cloner is not cloner building");
		return;
	}

	PlayerObject* ghost = player->getPlayerObject();
	CloningBuildingObject* cloningBuilding = cast<CloningBuildingObject*>( cloner.get());

	CloneSpawnPoint* clonePoint = cloningBuilding->getRandomSpawnPoint();

	if (clonePoint == NULL) {
		error("clone point null");
		return;
	}

	if (ghost->getFactionStatus() != FactionStatus::ONLEAVE) {
		ghost->setFactionStatus(FactionStatus::ONLEAVE); // TODO: setting this to onleave untill we have factional cloners
	}

	Coordinate* coordinate = clonePoint->getCoordinate();
	Quaternion* direction = clonePoint->getDirection();
	int cellID = clonePoint->getCellID();

	SceneObject* cell = cloningBuilding->getCell(cellID);

	if (cell == NULL) {
		StringBuffer msg;
		msg << "null cell for cellID " << cellID << " in building: " << cloningBuilding->getObjectTemplate()->getFullTemplateString();
		error(msg.toString());
		return;
	}

	Zone* zone = player->getZone();

	ManagedReference<SceneObject*> parent = player->getParent();

	if (parent != NULL) {
		if (parent->isCellObject()) {
			BuildingObject* build = cast<BuildingObject*>(parent->getParent());

			if (build != NULL) {
					build->onExit(player, 0);
			}
		}
	}

	player->switchZone(zone->getZoneName(), coordinate->getPositionX(), coordinate->getPositionZ(), coordinate->getPositionY(), cell->getObjectID());

	CloningBuildingObject* preDesignatedFacility = (CloningBuildingObject*)ghost->getCloningFacility();

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

	// Decay
	if (typeofdeath == 0 /*|| (typeofdeath == 2 && cloningBuilding-> ADD FACTION CHECK FOR CLONING HERE )*/) {

		Vector<ManagedReference<SceneObject*> > insurableItems = getInsurableItems(player, false);
		for (int i = 0; i < insurableItems.size(); i++) {
			SceneObject* item = insurableItems.get(i);

			if (item != NULL && item->isTangibleObject()) {
				ManagedReference<TangibleObject*> obj = cast<TangibleObject*>(item);

				if (obj->getOptionsBitmask() & OptionBitmask::INSURED) {
					//1% Decay for insured items
					obj->setConditionDamage((int)(obj->getConditionDamage() + (0.01 * obj->getMaxCondition()) ), true);
					//Set uninsured
					uint32 bitmask = obj->getOptionsBitmask();
					bitmask -= OptionBitmask::INSURED;
					obj->setOptionsBitmask(bitmask);
				} else {
					//5% Decay for uninsured items
					obj->setConditionDamage((int)(obj->getConditionDamage() + (0.05 * obj->getMaxCondition()) ), true);
				}
			}
		}
	}

	Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(3 * 1000);
}

void PlayerManagerImplementation::disseminateExperience(TangibleObject* destructedObject, ThreatMap* threatMap) {
	uint32 totalDamage = threatMap->getTotalDamage();

	int level = destructedObject->getLevel();

	//info("level: " + String::valueOf(level), true);

	VectorMap<GroupObject*, int> groups;
	groups.setNullValue(0);

	for (int i = 0; i < threatMap->size(); ++i) {
		CreatureObject* creature = threatMap->elementAt(i).getKey();
		if (!creature->isPlayerCreature())
			continue;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ThreatMapEntry* entry = &threatMap->elementAt(i).getValue();

		Locker crossLocker(player, destructedObject);

		uint32 totalPlayerDamage = 0;
		uint32 playerWeaponXp = 0;

		for (int j = 0; j < entry->size(); ++j) {
			ManagedReference<WeaponObject*> weapon = entry->elementAt(j).getKey();

			if (weapon == NULL)
				continue;

			uint32 damage = entry->elementAt(j).getValue();

			totalPlayerDamage += damage;

			String xpType = weapon->getXpType();

			int xpAmmount = (int) (float((float(damage) / float(totalDamage))) * 40.f * level);

			//info("xpAmmount: " + String::valueOf(xpAmmount), true);

			playerWeaponXp += xpAmmount;

			awardExperience(player, xpType, xpAmmount);
		}

		awardExperience(player, "combat_general", playerWeaponXp / 10);

		if (player->isGrouped()) {
			ManagedReference<GroupObject*> group = player->getGroup();
			if (!squadLeaderCheck(player, group))
				continue;

			int amount = playerWeaponXp;

			if (groups.contains(group)) {
				amount += groups.get(group);
				groups.drop(group);
			}

			groups.put(group, amount);
		}

	}

	if (!groups.isEmpty())
		for (int x = 0; x < groups.size(); x++)
			awardSquadLeaderExperience(groups.elementAt(x).getKey(), groups.get(x), destructedObject);

	threatMap->removeAll();
}

void PlayerManagerImplementation::awardSquadLeaderExperience(GroupObject* group, int amount, TangibleObject* source) {
	if (source == NULL || group == NULL || amount <= 0)
		return;

	ManagedReference<SceneObject*> leader = group->getLeader();

	if (leader == NULL)
		return;

	if (!leader->isPlayerCreature())
		return;

	ManagedReference<CreatureObject*> leaderPlayer = cast<CreatureObject*>( leader.get());

	Locker clocker(leaderPlayer, source);

	float groupModifier = group->getGroupSize() / 10.0f;
	if (groupModifier < 1)
		groupModifier += 1;

	awardExperience(leaderPlayer, "squadleader", (int) amount * groupModifier * 0.75);
}

bool PlayerManagerImplementation::squadLeaderCheck(CreatureObject* player, GroupObject* group) {
	if (player == NULL || group == NULL)
		return false;

	if (!group->hasSquadLeader())
		return false;

	if (group->getLeader()->getZone() != player->getZone())
		return false;

	if (group->getLeader()->compareTo(player) == 0)
		return false;

	return true;
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

	CreatureObject* player = dynamic_cast<CreatureObject*>(ghost->getParent());

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

	//You receive 30 points of Surveying experience.
	if (sendSystemMessage) {
		if (xp <= 0) {
			if (amount > 0) {
				VectorMap<String, int>* xpTypeCapList = playerObject->getXpTypeCapList();

				int maxXp = xpTypeCapList->get(xpType);

				if (maxXp > 0) {
					//StringIdChatParameter message("error_message","prose_at_xp_limit");
					StringIdChatParameter message("base_player", "prose_hit_xp_cap"); //You have achieved your current limit for %TO experience.
					//message.setDI(maxXp);
					message.setTO("exp_n", xpType);
					player->sendSystemMessage(message);
				}

			}

		} else {
			StringIdChatParameter message("base_player","prose_grant_xp");
			message.setDI(xp);
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

void PlayerManagerImplementation::handleAbortTradeMessage(CreatureObject* player, bool doLock) {
	try {
		player->wlock(doLock);

		PlayerObject* ghost = player->getPlayerObject();

		TradeContainer* tradeContainer = ghost->getTradeContainer();

		/*if (tradeContainer == NULL) {
			AbortTradeMessage* msg = new AbortTradeMessage();
			player->sendMessage(msg);

			player->unlock(doLock);
			return;
		}*/

		uint64 targID = tradeContainer->getTradeTargetPlayer();
		ManagedReference<SceneObject*> obj = server->getObject(targID);

		AbortTradeMessage* msg = new AbortTradeMessage();

		if (obj != NULL && obj->isPlayerCreature()) {
			CreatureObject* receiver = cast<CreatureObject*>( obj.get());

			Locker locker(receiver, player);
			//receiver->wlock(player);

			PlayerObject* targetGhost = receiver->getPlayerObject();

			TradeContainer* receiverContainer = targetGhost->getTradeContainer();

			if (receiverContainer->getTradeTargetPlayer() == player->getObjectID()) {
				targetGhost->clearTradeContainer();
				receiver->sendMessage(msg->clone());
			}

			//receiver->unlock();
			locker.release();
		}

		player->sendMessage(msg->clone());

		delete msg;

		ghost->clearTradeContainer();

		player->unlock(doLock);
	} catch (...) {
		player->unlock(doLock);

		throw;
	}
}

void PlayerManagerImplementation::handleAddItemToTradeWindow(CreatureObject* player, uint64 itemID) {
	Locker _locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	TradeContainer* tradeContainer = ghost->getTradeContainer();

	// First Verify Target is Player
	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* receiver = cast<CreatureObject*>( obj.get());

	SceneObject* inventory = player->getSlottedObject("inventory");
	ManagedReference<SceneObject*> inventoryObject = inventory->getContainerObject(itemID);

	if (inventoryObject == NULL) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player, false);
		return;
	}

	tradeContainer->addTradeItem(inventoryObject);

	inventoryObject->sendWithoutParentTo(receiver);

	AddItemMessage* msg = new AddItemMessage(itemID);
	receiver->sendMessage(msg);
}

void PlayerManagerImplementation::handleGiveMoneyMessage(CreatureObject* player, uint32 value) {
	Locker _locker(player);

	int currentMoney = player->getCashCredits();

	if (value > currentMoney)
		value = currentMoney;

	PlayerObject* ghost = player->getPlayerObject();

	TradeContainer* tradeContainer = ghost->getTradeContainer();

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

	PlayerObject* ghost = player->getPlayerObject();

	TradeContainer* tradeContainer = ghost->getTradeContainer();

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

	PlayerObject* ghost = player->getPlayerObject();

	TradeContainer* tradeContainer = ghost->getTradeContainer();

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

	TradeContainer* tradeContainer = ghost->getTradeContainer();
	TradeContainer* receiverContainer = targetGhost->getTradeContainer();

	if (tradeContainer->getTradeTargetPlayer() != receiver->getObjectID())
		return false;

	if (receiverContainer->getTradeTargetPlayer() != player->getObjectID())
		return false;

	SceneObject* playerInventory = player->getSlottedObject("inventory");
	SceneObject* receiverInventory = receiver->getSlottedObject("inventory");

	if (receiverInventory->getContainerObjectsSize() + tradeContainer->getTradeSize() >= receiverInventory->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (playerInventory->getContainerObjectsSize() + receiverContainer->getTradeSize() >= playerInventory->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = tradeContainer->getTradeItem(i);

		String err;
		if (receiverInventory->canAddObject(scene, -1, err) != 0)
			return false;

		if (!playerInventory->hasObjectInContainer(scene->getObjectID()))
			return false;
	}

	for (int i = 0; i < receiverContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = receiverContainer->getTradeItem(i);

		String err;
		if (playerInventory->canAddObject(scene, -1, err) != 0)
			return false;

		if (!receiverInventory->hasObjectInContainer(scene->getObjectID()))
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

	return true;
}

void PlayerManagerImplementation::handleVerifyTradeMessage(CreatureObject* player) {
	ManagedReference<ObjectController*> objectController = server->getObjectController();

	Locker locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	TradeContainer* tradeContainer = ghost->getTradeContainer();

	if (tradeContainer == NULL) {
		return;
	}

	tradeContainer->setVerifiedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		Locker clocker(receiver, player);

		PlayerObject* targetGhost = receiver->getPlayerObject();

		TradeContainer* receiverTradeContainer = targetGhost->getTradeContainer();

		if (receiverTradeContainer == NULL) {
			locker.release();
			return;
		}

		if (!checkTradeItems(player, receiver)) {
			clocker.release();
			handleAbortTradeMessage(player, false);

			locker.release();
			return;
		}

		if (receiverTradeContainer->hasVerifiedTrade()) {
			SceneObject* receiverInventory = receiver->getSlottedObject("inventory");

			for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = tradeContainer->getTradeItem(i);

				if (objectController->transferObject(item, receiverInventory, -1, true))
					item->sendDestroyTo(player);
			}

			SceneObject* playerInventory = player->getSlottedObject("inventory");

			for (int i = 0; i < receiverTradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = receiverTradeContainer->getTradeItem(i);

				if (objectController->transferObject(item, playerInventory, -1, true))
					item->sendDestroyTo(receiver);
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

			targetGhost->clearTradeContainer();

			ghost->clearTradeContainer();

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

		// Check POSTERCHANGE on Meditate...
		Reference<MeditateTask*> meditateTask = cast<MeditateTask*>( creature->getPendingTask("meditate"));
		if (meditateTask != NULL) {
			creature->removePendingTask("meditate");
			creature->sendSystemMessage("@teraskasi:med_end");
			creature->setMood(creature->getMoodID(), true);
			creature->clearState(CreatureState::ALERT, true);

			if (meditateTask->isScheduled())
				meditateTask->cancel();
		}

		// Check POSTURECHANGED disrupting Logout...
		Reference<LogoutTask*> logoutTask = (LogoutTask*) creature->getPendingTask("logout");
		if(logoutTask != NULL) {
			logoutTask->cancelLogout();
		}
	}

	return 1;
}

void PlayerManagerImplementation::sendBattleFatigueMessage(CreatureObject* player, CreatureObject* target) {
	uint32 battleFatigue = target->getShockWounds();

	if (battleFatigue == 0)
		return;

	String targetName = target->getFirstName();

	StringBuffer msgPlayer, msgTarget;

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

	target->sendSystemMessage(msgTarget.toString());

	if (player != target)
		player->sendSystemMessage(msgPlayer.toString());
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
	buff->setAttributeModifier(attribute, buffvalue);
	buff->setFillAttributesOnBuff(true);
	patient->addBuff(buff);

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

		if (obj != NULL && obj->isStructureObject() && (cast<StructureObject*>(obj.get()))->isOnAdminList(creature->getFirstName()))
			return obj.get();
	}


	ManagedReference<SceneObject*> rootParent = creature->getRootParent();

	if (rootParent != NULL && rootParent->isStructureObject() && (cast<StructureObject*>(rootParent.get()))->isOnAdminList(creature->getFirstName())) {
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

				if (structureObject->isOnAdminList(creature->getFirstName()) && dist < distance) {
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
		ManagedReference<StructureObject*> structure = ghost->getOwnedStructure(i);

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

void PlayerManagerImplementation::updateAdminLevel(CreatureObject* player, const String& targetName, int adminLevel) {
	ManagedReference<CreatureObject*> targetPlayer = getPlayer(targetName);

	if (targetPlayer == NULL) {
		player->sendSystemMessage("That player does not exist.");
		return;
	}

	Locker clocker(targetPlayer, player);

	ManagedReference<PlayerObject*> ghost = targetPlayer->getPlayerObject();

	if (ghost == NULL) {
		player->sendSystemMessage("That player did not have a PlayerObject.");
		return;
	}

	SkillManager* skillManager = server->getSkillManager();

	if (adminLevel == PlayerObject::NORMALPLAYER)
		skillManager->removeAbility(ghost, "admin");
	else
		skillManager->addAbility(ghost, "admin");

	ghost->setAdminLevel(adminLevel);

	//Send deltas
	if (targetPlayer->isOnline()) {
		TangibleObjectDeltaMessage3* tanod3 = new TangibleObjectDeltaMessage3(targetPlayer);
		tanod3->updateName(targetPlayer->getObjectName()->getDisplayedName());
		tanod3->close();
		targetPlayer->broadcastMessage(tanod3, true);

		PlayerObjectDeltaMessage6* playd6 = new PlayerObjectDeltaMessage6(ghost);
		playd6->setAdminLevel(adminLevel);
		playd6->close();
		targetPlayer->broadcastMessage(playd6, true);
	}
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
			player->info(msg.toString(), true);

			player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return 1;
		}

		SpeedModChange* firstChange = &changeBuffer->get(changeBuffer->size() - 1);
		Time* timeStamp = &firstChange->getTimeStamp();

		if (timeStamp->miliDifference() > 2000) { // we already should have lowered the speed, 2 seconds lag
			StringBuffer msg;
			msg << "max allowed speed should be " << maxAllowedSpeed * errorMultiplier;
			msg << " parsed " << parsedSpeed;
			player->info(msg.toString(), true);

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

		player->info(msg.toString(), true);

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

void PlayerManagerImplementation::lootAll(CreatureObject* player, AiAgent* ai) {

	Locker locker(ai, player);

	if (!ai->isDead())
		return;

	int cashCredits = ai->getCashCredits();

	if (cashCredits > 0) {
		player->addCashCredits(cashCredits, true);
		ai->setCashCredits(0);

		StringIdChatParameter param("base_player", "prose_coin_loot"); //You loot %DI credits from %TT.
		param.setDI(cashCredits);
		param.setTT(ai);

		player->sendSystemMessage(param);
	}

	SceneObject* creatureInventory = ai->getSlottedObject("inventory");

	if (creatureInventory == NULL)
		return;

	SceneObject* playerInventory = player->getSlottedObject("inventory");

	if (playerInventory == NULL)
		return;

	int totalItems = creatureInventory->getContainerObjectsSize();

	if (totalItems < 1)
		return;

	StringBuffer args;
	args << playerInventory->getObjectID() << " -1 0 0 0";

	String stringArgs = args.toString();

	for (int i = totalItems - 1; i >= 0; --i) {
		SceneObject* object = creatureInventory->getContainerObject(i);

		player->executeObjectControllerAction(String("transferitemmisc").hashCode(), object->getObjectID(), stringArgs);
	}

	if (creatureInventory->getContainerObjectsSize() <= 0)
		player->sendSystemMessage("@base_player:corpse_looted"); //You have completely looted the corpse of all items.

}

void PlayerManagerImplementation::generateHologrindSkills(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint8> profs;
	//Fill the total profs array.
	for (int i = 0; i < 32; ++i)
		profs.put(i + 1);

	uint32 holomask = 0;

	uint8 totalProfsNeeded = System::random(7) + 5; //5-12 professions according to insider info.

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

Vector<ManagedReference<SceneObject*> > PlayerManagerImplementation::getInsurableItems(CreatureObject* player, bool onlyInsurable) {
	Vector<ManagedReference<SceneObject*> > insurableItems;

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
				insurableItems.add(item);
			} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
				insurableItems.add(item);
			}
		}

		for (int j = 0; j < container->getContainerObjectsSize(); j++) {
			SceneObject* object = container->getContainerObject(j);

			if (!object->isTangibleObject())
				continue;

			TangibleObject* item = cast<TangibleObject*>( object);

			if (item != NULL && !(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject())) {
				insurableItems.add(item);
			} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
				insurableItems.add(item);
			}
		}
	}

	return insurableItems;
}

int PlayerManagerImplementation::calculatePlayerLevel(CreatureObject* player) {
	ManagedReference<WeaponObject*> weapon = player->getWeapon();

	if (weapon == NULL) {
		player->error("player with NULL weapon");

		return 0;
	}

	String xpType = weapon->getXpType();

	SkillList* skillList = player->getSkillList();

	int level = 0;
	int finalLevel = 0;

	for (int j = 0; j < 2; ++j) {
		level = 0;

		for (int i = 0; i < skillList->size(); ++i) {
			Skill* skill = skillList->get(i);

			if (skill->getXpType() == xpType)
				++level;
		}

		if (level > finalLevel)
			finalLevel = level;

		xpType = "medical";
	}

	if (finalLevel < 5)
		finalLevel = 5;
	else if (finalLevel > 25)
		finalLevel = 25;

	return finalLevel;
}

String PlayerManagerImplementation::getBadgeKey(int idx) {
	VectorMapEntry<int, String> entry = badgeMap.elementAt(idx);

	return entry.getValue();
}
