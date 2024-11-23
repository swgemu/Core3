/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SERVERTIMETASK_H_
#define SERVERTIMETASK_H_

#include "engine/engine.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/scene/ServerTimeMessage.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class ServerTimeTask: public Task {
	ManagedReference<PlayerObject*> player;

public:
	ServerTimeTask(PlayerObject* pl) {
		player = pl;
	}

	void run() {
		if (player == nullptr || !player->isOnline() || player->isLinkDead())
			return;

		Zone* zone = player->getZone();
		if (zone == nullptr)
			return;

		ServerTimeMessage* stm = new ServerTimeMessage(zone);
		player->sendMessage(stm);

		if (isScheduled()) {
			reschedule(60 * 1000);
		} else {
			schedule(60 * 1000);
		}
	}
};

}
}
}
}
}

#endif /* SERVERTIMETASK_H_ */
