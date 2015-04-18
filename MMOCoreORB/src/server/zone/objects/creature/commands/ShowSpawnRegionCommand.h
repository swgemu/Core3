/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWSPAWNREGIONCOMMAND_H_
#define SHOWSPAWNREGIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShowSpawnRegionCommand : public QueueCommand {
public:

	ShowSpawnRegionCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOWSPAWNREGIONCOMMAND_H_
