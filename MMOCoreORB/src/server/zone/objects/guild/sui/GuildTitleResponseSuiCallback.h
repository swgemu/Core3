/*
 * GuildMemberTitleCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERTITLESUICALLBACK_H_
#define GUILDMEMBERTITLESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildTitleResponseSuiCallback : public SuiCallback {
public:
	GuildTitleResponseSuiCallback(ZoneProcessServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String title = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		PlayerCreature* target = (PlayerCreature*) obj.get();

		guildManager->setMemberTitle(player, target, title);
	}
};

#endif /* GUILDMEMBERTITLESUICALLBACK_H_ */
