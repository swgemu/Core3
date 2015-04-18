/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETLOGINMESSAGECOMMAND_H_
#define SETLOGINMESSAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetLoginMessageCommand : public QueueCommand {
public:

	SetLoginMessageCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL || !ghost->isPrivileged()) {
			creature->sendSystemMessage("@error_message:insufficient_permissions"); //You do not have sufficient permissions to perform the requested action.
			return INSUFFICIENTPERMISSION;
		}

		return SUCCESS;
	}

};

#endif //SETLOGINMESSAGECOMMAND_H_
