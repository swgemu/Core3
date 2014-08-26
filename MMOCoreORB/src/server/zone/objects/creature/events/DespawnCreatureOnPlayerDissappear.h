/*
 * DespawnCreatureOnPlayerDissappear.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATUREONPLAYERDISSAPPEAR_H_
#define DESPAWNCREATUREONPLAYERDISSAPPEAR_H_

#include "server/zone/objects/creature/AiAgent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    namespace events {


class DespawnCreatureOnPlayerDissappear : public Task {
	ManagedWeakReference<AiAgent*> creature;

public:
	DespawnCreatureOnPlayerDissappear(AiAgent* creo) {
		creature = creo;
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->clearDespawnEvent();

		Zone* zone = strongRef->getZone();

		if (zone == NULL)
			return;

		if (!strongRef->getDespawnOnNoPlayerInRange())
			return;

		if (strongRef->getNumberOfPlayersInRange() <= 0) {
			strongRef->destroyObjectFromWorld(true);
			strongRef->notifyDespawn(zone);
		}
	}
};


    }
   }
  }
 }
}

using namespace server::zone::objects::creature::events;

#endif /* DESPAWNCREATUREONPLAYERDISSAPPEAR_H_ */
