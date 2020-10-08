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
	Vector<WeakReference<AiAgent*>> containmentTeam;
	int difficulty;
	int spawnNumber;
	String chatMessageId;
	Vector3 spawnPosition;
	Quaternion spawnDirection;
	bool attack;
	int closingInTime;
	int timeToDespawnLambdaShuttle;
	int cleanUpTime;
	float spawnOffset;

	const String LAMBDATEMPLATE = "object/creature/npc/theme_park/lambda_shuttle.iff";
	const int LANDINGTIME = 18000;
	const int SPAWNDELAY = 750;
	const int TASKDELAY = 1000;
	const int CLEANUPDELAY = 60000;
	const int LAMBDATAKEOFFDESPAWNTIME = 17;

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
		UPRIGHT,
		ZONEIN,
		LAND,
		SPAWNTROOPS,
		TAKEOFF,
		CLOSINGIN,
		DELAY,
		PICKUPSPAWN,
		PICKUPUPRIGHT,
		PICKUPZONEIN,
		PICKUPLAND,
		DESPAWN,
		PICKUPTAKEOFF,
		PICKUPDESPAWN,
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
			if (attack) {
				CombatManager::instance()->startCombat(npc, player);

				if (spawnNumber == 0) {
					StringIdChatParameter chatMessage;
					chatMessage.setStringId(chatMessageId);
					zone->getZoneServer()->getChatManager()->broadcastChatMessage(npc, chatMessage, player->getObjectID(), 0, 0);
				}
			} else if (spawnNumber == 0) {
				npc->setFollowObject(player);
			} else {
				npc->setFollowObject(containmentTeam.get(Math::max(containmentTeam.size() - 2, 0)).get());
			}
			containmentTeam.add(npc);
		}
	}

	void spawnOneSetOfTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		if (troops[spawnNumber].singleSpawn) {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.0f, spawnOffset);
		} else {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.5f, spawnOffset - spawnNumber * 1.0f);
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, -0.5f, spawnOffset - spawnNumber * 1.0f);
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
		lambdaShuttle->createChildObjects();
		lambdaShuttle->_setUpdated(true);
	}

	void lambdaShuttleLanding(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::PRONE);
	}

	void lambdaShuttleUpright(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);
	}

	void lambdaShuttleTakeoff(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);
		timeToDespawnLambdaShuttle = LAMBDATAKEOFFDESPAWNTIME;
	}

	void closingInOnPlayer(CreatureObject* player) {
		if (attack) {
			state = DELAY;
		} else {
			--closingInTime;
			AiAgent* npc = containmentTeam.get(0).get();
			if (npc == nullptr) {
				state = DELAY;
			} else if (npc->getWorldPosition().distanceTo(player->getWorldPosition()) < 16 && !npc->isInCombat() && !npc->isDead()) {
				player->getZone()->getGCWManager()->startContrabandScanSession(npc, player, true);

				state = DELAY;
			} else if (closingInTime <= 0) {
				state = DELAY;
			}
		}
		reschedule(TASKDELAY);
	}

	void delay() {
		state = PICKUPSPAWN;
		reschedule(CLEANUPDELAY);
	}

	void despawnNpcs(SceneObject* lambdaShuttle) {
		--cleanUpTime;
		bool npcsLeftToDespawn = false;
		for (int i = containmentTeam.size() - 1; i >= 0; i--) {
			ManagedReference<AiAgent*> npc = containmentTeam.get(i).get();
			if (npc != nullptr) {
				Locker npcLock(npc);
				if (npc->isInCombat() && cleanUpTime >= 0) {
					npcsLeftToDespawn = true;
				} else {
					if (!npc->isDead() && npc->getWorldPosition().distanceTo(lambdaShuttle->getWorldPosition()) > 2 && cleanUpTime >= 0) {
						npc->setFollowObject(lambdaShuttle);
						npcsLeftToDespawn = true;
					} else {
						if (!npc->isDead()) {
							npc->destroyObjectFromWorld(true);
						}
						containmentTeam.remove(i);
					}
				}
			} else {
				containmentTeam.remove(i);
			}
		}

		if (!npcsLeftToDespawn || cleanUpTime < 0) {
			state = PICKUPTAKEOFF;
		}
		reschedule(TASKDELAY);
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
	LambdaShuttleWithReinforcementsTask(CreatureObject* player, unsigned int faction, unsigned int difficulty, String chatMessageId, Vector3 position, Quaternion direction, bool attack) {
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
		this->attack = attack;
		closingInTime = 120;
		timeToDespawnLambdaShuttle = -1;
		cleanUpTime = 60;
		spawnOffset = difficulty * TROOPSSPAWNPERDIFFICULTY;
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

		if (--timeToDespawnLambdaShuttle == 0) {
			lambdaShuttle->destroyObjectFromWorld(true);
		}

		switch (state) {
		case SPAWN:
			lambdaShuttleSpawn(lambdaShuttle, player);
			state = UPRIGHT;
			reschedule(TASKDELAY);
			break;
		case UPRIGHT:
			lambdaShuttleUpright(lambdaShuttle);
			state = ZONEIN;
			reschedule(TASKDELAY);
			break;
		case ZONEIN:
			player->getZone()->transferObject(lambdaShuttle, -1, true);
			state = LAND;
			reschedule(TASKDELAY);
			break;
		case LAND:
			lambdaShuttleLanding(lambdaShuttle);
			state = SPAWNTROOPS;
			reschedule(LANDINGTIME);
			break;
		case SPAWNTROOPS:
			spawnTroops(lambdaShuttle, player);
			break;
		case TAKEOFF:
			lambdaShuttleTakeoff(lambdaShuttle);
			state = CLOSINGIN;
			reschedule(TASKDELAY);
			break;
		case CLOSINGIN:
			closingInOnPlayer(player);
			break;
		case DELAY:
			delay();
			break;
		case PICKUPSPAWN:
			lambdaShuttleSpawn(lambdaShuttle, player);
			state = PICKUPUPRIGHT;
			reschedule(TASKDELAY);
			break;
		case PICKUPUPRIGHT:
			lambdaShuttleUpright(lambdaShuttle);
			state = PICKUPZONEIN;
			reschedule(TASKDELAY);
			break;
		case PICKUPZONEIN:
			player->getZone()->transferObject(lambdaShuttle, -1, true);
			state = PICKUPLAND;
			reschedule(TASKDELAY);
			break;
		case PICKUPLAND:
			lambdaShuttleLanding(lambdaShuttle);
			state = DESPAWN;
			reschedule(LANDINGTIME);
			break;
		case DESPAWN:
			despawnNpcs(lambdaShuttle);
			break;
		case PICKUPTAKEOFF:
			lambdaShuttleTakeoff(lambdaShuttle);
			state = PICKUPDESPAWN;
			reschedule(TASKDELAY);
			break;
		case PICKUPDESPAWN:
			if (timeToDespawnLambdaShuttle == 0) {
				state = FINISHED;
			}
			break;
		default:
			break;
		}
	}
};

#endif /* LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_ */
