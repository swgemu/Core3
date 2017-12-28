/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORAGECLEANUPEVENT_H_
#define FORAGECLEANUPEVENT_H_

#include "engine/core/ManagedReference.h"
#include "engine/core/Task.h"
#include "server/zone/ZoneProcessServer.h"
#include "system/lang/String.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class ForageCleanupEvent : public Task {

public:
	ForageCleanupEvent(const String& name, ZoneProcessServer* zoneServer);

	void run();

	String playerName;
	ManagedReference<ZoneProcessServer*> zoneServer;

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /*FORAGECLEANUPEVENT_H_*/
