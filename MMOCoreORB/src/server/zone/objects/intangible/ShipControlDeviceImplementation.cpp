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
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "templates/params/creature/PlayerArrangement.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

void ShipControlDeviceImplementation::setStoredLocationData(CreatureObject* player) {
	auto ghost = player == nullptr ? nullptr : player->getPlayerObject().get();

	if (ghost == nullptr) {
		return;
	}

	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return;
	}

	auto zone = player->getZone();

	if (zone == nullptr) {
		return;
	}

	auto planetManager = zone->getPlanetManager();

	if (planetManager == nullptr) {
		return;
	}

	auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition(), FLT_MAX);

	if (travelPoint == nullptr) {
		return;
	}

	Vector3 position = travelPoint->getArrivalPosition();
	String pointName = travelPoint->getPointName();
	String zoneName = zone->getZoneName();

	float z = CollisionManager::getWorldFloorCollision(position.getX(), position.getY(), position.getZ(), zone, true);
	position.setZ(z);

	storedPosition = position;
	storedCityName = pointName;
	storedZoneName = zoneName;

	ghost->setSpaceLaunchLocation(position);
	ghost->setSpaceLaunchCityName(pointName);
	ghost->setSpaceLaunchZone(zoneName);
}

Vector3 ShipControlDeviceImplementation::getStoredPosition(bool randomPosition) {
	Vector3 random = randomPosition ? Vector3(System::random(10) - 5, System::random(10) - 5, 0) : Vector3::ZERO;
	return storedPosition + random;
}

bool ShipControlDeviceImplementation::storeShip(CreatureObject* player) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return false;
	}

	if (!ejectPlayers()) {
		return false;
	}

	Locker sLock(ship);
	ship->destroyObjectFromWorld(false);

	ship->initializePosition(0,0,0);
	ship->setDirection(1,0,0,0);
	ship->setMovementCounter(0);

	if (transferObject(ship, PlayerArrangement::RIDER, true) && !isShipLaunched()) {
		ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);
	}

	updateStatus(isShipLaunched(), true);

	if (player != nullptr) {
		Locker cLock(player);
		setStoredLocationData(player);
	}

	return isShipLaunched() ? false : true;
}

bool ShipControlDeviceImplementation::launchShip(CreatureObject* player, const String& zoneName, const Vector3& position) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return false;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer ==  nullptr)
		return false;

	auto spaceZone = zoneServer->getSpaceZone(zoneName);

	if (spaceZone == nullptr) {
		return false;
	}

	Locker sLock(ship);
	ship->destroyObjectFromWorld(false);

	ship->initializePosition(position.getX(), position.getZ(), position.getY());
	ship->setDirection(1,0,0,0);
	ship->setMovementCounter(0);

	if (spaceZone->transferObject(ship, -1, true) && isShipLaunched()) {
		ship->setFactionStatus(player->getFactionStatus());
		ship->setShipFaction(player->getFaction());
		ship->scheduleRecovery();

		if (player->isInvulnerable()) {
			ship->setOptionBit(OptionBitmask::INVULNERABLE, false);
		} else {
			ship->clearOptionBit(OptionBitmask::INVULNERABLE, false);
		}
	}

	updateStatus(isShipLaunched(), true);
	setStoredLocationData(player);

	return isShipLaunched() ? true : false;
}

bool ShipControlDeviceImplementation::removePlayer(CreatureObject* player) {
	auto zone = getZoneServer()->getZone(storedZoneName);

	if (zone == nullptr) {
		return false;
	}

	Locker sLock(player);
	player->destroyObjectFromWorld(false);
	player->switchZone(storedZoneName, storedPosition.getX(), storedPosition.getZ(), storedPosition.getY(), 0);

	return player->getRootParent() == nullptr;
}

bool ShipControlDeviceImplementation::insertPlayer(CreatureObject* player) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return false;
	}

	auto spaceZone = ship->getSpaceZone();

	if (spaceZone == nullptr) {
		return false;
	}

	Locker sLock(player);
	player->destroyObjectFromWorld(false);

	if (ship->getChassisCategory() == "pob") {
		auto station = ship->getPilotChair().get();

		if (station == nullptr) {
			return false;
		}

		player->setState(CreatureState::PILOTINGPOBSHIP);
		player->switchZone(spaceZone->getZoneName(), station->getPositionX(),station->getPositionZ(),station->getPositionY(), station->getObjectID());
	} else {
		player->setState(CreatureState::PILOTINGSHIP);
		player->switchZone(spaceZone->getZoneName(), ship->getPositionX(),ship->getPositionZ(),ship->getPositionY(), ship->getObjectID());
	}

	return player->getRootParent() == ship;
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	auto ghost = player == nullptr ? nullptr : player->getPlayerObject().get();

	if (ghost == nullptr || !ghost->hasGodMode()) {
		return;
	}

	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return;
	}

	auto root = player->getRootParent();

	if (root != nullptr && root->isShipObject() && root != ship) {
		return;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	if (isShipLaunched()) {
		String zoneName = StringIdManager::instance()->getStringId("@planet_n:" + storedZoneName).toString();
		menuResponse->addRadialMenuItem(LANDSHIP, 3, "Land Ship: " + storedCityName + ", " + zoneName);
	} else {
		menuResponse->addRadialMenuItem(LAUNCHSHIP, 3, "Launch Ship");

		for (int i = 0; i < zoneServer->getSpaceZoneCount(); ++i) {
			auto zone = zoneServer->getSpaceZone(i);

			if (zone == nullptr) {
				continue;
			}

			menuResponse->addRadialMenuItemToRadialID(LAUNCHSHIP, 1 + LAUNCHSHIP + i, 3, "@planet_n:" + zone->getZoneName());
		}
	}
}

int ShipControlDeviceImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return 1;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	if (isShipLaunched()) {
		if (selectedID == LANDSHIP) {
			auto zone = zoneServer->getZone(storedZoneName);

			if (zone == nullptr) {
				return 1;
			}

			removePlayer(player);
			storeShip(player);

			return isShipLaunched() ? 1 : 0;
		}
	} else {
		if (selectedID > LAUNCHSHIP) {
			int zoneIndex = selectedID - LAUNCHSHIP - 1;
			int zoneCount = zoneServer->getSpaceZoneCount();

			auto zone = (zoneIndex < zoneCount) ? zoneServer->getSpaceZone(zoneIndex) : nullptr;

			if (zone == nullptr) {
				return 1;
			}

			launchShip(player, zone->getZoneName(), player->getPosition());
			insertPlayer(player);

			return isShipLaunched() ? 0 : 1;
		}
	}

	return 1;
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

bool ShipControlDeviceImplementation::isShipLaunched() {
	auto object = getControlledObject();

	return object != nullptr && object->isInOctTree();
}

void ShipControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship != nullptr) {
		if (!storeShip(ship->getOwner().get())) {
			return;
		}

		Locker sLock(ship);
		ship->destroyObjectFromDatabase(destroyContainedObjects);
	}

	ControlDeviceImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

bool ShipControlDeviceImplementation::ejectPlayers() {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return false;
	}

	auto chair = ship->getPilotChair().get();

	if (chair != nullptr) {
		ManagedReference<CreatureObject*> pilot = chair->getSlottedObject("ship_pilot_pob").castTo<CreatureObject*>();

		if (pilot != nullptr && !removePlayer(pilot)) {
			return false;
		}
	}

	for (int i = 0; i < ship->getSlottedObjectsSize(); ++i) {
		ManagedReference<CreatureObject*> object = ship->getSlottedObject(i).castTo<CreatureObject*>();

		if (object != nullptr && !removePlayer(object)) {
			return false;
		}
	}

	for (int i = 0; i < ship->getContainerObjectsSize(); ++i) {
		ManagedReference<CreatureObject*> object = ship->getContainerObject(i).castTo<CreatureObject*>();

		if (object != nullptr && !removePlayer(object)) {
			return false;
		}
	}

	for (int i = 0; i < ship->getTotalCellNumber(); ++i) {
		auto cell = ship->getCell(i);

		if (cell == nullptr) {
			continue;
		}

		for (int ii = 0; ii < cell->getContainerObjectsSize(); ++ii) {
			ManagedReference<CreatureObject*> object = cell->getContainerObject(ii).castTo<CreatureObject*>();

			if (object != nullptr && !removePlayer(object)) {
				return false;
			}
		}
	}

	return true;
}
