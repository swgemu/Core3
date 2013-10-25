
#ifndef CALLDROIDTASK_H_
#define CALLDROIDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"

class CallDroidTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<DroidControlDevice*> device;
	String taskName;

public:
	CallDroidTask(DroidControlDevice* controlDevice, CreatureObject* creo, const String& task) {
		player = creo;
		device = controlDevice;
		taskName = task;
	}

	void run() {

		Locker locker(player);

		player->removePendingTask("call_droid");

		if(player->isInCombat())
			return;

		Locker clocker(device->getControlledObject(), player);
		device->spawnObject(player);
	}
};

#endif /* CALLDROIDTASK_H_ */
