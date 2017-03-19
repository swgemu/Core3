/*
 * GuildDisbandSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDDISBANDSUICALLBACK_H_
#define GUILDDISBANDSUICALLBACK_H_


#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildDisbandSuiCallback : public SuiCallback {
public:
	GuildDisbandSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal())
			return;

		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild == NULL)
			return;

		Locker guildLocker(guild, player);

		guildManager->disbandGuild(player, guild);
	}
};


#endif /* GUILDDISBANDSUICALLBACK_H_ */
