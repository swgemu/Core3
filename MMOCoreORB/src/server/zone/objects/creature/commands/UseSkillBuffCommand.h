/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef USESKILLBUFFCOMMAND_H_
#define USESKILLBUFFCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class UseSkillBuffCommand : public QueueCommand {
public:

	UseSkillBuffCommand(const String& name, ZoneProcessServer* server)
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

#endif //USESKILLBUFFCOMMAND_H_
