/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REMOVEALLOWEDPLAYERCOMMAND_H_
#define REMOVEALLOWEDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RemoveAllowedPlayerCommand : public QueueCommand {
public:

	RemoveAllowedPlayerCommand(const String& name, ZoneProcessServer* server)
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

#endif //REMOVEALLOWEDPLAYERCOMMAND_H_
