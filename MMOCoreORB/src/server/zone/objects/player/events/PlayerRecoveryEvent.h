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
	ManagedReference<PlayerObject*> player;
	Time startTime;

public:
	PlayerRecoveryEvent(PlayerObject* pl) : Task(2000) {
		player = pl;
		startTime.updateToCurrentTime();
	}

	~PlayerRecoveryEvent() {
		/*if (enQueued) {
			System::out << "ERROR: PlayerRecoveryEvent scheduled event deleted\n";
			raise(SIGSEGV);
		}*/
	}

	void run() {
		ManagedReference<SceneObject*> strongParent = player->getParent();
		
		if (strongParent == NULL)
			return;

		Locker _locker(strongParent);

		if (player->isOnline() || player->isLinkDead())
			player->doRecovery(startTime.miliDifference());


	}

	void schedule(uint64 delay = 0)
	{
		startTime.updateToCurrentTime();
		Task::schedule(delay);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /*PLAYERRECOVERYEVENT_H_*/
