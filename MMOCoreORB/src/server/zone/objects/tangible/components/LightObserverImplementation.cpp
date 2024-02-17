/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/objects/tangible/components/LightObserver.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/misc/LightObject.h"

int LightObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::PARENTCHANGED)
		return 1;

	if (observable == nullptr)
		return 1;

	LightObject* lightObject = cast<LightObject*>(observable);

	if (lightObject == nullptr)
		return 1;

	Locker lock(lightObject);

	lightObject->updateLifespan();

	// Check if light has passed its lifespawn
	if (!lightObject->lifespanIsPast()) {
		return 0;
	}

	// Candle or lamp has decayed, change template to non lit version
	lightObject->updateTemplate();

	return 1;
}
