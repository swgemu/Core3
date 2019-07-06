/*
* OnlinePlayerLogTask.h
*
*  Created on: Sat Jul  6 14:59:26 UTC 2019
*      Author: lordkator
*/

#ifndef ONLINEPLAYERLOGTASK_H_
#define ONLINEPLAYERLOGTASK_H_

#include "server/zone/managers/player/PlayerManager.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class OnlinePlayerLogTask : public Task {
	Reference<PlayerManager*> playerManager;
	int logMaxSize;

	public:
	OnlinePlayerLogTask(PlayerManager* mgr, int logSize) : Task() {
		playerManager = mgr;
		logMaxSize = logSize;
	}

	void run() {
		if (playerManager == nullptr)
			return;

		playerManager->logOnlinePlayers(logMaxSize);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* ONLINEPLAYERLOGTASK_H_ */
