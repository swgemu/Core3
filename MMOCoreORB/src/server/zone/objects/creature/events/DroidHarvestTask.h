/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDHARVESTTASK_H_
#define DROIDHARVESTTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/managers/creature/CreatureManager.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidHarvestTask : public Task {
	Reference<DroidHarvestModuleDataComponent*> module;
	ManagedWeakReference<CreatureObject*> creature;

public:
	DroidHarvestTask(DroidHarvestModuleDataComponent* module, CreatureObject* creo) : Task() {
		this->module = module;
		creature = creo;
	}

	void run() {
		ManagedReference<CreatureObject*> tarCreo = creature.get();

		if (module == nullptr || tarCreo == nullptr) {
			return;
		}

		Reference<DroidObject*> droid = module->getDroidObject();

		if (droid == nullptr) {
			return;
		}

		Locker droidLock(droid);

		ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();

		if (owner == nullptr) {
			return;
		}

		ManagedReference<Creature*> cr = cast<Creature*>(tarCreo->asTangibleObject());

		if (cr == nullptr) {
			return;
		}

		// Droid should be in range now.
		int harvestInterest = module->getHarvestInterest();
		int bonus = module->getHarvestPower();

		// we have all the info we need form the droid for now.
		Locker tpLock(tarCreo, droid);

		Vector<int> types;
		int type = 0;

		if (harvestInterest == DroidHarvestModuleDataComponent::INTEREST_BONE) {
			type = 236;
		}

		if (harvestInterest == DroidHarvestModuleDataComponent::INTEREST_HIDE) {
			type = 235;
		}

		if (harvestInterest == DroidHarvestModuleDataComponent::INTEREST_MEAT) {
			type = 234;
		}

		if ((harvestInterest == DroidHarvestModuleDataComponent::INTEREST_BONE && cr->getBoneType().isEmpty()) ||
			(harvestInterest == DroidHarvestModuleDataComponent::INTEREST_HIDE && cr->getHideType().isEmpty()) ||
			(harvestInterest == DroidHarvestModuleDataComponent::INTEREST_MEAT && cr->getMeatType().isEmpty())) {

			owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
			droid->setFollowObject(owner);
			droid->storeFollowObject();
			return;
		}

		if (harvestInterest == DroidHarvestModuleDataComponent::INTEREST_RANDOM) {
			// pick one at random
			if (!cr->getMeatType().isEmpty()) {
				types.add(234);
			}

			if (!cr->getHideType().isEmpty()) {
				types.add(235);
			}

			if (!cr->getBoneType().isEmpty()) {
				types.add(236);
			}

			if (types.size() > 0)
				type = types.get(System::random(types.size() - 1));
		}

		if (type == 0 || cr->getDnaState() == CreatureManager::DNADEATH) {
			owner->sendSystemMessage("@pet/droid_modules:no_resources_to_harvest");

			droid->setFollowObject(owner);
			droid->storeFollowObject();

			droid->setMovementState(AiAgent::FOLLOWING);

			return;
		}

		Zone* zone = cr->getZone();

		if (zone == nullptr) {
			return;
		}

		ManagedReference<CreatureManager*> creatureManager = zone->getCreatureManager();

		if (creatureManager != nullptr)
			creatureManager->droidHarvest(cr, droid, type,bonus);
	}
};

} // namespace events
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature::events;

#endif /*DROIDHARVESTTASK_H_*/
