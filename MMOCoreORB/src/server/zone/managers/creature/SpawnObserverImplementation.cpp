
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"

void SpawnObserverImplementation::despawnSpawns() {
	Vector<ManagedReference<AiAgent* > > agents;

	for (int i = spawnedCreatures.size() - 1; i >= 0; --i) {
		ManagedReference<CreatureObject*> creature = spawnedCreatures.get(i);

		spawnedCreatures.remove(i);

		if (creature == nullptr) {
			continue;
		}

		auto agent = cast<AiAgent*>(creature.get());

		if (agent == nullptr || agent->isPet()) {
			continue;
		}

		agents.add(agent);
	}

	// info(true) << "SpawnObserverImplementation::despawnSpawns() -- LAIR IS DESTROYED! - Setting " << agents.size() << " agents to despawn!";

	for (int i = agents.size() - 1; i >= 0; --i) {
		auto agent = agents.get(i);

		// Remove it from the list
		agents.remove(i);

		if (agent != nullptr) {
			Core::getTaskManager()->executeTask([agent]() {
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

				agent->setDespawnOnNoPlayerInRange(true);
			}, "DespawnSpawnsLambda");
		}
	}
}
