/*
 * GuildTransferLeadershipSuiCallback.h
 *
 *  Created on: Oct 8, 2012
 *      Author: root
 */

#ifndef GUILDTRANSFERLEADERSHIPSUICALLBACK_H_
#define GUILDTRANSFERLEADERSHIPSUICALLBACK_H_
//#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildTransferLeadershipSuiCallback : public SuiCallback {
public:
	GuildTransferLeadershipSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
					return;

		String newOwnerName = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		guildManager->sendTransferAckTo(player, newOwnerName, suiBox->getUsingObject().get());
	}

};



#endif /* GUILDTRANSFERLEADERSHIPSUICALLBACK_H_ */
