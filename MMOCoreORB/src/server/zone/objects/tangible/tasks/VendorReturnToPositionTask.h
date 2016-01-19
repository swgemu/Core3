/*
 * VendorReturnToPositionTask.h
 *
 *  Created on: 1/22/2012
 *      Author: Kyle
 */

#ifndef VENDORRETURNTOPOSITIONTASK_H_
#define VENDORRETURNTOPOSITIONTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class VendorReturnToPositionTask : public Task {
	WeakReference<CreatureObject*> vendor;
	float heading;
public:
	VendorReturnToPositionTask(CreatureObject* cr, int va) {
		vendor = cr;
		heading = va;
	}

	void run() {

		ManagedReference<CreatureObject*> strongref = vendor.get();

		if(strongref == NULL)
			return;

		Locker locker(strongref);
		strongref->updateDirection(Math::deg2rad(heading));

		strongref->removePendingTask("vendorreturn");
	}
};

#endif /* VENDORRETURNTOPOSITIONTASK_H_ */
