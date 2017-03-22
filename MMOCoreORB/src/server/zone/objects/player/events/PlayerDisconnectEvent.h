/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYERDISCONNECTEVENT_H_
#define PLAYERDISCONNECTEVENT_H_

#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerDisconnectEvent : public Task {
	ManagedWeakReference<PlayerObject*> player;
	bool isSafeArea;
public:
	PlayerDisconnectEvent(PlayerObject* pl, bool isSafe) : Task(2000) {
		player = pl;
		isSafeArea = isSafe;
	}

	void run() {
		ManagedReference<PlayerObject*> play = player.get();

		if (play == NULL)
			return;

		ManagedReference<SceneObject*> par = play->getParent().get();

		Locker locker(par);

		try {
			play->clearDisconnectEvent();

			play->setLinkDead(isSafeArea);

			if (play->isOnline())
				play->disconnect(true, false);


		} catch (Exception& e) {
			play->error("Unreported Exception caught in PlayerDisconnectEvent::activate");

			play->clearDisconnectEvent();
		}
	}

};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /*PLAYERDISCONNECTEVENT_H_*/
