/*
 * SpawnCreatureTask.h
 *
 *  Created on: 02/08/2015
 *      Author: Miztah
 */

#ifndef SPAWNCREATURETASK_H_
#define SPAWNCREATURETASK_H_

#include "server/zone/Zone.h"
#include "server/ServerCore.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/creature/CreatureManager.h"

class SpawnCreatureTask : public Task {
	uint32 templateCRC;
	float x, z, y, respawn;
	uint64 parentID;
	bool randomRespawn;
	String zoneName;

public:
	SpawnCreatureTask(uint32 temp, float resp, String zone, float xPos, float zPos, float yPos, uint64 par, bool rand) {
		templateCRC = temp;
		respawn = resp;
		zoneName = zone;
		x = xPos;
		z = zPos;
		y = yPos;
		parentID = par;
		randomRespawn = rand;
	}

	void run() {
		ZoneServer* zoneServer = ServerCore::getZoneServer();
		Zone* zone = zoneServer->getZone(zoneName);

		if (zone == NULL)
			return;

		CreatureObject* creature = zone->getCreatureManager()->spawnCreature(templateCRC, 0, x, z, y, parentID);

		if (creature->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(creature);

			Locker locker(ai);

			ai->setRespawnTimer(respawn);

			if (randomRespawn)
				ai->setRandomRespawn(true);

			ai->activateLoad("stationary");
		}
	}
};


#endif /* SPAWNCREATURETASK_H_ */
