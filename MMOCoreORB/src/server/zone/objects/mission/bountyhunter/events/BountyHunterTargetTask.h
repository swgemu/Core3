/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BOUNTYHUNTERTARGETTASK_H_
#define BOUNTYHUNTERTARGETTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
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

	Vector3 currentPosition;
	Vector3 destination;
	bool move, movedOffPlanet, movingToStarport, targetSpawned;
	String zoneName;

public:
	BountyHunterTargetTask(MissionObject* mission, CreatureObject* player, const String& zoneName) :
		Logger("BountyHunterTargetTask") {
		this->mission = mission;
		this->player = player;
		this->zoneName = zoneName;
		this->movedOffPlanet = false;
		this->movingToStarport = false;
		this->targetSpawned = false;
		this->destination = Vector3(0, 0, 0);

		objective = cast<BountyMissionObjective*> (mission->getMissionObjective());

		currentPosition.setX(mission->getEndPositionX());
		currentPosition.setY(mission->getEndPositionY());
		currentPosition.setZ(0);

		if (mission->getMissionLevel() > 1) {
			move = true;
		} else {
			move = false;
		}
	}

	~BountyHunterTargetTask() {
	}

	void run() {
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (objectiveRef == NULL)
			return;

		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL)
			return;

		ZoneServer* zoneServer = playerRef->getZoneServer();

		Zone* zone = zoneServer->getZone(zoneName);

		if (zone == NULL)
			return;

		ManagedReference<MissionObject*> strongMissionRef = mission.get();

		if (strongMissionRef == NULL)
			return;

		if (destination == Vector3(0, 0, 0)) {
			ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

			if (strongMissionRef->getMissionLevel() > 2) {
				Reference<PlanetTravelPoint*> randomStarport = planetManager->getRandomStarport();
				destination = randomStarport->getDeparturePosition();
				destination.setZ(0);
				movingToStarport = true;
			} else {
				destination = zoneServer->getMissionManager()->getRandomBountyTargetPosition(playerRef, zoneName);
			}
		}

		Locker locker(playerRef);

		if (move && !targetSpawned)
			updatePosition(playerRef);

		Zone* playerZone = playerRef->getZone();

		if (!targetSpawned && playerZone != NULL && playerZone->getZoneName() == zoneName) {
			Vector3 playerPosition = playerRef->getWorldPosition();
			playerPosition.setZ(0);

			if (playerPosition.distanceTo(currentPosition) < 256.0f) {
				updateToSpawnableTargetPosition();
				if (playerPosition.distanceTo(currentPosition) < 256.0f) {
					targetSpawned = true;
					Locker olocker(objectiveRef);
					objectiveRef->spawnTarget(zoneName);
				}
			}
		}

		reschedule(10 * 1000);
	}

	Vector3 getTargetPosition() {
		return currentPosition;
	}

	const String& getTargetZoneName() {
		return zoneName;
	}

private:
	void updatePosition(CreatureObject* player) {
		Vector3 direction = destination - currentPosition;
		float distToDest = direction.length();
		int distPerSec = Math::min(4, 1 + mission.get()->getMissionLevel());
		float distToTravel = distPerSec * 10.f;

		if (distToDest <= distToTravel) {
			currentPosition = destination;

			if (movingToStarport && !movedOffPlanet) {
				zoneName = player->getZoneServer()->getMissionManager()->getRandomBountyPlanet();
				movedOffPlanet = true;
				movingToStarport = false;

				ZoneServer* zoneServer = player->getZoneServer();
				Zone* zone = zoneServer->getZone(zoneName);

				if (zone == NULL)
					return;

				ManagedReference<MissionObject*> strongMissionRef = mission.get();

				if (strongMissionRef == NULL)
					return;

				Locker clocker(strongMissionRef, player);
				strongMissionRef->setEndPlanet(zoneName);

				ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
				Reference<PlanetTravelPoint*> randomStarport = planetManager->getRandomStarport();
				currentPosition = randomStarport->getDeparturePosition();
			}

			destination = player->getZoneServer()->getMissionManager()->getRandomBountyTargetPosition(player, zoneName);
		} else {
			Vector3 movementUpdate = direction;
			movementUpdate.normalize();
			movementUpdate = movementUpdate * distToTravel;

			currentPosition = currentPosition + movementUpdate;
		}
	}

	void updateToSpawnableTargetPosition() {
		ManagedReference<CreatureObject*> playerRef = player.get();

		if (playerRef == NULL || playerRef->getZone() == NULL)
			return;

		Zone* zone = playerRef->getZone();
		SortedVector<ManagedReference<NavArea*> > areas;

		Sphere sphere(Vector3(currentPosition.getX(), currentPosition.getY(), zone->getHeightNoCache(currentPosition.getX(), currentPosition.getY())), 20);
		Vector3 result;

		if (PathFinderManager::instance()->getSpawnPointInArea(sphere, zone, result)) {
			currentPosition.setX(result.getX());
			currentPosition.setY(result.getY());
			return;
		}

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
