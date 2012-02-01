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

#ifndef BOUNTYHUNTERTARGETTASK_H_
#define BOUNTYHUNTERTARGETTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class BountyHunterTargetTask : public Task, public Logger {
	ManagedWeakReference<MissionObject*> mission;
	ManagedWeakReference<BountyMissionObjective*> objective;
	ManagedWeakReference<CreatureObject*> player;

	Vector3 nextPosition;
	Vector3 currentPosition;
	bool move;

public:
	BountyHunterTargetTask(MissionObject* mission, CreatureObject* player) :
		Logger("BountyHunterTargetTask") {
		this->mission = mission;
		this->player = player;

		objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

		currentPosition.setX(mission->getEndPositionX());
		currentPosition.setY(mission->getEndPositionX());
		currentPosition.setZ(0);
		nextPosition = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player);
		nextPosition.setZ(0);

		if (mission->getDifficultyLevel() > 1) {
			move = true;
		} else {
			move = false;
		}
	}

	~BountyHunterTargetTask() {
		cancel();
	}

	void run() {
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL) {
			return;
		}

		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL || playerRef->getZoneServer() == NULL) {
			return;
		}

		Locker locker(playerRef);

		if (move) {
			updatePosition(playerRef);

			String zoneName = objectiveRef->getMissionObject()->getEndPlanet();

			Zone* zone = playerRef->getZone();

			if (zone != NULL && zone->getZoneName() == zoneName && playerRef->getWorldPosition().distanceTo(currentPosition) < 500.0) {
				move = false;
				objectiveRef->spawnTarget(zoneName);
			}

			reschedule(10 * 1000);
		}
	}

	void updatePosition(CreatureObject* playerRef) {
		Vector3 direction = nextPosition - currentPosition;
		Vector3 movementUpdate = direction;
		movementUpdate.normalize();

		if (direction.length() > 10.0) {
			currentPosition = currentPosition + (10 * movementUpdate);
		} else {
			currentPosition = nextPosition;
			nextPosition = playerRef->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(playerRef);
			nextPosition.setZ(0);
		}
	}

	Vector3 getTargetPosition() {
		return currentPosition;
	}
};

} // namespace events
} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter::events;

#endif /* BOUNTYHUNTERTARGETTASK_H_ */
