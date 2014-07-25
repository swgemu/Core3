/*
 * DespawnLairOnPlayerDisappear.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATUREONPLAYERDISAPPEAR_H_
#define DESPAWNCREATUREONPLAYERDISAPPEAR_H_

#include "server/zone/objects/tangible/LairObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace tangible {


class DespawnLairOnPlayerDisappear : public Task {
	ManagedWeakReference<LairObject*> lair;

public:
	DespawnLairOnPlayerDisappear(LairObject* l) {
		lair = l;
	}

	void run() {
		ManagedReference<LairObject*> strongRef = lair.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->clearDespawnEvent();

		Zone* zone = strongRef->getZone();

		if (zone == NULL)
			return;

		if (strongRef->getNumberOfPlayersInRange() <= 0) {
			strongRef->destroyObjectFromWorld(true);
		}
	}
};

   }
  }
 }
}

using namespace server::zone::objects::tangible;

#endif /* DESPAWNCREATUREONPLAYERDISAPPEAR_H_ */
