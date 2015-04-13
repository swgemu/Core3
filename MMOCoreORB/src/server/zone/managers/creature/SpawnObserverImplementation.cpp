
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/AiAgent.h"

void SpawnObserverImplementation::despawnSpawns() {
	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* obj = spawnedCreatures.get(i);

		if (obj->isAiAgent()) {
			AiAgent* aiObj = cast<AiAgent*>(obj);

			Locker locker(aiObj);
			aiObj->setDespawnOnNoPlayerInRange(true);
		}
	}

	spawnedCreatures.removeAll();
}
