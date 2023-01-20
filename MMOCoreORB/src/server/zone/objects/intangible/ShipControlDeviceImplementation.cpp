/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipControlDeviceImplementation::generateObject(CreatureObject* player) {
	//info("generating ship", true);
	//return;

	ZoneServer* zoneServer = getZoneServer();

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	Locker clocker(controlledObject, player);

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ() + 10, player->getPositionY());

	try {
		if (player->getZone() != nullptr) {
			player->getZone()->transferObject(controlledObject, -1, true);
		} else if (player->getSpaceZone() != nullptr) {
			player->getSpaceZone()->transferObject(controlledObject, -1, true);
		}
	} catch (ArrayIndexOutOfBoundsException& e) {
		e.printStackTrace();
	}

	controlledObject->transferObject(player, 5, true);

	updateStatus(1);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr)
		ghost->setTeleporting(true);
}

void ShipControlDeviceImplementation::storeShip(CreatureObject* player, ShipObject* ship) {
	if (player == nullptr || !player->isInQuadTree())
		return;

	if (ship == nullptr || !ship->isInOctTree())
		return;

	Locker locker(ship);

	String storedLocation = player->getCityRegion().get()->getRegionDisplayedName();

	ship->setStoredLocation(storedLocation);

	ship->destroyObjectFromWorld(true);

	transferObject(ship, 4, true);

	updateStatus(0);
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
}

int ShipControlDeviceImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	return 0;
}

bool ShipControlDeviceImplementation::canBeTradedTo(CreatureObject* player, CreatureObject* receiver, int numberInTrade) {
	ManagedReference<SceneObject*> datapad = receiver->getSlottedObject("datapad");

	if (datapad == nullptr)
		return false;

	ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

	int shipsInDatapad = numberInTrade;
	int maxStoredShips = playerManager->getBaseStoredShips();

	for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

		if (obj != nullptr && obj->isShipControlDevice() ){
			shipsInDatapad++;
		}
	}

	if (shipsInDatapad >= maxStoredShips){
		player->sendSystemMessage("That person has too many ships in their datapad");
		receiver->sendSystemMessage("You already have the maximum number of ships that you can own.");
		return false;
	}

	return true;
}
