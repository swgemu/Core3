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
#include "../events/NotifyDisappearEvent.h"
#include "../events/NotifyInsertEvent.h"
#include "../events/NotifyMovementEvent.h"

int AiObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<AiActor*> actor = cast<AiActor*>(observable);
	if (actor == NULL)
		return 1;

	ManagedReference<QuadTreeEntry*> entry = cast<QuadTreeEntry*>(arg1);
	if (entry == NULL)
		return 1;

	ManagedReference<Task*> task;

	switch (eventType) {
	case ObserverEventType::OBJECTDESTRUCTION:
		break;
	case ObserverEventType::DAMAGERECEIVED:
		break;
	case ObserverEventType::OBJECTINRANGEMOVED:
		task = new NotifyMovementEvent(actor, entry);
		break;
	case ObserverEventType::OBJECTINSERTED:
		task = new NotifyInsertEvent(actor, entry);
		break;
	case ObserverEventType::OBJECTDISAPPEARED:
		task = new NotifyDisappearEvent(actor, entry);
		break;
	}

	task->execute();

	return 0;
}


