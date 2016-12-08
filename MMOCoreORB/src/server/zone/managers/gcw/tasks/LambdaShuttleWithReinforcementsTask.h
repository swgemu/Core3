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

	void spawnSingleTroop(CreatureManager* creatureManager, float xOffset, float yOffset) {
		CreatureObject* npc = creatureManager->spawnCreature(TROOPTEMPLATE.hashCode(), 0, lambdaShuttle->getPositionX() + xOffset, lambdaShuttle->getPositionZ(), lambdaShuttle->getPositionY() + yOffset, 0, false);
		if (npc != NULL) {
			containmentTeam.add(npc);
		}
	}

	void spawnOneSetOfTroops() {
		ManagedReference<SceneObject*> lambdaShuttle = weakLambdaShuttle.get();
		CreatureManager* creatureManager = lambdaShuttle->getZone()->getCreatureManager();
		spawnSingleTroop(creatureManager, 0.5f, spawnNumber * 1.0f);
		spawnSingleTroop(creatureManager, -0.5f, spawnNumber * 1.0f);
		spawnNumber++;
	}

	void spawnTroops(SceneObject* lambdaShuttle) {
		spawnOneSetOfTroops();
		if (spawnNumber > difficulty) {
			state = TAKEOFF;
		}
		reschedule(750);
	}

	void lambdaShuttleSpawn(ZoneServer* zoneServer, SceneObject* lambdaShuttle, CreatureObject* player) {
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
		for (int i = containmentTeam.size() - 1; i >= 0; i--) {
			ManagedReference<CreatureObject*> npc = containmentTeam.get(i).get();
			if (npc != NULL) {
				Locker npcLock(npc);
				npc->destroyObjectFromWorld(true);
			}
			containmentTeam.remove(i);
		}
		state = FINISHED;
	}

public:
	LambdaShuttleWithReinforcementsTask(CreatureObject* player, int difficulty) {
		weakPlayer = player;
		state = SPAWN;
		this->difficulty = difficulty;
		spawnNumber = 0;

		weakLambdaShuttle = zoneServer->createObject(LAMBDATEMPLATE.hashCode(), 0);
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();
		ManagedReference<SceneObject*> lambdaShuttle = weakLambdaShuttle.get();

		if (player == NULL || lambdaShuttle == NULL) {
			return;
		}

		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer == NULL) {
			return;
		}

		Locker objLocker(lambdaShuttle);

		switch (state) {
		case SPAWN:
			lambdaShuttleSpawn(zoneServer, lambdaShuttle, player);
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
