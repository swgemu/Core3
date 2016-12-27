/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VEHICLEDECAYTASK_H_
#define VEHICLEDECAYTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"
#include "templates/creature/VehicleObjectTemplate.h"

class VehicleDecayTask : public Task {
	ManagedWeakReference<TangibleObject*> vehicleObj;
	bool initialDecay;

public:
	VehicleDecayTask(TangibleObject* veh) : Task() {
		vehicleObj = veh;
		initialDecay = true;
	}

	void run() {
		ManagedReference<TangibleObject*> vehicle = vehicleObj.get();

		if (vehicle == NULL)
			return;

		Reference<VehicleObjectTemplate*> vehicleTemplate = cast<VehicleObjectTemplate*>(vehicle->getObjectTemplate());

		if (vehicleTemplate == NULL)
			return;

		Locker locker(vehicle);

		vehicle->removePendingTask("decay");

		int decayCycle = vehicleTemplate->getDecayCycle();

		if (decayCycle == 0)
			decayCycle = 600;

		int decayRate = vehicleTemplate->getDecayRate();

		if (decayRate == 0)
			decayRate = 15;

		if (initialDecay) {
			vehicle->inflictDamage(vehicle, 0, decayRate / 2, true);
			initialDecay = false;
		} else {
			vehicle->inflictDamage(vehicle, 0, decayRate, true);
		}

		vehicle->addPendingTask("decay", this, decayCycle * 1000);
	}
};

#endif /*VEHICLEDECAYTASK_H_*/
