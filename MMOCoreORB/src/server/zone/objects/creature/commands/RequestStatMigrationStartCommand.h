/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSTATMIGRATIONSTARTCOMMAND_H_
#define REQUESTSTATMIGRATIONSTARTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"

class RequestStatMigrationStartCommand : public QueueCommand {
public:

	RequestStatMigrationStartCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		return SUCCESS;
	}

};

#endif //REQUESTSTATMIGRATIONSTARTCOMMAND_H_
