/*
 * ThreatMapObserverImplementation.cpp
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */


#include "server/zone/objects/tangible/threat/ThreatMapObserver.h"
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
		CreatureObject* originator = cast<CreatureObject*>(observable);

		if (originator == NULL )
			return 1;

		int findIndex = threatMap->find(originator);

		if (findIndex >= 0) {
			ThreatMapEntry& entry = threatMap->get(findIndex);

			if (entry.getTotalDamage() == entry.getNonAggroDamage())
				return 1;

		} else {
			return 1;
		}

		CreatureObject* target = cast<CreatureObject*>(arg1);
		if (target != NULL)
			threatMap->addHeal(target, arg2);
	}

	return 1;
}
