/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMINDTRICKCOMMAND_H_
#define JEDIMINDTRICKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class JediMindTrickCommand : public QueueCommand {
public:

	JediMindTrickCommand(const String& name, ZoneProcessServer* server)
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

#endif //JEDIMINDTRICKCOMMAND_H_
