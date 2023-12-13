
#ifndef STORESPAWNEDCHILDRENTASK_H_
#define STORESPAWNEDCHILDRENTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreTask.h"

class StoreSpawnedChildrenTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	Vector<ManagedReference<CreatureObject*>> children;

public:
	StoreSpawnedChildrenTask(CreatureObject* creo, Vector<ManagedReference<CreatureObject*>>&& ch) : play(creo), children(std::move(ch)) {
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();

		if (player == nullptr)
			return;

		Locker locker(player);

		for (int i = 0; i < children.size(); ++i) {
			CreatureObject* child = children.get(i);

			if (child == nullptr)
				continue;

			Locker clocker(child, player);

			ManagedReference<ControlDevice*> controlDevice = child->getControlDevice().get();

			if (controlDevice == nullptr)
				continue;

			if (controlDevice->isPetControlDevice()) {
				PetControlDeviceStoreTask* storeTask = new PetControlDeviceStoreTask(controlDevice.castTo<PetControlDevice*>(), player, true);

				if (storeTask != nullptr)
					storeTask->execute();
			} else {
				Locker deviceLocker(controlDevice);
				controlDevice->storeObject(player, true);
			}
		}
	}
};

#endif /* STORESPAWNEDCHILDRENTASK_H_ */
