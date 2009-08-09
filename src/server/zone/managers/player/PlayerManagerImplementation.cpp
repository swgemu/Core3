/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

#include "../object/ObjectManager.h"
#include "../../packets/charcreation/ClientCreateCharacter.h"
#include "../../packets/charcreation/ClientCreateCharacterSuccess.h"
#include "../../packets/charcreation/ClientCreateCharacterFailed.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/managers/command/CommandQueueManager.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/db/ServerDatabase.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"


PlayerManagerImplementation::PlayerManagerImplementation(ObjectManager* objMan, ZoneProcessServerImplementation* srv) :
	Logger("PlayerManager") {
	objectManager = objMan;

	server = srv;

	playerMap = new PlayerMap(3000);

	commandQueueManager = new CommandQueueManager(srv);

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

	NameManager* nm = server->getNameManager();
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
		return false;
	}

	SceneObject* player = objectManager->createObject(playerCRC); // player

	if (player == NULL) {
		error("could not create player... could not create player object");
		return false;
	}

	if (!player->isPlayerCreature()) {
		player->finalize();
		error("could not create player... wrong object type");
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

		info("created hair object");
	}

	playerCreature->setHeight(callback->getHeight());

	UnicodeString biography;
	callback->getBiography(biography);
	playerCreature->setBiography(biography);

	ZoneClientSession* client = data->getClient();

	playerCreature->setClient(client);
	client->setPlayer(player);

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(player->getObjectID());
	playerCreature->sendMessage(msg);

	ZoneServer* zoneServer = server->getZoneServer();
	if (callback->getTutorialFlag()) {
		Zone* zone = zoneServer->getZone(42);

		String tut = "object/building/general/shared_newbie_hall.iff";
		String cell = "object/cell/shared_cell.iff";

		BuildingObject* tutorial = (BuildingObject*) objectManager->createObject(tut.hashCode());
		tutorial->setStaticBuilding(false);

		SceneObject* cellTut = NULL;

		for (int i = 0; i < 14; ++i) {
			cellTut = objectManager->createObject(cell.hashCode());

			tutorial->addCell((CellObject*)cellTut);

			if (i == 10)
				cellTut->addObject(player, -1);
		}

		tutorial->insertToZone(zone);

		player->initializePosition(27.0f, -3.5f, -165.0f);
		player->setZone(zone);
	} else {
		Zone* zone = zoneServer->getZone(8);
		player->setZone(zone);
	}

	StringBuffer infoMsg;
	infoMsg << "player " << name.toString() << " successfully created";
	info(infoMsg);

	/*Zone* zone = server->getZoneServer()->getZone(8);
	player->setZone(zone);*/

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
	SceneObject* hair = objectManager->createObject(sharedHairObjectFile.hashCode());

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
	SceneObject* inventory = objectManager->createObject(0x3969E83B); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->addObject(inventory, 4);

	SceneObject* datapad = objectManager->createObject(0x73BA5001); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	player->addObject(datapad, 4);

	SceneObject* playerObject = objectManager->createObject(0x619BAE21); //player object

	if (playerObject == NULL) {
		error("could not create player object");
		return false;
	}

	player->addObject(playerObject, 4);

	SceneObject* bank = objectManager->createObject(0x70FD1394); //bank

	if (bank == NULL) {
		error("could not create bank");
		return false;
	}

	player->addObject(bank, 4);

	SceneObject* missionBag = objectManager->createObject(0x3D7F6F9F); //mission bag

	if (missionBag == NULL) {
		error("could not create mission bag");
		return false;
	}

	player->addObject(missionBag, 4);

	// temp

	SceneObject* vibro = objectManager->createObject(0x652688CE);
	player->addObject(vibro, 4);
	player->setWeaponID(vibro->getObjectID());

	SceneObject* vibro2 = objectManager->createObject(0x652688CE);
	inventory->addObject(vibro2, -1);

	String bharmor = "object/tangible/wearables/armor/bounty_hunter/shared_armor_bounty_hunter_chest_plate.iff";
	SceneObject* armor = objectManager->createObject(bharmor.hashCode());
	inventory->addObject(armor, -1);

	String backpack = "object/tangible/wearables/backpack/shared_backpack_s01.iff";
	SceneObject* backpackObject = objectManager->createObject(backpack.hashCode());
	inventory->addObject(backpackObject, -1);

	return true;
}
