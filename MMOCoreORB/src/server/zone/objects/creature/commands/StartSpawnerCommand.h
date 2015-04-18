/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTSPAWNERCOMMAND_H_
#define STARTSPAWNERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StartSpawnerCommand : public QueueCommand {
public:

	StartSpawnerCommand(const String& name, ZoneProcessServer* server)
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

#endif //STARTSPAWNERCOMMAND_H_
