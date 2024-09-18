/*
 * InsertGroupMembertIntoShipTask.h
 */

#ifndef INSERTGROUPMEMBERINTOSHIPTASK_H_
#define INSERTGROUPMEMBERINTOSHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/ship/MultiPassengerShipObject.h"
#include "server/zone/SpaceZone.h"

class InsertGroupMembertIntoShipTask : public Task, public Logger {
	ManagedWeakReference<ShipObject*> shipObj;
	uint64 memberID;
	int playerArrangement;

public:
	InsertGroupMembertIntoShipTask(ShipObject* shipObj, uint64 memID, int arrangement) : shipObj(shipObj), memberID(memID), playerArrangement(arrangement) {
		setLoggingName("InsertPlayerToShipTask");
	}

	void run() {
		auto ship = shipObj.get();

		if (ship == nullptr)
			return;

		auto spaceZone = ship->getZone();

		if (spaceZone == nullptr) {
			return;
		}

		auto zoneServer = ship->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto memberObject = zoneServer->getObject(memberID).get();

		if (memberObject == nullptr || !memberObject->isPlayerCreature()) {
			return;
		}

		auto groupMember = memberObject->asCreatureObject();

		if (groupMember == nullptr) {
			return;
		}

		Locker lock(ship);

		if (ship->isPobShip()) {
			auto pobShip = ship->asPobShip();

			if (pobShip == nullptr) {
				return;
			}

			String randomCell = pobShip->getRandomLaunchCell();

			if (randomCell.isEmpty()) {
				return;
			}

			Vector3 launchLoc(pobShip->getLaunchPointInCell(randomCell));
			auto cell = pobShip->getCell(randomCell);

			if (cell == nullptr) {
				return;
			}

			Locker clock(groupMember, ship);

			groupMember->setState(CreatureState::SHIPINTERIOR);

			// info(true) << endl << endl << endl << "Inserting Group Member into POB ship - " << groupMember->getDisplayedName() << " Into Cell: " << randomCell << " Launch Location: " << launchLoc << " Player Arrangement: " << playerArrangement;

			groupMember->switchZone(spaceZone->getZoneName(), launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), cell->getObjectID(), false, playerArrangement);
		} else {
			Locker clock(groupMember, ship);

			groupMember->setState(CreatureState::SHIPGUNNER);

			// info(true) << "Inserting Group Member into MultiPassenger ship - " << groupMember->getDisplayedName();

			groupMember->switchZone(spaceZone->getZoneName(), ship->getWorldPositionX(), ship->getWorldPositionZ(), ship->getWorldPositionY(), ship->getObjectID(), false, playerArrangement);

			ship->addPlayerOnBoard(groupMember);
		}
	}
};

#endif /* INSERTGROUPMEMBERINTOSHIPTASK_H_ */
