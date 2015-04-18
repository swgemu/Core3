/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DECLAREOVERTCOMMAND_H_
#define DECLAREOVERTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DeclareOvertCommand : public QueueCommand {
public:

	DeclareOvertCommand(const String& name, ZoneProcessServer* server)
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

#endif //DECLAREOVERTCOMMAND_H_
