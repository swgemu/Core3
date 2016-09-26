/*
 * RemoveNoSpawnAreaTask.h
 *
 *  Created on: 16/05/2012
 *      Author: victor
 */

#ifndef REMOVENOSPAWNAREATASK_H_
#define REMOVENOSPAWNAREATASK_H_

#include "engine/engine.h"
#include "server/zone/objects/area/ActiveArea.h"

class RemoveNoSpawnAreaTask : public Task {
	ManagedWeakReference<ActiveArea*> area;

public:
	RemoveNoSpawnAreaTask(ActiveArea* camp) {
		area = camp;
	}

	void run() {
		ManagedReference<ActiveArea*> strongArea = area.get();

		if (strongArea == NULL)
			return;

		ZoneServer* zoneServer = strongArea->getZoneServer();

		if (zoneServer == NULL || zoneServer->isServerShuttingDown())
			return;

		Locker locker(strongArea);

		strongArea->destroyObjectFromWorld(true);
	}
};




#endif /* REMOVENOSPAWNAREATASK_H_ */
