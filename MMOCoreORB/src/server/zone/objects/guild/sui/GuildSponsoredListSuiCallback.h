/*
 * GuildSponsoredListSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSOREDLISTSUICALLBACK_H_
#define GUILDSPONSOREDLISTSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildSponsoredListSuiCallback : public SuiCallback {
public:
	GuildSponsoredListSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

		ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

		if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
			return;
		}

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		uint64 playerID = listBox->getMenuObjectID(index);

		guildManager->sendGuildSponsoredOptionsTo(player, guild, playerID, guildTerminal);
	}
};

#endif /* GUILDSPONSOREDLISTSUICALLBACK_H_ */
