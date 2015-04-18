/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCOMMAND_H_
#define NPCCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NpcCommand : public QueueCommand {
public:

	NpcCommand(const String& name, ZoneProcessServer* server)
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

#endif //NPCCOMMAND_H_
