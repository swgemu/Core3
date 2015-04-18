/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDAUTOREPAIRTASK_H_
#define DROIDAUTOREPAIRTASK_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidAutoRepairModuleDataComponent.h"
#include "server/zone/objects/group/GroupObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidAutoRepairTask : public Task {

	ManagedReference<DroidAutoRepairModuleDataComponent*> module;

public:
	DroidAutoRepairTask(DroidAutoRepairModuleDataComponent* module) : Task() {
		this->module = module;
	}

	void run() {

		if( module == NULL || module->getDroidObject() == NULL ){
			return;
		}

		DroidObject* droid = module->getDroidObject();

		Locker locker(droid);

		// Check if module is still active
		if( !module->isActive() ){
			droid->removePendingTask("droid_auto_repair");
			return;
		}

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				droid->removePendingTask("droid_auto_repair");
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			droid->removePendingTask("droid_auto_repair");
			return;
		}


		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_auto_repair");
			return;
		}

		// Heal droid
		healDroid( droid, droid, module->getAutoRepairPower() );

		// Heal all droids in group within 30m
		ManagedReference<GroupObject*> group = droid->getGroup();
		if (group != NULL) {

			for( int i=0; i<group->getGroupSize(); i++){

				SceneObject* member = group->getGroupMember(i);
				if( member != NULL && member->isDroidObject() && member->isInRange(droid, 30.0f) ){

					ManagedReference<DroidObject*> groupedDroid = cast<DroidObject*>(member);
					if( groupedDroid != NULL && groupedDroid != droid){
						Locker dlocker(groupedDroid, droid);
						healDroid( droid, groupedDroid, module->getAutoRepairPower() );
						dlocker.release();
					}
				}
			}
		}

		// Reschedule task
		reschedule( 10000 ); // 10 sec
	}

private:
	void healDroid( DroidObject* healer, DroidObject* droid, int amount ){

		bool droidHealed = false;
		for( int attr = 0; attr <= 8; attr++ ){
			if( droid->hasDamage( attr ) ){
				droid->healDamage( healer, attr, amount, true, true );
				droidHealed = true;
			}
		}

		if( droidHealed ){
			droid->showFlyText("npc_reaction/flytext","repaired", 0, 153, 0); // "*Repaired*"
			droid->playEffect("clienteffect/healing_healdamage.cef", "");
			healer->doAnimation("heal_other");
		}

	}

};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDAUTOREPAIRTASK_H_*/
