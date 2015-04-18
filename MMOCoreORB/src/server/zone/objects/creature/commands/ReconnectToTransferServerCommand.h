/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RECONNECTTOTRANSFERSERVERCOMMAND_H_
#define RECONNECTTOTRANSFERSERVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ReconnectToTransferServerCommand : public QueueCommand {
public:

	ReconnectToTransferServerCommand(const String& name, ZoneProcessServer* server)
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

#endif //RECONNECTTOTRANSFERSERVERCOMMAND_H_
