/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDHARVESTTASK_H_
#define DROIDHARVESTTASK_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/group/GroupObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidHarvestTask : public Task {

	ManagedReference<DroidHarvestModuleDataComponent*> module;
	ManagedReference<CreatureObject* > target;

public:
	DroidHarvestTask(DroidHarvestModuleDataComponent* module, CreatureObject* target) : Task() {
		this->module = module;
		this->target = target;
	}

	void run() {
		System::out << "running harvest task\n";

		if( module == NULL || target == NULL){
			System::out << "Null target\n";
			return;
		}

		DroidObject* droid = module->getDroidObject();

		if (droid == NULL) {
			System::out << "Null droid\n";
			return;
		}
		// are we already running?
		Task* task = droid->getPendingTask( "droid_harvest" );
		if( task != NULL ){
			droid->removePendingTask( "droid_harvest" );
			return;
		}

		Locker droidLock(droid);

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				droid->removePendingTask("droid_harvest");
				System::out << "Null zone\n";

				return;
			}
		}

		// Check droid states, droids cant harvest while in combat
		if( droid->isDead() || droid->isIncapacitated() || droid->isInCombat()){
			droid->removePendingTask("droid_harvest");
			System::out << "droid dead\n";

			return;
		}

		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_harvest");
			System::out << "Null power\n";

			return;
		}

		if (!target->isInRange(droid,7)) { // this should run the droid to the target for harvesting
			droid->setTargetObject(target);
			return;
		}

		int harvestInterest = module->getHarvestInterest();
		int bonus = module->getHarvestPower();
		// we have all the info we need form the droid for now.
		Locker targetLock(target);
		droidLock.release();
		ManagedReference<CreatureObject*> owner = droid->getLinkedCreature();
		Locker tpLock(owner,target);

		if (!target->isDead()){
			// notify owner target is invalid
			owner->sendSystemMessage("@pet/droid_modules:invalid_harvest_target");
			return;
		}
		Creature* cr = cast<Creature*>(target.get());
		Vector<int> types;
		int type = 0;
		if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_BONE && cr->getBoneType().isEmpty()) {
			owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
			return;
		} else {
			type = 236;
		}
		if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_HIDE && cr->getHideType().isEmpty()) {
			owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
			return;
		} else {
			type = 235;
		}
		if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_MEAT && cr->getMeatType().isEmpty()) {
			owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
			return;
		} else {
			type = 234;
		}

		if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_RANDOM) {
			// pick one at random
			if(!cr->getMeatType().isEmpty()) {
				types.add(234);
			}

			if(!cr->getHideType().isEmpty()) {
				types.add(235);
			}

			if(!cr->getBoneType().isEmpty()) {
				types.add(236);
			}
			if(types.size() > 0)
				type = types.get(System::random(types.size() -1));
		}

		if (type == 0) {
			owner->sendSystemMessage("@pet/droid_modules:no_resources_to_harvest");
		}
		if (cr->canHarvestMe(owner)) {

			if (cr->getZone() == NULL)
				return;

			if (cr->getDnaState() == CreatureManager::DNADEATH) {
				owner->sendSystemMessage("@pet/droid_modules:no_resources_to_harvest");
				return;
			}
			System::out << "calling cm target\n";

			tpLock.release();
			Locker dlock(droid);
			Locker clock(target,droid);
			ManagedReference<CreatureManager*> manager = cr->getZone()->getCreatureManager();
			manager->droidHarvest(cr, droid, type,bonus);
			droid->restoreFollowObject();
		}
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDHARVESTTASK_H_*/
