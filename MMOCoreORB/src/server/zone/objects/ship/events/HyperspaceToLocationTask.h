//
// Created by g on 12/20/17.
//

#ifndef CORE3_HYPERSPACETOLOCATIONTASK_H
#define CORE3_HYPERSPACETOLOCATIONTASK_H

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/ZoneClientSession.h"

#define DEBUG_HYPERSPACE_PACKETS

class HyperspaceToLocationTask : public Task {
	WeakReference<CreatureObject*> play;
	WeakReference<ShipObject*> ship;
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
		auto player = play.get();
		auto shipObject = ship.get();

		if (player == nullptr || shipObject == nullptr) {
			return;
		}

		if (!shipObject->isHyperspacing() || !shipObject->isShipLaunched()) {
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
#ifdef DEBUG_HYPERSPACE_PACKETS
			startPacketLoggingForShip(shipObject);
#endif // DEBUG_HYPERSPACE_PACKETS

			// Randomize and set the location.
			location.setX(location.getX() + System::random(100.f));
			location.setZ(location.getZ() + System::random(100.f));
			location.setY(location.getY() + System::random(100.f));

			shipObject->sendMembersHyperspaceBeginMessage(zoneName, location);

			reschedule(6000);
			return;
		}
		case 10: {
			// Switch the ships zone - passengers in cells travel with the ship automatically
			shipObject->switchZone(zoneName, location.getX(), location.getZ(), location.getY());

			// Notify all players onboard about the zone change.
			// Close objects are stale from the old zone - clear them before sending
			// so sendToOwner doesn't re-send passengers to each other via the close objects loop.
			int totalPlayers = shipObject->getTotalPlayersOnBoard();

			for (int i = 0; i < totalPlayers; i++) {
				auto shipMember = shipObject->getPlayerOnBoard(i);

				if (shipMember == nullptr) {
					continue;
				}

				try {
					Locker memberLock(shipMember, shipObject);

					auto closeObjects = shipMember->getCloseObjects();

					if (closeObjects != nullptr) {
						closeObjects->removeAll();
					}

					shipMember->sendToOwner(true);
				} catch (...) {
					shipMember->error() << "Failed to notify player onboard ship after hyperspace - ShipID: " << shipObject->getObjectID() << " Ship Member ID: " << shipMember->getObjectID();
				}
			}

			Reference<ShipObject*> shipRef = shipObject;

			// Delay must outlast all onEnter lambdas which schedule at
			// ((cellIndex * 200) + 1000)ms. For a ship with 20 cells that's
			// up to 4800ms. Use 6000ms to be safe.
			Core::getTaskManager()->scheduleTask([shipRef] () {
				if (shipRef == nullptr) {
					return;
				}

				Locker lock(shipRef);

				shipRef->setHyperspacing(false);
			}, "ShipRemoveHyperspaceLambda", 6000);

#ifdef DEBUG_HYPERSPACE_PACKETS
			// Delay packet logging stop to capture post-hyperspace sends
			Reference<ShipObject*> logShipRef = shipObject;
			WeakReference<CreatureObject*> logPlayRef = play;

			Core::getTaskManager()->scheduleTask([logShipRef, logPlayRef] () {
				if (logShipRef == nullptr) {
					return;
				}

				auto zoneServer = logShipRef->getZoneServer();
				if (zoneServer == nullptr) return;

				auto pilot = logPlayRef.get();
				if (pilot != nullptr) {
					auto client = pilot->getClient();
					if (client != nullptr) client->stopPacketLogging();
				}

				int totalPlayers = logShipRef->getTotalPlayersOnBoard();
				for (int i = 0; i < totalPlayers; i++) {
					auto member = logShipRef->getPlayerOnBoard(i);
					if (member == nullptr || member == pilot) continue;
					auto client = member->getClient();
					if (client != nullptr) client->stopPacketLogging();
				}
			}, "StopPacketLoggingDelayed", 12000);
#endif // DEBUG_HYPERSPACE_PACKETS

			return;
		}
		}
	}

#ifdef DEBUG_HYPERSPACE_PACKETS
	void startPacketLoggingForShip(ShipObject* shipObject) {
		auto zoneServer = shipObject->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		// Log for pilot
		auto pilot = play.get();

		if (pilot != nullptr) {
			auto client = pilot->getClient();

			if (client != nullptr) {
				client->startPacketLogging(pilot->getFirstName());
			}
		}

		// Log for all passengers
		int totalPlayers = shipObject->getTotalPlayersOnBoard();

		for (int i = 0; i < totalPlayers; i++) {
			auto member = shipObject->getPlayerOnBoard(i);

			if (member == nullptr || member == pilot) {
				continue;
			}

			auto client = member->getClient();

			if (client != nullptr) {
				client->startPacketLogging(member->getFirstName());
			}
		}
	}

	void stopPacketLoggingForShip(ShipObject* shipObject) {
		auto zoneServer = shipObject->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto pilot = play.get();

		if (pilot != nullptr) {
			auto client = pilot->getClient();

			if (client != nullptr) {
				client->stopPacketLogging();
			}
		}

		int totalPlayers = shipObject->getTotalPlayersOnBoard();

		for (int i = 0; i < totalPlayers; i++) {
			auto member = shipObject->getPlayerOnBoard(i);

			if (member == nullptr || member == pilot) {
				continue;
			}

			auto client = member->getClient();

			if (client != nullptr) {
				client->stopPacketLogging();
			}
		}
	}
#endif // DEBUG_HYPERSPACE_PACKETS
};

#endif // CORE3_HYPERSPACETOLOCATIONTASK_H
