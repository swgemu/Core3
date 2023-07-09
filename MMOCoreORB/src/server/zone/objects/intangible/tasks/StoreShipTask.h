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

		if (ship->isPobShipObject()) {
			PobShipObject* pobShip = ship->asPobShipObject();

#ifdef DEBUG_SHIP_STORE
			info(true) << "Ship is POB type";
#endif

			if (pobShip != nullptr) {
				auto chair = pobShip->getPilotChair().get();

				if (chair != nullptr) {
					ManagedReference<CreatureObject*> pilot = chair->getSlottedObject("ship_pilot_pob").castTo<CreatureObject*>();

					if (pilot != nullptr) {
#ifdef DEBUG_SHIP_STORE
						info(true) << "Pilot is not null";
#endif

						pobShip->unlock();

						try {
							Locker pilotLock(pilot);
							removePlayer(pilot, zoneName, coordinates);
						} catch (...) {
							error() << "Failed to remove pilot from POB Ship Chair - ShipID: " << pobShip->getObjectID();
						}

						pobShip->wlock();
					}
				}
			}

	#ifdef DEBUG_SHIP_STORE
			info(true) << "Check Total Cells: " << ship->getTotalCellNumber();
	#endif

			for (int k = 0; k < pobShip->getTotalCellNumber(); ++k) {
	#ifdef DEBUG_SHIP_STORE
				info(true) << "Checking Cell #" << k;
	#endif

				auto cellObject = pobShip->getCell(k);

				if (cellObject == nullptr) {
					continue;
				}

				int childObjects = cellObject->getContainerObjectsSize();

				if (childObjects <= 0)
					continue;

#ifdef DEBUG_SHIP_STORE
				info(true) << "Checking cells objects - total count: " << childObjects;
#endif

				// Iterate the vector backwards since the size will change as objects are removed.
				for (int ii = childObjects - 1; ii >= 0; --ii) {
					ManagedReference<SceneObject*> sceneO = cellObject->getContainerObject(ii);

#ifdef DEBUG_SHIP_STORE
					info(true) << "Cell-ContainerObjects - checking #" << ii << " ID: " << sceneO->getObjectID() << "   " << sceneO->getObjectNameStringIdName() << ".";
#endif

					if (sceneO == nullptr || !sceneO->isPlayerCreature())
						continue;

					auto playerCreo = sceneO->asCreatureObject();

					if (playerCreo == nullptr)
						continue;

					pobShip->unlock();

					try {
						Locker playLock(playerCreo);

						removePlayer(playerCreo, zoneName, coordinates);
					} catch (...) {
						error() << "Failed to remove player from ship cell #" << k << " - ShipID: " << pobShip->getObjectID();
					}

					pobShip->wlock();
				}
			}

#ifdef DEBUG_SHIP_STORE
			info(true) << "Ship Players have been removed.";
#endif
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "Checking slotted objects for players - Total: " << ship->getSlottedObjectsSize();
#endif

		for (int i = 0; i < ship->getSlottedObjectsSize(); ++i) {
			ManagedReference<CreatureObject*> slottedCreo = ship->getSlottedObject(i).castTo<CreatureObject*>();

#ifdef DEBUG_SHIP_STORE
			info(true) << "SlottedObjects - checking: " << slottedCreo->getObjectID();
#endif

			if (slottedCreo != nullptr) {
				ship->unlock();

				try {
					Locker slotLock(slottedCreo);
					removePlayer(slottedCreo, zoneName, coordinates);
				} catch (...) {
					error() << "Failed to remove player from ship slotted object - ShipID: " << ship->getObjectID();
				}

				ship->wlock();
			}
		}

		ship->destroyObjectFromWorld(false);

		Locker sLock(shipControlDevice, ship);

		if (shipControlDevice->transferObject(ship, PlayerArrangement::RIDER, true)) {
			ship->cancelRecovery();
			ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);
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
		player->switchZone(newZoneName, location.getX(), location.getZ(), location.getY(), 0);
	}
};

#endif /* STORESHIPTASK_H_ */
