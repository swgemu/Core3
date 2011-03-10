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
	}

	void run() {
		// Relocks static loot containers
		if (tano->getGameObjectType() != SceneObject::STATICLOOTCONTAINER && !tano->isContainerObject())
			return;

		Container* container = (Container*) tano.get();

		container->setSliced(false);
		container->setLockedStatus(true);

	}

};

#endif /* RELOCKLOOTCONTAINEREVENT_H_ */
