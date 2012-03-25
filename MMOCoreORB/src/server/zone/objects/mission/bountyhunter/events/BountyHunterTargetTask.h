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
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class BountyHunterTargetTask: public Task, public Logger {
	ManagedWeakReference<MissionObject*> mission;
	ManagedWeakReference<BountyMissionObjective*> objective;
	ManagedWeakReference<CreatureObject*> player;

	Vector3 nextPosition;
	Vector3 currentPosition;
	bool move;
	String zoneName;

public:
	BountyHunterTargetTask(MissionObject* mission, CreatureObject* player, const String& zoneName) :
		Logger("BountyHunterTargetTask") {
		this->mission = mission;
		this->player = player;
		this->zoneName = zoneName;

		objective = cast<BountyMissionObjective*> (mission->getMissionObjective());

		currentPosition.setX(mission->getEndPositionX());
		currentPosition.setY(mission->getEndPositionX());
		currentPosition.setZ(0);
		nextPosition = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player);
		nextPosition.setZ(0);

		if (mission->getMissionLevel() > 1) {
			move = true;
		} else {
			move = false;
		}
	}

	~BountyHunterTargetTask() {
		cancel();
	}

	// TODO: add shuttle jumping and planet jumping when path finding in cities is good enough.
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
		}

		String zoneName = objectiveRef->getMissionObject()->getEndPlanet();

		Zone* zone = playerRef->getZone();

		if (zone != NULL && zone->getZoneName() == zoneName) {
			Vector3 playerPosition = playerRef->getWorldPosition();
			playerPosition.setZ(0);

			if (playerPosition.distanceTo(currentPosition) < 500.0f) {
				move = false;
				objectiveRef->spawnTarget(zoneName);
			}
		}

		reschedule(10 * 1000);
	}

	Vector3 getTargetPosition() {
		return currentPosition;
	}

	String getTargetZoneName() {
		return zoneName;
	}

private:
	void updatePosition(CreatureObject* player) {
		Vector3 direction = nextPosition - currentPosition;
		Vector3 movementUpdate = direction;
		movementUpdate.normalize();

		if (direction.length() > 10.0) {
			currentPosition = currentPosition + (10 * movementUpdate);
		} else {
			currentPosition = nextPosition;
			nextPosition = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player);
			nextPosition.setZ(0);
		}
	}

	void updateToSpawnableTargetPosition() {
		if (canSpawnTargetAt(currentPosition)) {
			return;
		}

		//Spawning at coordinates failed, try to find new coordinates.
		int radius = 50;
		while (radius <= 1600) {
			//Max 20 retries per radius, total 120 retries.
			int retries = 20;

			while (retries > 0) {
				//Generate a random direction and move the target position in that direction within the radius.
				Vector3 direction;
				direction.setX(System::random(2 * radius) - radius);
				direction.setY(System::random(2 * radius) - radius);
				direction.normalize();
				direction = direction * System::random(radius);

				if (canSpawnTargetAt(currentPosition + direction)) {
					currentPosition = currentPosition + direction;
					return;
				}

				retries--;
			}

			radius *= 2;
		}

		//Failed to find new spawn for the target, spawn at current position.
	}

	bool canSpawnTargetAt(const Vector3& position) {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL || playerRef->getZone() == NULL) {
			return false;
		}

		Zone* zone = playerRef->getZone();

		if (zone->isWithinBoundaries(position)) {
			if (zone->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL)) {
				return true;
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

#endif /* BOUNTYHUNTERTARGETTASK_H_ */
