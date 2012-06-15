/*
 * AiObserverImplementation.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: da
 */

#include "AiObserver.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "engine/util/Observable.h"
#include "engine/core/ManagedObject.h"
#include "AiActor.h"

int AiObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<AiActor*> actor = cast<AiActor*>(observable);
	if (actor == NULL)
		return 1;

	switch (eventType) {
	case ObserverEventType::OBJECTDESTRUCTION:
		break;
	case ObserverEventType::DAMAGERECEIVED:
		break;
	case ObserverEventType::OBJECTINRANGEMOVED:
		actor->notifyPositionUpdate(cast<QuadTreeEntry*>(arg1));
		break;
	}

	return 0;
}


