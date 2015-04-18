/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDMERCHANTBARKERTASK_H_
#define DROIDMERCHANTBARKERTASK_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidMerchantModuleDataComponent.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidMerchantBarkerTask : public Task, public Logger {

	ManagedReference<DroidMerchantModuleDataComponent*> module;

public:
	DroidMerchantBarkerTask(DroidMerchantModuleDataComponent* module) : Task() {
		this->module = module;
	}

	void run() {

		if( module == NULL) {
			return;
		}

		ManagedReference<DroidObject*> droid = module->getDroidObject();

		if (droid == NULL) {
			return;
		}

		Locker locker(droid);
		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				droid->removePendingTask("barking");
				module->deactivate();
				return;
			}
		}
		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("barking");
			return;
		}

		// Check if module is still active
		if( !module->isActive() ){
			droid->removePendingTask("barking");
			return;
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			droid->removePendingTask("barking");
			module->deactivate();
			return;
		}
		String message = module->getMessage();
		if (message.length() == 0) {
			module->deactivate();
		}
		// Get nearby people and bark
		CloseObjectsVector* vec = (CloseObjectsVector*) droid->getCloseObjects();
		SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);
		if (vec != NULL) {
			vec->safeCopyTo(closeEntryObjects);
		} else {
			droid->info("Null closeobjects vector in DroidMerchantBarkerTask::run()", true);
			droid->getZone()->getInRangeObjects(droid->getWorldPositionX(), droid->getWorldPositionX(), 192, &closeEntryObjects, true);
		}
		bool speak = false;
		for (int i = 0; i < closeEntryObjects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());
			if (object->isPlayerCreature() && object->isInRange(droid,15)) {
				speak = true;
				break;
			}
		}
		if (speak) {
			droid->getZoneServer()->getChatManager()->broadcastMessage(droid,message,0,0,0);
		}
		droid->addPendingTask("barking",this,60000); // wait a mintue to bark again
	}

};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDEFFECTSTASK_H_*/
