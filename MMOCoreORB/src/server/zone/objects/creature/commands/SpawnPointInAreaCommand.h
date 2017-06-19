
#ifndef SPAWNPOINTINAREACOMMAND_H
#define SPAWNPOINTINAREACOMMAND_H

#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/managers/collision/PathFinderManager.h"

class SpawnPointInAreaCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		PlayerObject* ghost = creature->getPlayerObject();
		Zone* zone = creature->getZone();

		if (ghost == nullptr || ghost->getAdminLevel() < 14 || zone == nullptr)
			return 1;

		try {
			StringTokenizer args(arguments.toString());
			float radius = args.getFloatToken();

			Vector3 position = creature->getWorldPosition();
			Vector3 point;
			Sphere sphere(position, radius);

			if (PathFinderManager::instance()->getSpawnPointInArea(sphere, zone, point, true)) {
				ghost->addWaypoint(zone->getZoneName(), point.getX(), point.getY());
			} else {
				creature->sendSystemMessage("Failed to find spawn point in area");
			}

		} catch (Exception& e) {
			sendSyntax(creature);
		}

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		player->sendSystemMessage("Syntax: /server spawnpointinarea radius");
	}
};

#endif //SPAWNPOINTINAREACOMMAND_H
