#include "server/zone/managers/creature/TheaterSpawnObserver.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"

int TheaterSpawnObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::CREATUREDESPAWNED)
		return 0;

	AiAgent* ai = cast<AiAgent*>(arg1);
	TangibleObject* theater = cast<TangibleObject*>(observable);

	if (ai == NULL || theater == NULL)
		return 0;

	if (ai->getRespawnCounter() > 1) {
		spawnedCreatures.removeElement(ai);
		ai->setHomeObject(NULL);
		ai->resetRespawnCounter();

		if (spawnedCreatures.isEmpty()) {
			//Schedule theater removal from world
		}

		return 1;
	}

	Reference<Task*> task = new RespawnCreatureTask(ai, ai->getZone(), ai->getLevel());
	task->schedule((difficulty / 25 + 1) * 60 * 1000);

	return 1;
}
