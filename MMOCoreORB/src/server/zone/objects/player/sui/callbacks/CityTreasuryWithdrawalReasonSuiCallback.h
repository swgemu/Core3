/*
 * CityTreasuryWithdrawalReasonSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_
#define CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"

class CityTreasuryWithdrawalReasonSuiCallback : public SuiCallback {
public:
	CityTreasuryWithdrawalReasonSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CityTreasuryWithdrawalSession*> session = player->getActiveSession(SessionFacadeType::CITYWITHDRAW).castTo<CityTreasuryWithdrawalSession*>();

		if (session == NULL)
			return;

		if (!suiBox->isInputBox() || cancelPressed || args->size() <= 0) {
			session->cancelSession();
			return;
		}

		String reason = args->get(0).toString();
		session->sendTransferBox(reason);
	}
};

#endif /* CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_ */
