
#include <stddef.h>
#include <algorithm>

#include "engine/core/Core.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/TaskManager.h"
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "system/util/SynchronizedVector.h"
#include "system/util/Vector.h"

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
