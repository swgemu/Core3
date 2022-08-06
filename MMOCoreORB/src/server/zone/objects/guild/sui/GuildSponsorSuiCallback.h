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

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String playerName = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		ManagedReference<SceneObject*> sceneO = suiBox->getUsingObject().get();

		if (sceneO == nullptr || (!sceneO->isGuildTerminal() && !sceneO->isGuildManagementDroid())) {
			return;
		}

		guildManager->sponsorPlayer(player, playerName);
	}
};


#endif /* GUILDSPONSORSUICALLBACK_H_ */
