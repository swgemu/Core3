/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "../../../managers/group/GroupManager.h"

class JoinCommand : public QueueCommand {
public:

	JoinCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		GroupManager* groupManager = GroupManager::instance();
		groupManager->joinGroup(creature);

		return SUCCESS;
	}

};

#endif //JOINCOMMAND_H_

