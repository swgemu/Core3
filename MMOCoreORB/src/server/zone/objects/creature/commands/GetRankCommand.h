/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETRANKCOMMAND_H_
#define GETRANKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetRankCommand : public QueueCommand {
public:

	GetRankCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETRANKCOMMAND_H_
