/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISMISSGROUPMEMBERCOMMAND_H_
#define DISMISSGROUPMEMBERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"

class DismissGroupMemberCommand : public QueueCommand {
public:

	DismissGroupMemberCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		GroupManager* groupManager = GroupManager::instance();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || (!object->isPlayerCreature() && !object->isPet()))
			return GENERALERROR;

		CreatureObject* targetObject = cast<CreatureObject*>( object.get());

		ManagedReference<GroupObject*> group = creature->getGroup();
		if (group == NULL)
			return GENERALERROR;

		groupManager->kickFromGroup(group.get(), creature, targetObject);

		return SUCCESS;
	}

};

#endif //DISMISSGROUPMEMBERCOMMAND_H_

