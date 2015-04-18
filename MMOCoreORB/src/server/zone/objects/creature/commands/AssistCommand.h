/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSISTCOMMAND_H_
#define ASSISTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AssistCommand : public QueueCommand {
public:

	AssistCommand(const String& name, ZoneProcessServer* server)
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

#endif //ASSISTCOMMAND_H_
