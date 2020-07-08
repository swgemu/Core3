/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
#define CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"

class CreateSpawningElementWithDifficultyCommand : public QueueCommand {
public:

	CreateSpawningElementWithDifficultyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

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

		Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(creature, Factions::FACTIONIMPERIAL, 2, "@imperial_presence/contraband_search:containment_team_imperial");
		lambdaTask->schedule(1);

		return SUCCESS;
	}

};

#endif //CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
