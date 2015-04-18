/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETRANKCOMMAND_H_
#define SETRANKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetRankCommand : public QueueCommand {
public:

	SetRankCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETRANKCOMMAND_H_
