/*
 * ThreatMapClearObserversTask.h
 *
 *  Created on: 08/04/2012
 *      Author: victor
 */

#ifndef THREATMAPCLEAROBSERVERSTASK_H_
#define THREATMAPCLEAROBSERVERSTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/objects/tangible/threat/ThreatMapObserver.h"

class ThreatMapClearObserversTask : public Task {
	ThreatMap threatMap;
	ManagedReference<ThreatMapObserver*> threatMapObserver;

public:
	ThreatMapClearObserversTask(const ThreatMap& map, ThreatMapObserver* obs) : threatMap(map), threatMapObserver(obs) {
	}

	void run() {
		while (threatMap.size() > 0) {
			CreatureObject* creature = threatMap.elementAt(0).getKey();

			if (creature != NULL && threatMapObserver != NULL) {
				Locker clocker(creature);

				creature->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
			}

			threatMap.remove(0);
		}

	}
};


#endif /* THREATMAPCLEAROBSERVERSTASK_H_ */
