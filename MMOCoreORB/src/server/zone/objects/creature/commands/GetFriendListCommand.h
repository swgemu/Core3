/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETFRIENDLISTCOMMAND_H_
#define GETFRIENDLISTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetFriendListCommand : public QueueCommand {
public:

	GetFriendListCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETFRIENDLISTCOMMAND_H_
