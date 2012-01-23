/*
 * CallMountTask.h
 *
 *  Created on: 1/22/2012
 *      Author: kyle
 */

#ifndef CALLMOUNTTASK_H_
#define CALLMOUNTTASK_H_

#include "../../creature/CreatureObject.h"
#include "../ControlDevice.h"

class CallMountTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<VehicleControlDevice*> device;
	String taskName;

public:
	CallMountTask(VehicleControlDevice* controlDevice, CreatureObject* creo, const String& task) {
		player = creo;
		device = controlDevice;
		taskName = task;
	}

	void run() {

		player->removePendingTask("call_mount");

		if(player->isInCombat())
			return;

		Locker clocker(device->getControlledObject(), player);
		device->spawnObject(player);
	}
};

#endif /* CALLMOUNTTASK_H_ */
