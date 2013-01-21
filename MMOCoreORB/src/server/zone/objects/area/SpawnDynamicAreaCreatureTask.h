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
	   int reschedulTime;

   public:
	   SpawnDynamicAreaCreatureTask(DynamicSpawnArea* area, int rescheduleTime) {
		   this->area = area;
		   this->reschedulTime = rescheduleTime;
	   }

	   void run() {
		   if (area == NULL)
			   return;

		   Locker locker(area);
		   area->doSpawnEvent();

		   reschedule(reschedulTime);
	   }
   };

   }
  }
 }
}

using namespace server::zone::objects::area;

#endif /* SPAWNDYNAMICAREACREATURETASK_H_ */
