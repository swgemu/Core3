/*
 * TurretObserverImplementation.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */
#include "TurretObserver.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/Zone.h"

int TurretObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if(eventType == ObserverEventType::OBJECTDESTRUCTION){
		ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(observable);
		if(installation != NULL){
			Zone* zone = installation->getZone();

			if(zone == NULL)
				return 1;

			GCWManager* gcwMan = zone->getGCWManager();

			if(gcwMan == NULL)
				return 1;

			zone->getGCWManager()->notifyTurretDestruction(installation);
		}
	}

	return 0;

}






