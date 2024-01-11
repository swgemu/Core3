//
// Created by g on 12/20/17.
//

#ifndef CORE3_HYPERSPACETOLOCATIONTASK_H
#define CORE3_HYPERSPACETOLOCATIONTASK_H

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/OrientForHyperspace.h"
#include "server/zone/packets/object/BeginHyperspace.h"
#include "server/zone/packets/object/Hyperspace.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
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

		if (player == nullptr || shipObject == nullptr)
			return;

		if (!shipObject->isHyperspacing()) {
			return;
		}

		int currentIter = iteration++;

		Locker locker(shipObject);

		switch (currentIter) {
		case 0:
			shipObject->sendShipMembersMessage("@space/space_interaction:hyperspace_route_begin");

			reschedule(5000);
			return;
		case 1: // 25%
		case 2: // 50%
		case 3: { // 75%
			String strid = "@space/space_interaction:hyperspace_route_calculation_";

			strid += String::valueOf(currentIter);

			shipObject->sendShipMembersMessage(strid);

			reschedule(5000);
			return;
		}
		case 4: // 100%
			orientShip(shipObject, player);

			reschedule(2000);
			return;
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
		case 9:
			beginHyperspace();

			reschedule(7000);
			return;
		case 10: {
			reschedule(1000);
			return;
		}
		case 11: {
			shipObject->switchZone(zoneName, location.getX() + System::random(100.f), location.getZ() + System::random(100.f), location.getY() + System::random(100.f), 0, false);

			shipObject->setHyperspacing(false);

			// Transport players onboard the ship
			int totalPlayers = shipObject->getTotalPlayersOnBoard();

			for (int i = totalPlayers - 1; i >= 0; --i) {
				auto shipMember = shipObject->getPlayerOnBoard(i);

				if (shipMember != nullptr) {
					try {
						Locker memberLock(shipMember, shipObject);

						shipMember->switchZone(zoneName, location.getX(), location.getZ(), location.getY(), shipMember->getParentID(), false);
					} catch (...) {
						shipMember->error() << "Failed to transport player in hyperspace - ShipID: " << shipObject->getObjectID() << " Player ID: " << player->getObjectID();
					}
				}
			}
		}
		}
	}

	void orientShip(ShipObject* shipObject, CreatureObject* player) {
		if (player == nullptr || shipObject == nullptr)
			return;

		//close s-foils as the ship is orienting if they're still open
		uint32 optionsBitmask = shipObject->getOptionsBitmask();

		if (optionsBitmask & OptionBitmask::WINGS_OPEN)
			shipObject->clearOptionBit(OptionBitmask::WINGS_OPEN);

		OrientForHyperspaceMessage *msg = new OrientForHyperspaceMessage(player->getObjectID(), zoneName, location.getX(), location.getY(), location.getZ());
		player->sendMessage(msg);
	}

	void beginHyperspace() {
		Reference<CreatureObject*> player = play.get();

		if (player == nullptr)
			return;

		BeginHyperspaceMessage *msg = new BeginHyperspaceMessage(player->getObjectID(), zoneName, location.getX(), location.getY(), location.getZ());
		player->sendMessage(msg);
	}
};

#endif // CORE3_HYPERSPACETOLOCATIONTASK_H
