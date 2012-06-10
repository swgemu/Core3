/*
 * RevokePaidAccessTask.h
 *
 *  Created on: June 2, 2012
 *      Author: Kyle
 */

#ifndef REVOKEPAIDACCESSTASK_H_
#define REVOKEPAIDACCESSTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "engine/engine.h"

class RevokePaidAccessTask : public Task {
	ManagedWeakReference<BuildingObject*> building;
public:
	RevokePaidAccessTask(BuildingObject* build) : Task() {
		building = build;
	}

	void run() {

		ManagedReference<BuildingObject*> strongRef = building;

		if (strongRef == NULL) {
			return;
		}

		Locker _lock(strongRef);
		strongRef->updatePaidAccessList();
	}
};

#endif /* REVOKEPAIDACCESSTASK_H_ */
