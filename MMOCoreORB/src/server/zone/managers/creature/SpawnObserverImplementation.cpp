
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

void SpawnObserverImplementation::despawnSpawns() {
	Vector<ManagedReference<AiAgent* > > agents;

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		ManagedReference<CreatureObject*> obj = spawnedCreatures.get(i);

		if (obj != NULL && obj->isAiAgent()) {
			AiAgent* aiObj = cast<AiAgent*>(obj.get());
			agents.add(aiObj);
		}
	}

	spawnedCreatures.removeAll();

	Core::getTaskManager()->executeTask([=] () {
		for (int i = 0; i < agents.size(); ++i) {
			AiAgent* agent = agents.get(i);

			Locker locker(agent);

			agent->setDespawnOnNoPlayerInRange(true);
		}
	}, "DespawnSpawnsLambda");
}
