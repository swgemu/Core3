/*
 * MissionObserverImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "MissionObserver.h"
#include "MissionObjective.h"
#include "server/zone/managers/object/ObjectManager.h"

int MissionObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	return missionObjective->notifyObserverEvent(_this, eventType, observable, arg1, arg2);
}

void MissionObserverImplementation::destroyObjectFromDatabase() {
	ObjectManager::instance()->destroyObjectFromDatabase(_this->_getObjectID());
}
