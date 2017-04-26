/*
 * SelectVeteranSuiCallback.h
 *
 *  Created on: 5/23/2014
 *      Author: Klivian
 */

#ifndef SELECTVETERANREWARDSUICALLBACK_H_
#define SELECTVETERANREWARDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class SelectVeteranRewardSuiCallback : public SuiCallback {

public:
	SelectVeteranRewardSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( !suiBox->isListBox() || playerManager == NULL )
			return;

		if( cancelPressed ){
			playerManager->cancelVeteranRewardSession( player );
			return;
		}

		if (args->size() < 1){
			playerManager->cancelVeteranRewardSession( player );
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		if (index < 0) {
			playerManager->cancelVeteranRewardSession( player );
			return;
		}


		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		uint64 itemId = listBox->getMenuObjectID(index);

		// Confirm selection
		playerManager->confirmVeteranReward( player, itemId );

	}
};


#endif /* SELECTVETERANREWARDSUICALLBACK_H_ */
