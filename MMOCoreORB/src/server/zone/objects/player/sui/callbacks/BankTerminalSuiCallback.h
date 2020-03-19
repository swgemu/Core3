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

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isBankTransferBox() || player == nullptr || cancelPressed) {
			return;
		}

		if (args->size() < 2)
			return;

		int cash = Integer::valueOf(args->get(0).toString());
		int bank = Integer::valueOf(args->get(1).toString());

		if (cash < 0 || bank < 0)
			return;

		SuiBankTransferBox* suiBank = cast<SuiBankTransferBox*>( sui);

		ManagedReference<SceneObject*> bankObject = suiBank->getBank();

		if (bankObject == nullptr)
			return;

		if (!player->isInRange(bankObject, 8)){
			StringIdChatParameter params;
			params.setStringId("@ui:radial_out_of_range_prose");
			params.setTT("@terminal_name:terminal_bank");
			params.setTO("@sui:bank_credits");
			player->sendSystemMessage(params);
			return;
		}

		player->transferCredits(cash, bank);

		player->sendSystemMessage("@base_player:bank_success");
	}
};

#endif /* BANKTERMINALSUICALLBACK_H_ */
