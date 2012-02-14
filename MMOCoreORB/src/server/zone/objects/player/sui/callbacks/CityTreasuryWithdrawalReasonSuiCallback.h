/*
 * CityTreasuryWithdrawalReasonSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_
#define CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"

class CityTreasuryWithdrawalReasonSuiCallback : public SuiCallback {
public:
	CityTreasuryWithdrawalReasonSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityTreasuryWithdrawalSession*> session = dynamic_cast<CityTreasuryWithdrawalSession*>(player->getActiveSession(SessionFacadeType::CITYWITHDRAW));

		if (session == NULL)
			return;

		if (!suiBox->isInputBox() || player == NULL || cancelPressed || args->size() <= 0) {
			session->cancelSession();
			return;
		}

		String reason = args->get(0).toString();
		session->sendTransferBox(reason);
	}
};

#endif /* CITYTREASURYWITHDRAWALREASONSUICALLBACK_H_ */
