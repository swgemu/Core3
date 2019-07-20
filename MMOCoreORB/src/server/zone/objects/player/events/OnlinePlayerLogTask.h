/*
* OnlinePlayerLogTask.h
*
*  Created on: Sat Jul  6 14:59:26 UTC 2019
*      Author: lordkator
*/

#ifndef ONLINEPLAYERLOGTASK_H_
#define ONLINEPLAYERLOGTASK_H_

#include "server/ServerCore.h"
#include "server/zone/managers/player/PlayerManager.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class OnlinePlayerLogTask : public Task {
	public:
	OnlinePlayerLogTask() : Task() {
	}

	void run() {
		auto server = ServerCore::getZoneServer();

		if (server == nullptr)
				return;

		Reference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == nullptr)
			return;

		playerManager->logOnlinePlayers(false);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* ONLINEPLAYERLOGTASK_H_ */
