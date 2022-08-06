/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#ifndef PLAYERBASEREMOVALTASK_H_
#define PLAYERBASEREMOVALTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/gcw/GCWManager.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerBaseRemovalTask: public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	PlayerBaseRemovalTask(CreatureObject* pl) {
		creature = pl;
	}

	void run() {
		ManagedReference<CreatureObject*> player = creature.get();

		if (player == nullptr)
			return;

		try {
			Zone* zone = player->getZone();

			if (zone == nullptr)
				return;

			GCWManager* gcwMan = zone->getGCWManager();

			if (gcwMan == nullptr)
				return;

			// If PvE base placement is not allowed, they are automatically scheduled to be removed and can be ignored here
			bool pvpBasesOnly = gcwMan->allowPveBasePlacement() ? false : true;

			int baseCount = gcwMan->getBaseCount(player, pvpBasesOnly);
			int maxBases = gcwMan->getMaxBasesPerPlayer();

			if (baseCount > maxBases) {
				ManagedReference<PlayerObject*> ghost = player->getPlayerObject().get();
				ZoneServer* zoneServer = player->getZoneServer();

				if (ghost != nullptr && zoneServer != nullptr) {
					Locker lock(player);

					int totalStructures = ghost->getTotalOwnedStructureCount();
					int basesDestroyed = 0;

#ifdef DEBUG
					player->info(true) << "PlayerBaseRemovalTask called - player base count = " << baseCount << "  maxBases = " << maxBases << "  total owned structures = " << totalStructures;
#endif

					for (int i = 0; i < totalStructures; ++i) {
#ifdef DEBUG
						player->info(true) << " Getting structure #" << i;
#endif
						if (basesDestroyed == (baseCount - maxBases))
							break;

						ManagedReference<SceneObject*> structure = zoneServer->getObject(ghost->getOwnedStructure(i));

						if (structure != nullptr && structure->isGCWBase()) {
							Reference<BuildingObject*> building = structure->asBuildingObject();

							if (building == nullptr)
								continue;

							// Check against all bases or if pveBase are not allowed then only try to remove the PvP bases. The PvE bases are auto removed on server boot.
							if (!pvpBasesOnly || (pvpBasesOnly && (building->getPvpStatusBitmask() & CreatureFlag::OVERT))) {
#ifdef DEBUG
								player->info(true) << " Destroying GCW Base #" << i << "  Total bases destroy = " << basesDestroyed;
#endif
								gcwMan->scheduleBaseDestruction(building, player, true);
								basesDestroyed++;
							}
						}
					}
				}
			}

		} catch (Exception& e) {
			player->error("unreported exception caught in PlayerBaseRemovalTask");
			e.printStackTrace();
		}
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PLAYERBASEREMOVALTASK_H_ */