/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "server/zone/managers/group/GroupManager.h"

class JoinCommand : public QueueCommand {
public:
	JoinCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isGrouped())
			return GENERALERROR;

		Reference<CreatureObject*> creatureRef = creature;

		Core::getTaskManager()->executeTask([creatureRef] () {
			if (creatureRef == nullptr)
				return;

			GroupManager* groupManager = GroupManager::instance();

			if (groupManager == nullptr)
				return;

			groupManager->joinGroup(creatureRef);
		}, "JoinGroupLambda");

		return SUCCESS;
	}
};

#endif // JOINCOMMAND_H_
