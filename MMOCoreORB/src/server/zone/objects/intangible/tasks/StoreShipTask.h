/*
 * StoreShipTask.h
 */

#ifndef STORESHIPTASK_H_
#define STORESHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "templates/params/creature/PlayerArrangement.h"
#include "server/zone/objects/player/PlayerObject.h"

//#define DEBUG_SHIP_STORE

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

		Locker shipLock(ship);

		// Remove the ship owner. This may be the pilot, but we cannot know for sure.
		Locker ownerLock(player, ship);

		removePlayer(player, zoneName, coordinates);

		ship->removePlayerOnBoard(player);

		ownerLock.release();

		// This function should remove all remaining players in the ship.
		int totalPlayers = ship->getTotalPlayersOnBoard();

		for (int i = totalPlayers - 1; i >= 0; --i) {
			auto shipMember = ship->getPlayerOnBoard(i);

			if (shipMember != nullptr && shipMember->getRootParent() == ship) {
				try {
					Locker playerLock(shipMember, ship);

					removePlayer(shipMember, zoneName, coordinates);
				} catch (...) {
					error() << "Failed to remove player from Ship - ShipID: " << ship->getObjectID() << " Player ID: " << shipMember->getObjectID();
				}
			}

			 ship->removePlayerOnBoard(i);
		}

		// Destroy the ship from the zone.
		ship->destroyObjectFromWorld(false);

		// Lock the device and transfer the ship inside.
		Locker sLock(shipControlDevice, ship);

		if (shipControlDevice->transferObject(ship, PlayerArrangement::RIDER, true)) {
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

	void removePlayer(CreatureObject* player, String newZoneName, Vector3 location) {
#ifdef DEBUG_SHIP_STORE
		info(true) << "removePlayer called";
#endif

		if (player == nullptr)
			return;

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return;

		auto zone = zoneServer->getZone(newZoneName);

		if (zone == nullptr) {
			return;
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "removing player: " << player->getDisplayedName() << " to zone: " << newZoneName;
#endif

		player->clearSpaceStates();

		if (player->isOnline()) {
			player->switchZone(newZoneName, location.getX(), location.getZ(), location.getY(), 0);
		} else {
			player->setPosition(location.getX(), location.getZ(), location.getY());

			player->setParent(nullptr);

			auto ghost = player->getPlayerObject();

			if (ghost != nullptr) {
				ghost->setSavedParentID(0);
				ghost->setSavedTerrainName(newZoneName);
			}
		}
	}
};

#endif /* STORESHIPTASK_H_ */
