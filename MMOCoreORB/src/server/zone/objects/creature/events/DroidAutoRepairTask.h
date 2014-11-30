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
