/*
 * CityTreasuryWithdrawalSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYTREASURYWITHDRAWALSUICALLBACK_H_
#define CITYTREASURYWITHDRAWALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"

class CityTreasuryWithdrawalSuiCallback : public SuiCallback {
public:
	CityTreasuryWithdrawalSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityTreasuryWithdrawalSession*> session = dynamic_cast<CityTreasuryWithdrawalSession*>(player->getActiveSession(SessionFacadeType::CITYSPEC));

		if (session == NULL)
			return;

		if (!suiBox->isTransferBox() || player == NULL || cancelPressed || args->size() <= 0) {
			session->cancelSession();
			return;
		}

		int value = Integer::valueOf(args->get(0).toString());

		session->withdrawCredits(value);
	}
};

#endif /* CITYTREASURYWITHDRAWALSUICALLBACK_H_ */
