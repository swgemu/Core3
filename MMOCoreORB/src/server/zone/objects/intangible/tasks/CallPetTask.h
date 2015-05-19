
#ifndef CALLPETTASK_H_
#define CALLPETTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"

class CallPetTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<PetControlDevice*> device;
	String taskName;

public:
	CallPetTask(PetControlDevice* controlDevice, CreatureObject* creo, const String& task) {
		player = creo;
		device = controlDevice;
		taskName = task;
	}

	void run() {

		Locker locker(player);

		player->removePendingTask("call_pet");

		if(player->isInCombat())
			return;

		Locker locker2(device);
		Locker clocker(device->getControlledObject(), player);
		device->spawnObject(player);
	}
};

#endif /* CALLPETTASK_H_ */
