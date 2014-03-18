/*
 * RelockLootContainer.h
 *
 *  Created on: Mar 10, 2011
 *      Author: polonel
 */

#ifndef RELOCKLOOTCONTAINEREVENT_H_
#define RELOCKLOOTCONTAINEREVENT_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/Container.h"

class RelockLootContainerEvent: public Task {
	ManagedReference<Container*> container;

public:
	RelockLootContainerEvent(Container* object) {
		
		container = object;
		container->setRelockingStatus(true);
		
	}

	void run() {

        Locker locker(container);

		container->setSliced(false);
		container->setRelockingStatus(false);

		if ((System::random(100)) < container->getLockChance()) {
			container->setSliceable(true);
			container->setLockedStatus(true);
		}
		else
		{
			container->setLockedStatus(false);
			container->setSliceable(false);
		}

	}

};

#endif /* RELOCKLOOTCONTAINEREVENT_H_ */
