
#ifndef PVPTEFREMOVALTASK_H_
#define PVPTEFREMOVALTASK_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PvpTefRemovalTask: public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	PvpTefRemovalTask(CreatureObject* creo) {
		creature = creo;
	}

	void run() {
		ManagedReference<CreatureObject*> player = creature.get();

		if (player == NULL)
			return;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject().get();

		if (ghost == NULL) {
			return;
		}

		Locker locker(player);

		if (ghost->hasPvpTef()) {
			this->reschedule(llabs(ghost->getLastPvpCombatActionTimestamp().miliDifference()));
		} else {
			ghost->updateInRangeBuildingPermissions();
			player->clearPvpStatusBit(CreatureFlag::TEF);
		}
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PVPTEFREMOVALTASK_H_ */
