/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REMOTECOMMAND_H_
#define REMOTECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RemoteCommand : public QueueCommand {
public:

	RemoteCommand(const String& name, ZoneProcessServer* server)
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

#endif //REMOTECOMMAND_H_
