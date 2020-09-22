/*
 * LambdaShuttleWithReinforcementsTask.h
 *
 *  Created on: Dec 7, 2016
 *      Author: loshult
 */

#ifndef LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_
#define LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_

#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "templates/faction/Factions.h"

class LambdaShuttleWithReinforcementsTask : public Task {
	WeakReference<CreatureObject*> weakPlayer;
	WeakReference<SceneObject*> weakLambdaShuttle;
	Vector<WeakReference<CreatureObject*>> containmentTeam;
	int difficulty;
	int spawnNumber;
	String chatMessageId;
	Vector3 spawnPosition;
	Quaternion spawnDirection;

	const String LAMBDATEMPLATE = "object/creature/npc/theme_park/lambda_shuttle.iff";
	const int TIMETILLSHUTTLELANDING = 100;
	const int LANDINGTIME = 18000;
	const int SPAWNDELAY = 750;
	const int CLEANUPTIME = 30000;
	const int CLEANUPRESCHEDULETIME = 1000;

	const int TROOPSSPAWNPERDIFFICULTY = 5;

	const int MAXDIFFICULTY = 2;
	const int MINDIFFICULTY = 1;

	struct LambdaTroop {
		const String troopTemplate;
		bool singleSpawn;
	};

	LambdaTroop IMPERIALTROOPS[11] = {
			{"stormtrooper_squad_leader", true},
			{"stormtrooper", false},
			{"stormtrooper", false},
			{"stormtrooper_sniper", false},
			{"stormtrooper", false},
			{"stormtrooper_rifleman", false},
			{"stormtrooper_medic", false},
			{"stormtrooper_sniper", false},
			{"stormtrooper_rifleman", false},
			{"stormtrooper", false},
			{"stormtrooper_bombardier", false}
	};

	LambdaTroop REBELTROOPS[11] = {
			{"crackdown_rebel_guard_captain", true},
			{"crackdown_rebel_cadet", false},
			{"crackdown_rebel_soldier", false},
			{"crackdown_rebel_liberator", false},
			{"crackdown_rebel_soldier", false},
			{"crackdown_rebel_guardsman", false},
			{"crackdown_rebel_elite_sand_rat", false},
			{"crackdown_rebel_command_security_guard", false},
			{"crackdown_rebel_commando", false},
			{"crackdown_rebel_comm_operator", false},
			{"crackdown_rebel_soldier", false}
	};

	enum LamdaShuttleState {
		SPAWN,
		LAND,
		SPAWNTROOPS,
		TAKEOFF,
		CLEANUP,
		FINISHED
	};

	LamdaShuttleState state;

	LambdaTroop* troops;

	void spawnSingleTroop(SceneObject* lambdaShuttle, CreatureObject* player, const String& creatureTemplate, float xOffset, float yOffset) {
		Quaternion offset = Quaternion(0, xOffset, 0, yOffset);
		Quaternion rotation = Quaternion(Vector3(0, 1, 0), spawnDirection.getRadians());
		offset = rotation * offset * rotation.getConjugate();  // Rotate offset quaternion to match spawnDirection.

		Zone* zone = lambdaShuttle->getZone();
		float x = lambdaShuttle->getPositionX() + offset.getX();
		float y = lambdaShuttle->getPositionY() + offset.getZ();
		float z = zone->getHeight(x, y);

		AiAgent* npc = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(creatureTemplate.hashCode(), 0, x, z, y, 0, false, spawnDirection.getRadians()));

		if (npc != nullptr) {
			Locker npcLock(npc);
			npc->activateLoad("");
			CombatManager::instance()->startCombat(npc, player);
			containmentTeam.add(npc);

			if (spawnNumber == 0) {
				StringIdChatParameter chatMessage;
				chatMessage.setStringId(chatMessageId);
				zone->getZoneServer()->getChatManager()->broadcastChatMessage(npc, chatMessage, player->getObjectID(), 0, 0);
			}
		}
	}

	void spawnOneSetOfTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		if (troops[spawnNumber].singleSpawn) {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.0f, 0.0f);
		} else {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.5f, spawnNumber * 1.0f);
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, -0.5f, spawnNumber * 1.0f);
		}
		spawnNumber++;
	}

	void spawnTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		spawnOneSetOfTroops(lambdaShuttle, player);
		if (spawnNumber > difficulty * TROOPSSPAWNPERDIFFICULTY) {
			state = TAKEOFF;
		}
		reschedule(SPAWNDELAY);
	}

	void lambdaShuttleSpawn(SceneObject* lambdaShuttle, CreatureObject* player) {
		lambdaShuttle->initializePosition(spawnPosition.getX(), spawnPosition.getZ(), spawnPosition.getY());
		lambdaShuttle->setDirection(spawnDirection);
		player->getZone()->transferObject(lambdaShuttle, -1, true);
		lambdaShuttle->createChildObjects();
		lambdaShuttle->_setUpdated(true);

		reschedule(TIMETILLSHUTTLELANDING);
		state = LAND;
	}

	void lambdaShuttleLanding(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::PRONE);

		reschedule(LANDINGTIME);
		state = SPAWNTROOPS;
	}

	void lambdaShuttleTakeoff(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);

		reschedule(CLEANUPTIME);
		state = CLEANUP;
	}

	void cleanUp(SceneObject* lambdaShuttle) {
		lambdaShuttle->destroyObjectFromWorld(true);

		bool rescheduleTask = false;

		for (int i = containmentTeam.size() - 1; i >= 0; i--) {
			ManagedReference<CreatureObject*> npc = containmentTeam.get(i).get();
			if (npc != nullptr) {
				Locker npcLock(npc);
				if (npc->isInCombat()) {
					rescheduleTask = true;
				} else {
					if (!npc->isDead()) {
						npc->destroyObjectFromWorld(true);
					}
					containmentTeam.remove(i);
				}
			} else {
				containmentTeam.remove(i);
			}
		}

		if (rescheduleTask) {
			reschedule(CLEANUPRESCHEDULETIME);
		} else {
			state = FINISHED;
		}
	}

	SceneObject* getLambdaShuttle(CreatureObject* player) {
		ManagedReference<SceneObject*> lambdaShuttle = weakLambdaShuttle.get();

		if (lambdaShuttle == nullptr) {
			ZoneServer* zoneServer = player->getZoneServer();

			if (zoneServer == nullptr) {
				return nullptr;
			}

			weakLambdaShuttle = zoneServer->createObject(LAMBDATEMPLATE.hashCode(), 0);
			lambdaShuttle = weakLambdaShuttle.get();
		}

		return lambdaShuttle;
	}

public:
	LambdaShuttleWithReinforcementsTask(CreatureObject* player, unsigned int faction, unsigned int difficulty, String chatMessageId, Vector3 position, Quaternion direction) {
		weakPlayer = player;
		state = SPAWN;
		if (difficulty > MAXDIFFICULTY) {
			this->difficulty = MAXDIFFICULTY;
		} else if (difficulty < MINDIFFICULTY) {
			this->difficulty = MINDIFFICULTY;
		} else {
			this->difficulty = difficulty;
		}
		if (faction == Factions::FACTIONIMPERIAL) {
			troops = IMPERIALTROOPS;
		} else {
			troops = REBELTROOPS;
		}
		this->chatMessageId = chatMessageId;
		spawnNumber = 0;
		spawnPosition = position;
		spawnDirection = direction;
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> lambdaShuttle = getLambdaShuttle(player);

		if (lambdaShuttle == nullptr) {
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
			spawnTroops(lambdaShuttle, player);
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
