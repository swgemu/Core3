/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FORCEREGENERATIONEVENT_H_
#define FORCEREGENERATIONEVENT_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class ForceRegenerationEvent : public Task {
	ManagedWeakReference<PlayerObject*> weakGhost;

public:
	ForceRegenerationEvent(PlayerObject* ghost) {
		weakGhost = ghost;
	}

	void run() {
		ManagedReference<PlayerObject*> ghost = weakGhost.get();

		if (ghost == nullptr) {
			return;
		}

		ManagedReference<CreatureObject*> player = dynamic_cast<CreatureObject*>(ghost->getParent().get().get());

		if (player == nullptr) {
			return;
		}

		Locker lock(player);

		if (!ghost->isOnline() && !ghost->isLinkDead()) {
			return;
		}

		int forceMax = ghost->getForcePowerMax();
		int forceCurrent = ghost->getForcePower();

		if (forceMax < 1 || ((forceMax - forceCurrent) < 1)) {
			return;
		}

		ghost->doForceRegen();
	}
};

} // namespace events
} // namespace player
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::player::events;

#endif /*PLAYERRECOVERYEVENT_H_*/
