/*
 * ShuttleTransitEvent.h
 *
 *  Created on: Apr 13, 2011
 *      Author: crush
 */

#ifndef SHUTTLETRANSITEVENT_H_
#define SHUTTLETRANSITEVENT_H_

#include "engine/engine.h"
#include "server/zone/managers/planet/PlanetManager.h"

class ShuttleTransitEvent : public Task {
	ManagedReference<PlanetManager*> planetManager;

public:
	ShuttleTransitEvent(PlanetManager* pman) : Task() {
		planetManager = pman;
	}

	void run() {
		if (planetManager == NULL)
			return;

		planetManager->scheduleShuttleTransit();
	}
};


#endif /* SHUTTLETRANSITEVENT_H_ */
