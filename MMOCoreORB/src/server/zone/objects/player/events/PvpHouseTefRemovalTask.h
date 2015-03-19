
#ifndef PVPHOUSETEFREMOVALTASK_H_
#define PVPHOUSETEFREMOVALTASK_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PvpHouseTefRemovalTask: public Task {
	ManagedWeakReference<PlayerObject*> playerObject;

public:
	PvpHouseTefRemovalTask(PlayerObject* player) {
		playerObject = player;
	}

	void run() {
		ManagedReference<PlayerObject*> ghost = playerObject.get();

		if (ghost == NULL) {
			return;
		}

		if (ghost->hasPvpTef()) {
			this->reschedule(llabs(ghost->getLastPvpCombatActionTimestamp().miliDifference()));
		} else {
			Locker locker(ghost);
			ghost->updateInRangeBuildingPermissions();
		}
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PVPHOUSETEFREMOVALTASK_H_ */
