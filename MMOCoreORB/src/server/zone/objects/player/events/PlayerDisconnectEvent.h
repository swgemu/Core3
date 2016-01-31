/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYERDISCONNECTEVENT_H_
#define PLAYERDISCONNECTEVENT_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerDisconnectEvent : public Task {
	ManagedReference<PlayerObject*> player;
	bool isSafeArea;
public:
	PlayerDisconnectEvent(PlayerObject* pl, bool isSafe) : Task(2000) {
		player = pl;
		isSafeArea = isSafe;
	}

	void run() {
		ManagedReference<SceneObject*> par = player->getParent();

		Locker locker(par);

		try {
			player->clearDisconnectEvent();

			player->setLinkDead(isSafeArea);

			if (player->isOnline())
				player->disconnect(true, false);


		} catch (Exception& e) {
			player->error("Unreported Exception caught in PlayerDisconnectEvent::activate");

			player->clearDisconnectEvent();
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
