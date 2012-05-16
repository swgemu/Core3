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
	ManagedReference<ActiveArea*> area;

public:
	RemoveNoSpawnAreaTask(ActiveArea* camp) {
		area = camp;
	}

	void run() {
		if (area == NULL)
			return;

		Locker locker(area);

		area->destroyObjectFromWorld(true);
	}
};




#endif /* REMOVENOSPAWNAREATASK_H_ */
