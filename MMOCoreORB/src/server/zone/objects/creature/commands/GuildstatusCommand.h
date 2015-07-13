/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDSTATUSCOMMAND_H_
#define GUILDSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/guild/GuildObject.h"

class GuildstatusCommand : public QueueCommand {
public:

	GuildstatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> obj = NULL;

		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		if (tokenizer.hasMoreTokens()) {
			UnicodeString targetName;
			tokenizer.getUnicodeToken(targetName);

			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

			uint64 targetPlayerID = playerManager->getObjectID(targetName.toString());

			obj = zoneServer->getObject(targetPlayerID);
		}

		if (obj == NULL || !obj->isCreatureObject())
			obj = zoneServer->getObject(target);

		if (obj == NULL || !obj->isPlayerCreature()) {
			player->sendSystemMessage("@base_player:guildstatus_not_player"); //You may only check the guild status of players.
			return GENERALERROR;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());

		StringIdChatParameter params;
		params.setTU(targetCreature->getDisplayedName());

		if (!targetCreature->isInGuild()) {
			params.setStringId("@base_player:guildstatus_not_in_guild"); //%TU is not in a guild.
			player->sendSystemMessage(params);
			return GENERALERROR;
		}

		ManagedReference<GuildObject*> guild = targetCreature->getGuildObject();
		uint64 objid = targetCreature->getObjectID();

		if (guild == NULL)
			return GENERALERROR;

		if (!guild->hasMember(objid))
			return GENERALERROR;

		String guildTitle = guild->getGuildMemberTitle(objid);
		params.setTT(guild->getGuildName());

		StringBuffer stringid;
		stringid << "@base_player:guildstatus_";

		if (guild->getGuildLeaderID() == objid)
			stringid << "leader";
		else
			stringid << "member";

		if (!guildTitle.isEmpty()) {
			stringid << "_title";
			params.setTO(guildTitle);
		}

		params.setStringId(stringid.toString());
		player->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //GUILDSTATUSCOMMAND_H_
