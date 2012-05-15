/*
 * SpawnDynamicAreaCreatureTask.h
 *
 *  Created on: 31/07/2010
 *      Author: victor
 */

#ifndef SPAWNDYNAMICAREACREATURETASK_H_
#define SPAWNDYNAMICAREACREATURETASK_H_

#include "DynamicSpawnArea.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace area {

   class SpawnDynamicAreaCreatureTask : public Task {
	   ManagedReference<DynamicSpawnArea*> area;
	   ManagedReference<CreatureObject*> player;

   public:
	   SpawnDynamicAreaCreatureTask(DynamicSpawnArea* ar, CreatureObject* play) {
		   area = ar;
		   player = play;
	   }

	   void run() {
		   if (area == NULL || player == NULL)
			   return;

		   Locker locker(area);
		   area->doSpawnEvent(player);
	   }
   };

   }
  }
 }
}

using namespace server::zone::objects::area;

#endif /* SPAWNDYNAMICAREACREATURETASK_H_ */
