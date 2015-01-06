/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include "server/zone/objects/tangible/components/droid/DroidPersonalityObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/tangible/components/droid/DroidPersonalityModuleDataComponent.h"

int DroidPersonalityObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	// check params we should have the player around here
	module->notifyEvent(eventType,arg1, arg2);
	return 0;
}
