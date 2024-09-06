/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYERRECOVERYEVENT_H_
#define PLAYERRECOVERYEVENT_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerRecoveryEvent : public Task {
	ManagedWeakReference<PlayerObject*> weakGhost;
	Time startTime;

public:
	PlayerRecoveryEvent(PlayerObject* ghost) : Task(2000) {
		weakGhost = ghost;
		startTime.updateToCurrentTime();
	}

	~PlayerRecoveryEvent() {
	}

	void run() {
		ManagedReference<PlayerObject*> ghost = weakGhost.get();

		if (ghost == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> strongParent = ghost->getParent().get();

		if (strongParent == nullptr) {
			return;
		}

		Locker lock(strongParent);

		if (!ghost->isOnline() && !ghost->isLinkDead()) {
			return;
		}

		ghost->doRecovery(startTime.miliDifference());
	}

	void schedule(uint64 delay = 0) {
		startTime.updateToCurrentTime();
		Task::schedule(delay);
	}
};

} // namespace events
} // namespace player
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::player::events;

#endif /*PLAYERRECOVERYEVENT_H_*/
