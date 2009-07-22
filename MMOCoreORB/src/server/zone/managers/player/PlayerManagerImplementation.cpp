/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

#include "../object/ObjectManager.h"
#include "../../packets/charcreation/ClientCreateCharacter.h"

PlayerManagerImplementation::PlayerManagerImplementation(ObjectManager* objMan, ZoneProcessServerImplementation* srv) :
	Logger("PlayerManager") {
	objectManager = objMan;

	server = srv;

	playerMap = new PlayerMap(3000);
}

bool PlayerManagerImplementation::createPlayer(MessageCallback* data) {
	ClientCreateCharacterCallback* callback = (ClientCreateCharacterCallback*) data;

	String race;
	callback->getRaceFile(race);
	info("trying to create " + race, true);

	uint32 playerCRC = race.hashCode();

	SceneObject* player = objectManager->createObject(playerCRC); // player

	if (player == NULL) {
		error("could not create player");
		return false;
	}

	if (player->getGameObjectType() != 0x409) {
		player->finalize();
		error("could not create player");
		return false;
	}

	SceneObject* datapad = objectManager->createObject(0x73BA5001); //datapad

	if (datapad == NULL) {
		error("could not create player datapad");
		return false;
	}

	SceneObject* inventory = objectManager->createObject(0x3969E83B); // character_inventory

	if (inventory == NULL) {
		error("could not create player inventory");
		return false;
	}

	player->addObject(datapad);
	player->addObject(inventory);

	ZoneClientSession* client = data->getClient();

	((PlayerCreature*)player)->setClient(client);
	client->setPlayer(player);

	return true;
}
