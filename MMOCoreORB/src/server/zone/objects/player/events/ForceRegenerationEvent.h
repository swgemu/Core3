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
	ManagedReference<PlayerObject*> player;

public:
	ForceRegenerationEvent(PlayerObject* pl) {
		player = pl;
	}

	void run() {
		ManagedReference<SceneObject*> strongParent = player->getParent();

		if (strongParent == NULL)
			return;

		Locker _locker(strongParent);

		if (player->isOnline() || player->isLinkDead()) {
			if (player->getForcePowerMax() > 0  && (player->getForcePowerMax() - player->getForcePower() > 0)){
				player->doForceRegen();
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
