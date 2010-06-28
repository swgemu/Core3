/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

#include "server/zone/packets/charcreation/ClientCreateCharacter.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterSuccess.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterFailed.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/db/ServerDatabase.h"
#include "server/chat/ChatManager.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/area/ActiveArea.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/cloning/CloningBuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/player/events/PlayerIncapacitationRecoverTask.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/professions/ProfessionManager.h"

#include "server/zone/packets/trade/AbortTradeMessage.h"
#include "server/zone/packets/trade/AcceptTransactionMessage.h"
#include "server/zone/packets/trade/UnAcceptTransactionMessage.h"
#include "server/zone/packets/trade/AddItemMessage.h"
#include "server/zone/packets/trade/BeginTradeMessage.h"
#include "server/zone/packets/trade/DenyTradeMessage.h"
#include "server/zone/packets/trade/TradeCompleteMessage.h"
#include "server/zone/packets/trade/GiveMoneyMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

#include "server/zone/Zone.h"

PlayerManagerImplementation::PlayerManagerImplementation(ZoneServer* zoneServer, ZoneProcessServerImplementation* impl) :
	ManagedObjectImplementation(), Logger("PlayerManager") {
	server = zoneServer;
	processor = impl;

	playerMap = new PlayerMap(3000);
	nameMap = new CharacterNameMap();

	globalExpMultiplier = 1.0f;

	loadStartingItems();

	setGlobalLogging(true);
	setLogging(true);

	loadNameMap();
}

void PlayerManagerImplementation::loadStartingItems() {
	try {
		startingItemList = StartingItemList::instance();

		startingItemList->loadItems();
	} catch (Exception& e) {
		error("unknown error while loadStartingItems");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in loadStartingItems");
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

	String query = "SELECT * FROM characters";

	ResultSet* res = ServerDatabase::instance()->executeQuery(query);

	while (res->next()) {
		uint64 oid = res->getUnsignedLong(0);
		String firstName = res->getString(3);

		nameMap->put(firstName.toLowerCase(), oid);
	}

	delete res;

	StringBuffer msg;
	msg << "loaded " << nameMap->size() << " character names in memory";
	info(msg.toString(), true);
}

bool PlayerManagerImplementation::existsName(const String& name) {
	bool res = false;

	rlock();

	try {
		res = nameMap->containsKey(name.toLowerCase());
	} catch (...) {
		error("unreported exception caught in bool PlayerManagerImplementation::existsName(const String& name)");
	}

	runlock();

	return res;
}

PlayerCreature* PlayerManagerImplementation::getPlayer(const String& name) {
	uint64 oid = 0;

	rlock();

	try {
		oid = nameMap->get(name.toLowerCase());
	} catch (...) {
		error("unreported exception caught in bool PlayerManagerImplementation::getPlayer(const String& name)");
	}

	runlock();

	if (oid == 0)
		return NULL;

	SceneObject* obj = server->getObject(oid);

	if (obj == NULL || !obj->isPlayerCreature())
		return NULL;

	return (PlayerCreature*) obj;
}

uint64 PlayerManagerImplementation::getObjectID(const String& name) {
	uint64 oid = 0;

	rlock();

	try {
		oid = nameMap->get(name.toLowerCase());
	} catch (...) {
		error("unreported exception caught in bool PlayerManagerImplementation::existsName(const String& name)");
	}

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

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		bool nameExists = res->next();

		delete res;

		return !nameExists;
	} catch (DatabaseException& e) {
		return false;
	}
}

bool PlayerManagerImplementation::checkPlayerName(MessageCallback* messageCallback) {
	ClientCreateCharacterCallback* callback = (ClientCreateCharacterCallback*) messageCallback;
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

bool PlayerManagerImplementation::createPlayer(MessageCallback* data) {
	Locker _locker(_this);

	ClientCreateCharacterCallback* callback = (ClientCreateCharacterCallback*) data;
	ZoneClientSession* client = data->getClient();

	String race;
	callback->getRaceFile(race);
	info("trying to create " + race);

	uint32 serverObjectCRC = race.hashCode();

	int raceID = Races::getRaceID(race);
	/*uint32 playerCRC = Races::getRaceCRC(raceID);*/

	UnicodeString name;
	callback->getCharacterName(name);

	if (!checkPlayerName(callback)) {
		info("invalid name " + name.toString());
		return false;
	}

	ManagedReference<SceneObject*> player = server->createObject(serverObjectCRC, 2); // player

	if (player == NULL) {
		error("could not create player... could not create player object");
		return false;
	}

	if (!player->isPlayerCreature()) {
		error("could not create player... wrong object type");
		return false;
	}

	String profession;
	callback->getProfession(profession);

	PlayerCreature* playerCreature = (PlayerCreature*) player.get();
	createAllPlayerObjects(playerCreature);
	createDefaultPlayerItems(playerCreature, profession, race);

	playerCreature->setRaceID((byte)raceID);

	String playerCustomization;
	callback->getCustomizationString(playerCustomization);
	playerCreature->setCustomizationString(playerCustomization);

	playerCreature->setCustomObjectName(name, false);

	String firstName = playerCreature->getFirstName();
	String lastName = playerCreature->getLastName();

	/*firstName.escapeString();
	lastName.escapeString();
	race.escapeString();*/

	try {
		StringBuffer query;
		query << "INSERT INTO `characters` (`character_oid`, `account_id`, `galaxy_id`, `firstname`, `surname`, `race`, `gender`, `template`)"
				<< " VALUES (" <<  playerCreature->getObjectID() << "," << client->getAccountID() <<  "," << 2 << ","
				<< "'" << firstName.escapeString() << "','" << lastName.escapeString() << "'," << raceID << "," <<  0 << ",'" << race.escapeString() << "')";

		ServerDatabase::instance()->executeStatement(query);
	} catch (Exception& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught while creating character");
	}

	nameMap->put(playerCreature);

	//hair
	String hairObjectFile;
	callback->getHairObject(hairObjectFile);

	String hairCustomization;
	callback->getHairCustomization(hairCustomization);

	TangibleObject* hair = createHairObject(hairObjectFile, hairCustomization);

	if (hair != NULL) {
		player->addObject(hair, 4);

		info("created hair object");
	}

	playerCreature->setHeight(callback->getHeight());

	UnicodeString biography;
	callback->getBiography(biography);
	playerCreature->setBiography(biography);

	//info("profession:" + profession, true);

	ProfessionManager* professionManager = server->getProfessionManager();
	professionManager->setStartingProfession(profession, raceID, playerCreature);

	playerCreature->setClient(client);
	client->setPlayer(player);

	playerCreature->setAccountID(client->getAccountID());

	if (callback->getTutorialFlag()) {
		createTutorialBuilding(playerCreature);
	} else {
		createSkippedTutorialBuilding(playerCreature);
	}

	player->updateToDatabase();

	StringBuffer infoMsg;
	infoMsg << "player " << name.toString() << " successfully created";
	info(infoMsg);

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(player->getObjectID());
	playerCreature->sendMessage(msg);

	ChatManager* chatManager = server->getChatManager();

	chatManager->addPlayer(playerCreature);

	return true;
}

TangibleObject* PlayerManagerImplementation::createHairObject(const String& hairObjectFile, const String& hairCustomization) {
	TangibleObject* hairObject = NULL;

	if (hairObjectFile.isEmpty()) {
		info("hairObjectFile empty");
		return NULL;
	}

	String sharedHairObjectFile = hairObjectFile.replaceFirst("hair_", "shared_hair_");

	info("trying to create hair object " + sharedHairObjectFile);
	SceneObject* hair = server->createObject(sharedHairObjectFile.hashCode(), 1);

	if (hair == NULL) {
		info("objectManager returned NULL hair object");
		return NULL;
	}

	if (hair->getGameObjectType() != SceneObjectImplementation::GENERICITEM) {
		info("wrong hair object type");
		//hair->finalize();

		return NULL;
	} else {
		hairObject = (TangibleObject*) hair;

		hairObject->setCustomizationString(hairCustomization);

		info("hair object created successfully");
	}

	return hairObject;
}

bool PlayerManagerImplementation::createAllPlayerObjects(PlayerCreature* player) {
	SceneObject* inventory = server->createObject(0x3969E83B, 1); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->addObject(inventory, 4);

	SceneObject* datapad = server->createObject(0x73BA5001, 1); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	player->addObject(datapad, 4);

	SceneObject* playerObject = server->createObject(String("object/player/player.iff").hashCode(), 1); //player object

	if (playerObject == NULL) {
		error("could not create player object");
		return false;
	}

	player->addObject(playerObject, 4);

	SceneObject* bank = server->createObject(0x70FD1394, 1); //bank

	if (bank == NULL) {
		error("could not create bank");
		return false;
	}

	player->addObject(bank, 4);

	SceneObject* missionBag = server->createObject(0x3D7F6F9F, 1); //mission bag

	if (missionBag == NULL) {
		error("could not create mission bag");
		return false;
	}

	player->addObject(missionBag, 4);

	uint32 defaultWeaponCRC = String("object/weapon/melee/unarmed/unarmed_default_player.iff").hashCode();

	SceneObject* defaultWeapon = server->createObject(defaultWeaponCRC, 1);

	if (defaultWeapon == NULL) {
		error("could not create default_weapon");
		return false;
	}

	player->addObject(defaultWeapon, 4);

	// temp

	/*SceneObject* vibro = server->createObject(0x652688CE, 1);
	player->addObject(vibro, 4);
	player->setWeaponID(vibro->getObjectID());

	SceneObject* vibro2 = server->createObject(0x652688CE, 1);
	inventory->addObject(vibro2, -1);

	String bharmor = "object/tangible/wearables/armor/bounty_hunter/shared_armor_bounty_hunter_chest_plate.iff";
	SceneObject* armor = server->createObject(bharmor.hashCode(), 1);
	inventory->addObject(armor, -1);

	String backpack = "object/tangible/wearables/backpack/shared_backpack_s01.iff";
	SceneObject* backpackObject = server->createObject(backpack.hashCode(), 1);
	inventory->addObject(backpackObject, -1);*/

	//admin
	ObjectController* objController = server->getObjectController();
	QueueCommand* admin = objController->getQueueCommand("admin");
	Vector<QueueCommand*> skills;
	skills.add(admin);
	((PlayerObject*)playerObject)->addSkills(skills, false);

	VehicleControlDevice* vehicleControlDevice = (VehicleControlDevice*) server->createObject(String("object/intangible/vehicle/speederbike_swoop_pcd.iff").hashCode(), 1);
	VehicleObject* vehicle = (VehicleObject*) server->createObject(String("object/mobile/vehicle/speederbike_swoop.iff").hashCode(), 1);
	vehicleControlDevice->setControlledObject(vehicle);
	datapad->addObject(vehicleControlDevice, -1);

	String pole = "object/tangible/fishing/shared_fishing_pole.iff";
	SceneObject* poleObject = server->createObject(pole.hashCode(), 1);
	inventory->addObject(poleObject, -1);

	String bait = "object/tangible/fishing/bait/shared_bait_worm.iff";
	SceneObject* baitObject = server->createObject(bait.hashCode(), 1);
	inventory->addObject(baitObject, -1);

	/*SceneObject* mission = server->createObject(3741732474UL, 1); // empty mission
	datapad->addObject(mission, -1);*/

	return true;
}

void PlayerManagerImplementation::createTutorialBuilding(PlayerCreature* player) {
	Zone* zone = server->getZone(42);

	String tut = "object/building/general/shared_newbie_hall.iff";
	String cell = "object/cell/shared_cell.iff";

	BuildingObject* tutorial = (BuildingObject*) server->createObject(tut.hashCode(), 1);
	tutorial->createCellObjects();
	tutorial->setStaticBuilding(false);

	SceneObject* travelTutorialTerminal = server->createObject((uint32)String("object/tangible/newbie_tutorial/terminal_warp.iff").hashCode(), 1);

	String blueFrogTemplateCRC = "object/tangible/terminal/terminal_character_builder.iff";
	SceneObject* blueFrogTemplate =  server->createObject(blueFrogTemplateCRC.hashCode(), 1);

	SceneObject* cellTut = tutorial->getCell(10);
	cellTut->addObject(travelTutorialTerminal, -1);
	cellTut->addObject(blueFrogTemplate, -1);

	tutorial->insertToZone(zone);
	travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);
	travelTutorialTerminal->insertToZone(zone);
	blueFrogTemplate->initializePosition(27.0f, -3.5f, -165.0f);
	blueFrogTemplate->insertToZone(zone);

	player->initializePosition(27.0f, -3.5f, -165.0f);
	player->setZone(zone);
	cellTut->addObject(player, -1);
	player->setSavedZoneID(zone->getZoneID());
	player->setSavedParentID(cellTut->getObjectID());

	tutorial->updateToDatabase();
}

void PlayerManagerImplementation::createSkippedTutorialBuilding(PlayerCreature* player) {
	Zone* zone = server->getZone(42);

	String tut = "object/building/general/shared_newbie_hall_skipped.iff";
	String cell = "object/cell/shared_cell.iff";

	BuildingObject* tutorial = (BuildingObject*) server->createObject(tut.hashCode(), 1);
	tutorial->createCellObjects();
	tutorial->setStaticBuilding(false);

	SceneObject* travelTutorialTerminal = server->createObject((uint32)String("object/tangible/newbie_tutorial/terminal_warp.iff").hashCode(), 1);

	String blueFrogTemplateCRC = "object/tangible/terminal/terminal_character_builder.iff";
	SceneObject* blueFrogTemplate =  server->createObject(blueFrogTemplateCRC.hashCode(), 1);

	SceneObject* cellTut = tutorial->getCell(0);
	cellTut->addObject(travelTutorialTerminal, -1);
	cellTut->addObject(blueFrogTemplate, -1);

	tutorial->insertToZone(zone);
	travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);
	travelTutorialTerminal->insertToZone(zone);

	blueFrogTemplate->initializePosition(27.0f, -3.5f, -165.0f);
	blueFrogTemplate->insertToZone(zone);

	player->initializePosition(27.0f, -3.5f, -165.0f);
	player->setZone(zone);
	cellTut->addObject(player, -1);
	player->setSavedZoneID(zone->getZoneID());
	player->setSavedParentID(cellTut->getObjectID());

	tutorial->updateToDatabase();
}

void PlayerManagerImplementation::createDefaultPlayerItems(PlayerCreature* player, const String& profession, const String& templateFile) {
	String prof;

	try {
		prof = profession.subString(profession.indexOf('_') + 1);
	} catch (...) {
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

	items = startingItemList->getProfessionItems(prof, species, sex);
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
			player->addObject(obj, 4);
		} else {
			inventory->addObject(obj, -1);
		}
	}

	//Make profession items for that apply to all species
	items = startingItemList->getProfessionItems(prof, all, sex);
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
			player->addObject(obj, 4);
		} else {
			inventory->addObject(obj, -1);
		}
	}


	//Make general items for species
	items = startingItemList->getProfessionItems(gen, species, sex);
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
			player->addObject(obj, 4);
		} else {
			inventory->addObject(obj, -1);
		}
	}


	//Make general items that apple to all species
	items = startingItemList->getProfessionItems(gen, all, sex);
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
			player->addObject(obj, 4);
		} else {
			inventory->addObject(obj, -1);
		}
	}

}

uint8 PlayerManagerImplementation::calculateIncapacitationTimer(PlayerCreature* playerCreature, int condition) {
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

	PlayerCreature* playerCreature = (PlayerCreature*) destructedObject;

	int AI = playerCreature->getSkillMod("avoid_incapacitation");

	if (AI > 0)
		return 0;

	playerCreature->updateIncapacitationCounter();

	playerCreature->clearCombatState();
	destructor->removeDefender(playerCreature);

	if (playerCreature->getIncapacitationCounter() < 3) {
		playerCreature->setPosture(CreaturePosture::INCAPACITATED, true);

		uint32 incapTime = calculateIncapacitationTimer(playerCreature, condition);
		playerCreature->setUseCount(incapTime);

		Reference<Task*> task = new PlayerIncapacitationRecoverTask(playerCreature, false);
		task->schedule(incapTime * 1000);

		ParameterizedStringId stringId;

		if (destructor != NULL) {
			stringId.setStringId("base_player", "prose_victim_incap");
			stringId.setTT(destructor->getObjectID());
		} else {
			stringId.setStringId("base_player", "victim_incapacitated");
		}

		playerCreature->sendSystemMessage(stringId);

	} else {
		if (!playerCreature->isFirstIncapacitationExpired()) {
			killPlayer(destructor, playerCreature);
		}
	}

	return 0;
}

void PlayerManagerImplementation::killPlayer(TangibleObject* attacker, PlayerCreature* player) {
	ParameterizedStringId stringId;

	if (attacker->isPlayerCreature()) {
		stringId.setStringId("base_player", "prose_target_dead");
		stringId.setTT(player->getObjectID());
		((CreatureObject*)attacker)->sendSystemMessage(stringId);
	}

	player->setPosture(CreaturePosture::DEAD, true);
	player->clearCombatState();

	CombatManager::instance()->freeDuelList(player, false);

	sendActivateCloneRequest(player);

	stringId.setStringId("base_player", "prose_victim_dead");
	stringId.setTT(attacker->getObjectID());
	player->sendSystemMessage(stringId);

	Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(10 * 1000);
}

void PlayerManagerImplementation::sendActivateCloneRequest(PlayerCreature* player) {
	player->removeSuiBoxType(SuiWindowType::CLONE_REQUEST);

	ManagedReference<SuiListBox*> cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);

	cloneMenu->setPromptTitle("@base_player:revive_title");

	Zone* zone = player->getZone();

	CloningBuildingObject* closestCloning = zone->getNearestCloningBuilding(player);
	CloningBuildingObject* preDesignatedFacility = NULL;

	UnicodeString name;
	StringId* objectName = closestCloning->getObjectName();

	ActiveArea* area = closestCloning->getActiveArea();

	if (area != NULL) {
		objectName = area->getObjectName();

		//info("area found", true);
	} else
		//info("area not found, true");

	name = objectName->getCustomString();

	if (name.length() == 0) {
		String fullPath;
		objectName->getFullPath(fullPath);

		name = fullPath;
	}

	String closestName = name.toString(); //"Not Working Yet";
	String predesignatedName = (preDesignatedFacility != NULL) ? "Not Working Yet" : "None";

	//TODO: Integrate this menu with cloning system.

	StringBuffer promptText;
	promptText << "@base_player:revive_closest : " << closestName << "\n"
			<< "@base_player:revive_bind : " << predesignatedName << "\n" //Space before tab character is needed for proper formatting in this case.
			<< "Cash Balance : " << player->getCashCredits() << "\n\n"
			<< "Select the desired option and click OK.";

	cloneMenu->setPromptText(promptText.toString());

	cloneMenu->addMenuItem("@base_player:revive_closest", closestCloning->getObjectID());

	//Check if predesignated is on this planet or not.
	if (preDesignatedFacility != NULL && preDesignatedFacility->getZone()->getZoneID() == zone->getZoneID())
		cloneMenu->addMenuItem("@base_player:revive_bind", preDesignatedFacility->getObjectID());

	player->addSuiBox(cloneMenu);
	player->sendMessage(cloneMenu->generateMessage());
}

void PlayerManagerImplementation::sendPlayerToCloner(PlayerCreature* player, uint64 clonerID) {
	ManagedReference<SceneObject*> cloner = server->getObject(clonerID);

	info("entering sendPlayerToCloner", true);

	if (cloner == NULL) {
		error("cloner is null");
		return;
	}

	if (!cloner->isCloningBuildingObject()) {
		error("cloner is not cloner building");
		return;
	}

	CloningBuildingObject* cloningBuilding = (CloningBuildingObject*) cloner.get();

	CloneSpawnPoint* clonePoint = cloningBuilding->getRandomSpawnPoint();

	if (clonePoint == NULL) {
		error("clone point null");
		return;
	}

	Coordinate* coordinate = clonePoint->getCoordinate();
	Quaternion* direction = clonePoint->getDirection();
	int cellID = clonePoint->getCellID();

	SceneObject* cell = cloningBuilding->getCell(cellID - 1);

	Zone* zone = player->getZone();

	player->switchZone(zone->getZoneID(), coordinate->getPositionX(), coordinate->getPositionZ(), coordinate->getPositionY(), cell->getObjectID());
}

bool PlayerManagerImplementation::checkEncumbrancies(PlayerCreature* player, ArmorObject* armor) {
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


void PlayerManagerImplementation::applyEncumbrancies(PlayerCreature* player, ArmorObject* armor) {
	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

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

void PlayerManagerImplementation::removeEncumbrancies(PlayerCreature* player, ArmorObject* armor) {
	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

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


void PlayerManagerImplementation::awardBadge(PlayerCreature* player, uint32 badge) {
	if (!Badge::exists(badge))
		return;

	ParameterizedStringId stringId("badge_n", "");
	stringId.setTO("badge_n", Badge::getName(badge));

	if (player->hasBadge(badge)) {
		stringId.setStringId("badge_n", "prose_hasbadge");
		player->sendSystemMessage(stringId);
		return;
	}

	player->setBadge(badge);
	stringId.setStringId("badge_n", "prose_grant");
	player->sendSystemMessage(stringId);

	switch (player->getNumBadges()) {
	case 5:
		awardBadge(player, Badge::COUNT_5);
		break;
	case 10:
		awardBadge(player, Badge::COUNT_10);
		break;
	case 25:
		awardBadge(player, Badge::COUNT_25);
		break;
	case 50:
		awardBadge(player, Badge::COUNT_50);
		break;
	case 75:
		awardBadge(player, Badge::COUNT_75);
		break;
	case 100:
		awardBadge(player, Badge::COUNT_100);
		break;
	case 125:
		awardBadge(player, Badge::COUNT_125);
		break;
	default:
		break;
	}

	if (Badge::getType(badge) == Badge::EXPLORATION) {
		switch (player->getBadgeTypeCount(Badge::EXPLORATION)) {
		case 10:
			awardBadge(player, Badge::BDG_EXP_10_BADGES);
			break;
		case 20:
			awardBadge(player, Badge::BDG_EXP_20_BADGES);
			break;
		case 30:
			awardBadge(player, Badge::BDG_EXP_30_BADGES);
			break;
		case 40:
			awardBadge(player, Badge::BDG_EXP_40_BADGES);
			break;
		case 45:
			awardBadge(player, Badge::BDG_EXP_45_BADGES);
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
void PlayerManagerImplementation::awardExperience(PlayerCreature* player, const String& xpType,
													int amount, bool sendSystemMessage, float localMultiplier) {

	player->getPlayerObject()->addExperience(xpType, amount * localMultiplier * globalExpMultiplier);

	//You receive 30 points of Surveying experience.
	if (sendSystemMessage) {
		ParameterizedStringId message("base_player","prose_grant_xp");
		message.setDI(amount * localMultiplier * globalExpMultiplier);
		message.setTO("exp_n", xpType);
		player->sendSystemMessage(message);
	}
}

void PlayerManagerImplementation::sendMessageOfTheDay(PlayerCreature* player) {
	String motd = ConfigManager::instance()->getMessageOfTheDay();

	ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::MOTD);

	suiMessageBox->setPromptTitle("Message of the Day");
	suiMessageBox->setPromptText(motd);

	player->sendMessage(suiMessageBox->generateMessage());
}

void PlayerManagerImplementation::handleAbortTradeMessage(PlayerCreature* player, bool doLock) {
	try {
		player->wlock(doLock);

		TradeContainer* tradeContainer = player->getTradeContainer();

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
			PlayerCreature* receiver = (PlayerCreature*) obj.get();

			Locker locker(receiver, player);
			//receiver->wlock(player);

			TradeContainer* receiverContainer = receiver->getTradeContainer();

			if (receiverContainer->getTradeTargetPlayer() == player->getObjectID()) {
				receiver->clearTradeContainer();
				receiver->sendMessage(msg->clone());
			}

			//receiver->unlock();
			locker.release();
		}

		player->sendMessage(msg->clone());

		delete msg;

		player->clearTradeContainer();

		player->unlock(doLock);
	} catch (...) {
		player->unlock(doLock);
		error("Unreported exception caught in PlayerManagerImplementation::handleAbortTradeMessage(Player* player)");
	}
}

void PlayerManagerImplementation::handleAddItemToTradeWindow(PlayerCreature* player, uint64 itemID) {
	Locker _locker(player);

	TradeContainer* tradeContainer = player->getTradeContainer();

	// First Verify Target is Player
	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	PlayerCreature* receiver = (PlayerCreature*) obj.get();

	SceneObject* inventory = player->getSlottedObject("inventory");
	ManagedReference<SceneObject*> inventoryObject = inventory->getContainerObject(itemID);

	if (inventoryObject == NULL) {
		player->sendSystemMessage("container_error_message", "container26");
		handleAbortTradeMessage(player, false);
		return;
	}

	tradeContainer->addTradeItem(inventoryObject);

	inventoryObject->sendWithoutParentTo(receiver);

	AddItemMessage* msg = new AddItemMessage(itemID);
	receiver->sendMessage(msg);
}

void PlayerManagerImplementation::handleGiveMoneyMessage(PlayerCreature* player, uint32 value) {
	Locker _locker(player);

	int currentMoney = player->getCashCredits();

	if (value > currentMoney)
		value = currentMoney;

	TradeContainer* tradeContainer = player->getTradeContainer();

	tradeContainer->setMoneyToTrade(value);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		PlayerCreature* receiver = (PlayerCreature*) obj.get();

		GiveMoneyMessage* msg = new GiveMoneyMessage(value);
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleAcceptTransactionMessage(PlayerCreature* player) {
	Locker _locker(player);

	TradeContainer* tradeContainer = player->getTradeContainer();

	if (tradeContainer == NULL)
		return;

	tradeContainer->setAcceptedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		PlayerCreature* receiver = (PlayerCreature*)obj.get();

		AcceptTransactionMessage* msg = new AcceptTransactionMessage();
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleUnAcceptTransactionMessage(PlayerCreature* player) {
	Locker _locker(player);

	TradeContainer* tradeContainer = player->getTradeContainer();

	tradeContainer->setAcceptedTrade(false);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		PlayerCreature* receiver = (PlayerCreature*)obj.get();

		UnAcceptTransactionMessage* msg = new UnAcceptTransactionMessage();
		receiver->sendMessage(msg);
	}

}

bool PlayerManagerImplementation::checkTradeItems(PlayerCreature* player, PlayerCreature* receiver) {
	TradeContainer* tradeContainer = player->getTradeContainer();
	TradeContainer* receiverContainer = receiver->getTradeContainer();

	if (tradeContainer->getTradeTargetPlayer() != receiver->getObjectID())
		return false;

	if (receiverContainer->getTradeTargetPlayer() != player->getObjectID())
		return false;

	SceneObject* playerInventory = player->getSlottedObject("inventory");
	SceneObject* receiverInventory = receiver->getSlottedObject("inventory");

	for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = tradeContainer->getTradeItem(i);

		String err;
		if (receiverInventory->canAddObject(scene, err) != 0)
			return false;

		if (!playerInventory->hasObjectInContainer(scene->getObjectID()))
			return false;
	}

	for (int i = 0; i < receiverContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = receiverContainer->getTradeItem(i);

		String err;
		if (playerInventory->canAddObject(scene, err) != 0)
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

void PlayerManagerImplementation::handleVerifyTradeMessage(PlayerCreature* player) {
	ObjectController* objectController = server->getObjectController();
	try {
		Locker locker(player);

		TradeContainer* tradeContainer = player->getTradeContainer();

		if (tradeContainer == NULL) {
			return;
		}

		tradeContainer->setVerifiedTrade(true);

		uint64 targID = tradeContainer->getTradeTargetPlayer();
		ManagedReference<SceneObject*> obj = server->getObject(targID);

		if (obj != NULL && obj->isPlayerCreature()) {
			PlayerCreature* receiver = (PlayerCreature*)obj.get();

			try {
				Locker clocker(receiver, player);

				TradeContainer* receiverTradeContainer = receiver->getTradeContainer();

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
						player->substractCashCredits(giveMoney);
						receiver->addCashCredits(giveMoney);
					}

					giveMoney = receiverTradeContainer->getMoneyToTrade();

					if (giveMoney > 0) {
						receiver->substractCashCredits(giveMoney);
						player->addCashCredits(giveMoney);
					}

					receiver->clearTradeContainer();

					player->clearTradeContainer();

					TradeCompleteMessage* msg = new TradeCompleteMessage();
					receiver->sendMessage(msg->clone());
					player->sendMessage(msg->clone());

					delete msg;
				}

			} catch (...) {
				System::out << "Exception in PlayerManagerImplementation::handleVerifyTradeMessage\n";
			}
		}

	} catch (...) {
		System::out << "Unreported exception caught in PlayerManagerImplementation::handleVerifyTradeMessage(Player* player)\n";
	}
}
