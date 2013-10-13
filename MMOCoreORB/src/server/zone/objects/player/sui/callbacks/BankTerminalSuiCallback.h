/*
 * BankTerminalSuiCallback.h
 *
 * Created on: October 13, 2013
 * by: zaphod
 */

#ifndef BANKTERMINALSUICALLBACK_H_
#define BANKTERMINALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class BankTerminalSuiCallback : public SuiCallback {
public:
	BankTerminalSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isBankTransferBox() || player == NULL || cancelPressed) {
			return;
		}

		player->sendSystemMessage("@base_player:bank_success");
	}
};

#endif /* BANKTERMINALSUICALLBACK_H_ */
