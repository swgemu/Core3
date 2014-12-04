#ifndef PETCONTROLDEVICESTOREOBJECTTASK_H_
#define PETCONTROLDEVICESTOREOBJECTTASK_H_

#include "engine/engine.h"

class PetControlDeviceStoreObjectTask : public Task {
	ManagedReference<PetControlDevice*> pet;
	ManagedReference<CreatureObject*> player;
	bool force;
public:
	PetControlDeviceStoreObjectTask(PetControlDevice* pet, CreatureObject* player, bool force) {
		this->pet = pet;
		this->force = force;
		this->player = player;
	}

	void run() {
		ManagedReference<TangibleObject*> controlledObject = pet->getControlledObject();

		if (controlledObject == NULL || !controlledObject->isAiAgent())
			return;

		Locker locker(controlledObject);

		Locker crossLocker(player, controlledObject);

		pet->storeObject(player, force);
	}
};






#endif /* PETCONTROLDEVICESTOREOBJECTTASK_H_ */
