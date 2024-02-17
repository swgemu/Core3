/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/objects/tangible/components/LightObserver.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/misc/LightObject.h"

int LightObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	info(true) << "LightObserverImplementation called with event type: " << eventType;

	if (eventType != ObserverEventType::PARENTCHANGED)
		return 1;

	if (observable == nullptr)
		return 1;

	LightObject* lightObject = cast<LightObject*>(observable);

	if (lightObject == nullptr)
		return 1;

	


	return 0;
}
