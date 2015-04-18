/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSIGNDROIDCOMMAND_H_
#define ASSIGNDROIDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AssignDroidCommand : public QueueCommand {
public:

	AssignDroidCommand(const String& name, ZoneProcessServer* server)
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

#endif //ASSIGNDROIDCOMMAND_H_
