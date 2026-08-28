
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"
#include "server/zone/managers/creature/observers/CreatureHerdObserver.h"

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

				// The lair is gone, so the herd is finished -- this is the last
				// moment anything can unhook a member that is dead with a respawn
				// pending (it is not in the world, so it never takes another
				// despawn pass). An intact HERD registration <-> herdMembers pair
				// is a strong reference cycle the reference-count GC can never
				// collect; every abandoned dynamic-spawn herd leaked this way,
				// each member pinning its weapons, inventory and CreditObject.
				SortedVector<ManagedReference<Observer* > > herdObservers = agent->getObservers(ObserverEventType::HERD);

				for (int i = herdObservers.size() - 1; i >= 0; --i) {
					ManagedReference<CreatureHerdObserver*> herdObserver = cast<CreatureHerdObserver*>(herdObservers.get(i).get());

					if (herdObserver != nullptr) {
						herdObserver->removeMember(agent);
						agent->dropObserver(ObserverEventType::HERD, herdObserver);
					}
				}

				if (agent->getHerdObserver() != nullptr) {
					agent->setHerdObserver(nullptr);
				}

				agent->setDespawnOnNoPlayerInRange(true);
			}, "DespawnSpawnsLambda");
		}
	}
}
