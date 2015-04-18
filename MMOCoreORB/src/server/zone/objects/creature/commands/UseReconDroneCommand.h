/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef USERECONDRONECOMMAND_H_
#define USERECONDRONECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class UseReconDroneCommand : public QueueCommand {
public:

	UseReconDroneCommand(const String& name, ZoneProcessServer* server)
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

#endif //USERECONDRONECOMMAND_H_
