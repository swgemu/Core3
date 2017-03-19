/*
 * GuildCreateAbbrevResponseSuiCallback.h
 *
 *  Created on: Oct 29, 2010
 *      Author: crush
 */

#ifndef GUILDCREATEABBREVRESPONSESUICALLBACK_H_
#define GUILDCREATEABBREVRESPONSESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildCreateAbbrevResponseSuiCallback : public SuiCallback {
public:
	GuildCreateAbbrevResponseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		uint64 playerID = player->getObjectID();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		//If the player isn't already creating a guild, then exit.
		if (!guildManager->isCreatingGuild(playerID))
			return;

		//After this point, we have to removePendingGuild anywhere we return, since they have to be creating a guild at this point.

		if (player->isInGuild()) {
			guildManager->removePendingGuild(playerID);
			player->sendSystemMessage("@guild:create_fail_in_guild"); //You cannot create a guild while already in a guild.
			return;
		}

		if (!suiBox->isInputBox() || cancelPressed) {
			guildManager->removePendingGuild(playerID);
			return;
		}

		if (args->size() < 1) {
			guildManager->removePendingGuild(playerID);
			return;
		}

		String guildAbbrev = args->get(0).toString();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL || !obj->isTerminal()) {
			guildManager->removePendingGuild(playerID);
			return;
		}

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal()) {
			guildManager->removePendingGuild(playerID);
			return;
		}

		if (guildManager->validateGuildAbbrev(player, guildAbbrev)) {
			String guildName = guildManager->getPendingGuildName(playerID);
			guildManager->createGuild(player, guildName, guildAbbrev); //Handles the removing of the pending guild.
			return;
		}

		//Resend the create abbrev box.
		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	}
};


#endif /* GUILDCREATEABBREVRESPONSESUICALLBACK_H_ */
