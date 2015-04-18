/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COUPDEGRACECOMMAND_H_
#define COUPDEGRACECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CoupDeGraceCommand : public QueueCommand {
public:

	CoupDeGraceCommand(const String& name, ZoneProcessServer* server)
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

#endif //COUPDEGRACECOMMAND_H_
