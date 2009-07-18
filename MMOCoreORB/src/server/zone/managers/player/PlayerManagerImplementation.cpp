/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "PlayerManager.h"

PlayerManagerImplementation::PlayerManagerImplementation(ObjectManager* objMan, ZoneProcessServerImplementation* srv) {
	objectManager = objMan;

	server = srv;

	playerMap = new PlayerMap(3000);
}
