/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORAGINGEVENT_H_
#define FORAGINGEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/minigames/ForageManager.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class ForagingEvent : public Task {

	ManagedReference<CreatureObject*> player;
	int forageType;
	float forageX;
	float forageY;
	String zoneName;

public:
	ForagingEvent(CreatureObject* player, int type, float playerX, float playerY, const String& planet) : Task() {
		this->player = player;
		this->forageType = type;
		this->forageX = playerX;
		this->forageY = playerY;
		this->zoneName = planet;
	}

	void run() {
		ManagedReference<ForageManager*> forageManager = player->getZoneProcessServer()->getForageManager();

		if (forageManager != NULL)
			forageManager->finishForaging(player, forageType, forageX, forageY, zoneName);
	}
};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /*FORAGINGEVENT_H_*/
