/*
 * LaunchShipTask.h
 */

#ifndef LAUNCHSHIPTASK_H_
#define LAUNCHSHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/events/InsertPilotIntoShipTask.h"
#include "server/zone/objects/ship/events/InsertGroupMemberIntoShipTask.h"
#include "server/zone/managers/planet/PlanetManager.h"

class LaunchShipTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipControlDevice*> shipDev;
	Vector<uint64> groupMembers;

public:
	LaunchShipTask(CreatureObject* creo, ShipControlDevice* controlDevice, Vector<uint64> group) : play(creo), shipDev(controlDevice), groupMembers(group) {
		setLoggingName("LaunchShipTask");
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<ShipControlDevice*> shipControlDevice = shipDev.get();

		if (player == nullptr || shipControlDevice == nullptr)
			return;

		Zone* departureZone = player->getZone();

		if (departureZone == nullptr) {
			return;
		}

		PlanetManager* planetManager = departureZone->getPlanetManager();

		if (planetManager == nullptr) {
			return;
		}

		String jtlZoneName = planetManager->getJtlZoneName();

		if (jtlZoneName == "") {
			return;
		}

		Vector3 randomPosition = Vector3(System::random(200.f), System::random(200.f), System::random(200.f));
		Vector3 launchPosition = planetManager->getJtlLaunchLocations() + randomPosition;

		// Lock the control device
		Locker deviceLock(shipControlDevice);

		// Ship is cross locked to device in the launchShip function
		if (!shipControlDevice->launchShip(player, jtlZoneName, launchPosition)) {
			error() << "Ship failed to launch - Device ID: " << shipControlDevice->getObjectID();
			return;
		}

		auto ship = cast<ShipObject*>(shipControlDevice->getControlledObject());

		if (ship == nullptr || ship->getLocalZone() == nullptr) {
			return;
		}

		// Lock player to store launch point
		Locker pilotLock(player, shipControlDevice);

		shipControlDevice->setStoredLocationData(player);

		pilotLock.release();

		InsertPilotIntoShipTask* pilotTask = new InsertPilotIntoShipTask(player, ship);

		if (pilotTask != nullptr)
			pilotTask->schedule(100);

		if (ship->isPobShipObject() && groupMembers.size() > 0) {
			auto pobShip = ship->asPobShipObject();

			if (pobShip == nullptr)
				return;

			for (int j = 0; j < groupMembers.size(); ++j) {
				auto memberID = groupMembers.get(j);

				// info(true) << "InsertGroupMembertIntoShipTask for member: " << memberID;

				InsertGroupMembertIntoShipTask* memberTask = new InsertGroupMembertIntoShipTask(pobShip, memberID);

				if (memberTask != nullptr)
					memberTask->schedule(200 + (j * 50));
			}
		}
	}
};

#endif /* LAUNCHSHIPTASK_H_ */
