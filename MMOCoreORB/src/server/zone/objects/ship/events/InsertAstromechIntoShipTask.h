/*
 * InsertAstromechIntoShipTask.h
 */

#ifndef INSERTASTROMECHINTOSHIPTASK_H_
#define INSERTASTROMECHINTOSHIPTASK_H_

#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreTask.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/SpaceZone.h"

class InsertAstromechIntoShipTask : public Task, public Logger {
	ManagedWeakReference<ShipObject*> shipObj;

public:
	InsertAstromechIntoShipTask(ShipObject* shipObj) : shipObj(shipObj) {
		setLoggingName("InsertPlayerToShipTask");
	}

	void run() {
		auto ship = shipObj.get();

		if (ship == nullptr || !ship->hasSlotDescriptor("ship_droid")) {
			return;
		}

		auto player = ship->getOwner().get();

		if (player == nullptr) {
			return;
		}

		auto shipZone = ship->getLocalZone();

		if (shipZone == nullptr) {
			return;
		}

		auto zoneServer = ship->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> droidControlDeviceRef = zoneServer->getObject(ship->getShipDroidID());

		if (droidControlDeviceRef == nullptr || !droidControlDeviceRef->isControlDevice()) {
			return;
		}

		auto droidControlDevice = dynamic_cast<PetControlDevice*>(droidControlDeviceRef.get());

		if (droidControlDevice == nullptr)
			return;

		auto droidObject = dynamic_cast<DroidObject*>(droidControlDevice->getControlledObject());

		if (droidObject == nullptr) {
			return;
		}

		Locker sLock(ship);
		Locker cLock(droidObject, ship);

		droidObject->setMovementCounter(0);
		droidObject->setDirection(1,0,0,0);
		droidObject->switchZone(shipZone->getZoneName(), 0,0,0, ship->getObjectID(), false, PlayerArrangement::RIDER);
	}
};

#endif /* INSERTASTROMECHINTOSHIPTASK_H_ */
