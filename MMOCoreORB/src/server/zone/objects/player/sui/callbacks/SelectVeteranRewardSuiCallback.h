/*
 * SelectVeteranSuiCallback.h
 *
 *  Created on: 5/23/2014
 *      Author: Klivian
 */

#ifndef SELECTVETERANREWARDSUICALLBACK_H_
#define SELECTVETERANREWARDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class SelectVeteranRewardSuiCallback : public SuiCallback {

public:
	SelectVeteranRewardSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

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

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		uint64 itemId = listBox->getMenuObjectID(index);

		// Confirm selection
		playerManager->confirmVeteranReward( player, itemId );

	}
};


#endif /* SELECTVETERANREWARDSUICALLBACK_H_ */
