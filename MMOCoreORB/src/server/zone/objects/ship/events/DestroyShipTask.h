#ifndef DESTROYSHIPTASK_H_
#define DESTROYSHIPTASK_H_

#include "server/zone/SpaceZone.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/packets/ship/DestroyShipMessage.h"
#include "server/zone/packets/object/DataTransform.h"

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

		auto spaceZone = ship->getSpaceZone();

		if (spaceZone == nullptr) {
			return;
		}

		auto pilot = ship->getOwner().get();

		Locker sLock(ship);

		switch (iteration++) {
			case 0: {
				ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);

				if (ship->isBoosterActive()) {
					ship->removeComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED, true);
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

				return;
			}

			case 1: {
				ship->clearOptionBit(OptionBitmask::DESTROYING, true);

				auto spaceManager = spaceZone->getSpaceManager();

				if (spaceManager == nullptr) {
					return;
				}

				if (pilot != nullptr) {
					pilot->sendToOwner(true);
				}

				Vector3 randomPosition = Vector3(System::random(100) - 50.f, System::random(100) - 50.f, 0.f);
				Vector3 stationPosition = spaceManager->getClosestSpaceStationPosition(ship->getPosition(), "neutral") + randomPosition;

				long sequence = System::getMiliTime() - sequenceStamp;

				ship->setPosition(stationPosition.getX(), stationPosition.getZ(), stationPosition.getY());
				ship->setMovementCounter(ship->getMovementCounter() + sequence);
				ship->setDirection(1,0,0,0);

				if (pilot != nullptr) {
					auto data = new DataTransform(ship);
					pilot->sendMessage(data);
				}

				return;
			}

			default: {
				if (pilot != nullptr) {
					Locker pLock(pilot);
					ship->storeShip(pilot);
				}

				if (ship->isInOctTree()) {
					ship->destroyObjectFromWorld(true);
				}

				if (pilot == nullptr && ship->getPersistenceLevel() == 0) {
					ship->destroyObjectFromDatabase(true);
				}

				return;
			}
		}
	}
};

#endif //DESTROYSHIPTASK_H_
