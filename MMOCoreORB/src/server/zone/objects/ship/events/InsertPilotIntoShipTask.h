/*
 * InsertPilotIntoShipTask.h
 */

#ifndef INSERTPILOTINTOSHIPTASK_H_
#define INSERTPILOTINTOSHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class InsertPilotIntoShipTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipObject*> shipObject;

public:
	InsertPilotIntoShipTask(CreatureObject* creo, ShipObject* shipObj) : play(creo), shipObject(shipObj) {
		setLoggingName("InsertPlayerToShipTask");
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<ShipObject*> ship = shipObject.get();

		if (player == nullptr || ship == nullptr)
			return;

		auto spaceZone = ship->getZone();

		if (spaceZone == nullptr || !spaceZone->isSpaceZone()) {
			return;
		}

		Locker lock(ship);

		Locker clock(player, ship);

		if (player->isGrouped()) {
			auto group = player->getGroup();

			if (group == nullptr)
				return;

			Locker glocker(group, ship);

			group->updateMemberShip(player, ship);
		}

		// Force the pilots position to update in space zone
		auto ghost = player->getPlayerObject();

		if (ghost != nullptr)
			ghost->setForcedTransform(true);

		if (ship->isPobShipObject()) {
			auto pilotChair = ship->getPilotChair().get();

			if (pilotChair == nullptr) {
				return;
			}

			// Always apply the interior state
			player->setState(CreatureState::PILOTINGPOBSHIP);

			// set pob pilot to the same direction as the chair
			player->setDirection(*pilotChair->getDirection());

			Vector3 chairLocation = pilotChair->getPosition();

			player->switchZone(spaceZone->getZoneName(), chairLocation.getX(), chairLocation.getZ() + 0.5, chairLocation.getY(), pilotChair->getObjectID());
		} else {
			player->setState(CreatureState::PILOTINGSHIP);

			// Set the pilots direction to the same as the ship
			player->setDirection(*ship->getDirection());

			player->switchZone(spaceZone->getZoneName(), ship->getPositionX(), ship->getPositionZ(), ship->getPositionY(), ship->getObjectID());
		}
	}
};

#endif /* INSERTPILOTINTOSHIPTASK_H_ */
