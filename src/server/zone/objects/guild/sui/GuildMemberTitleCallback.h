/*
 * GuildMemberTitleCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERTITLECALLBACK_H_
#define GUILDMEMBERTITLECALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiMessageCallback.h"

class GuildMemberTitleCallback : public SuiMessageCallback {
public:
	GuildMemberTitleCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isInputBox() || cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		//TODO: Set title
	}
};

#endif /* GUILDMEMBERTITLECALLBACK_H_ */
