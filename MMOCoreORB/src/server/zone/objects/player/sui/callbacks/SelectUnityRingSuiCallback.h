/*
 * SelectUnityRingSuiCallback.h
 *
 *  Created on: 5/3/2014
 *      Author: Klivian
 */

#ifndef SELECTUNITYRINGSUICALLBACK_H_
#define SELECTUNITYRINGSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class SelectUnityRingSuiCallback : public SuiCallback {

public:
	SelectUnityRingSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( !suiBox->isListBox() || playerManager == NULL )
			return;

		if( cancelPressed ){
			playerManager->denyUnity( player );
			return;
		}

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		uint64 itemId = listBox->getMenuObjectID(index);

		// Finialize unity proposal
		playerManager->completeUnity( player, itemId );

	}
};


#endif /* SELECTUNITYRINGSUICALLBACK_H_ */
