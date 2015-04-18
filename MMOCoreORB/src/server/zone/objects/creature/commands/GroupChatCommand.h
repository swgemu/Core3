/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPCHATCOMMAND_H_
#define GROUPCHATCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"


class GroupChatCommand : public QueueCommand {
public:

	GroupChatCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->handleGroupChat( creature, arguments);

		return SUCCESS;
	}

};

#endif //GROUPCHATCOMMAND_H_

