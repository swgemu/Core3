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
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/observers/ContainmentTeamObserver.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/faction/Factions.h"

class LambdaShuttleWithReinforcementsTask : public Task {
public:
	enum ReinforcementType { LAMBDASHUTTLEATTACK, LAMBDASHUTTLESCAN, LAMBDASHUTTLENOTROOPS, NOLAMBDASHUTTLEONLYTROOPS };

private:
	WeakReference<CreatureObject*> weakPlayer;
	WeakReference<SceneObject*> weakLambdaShuttle;
	ManagedReference<ContainmentTeamObserver*> containmentTeamObserver;
	int difficulty;
	int spawnNumber;
	String chatMessageId;
	Vector3 spawnPosition;
	Quaternion spawnDirection;
	int closingInTime;
	int timeToDespawnLambdaShuttle;
	int cleanUpTime;
	float spawnOffset;
	unsigned int faction;
	int delayTime;
	ReinforcementType reinforcementType;

	const String LAMBDATEMPLATE = "object/creature/npc/theme_park/lambda_shuttle.iff";
	const int LANDINGTIME = 18000;
	const int SPAWNDELAY = 750;
	const int TASKDELAY = 1000;
	const int LAMBDATAKEOFFDESPAWNTIME = 17;

	const int TROOPSSPAWNPERDIFFICULTY = 5;

	const int MAXDIFFICULTY = 2;
	const int MINDIFFICULTY = 1;

	struct LambdaTroop {
		const String troopTemplate;
		bool singleSpawn;
	};

	LambdaTroop IMPERIALTROOPS[11] = {{"stormtrooper_squad_leader", true},
									  {"stormtrooper", false},
									  {"stormtrooper", false},
									  {"stormtrooper_sniper", false},
									  {"stormtrooper", false},
									  {"stormtrooper_rifleman", false},
									  {"stormtrooper_medic", false},
									  {"stormtrooper_sniper", false},
									  {"stormtrooper_rifleman", false},
									  {"stormtrooper", false},
									  {"stormtrooper_bombardier", false}};

	LambdaTroop REBELTROOPS[11] = {{"crackdown_rebel_guard_captain", true},	  {"crackdown_rebel_cadet", false},
								   {"crackdown_rebel_soldier", false},		  {"crackdown_rebel_liberator", false},
								   {"crackdown_rebel_soldier", false},		  {"crackdown_rebel_guardsman", false},
								   {"crackdown_rebel_elite_sand_rat", false}, {"crackdown_rebel_command_security_guard", false},
								   {"crackdown_rebel_commando", false},		  {"crackdown_rebel_comm_operator", false},
								   {"crackdown_rebel_soldier", false}};

	enum LamdaShuttleState {
		SPAWNSHUTTLE,
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
		float rotationRadians = spawnDirection.getRadians();
		float xOffsetRotated = xOffset * Math::cos(rotationRadians) + yOffset * Math::sin(rotationRadians);
		float yOffsetRotated = -xOffset * Math::sin(rotationRadians) + yOffset * Math::cos(rotationRadians);

		Zone* zone = player->getZone();

		if (zone == nullptr) {
			return;
		}

		float x = spawnPosition.getX() + xOffsetRotated;
		float y = spawnPosition.getY() + yOffsetRotated;
		if (lambdaShuttle != nullptr) {
			zone = lambdaShuttle->getZone();
			x = lambdaShuttle->getPositionX() + xOffsetRotated;
			y = lambdaShuttle->getPositionY() + yOffsetRotated;
		}

		float z = CollisionManager::getWorldFloorCollision(x, y, zone, false);

		Reference<AiAgent*> npc = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(creatureTemplate.hashCode(), 0, x, z, y, 0, false, spawnDirection.getRadians()));

		if (npc != nullptr) {
			Locker npcLock(npc);
			npc->activateLoad("combatpatrol");
			if (reinforcementType == LAMBDASHUTTLEATTACK) {
				CombatManager::instance()->startCombat(npc, player);

				if (spawnNumber == 0) {
					StringIdChatParameter chatMessage;
					chatMessage.setStringId(chatMessageId);
					auto zoneServer = zone->getZoneServer();
					if (zoneServer != nullptr) {
						auto chatManager = zoneServer->getChatManager();
						if (chatManager != nullptr) {
							chatManager->broadcastChatMessage(npc, chatMessage, player->getObjectID(), 0, 0);
						}
					}
				}
			} else {
				if (spawnNumber == 0) {
					npc->setFollowObject(player);
				} else {
					npc->setFollowObject(containmentTeamObserver->getMember(Math::max(containmentTeamObserver->size() - 2, 0)));
				}
				npc->registerObserver(ObserverEventType::DEFENDERADDED, containmentTeamObserver);
			}

			containmentTeamObserver->addMember(npc);
		}
	}

	void spawnOneSetOfTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		auto offset = spawnOffset;
		float spawnSeparation = 1.0f;
		if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
			offset /= 2;
			spawnSeparation /= 2;
		}
		if (troops[spawnNumber].singleSpawn) {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.0f, offset);
		} else {
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, 0.5f, offset - spawnNumber * spawnSeparation);
			spawnSingleTroop(lambdaShuttle, player, troops[spawnNumber].troopTemplate, -0.5f, offset - spawnNumber * spawnSeparation);
		}
		spawnNumber++;
	}

	void spawnTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		if (reinforcementType == LAMBDASHUTTLESCAN && ((faction != player->getFaction() && player->getFaction() != Factions::FACTIONNEUTRAL) ||
													   (player->getPlayerObject() != nullptr && player->getPlayerObject()->hasCrackdownTefTowards(faction)))) {
			if (player->getFactionStatus() == FactionStatus::OVERT || player->getFactionStatus() == FactionStatus::COVERT) {
				reinforcementType = LAMBDASHUTTLEATTACK;
			}
		}
		if (reinforcementType != LAMBDASHUTTLENOTROOPS) {
			spawnOneSetOfTroops(lambdaShuttle, player);
			if (spawnNumber > difficulty * TROOPSSPAWNPERDIFFICULTY) {
				if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
					state = CLOSINGIN;
				} else {
					state = TAKEOFF;
				}
			}
		} else {
			state = TAKEOFF;
		}
		reschedule(SPAWNDELAY);
	}

	void lambdaShuttleSpawn(SceneObject* lambdaShuttle, CreatureObject* player) {
		Locker objLocker(lambdaShuttle);
		lambdaShuttle->initializePosition(spawnPosition.getX(), spawnPosition.getZ(), spawnPosition.getY());
		lambdaShuttle->setDirection(spawnDirection);
		lambdaShuttle->createChildObjects();
		lambdaShuttle->_setUpdated(true);
	}

	void lambdaShuttleLanding(SceneObject* lambdaShuttle) {
		Locker objLocker(lambdaShuttle);
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::PRONE);
	}

	void lambdaShuttleUpright(SceneObject* lambdaShuttle) {
		Locker objLocker(lambdaShuttle);
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);
	}

	void lambdaShuttleTakeoff(SceneObject* lambdaShuttle) {
		Locker objLocker(lambdaShuttle);
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT);
		timeToDespawnLambdaShuttle = LAMBDATAKEOFFDESPAWNTIME;
	}

	void closingInOnPlayer(CreatureObject* player) {
		if (reinforcementType == LAMBDASHUTTLEATTACK) {
			state = DELAY;
		} else {
			--closingInTime;
			auto npc = containmentTeamObserver->getMember(0);
			if (npc == nullptr) {
				state = DELAY;
			} else if (npc->getWorldPosition().distanceTo(player->getWorldPosition()) < 12 && !npc->isInCombat() && !npc->isDead()) {
				auto zone = player->getZone();
				if (zone != nullptr) {
					auto gcwManager = zone->getGCWManager();
					if (gcwManager != nullptr) {
						gcwManager->startContrabandScanSession(npc, player, true);
					}
				}

				state = DELAY;
			} else if (closingInTime <= 0) {
				state = DELAY;
			}
		}
		reschedule(TASKDELAY);
	}

	void delay() {
		if (--delayTime <= 0) {
			if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
				state = DESPAWN;
			} else {
				state = PICKUPSPAWN;
			}
		}
		reschedule(TASKDELAY);
	}

	void despawnNpcs(SceneObject* lambdaShuttle) {
		--cleanUpTime;

		if (containmentTeamObserver->despawnMembersCloseToLambdaShuttle(spawnPosition, cleanUpTime < 0)) {
			if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
				state = FINISHED;
			} else {
				state = PICKUPTAKEOFF;
			}
		}
		reschedule(TASKDELAY);
	}

	bool transferLambdaShuttle(CreatureObject* player, SceneObject* lambdaShuttle) {
		Zone* zone = player->getZone();
		if (zone == nullptr) {
			return false;
		} else {
			Locker objLocker(lambdaShuttle);
			zone->transferObject(lambdaShuttle, -1, true);
			return true;
		}
	}

	SceneObject* getLambdaShuttle(CreatureObject* player) {
		if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
			return nullptr;
		}

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
	LambdaShuttleWithReinforcementsTask(CreatureObject* player, unsigned int faction, unsigned int difficulty, String chatMessageId, Vector3 position, Quaternion direction, ReinforcementType reinforcementType) {
		weakPlayer = player;
		containmentTeamObserver = new ContainmentTeamObserver();
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
		closingInTime = 120;
		timeToDespawnLambdaShuttle = -1;
		cleanUpTime = 60;
		spawnOffset = difficulty * TROOPSSPAWNPERDIFFICULTY;
		this->faction = faction;
		delayTime = 90;
		this->reinforcementType = reinforcementType;
		if (reinforcementType == NOLAMBDASHUTTLEONLYTROOPS) {
			state = SPAWNTROOPS;
		} else {
			state = SPAWNSHUTTLE;
		}
		spawnPosition.setZ(player->getZone()->getHeight(spawnPosition.getX(), spawnPosition.getY()));
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> lambdaShuttle = getLambdaShuttle(player);

		if (lambdaShuttle == nullptr && reinforcementType != NOLAMBDASHUTTLEONLYTROOPS) {
			return;
		}

		if (--timeToDespawnLambdaShuttle == 0) {
			Locker objLocker(lambdaShuttle);
			lambdaShuttle->destroyObjectFromWorld(true);
			weakLambdaShuttle = nullptr;
		}

		switch (state) {
		case SPAWNSHUTTLE:
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
			if (transferLambdaShuttle(player, lambdaShuttle)) {
				state = LAND;
			} else {
				state = FINISHED;
			}
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
			if (reinforcementType != LAMBDASHUTTLENOTROOPS) {
				state = CLOSINGIN;
			} else {
				state = PICKUPDESPAWN;
			}
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
			if (transferLambdaShuttle(player, lambdaShuttle)) {
				state = PICKUPLAND;
			} else {
				state = FINISHED;
			}
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
			reschedule(TASKDELAY);
			break;
		default:
			break;
		}
	}
};

#endif /* LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_ */
