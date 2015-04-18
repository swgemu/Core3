/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTTRACELOGGINGCOMMAND_H_
#define STARTTRACELOGGINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StartTraceLoggingCommand : public QueueCommand {
public:

	StartTraceLoggingCommand(const String& name, ZoneProcessServer* server)
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

#endif //STARTTRACELOGGINGCOMMAND_H_
