/*
 * ProposeUnitySuiCallback.h
 *
 *  Created on: 5/2/2014
 *      Author: Klivian
 */

#ifndef PROPOSEUNITYSUICALLBACK_H_
#define PROPOSEUNITYSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class ProposeUnitySuiCallback : public SuiCallback {

public:

	ProposeUnitySuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();
		if( playerManager == NULL )
			return;

		if( cancelPressed ){
			playerManager->denyUnity( creature );
		}
		else{
			playerManager->acceptUnity( creature );
		}

	}
};

#endif /* PROPOSEUNITYSUICALLBACK_H_ */
