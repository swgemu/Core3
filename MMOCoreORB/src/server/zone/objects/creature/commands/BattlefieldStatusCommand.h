/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BATTLEFIELDSTATUSCOMMAND_H_
#define BATTLEFIELDSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BattlefieldStatusCommand : public QueueCommand {
public:

	BattlefieldStatusCommand(const String& name, ZoneProcessServer* server)
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

#endif //BATTLEFIELDSTATUSCOMMAND_H_
