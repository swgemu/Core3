/*
 * StoreShipTask.h
 */

#ifndef STORESHIPTASK_H_
#define STORESHIPTASK_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "templates/params/creature/PlayerArrangement.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreTask.h"

// #define DEBUG_SHIP_STORE

class StoreShipTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipControlDevice*> shipDev;
	String zoneName;
	Vector3 coordinates;

public:
	StoreShipTask(CreatureObject* creo, ShipControlDevice* controlDevice, String zName, Vector3 coords) : play(creo), shipDev(controlDevice), zoneName(zName), coordinates(coords) {
		setLoggingName("StoreShipTask");
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<ShipControlDevice*> shipControlDevice = shipDev.get();

		if (player == nullptr || shipControlDevice == nullptr) {
			return;
		}

		auto ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->isOnLoadScreen()) {
			reschedule(2000);
			return;
		}

		ManagedReference<ShipObject*> ship = shipControlDevice->getControlledObject()->asShipObject();

		if (ship == nullptr) {
			return;
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "StoreShipTask called for Player: " << player->getDisplayedName() << " Ship: " << ship->getDisplayedName() << " Zone: " << zoneName << " Loc: " << coordinates.toString();
#endif

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		// Lock the player
		Locker shipLock(player);
		Locker shipClock(ship, player);

		// Remove the ships astromech if one is assigned
		if (ship->getShipDroidID() != 0) {
			removeDroid(ship, player);
		}

		// Make sure no players remain in the ship
		ship->removeAllPlayersFromShip();

		// Clear Staff Speed
		ship->setStaffShipSpeed(0.f);

		// Clear the wings open
		ship->clearOptionBit(OptionBitmask::WINGS_OPEN, false);

		// Destroy the ship from the zone.
		ship->destroyObjectFromWorld(false);

		// Lock the device and transfer the ship inside.
		Locker deviceClock(shipControlDevice, player);

		if (!shipControlDevice->transferObject(ship, PlayerArrangement::RIDER, false, false, false)) {
			error() << "StoreShipTask -- Failed to transfer ship into control Device! Ship: " << ship->getObjectID() << " Control Device: " << shipControlDevice->getObjectID();
			return;
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "ShipControlDevice State and stored postion updated.";
#endif

		shipControlDevice->updateStatus(shipControlDevice->isShipLaunched(), true);
		shipControlDevice->setStoredLocationData(player);

		deviceClock.release();

		if (player->isGrouped()) {
			auto group = player->getGroup();

			if (group == nullptr)
				return;

			Locker glocker(group, ship);

			group->updateMemberShip(player, nullptr);
		}
	}

	/*
	// Player is locked coming into this function
	bool removePlayer(CreatureObject* player, String newZoneName, Vector3 location) {
#ifdef DEBUG_SHIP_STORE
		info(true) << "removePlayer called";
#endif

		if (player == nullptr) {
			return false;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "removing player: " << player->getDisplayedName() << " to zone: " << newZoneName;
#endif

		auto parent = player->getParent().get();

		// Clear the Players Space States
		player->clearSpaceStates();

		// Clear the Players Space Mission Objects
		player->removeAllSpaceMissionObjects(false);

		player->switchZone(newZoneName, location.getX(), location.getZ(), location.getY(), 0, false);

		if (parent != nullptr && parent->hasObjectInContainer(player->getObjectID())) {
#ifdef DEBUG_SHIP_STORE
			info(true) << "Clearing player parent ID: " << parent->getObjectID();
#endif
			parent->removeObject(player, nullptr, false);
		}

		return true;
	}
	*/

	bool removeDroid(ShipObject* ship, CreatureObject* player) {
		if (ship == nullptr || player == nullptr) {
			return false;
		}

		auto zoneServer = ship->getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

		const uint64& controlDeviceID = ship->getShipDroidID();

		if (controlDeviceID == 0) {
			return false;
		}

		ManagedReference<SceneObject*> controlDeviceRef = zoneServer->getObject(controlDeviceID);

		if (controlDeviceRef == nullptr || !controlDeviceRef->isPetControlDevice()) {
			return false;
		}

		ManagedReference<PetControlDevice*> controlDevice = dynamic_cast<PetControlDevice*>(controlDeviceRef.get());

		if (controlDevice == nullptr) {
			return false;
		}

		Locker cLock(controlDevice, ship);

		auto storeTask = new PetControlDeviceStoreTask(controlDevice, player, true);

		if (storeTask != nullptr) {
			storeTask->execute();
		}

		return true;
	}
};

#endif /* STORESHIPTASK_H_ */
