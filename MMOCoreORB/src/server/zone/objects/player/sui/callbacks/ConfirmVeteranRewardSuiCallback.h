/*
 * ConfirmVeteranSuiCallback.h
 *
 *  Created on: 5/30/2014
 *      Author: Klivian
 */

#ifndef CONFIRMVETERANREWARDSUICALLBACK_H_
#define CONFIRMVETERANREWARDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class ConfirmVeteranRewardSuiCallback : public SuiCallback {

public:
	ConfirmVeteranRewardSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( !suiBox->isMessageBox() || playerManager == NULL )
			return;

		if( cancelPressed ){
			playerManager->cancelVeteranRewardSession( player );
			return;
		}

		// Generate reward
		playerManager->generateVeteranReward( player );

	}
};


#endif /* CONFIRMVETERANREWARDSUICALLBACK_H_ */
