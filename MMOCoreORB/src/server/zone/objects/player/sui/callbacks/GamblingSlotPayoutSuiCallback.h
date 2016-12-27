/*
 * GamblingSlotPayoutSuiCallback.h
 *
 *  Created on: 04/29, 2012
 *      Author: Elvaron
 */

#ifndef GAMBLINGSLOTPAYOUTSUICALLBACK_H_
#define GAMBLINGSLOTPAYOUTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/minigames/GamblingManager.h"

class GamblingSlotPayoutSuiCallback : public SuiCallback {
public:
	GamblingSlotPayoutSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || player == NULL)
			return;

		player->sendMessage(suiBox->generateCloseMessage());
	}
};

#endif /* GAMBLINGSLOTSUICALLBACK_H_ */
