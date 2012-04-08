/*
 * ThreatMapClearObserversTask.h
 *
 *  Created on: 08/04/2012
 *      Author: victor
 */

#ifndef THREATMAPCLEAROBSERVERSTASK_H_
#define THREATMAPCLEAROBSERVERSTASK_H_

#include "engine/engine.h"
#include "ThreatMap.h"
#include "ThreatMapObserver.h"

class ThreatMapClearObserversTask : public Task {
	ThreatMap threatMap;
	ManagedReference<ThreatMapObserver*> threatMapObserver;

public:
	ThreatMapClearObserversTask(const ThreatMap& map, ThreatMapObserver* obs) : threatMap(map), threatMapObserver(obs) {
	}

	void run() {
		for (int i = 0; i < threatMap.size(); ++i) {
			CreatureObject* creature = threatMap.elementAt(i).getKey();

			if (creature != NULL && threatMapObserver != NULL) {
				Locker clocker(creature);

				creature->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
			}
		}
	}
};


#endif /* THREATMAPCLEAROBSERVERSTASK_H_ */
