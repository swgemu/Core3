/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERHARVESTCOMMAND_H_
#define HARVESTERHARVESTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HarvesterHarvestCommand : public QueueCommand {
public:

	HarvesterHarvestCommand(const String& name, ZoneProcessServer* server)
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

#endif //HARVESTERHARVESTCOMMAND_H_
