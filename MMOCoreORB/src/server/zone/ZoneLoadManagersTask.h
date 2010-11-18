/*
 * ZoneLoadManagersTask.h
 *
 *  Created on: Nov 18, 2010
 *      Author: oru
 */

#ifndef ZONELOADMANAGERSTASK_H_
#define ZONELOADMANAGERSTASK_H_

#include "engine/engine.h"

#include "Zone.h"

class ZoneLoadManagersTask : public Task {
	ManagedReference<Zone*> zone;
public:
	ZoneLoadManagersTask(Zone* zone) {
		this->zone = zone;
	}

	void run() {
		if (zone == NULL)
			return;

		if (zone->hasManagersStarted())
			return;

		zone->startManagers();
	}
};


#endif /* ZONELOADMANAGERSTASK_H_ */
