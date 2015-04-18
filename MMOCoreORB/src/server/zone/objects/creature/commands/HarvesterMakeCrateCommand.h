/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERMAKECRATECOMMAND_H_
#define HARVESTERMAKECRATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HarvesterMakeCrateCommand : public QueueCommand {
public:

	HarvesterMakeCrateCommand(const String& name, ZoneProcessServer* server)
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

#endif //HARVESTERMAKECRATECOMMAND_H_
