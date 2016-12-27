/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LISTGUILDSCOMMAND_H_
#define LISTGUILDSCOMMAND_H_

#include "server/zone/managers/guild/GuildManager.h"

class ListGuildsCommand : public QueueCommand {
public:

	ListGuildsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		guildManager->sendGuildListTo(player, arguments.toString());

		return SUCCESS;
	}

};

#endif //LISTGUILDSCOMMAND_H_
