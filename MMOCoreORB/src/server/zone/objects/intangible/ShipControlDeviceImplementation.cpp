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
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/intangible/tasks/LaunchShipTask.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "templates/params/creature/PlayerArrangement.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"


ShipObject* ShipControlDeviceImplementation::launchShip(CreatureObject* player, const String& zoneName, const Vector3& position) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return nullptr;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer ==  nullptr) {
		return nullptr;
	}

	auto zone = zoneServer->getZone(zoneName);

	if (zone == nullptr) {
		return nullptr;
	}

	Locker sLock(ship, _this.getReferenceUnsafeStaticCast());

	ship->initializePosition(position.getX(), position.getZ(), position.getY());
	ship->setDirection(1,0,0,0);
	ship->setMovementCounter(0);

	ship->clearPlayersOnBoard();

	if (!zone->transferObject(ship, -1, true)) {
		return nullptr;
	}

	ship->scheduleRecovery();

	if (player->isInvulnerable()) {
		ship->setOptionBit(OptionBitmask::INVULNERABLE, false);
	} else {
		ship->clearOptionBit(OptionBitmask::INVULNERABLE, false);
	}

	updateStatus(true, true);

	// ship->info(true) << ship->getDisplayedName() << " ship succesfully launched into space zone";

	return ship;
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;

	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return;
	}

	// Name Ship
	menuResponse->addRadialMenuItem(RadialOptions::SET_NAME, 3, "@sui:rename_ship"); // Rename Ship

	// Deed Ship
	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU1, 3, "@sui:pack_ship"); // Deed Ship

	auto root = player->getRootParent();

	// Player is in another ship, no additional menu options given
	if (root != nullptr && root->isShipObject() && root != ship) {
		return;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	// Launch and Land from datapad
	auto ghost = player->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged()) {
		return;
	}

	if (isShipLaunched()) {
		String zoneName = StringIdManager::instance()->getStringId("@planet_n:" + storedZoneName).toString();
		menuResponse->addRadialMenuItem(LANDSHIP, 3, "Land Ship: " + parkingLocation + ", " + zoneName);
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
	if (player == nullptr)
		return 0;

	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return 1;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	// Name Ship
	if (selectedID == RadialOptions::SET_NAME) {
		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return 1;
		}

		shipManager->promptNameShip(player, _this.getReferenceUnsafeStaticCast());
	// Deed Ship
	} else if (selectedID == RadialOptions::SERVER_MENU1) {
		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return 1;
		}

		shipManager->reDeedShip(player, _this.getReferenceUnsafeStaticCast());
	} else if (isShipLaunched()) {
		if (selectedID == LANDSHIP) {
			auto zone = zoneServer->getZone(storedZoneName);

			if (zone == nullptr) {
				return 1;
			}

			StoreShipTask* task = new StoreShipTask(player, _this.getReferenceUnsafeStaticCast(), storedZoneName, storedPosition);

			if (task != nullptr)
				task->execute();

			return isShipLaunched() ? 1 : 0;
		}
	} else {
		if (selectedID > LAUNCHSHIP) {
			int spaceZoneIndex = selectedID - LAUNCHSHIP - 1;
			int spaceZoneCount = zoneServer->getSpaceZoneCount();

			auto zone = (spaceZoneIndex < spaceZoneCount) ? zoneServer->getSpaceZone(spaceZoneIndex) : nullptr;

			if (zone == nullptr) {
				return 1;
			}

			Vector<uint64> dummyVec;

			LaunchShipTask* launchTask = new LaunchShipTask(player, _this.getReferenceUnsafeStaticCast(), dummyVec, zone->getZoneName());

			if (launchTask != nullptr)
				launchTask->execute();

			return 0;
		}
	}

	return 1;
}

void ShipControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("parking_spot", getParkingLocation());
}

bool ShipControlDeviceImplementation::canBeTradedTo(CreatureObject* player, CreatureObject* receiver, int numberInTrade) {
	ManagedReference<SceneObject*> datapad = receiver->getSlottedObject("datapad");

	if (datapad == nullptr)
		return false;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
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

int ShipControlDeviceImplementation::canBeDestroyed(CreatureObject* player) {
	if (player == nullptr)
		return 1;

	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return 1;
	}

	auto owner = ship->getOwner().get();

	if (owner == nullptr) {
		return 1;
	}

	if (isShipLaunched()) {
		player->sendSystemMessage("You must land your ship before it can be destroyed.");
		return 1;
	} else if (ship->isPobShip()) {
		auto pobShip = ship->asPobShip();

		if (pobShip != nullptr && pobShip->getCurrentNumberOfPlayerItems() > 0) {
			owner->sendSystemMessage("You must remove all of your items from your ship before it can be destroyed.");
			return 1;
		}
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

void ShipControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	auto ship = getControlledObject();

	if (ship != nullptr && ship->getLocalZone() != nullptr) {
		Locker clock(ship, _this.getReferenceUnsafeStaticCast());

		ship->destroyObjectFromDatabase(true);
	}

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

// The control device needs to be locked as well as the player coming into this function
void ShipControlDeviceImplementation::setStoredLocationData(CreatureObject* player) {
	if (player == nullptr)
		return;

	auto ghost = player->getPlayerObject();

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

	auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition(), 128.f);

	if (travelPoint == nullptr) {
		return;
	}

	Vector3 position = travelPoint->getArrivalPosition();
	String pointName = travelPoint->getPointName();
	String zoneName = zone->getZoneName();

	float z = CollisionManager::getWorldFloorCollision(position.getX(), position.getY(), position.getZ(), zone, true);
	position.setZ(z);

	storedPosition = position;
	parkingLocation = pointName;
	storedZoneName = zoneName;

	ghost->setSpaceLaunchLocation(position);
	ghost->setSpaceLaunchCityName(pointName);
	ghost->setSpaceLaunchZone(zoneName);

	ship->setSpaceLaunchLocation(position);
	ship->setSpaceLaunchCityName(pointName);
	ship->setSpaceLaunchZone(zoneName);
}

Vector3 ShipControlDeviceImplementation::getStoredPosition(bool randomPosition) {
	Vector3 random = randomPosition ? Vector3(System::random(10) - 5, System::random(10) - 5, 0) : Vector3::ZERO;
	return storedPosition + random;
}

bool ShipControlDeviceImplementation::isShipLaunched() {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr)
		return false;

	return ship->isShipLaunched();
}
