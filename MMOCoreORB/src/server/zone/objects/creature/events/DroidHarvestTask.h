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

public:
	DroidHarvestTask(DroidHarvestModuleDataComponent* module) : Task() {
		this->module = module;
	}

	void run() {
		// ReVamp: This should always run while the droid is active. auto harvest should just auto add targets to the module.
		// droid command should just add a single target id, and this re-scheduling task should just pick it up.
		if( module == NULL){
			return;
		}

		DroidObject* droid = module->getDroidObject();
		if (droid == NULL) {
			return;
		}
		Locker droidLock(droid);
		droid->removePendingTask( "droid_harvest" );
		ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();
		if (owner == NULL) {
			return;
		}
		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				droid->removePendingTask("droid_harvest");
				return;
			}
		}
		// Droid must have power move to module itself.
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_harvest");
			return;
		}
		if (droid->isDead()) {
			droid->removePendingTask("droid_harvest");
			return;
		}
		// Check droid states, droids cant harvest while in combat

		// droid isnt in combat and has power. it can do a harvest if there are available targets
		if (module->hasMoreTargets()) {
			uint64 droidTarget = module->getNextHarvestTarget();

			if(droid->isIncapacitated()){
				reschedule(1000); // check again in a second
				return;
			}
			if (droid->isInCombat()) {
				reschedule(1000);
				return;
			}

			if (!droid->isInRange(owner,64.0f)) {
				// droid out of range, just re-schedule till we are back in range.
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
			}

			// check for no target
			if (droidTarget == -1) {
				reschedule(1000);
				return;
			}
			// end re-do
			Reference<CreatureObject*> target = droid->getZoneServer()->getObject(droidTarget, true).castTo<CreatureObject*>();
			if (target == NULL) {
				reschedule(1000);
				return;
			}

			Creature* cr = cast<Creature*>(target.get());
			if (cr == NULL) {
				reschedule(1000);
				return;
			}
			if (!target->isInRange(droid,64.0f)) {
				reschedule(1000);
				return;
			}
			if (!target->isInRange(droid,7.0f + target->getTemplateRadius() + droid->getTemplateRadius())) { // this should run the droid to the target for harvesting
				module->addHarvestTarget(droidTarget,true);
				droid->setTargetObject(target);
				droid->storeFollowObject(); // calling store here as a tthe end of a task we reset the follow object
				droid->activateInterrupt(owner,ObserverEventType::STARTCOMBAT);
				reschedule(1000); // wait 5 seconds for the droid to get there before checking again.
				return;
			}
			// droid should be in rnge now.
			int harvestInterest = module->getHarvestInterest();
			int bonus = module->getHarvestPower();
			// we have all the info we need form the droid for now.
			Locker tpLock(target,droid);

			Vector<int> types;
			int type = 0;
			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_BONE) {
				type = 236;
			}

			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_HIDE) {
				type = 235;
			}

			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_MEAT) {
				type = 234;
			}

			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_BONE && cr->getBoneType().isEmpty()) {
				owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
			}

			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_HIDE && cr->getHideType().isEmpty()) {
				owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
			}

			if (harvestInterest == DroidHarvestModuleDataComponent::INTREST_MEAT && cr->getMeatType().isEmpty()) {
				owner->sendSystemMessage("@pet/droid_modules:target_type_not_found");
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
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
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
			}
			if (cr->getDnaState() == CreatureManager::DNADEATH) {
				owner->sendSystemMessage("@pet/droid_modules:no_resources_to_harvest");
				droid->setFollowObject(owner);
				droid->storeFollowObject();
				reschedule(1000);
				return;
			}
			tpLock.release();
			Locker clock(target,droid);

			Zone* zone = cr->getZone();

			if (zone != NULL) {
				ManagedReference<CreatureManager*> manager = zone->getCreatureManager();
				manager->droidHarvest(cr, droid, type,bonus);
			}
			droid->setFollowObject(owner);
			droid->storeFollowObject();
			if (module->hasMoreTargets()) {
				reschedule(10); // we have mroe targets just recheck it
			} else {
				reschedule(1000);
			}
		} else {
			droid->setFollowObject(owner);
			droid->storeFollowObject();
			reschedule(1000); // try again in 1 scond to see if we got targets to harvest
			return;
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
