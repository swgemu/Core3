
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void SpawnObserverImplementation::despawnSpawns() {
	info(true) << "SpawnObserverImplementation::despawnSpawns() called";

	Vector<ManagedReference<AiAgent* > > agents;

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		ManagedReference<CreatureObject*> creature = spawnedCreatures.get(i);

		if (creature != nullptr && creature->isAiAgent()) {
			AiAgent* agent = cast<AiAgent*>(creature.get());

			if (agent == nullptr)
				continue;

			agents.add(agent);
		}
	}

	spawnedCreatures.removeAll();

	for (int i = agents.size() - 1; i >= 0; --i) {
		ManagedReference<AiAgent*> agent = agents.get(i);

		if (agent != nullptr) {
			Reference<AiAgent*> agentRef = agents.get(i);

			Core::getTaskManager()->executeTask([agentRef] () {
				if (agentRef == nullptr)
					return;

				agentRef->info(true) << "despawn agent from lair lambda called";

				Locker locker(agentRef);

				agentRef->unequipWeapons();

				WeaponObject* primaryWeap = agentRef->getPrimaryWeapon();
				WeaponObject* secondaryWeap = agentRef->getSecondaryWeapon();
				WeaponObject* thrownWeap = agentRef->getThrownWeapon();
				WeaponObject* defaultWeap = agentRef->getDefaultWeapon();

				if (primaryWeap != nullptr && primaryWeap != agentRef->getDefaultWeapon()) {
					Locker plocker(primaryWeap, agentRef);
					primaryWeap->destroyObjectFromWorld(true);
				}

				if (secondaryWeap != nullptr) {
					Locker slocker(secondaryWeap, agentRef);
					secondaryWeap->destroyObjectFromWorld(true);
				}

				if (thrownWeap != nullptr) {
					Locker tlocker(thrownWeap, agentRef);
					thrownWeap->destroyObjectFromWorld(true);
				}

				if (defaultWeap != nullptr) {
					Locker dlocker(defaultWeap, agentRef);
					defaultWeap->destroyObjectFromWorld(true);
				}

				agentRef->nullifyWeapons();

				//agentRef->setDespawnOnNoPlayerInRange(true);
				agentRef->destroyObjectFromWorld(true);
				agentRef->destroyObjectFromDatabase(true);

			}, "DespawnSpawnsLambda");
		}

		agents.remove(i);
	}
}
