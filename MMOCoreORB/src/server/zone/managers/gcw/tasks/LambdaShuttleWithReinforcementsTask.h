/*
 * LambdaShuttleWithReinforcementsTask.h
 *
 * Created on: Dec 7, 2016
 * Author: loshult
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
#include "server/zone/managers/gcw/observers/SquadObserver.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/faction/Factions.h"

class LambdaShuttleWithReinforcementsTask : public Task {
public:
	enum ReinforcementType { LAMBDASHUTTLEATTACK, LAMBDASHUTTLESCAN, LAMBDASHUTTLEONLY, CONTAINMENTTEAM };

private:
	WeakReference<CreatureObject*> weakPlayer;
	WeakReference<SceneObject*> weakLambdaShuttle;
	ManagedReference<SquadObserver*> squadObserver;
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

	LambdaTroop IMPERIALTROOPS[11] = {
		{"crackdown_stormtrooper_squad_leader", true},
		{"crackdown_stormtrooper", false},
		{"crackdown_stormtrooper", false},
		{"crackdown_stormtrooper_sniper", false},
		{"crackdown_stormtrooper", false},
		{"crackdown_stormtrooper_rifleman", false},
		{"crackdown_stormtrooper_medic", false},
		{"crackdown_stormtrooper_sniper", false},
		{"crackdown_stormtrooper_rifleman", false},
		{"crackdown_stormtrooper", false},
		{"crackdown_stormtrooper_bombardier", false}
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
		float z = 0.f;

		if (lambdaShuttle != nullptr) {
			zone = lambdaShuttle->getZone();
			x = lambdaShuttle->getPositionX() + xOffsetRotated;
			y = lambdaShuttle->getPositionY() + yOffsetRotated;
		}

		if (reinforcementType == CONTAINMENTTEAM) {
			z = player->getPositionZ();
		} else {
			z = CollisionManager::getWorldFloorCollision(x, y, zone, true);
		}

		Reference<AiAgent*> npc = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(creatureTemplate.hashCode(), 0, x, z, y, 0, false, spawnDirection.getRadians()));

		if (npc != nullptr) {
			Locker npcLock(npc, player);

			if (reinforcementType == LAMBDASHUTTLEATTACK || reinforcementType == CONTAINMENTTEAM) {
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
			}

			npc->setAITemplate();

			if (spawnNumber != 0) {
				Vector3 formationOffset;
				formationOffset.setX(xOffset);
				formationOffset.setY(spawnNumber * -1);

				npc->writeBlackboard("formationOffset", formationOffset);
			} else {
				npc->addCreatureFlag(CreatureFlag::STATIONARY);
			}

			squadObserver->addMember(npc);
			npc->registerObserver(ObserverEventType::SQUAD, squadObserver);
		}
	}

	void spawnOneSetOfTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		auto offset = spawnOffset;
		float spawnSeparation = 1.0f;
		if (reinforcementType == CONTAINMENTTEAM) {
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

	void setupMovement(CreatureObject* player) {
		if (squadObserver == nullptr)
			return;

		AiAgent* squadLeader = squadObserver->getMember(0);

		if (squadLeader != nullptr && player != nullptr) {
			Locker slLock(squadLeader, player);

			for (int i = 1; i <= squadObserver->size(); ++i) {
				AiAgent* agent = squadObserver->getMember(i);

				if (agent == nullptr || agent->isInCombat())
					continue;

				Locker alock(agent, squadLeader);
				agent->addCreatureFlag(CreatureFlag::FOLLOW);
				agent->setFollowObject(squadLeader);
			}

			squadLeader->removeCreatureFlag(CreatureFlag::STATIONARY);
			squadLeader->addCreatureFlag(CreatureFlag::FOLLOW);
			squadLeader->setFollowObject(player);
		}

	}

	void spawnTroops(SceneObject* lambdaShuttle, CreatureObject* player) {
		if (reinforcementType == LAMBDASHUTTLESCAN && ((faction != player->getFaction() && player->getFaction() != Factions::FACTIONNEUTRAL) || (player->getPlayerObject() != nullptr && player->getPlayerObject()->hasCrackdownTefTowards(faction)))) {
			if (player->getFactionStatus() == FactionStatus::OVERT || player->getFactionStatus() == FactionStatus::COVERT) {
				reinforcementType = LAMBDASHUTTLEATTACK;
			}
		}
		if (reinforcementType != LAMBDASHUTTLEONLY) {
			spawnOneSetOfTroops(lambdaShuttle, player);
			if (spawnNumber > difficulty * TROOPSSPAWNPERDIFFICULTY) {
				if (reinforcementType == CONTAINMENTTEAM) {
					state = CLOSINGIN;
				} else {
					state = TAKEOFF;
				}

				setupMovement(player);
			}
		} else {
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
		lambdaShuttleCreature->setPosture(CreaturePosture::PRONE, true, true);
	}

	void lambdaShuttleUpright(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT, true, true);
	}

	void lambdaShuttleTakeoff(SceneObject* lambdaShuttle) {
		CreatureObject* lambdaShuttleCreature = lambdaShuttle->asCreatureObject();
		lambdaShuttleCreature->setPosture(CreaturePosture::UPRIGHT, true, true);
		timeToDespawnLambdaShuttle = LAMBDATAKEOFFDESPAWNTIME;
	}

	void closingInOnPlayer(CreatureObject* player) {
		if (reinforcementType == LAMBDASHUTTLEATTACK) {
			state = DELAY;
		} else {
			--closingInTime;
			auto npc = squadObserver->getMember(0);
			if (npc == nullptr) {
				state = DELAY;
			} else if ((npc->getWorldPosition().squaredDistanceTo(player->getWorldPosition()) < 20 * 20) && !npc->isInCombat() && !npc->isDead()) {
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
			if (reinforcementType == CONTAINMENTTEAM) {
				state = DESPAWN;
			} else {
				state = PICKUPSPAWN;
			}
		}
		reschedule(TASKDELAY);
	}

	void despawnNpcs(SceneObject* lambdaShuttle) {
		--cleanUpTime;

		if (squadObserver->despawnMembersCloseToLambdaShuttle(spawnPosition, cleanUpTime < 0)) {
			if (reinforcementType == CONTAINMENTTEAM) {
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
			zone->transferObject(lambdaShuttle, -1, true);
			return true;
		}
	}

	SceneObject* getLambdaShuttle(CreatureObject* player) {
		if (reinforcementType == CONTAINMENTTEAM) {
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
		squadObserver = new SquadObserver();

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
		if (reinforcementType == CONTAINMENTTEAM) {
			state = SPAWNTROOPS;
		} else {
			state = SPAWNSHUTTLE;
		}
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		Locker locker(player);

		if (faction == 0) {
			if (player->getFactionStatus() == FactionStatus::COVERT || player->getFactionStatus() == FactionStatus::OVERT) {
				if (player->getFaction() == Factions::FACTIONREBEL) {
					troops = IMPERIALTROOPS;
					faction = Factions::FACTIONIMPERIAL;
				} else {
					troops = REBELTROOPS;
					faction = Factions::FACTIONREBEL;
				}
			} else {
				if (player->isPlayerObject()) {
					PlayerObject* ghost = player->getPlayerObject();
					if (ghost != nullptr) {
						if (ghost->hasCrackdownTefTowards(Factions::FACTIONIMPERIAL)) {
							troops = IMPERIALTROOPS;
							faction = Factions::FACTIONIMPERIAL;
						} else if (ghost->hasCrackdownTefTowards(Factions::FACTIONREBEL)) {
							troops = REBELTROOPS;
							faction = Factions::FACTIONREBEL;
						}
					}
				}
			}
		}

		ManagedReference<SceneObject*> lambdaShuttle = getLambdaShuttle(player);

		if (lambdaShuttle == nullptr && reinforcementType != CONTAINMENTTEAM) {
			return;
		}

		Locker* cLock = nullptr;

		if (lambdaShuttle != nullptr) {
			cLock = new Locker(lambdaShuttle, player);
		}

		try {

		if (--timeToDespawnLambdaShuttle == 0) {
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
			if (reinforcementType != LAMBDASHUTTLEONLY) {
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

		} catch (Exception& e) {
			player->error() << "exception caught in LambdaShuttleWithReinforcementsTask " << e.what();
			e.printStackTrace();
		}

		if (cLock != nullptr) {
			delete cLock;
		}
	}
};

#endif /* LAMBDASHUTTLEWITHREINFORCEMENTSTASK_H_ */
