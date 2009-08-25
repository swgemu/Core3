/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

#include "../../packets/charcreation/ClientCreateCharacter.h"
#include "../../packets/charcreation/ClientCreateCharacterSuccess.h"
#include "../../packets/charcreation/ClientCreateCharacterFailed.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/db/ServerDatabase.h"
#include "server/chat/ChatManager.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"


PlayerManagerImplementation::PlayerManagerImplementation(ZoneServer* zoneServer, ZoneProcessServerImplementation* impl) :
	ManagedObjectImplementation(), Logger("PlayerManager") {
	server = zoneServer;
	processor = impl;

	playerMap = new PlayerMap(3000);

	setGlobalLogging(true);
	setLogging(true);
}

bool PlayerManagerImplementation::checkExistentNameInDatabase(const String& name) {
	if (name.isEmpty())
		return false;

	try {
		String fname = name.toLowerCase();
		MySqlDatabase::escapeString(fname);
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
	if (!checkExistentNameInDatabase(firstName)) {
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
	try {
		wlock();

		ClientCreateCharacterCallback* callback = (ClientCreateCharacterCallback*) data;

		String race;
		callback->getRaceFile(race);
		info("trying to create " + race);

		int raceID = Races::getRaceID(race);
		uint32 playerCRC = Races::getRaceCRC(raceID);

		UnicodeString name;
		callback->getCharacterName(name);

		if (!checkPlayerName(callback)) {
			info("invalid name " + name.toString());
			unlock();
			return false;
		}

		SceneObject* player = server->createObject(playerCRC, true); // player

		if (player == NULL) {
			error("could not create player... could not create player object");
			unlock();
			return false;
		}

		if (!player->isPlayerCreature()) {
			//player->finalize(); destroy object
			error("could not create player... wrong object type");
			unlock();
			return false;
		}

		PlayerCreature* playerCreature = (PlayerCreature*) player;
		createAllPlayerObjects(playerCreature);

		playerCreature->setRaceID((byte)raceID);

		String playerCustomization;
		callback->getCustomizationString(playerCustomization);
		playerCreature->setCustomizationString(playerCustomization);

		playerCreature->setObjectName(name);

		//hair
		String hairObjectFile;
		callback->getHairObject(hairObjectFile);

		String hairCustomization;
		callback->getHairCustomization(hairCustomization);

		TangibleObject* hair = createHairObject(hairObjectFile, hairCustomization);

		if (hair != NULL) {
			player->addObject(hair, 4);
			hair->updateToDatabase();

			info("created hair object");
		}

		playerCreature->setHeight(callback->getHeight());

		UnicodeString biography;
		callback->getBiography(biography);
		playerCreature->setBiography(biography);

		ZoneClientSession* client = data->getClient();

		playerCreature->setClient(client);
		client->setPlayer(player);

		playerCreature->setAccountID(client->getAccountID());

		if (callback->getTutorialFlag()) {
			createTutorialBuilding(playerCreature);
		} else {
			Zone* zone = server->getZone(8);
			player->setZone(zone);
		}

		server->updateObjectToDatabase(player);

		StringBuffer infoMsg;
		infoMsg << "player " << name.toString() << " successfully created";
		info(infoMsg);

		ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(player->getObjectID());
		playerCreature->sendMessage(msg);

		ChatManager* chatManager = server->getChatManager();

		chatManager->addPlayer(playerCreature);

		unlock();
	} catch (...) {
		error("unreported exception caught while creating player");
		unlock();
	}

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
	SceneObject* hair = server->createObject(sharedHairObjectFile.hashCode(), true);

	if (hair == NULL) {
		info("objectManager returned NULL hair object");
		return NULL;
	}

	if (hair->getGameObjectType() != SceneObjectImplementation::GENERICITEM) {
		info("wrong hair object type");
		hair->finalize();

		return NULL;
	} else {
		hairObject = (TangibleObject*) hair;

		hairObject->setCustomizationString(hairCustomization);

		info("hair object created successfully");
	}

	return hairObject;
}

bool PlayerManagerImplementation::createAllPlayerObjects(PlayerCreature* player) {
	SceneObject* inventory = server->createObject(0x3969E83B, true); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->addObject(inventory, 4);

	SceneObject* datapad = server->createObject(0x73BA5001, true); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	player->addObject(datapad, 4);
	datapad->updateToDatabase();

	SceneObject* playerObject = server->createObject(0x619BAE21, true); //player object

	if (playerObject == NULL) {
		error("could not create player object");
		return false;
	}

	player->addObject(playerObject, 4);
	playerObject->updateToDatabase();

	SceneObject* bank = server->createObject(0x70FD1394, true); //bank

	if (bank == NULL) {
		error("could not create bank");
		return false;
	}

	player->addObject(bank, 4);
	bank->updateToDatabase();

	SceneObject* missionBag = server->createObject(0x3D7F6F9F, true); //mission bag

	if (missionBag == NULL) {
		error("could not create mission bag");
		return false;
	}

	player->addObject(missionBag, 4);
	missionBag->updateToDatabase();

	// temp

	SceneObject* vibro = server->createObject(0x652688CE, true);
	player->addObject(vibro, 4);
	player->setWeaponID(vibro->getObjectID());
	vibro->updateToDatabase();

	SceneObject* vibro2 = server->createObject(0x652688CE, true);
	inventory->addObject(vibro2, -1);
	vibro2->updateToDatabase();

	String bharmor = "object/tangible/wearables/armor/bounty_hunter/shared_armor_bounty_hunter_chest_plate.iff";
	SceneObject* armor = server->createObject(bharmor.hashCode(), true);
	inventory->addObject(armor, -1);
	armor->updateToDatabase();

	String backpack = "object/tangible/wearables/backpack/shared_backpack_s01.iff";
	SceneObject* backpackObject = server->createObject(backpack.hashCode(), true);
	inventory->addObject(backpackObject, -1);
	backpackObject->updateToDatabase();
	inventory->updateToDatabase();

	return true;
}

void PlayerManagerImplementation::createTutorialBuilding(PlayerCreature* player) {
	Zone* zone = server->getZone(42);

	SceneObject* oldPlayer = server->getObject(0x1500000001uLL);

	if (player!= oldPlayer && oldPlayer != NULL) {
		SceneObject* tutCell = oldPlayer->getParent();

		if (tutCell != NULL) {
			player->initializePosition(27.0f, -3.5f, -165.0f);
			player->setZone(zone);

			tutCell->addObject(player, -1);

			return;
		}
	}

	String tut = "object/building/general/shared_newbie_hall.iff";
	String cell = "object/cell/shared_cell.iff";

	BuildingObject* tutorial = (BuildingObject*) server->createObject(tut.hashCode(), true);
	tutorial->setStaticBuilding(false);

	SceneObject* travelTutorialTerminal = server->createObject(4258705837uL, true);

	SceneObject* cellTut = NULL;

	for (int i = 0; i < 14; ++i) {
		SceneObject* newCell = server->createObject(cell.hashCode(), true);

		tutorial->addCell((CellObject*)newCell);

		if (i == 10) {
			cellTut = newCell;
			cellTut->addObject(travelTutorialTerminal, -1);
		}
	}

	tutorial->insertToZone(zone);
	travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);
	travelTutorialTerminal->insertToZone(zone);

	player->initializePosition(27.0f, -3.5f, -165.0f);
	player->setZone(zone);
	cellTut->addObject(player, -1);
}
