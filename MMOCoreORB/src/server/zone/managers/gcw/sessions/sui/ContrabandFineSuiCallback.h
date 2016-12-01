/*
 * ContrabandFineSuiCallback.h
 *
 *  Created on: nov 30, 2016
 *      Author: loshult
 */

#ifndef CONTRABANDFINESUICALLBACK_H_
#define CONTRABANDFINESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/gcw/sessions/ContrabandScanSession.h"

class ContrabandFineSuiCallback : public SuiCallback {
public:
	ContrabandFineSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool acceptedFine = (eventIndex != 1);

		if (player != NULL) {
			ManagedReference<ContrabandScanSession*> scanSession = player->getActiveSession(SessionFacadeType::CONTRABANDSCAN).castTo<ContrabandScanSession*>();
			if (scanSession != NULL) {
				scanSession->setAcceptFineAnswer(acceptedFine);
			}
		}
	}
};

#endif /* CONTRABANDFINESUICALLBACK_H_ */
