/*
 * SpaceZoneLoadManagersTask.h
 *
 *  Created on: Nov 18, 2010
 *      Author: oru
 */

#ifndef SPACEZONELOADMANAGERSTASK_H_
#define SPACEZONELOADMANAGERSTASK_H_

#include "engine/engine.h"

#include "server/zone/SpaceZone.h"

class SpaceZoneLoadManagersTask : public Task {
	ManagedReference<ZoneServer*> zoneServer;
	ManagedReference<SpaceZone*> zone;
public:
	SpaceZoneLoadManagersTask(ZoneServer* server, SpaceZone* zone) {
		this->zone = zone;
		zoneServer = server;
	}

	void run() {
		if (zone == nullptr)
			return;

		if (zone->hasManagersStarted())
			return;

		zone->startManagers();
	}
};


#endif /* ZONELOADMANAGERSTASK_H_ */
