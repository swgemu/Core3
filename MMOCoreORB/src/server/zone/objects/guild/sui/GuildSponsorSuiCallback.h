/*
 * GuildSponsorSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSORSUICALLBACK_H_
#define GUILDSPONSORSUICALLBACK_H_


#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildSponsorSuiCallback : public SuiCallback {
public:
	GuildSponsorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String playerName = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal())
			return;

		//Locker _lock(terminal);

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

		guildManager->sponsorPlayer(player, guildTerminal, playerName);
	}
};


#endif /* GUILDSPONSORSUICALLBACK_H_ */
