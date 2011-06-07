/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef FISHINGEVENT_H_
#define FISHINGEVENT_H_


#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/ZoneServer.h"
#include "../FishingManager.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class FishingEvent : public Task {
	ManagedReference<PlayerCreature*> player;
	ManagedReference<ZoneServer*> zoneServer;
	int fishingState;

public:
	FishingEvent(PlayerCreature* player, ZoneServer* zoneServer, int fishingState) : Task(7000) {
		this->player = player;
		this->zoneServer = zoneServer;
		this->fishingState = fishingState;
	}

	void run() {
		// FIXME
		/*if (player == NULL)
			return;*/

		try {
			Locker _locker(player);

			//player->info("activating command queue action");

			ManagedReference<FishingManager*> manager = zoneServer->getFishingManager();
			//Locker lockerManager(manager);
			//player->removePendingTask("fishing");
			if (fishingState != FishingManagerImplementation::NOTFISHING) {
				manager->fishingStep(player);

			} /*else if (marker != NULL) {
					// new event
				manager->createFishingEvent(player, nextAction, zoneServer, marker, fish, boxID, fishingState, mood);

			}*/ else {

				manager->stopFishingEvent(player);

			}

			//player->info("command queue action activated");


		} catch (...) {
			//player = NULL;

			throw;
		}

		//player = NULL;
	}
};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGEVENT_H_ */
