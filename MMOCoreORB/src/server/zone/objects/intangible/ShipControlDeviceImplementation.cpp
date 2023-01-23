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
#include "server/zone/managers/ship/ShipManager.h"
#include "templates/params/creature/PlayerArrangement.h"

void ShipControlDeviceImplementation::storeShip(CreatureObject* player) {
	if (player == nullptr || !isShipLaunched())
		return;

	ShipObject* ship = cast<ShipObject*>(getControlledObject());

	if (ship == nullptr)
		return;

	ShipControlDevice* device = _this.getReferenceUnsafeStaticCast();

	Locker lock(device);
	Locker clock(ship, device);

	CityRegion* cityRegion = player->getCityRegion().get();

	// City Region for player can be a nullptr when they log off in the ship. The ship will still have its launch
	// point as a stored location and the player will be transported back there as well.
	if (cityRegion != nullptr) {
		String storedLocation = cityRegion->getRegionDisplayedName();

		ship->setStoredLocation(storedLocation);
	}

	ship->destroyObjectFromWorld(true);

	transferObject(ship, PlayerArrangement::RIDER, true);

	setShipLaunchStatus(false);
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

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer != nullptr)
		return false;

	PlayerManager* playerManager = zoneServer->getPlayerManager();

	if (playerManager == nullptr)
		return false;

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

			if (shipDevice != nullptr && (shipDevice->getShipType() == ShipManager::POBSHIP))
				pobShips++;
		}
	}

	if (totalShips >= maxStoredShips) {
		receiver->sendSystemMessage("@space/space_interaction:toomanyships"); // You have too many ships in your datapad already!
		return false;
	}

	if (pobShips >= 1 && getShipType() == ShipManager::POBSHIP) {
		receiver->sendSystemMessage("@space/space_interaction:too_many_pobs"); // You cannot launch another ship with an interior. Empty out one of your other ships and you may take off with this ship.
		return false;
	}

	return true;
}
