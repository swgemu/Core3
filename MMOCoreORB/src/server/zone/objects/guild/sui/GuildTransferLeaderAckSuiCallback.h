/*
 * GuildTransferLeaderAckSuiCallback.h
 *
 *  Created on: Oct 8, 2012
 *      Author: root
 */

#ifndef GUILDTRANSFERLEADERACKSUICALLBACK_H_
#define GUILDTRANSFERLEADERACKSUICALLBACK_H_
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"


class GuildTransferLeaderAckSuiCallback : public SuiCallback {
public:
	GuildTransferLeaderAckSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* newLeader, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		GuildObject* guild = newLeader->getGuildObject();

		if ( guild == NULL)
			return;

		// get the guild leader
		uint64 leaderID = guild->getGuildLeaderID();

		ManagedReference<SceneObject*> sceo = server->getObject(leaderID);

		ManagedReference<CreatureObject*> currentLeader = NULL;

		if (sceo != NULL && sceo->isCreatureObject()) {
			currentLeader = cast<CreatureObject*>(sceo.get());
		}

		if ( cancelPressed )
		{
			if ( currentLeader != NULL )
				currentLeader->sendSystemMessage("@guild:ml_rejected"); // That player does not want to become guild leader

			return;
		}

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if ( guildManager != NULL )
		{
			// change leadership of guild
			guildManager->transferLeadership(newLeader, currentLeader, suiBox->getUsingObject().get());

			// transfer structure to new leader ..pass the guild terminal back transferGuildHall
			guildManager->transferGuildHall(newLeader, suiBox->getUsingObject().get());
		}

	}
};

#endif /* GUILDTRANSFERLEADERACKSUICALLBACK_H_ */
