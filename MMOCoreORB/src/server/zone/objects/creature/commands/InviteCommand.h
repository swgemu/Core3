/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INVITECOMMAND_H_
#define INVITECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/ZoneServer.h"

class InviteCommand : public QueueCommand {
public:

	InviteCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* playerObject = creature->getPlayerObject();
		bool privileged = false;

		if (playerObject)
		{
			if (playerObject->isPrivileged())
				privileged = true;
		}

		GroupManager* groupManager = GroupManager::instance();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return GENERALERROR;


		if (object->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( object.get());

			if (!player->getPlayerObject()->isIgnoring(creature->getFirstName().toLowerCase()) || privileged)
				groupManager->inviteToGroup(creature, player);
		}

		return SUCCESS;
	}

};

#endif //INVITECOMMAND_H_

