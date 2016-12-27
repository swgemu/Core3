/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LEAVEGROUPCOMMAND_H_
#define LEAVEGROUPCOMMAND_H_

#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/group/GroupObject.h"

class LeaveGroupCommand : public QueueCommand {
public:

	LeaveGroupCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		GroupManager* groupManager = GroupManager::instance();

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL)
			return GENERALERROR;

		groupManager->leaveGroup(group.get(), creature);

		return SUCCESS;
	}

};

#endif //LEAVEGROUPCOMMAND_H_

