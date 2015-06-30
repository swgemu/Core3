/*
 * GuildSponsorVerifySuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDSPONSORVERIFYSUICALLBACK_H_
#define GUILDSPONSORVERIFYSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildSponsorVerifySuiCallback : public SuiCallback {
public:
	GuildSponsorVerifySuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox())
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* sponsor = cast<CreatureObject*>( obj.get());

		if (!sponsor->isOnline())
			return;

		if (!sponsor->isInRange(player, 32)) {
			sponsor->sendSystemMessage("@guild:sponsor_not_found"); // The specified person to sponsor could not be found nearby.
			return;
		}

		ManagedReference<GuildObject*> guild = sponsor->getGuildObject();

		if (guild == NULL || !guild->hasSponsorPermission(sponsor->getObjectID())) {
			sponsor->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
			return;
		}

		if (cancelPressed) {
			StringIdChatParameter params;
			params.setStringId("@guild:sponsor_decline"); // %TU has declined your sponsorship.
			params.setTU(player->getObjectID());
			sponsor->sendSystemMessage(params);
		} else {
			guildManager->acceptSponsorshipRequest(sponsor, player);
		}
	}
};

#endif /* GUILDSPONSORVERIFYSUICALLBACK_H_ */
