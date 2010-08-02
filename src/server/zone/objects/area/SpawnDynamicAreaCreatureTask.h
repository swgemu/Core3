/*
 * SpawnDynamicAreaCreatureTask.h
 *
 *  Created on: 31/07/2010
 *      Author: victor
 */

#ifndef SPAWNDYNAMICAREACREATURETASK_H_
#define SPAWNDYNAMICAREACREATURETASK_H_

#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/area/DynamicSpawnArea.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace area {

   class SpawnDynamicAreaCreatureTask : public Task {
	   String templateToSpawn;
	   int numberToSpawn;

	   ManagedReference<Zone*> zone;

	   ManagedWeakReference<DynamicSpawnActiveArea*> area;

   public:
	   SpawnDynamicAreaCreatureTask(const String& file, int number, DynamicSpawnActiveArea* ar) {
		   templateToSpawn = file;
		   numberToSpawn = number;

		   area = ar;
	   }

	   void run() {
		   ManagedReference<DynamicSpawnActiveArea*> strongRef = area.get();

		   if (strongRef == NULL)
			   return;

		   CreatureManager* creatureManager = zone->getCreatureManager();

		   float radius = area->getRadius();

		   for (int i = 0;  i < numberToSpawn; ++i) {

			   float x = area->getPositionX() + (radius - System::random(radius * 2));
			   float y = area->getPositionY() + (radius - System::random(radius * 2));
			   float z = zone->getHeight(x, y);

			   ManagedReference<CreatureObject*> creature = creatureManager->spawnCreature(templateToSpawn.hashCode(), x, z, y);

			   if (creature->isAiAgent()) {
				   ((AiAgent*)creature.get())->setDespawnOnNoPlayerInRange(true);
			   }
		   }
	   }
   };

   }
  }
 }
}

using namespace server::zone::objects::area;


#endif /* SPAWNDYNAMICAREACREATURETASK_H_ */
