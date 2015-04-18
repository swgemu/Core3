/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESSAMPLELOOPCOMMAND_H_
#define RESSAMPLELOOPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ResSampleLoopCommand : public QueueCommand {
public:

	ResSampleLoopCommand(const String& name, ZoneProcessServer* server)
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

#endif //RESSAMPLELOOPCOMMAND_H_
