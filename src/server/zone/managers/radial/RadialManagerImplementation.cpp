/*
 * RadialManagerImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "RadialManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"

RadialManagerImplementation::RadialManagerImplementation(ZoneServer* server) : ManagedObjectImplementation(), Logger() {
	setLoggingName("RadialManager");

	setGlobalLogging("true");
	setLogging("true");

	zoneServer = server;
}

void RadialManagerImplementation::handleObjectMenuRequest(PlayerCreature* player, ObjectMenuResponse* defaultMenuResponse, uint64 objectID) {
	//Pre: Player is WLOCKED
	//Post: Player is WLOCKED

	ManagedReference<SceneObject> menuObject = zoneServer->getObject(objectID);

	if (menuObject != NULL) {
		try {
			menuObject->wlock(player);

			menuObject->fillObjectMenuResponse(defaultMenuResponse);

			menuObject->unlock();
		} catch (...) {
			menuObject->unlock();
			error("RadialManagerImplementation::handleObjectMenuRequest");
		}
	}

	defaultMenuResponse->finish();

	player->sendMessage(defaultMenuResponse);
}

void RadialManagerImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectID, uint64 objectID) {
	//Pre: player is NOT wlocked upon entry
	//Post: nothing is WLOCKED

	//System::out << "entering radial call 1" << endl;

	ManagedReference<SceneObject> selectedObject = zoneServer->getObject(objectID);

	if (selectedObject == NULL) {
		StringBuffer infoMsg;
		infoMsg << "NULL object selected in ObjectMenuSelect objectID: 0x" << hex << objectID;
		error(infoMsg.toString());

		return;
	}

	try {
		player->wlock();

		try {
			selectedObject->wlock(player);

			//System::out << "entering radial call" << endl;
			selectedObject->handleObjectMenuSelect(player, selectID);

			selectedObject->unlock();
		} catch (...) {
			selectedObject->unlock();

			throw;
		}

		player->unlock();
	} catch (Exception& e) {
		player->unlock();

		error("exception caught in void RadialManagerImplementation::handleObjectMenuSelect");
		error(e.getMessage());
		e.printStackTrace();
	} catch (...) {
		player->unlock();
		error("unreported exception caught in void RadialManagerImplementation::handleObjectMenuSelect");
	}



	//remove the switch and make the calls virtual to SceneObject??
/*
	switch (selectID) {
	case 0: //UNKNOWN
	case 1: //COMBAT_TARGET
	case 2: //COMBAT_UNTARGET
	case 3: //COMBAT_ATTACK
	case 4: //COMBAT_PEACE
	case 5: //COMBAT_DUEL
	case 6: //COMBAT_DEATH_BLOW
		break;
	case 7: //EXAMINE
		break;
	case 8: //TRADE_START
		//handleTrade(player, obj);
		break;
	case 9: //TRADE_ACCEPT
		break;
	case 10: //ITEM_PICKUP
	case 11: //ITEM_EQUIP
		break;
	case 12: //ITEM_UNEQUIP
		break;
	case 13: //ITEM_DROP
		//handleItemDrop(player, obj);
		break;
	case 14: //ITEM_DESTROY
		break;
	case 15: //ITEM_TOKEN
		break;
	case 16: //ITEM_OPEN
		break;
	case 17: //ITEM_OPEN_NEW_WINDOW
		break;
	case 18: //ITEM_ACTIVATE
	case 19: //ITEM_DEACTIVATE
		break;
	case 20: //ITEM_USE
		handleUseObject(player, selectedObject);
		break;
	default:
		break;
	}
	*/
}
