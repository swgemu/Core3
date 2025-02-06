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

		if (player == nullptr || shipControlDevice == nullptr)
			return;

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

		// Lock the ship
		Locker shipLock(ship);

		// Remove the ships astromech if one is assigned
		if (ship->getShipDroidID() != 0) {
			removeDroid(ship, player);
		}

		// Copy list of the players onboard for removal
		Vector<uint64> playersOnBoard = ship->getPlayersOnBoard();

#ifdef DEBUG_SHIP_STORE
		info(true) << "StoreShipTask seeing " << playersOnBoard.size() << " player(s) on board.";
#endif

		// This function should remove all players in the ship.
		for (int i = playersOnBoard.size() - 1; i >= 0; --i) {
			auto shipMemberID = playersOnBoard.get(i);
			auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

			if (shipMember == nullptr) {
				continue;
			}

			try {
				// Cross lock the player for removal
				Locker playerLock(shipMember, ship);

				if (!removePlayer(shipMember, zoneName, coordinates)) {
					error() << "Failed to remove player from Ship - ShipID: " << ship->getObjectID() << " Player ID: " << shipMember->getObjectID();
					return;
				}
			} catch (...) {
				error() << "Failed to remove player from Ship - ShipID: " << ship->getObjectID() << " Player ID: " << shipMember->getObjectID();
			}

			playersOnBoard.remove(i);
		}

		// Clear Staff Speed
		ship->setStaffShipSpeed(0.f);

		// Destroy the ship from the zone.
		ship->destroyObjectFromWorld(false);

		// Lock the device and transfer the ship inside.
		Locker sLock(shipControlDevice, ship);

		if (shipControlDevice->transferObject(ship, PlayerArrangement::RIDER, false, false, false)) {
			ship->cancelRecovery();
			ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);
			ship->clearPlayersOnBoard();
		}

		shipControlDevice->updateStatus(shipControlDevice->isShipLaunched(), true);

#ifdef DEBUG_SHIP_STORE
		info(true) << "Setting stored postion";
#endif

		Locker cLock(player, shipControlDevice);
		shipControlDevice->setStoredLocationData(player);
		cLock.release();

		if (player->isGrouped()) {
			auto group = player->getGroup();

			if (group == nullptr)
				return;

			Locker glocker(group, ship);

			group->updateMemberShip(player, nullptr);
		}
	}

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

	bool removeDroid(ShipObject* ship, CreatureObject* player) {
		if (ship == nullptr || player == nullptr) {
			return false;
		}

		auto zoneServer = ship->getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

		const uint64& droidID = ship->getShipDroidID();

		if (droidID == 0) {
			return false;
		}

		ManagedReference<SceneObject*> droidRef = zoneServer->getObject(droidID);

		if (droidRef == nullptr || !droidRef->isDroidObject()) {
			return false;
		}

		auto droidObject = dynamic_cast<DroidObject*>(droidRef.get());

		if (droidObject == nullptr) {
			return false;
		}

		ManagedReference<ControlDevice*> controlDevice = droidObject->getControlDevice().get();

		if (controlDevice == nullptr || !controlDevice->isPetControlDevice()) {
			return false;
		}

		auto petControlDevice = dynamic_cast<PetControlDevice*>(controlDevice.get());

		if (petControlDevice == nullptr) {
			return false;
		}

		Locker cLock(controlDevice, ship);

		auto storeTask = new PetControlDeviceStoreTask(petControlDevice, player, true);

		if (storeTask != nullptr) {
			storeTask->execute();
		}

		return true;
	}
};

#endif /* STORESHIPTASK_H_ */
