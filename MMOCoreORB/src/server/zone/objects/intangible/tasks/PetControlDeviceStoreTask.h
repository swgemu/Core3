#ifndef PETCONTROLDEVICESTORETASK_H_
#define PETCONTROLDEVICESTORETASK_H_

#include "engine/engine.h"

class PetControlDeviceStoreTask : public Task {
	ManagedWeakReference<PetControlDevice*> device;
	ManagedWeakReference<CreatureObject*> playerCreo;
	bool force;

public:
	PetControlDeviceStoreTask(PetControlDevice* device, CreatureObject* playerCreo, bool force) {
		this->device = device;
		this->force = force;
		this->playerCreo = playerCreo;
	}

	void run() {
		auto petDevice = device.get();
		auto player = playerCreo.get();

		if (petDevice == nullptr || player == nullptr)
			return;

		ManagedReference<TangibleObject*> controlledObject = petDevice->getControlledObject();

		if (controlledObject == nullptr || !controlledObject->isAiAgent())
			return;

		Locker lock(petDevice);

		petDevice->storeObject(player, force);
	}
};

#endif /* PETCONTROLDEVICESTORETASK_H_ */
