/*
 * CityTreasuryWithdrawalSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYTREASURYWITHDRAWALSUICALLBACK_H_
#define CITYTREASURYWITHDRAWALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"

class CityTreasuryWithdrawalSuiCallback : public SuiCallback {
public:
	CityTreasuryWithdrawalSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CityTreasuryWithdrawalSession*> session = player->getActiveSession(SessionFacadeType::CITYWITHDRAW).castTo<CityTreasuryWithdrawalSession*>();

		if (session == NULL)
			return;

		if (!suiBox->isTransferBox() || cancelPressed || args->size() <= 1) {
			session->cancelSession();
			return;
		}

		int value = Integer::valueOf(args->get(1).toString());
		session->withdrawCredits(value);
	}
};

#endif /* CITYTREASURYWITHDRAWALSUICALLBACK_H_ */
