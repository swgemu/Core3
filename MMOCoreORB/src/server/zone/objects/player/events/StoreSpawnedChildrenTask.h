
#ifndef STORESPAWNEDCHILDRENTASK_H_
#define STORESPAWNEDCHILDRENTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreTask.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"

class StoreSpawnedChildrenTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	Vector<ManagedReference<ControlDevice*>> devices;

public:
	StoreSpawnedChildrenTask(CreatureObject* creo, Vector<ManagedReference<ControlDevice*>>&& dev) : play(creo), devices(std::move(dev)) {
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();

		if (player == nullptr)
			return;

		Locker locker(player);

		for (int i = 0; i < devices.size(); ++i) {
			ManagedReference<ControlDevice*> controlDevice = devices.get(i).get();

			if (controlDevice == nullptr)
				continue;

			if (controlDevice->isPetControlDevice()) {
				CreatureObject* pet = cast<CreatureObject*>(controlDevice->getControlledObject());

				if (pet == nullptr)
					continue;

				Locker clocker(pet, player);

				PetControlDeviceStoreTask* storeTask = new PetControlDeviceStoreTask(controlDevice.castTo<PetControlDevice*>(), player, true);

				if (storeTask != nullptr)
					storeTask->execute();
			} else if (controlDevice->isShipControlDevice()) {
				auto ghost = player->getPlayerObject();

				if (ghost == nullptr)
					continue;

				auto shipDevice = controlDevice.castTo<ShipControlDevice*>();

				if (shipDevice == nullptr || !shipDevice->isShipLaunched())
					continue;

				StoreShipTask* storeTask = new StoreShipTask(player, shipDevice, ghost->getSpaceLaunchZone(), ghost->getSpaceLaunchLocation());

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
