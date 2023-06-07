
#ifndef STORESHIPTASK_H_
#define STORESHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/params/creature/PlayerArrangement.h"

//#define DEBUG_SHIP_STORE

class StoreShipTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipControlDevice*> shipDev;

public:
	StoreShipTask(CreatureObject* creo, ShipControlDevice* controlDevice) : play(creo), shipDev(controlDevice) {
		setLoggingName("StoreShipTask");
	}

	void run() {
#ifdef DEBUG_SHIP_STORE
		info(true) << "StoreShipTask called";
#endif

		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<ShipControlDevice*> shipControlDevice = shipDev.get();

		if (player == nullptr || shipControlDevice == nullptr)
			return;

		ManagedReference<ShipObject*> ship = shipControlDevice->getControlledObject()->asShipObject();

		if (ship == nullptr) {
			return;
		}

		String storedZoneName = shipControlDevice->getStoredZoneName();
		Vector3 storedPosition = shipControlDevice->getStoredPosition();

		Locker shipLock(ship);

		if (ship->isPobShipObject()) {
#ifdef DEBUG_SHIP_STORE
			info(true) << "Ship is POB type";
#endif

			auto chair = ship->getPilotChair().get();

			if (chair != nullptr) {
				ManagedReference<CreatureObject*> pilot = chair->getSlottedObject("ship_pilot_pob").castTo<CreatureObject*>();

				if (pilot != nullptr) {
#ifdef DEBUG_SHIP_STORE
					info(true) << "Pilot is not null";
#endif

					ship->unlock();

					try {
						Locker pilotLock(pilot);
						removePlayer(pilot, storedZoneName, storedPosition);
					} catch (...) {
						error() << "Failed to remove pilot from POB Ship Chair - ShipID: " << ship->getObjectID();
					}

					ship->wlock();
				}
			}
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
					removePlayer(slottedCreo, storedZoneName, storedPosition);
				} catch (...) {
					error() << "Failed to remove player from ship slotted object - ShipID: " << ship->getObjectID();
				}

				ship->wlock();
			}
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "Check Total Cells: " << ship->getTotalCellNumber();
#endif

		for (int k = 0; k < ship->getTotalCellNumber(); ++k) {
#ifdef DEBUG_SHIP_STORE
			info(true) << "Checking Cell #" << k;
#endif

			auto cellObject = ship->getCell(k);

			if (cellObject == nullptr) {
				continue;
			}

			int childObjects = cellObject->getContainerObjectsSize();

			if (childObjects <= 0)
				continue;

#ifdef DEBUG_SHIP_STORE
			info(true) << "Checking cells objects - total count: " << childObjects;
#endif

			// Traverse the vector backwards since the size will change as objects are removed.
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

				ship->unlock();

				try {
					Locker playLock(playerCreo);

					removePlayer(playerCreo, storedZoneName, storedPosition);
				} catch (...) {
					error() << "Failed to remove player from ship cell #" << k << " - ShipID: " << ship->getObjectID();
				}

				ship->wlock();
			}
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "Ship Players have been removed.";
#endif

		Locker sLock(shipControlDevice, ship);

		if (shipControlDevice->transferObject(ship, PlayerArrangement::RIDER, true) && !shipControlDevice->isShipLaunched()) {
			ship->cancelRecovery();
			ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);
		}

		shipControlDevice->updateStatus(shipControlDevice->isShipLaunched(), true);

#ifdef DEBUG_SHIP_STORE
		info(true) << "Setting stored location";
#endif

		Locker cLock(player, ship);
		shipControlDevice->setStoredLocationData(player);
	}

	void removePlayer(CreatureObject* player, String storedZoneName, Vector3 storedPosition) {
#ifdef DEBUG_SHIP_STORE
		info(true) << "removePlayer called";
#endif

		if (player == nullptr)
			return;

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return;

		auto zone = zoneServer->getZone(storedZoneName);

		if (zone == nullptr) {
			return;
		}

#ifdef DEBUG_SHIP_STORE
		info(true) << "removing player: " << player->getDisplayedName() << " to zone: " << storedZoneName;
#endif

		player->clearSpaceStates();
		player->switchZone(storedZoneName, storedPosition.getX(), storedPosition.getZ(), storedPosition.getY(), 0);
	}
};

#endif /* STORESHIPTASK_H_ */
