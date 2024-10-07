//
// Created by g on 12/20/17.
//

#ifndef CORE3_HYPERSPACETOLOCATIONTASK_H
#define CORE3_HYPERSPACETOLOCATIONTASK_H

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"

class HyperspaceToLocationTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipObject*> ship;
	String zoneName;
	Vector3 location;
	int iteration;

public:
	HyperspaceToLocationTask(CreatureObject* pl, ShipObject* ship, const String& zoneName, const Vector3& location) : Task() {
		play = pl;
		this->zoneName = zoneName;
		this->location = location;
		this->ship = ship;
		iteration = 0;
	}

	void run() {
		CreatureObject* player = play.get();
		ShipObject* shipObject = ship.get();

		if (player == nullptr || shipObject == nullptr) {
			return;
		}

		if (!shipObject->isHyperspacing()) {
			return;
		}

		int currentIter = iteration++;

		// shipObject->info(true) << shipObject->getDisplayedName() << " HyperspaceToLocationTask - Iteration: " << currentIter << " Pilot: " << player->getDisplayedName();

		Locker locker(shipObject);

		switch (currentIter) {
		case 0:
			shipObject->sendShipMembersMessage("@space/space_interaction:hyperspace_route_begin");

			reschedule(5000);
			return;
		case 1: // 25%
		case 2: // 50%
		case 3: // 75%
		case 4: { // 100%
			String strid = "@space/space_interaction:hyperspace_route_calculation_";

			strid += String::valueOf(currentIter);

			shipObject->sendShipMembersMessage(strid);

			if (currentIter >= 4) {
				//close s-foils as the ship is orienting if they're still open
				uint32 optionsBitmask = shipObject->getOptionsBitmask();

				if (optionsBitmask & OptionBitmask::WINGS_OPEN)
					shipObject->clearOptionBit(OptionBitmask::WINGS_OPEN);

				shipObject->sendMembersHyperspaceOrientMessage(zoneName, location);

				reschedule(1000);
			} else {
				reschedule(5000);
			}

			return;
		}
		case 5: // t-4
		case 6: // t-3
		case 7: // t-2
		case 8: { // t-1
			String strid = "@space/space_interaction:hyperspace_route_calculation_";
			strid += String::valueOf(currentIter);

			shipObject->sendShipMembersMessage(strid);
			shipObject->sendShipMembersMusicMessage("sound/ship_hyperspace_countdown.snd");

			reschedule(1000);
			return;
		}
		case 9: {
			// Randomize and set the location.
			location.setX(location.getX() + System::random(100.f));
			location.setZ(location.getZ() + System::random(100.f));
			location.setY(location.getY() + System::random(100.f));

			shipObject->sendMembersHyperspaceBeginMessage(zoneName, location);

			reschedule(6000);
			return;
		}
		case 10: {
			// Switch the ships zone
			shipObject->switchZone(zoneName, location.getX(), location.getZ(), location.getY());

			// Switch all remaining players onboard the ship
			int totalPlayers = shipObject->getTotalPlayersOnBoard();
			auto zoneServer = shipObject->getZoneServer();

			for (int i = 0; i < totalPlayers; i++) {
				auto shipMember = shipObject->getPlayerOnBoard(i);

				if (shipMember == nullptr) {
					continue;
				}

				try {
					Locker memberLock(shipMember, shipObject);

					Vector3 memberPosition = shipMember->getPosition();
					uint64 parentID = shipMember->getParentID();

					// shipObject->info(true) << "Transferring Ship Member: " << shipMember->getDisplayedName() << " To Position: " << memberPosition.toString() << " ID: " << parentID;

					const Quaternion* direction = nullptr;

					if (parentID != shipObject->getObjectID() && zoneServer != nullptr) {
						auto parentObject = zoneServer->getObject(parentID);

						if (parentObject != nullptr) {
							direction = parentObject->getDirection();
						}
					} else {
						direction = shipObject->getDirection();
					}

					if (direction != nullptr) {
						shipMember->setDirection(direction->getW(), direction->getX(), direction->getY(), direction->getZ());
					}

					shipMember->switchZone(zoneName, memberPosition.getX(), memberPosition.getZ(), memberPosition.getY(), parentID, false, shipMember->getContainmentType());
				} catch (...) {
					shipMember->error() << "Failed to transport player onboard ship in hyperspace - ShipID: " << shipObject->getObjectID() << " Ship Member ID: " << shipMember->getObjectID();
				}
			}

			Reference<ShipObject*> shipRef = shipObject;

			Core::getTaskManager()->scheduleTask([shipRef] () {
				if (shipRef == nullptr) {
					return;
				}

				Locker lock(shipRef);

				shipRef->setHyperspacing(false);
			}, "ShipRemoveHyperspaceLambda", 1000);

			return;
		}
		}
	}
};

#endif // CORE3_HYPERSPACETOLOCATIONTASK_H
