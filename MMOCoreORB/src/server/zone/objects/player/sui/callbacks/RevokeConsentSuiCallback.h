/*
 * RevokeConsentSuiCallback.h
 *
 *  Created on: may 5, 2013
 *      Author: trick77
 */

#ifndef REVOKECONSENTSUICALLBACK_H_
#define REVOKECONSENTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class RevokeConsentSuiCallback : public SuiCallback {
public:
	RevokeConsentSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0 )
			return;

		int index = Integer::valueOf(args->get(0).toString());

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == NULL || index < 0 || index >= ghost->getConsentListSize())
			return;

		String entryName = ghost->getConsentName(index);

		if (!entryName.isEmpty()) {
			ghost->removeFromConsentList(entryName);
			StringIdChatParameter stringId("base_player", "prose_unconsent"); //You revoke your consent from %TO.
			stringId.setTO(entryName);
			player->sendSystemMessage(stringId);

			PlayerManager* playerManager = server->getPlayerManager();
			Reference<CreatureObject*> targetPlayer = playerManager->getPlayer(entryName);

			if (targetPlayer != NULL) {
				StringIdChatParameter stringId2("base_player", "prose_lost_consent"); //%TO no longer consents you.
				stringId2.setTO(player->getFirstName());
				targetPlayer->sendSystemMessage(stringId2);
			}
		}
	}
};

#endif /* REVOKECONSENTSUICALLBACK_H_ */
