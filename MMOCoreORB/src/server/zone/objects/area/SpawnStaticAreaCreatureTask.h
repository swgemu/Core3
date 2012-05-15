/*
 * SpawnStaticAreaCreatureTask.h
 *
 *  Created on: Nov 7, 2010
 *      Author: da
 */

#ifndef SPAWNSTATICAREACREATURETASK_H_
#define SPAWNSTATICAREACREATURETASK_H_

#include "StaticSpawnArea.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace area {

   class SpawnStaticAreaCreatureTask : public Task {
	   ManagedReference<StaticSpawnArea*> area;

   public:
	   SpawnStaticAreaCreatureTask(StaticSpawnArea* ar) {
		   area = ar;
	   }

	   void run() {
		   if (area == NULL)
			   return;

		   area->doSpawnEvent();
	   }
   };

   }
  }
 }
}

#endif /* SPAWNSTATICAREACREATURETASK_H_ */
