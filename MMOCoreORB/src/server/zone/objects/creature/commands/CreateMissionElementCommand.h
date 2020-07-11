/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATEMISSIONELEMENTCOMMAND_H_
#define CREATEMISSIONELEMENTCOMMAND_H_

#include "server/zone/managers/mission/MissionManager.h"

class CreateMissionElementCommand : public QueueCommand {
public:

	CreateMissionElementCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
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

		//Try to create a mission NPC spawn point.
		creature->getZoneServer()->getMissionManager()->createSpawnPoint(creature, arguments.toString());

		return SUCCESS;
	}

};

#endif //CREATEMISSIONELEMENTCOMMAND_H_
