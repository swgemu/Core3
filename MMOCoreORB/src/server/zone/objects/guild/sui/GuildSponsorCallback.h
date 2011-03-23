/*
 * GuildSponsorCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSORCALLBACK_H_
#define GUILDSPONSORCALLBACK_H_


#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildSponsorCallback : public SuiCallback {
public:
	GuildSponsorCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String playerName = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = (Terminal*) obj.get();

		if (!terminal->isGuildTerminal())
			return;

		Locker _lock(terminal);

		GuildTerminal* guildTerminal = (GuildTerminal*) terminal;

		guildManager->sponsorPlayer(player, guildTerminal, playerName);
	}
};


#endif /* GUILDSPONSORCALLBACK_H_ */
