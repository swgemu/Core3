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
	ManagedWeakReference<PlayerObject*> player;

public:
	ForceRegenerationEvent(PlayerObject* pl) {
		player = pl;
	}

	void run() {
		ManagedReference<PlayerObject*> play = player.get();

		if (play == NULL)
			return;

		ManagedReference<SceneObject*> strongParent = play->getParent().get();

		if (strongParent == NULL)
			return;

		Locker _locker(strongParent);

		if (play->isOnline() || play->isLinkDead()) {
			if (play->getForcePowerMax() > 0  && (play->getForcePowerMax() - play->getForcePower() > 0)){
				play->doForceRegen();
			}
		}


	}

};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /*PLAYERRECOVERYEVENT_H_*/
