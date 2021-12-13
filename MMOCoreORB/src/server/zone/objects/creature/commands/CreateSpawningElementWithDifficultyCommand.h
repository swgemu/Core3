/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
#define CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"
#include "server/zone/managers/gcw/sessions/WildContrabandScanSession.h"

class CreateSpawningElementWithDifficultyCommand : public QueueCommand {
public:
	CreateSpawningElementWithDifficultyCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// This command has temporary been set up to test the Lambda shuttle landing routine without having to go through the contraband scan.
		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		if (!creature->isPlayerCreature()) {
			return GENERALERROR;
		}

		Reference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == nullptr || !ghost->isPrivileged()) {
			return GENERALERROR;
		}

		Reference<GCWManager*> gcwManager = creature->getZone()->getGCWManager();
		if (gcwManager == nullptr || !gcwManager->getCrackdownScansEnabled()) {
			return GENERALERROR;
		}

		StringTokenizer args(arguments.toString());

		if (!args.hasMoreTokens()) {
			Quaternion direction;
			direction.setHeadingDirection(creature->getDirection()->getRadians());
			Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(creature, Factions::FACTIONIMPERIAL, 2, "@imperial_presence/contraband_search:containment_team_imperial", creature->getWorldPosition(), direction, LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLESCAN);

			lambdaTask->schedule(1);
		} else {
			String arg = "";

			args.getStringToken(arg);

			if (arg == "closestlambda" || arg == "closestlambdanotroops" || arg == "closestcontainmentteam") {
				Reference<MissionManager*> missionManager = creature->getZoneServer()->getMissionManager();
				if (missionManager != nullptr) {
					NpcSpawnPoint::SpawnType spawnType = NpcSpawnPoint::LAMBDASHUTTLESPAWN;
					if (arg == "closestcontainmentteam") {
						spawnType = NpcSpawnPoint::CONTAINMENTTEAMSPAWN;
					}
					NpcSpawnPoint* nsp = missionManager->getFreeNpcSpawnPoint(creature->getPlanetCRC(), creature->getWorldPositionX(), creature->getWorldPositionY(), spawnType);
					if (nsp != nullptr) {
						Quaternion direction;
						direction.setHeadingDirection(nsp->getDirection()->getRadians());
						LambdaShuttleWithReinforcementsTask::ReinforcementType reinforcementType = LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLESCAN;
						if (arg == "closestlambdanotroops") {
							reinforcementType = LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLEONLY;
						} else if (arg == "closestcontainmentteam") {
							reinforcementType = LambdaShuttleWithReinforcementsTask::CONTAINMENTTEAM;
						}
						Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(creature, Factions::FACTIONIMPERIAL, 2, "@imperial_presence/contraband_search:containment_team_imperial", *(nsp->getPosition()), direction, reinforcementType);
						lambdaTask->schedule(1);
						String text = "Lambda shuttle landing coordinates = " + nsp->getPosition()->toString() + ", direction = " + String::valueOf(nsp->getDirection()->getRadians());
						creature->sendSystemMessage(text);
					} else {
						return INVALIDSTATE;
					}
				} else {
					return INVALIDSTATE;
				}
			} else if (arg == "removeclosestlambda") {
				Reference<MissionManager*> missionManager = creature->getZoneServer()->getMissionManager();
				missionManager->removeSpawnPoint(creature, "lambda");
			} else if (arg == "removeclosestcontainmentteam") {
				Reference<MissionManager*> missionManager = creature->getZoneServer()->getMissionManager();
				missionManager->removeSpawnPoint(creature, "containmentteam");
			} else if (arg == "closestreinforcement") {
				MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
				auto lambdaSpawnPoint = missionManager->getFreeNpcSpawnPoint(creature->getPlanetCRC(), creature->getWorldPositionX(), creature->getWorldPositionY(), NpcSpawnPoint::LAMBDASHUTTLESPAWN);
				auto containmentTeamSpawnPoint = missionManager->getFreeNpcSpawnPoint(creature->getPlanetCRC(), creature->getWorldPositionX(), creature->getWorldPositionY(), NpcSpawnPoint::CONTAINMENTTEAMSPAWN);

				LambdaShuttleWithReinforcementsTask::ReinforcementType reinforcementType;
				NpcSpawnPoint* spawnPoint = nullptr;

				if (lambdaSpawnPoint != nullptr && containmentTeamSpawnPoint != nullptr) {
					auto position = creature->getWorldPosition();
					if (position.distanceTo(*lambdaSpawnPoint->getPosition()) <= position.distanceTo(*containmentTeamSpawnPoint->getPosition())) {
						reinforcementType = LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLEATTACK;
						spawnPoint = lambdaSpawnPoint;
					} else {
						reinforcementType = LambdaShuttleWithReinforcementsTask::CONTAINMENTTEAM;
						spawnPoint = containmentTeamSpawnPoint;
					}
				} else if (lambdaSpawnPoint != nullptr) {
					reinforcementType = LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLEATTACK;
					spawnPoint = lambdaSpawnPoint;
				} else if (containmentTeamSpawnPoint != nullptr) {
					reinforcementType = LambdaShuttleWithReinforcementsTask::CONTAINMENTTEAM;
					spawnPoint = containmentTeamSpawnPoint;
				} else {
					creature->sendSystemMessage("No containment team or Lambda shuttle spawns in range.");
					return GENERALERROR;
				}

				String text = "Closest reinforcement spawn point is " + spawnPoint->getPosition()->toString() + ", direction " + String::valueOf(spawnPoint->getDirection()->getRadians()) + ", distance " + String::valueOf(creature->getWorldPosition().distanceTo(*spawnPoint->getPosition()));
				creature->sendSystemMessage(text);
				auto ghost = creature->getPlayerObject();
				if (ghost != nullptr) {
					ManagedReference<WaypointObject*> waypoint = creature->getZoneServer()->createObject(0xc456e788, false).castTo<WaypointObject*>();

					Locker locker(waypoint);

					waypoint->setPlanetCRC(creature->getPlanetCRC());
					waypoint->setPosition(spawnPoint->getPosition()->getX(), 0, spawnPoint->getPosition()->getY());
					waypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_FINDOBJECT);
					waypoint->setCustomObjectName("Closest Reinforcement Spawn Point", false);
					waypoint->setColor(WaypointObject::COLOR_WHITE);
					waypoint->setActive(true);

					Locker glocker(ghost);
					ghost->addWaypoint(waypoint, false, true);
				}
			} else if (arg == "probot") {
				WildContrabandScanSession* wildContrabandScanSession = new WildContrabandScanSession(creature, gcwManager->getWinningFactionDifficultyScaling());
				wildContrabandScanSession->initializeSession();
			} else {
				return INVALIDPARAMETERS;
			}
		}

		return SUCCESS;
	}
};

#endif // CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
