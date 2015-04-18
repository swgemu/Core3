/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVOKESKILLCOMMAND_H_
#define REVOKESKILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RevokeSkillCommand : public QueueCommand {
public:

	RevokeSkillCommand(const String& name, ZoneProcessServer* server)
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

#endif //REVOKESKILLCOMMAND_H_
