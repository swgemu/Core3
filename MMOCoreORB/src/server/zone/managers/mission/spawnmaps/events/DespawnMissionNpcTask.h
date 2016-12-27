/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DESPAWNMISSIONNPCTASK_H_
#define DESPAWNMISSIONNPCTASK_H_

#include "server/zone/managers/mission/spawnmaps/NpcSpawnPoint.h"
#include "server/zone/managers/mission/MissionManager.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {
namespace events {

class DespawnMissionNpcTask : public Task {
	ManagedReference<MissionManager*> missionManager;
	Reference<NpcSpawnPoint*> npcSpawnPoint;

public:
	DespawnMissionNpcTask(MissionManager* missionManager, NpcSpawnPoint* npcSpawnPoint) {
		this->missionManager = missionManager;
		this->npcSpawnPoint = npcSpawnPoint;
	}

	void run() {
		missionManager->despawnMissionNpc(npcSpawnPoint);
	}
};

} // namespace events
} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps::events;

#endif /* DESPAWNMISSIONNPCTASK_H_ */
