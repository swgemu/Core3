
#ifndef STORESHIPTASK_H_
#define STORESHIPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"

class StoreShipTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<ShipControlDevice*> shipDev;

public:
	StoreShipTask(CreatureObject* creo, ShipControlDevice* controlDevice) : play(creo), shipDev(controlDevice) {
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<ShipControlDevice*> shipControlDevice = shipDev.get();

		if (player == nullptr || shipControlDevice == nullptr)
			return;

		shipControlDevice->storeShip(player);
	}
};

#endif /* STORESHIPTASK_H_ */
