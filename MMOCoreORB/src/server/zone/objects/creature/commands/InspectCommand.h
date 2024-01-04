/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSPECT_H_
#define INSPECT_H_

#include "QueueCommand.h"

class InspectCommand : public QueueCommand {
public:
	InspectCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!checkSpaceStates(creature))
			return INVALIDSTATE;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == nullptr)
			return INVALIDTARGET;

		creature->sendSystemMessage("Inspect has not been implemented yet.");

		return SUCCESS;
	}
};

#endif // INSPECT_H_
