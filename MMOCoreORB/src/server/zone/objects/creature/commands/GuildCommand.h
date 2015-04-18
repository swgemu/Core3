/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDCOMMAND_H_
#define GUILDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"


class GuildCommand : public QueueCommand {
public:

	GuildCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->handleGuildChat(creature, arguments);

		return SUCCESS;
	}

};

#endif //GUILDCOMMAND_H_
