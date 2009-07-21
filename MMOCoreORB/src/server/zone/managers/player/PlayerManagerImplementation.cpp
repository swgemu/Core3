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

	SceneObject* player = objectManager->createObject(0x1D52730E); // player

	if (player->getGameObjectType() != 0x409) {
		player->finalize();
		return false;
	}

	SceneObject* datapad = objectManager->createObject(0x73BA5001); //datapad
	SceneObject* inventory = objectManager->createObject(0x3969E83B); // character_inventory

	if (player == NULL || datapad == NULL || inventory == NULL) {
		error("could not create player");
		return false;
	}

	player->addObject(datapad);
	player->addObject(inventory);

	((PlayerCreature*)player)->setClient(data->getClient());
	//client->setPlayer(player);

	return true;
}
