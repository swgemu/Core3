
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"

void SpawnObserverImplementation::despawnSpawns() {
	Vector<ManagedReference<AiAgent* > > agents;

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		ManagedReference<CreatureObject*> creature = spawnedCreatures.get(i);

		if (creature != nullptr && creature->isAiAgent()) {
			AiAgent* agent = cast<AiAgent*>(creature.get());

			if (agent == nullptr || agents.contains(agent))
				continue;

			agents.add(agent);
		}
	}

	spawnedCreatures.removeAll();

	for (int i = agents.size() - 1; i >= 0; --i) {
		Reference<AiAgent*> agent = agents.get(i);

		if (agent != nullptr) {
			Core::getTaskManager()->executeTask([agent] () {
				if (agent == nullptr)
					return;

				Locker locker(agent);

				SortedVector<ManagedReference<Observer* > > observers = agent->getObservers(ObserverEventType::SQUAD);

				for (int i = observers.size() - 1; i >= 0; --i) {
					ManagedReference<SquadObserver*> squadObserver = cast<SquadObserver*>(observers.get(i).get());

					if (squadObserver != nullptr) {
						agent->dropObserver(ObserverEventType::SQUAD, squadObserver);
					}
				}

				if (agent->getZone() == nullptr) {
					agent->wipeBlackboard();
					agent->destroyAllWeapons();
				} else {
					agent->setDespawnOnNoPlayerInRange(true);
					agent->scheduleDespawn(300, true);
				}
			}, "DespawnSpawnsLambda");
		}

		agents.remove(i);
	}
}
