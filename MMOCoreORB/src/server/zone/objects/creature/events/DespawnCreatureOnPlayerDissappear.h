/*
 * DespawnCreatureOnPlayerDissappear.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATUREONPLAYERDISSAPPEAR_H_
#define DESPAWNCREATUREONPLAYERDISSAPPEAR_H_

#include "../AiAgent.h"
#include "../ai/AiActor.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    namespace events {


class DespawnCreatureOnPlayerDissappear : public Task {
	ManagedWeakReference<AiAgent*> creature;
	ManagedWeakReference<AiActor*> actor;

public:
	DespawnCreatureOnPlayerDissappear(AiAgent* creo) {
		creature = creo;
	}

	DespawnCreatureOnPlayerDissappear(AiActor* a) {
		actor = a;
	}

	void run() {
		ManagedReference<AiActor*> strongRef = actor.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->clearDespawnEvent();

		Zone* zone = strongRef->getZone();

		if (zone == NULL)
			return;

		if (!strongRef->getDespawnOnNoPlayerInRange())
			return;

		if (strongRef->inRangeObjects(SceneObjectType::PLAYERCREATURE, 128) == 0 && strongRef->getNumberOfPlayersInRange() <= 0) {
			ManagedReference<CreatureObject*> host = strongRef->getHost();
			if (host != NULL) {
				host->destroyObjectFromWorld(true);
				strongRef->setHost(NULL);
			}

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
