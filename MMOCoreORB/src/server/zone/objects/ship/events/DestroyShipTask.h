#ifndef DESTROYSHIPTASK_H_
#define DESTROYSHIPTASK_H_

#include "server/zone/SpaceZone.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/packets/ship/DestroyShipMessage.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"

class DestroyShipTask: public Task {
private:
	ManagedWeakReference<ShipObject*> weakShip;

	uint64 sequenceStamp;
	int iteration;

public:
	DestroyShipTask(ShipObject* ship) : Task() {
		this->weakShip = ship;

		sequenceStamp = System::getMiliTime();
		iteration = 0;
	}

	void run() {
		auto ship = weakShip.get();

		if (ship == nullptr) {
			return;
		}

		auto zone = ship->getZone();

		if (zone == nullptr) {
			return;
		}

		auto pilot = ship->getOwner().get();

		Locker sLock(ship);

		switch (iteration++) {
			case 0: {
				ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);

				if (ship->isBoosterActive()) {
					ship->removeComponentFlag(Components::BOOSTER, ShipComponentFlag::ACTIVE, true);
					ship->restartBooster();
				}

				auto msg = new DestroyShipMessage(ship->getObjectID(), System::random(100) * 0.01f);
				ship->broadcastMessage(msg, false);

				if (pilot == nullptr && ship->getPersistenceLevel() == 0) {
					ship->destroyObjectFromWorld(true);
					ship->destroyObjectFromDatabase(true);
				} else {
					ship->setOptionBit(OptionBitmask::DESTROYING, true);
					reschedule(5000);
				}

				ship->notifyDespawn(zone);

				return;
			}
			case 1: {
				ship->clearOptionBit(OptionBitmask::DESTROYING, true);

				auto spaceManager = zone->getSpaceManager();

				if (spaceManager == nullptr) {
					return;
				}

				if (pilot != nullptr) {
					pilot->sendToOwner(true);
				}

				Vector3 randomPosition = Vector3(System::random(100) - 50.f, System::random(100) - 50.f, 0.f);
				Vector3 stationPosition = spaceManager->getClosestSpaceStationPosition(ship->getPosition(), "neutral") + randomPosition;
				const String zoneName = zone->getZoneName();

				ship->setDirection(1,0,0,0);

				// Switch the ships zone
				ship->switchZone(zoneName, stationPosition.getX(), stationPosition.getZ(), stationPosition.getY());

				// Switch all remaining players onboard the ship
				int totalPlayers = ship->getTotalPlayersOnBoard();
				auto zoneServer = ship->getZoneServer();

				for (int i = 0; i < totalPlayers; i++) {
					auto shipMember = ship->getPlayerOnBoard(i);

					if (shipMember == nullptr) {
						continue;
					}

					try {
						Locker memberLock(shipMember, ship);

						Vector3 memberPosition = shipMember->getPosition();
						uint64 parentID = shipMember->getParentID();

						// ship->info(true) << "Transferring Ship Member: " << shipMember->getDisplayedName() << " To Position: " << memberPosition.toString() << " ID: " << parentID;

						const Quaternion* direction = nullptr;

						if (parentID != ship->getObjectID() && zoneServer != nullptr) {
							auto parentObject = zoneServer->getObject(parentID);

							if (parentObject != nullptr) {
								direction = parentObject->getDirection();
							}
						} else {
							direction = ship->getDirection();
						}

						if (direction != nullptr) {
							shipMember->setDirection(direction->getW(), direction->getX(), direction->getY(), direction->getZ());
						}

						shipMember->switchZone(zoneName, memberPosition.getX(), memberPosition.getZ(), memberPosition.getY(), parentID, false, shipMember->getContainmentType());
					} catch (...) {
						shipMember->error() << "Failed to transport player onboard ship in DestroyShipTask - ShipID: " << ship->getObjectID() << " Ship Member ID: " << shipMember->getObjectID();
					}
				}

				return;
			}

			default: {
				if (pilot != nullptr) {
					auto zoneServer = pilot->getZoneServer();

					if (zoneServer == nullptr)
						return;

					ManagedReference<SceneObject*> device = zoneServer->getObject(ship->getControlDeviceID());

					if (device == nullptr || !device->isShipControlDevice())
						return;

					ShipControlDevice* shipControlDevice = device.castTo<ShipControlDevice*>();

					if (shipControlDevice == nullptr)
						return;

					StoreShipTask* storeTask = new StoreShipTask(pilot, shipControlDevice, shipControlDevice->getStoredZoneName(), shipControlDevice->getStoredPosition());

					if (storeTask != nullptr)
						storeTask->execute();

					return;
				}

				if (ship->getPersistenceLevel() == 0) {
					ship->destroyObjectFromWorld(true);
					ship->destroyObjectFromDatabase(true);
				}

				return;
			}
		}
	}
};

#endif //DESTROYSHIPTASK_H_
