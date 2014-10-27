
#ifndef PETINCAPACITATIONRECOVERTASK_H_
#define PETINCAPACITATIONRECOVERTASK_H_

#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class PetIncapacitationRecoverTask : public Task {
	ManagedReference<AiAgent*> pet;
	bool autostore;

public:
	PetIncapacitationRecoverTask(AiAgent* pl, bool store) : Task() {
		pet = pl;
		autostore = store;
	}

	~PetIncapacitationRecoverTask() {

	}

	void run() {
		try {
			Locker petLocker(pet);

			pet->removePendingTask("incapacitationRecovery");

			if (!pet->isIncapacitated())
				return;

			int health = pet->getHAM(CreatureAttribute::HEALTH);

			if (health < 0)
				pet->setHAM(CreatureAttribute::HEALTH, 1);

			int action = pet->getHAM(CreatureAttribute::ACTION);

			if (action < 0)
				pet->setHAM(CreatureAttribute::ACTION, 1);

			int mind = pet->getHAM(CreatureAttribute::MIND);

			if (mind < 0)
				pet->setHAM(CreatureAttribute::MIND, 1);

			pet->setPosture(CreaturePosture::UPRIGHT);

			CreatureObject* owner = pet->getLinkedCreature().get();

			if (owner != NULL) {
				pet->setFollowObject(owner);
				pet->activateMovementEvent();
			}

			if (autostore) {
				PetControlDevice* device = pet->getControlDevice().get().castTo<PetControlDevice*>();

				if (device != NULL && owner != NULL) {
					Locker clocker(owner, pet);

					device->storeObject(owner, true);
				}
			}

		} catch (Exception& e) {

		}
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* PETINCAPACITATIONRECOVERTASK_H_ */
