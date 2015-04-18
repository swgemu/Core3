/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

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
		currentPosition.setY(mission->getEndPositionY());
		currentPosition.setZ(0);
		nextPosition = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player, zoneName);
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

		if (objectiveRef->getPlayerOwner() == NULL)
			return;

		if (move && playerRef->getZone() != NULL) {
			updatePosition(playerRef);
		}

		ManagedReference<MissionObject*> strongMissionRef = objectiveRef->getMissionObject();

		String zoneName = strongMissionRef->getEndPlanet();

		Zone* zone = playerRef->getZone();

		if (zone != NULL && zone->getZoneName() == zoneName) {
			Vector3 playerPosition = playerRef->getWorldPosition();
			playerPosition.setZ(0);

			if (playerPosition.distanceTo(currentPosition) < 500.0f) {
				updateToSpawnableTargetPosition();
				if (playerPosition.distanceTo(currentPosition) < 500.0f) {
					move = false;
					objectiveRef->spawnTarget(zoneName);
				}
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
			nextPosition = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player, zoneName);
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
				direction.setX((float)System::random(2 * radius) - radius);
				direction.setY((float)System::random(2 * radius) - radius);
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

		if (zone->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL)) {
			return true;
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
