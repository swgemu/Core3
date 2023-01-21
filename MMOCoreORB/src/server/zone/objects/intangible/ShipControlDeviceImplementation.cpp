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

	int totalShips = numberInTrade;
	int pobShips = 0;
	int maxStoredShips = playerManager->getBaseStoredShips();

	for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

		if (obj == nullptr)
			continue;

		if (obj->isShipControlDevice()) {
			totalShips++;

			ShipControlDevice* shipDevice = obj.castTo<ShipControlDevice*>();

			if (shipDevice != nullptr && shipDevice->isPobShipController())
				pobShips++;
		}
	}

	if (totalShips >= maxStoredShips) {
		StringIdChatParameter maxShips("space_interaction", "toomanyships"); // You have too many ships in your datapad already!
		player->sendSystemMessage(maxShips);

		return 1;
	}

	/*
	if (pobShips > 1) {
		StringIdChatParameter maxPobShips("space_interaction", "too_many_pobs"); // You cannot launch another ship with an interior. Empty out one of your other ships and you may take off with this ship.
		player->sendSystemMessage(maxPobShips);

		return 1;
	}*/

	return true;
}

bool ShipControlDeviceImplementation::isPobShipController() {
	TangibleObject* shipTanO = getControlledObject();

	if (shipTanO == nullptr || !shipTanO->isShipObject())
		return false;

	if (shipTanO->getContainerObjectsSize() > 0)
		return true;

	return false;
}
