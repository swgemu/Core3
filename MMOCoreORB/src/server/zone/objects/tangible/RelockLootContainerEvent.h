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
		if (container != NULL)
			container->setRelockingStatus(true);
		else
			tano = NULL;

	}

	void run() {

		// Relocks static loot containers
		if (!tano)
			return;
		if (tano->getGameObjectType() != SceneObjectType::STATICLOOTCONTAINER
				&& !tano->isContainerObject())
			return;

		Container* container = cast<Container*> (tano.get());
		container->setRelockingStatus(false);

		container->setSliced(false);

		if ((System::random(100)) < container->getLockChance()) {
			container->setSliceable(true);
			container->setLockedStatus(true);
		} else {
			container->setSliceable(false);
			container->setLockedStatus(false);
		}

	}

};

#endif /* RELOCKLOOTCONTAINEREVENT_H_ */
