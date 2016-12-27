/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#include "ForageCleanupEvent.h"
#include "server/zone/managers/minigames/ForageManager.h"
#include "server/zone/ZoneProcessServer.h"

ForageCleanupEvent::ForageCleanupEvent(const String& name, ZoneProcessServer* zoneSrv) : Task() {
	playerName = name;
	zoneServer = zoneSrv;
}

void ForageCleanupEvent::run() {
	if (zoneServer == NULL)
		return;

	ManagedReference<ForageManager*> forageManager = zoneServer->getForageManager();

	if (forageManager != NULL)
		forageManager->deleteForageAreaCollection(playerName);

}




