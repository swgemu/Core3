/*
 * GuildCreateNameResponseCallback.h
 *
 *  Created on: Oct 29, 2010
 *      Author: crush
 */

#ifndef GUILDCREATENAMERESPONSECALLBACK_H_
#define GUILDCREATENAMERESPONSECALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiMessageCallback.h"

class GuildCreateNameResponseCallback : public SuiMessageCallback {
	String guildName;

public:
	GuildCreateNameResponseCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (player->isInGuild()) {
			player->sendSystemMessage("@guild:create_fail_in_guild"); //You cannot create a guild while already in a guild.
			return;
		}

		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String guildName = args->get(0).toString();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = (Terminal*) obj.get();

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = (GuildTerminal*) terminal;

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		uint64 playerID = player->getObjectID();

		//Check if this player is already creating a guild...
		if (guildManager->isCreatingGuild(playerID))
			return;

		if (guildManager->validateGuildName(player, guildName)) {
			guildManager->addPendingGuild(playerID, guildName);
			guildManager->sendGuildCreateAbbrevTo(player, guildTerminal);
			return;
		}

		//Resend the create name box.
		player->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	}
};

#endif /* GUILDCREATENAMERESPONSECALLBACK_H_ */
