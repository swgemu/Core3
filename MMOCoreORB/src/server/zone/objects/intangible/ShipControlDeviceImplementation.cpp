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

void ShipControlDeviceImplementation::setStoredLocationData(CreatureObject* player) {
	// The control device needs to be locked as well as the player coming into this function

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

bool ShipControlDeviceImplementation::launchShip(CreatureObject* player, const String& zoneName, const Vector3& position) {
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr) {
		return false;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer ==  nullptr)
		return false;

	Zone* zone = zoneServer->getZone(zoneName);

	if (zone == nullptr || !zone->isSpaceZone())
		return false;

	SpaceZone* spaceZone = cast<SpaceZone*>(zone);

	if (spaceZone == nullptr)
		return false;

	Locker sLock(ship, _this.getReferenceUnsafeStaticCast());

	ship->initializePosition(position.getX(), position.getZ(), position.getY());
	ship->setDirection(1,0,0,0);
	ship->setMovementCounter(0);

	if (spaceZone->transferObject(ship, -1, true)) {
		ship->setFactionStatus(player->getFactionStatus());
		ship->setShipFaction(player->getFaction());
		ship->scheduleRecovery();

		if (player->isInvulnerable()) {
			ship->setOptionBit(OptionBitmask::INVULNERABLE, false);
		} else {
			ship->clearOptionBit(OptionBitmask::INVULNERABLE, false);
		}

		updateStatus(true, true);

		return true;
	}

	return false;
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;

	auto ghost = player->getPlayerObject().get();

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

	if (isShipLaunched()) {
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

			LaunchShipTask* launchTask = new LaunchShipTask(player, _this.getReferenceUnsafeStaticCast(), dummyVec);

			if (launchTask != nullptr)
				launchTask->execute();

			return 0;
		}
	}

	return 1;
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
	auto ship = controlledObject.get().castTo<ShipObject*>();

	if (ship == nullptr)
		return 1;

	auto owner = ship->getOwner().get();

	if (owner == nullptr)
		return 1;

	if (ship->isInOctTree()) {
		owner->sendSystemMessage("You must land your ship before it can be destroyed.");
		return 1;
	}

	if (ship->isPobShipObject()) {
		auto pobShip = ship->asPobShipObject();

		if (pobShip != nullptr && pobShip->getCurrentNumberOfPlayerItems() > 0) {
			owner->sendSystemMessage("You must remove all of your items from your ship before it can be destroyed.");
			return 1;
		}
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

void ShipControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

bool ShipControlDeviceImplementation::isShipLaunched() {
	auto object = getControlledObject();

	return object != nullptr && object->isInOctTree();
}
