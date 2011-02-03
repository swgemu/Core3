/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef GUILDSTATUSCOMMAND_H_
#define GUILDSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/guild/GuildMemberInfo.h"

class GuildstatusCommand : public QueueCommand {
public:

	GuildstatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) creature;

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

		PlayerCreature* targetCreature = (PlayerCreature*) obj.get();

		StringIdChatParameter params;
		params.setTU(targetCreature->getObjectName()->getDisplayedName());

		if (!creature->isInGuild()) {
			params.setStringId("@base_player:guildstatus_not_in_guild"); //%TU is not in a guild.
			player->sendSystemMessage(params);
			return GENERALERROR;
		}

		ManagedReference<GuildObject*> guild = targetCreature->getGuildObject();
		uint64 objid = targetCreature->getObjectID();

		if (guild == NULL)
			return GENERALERROR;

		GuildMemberInfo* gmi = guild->getMember(objid);

		if (gmi == NULL)
			return GENERALERROR;

		String guildTitle = gmi->getGuildTitle();
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
