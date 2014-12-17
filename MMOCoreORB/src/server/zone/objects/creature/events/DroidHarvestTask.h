/*
Copyright (C) 2014 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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
