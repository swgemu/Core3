/*
 * GuildSponsorVerifyCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSORVERIFYCALLBACK_H_
#define GUILDSPONSORVERIFYCALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildSponsorVerifyCallback : public SuiCallback {
public:
	GuildSponsorVerifyCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox())
			return;

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		PlayerCreature* sponsor = (PlayerCreature*) obj.get();

		ManagedReference<GuildObject*> guild = sponsor->getGuildObject();

		if (guild == NULL || !guild->hasSponsorPermission(sponsor->getObjectID())) {
			sponsor->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
			return;
		}

		if (cancelPressed) {
			StringIdChatParameter params;
			params.setStringId("@guild:sponsor_decline"); //%TU has declined your sponsorship.
			params.setTU(player->getObjectID());
			sponsor->sendSystemMessage(params);
		} else {
			guildManager->acceptSponsorshipRequest(sponsor, player);
		}
	}
};

#endif /* GUILDSPONSORVERIFYCALLBACK_H_ */
