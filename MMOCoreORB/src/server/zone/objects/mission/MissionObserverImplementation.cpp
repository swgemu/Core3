/*
 * MissionObserverImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "server/zone/objects/mission/MissionObserver.h"
#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/object/ObjectManager.h"

int MissionObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<MissionObjective*> objective = missionObjective.get();

	if (objective == NULL)
		return 1;
	else
		return objective->notifyObserverEvent(_this.getReferenceUnsafeStaticCast(), eventType, observable, arg1, arg2);
}

void MissionObserverImplementation::destroyObjectFromDatabase() {
	ObjectManager::instance()->destroyObjectFromDatabase(_this.getReferenceUnsafeStaticCast()->_getObjectID());
}
