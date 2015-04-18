/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PAUSEDANCECOMMAND_H_
#define PAUSEDANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PauseDanceCommand : public QueueCommand {
public:

	PauseDanceCommand(const String& name, ZoneProcessServer* server)
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

#endif //PAUSEDANCECOMMAND_H_
