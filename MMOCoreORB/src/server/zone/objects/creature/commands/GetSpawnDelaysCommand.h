/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETSPAWNDELAYSCOMMAND_H_
#define GETSPAWNDELAYSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetSpawnDelaysCommand : public QueueCommand {
public:

	GetSpawnDelaysCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETSPAWNDELAYSCOMMAND_H_
