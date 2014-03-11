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
	ManagedReference<TangibleObject*> tano;

public:
	RelockLootContainerEvent(TangibleObject* object) {
		tano = object;
		Container *container = cast<Container*> (tano.get());
		if(container)
			container->setRelockingStatus(true);
		else
			tano = NULL;
	}

	void run() {
		// Relocks static loot containers
		if (tano->getGameObjectType() != SceneObjectType::STATICLOOTCONTAINER && !tano->isContainerObject())
			return;

		Container* container = cast<Container*>( tano.get());

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
