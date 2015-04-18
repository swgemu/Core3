/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SPLITCREDITSWITHGROUPCOMMAND_H_
#define SPLITCREDITSWITHGROUPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SplitCreditsWithGroupCommand : public QueueCommand {
public:

	SplitCreditsWithGroupCommand(const String& name, ZoneProcessServer* server)
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

#endif //SPLITCREDITSWITHGROUPCOMMAND_H_
