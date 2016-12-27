/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISBANDCOMMAND_H_
#define DISBANDCOMMAND_H_

#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"

class DisbandCommand : public QueueCommand {
public:

	DisbandCommand(const String& name, ZoneProcessServer* server)
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

		//If player not is leader, he will leave the group instead.
		//Fix 13 feb 2009 - Bankler
		if (creature != group->getLeader())
			groupManager->leaveGroup(group.get(), creature);
		else
			groupManager->disbandGroup(group.get(), creature);

		return SUCCESS;
	}

};

#endif //DISBANDCOMMAND_H_

