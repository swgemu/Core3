/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
#define CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"

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
			Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(
				creature, Factions::FACTIONIMPERIAL, 2, "@imperial_presence/contraband_search:containment_team_imperial", creature->getWorldPosition(), direction);
			lambdaTask->schedule(1);
		} else {
			String arg = "";

			args.getStringToken(arg);

			if (arg == "closestlambda") {
				Reference<MissionManager*> missionManager = creature->getZoneServer()->getMissionManager();
				if (missionManager != nullptr) {
					NpcSpawnPoint* nsp = missionManager->getFreeNpcSpawnPoint(creature->getPlanetCRC(), creature->getWorldPositionX(),
																			  creature->getWorldPositionY(), NpcSpawnPoint::LAMBDASHUTTLESPAWN);
					if (nsp != nullptr) {
						Quaternion direction;
						direction.setHeadingDirection(nsp->getDirection()->getRadians());
						Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(
							creature, Factions::FACTIONIMPERIAL, 2, "@imperial_presence/contraband_search:containment_team_imperial", *(nsp->getPosition()), direction);
						lambdaTask->schedule(1);
						String text = "Lambda shuttle landing coordinates = " + nsp->getPosition()->toString() + ", direction = " + String::valueOf(nsp->getDirection()->getRadians());
						creature->sendSystemMessage(text);
					} else {
						return INVALIDSTATE;
					}
				} else {
					return INVALIDSTATE;
				}
			} else {
				return INVALIDPARAMETERS;
			}
		}

		return SUCCESS;
	}
};

#endif // CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
