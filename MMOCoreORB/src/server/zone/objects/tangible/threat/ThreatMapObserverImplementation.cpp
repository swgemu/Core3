/*
 * ThreatMapObserverImplementation.cpp
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */


#include "ThreatMapObserver.h"
#include "ThreatMap.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"

int ThreatMapObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<TangibleObject*> strongRef = self.get();

	if (eventType != ObserverEventType::HEALINGPERFORMED || strongRef == NULL) {
		return 1;
	}

	ThreatMap* threatMap = strongRef->getThreatMap();

	if (threatMap != NULL) {
		CreatureObject* target = cast<CreatureObject*>(arg1);

		if (target != NULL)
			threatMap->addHeal(target, arg2);
	}

	return 1;
}
