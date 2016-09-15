/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BOUNTYHUNTERTEFREMOVALTASK_H_
#define BOUNTYHUNTERTEFREMOVALTASK_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class BountyHunterTefRemovalTask: public Task {
	ManagedWeakReference<PlayerObject*> bountyHunter;
	uint64 targetId;

public:
	BountyHunterTefRemovalTask(PlayerObject* bountyHunter, uint64 targetId) {
		this->bountyHunter = bountyHunter;
		this->targetId = targetId;
	}

	void run() {
		ManagedReference<PlayerObject*> bountyHunterRef = bountyHunter.get();

		if (bountyHunterRef == NULL) {
			return;
		}

		ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(bountyHunterRef->getParent().get().get());

		if (creature == NULL) {
			return;
		}

		Locker creatureLock(creature);

		bountyHunterRef->removeFromBountyLockListDirectly(targetId);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* BOUNTYHUNTERTEFREMOVALTASK_H_ */
