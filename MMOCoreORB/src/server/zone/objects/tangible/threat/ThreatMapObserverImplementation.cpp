/*
 * ThreatMapObserverImplementation.cpp
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */


#include "server/zone/objects/tangible/threat/ThreatMapObserver.h"
#include "ThreatMap.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/ObserverEventType.h"

int ThreatMapObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<TangibleObject*> strongRef = self.get();

	if (strongRef == NULL)
		return 1;

	if (eventType != ObserverEventType::HEALINGRECEIVED)
		return 0;

	Reference<CreatureObject*> healTarget = cast<CreatureObject*>(observable);

	if (healTarget == NULL)
		return 0;

	Reference<CreatureObject*> healer = cast<CreatureObject*>(arg1);

	if (healer == NULL)
		return 0;

	Core::getTaskManager()->executeTask([=]{
		Locker locker(strongRef);

		ThreatMap* threatMap = strongRef->getThreatMap();

		if (threatMap != NULL) {
			int targetIndex = threatMap->find(healTarget);
			int healerIndex = threatMap->find(healer);

			if (targetIndex >= 0) {
				ThreatMapEntry& entry = threatMap->get(targetIndex);

				if (entry.getAggroMod() == 0) {
					return;
				}
			} else if (healerIndex < 0) {
				return;
			}

			threatMap->addHeal(healer, arg2);
		}
	}, "updateThreatMapHeal");

	return 0;
}
