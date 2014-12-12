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

#ifndef DROIDTRAPTASK_H_
#define DROIDTRAPTASK_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidStimpackTask : public Task {

	ManagedReference<DroidObject*> droid;
	ManagedReference<CreatureObject*> target;
	String droidName;

public:
	DroidStimpackTask(DroidObject* droid, CreatureObject* player,String droidName) : Task() {
		this->droid = droid;
		this->target = player;
		this->droidName = droidName;
	}

	void run() {
		Locker lock(droid);
		Locker crosslocker(target,droid);

		droid->removePendingTask("droid_request_stimpack");
		if( droid == NULL){
			return;
		}

		DroidTrapModuleDataComponent* module = cast<DroidTrapModuleDataComponent*>(droid->getModule("trap_module"));
		if(module == NULL) {
			target->sendSystemMessage("@pet/droid_modules:not_stimpack_droid");
			return;
		}
		DroidComponent* droidComponent = cast<DroidComponent*>(module->getParent());

		if(droidComponent == NULL) {
			target->sendSystemMessage("@pet/droid_modules:stimpack_error");
			return;
		}

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() || target->isDead()){
			return;
		}

		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return;
		}

		// target must be in range
		if (!target->isInRange(droid,64)){
			// 64 meter range for trap target
			target->sendSystemMessage("@pet/droid_modules:stimpack_too_far_away");
			return;
		}

		// check droid cooldown on dispensing
		if (droid->getCooldownTimerMap()->isPast("DroidTrap")) {
			// use the stim pack
			droid->getCooldownTimerMap()->updateToCurrentAndAddMili("DroidTrap",5000); // 5 sec cooldown on droid traps
			droid->usePower(1);
			return;
		} else {
			target->sendSystemMessage("@pet/droid_modules:stimpack_not_ready");
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

#endif /*DROIDTRAPTASK_H_*/
