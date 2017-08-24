/*
 * DespawnLairOnPlayerDisappear.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DESPAWNLAIRONPLAYERDISAPPEAR_H_
#define DESPAWNLAIRONPLAYERDISAPPEAR_H_

#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/objects/building/PoiBuilding.h"
#include "server/zone/objects/intangible/TheaterObject.h"
#include "server/zone/Zone.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace tangible {


class DespawnLairOnPlayerDisappear : public Task {
	ManagedWeakReference<SceneObject*> lair;

public:
	DespawnLairOnPlayerDisappear(SceneObject* l) {
		lair = l;

		auto zone = l->getZone();

		if (zone != nullptr) {
			setCustomTaskQueue(zone->getZoneName());
		}
	}

	void run() {
		ManagedReference<SceneObject*> strongRef = lair.get();

		if (strongRef == NULL)
			return;

		Zone* zone = strongRef->getZone();

		if (zone == NULL)
			return;

		if (strongRef->isLairObject()) {
			ManagedReference<LairObject*> strongLair = strongRef.castTo<LairObject*>();

			Locker locker(strongLair);

			strongLair->clearDespawnEvent();

			if (strongLair->getNumberOfPlayersInRange() <= 0) {
				strongLair->destroyObjectFromWorld(true);
			}

		} else if (strongRef->isPoiBuilding()) {
			ManagedReference<PoiBuilding*> strongPoi = strongRef.castTo<PoiBuilding*>();

			Locker locker(strongPoi);

			strongPoi->clearDespawnEvent();

			if (strongPoi->getNumberOfPlayersInRange() <= 0) {
				strongPoi->destroyObjectFromWorld(true);
			}

		} else if (strongRef->isTheaterObject()) {
			ManagedReference<TheaterObject*> strongTheater = strongRef.castTo<TheaterObject*>();

			Locker locker(strongTheater);

			strongTheater->clearDespawnEvent();

			if (strongTheater->getNumberOfPlayersInRange() <= 0) {
				strongTheater->destroyObjectFromWorld(true);
			}

		}
	}
};

   }
  }
 }
}

using namespace server::zone::objects::tangible;

#endif /* DESPAWNLAIRONPLAYERDISAPPEAR_H_ */
