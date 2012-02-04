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

#ifndef CALLARAKYDTASK_H_
#define CALLARAKYDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class CallArakydTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> player;
	int time;

public:
	CallArakydTask(CreatureObject* player) :
		Logger("FindTargetTask") {
		this->player = player;
		time = 20;
	}

	~CallArakydTask() {
		cancel();
	}

	void run() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL) {
			return;
		}

		switch (time) {
		case 20:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_launch_prep");
			time -= 15;
			reschedule(15 * 1000);
			break;
		case 3: {
			PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/probot_delivery.cef", playerRef->getZone()->getZoneName(), playerRef->getPositionX() + 30, playerRef->getPositionZ(), playerRef->getPositionY(), 0, 0);
			playerRef->sendMessage(effect);
		}
		case 5:
		case 4:
		case 2:
		case 1:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_arrival_" + String::valueOf(time));
			time -= 1;
			reschedule(1 * 1000);
			break;
		case 0:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_arrival");
			//TODO spawn droid.
			break;
		default:
			error("Unknowns state.");
			break;
		}
	}
};

} // namespace events
} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter::events;

#endif /* CALLARAKYDTASK_H_ */
