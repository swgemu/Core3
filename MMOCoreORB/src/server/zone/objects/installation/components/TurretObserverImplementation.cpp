/*
 * TurretObserverImplementation.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */
#include "server/zone/objects/installation/components/TurretObserver.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/DestroyFactionInstallationTask.h"
#include "server/zone/objects/installation/InstallationObject.h"


int TurretObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if(eventType == ObserverEventType::OBJECTDESTRUCTION){
		ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(observable);

		if(installation != NULL){
			DestroyFactionInstallationTask* task = new DestroyFactionInstallationTask(installation);
			task->execute();
		}

		return 1;
	}

	return 0;
}






