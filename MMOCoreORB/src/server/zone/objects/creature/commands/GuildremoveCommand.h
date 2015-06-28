/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDREMOVECOMMAND_H_
#define GUILDREMOVECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/guild/GuildManager.h"

class GuildremoveCommand : public QueueCommand {
public:

	GuildremoveCommand(const String& name, ZoneProcessServer* server)
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

		if (!player->isInGuild()) {
			player->sendSystemMessage("@base_player:guildremove_not_in_guild"); //You are not in a guild.
			return GENERALERROR;
		}

		if(server == NULL)
			return GENERALERROR;

		ManagedReference<ZoneServer* > zserv = server->getZoneServer();
		if( zserv == NULL )
			return GENERALERROR;

		ManagedReference<CreatureObject*> playerToKick = NULL;
		ManagedReference<SceneObject* > targetedObject = zserv->getObject(target);
		ManagedReference<GuildObject*> guild = player->getGuildObject();
		ManagedReference<GuildManager*> guildManager = zserv->getGuildManager();
		ManagedReference<PlayerManager*> playerManager = zserv->getPlayerManager();

		if( guild == NULL || guildManager == NULL || playerManager == NULL)
			return GENERALERROR;

		String lowerNamedTarget = arguments.toString().toLowerCase();

		if(!lowerNamedTarget.isEmpty()) {
			playerToKick = playerManager->getPlayer(lowerNamedTarget);
		} else if(targetedObject != NULL && targetedObject->isPlayerCreature()) {
			playerToKick = cast<CreatureObject*>( targetedObject.get());
		} else {
			playerToKick = player;
		}

		if(playerToKick == NULL || !playerToKick->isInGuild() || !guild->hasMember(playerToKick->getObjectID())) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
			return GENERALERROR;
		}

		if(playerToKick->getObjectID() != creature->getObjectID()) {
			if(!guild->hasKickPermission(creature->getObjectID())) {
				player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
				return GENERALERROR;
			}
			guildManager->sendGuildKickPromptTo(player, playerToKick);

		} else {
			// TODO: Allow leader to leave guild once guild elections are enabled
			if(guild->getGuildLeaderID() == player->getObjectID())
				player->sendSystemMessage("Guild leader cannot leave the guild");
			else
				guildManager->leaveGuild(player, guild);
		}

		return SUCCESS;
	}

};

#endif //GUILDREMOVECOMMAND_H_
