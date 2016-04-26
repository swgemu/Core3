/*
 * RankMaintenanceEvent.h
 *
 *  Created on: December 12, 2013
 *      Author: Dreadlow
 */

#ifndef RANKMAINTENANCEEVENT_H_
#define RANKMAINTENANCEEVENT_H_

#include "server/zone/managers/frs/FrsManager.h"

class RankMaintenanceEvent: public Task {
	ZoneServer* zoneServer;
	int interval;

public:
	RankMaintenanceEvent(ZoneServer* serv, int inter) {
		zoneServer = serv;
		interval = inter;
	}

	void run() {
		FrsManager* frsManager = zoneServer->getFrsManager();
		frsManager->processRankMaintenance();
		reschedule(interval);
	}
};

#endif /* RANKMAINTENANCEEVENT_H_ */
