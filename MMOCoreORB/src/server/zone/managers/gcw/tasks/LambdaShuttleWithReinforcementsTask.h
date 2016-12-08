/*
 * LambdaShuttleWithReinforcementsTask.h
 *
 *  Created on: Dec 7, 2016
 *      Author: loshult
 */

#ifndef LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_
#define LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/creature/CreatureManager.h"

class LambdaShuttleWithReinforcementsTask : public Task {
	WeakReference<CreatureObject*> weakPlayer;
	WeakReference<SceneObject*> weakLambdaShuttle;
	Vector<WeakReference<CreatureObject*>> containmentTeam;
	int difficulty;
	int spawnNumber;

	const String LAMBDATEMPLATE = "object/creature/npc/theme_park/lambda_shuttle.iff";
	const String TROOPTEMPLATE = "stormtrooper";

	enum LamdaShuttleState {
		SPAWN,
		LAND,
		SPAWNTROOPS,
		TAKEOFF,
		CLEANUP,
		FINISHED
	};

	LamdaShuttleState state;

	void spawnSingleTroop(SceneObject* lambdaShuttle, float xOffset, float yOffset) {
		Zone* zone = lambdaShuttle->getZone();
		float x = lambdaShuttle->getPositionX() + xOffset;
		float y = lambdaShuttle->getPositionY() + yOffset;
		float z = zone->getHeight(x, y);
		CreatureObject* npc = zone->getCreatureManager()->spawnCreature(TROOPTEMPLATE.hashCode(), 0, x, z, y, 0, false);
		if (npc != NULL) {
			containmentTeam.add(npc);
		}
	}

	void spawnOneSetOfTroops(SceneObject* lambdaShuttle) {
		spawnSingleTroop(lambdaShuttle, 0.5f, spawnNumber * 1.0f);
		spawnSingleTroop(lambdaShuttle, -0.5f, spawnNumber * 1.0f);
		spawnNumber++;
	}

	void spawnTroops(SceneObject* lambdaShuttle) {
		spawnOneSetOfTroops(lambdaShuttle);
		if (spawnNumber > difficulty) {
			state = TAKEOFF;
		}
		reschedule(750);
	}

	void lambdaShuttleSpawn(SceneObject* lambdaShuttle, CreatureObject* player) {
		lambdaShuttle->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		player->getZone()->transferObject(lambdaShuttle, -1, true);
		lambdaShuttle->createChildObjects();
		lambdaShuttle->_setUpdated(true);

		reschedule(6000);
		state = LAND;
	}

	void lambdaShuttleLanding(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::PRONE);

		reschedule(18000);
		state = SPAWNTROOPS;
	}

	void lambdaShuttleTakeoff(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);

		state = CLEANUP;
		reschedule(30000);
	}

	void cleanUp(SceneObject* lambdaShuttle) {
		lambdaShuttle->destroyObjectFromWorld(true);

		bool rescheduleTask = false;

		for (int i = containmentTeam.size() - 1; i >= 0; i--) {
			ManagedReference<CreatureObject*> npc = containmentTeam.get(i).get();
			if (npc != NULL) {
				Locker npcLock(npc);
				if (npc->isInCombat()) {
					rescheduleTask = true;
				} else {
					npc->destroyObjectFromWorld(true);
					containmentTeam.remove(i);
				}
			} else {
				containmentTeam.remove(i);
			}
		}

		if (rescheduleTask) {
			reschedule(1000);
		} else {
			state = FINISHED;
		}
	}

	SceneObject* getLambdaShuttle(CreatureObject* player) {
		ManagedReference<SceneObject*> lambdaShuttle = weakLambdaShuttle.get();

		if (lambdaShuttle == NULL) {
			ZoneServer* zoneServer = player->getZoneServer();

			if (zoneServer == NULL) {
				return NULL;
			}

			weakLambdaShuttle = zoneServer->createObject(LAMBDATEMPLATE.hashCode(), 0);
			lambdaShuttle = weakLambdaShuttle.get();
		}

		return lambdaShuttle;
	}

public:
	LambdaShuttleWithReinforcementsTask(CreatureObject* player, int difficulty) {
		weakPlayer = player;
		state = SPAWN;
		this->difficulty = difficulty;
		spawnNumber = 0;
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player == NULL) {
			return;
		}

		ManagedReference<SceneObject*> lambdaShuttle = getLambdaShuttle(player);

		if (lambdaShuttle == NULL) {
			return;
		}

		Locker objLocker(lambdaShuttle);

		switch (state) {
		case SPAWN:
			lambdaShuttleSpawn(lambdaShuttle, player);
			break;
		case LAND:
			lambdaShuttleLanding(lambdaShuttle);
			break;
		case SPAWNTROOPS:
			spawnTroops(lambdaShuttle);
			break;
		case TAKEOFF:
			lambdaShuttleTakeoff(lambdaShuttle);
			break;
		case CLEANUP:
			cleanUp(lambdaShuttle);
			break;
		default:
			break;
		}
	}
};

#endif /* LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_ */
