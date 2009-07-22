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
#include "server/zone/objects/player/Races.h"

#include "server/zone/ZoneProcessServerImplementation.h"

PlayerManagerImplementation::PlayerManagerImplementation(ObjectManager* objMan, ZoneProcessServerImplementation* srv) :
	Logger("PlayerManager") {
	objectManager = objMan;

	server = srv;

	playerMap = new PlayerMap(3000);

	setGlobalLogging(true);
	setLogging(true);
}

bool PlayerManagerImplementation::createPlayer(MessageCallback* data) {
	ClientCreateCharacterCallback* callback = (ClientCreateCharacterCallback*) data;

	String race;
	callback->getRaceFile(race);
	info("trying to create " + race);

	int raceID = Races::getRaceID(race);
	uint32 playerCRC = Races::getRaceCRC(raceID);

	SceneObject* player = objectManager->createObject(playerCRC); // player

	if (player == NULL) {
		error("could not create player... could not create player object");
		return false;
	}

	if (player->getGameObjectType() != 0x409) {
		player->finalize();
		error("could not create player... wrong object type");
		return false;
	}

	PlayerCreature* playerCreature = (PlayerCreature*) player;

	playerCreature->setRaceID((byte)raceID);

	String playerCustomization;
	callback->getCustomizationString(playerCustomization);
	playerCreature->setCustomizationString(playerCustomization);

	UnicodeString name;
	callback->getCharacterName(name);
	playerCreature->setObjectName(name);

	//hair
	String hairObjectFile;
	callback->getHairObject(hairObjectFile);

	String hairCustomization;
	callback->getHairCustomization(hairCustomization);

	TangibleObject* hair = createHairObject(hairObjectFile, hairCustomization);

	if (hair != NULL) {
		player->addObject(hair);

		info("created hair object");
	}

	playerCreature->setHeight(callback->getHeight());

	UnicodeString biography;
	callback->getBiography(biography);
	playerCreature->setBiography(biography);

	SceneObject* datapad = objectManager->createObject(0x73BA5001); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	player->addObject(datapad);

	SceneObject* inventory = objectManager->createObject(0x3969E83B); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->addObject(inventory);

	ZoneClientSession* client = data->getClient();

	playerCreature->setClient(client);
	client->setPlayer(player);

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(player->getObjectID());
	playerCreature->sendMessage(msg);

	StringBuffer infoMsg;
	infoMsg << "player " << name.toString() << " successfully created";
	info(infoMsg);

	Zone* zone = server->getZoneServer()->getZone(8);
	player->setZone(zone);

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
