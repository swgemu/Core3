#ifndef STOREOBJECTTASK_H_
#define STOREOBJECTTASK_H_

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
		Locker locker(pet);

		Locker crossLocker(player, pet);

		pet->storeObject(player, force);
	}
};






#endif /* STOREOBJECTTASK_H_ */
