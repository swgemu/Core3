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


	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0 )
			return;

		int index = Integer::valueOf(args->get(0).toString());

		PlayerObject* ghost = player->getPlayerObject();
		for (int i = 0; i < ghost->getConsentListSize(); ++i) {
			String entryName = ghost->getConsentName(i);
			if (!entryName.isEmpty() && index == i){
				ghost->removeFromConsentList(entryName);
				StringIdChatParameter stringId("base_player", "prose_unconsent");
				stringId.setTO(entryName);
				player->sendSystemMessage(stringId);
			}
		}
	}
};





#endif /* REVOKECONSENTSUICALLBACK_H_ */
