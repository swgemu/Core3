/*
 * GuildTransferLotsSuiCallback.h
 *
 *  Created on: Oct 9, 2012
 *      Author: root
 */

#ifndef GUILDTRANSFERLOTSSUICALLBACK_H_
#define GUILDTRANSFERLOTSSUICALLBACK_H_
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildTransferLotsSuiCallback : public SuiCallback {
public:
	GuildTransferLotsSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox())
			return;

		if (cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if ( suiBox->getUsingObject() != NULL)
			guildManager->transferGuildHall(player, suiBox->getUsingObject().get());

	}

};

#endif /* GUILDTRANSFERLOTSSUICALLBACK_H_ */
