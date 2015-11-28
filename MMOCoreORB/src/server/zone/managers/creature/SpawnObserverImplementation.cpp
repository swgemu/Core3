
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

void SpawnObserverImplementation::despawnSpawns() {
	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		ManagedReference<CreatureObject*> obj = spawnedCreatures.get(i);

		if (obj != NULL && obj->isAiAgent()) {
			AiAgent* aiObj = cast<AiAgent*>(obj.get());

			Locker locker(aiObj);
			aiObj->setDespawnOnNoPlayerInRange(true);
		}
	}

	spawnedCreatures.removeAll();
}
