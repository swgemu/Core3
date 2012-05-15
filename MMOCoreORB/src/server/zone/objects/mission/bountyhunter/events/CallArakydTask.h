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
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class CallArakydTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> player;
	ManagedWeakReference<BountyMissionObjective*> objective;
	int time;
	Vector3 droidPosition;

public:
	CallArakydTask(CreatureObject* player, BountyMissionObjective* objective) :
		Logger("FindTargetTask") {
		this->player = player;
		this->objective = objective;
		time = 20;
	}

	~CallArakydTask() {
		cancel();
	}

	void run() {
		ManagedReference<CreatureObject*> playerRef = player.get();
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (playerRef == NULL || objectiveRef == NULL) {
			return;
		}

		switch (time) {
		case 20:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_launch_prep");
			time -= 15;
			reschedule(15 * 1000);
			break;
		case 3: {
			droidPosition = getLandingCoordinates(playerRef);
			PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/probot_delivery.cef", playerRef->getZone()->getZoneName(), droidPosition.getX(), droidPosition.getZ(), droidPosition.getY(), 0, 0);
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
		case 0: {
				playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_arrival");
				ManagedReference<AiAgent*> droid = cast<AiAgent*>(playerRef->getZone()->getCreatureManager()->spawnCreature(String("probot").hashCode(), 0, droidPosition.getX(), droidPosition.getZ(), droidPosition.getY(), 0));
				objectiveRef->setArakydDroid(droid);
				droid->setFollowObject(playerRef);
			}
			break;
		default:
			error("Unknowns state.");
			break;
		}
	}

	Vector3 getLandingCoordinates(CreatureObject* player) {
		Vector3 position = player->getPosition();

		if (player->getZone() == NULL || player->getZone()->getPlanetManager() == NULL) {
			return position;
		}

		PlanetManager* planetManager = player->getZone()->getPlanetManager();

		int distance = 30;
		int angle = 15;

		do {
			for (int i = 0; i < 10; i++) {
				position = player->getWorldCoordinate(distance + System::random(20), angle - System::random(2 * angle));

				if (noInterferingObjects(player, position)) {
					return position;
				}
			}

			distance += 10;
			angle += 5;
		} while (distance <= 60);

		return player->getPosition();
	}

	bool noInterferingObjects(CreatureObject* player, Vector3 position)
	{
		SortedVector<ManagedReference<QuadTreeEntry* > >* closeObjects =  player->getCloseObjects();

		for (int j = 0; j < closeObjects->size(); j++) {
			SceneObject* obj = cast<SceneObject*>(closeObjects->get(j).get());

			SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

			if (objectTemplate != NULL) {
				float radius = objectTemplate->getNoBuildRadius();

				if (radius > 0) {
					Vector3 objWorldPos = obj->getWorldPosition();

					if (objWorldPos.squaredDistanceTo(position) < radius * radius) {
						return false;
					}
				}
			}
		}

		return true;
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
