/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJVARCOMMAND_H_
#define OBJVARCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ObjvarCommand : public QueueCommand {
public:

	ObjvarCommand(const String& name, ZoneProcessServer* server)
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

#endif //OBJVARCOMMAND_H_
