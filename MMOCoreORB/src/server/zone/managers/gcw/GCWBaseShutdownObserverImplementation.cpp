/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/GCWBaseShutdownObserver.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureObject.h"

int GCWBaseShutdownObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(observable);

	if (player == NULL) {
		return 1;
	}

	if (eventType == ObserverEventType::PARENTCHANGED) {
		if (player->getParentID() == 0) {
			player->sendSystemMessage("@hq:vulnerability_reset_no_longer_in_structure"); // You don't appear to be in the structure any longer. Aborting structure shutdown.
		} else {
			player->sendSystemMessage("@hq:vulnerability_reset_wrong_cell"); // You don't appear to be in the same cell you were in when you requested the facility shutdown. You need to be, in order to successfully shut down the facility. Aborting Facility Shutdown.
		}

		player->removePendingTask("base_shutdown");

		player->dropObserver(ObserverEventType::OBJECTDESTRUCTION, _this.getReferenceUnsafeStaticCast());

		return 1;

	} else if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		player->sendSystemMessage("@hq:vulnerability_reset_not_alive"); // 	You appear to be either incapacitated or dead. Aborting structure shutdown.

		player->removePendingTask("base_shutdown");

		player->dropObserver(ObserverEventType::PARENTCHANGED, _this.getReferenceUnsafeStaticCast());

		return 1;
	}

	return 0;
}
